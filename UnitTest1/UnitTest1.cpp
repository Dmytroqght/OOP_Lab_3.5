#include "pch.h"
#include "CppUnitTest.h"
#include "../OOP_Lab_3.5/Array.cpp"
#include "../OOP_Lab_3.5/Set.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab35UnitTest
{
    TEST_CLASS(SetTests)
    {
    public:
        TEST_METHOD(TestSetOperationsAndSubset)
        {
            Set a("abc");
            Set b("bcd");

            // Перевірка кількості елементів (без дублікатів)
            Assert::AreEqual(3, a.count());
            Assert::IsTrue(a.contains('a'));
            Assert::IsFalse(a.contains('d'));

            // Перевірка об'єднання, перетину та різниці
            Set u = a | b;
            Assert::AreEqual(4, u.count()); // {a, b, c, d}

            Set inter = a & b;
            Assert::AreEqual(2, inter.count()); // {b, c}
            Assert::IsTrue(inter.contains('b'));
            Assert::IsTrue(inter.contains('c'));

            Set diff = a - b;
            Assert::AreEqual(1, diff.count()); // {a}
            Assert::IsTrue(diff.contains('a'));

            // Перевірка входження підмножини
            Assert::IsTrue(inter <= a);
            Assert::IsTrue(inter < u);
            Assert::IsFalse(a <= b);
        }
    };
}