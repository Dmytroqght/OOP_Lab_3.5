#pragma once
#include <iostream>
#include <string>

class Array
{
public:
    // Максимально можливий розмір масиву (статична константа)
    static const int MAX_SIZE = 256;

private:
    int data[MAX_SIZE]; // Масив елементів
    int size;           // Фактична кількість елементів у поточному об'єкті-масиві

public:
    // Конструктор ініціалізації та конструктор без аргументів (за умовчанням size = 0, initVal = 0)
    Array(int n = 0, int initVal = 0);
    // Конструктор копіювання
    Array(const Array& other);
    // Деструктор
    virtual ~Array();

    // Метод перевірки входження індексу в допустимий діапазон
    bool rangeCheck(int index) const;

    // Гетери (методи отримання значень)
    int getSize() const { return size; }
    int getElement(int index) const;

    // Сетери (методи встановлення значень із контролем коректності)
    void setSize(int value);
    void setElement(int index, int value);

    // Перевантаження операції присвоювання
    Array& operator=(const Array& other);

    // Перевантаження операції індексування (для зміни та для читання)
    int& operator[](int index);
    const int& operator[](int index) const;

    // Операція приведення типу до string
    operator std::string() const;

    // Дружні функції вводу та виводу
    friend std::ostream& operator<<(std::ostream& out, const Array& r);
    friend std::istream& operator>>(std::istream& in, Array& r);
};