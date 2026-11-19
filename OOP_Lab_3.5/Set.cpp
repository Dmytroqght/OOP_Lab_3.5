#include "Set.h"
#include <sstream>
#include <cstdlib>
#include <cctype>

using namespace std;

// Конструктор без аргументів: створює масив на 256 елементів, заповнений нулями
Set::Set() : Array(MAX_SIZE, 0)
{
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        setFlag(static_cast<unsigned char>(i), 0);
    }
}

// Конструктор ініціалізації одним символом (звертається до сетерів)
Set::Set(char ch) : Array(MAX_SIZE, 0)
{
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        setFlag(static_cast<unsigned char>(i), 0);
    }
    setFlag(static_cast<unsigned char>(ch), 1);
}

// Конструктор ініціалізації рядком символів (звертається до сетерів)
Set::Set(const string& chars) : Array(MAX_SIZE, 0)
{
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        setFlag(static_cast<unsigned char>(i), 0);
    }
    for (size_t i = 0; i < chars.length(); ++i)
    {
        setFlag(static_cast<unsigned char>(chars[i]), 1);
    }
}

// Конструктор копіювання (звертається до сетерів)
Set::Set(const Set& other) : Array(MAX_SIZE, 0)
{
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        unsigned char idx = static_cast<unsigned char>(i);
        setFlag(idx, other.getFlag(idx));
    }
}

// Деструктор
Set::~Set()
{
}

// Гетер ознаки присутності символу в множині
int Set::getFlag(unsigned char ch) const
{
    return getElement(static_cast<int>(ch));
}

// Сетер ознаки присутності символу (дозволяє записати лише 0 або 1)
void Set::setFlag(unsigned char ch, int flag)
{
    if (flag != 0 && flag != 1)
    {
        cerr << "Error: Invalid set flag (" << flag << "). Only 0 or 1 is allowed!" << endl;
        exit(1);
    }
    Array::setElement(static_cast<int>(ch), flag);
}

// Перевизначений сетер базового класу для захисту інваріанту множини (0 або 1)
void Set::setElement(int index, int value)
{
    if (value != 0 && value != 1)
    {
        cerr << "Error: Invalid set element value (" << value << "). Only 0 or 1 is allowed!" << endl;
        exit(1);
    }
    Array::setElement(index, value);
}

// Обчислення фактичної кількості елементів у множині (кількість одиниць у масиві)
int Set::count() const
{
    int total = 0;
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (getFlag(static_cast<unsigned char>(i)) == 1)
            ++total;
    }
    return total;
}

// Перевірка наявності символу в множині
bool Set::contains(char ch) const
{
    return getFlag(static_cast<unsigned char>(ch)) == 1;
}

// Перевірка входження поточної множини в множину other (this <= other)
bool Set::isSubsetOf(const Set& other) const
{
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        unsigned char idx = static_cast<unsigned char>(i);
        if (getFlag(idx) == 1 && other.getFlag(idx) == 0)
            return false;
    }
    return true;
}

// Операція присвоювання
Set& Set::operator=(const Set& other)
{
    if (this == &other)
        return *this;

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        unsigned char idx = static_cast<unsigned char>(i);
        setFlag(idx, other.getFlag(idx));
    }
    return *this;
}

// Включення елементу у множину з присвоюванням
Set& Set::operator+=(char ch)
{
    setFlag(static_cast<unsigned char>(ch), 1);
    return *this;
}

// Вилучення елементу із множини з присвоюванням
Set& Set::operator-=(char ch)
{
    setFlag(static_cast<unsigned char>(ch), 0);
    return *this;
}

// Об'єднання множин з присвоюванням (операція "АБО" над відповідними позиціями)
Set& Set::operator|=(const Set& other)
{
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        unsigned char idx = static_cast<unsigned char>(i);
        int combined = (getFlag(idx) == 1 || other.getFlag(idx) == 1) ? 1 : 0;
        setFlag(idx, combined);
    }
    return *this;
}

Set& Set::operator+=(const Set& other)
{
    return (*this |= other);
}

// Перетин множин з присвоюванням (операція "І" над відповідними позиціями)
Set& Set::operator&=(const Set& other)
{
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        unsigned char idx = static_cast<unsigned char>(i);
        int intersected = (getFlag(idx) == 1 && other.getFlag(idx) == 1) ? 1 : 0;
        setFlag(idx, intersected);
    }
    return *this;
}

Set& Set::operator*=(const Set& other)
{
    return (*this &= other);
}

// Різниця множин з присвоюванням (елементи, що є в this, але відсутні в other)
Set& Set::operator-=(const Set& other)
{
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        unsigned char idx = static_cast<unsigned char>(i);
        int diff = (getFlag(idx) == 1 && other.getFlag(idx) == 0) ? 1 : 0;
        setFlag(idx, diff);
    }
    return *this;
}

// Включення елементу (Set + char)
Set operator+(const Set& s, char ch)
{
    Set result(s);
    result += ch;
    return result;
}

// Включення елементу (char + Set)
Set operator+(char ch, const Set& s)
{
    return s + ch;
}

// Вилучення елементу (Set - char)
Set operator-(const Set& s, char ch)
{
    Set result(s);
    result -= ch;
    return result;
}

// Об'єднання двох множин (|)
Set operator|(const Set& lhs, const Set& rhs)
{
    Set result(lhs);
    result |= rhs;
    return result;
}

// Об'єднання двох множин (+)
Set operator+(const Set& lhs, const Set& rhs)
{
    return lhs | rhs;
}

// Перетин двох множин (&)
Set operator&(const Set& lhs, const Set& rhs)
{
    Set result(lhs);
    result &= rhs;
    return result;
}

// Перетин двох множин (*)
Set operator*(const Set& lhs, const Set& rhs)
{
    return lhs & rhs;
}

// Різниця двох множин (-)
Set operator-(const Set& lhs, const Set& rhs)
{
    Set result(lhs);
    result -= rhs;
    return result;
}

// Перевірка рівності двох множин
bool operator==(const Set& lhs, const Set& rhs)
{
    return lhs.isSubsetOf(rhs) && rhs.isSubsetOf(lhs);
}

// Перевірка нерівності двох множин
bool operator!=(const Set& lhs, const Set& rhs)
{
    return !(lhs == rhs);
}

// Перевірка входження lhs у rhs (підмножина або рівність)
bool operator<=(const Set& lhs, const Set& rhs)
{
    return lhs.isSubsetOf(rhs);
}

// Перевірка строгого входження lhs у rhs
bool operator<(const Set& lhs, const Set& rhs)
{
    return lhs.isSubsetOf(rhs) && (lhs.count() < rhs.count());
}

// Перевірка входження rhs у lhs (надмножина або рівність)
bool operator>=(const Set& lhs, const Set& rhs)
{
    return rhs.isSubsetOf(lhs);
}

// Перевірка строгого входження rhs у lhs
bool operator>(const Set& lhs, const Set& rhs)
{
    return rhs.isSubsetOf(lhs) && (lhs.count() > rhs.count());
}

// Перетворення множини до літерного рядка (використовує гетери)
Set::operator string() const
{
    stringstream ss;
    ss << "{ ";
    bool first = true;
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        unsigned char ch = static_cast<unsigned char>(i);
        if (getFlag(ch) == 1)
        {
            if (!first)
                ss << ", ";
            if (isprint(ch))
                ss << "'" << static_cast<char>(ch) << "'";
            else
                ss << "ASCII(" << i << ")";
            first = false;
        }
    }
    ss << " } [count = " << count() << "]";
    return ss.str();
}

// Операція виводу множини на екран (використовує гетери через operator string())
ostream& operator<<(ostream& out, const Set& s)
{
    return out << string(s);
}

// Операція вводу множини з клавіатури (користувач вводить усі дані через сетери)
istream& operator>>(istream& in, Set& s)
{
    // Очищення множини перед заповненням через сетер
    for (int i = 0; i < Set::MAX_SIZE; ++i)
    {
        s.setFlag(static_cast<unsigned char>(i), 0);
    }

    int n;
    cout << "Enter number of characters to insert into set (0.." << Set::MAX_SIZE << "): ";
    in >> n;

    if (n < 0 || n > Set::MAX_SIZE)
    {
        cerr << "Error: Invalid number of elements (" << n << ")!" << endl;
        exit(1);
    }

    if (n > 0)
    {
        cout << "Enter " << n << " characters: ";
        for (int i = 0; i < n; ++i)
        {
            char ch;
            in >> ch;
            s.setFlag(static_cast<unsigned char>(ch), 1);
        }
    }
    return in;
}