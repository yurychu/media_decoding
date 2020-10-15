#pragma once

#include <QColor>
#include <QImage>
#include <QWidget>


class IconEditor : public QWidget
{
Q_OBJECT  // необходим для классов в которых определяются свойства

    // объявляются пользовательские свойства
    // Появляются в QT Designer в редакторе свойств
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
    explicit IconEditor(QWidget *parent = nullptr);

    void setPenColor(const QColor &newColor);
    QColor penColor() const { return curColor; }
    void setZoomFactor(int newZoom);
    int zoomFactor() const { return zoom; }
    void setIconImage(const QImage &newImage); // юзается снаружи
    QImage iconImage() const { return image; }
    QSize sizeHint() const override;  // полезно для менеджеров компоновки

protected:
    // protected event handlers
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void setImagePixel(const QPoint &pos, bool opaque);
    QRect pixelRect(int i, int j) const;

private:
    QColor curColor;
    QImage image;
    int zoom;
};
