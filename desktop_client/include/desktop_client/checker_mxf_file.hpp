#pragma once

#include <sstream>
#include <QJsonObject>
#include <QString>

void check_file_with_out(std::stringstream &ss,
                         const QString& filePath,
                         const QJsonObject& obj);
