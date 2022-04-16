#include <iostream>
#include <string>

#include "sort.h"

int StringCompFunc(const std::string *pElem1, const std::string *pElem2)
{
    return pElem1 < pElem2;
}

void TEST_string()
{
    size_t size = 6;
    std::string strings[size] = {"aa", "b", "g", "ab", "ab", "z"};
    std::string **arr = new std::string *[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = &strings[i];
    }
    templates::simpleSort<std::string>(arr, size, StringCompFunc);

    bool sorted_correctly = true;
    for (size_t i = 0; i < size - 1; i++)
    {
        sorted_correctly &= (*arr[i] <= *arr[i + 1]);
        // std::cout << *arr[i] << " ";
    }
    if (sorted_correctly)
    {
        std::cout << "OK\n";
    }
    else
    {
        std::cout << "FAIL\n";
    }
}

struct TestStruct
{
    int num1 = 0;
    int num2 = 0;

    TestStruct() = default;
    TestStruct(int num1, int num2) : num1(num1), num2(num2)
    {
    }
};

int StructCompFunc(const TestStruct *pElem1, const TestStruct *pElem2)
{
    int comp = pElem2->num1 - pElem1->num1;
    if (comp != 0)
    {
        return comp;
    }
    return pElem2->num2 - pElem1->num2;
}

void TEST_struct()
{
    size_t size = 5;
    TestStruct structs[size] = {TestStruct(), TestStruct(1, 1), TestStruct(2, 3), TestStruct(2, 2), TestStruct()};
    TestStruct **arr = new TestStruct *[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = &structs[i];
    }
    templates::simpleSort<TestStruct>(arr, size, StructCompFunc);

    for (size_t i = 0; i < size; i++)
    {
        std::cout << "(" << arr[i]->num1 << ", " << arr[i]->num2 << ") ";
    }

    bool sorted_correctly = true;
    for (size_t i = 0; i < size - 1; i++)
    {
        sorted_correctly &= (StructCompFunc(arr[i], arr[i + 1]) >= 0);
    }
    if (sorted_correctly)
    {
        std::cout << "OK\n";
    }
    else
    {
        std::cout << "FAIL\n";
    }
}

// GENERAL COMMENTS
// ~ generate test data automatically (random data)
// ~ compare results with correct answer automatically
//  (output is only Passed/Error)

int main()
{
    std::cout << "Test with strings" << std::endl;
    TEST_string();
    std::cout << std::endl;

    std::cout << "Test with struct" << std::endl;
    TEST_struct();
    std::cout << std::endl;
}