#pragma once

#include <QTableWidgetItem>

// Не имеет сигналов и слотов, не наследует QObject
// Это для оптимизации
class Cell : public QTableWidgetItem
{
public:
    Cell();

    QTableWidgetItem *clone() const override;
    void setData(int role, const QVariant &value) override;
    QVariant data(int role) const override;
    void setFormula(const QString &formula);
    QString formula() const;
    void setDirty();

private:
    QVariant value() const;

    // тут блок синтаксического анализа для формулы и ее вычисление
    QVariant evalExpression(const QString &str, int &pos) const;
    QVariant evalTerm(const QString &str, int &pos) const;
    QVariant evalFactor(const QString &str, int &pos) const;

private:
    mutable QVariant cachedValue;
    mutable bool cacheIsDirty;
};
