#pragma once
#include "Array.h"
#include <string>
#include <iostream>

// Відкрите успадкування від базового класу Array
class Set : public Array
{
public:
    // Конструктор без аргументів (порожня множина розміром 256 елементів)
    Set();
    // Конструктор ініціалізації одним символом
    Set(char ch);
    // Конструктор ініціалізації рядком символів
    Set(const std::string& chars);
    // Конструктор копіювання
    Set(const Set& other);
    // Деструктор
    ~Set() override;

    // Гетер та сетер ознаки входження символу (допустимі значення: 0 або 1)
    int getFlag(unsigned char ch) const;
    void setFlag(unsigned char ch, int flag);

    // Перевизначення сетера елемента базового класу для контролю значень (лише 0 або 1)
    void setElement(int index, int value);

    // Методи множини: обчислення кількості елементів, перевірка належності та підмножини
    int count() const;
    bool contains(char ch) const;
    bool isSubsetOf(const Set& other) const;

    // Операція присвоювання
    Set& operator=(const Set& other);

    // Операції з присвоюванням:
    Set& operator+=(char ch);          // Включення елементу у множину
    Set& operator-=(char ch);          // Вилучення елементу із множини
    Set& operator|=(const Set& other); // Об'єднання множин з присвоюванням
    Set& operator+=(const Set& other); // Альтернативне об'єднання з присвоюванням
    Set& operator&=(const Set& other); // Перетин множин з присвоюванням
    Set& operator*=(const Set& other); // Альтернативний перетин з присвоюванням
    Set& operator-=(const Set& other); // Різниця множин з присвоюванням

    // Бінарні операції над множинами та елементами:
    friend Set operator+(const Set& s, char ch);          // Включення елементу
    friend Set operator+(char ch, const Set& s);          // Включення елементу (комутативність)
    friend Set operator-(const Set& s, char ch);          // Вилучення елементу

    friend Set operator|(const Set& lhs, const Set& rhs); // Об'єднання множин (АБО)
    friend Set operator+(const Set& lhs, const Set& rhs); // Об'єднання множин
    friend Set operator&(const Set& lhs, const Set& rhs); // Перетин множин (І)
    friend Set operator*(const Set& lhs, const Set& rhs); // Перетин множин
    friend Set operator-(const Set& lhs, const Set& rhs); // Різниця множин

    // Операції порівняння та перевірки входження однієї множини в іншу:
    friend bool operator==(const Set& lhs, const Set& rhs);
    friend bool operator!=(const Set& lhs, const Set& rhs);
    friend bool operator<=(const Set& lhs, const Set& rhs); // lhs є підмножиною rhs
    friend bool operator<(const Set& lhs, const Set& rhs);  // lhs є строгою підмножиною rhs
    friend bool operator>=(const Set& lhs, const Set& rhs); // rhs є підмножиною lhs
    friend bool operator>(const Set& lhs, const Set& rhs);  // rhs є строгою підмножиною lhs

    // Перетворення до літерного рядка
    operator std::string() const;

    // Операції вводу та виводу
    friend std::ostream& operator<<(std::ostream& out, const Set& s);
    friend std::istream& operator>>(std::istream& in, Set& s);
};