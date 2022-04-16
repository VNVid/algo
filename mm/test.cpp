#include "mm.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

void SimpleTest()
{
    int block_size = 10;
    lab618::CMemoryManager<int> mm(block_size);

    std::vector<int *> array(block_size * 2);
    for (int i = 0; i < block_size * 2; i++)
    {
        array[i] = mm.newObject();
        *array[i] = i;
    }

    int *number = new int[1];
    *number = 0;

    assert(mm.deleteObject(number) == false);
    assert(mm.deleteObject(array[0]) == true);
    assert(mm.deleteObject(array[0]) == false);

    for (auto p : array)
    {
        mm.deleteObject(p);
    }

    try
    {
        mm.clear();
    }
    catch (lab618::CMemoryManager<int>::CException e)
    {
        assert(false);
    }
    assert(mm.deleteObject(array[1]) == false);
}

struct TestStruct
{
    std::string str;
    int num;
};
struct PairTestStruct
{
    TestStruct *s1;
    TestStruct *s2;
};
void StructMMTest()
{
    int block_size = 1000;
    lab618::CMemoryManager<PairTestStruct> mm(block_size, true);

    std::vector<PairTestStruct *> array(block_size * 2);
    for (int i = 0; i < block_size * 2; i++)
    {
        array[i] = mm.newObject();
        *array[i] = PairTestStruct{new TestStruct{"", i}, new TestStruct{"", i}};
    }

    PairTestStruct pair{new TestStruct{"", 1}, new TestStruct{"", 1}};

    assert(mm.deleteObject(&pair) == false);
    assert(mm.deleteObject(array[0]) == true);
    assert(mm.deleteObject(array[0]) == false);

    try
    {
        mm.clear();
    }
    catch (lab618::CMemoryManager<PairTestStruct>::CException e)
    {
        assert(false);
    }
}
void DestructOnClearTest()
{
    int block_size = 1000;
    lab618::CMemoryManager<PairTestStruct> mm(block_size, false);

    std::vector<PairTestStruct *> array(block_size * 2);
    for (int i = 0; i < block_size * 2; i++)
    {
        array[i] = mm.newObject();
        *array[i] = PairTestStruct{new TestStruct{"", i}, new TestStruct{"", i}};
    }

    try
    {
        mm.clear();
        assert(false);
    }
    catch (lab618::CMemoryManager<PairTestStruct>::CException e)
    {
        std::cout << "DestructOnClearTest passed\n";
        throw;
    }
}

int main()
{
    SimpleTest();
    std::cout << "SimpleTest passed\n";

    StructMMTest();
    std::cout << "StructMMTest passed\n";

    try
    {
        DestructOnClearTest();
    }
    catch (...)
    {
        std::cout << "DestructOnClearTest passed\n";
    }
}