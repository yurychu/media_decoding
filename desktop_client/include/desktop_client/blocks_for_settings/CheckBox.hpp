#pragma once

#include <QCheckBox>

const QString& getEnableLiteral();

QCheckBox* makeUncheckedCheckBox(const QString& text, QWidget*parent=nullptr);