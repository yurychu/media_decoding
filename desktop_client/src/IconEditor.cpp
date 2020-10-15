
#include <desktop_client/IconEditor.hpp>

#include <QPainter>
#include <QRegion>
#include <QMouseEvent>
#include <QPaintEvent>

IconEditor::IconEditor(QWidget *parent)
        : QWidget(parent)
{
    // Содержимое виджета не изменяется при изменении его размеров
    setAttribute(Qt::WA_StaticContents);
    // политика желательно или не желательно растягивать или сжимать
    // горизонтальная и вертикальная политики
    // тут меньше минимума sizeHint() сжать нельзя
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    // В qt designere можо менять sizePolicy


    curColor = Qt::black;
    zoom = 16;

    image = QImage(16, 16, QImage::Format_ARGB32);
    image.fill(qRgba(0, 0, 0, 0));
}

void IconEditor::setPenColor(const QColor &newColor)
{
    curColor = newColor;
}

void IconEditor::setZoomFactor(int newZoom)
{
    if (newZoom < 1){
        newZoom = 1;
    }

    if (newZoom != zoom) {
        zoom = newZoom;
        update();
        updateGeometry();
    }
}

void IconEditor::setIconImage(const QImage &newImage)
{
    if (newImage != image) {
        image = newImage.convertToFormat(QImage::Format_ARGB32);
        update(); // перерисовка с новым изображением, помещается в очередь, в отл. от repaint(), она сразу.
        updateGeometry();  // сообщаем менеджерам компоновки об изменении размера
    }
}

QSize IconEditor::sizeHint() const
{
    QSize size = zoom * image.size();
    if (zoom >= 3){
        size += QSize(1, 1); //  если больше 3х добавляем пиксель для размещения сетки
    }
    return size;
}

void IconEditor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    }
    else if (event->button() == Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    }
    else if (event->buttons() & Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (zoom >= 3) {  // тут рисуется сетка
        painter.setPen(palette().windowText().color());

        for (int i = 0; i <= image.width(); ++i){
            painter.drawLine(zoom * i, 0,
                             zoom * i, zoom * image.height());
        }

        for (int j = 0; j <= image.height(); ++j){
            painter.drawLine(0, zoom * j,
                             zoom * image.width(), zoom * j);
        }
    }

    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            QRect rect = pixelRect(i, j);
            if (!event->region().intersected(rect).isEmpty()) {
                QColor color = QColor::fromRgba(image.pixel(i, j));
                if (color.alpha() < 255){
                    painter.fillRect(rect, Qt::white);
                }
                painter.fillRect(rect, color);
            }
        }
    }
}

void IconEditor::setImagePixel(const QPoint &pos, bool opaque)
{
    int i = pos.x() / zoom;
    int j = pos.y() / zoom;

    if (image.rect().contains(i, j)) {
        if (opaque) {
            image.setPixel(i, j, penColor().rgba());
        }
        else {
            image.setPixel(i, j, qRgba(0, 0, 0, 0));
        }

        update(pixelRect(i, j));
    }
}

QRect IconEditor::pixelRect(int i, int j) const
{
    if (zoom >= 3) {
        // уменьшаем, что бы не загораживать линии сетки
        return QRect(zoom * i + 1, zoom * j + 1, zoom - 1, zoom - 1);
    }
    else {
        return QRect(zoom * i, zoom * j, zoom, zoom);
    }
}
