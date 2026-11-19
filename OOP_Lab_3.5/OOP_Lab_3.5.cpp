#include <iostream>
#include <string>
#include "Array.h"
#include "Set.h"

using namespace std;

int main()
{
    cout << "=== PART 1: Base Class Array Demonstration ===" << endl;
    Array arr1;
    cin >> arr1;
    cout << "arr1 = " << arr1 << endl;

    if (arr1.getSize() > 0)
    {
        int idx, newVal;
        cout << "Enter index to modify (0.." << arr1.getSize() - 1 << "): ";
        cin >> idx;
        cout << "Enter new integer value for arr1[" << idx << "]: ";
        cin >> newVal;
        arr1[idx] = newVal; // Демонстрація operator[] та rangeCheck()
        cout << "Updated arr1 = " << arr1 << endl;
    }

    Array arr2(arr1); // Конструктор копіювання базового класу
    cout << "Copied arr2 = " << string(arr2) << endl;

    cout << "\n=== PART 2: Derived Class Set Demonstration ===" << endl;

    // 1. Створення об'єкта конструктором без аргументів та ввід з клавіатури
    Set s1;
    cout << "\n--- Input Set s1 (default constructor + operator>>) ---" << endl;
    cin >> s1;
    cout << "s1 = " << s1 << endl;

    // 2. Створення об'єкта конструктором ініціалізації з рядка, введеного користувачем
    string initStr;
    cout << "\n--- Input string to initialize Set s2 (initialization constructor) ---" << endl;
    cout << "Enter a word or string of characters (no spaces): ";
    cin >> initStr;
    Set s2(initStr);
    cout << "s2 = " << s2 << endl;

    // 3. Створення об'єкта конструктором копіювання
    Set s3(s1);
    cout << "\n--- Copy constructor Set s3(s1) ---" << endl;
    cout << "s3 = " << s3 << endl;

    // 4. Включення та вилучення елементів
    char addChar, delChar;
    cout << "\n--- Element Insertion and Removal ---" << endl;
    cout << "Enter a character to add to s1: ";
    cin >> addChar;
    Set sWithAdded = s1 + addChar;
    cout << "s1 + '" << addChar << "' = " << sWithAdded << endl;
    s1 += addChar;
    cout << "After s1 += '" << addChar << "', s1 = " << s1 << endl;

    cout << "Enter a character to remove from s1: ";
    cin >> delChar;
    Set sWithRemoved = s1 - delChar;
    cout << "s1 - '" << delChar << "' = " << sWithRemoved << endl;
    s1 -= delChar;
    cout << "After s1 -= '" << delChar << "', s1 = " << s1 << endl;

    // 5. Перевірка наявності символу та кількості елементів
    char checkChar;
    cout << "\n--- Membership & Cardinality Check ---" << endl;
    cout << "Enter a character to check in s1: ";
    cin >> checkChar;
    cout << "Does s1 contain '" << checkChar << "'? " << (s1.contains(checkChar) ? "Yes" : "No") << endl;
    cout << "Number of elements in s1: " << s1.count() << endl;
    cout << "Number of elements in s2: " << s2.count() << endl;

    // 6. Об'єднання, перетин та різниця множин
    cout << "\n--- Set Operations: Union, Intersection, Difference ---" << endl;
    Set setUnion = s1 | s2;
    Set setInter = s1 & s2;
    Set setDiff12 = s1 - s2;
    Set setDiff21 = s2 - s1;

    cout << "Union (s1 | s2)        = " << setUnion << endl;
    cout << "Intersection (s1 & s2) = " << setInter << endl;
    cout << "Difference (s1 - s2)   = " << setDiff12 << endl;
    cout << "Difference (s2 - s1)   = " << setDiff21 << endl;

    // Демонстрація операцій з присвоюванням (|=, &=, -=)
    Set tempSet = s1;
    tempSet |= s2;
    cout << "Compound union (temp |= s2)        = " << tempSet << endl;
    tempSet = s1;
    tempSet &= s2;
    cout << "Compound intersection (temp &= s2) = " << tempSet << endl;
    tempSet = s1;
    tempSet -= s2;
    cout << "Compound difference (temp -= s2)   = " << tempSet << endl;

    // 7. Перевірка входження однієї множини в іншу та рівності
    cout << "\n--- Subset and Equality Checks ---" << endl;
    cout << "s1 == s2 : " << (s1 == s2 ? "true" : "false") << endl;
    cout << "s1 != s2 : " << (s1 != s2 ? "true" : "false") << endl;
    cout << "s1 <= s2 (s1 is subset of s2) : " << (s1 <= s2 ? "true" : "false") << endl;
    cout << "s1 <  s2 (s1 is proper subset): " << (s1 < s2 ? "true" : "false") << endl;
    cout << "s1 >= s2 (s2 is subset of s1) : " << (s1 >= s2 ? "true" : "false") << endl;
    cout << "s1 >  s2 (s2 is proper subset): " << (s1 > s2 ? "true" : "false") << endl;

    // 8. Масив об'єктів класу Set
    cout << "\n=== PART 3: Array of Set Objects ===" << endl;
    const int ARR_COUNT = 2;
    Set setArray[ARR_COUNT];
    for (int i = 0; i < ARR_COUNT; ++i)
    {
        cout << "\nInput setArray[" << i << "]:" << endl;
        cin >> setArray[i];
    }

    cout << "\nEntered sets in setArray:" << endl;
    for (int i = 0; i < ARR_COUNT; ++i)
    {
        cout << "setArray[" << i << "] = " << setArray[i] << endl;
    }
    cout << "Union of setArray[0] and setArray[1] = " << (setArray[0] | setArray[1]) << endl;

    return 0;
}