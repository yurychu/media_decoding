#pragma once




#include <QSpinBox>
#include <QRegExpValidator>


class HexSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit HexSpinBox(QWidget *parent = nullptr);

protected:
    QValidator::State validate(QString &text, int &pos) const override;
    int valueFromText(const QString &text) const override;
    QString textFromValue(int value) const override;

private:
    QRegExpValidator *validator;
};
