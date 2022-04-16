#ifndef MEMORY_MANAGER_HEAD_H_2022_02_17
#define MEMORY_MANAGER_HEAD_H_2022_02_17

#include <cstring>

namespace lab618
{
template <class T> class CMemoryManager
{
  private:
    struct block
    {
        // Массив данных блока
        T *pdata;
        // Адрес следующего блока
        block *pnext;
        // Первая свободная ячейка
        int firstFreeIndex;
        // Число заполненных ячеек
        int usedCount;
    };

  public:
    class CException
    {
      public:
        CException()
        {
        }
    };

  public:
    CMemoryManager(int _default_block_size, bool isDeleteElementsOnDestruct = false)
        : m_blkSize(_default_block_size), m_isDeleteElementsOnDestruct(isDeleteElementsOnDestruct), m_pBlocks(nullptr),
          m_pCurrentBlk(nullptr)
    {
    }

    virtual ~CMemoryManager()
    {
        clear();
    }

    // Получить адрес нового элемента из менеджера
    T *newObject()
    {
        if (m_pBlocks == nullptr)
        {
            m_pBlocks = newBlock();
        }
        if (m_pCurrentBlk == nullptr)
        {
            m_pCurrentBlk = m_pBlocks;
        }

        // ищем свободный блок
        if (m_pCurrentBlk->usedCount == m_blkSize)
        {
            m_pCurrentBlk = m_pBlocks;
            while (m_pCurrentBlk != nullptr)
            {
                if (m_pCurrentBlk->usedCount < m_blkSize)
                {
                    break;
                }
                m_pCurrentBlk = m_pCurrentBlk->pnext;
            }
            if (m_pCurrentBlk == nullptr)
            {
                m_pCurrentBlk = newBlock();
            }
        }

        T *object = m_pCurrentBlk->pdata + m_pCurrentBlk->firstFreeIndex;
        m_pCurrentBlk->firstFreeIndex = *(reinterpret_cast<int *>(object));
        ++m_pCurrentBlk->usedCount;
        memset(reinterpret_cast<void *>(object), 0, sizeof(T));
        ::new (reinterpret_cast<void *>(object)) T;

        return object;
    }

    // Освободить элемент в менеджере
    bool deleteObject(T *p)
    {
        block *cur_block = m_pBlocks;
        while (cur_block != nullptr)
        {
            if (cur_block->pdata <= p && p < cur_block->pdata + m_blkSize)
            {
                int ind = cur_block->firstFreeIndex;
                while (ind != -1)
                {
                    if (ind == p - cur_block->pdata)
                    {
                        return false;
                    }
                    ind = *(reinterpret_cast<int *>(cur_block->pdata + ind));
                }

                p->~T();
                memset(reinterpret_cast<void *>(p), 0, sizeof(T));

                *(reinterpret_cast<int *>(p)) = cur_block->firstFreeIndex;
                cur_block->firstFreeIndex = p - cur_block->pdata;
                --cur_block->usedCount;
                m_pCurrentBlk = cur_block;
                return true;
            }
            cur_block = cur_block->pnext;
        }
        return false;
    }

    // Очистка данных, зависит от m_isDeleteElementsOnDestruct
    void clear()
    {
        m_pCurrentBlk = m_pBlocks;
        while (m_pCurrentBlk != nullptr)
        {
            if (m_pCurrentBlk->usedCount > 0)
            {
                if (!m_isDeleteElementsOnDestruct)
                {
                    throw CException();
                }

                bool *free_elems = new bool[m_blkSize];
                memset(reinterpret_cast<void *>(free_elems), 0, m_blkSize);

                while (m_pCurrentBlk->firstFreeIndex != -1)
                {
                    free_elems[m_pCurrentBlk->firstFreeIndex] = true;
                    m_pCurrentBlk->firstFreeIndex =
                        *(reinterpret_cast<int *>(m_pCurrentBlk->pdata + m_pCurrentBlk->firstFreeIndex));
                }

                for (int i = 0; i < m_blkSize; i++)
                {
                    if (!free_elems[i])
                    {
                        (m_pCurrentBlk->pdata + i)->~T();
                    }
                }

                delete[] free_elems;
            }

            block *delete_block = m_pCurrentBlk;
            m_pCurrentBlk = m_pCurrentBlk->pnext;
            deleteBlock(delete_block);
        }

        m_pBlocks = nullptr;
        m_pCurrentBlk = nullptr;
    }

  private:
    // Создать новый блок данных. применяется в newObject
    block *newBlock()
    {
        block *new_block = new block;
        new_block->pdata = reinterpret_cast<T *>(new char[m_blkSize * sizeof(T)]);
        new_block->pnext = m_pBlocks;
        new_block->usedCount = 0;
        new_block->firstFreeIndex = 0;

        for (int i = 0; i < m_blkSize - 1; i++)
        {
            *(reinterpret_cast<int *>(new_block->pdata + i)) = i + 1;
        }
        *(reinterpret_cast<int *>(new_block->pdata + m_blkSize - 1)) = -1;

        m_pBlocks = new_block;

        return new_block;
    }

    // Освободить память блока данных. Применяется в clear
    void deleteBlock(block *p)
    {
        delete[] reinterpret_cast<char *>(p->pdata);
        p->pdata = nullptr;

        delete p;
        p = nullptr;
    }

    // Размер блока
    int m_blkSize;
    // Начало списка блоков
    block *m_pBlocks;
    // Текущий блок
    block *m_pCurrentBlk;
    // Удалять ли элементы при освобождении
    bool m_isDeleteElementsOnDestruct;
};
}; // namespace lab618

#endif // #define MEMORY_MANAGER_HEAD_H_2022_02_17