#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "hash.h"

struct TestStruct
{
    unsigned int num; // for counting hash
    std::string data;
};

unsigned int HashFunc(const TestStruct *pElement)
{
    return pElement->num % 6;
}

int StructCompFunc(const TestStruct *pElem1, const TestStruct *pElem2)
{
    return pElem1->num - pElem2->num;
}

void Test()
{
    int table_size = 3;
    int block_size = 10;
    lab618::CHash<TestStruct, &HashFunc, StructCompFunc> table(table_size, block_size);

    size_t data_size = 12;
    TestStruct **test_data = new TestStruct *[data_size];
    for (unsigned int i = 0; i < data_size; i++)
    {
        test_data[i] = new TestStruct{i, "a"};
    }

    // testing add
    for (size_t i = 0; i < data_size / 2; i++)
    {
        assert(table.add(test_data[i]) == true);
    }
    for (size_t i = 0; i < data_size / 2; i++)
    {
        assert(table.add(test_data[i]) == false);
    }

    // testing update
    for (size_t i = data_size / 2; i < data_size; i++)
    {
        assert(table.update(test_data[i]) == false);
    }
    for (size_t i = 0; i < data_size; i++)
    {
        test_data[i]->data = "b";
        assert(table.update(test_data[i]) == true);
    }

    // testing find
    for (size_t i = 0; i < data_size; i++)
    {
        TestStruct find_data{i, ""};
        TestStruct *found = table.find(find_data);
        assert(found->data == test_data[i]->data);
    }
    TestStruct find_data{data_size, ""};
    assert(table.find(find_data) == nullptr);

    // testing remove
    assert(table.remove(find_data) == false);
    for (size_t i = 0; i < data_size; i++)
    {
        TestStruct find_data{i, ""};
        assert(table.remove(find_data) == true);
    }
    for (size_t i = 0; i < data_size; i++)
    {
        TestStruct find_data{i, ""};
        assert(table.remove(find_data) == false);
    }
}

int main()
{
    Test();
    std::cout << "Test passed";
}