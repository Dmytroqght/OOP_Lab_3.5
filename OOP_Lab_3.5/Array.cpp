#include "Array.h"
#include <sstream>
#include <cstdlib>

using namespace std;

// Конструктор ініціалізації (звертається до сетерів)
Array::Array(int n, int initVal)
{
    setSize(n);
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (i < getSize())
            setElement(i, initVal);
        else
            data[i] = 0; // Очищення невикористаної частини буфера
    }
}

// Конструктор копіювання (звертається до сетерів)
Array::Array(const Array& other)
{
    setSize(other.getSize());
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (i < getSize())
            setElement(i, other.getElement(i));
        else
            data[i] = 0;
    }
}

// Деструктор
Array::~Array()
{
}

// Перевірка індексу на входження до діапазону [0; size - 1]
bool Array::rangeCheck(int index) const
{
    return index >= 0 && index < size;
}

// Гетер окремого елемента з перевіркою діапазону
int Array::getElement(int index) const
{
    if (!rangeCheck(index))
    {
        cerr << "Error: Array index " << index << " is out of range!" << endl;
        exit(1);
    }
    return data[index];
}

// Сетер розміру масиву з перевіркою допустимості
void Array::setSize(int value)
{
    if (value < 0 || value > MAX_SIZE)
    {
        cerr << "Error: Invalid array size (" << value << "). Must be between 0 and " << MAX_SIZE << "." << endl;
        exit(1);
    }
    size = value;
}

// Сетер окремого елемента з перевіркою діапазону
void Array::setElement(int index, int value)
{
    if (!rangeCheck(index))
    {
        cerr << "Error: Array index " << index << " is out of range!" << endl;
        exit(1);
    }
    data[index] = value;
}

// Операція присвоювання
Array& Array::operator=(const Array& other)
{
    if (this == &other)
        return *this;

    setSize(other.getSize());
    for (int i = 0; i < getSize(); ++i)
    {
        setElement(i, other.getElement(i));
    }
    return *this;
}

// Операція індексування для запису/читання
int& Array::operator[](int index)
{
    if (!rangeCheck(index))
    {
        cerr << "Error: Array index " << index << " is out of range!" << endl;
        exit(1);
    }
    return data[index];
}

// Константна операція індексування лише для читання
const int& Array::operator[](int index) const
{
    if (!rangeCheck(index))
    {
        cerr << "Error: Array index " << index << " is out of range!" << endl;
        exit(1);
    }
    return data[index];
}

// Перетворення об'єкта до літерного рядка (використовує гетери)
Array::operator string() const
{
    stringstream ss;
    ss << "[ ";
    for (int i = 0; i < getSize(); ++i)
    {
        ss << getElement(i) << " ";
    }
    ss << "]";
    return ss.str();
}

// Операція виводу на екран (використовує перетворення до string через гетери)
ostream& operator<<(ostream& out, const Array& r)
{
    return out << string(r);
}

// Операція вводу з клавіатури (використовує сетери)
istream& operator>>(istream& in, Array& r)
{
    int n;
    cout << "Enter array size (0.." << Array::MAX_SIZE << "): ";
    in >> n;
    r.setSize(n);

    for (int i = 0; i < r.getSize(); ++i)
    {
        int val;
        cout << "Element [" << i << "] = ";
        in >> val;
        r.setElement(i, val);
    }
    return in;
}