//
// Created by yurychu on 22.03.2021.
//

#pragma once

#include <type_traits>


template<typename TypeOfValue>
class ValueCounter
{
private:
    TypeOfValue _value;
    size_t _count;

public:
    ValueCounter();
    ~ValueCounter() = default;

    TypeOfValue getValue() const;
    size_t getCount() const;

    bool isSame(const TypeOfValue& value) const;
    void add(const TypeOfValue& value);

    void plusOneMoreTime();
    void updateTarget(const TypeOfValue& value);
    void reset();

};


template<typename TypeOfValue>
ValueCounter<TypeOfValue>::ValueCounter()
    : _value{},
    _count{0}
{
    if (std::is_integral_v<TypeOfValue>){
        _value = static_cast<TypeOfValue>(0);
    }
}

template<typename TypeOfValue>
void ValueCounter<TypeOfValue>::add(const TypeOfValue& value)
{
    if (_value == value){
        _count++;
    }
    else {
        _value = value;
        _count = 1;
    }
}

template<typename TypeOfValue>
TypeOfValue ValueCounter<TypeOfValue>::getValue() const
{
    return _value;
}

template<typename TypeOfValue>
size_t ValueCounter<TypeOfValue>::getCount() const
{
    return _count;
}

template<typename TypeOfValue>
bool ValueCounter<TypeOfValue>::isSame(const TypeOfValue &value) const
{
    return _value == value;
}

template<typename TypeOfValue>
void ValueCounter<TypeOfValue>::plusOneMoreTime()
{
    _count++;
}

template<typename TypeOfValue>
void ValueCounter<TypeOfValue>::updateTarget(const TypeOfValue &value)
{
    _value = value;
    _count = 1;
}

template<typename TypeOfValue>
void ValueCounter<TypeOfValue>::reset()
{
    _count = 0;
}


