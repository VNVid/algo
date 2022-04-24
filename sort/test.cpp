#include <cstdlib>
#include <iostream>
#include <string>

#include "sort.h"

int StringCompFunc(const std::string *pElem1, const std::string *pElem2)
{
    if (*pElem1 < *pElem2)
    {
        return 1;
    }
    else if (*pElem1 == *pElem2)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void TEST_SimpleSort_string()
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

void TEST_MergeSort_string()
{
    size_t size = 6;
    std::string strings[size] = {"aa", "b", "g", "ab", "ab", "z"};
    std::string **arr = new std::string *[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = &strings[i];
    }
    templates::mergeSort<std::string>(arr, size, StringCompFunc);

    bool sorted_correctly = true;
    for (size_t i = 0; i < size - 1; i++)
    {
        sorted_correctly &= (*arr[i] <= *arr[i + 1]);
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

void TEST_SimpleSort_struct()
{
    size_t size = 5;
    TestStruct structs[size] = {TestStruct(), TestStruct(1, 1), TestStruct(2, 3), TestStruct(2, 2), TestStruct()};
    TestStruct **arr = new TestStruct *[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = &structs[i];
    }
    templates::simpleSort<TestStruct>(arr, size, StructCompFunc);

    /*for (size_t i = 0; i < size; i++)
    {
        std::cout << "(" << arr[i]->num1 << ", " << arr[i]->num2 << ") ";
    }*/

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

void TEST_MergeSort_struct()
{
    size_t size = 5;
    TestStruct structs[size] = {TestStruct(), TestStruct(1, 1), TestStruct(2, 3), TestStruct(2, 2), TestStruct()};
    TestStruct **arr = new TestStruct *[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = &structs[i];
    }
    templates::mergeSort<TestStruct>(arr, size, StructCompFunc);

    /*for (size_t i = 0; i < size; i++)
    {
        std::cout << "(" << arr[i]->num1 << ", " << arr[i]->num2 << ") ";
    }*/

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

void BIGTEST_MergeSort_struct()
{
    size_t size = 300;
    TestStruct structs[size];
    for (size_t i = 0; i < size; i++)
    {
        structs[i] = TestStruct(rand(), rand());
    }

    TestStruct **arr = new TestStruct *[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = &structs[i];
    }
    templates::mergeSort<TestStruct>(arr, size, StructCompFunc);

    /*for (size_t i = 0; i < size; i++)
    {
        std::cout << "(" << arr[i]->num1 << ", " << arr[i]->num2 << ") ";
    }*/

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

int main()
{
    std::cout << "Testing bubble sort.\n";
    std::cout << "Test with strings: ";
    TEST_SimpleSort_string();
    std::cout << "Test with struct: ";
    TEST_SimpleSort_struct();
    std::cout << std::endl;

    std::cout << "Testing merge sort.\n";
    std::cout << "Test with strings: ";
    TEST_MergeSort_string();
    std::cout << "Test with struct: ";
    TEST_MergeSort_struct();
    std::cout << "Test with many random generated structs: ";
    BIGTEST_MergeSort_struct();
    std::cout << std::endl;
}