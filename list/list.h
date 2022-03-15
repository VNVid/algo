#ifndef TEMPLATES_LIST_2022_02_03
#define TEMPLATES_LIST_2022_02_03

namespace lab618 {
template <class T>
class CSingleLinkedList {
 private:
  struct leaf {
    T data;
    leaf *pnext;
    leaf(T &_data, leaf *_pnext) : data(_data), pnext(_pnext) {}
  };

 public:
  class CIterator {
   public:
    CIterator() : m_pCurrent(nullptr), m_pBegin(nullptr) {}

    CIterator(leaf *p) {
      m_pCurrent = p;
      m_pBegin = nullptr;
    }

    CIterator(const CIterator &src) {
      m_pBegin = src.m_pBegin;
      m_pCurrent = src.m_pCurrent;
    }

    ~CIterator() {
      m_pBegin = nullptr;
      m_pCurrent = nullptr;
    }

    CIterator &operator=(const CIterator &src) {
      this->m_pBegin = src.m_pBegin;
      this->m_pCurrent = src.m_pCurrent;

      return *this;
    }

    bool operator!=(const CIterator &it) const {
      return !(this->m_pBegin == it.m_pBegin &&
               this->m_pCurrent == it.m_pCurrent);
    }

    void operator++() {
      if (m_pCurrent == nullptr) {
        m_pCurrent = m_pBegin;
        m_pBegin = nullptr;
      } else {
        m_pCurrent = m_pCurrent->pnext;
      }
    }

    T &getData() {
      if (m_pCurrent != nullptr) {
        return m_pCurrent->data;
      }
      T tmp = T();
      return tmp;
    }

    T &operator*() { return m_pCurrent->data; }

    leaf *getLeaf() { return m_pCurrent; }

    void setLeaf(leaf *p) {
      m_pCurrent = p;
      m_pBegin = nullptr;
    }

    void setLeafPreBegin(leaf *p) {
      m_pBegin = p;
      m_pCurrent = nullptr;
    }

    bool isValid() { return m_pCurrent != nullptr; }

   private:
    //храним голову списка, если мы находимся перед началом
    leaf *m_pBegin;
    // храним текущее положение
    leaf *m_pCurrent;
  };

 public:
  CSingleLinkedList() {
    m_pBegin = nullptr;
    m_pEnd = nullptr;
  }

  virtual ~CSingleLinkedList() { clear(); }

  void pushBack(T &data) {
    leaf *new_end = new leaf(data, nullptr);
    if (m_pEnd != nullptr) {
      m_pEnd->pnext = new_end;
    } else {
      m_pBegin = new_end;
    }
    m_pEnd = new_end;
  }

  void pushFront(T &data) {
    leaf *new_begin = new leaf(data, m_pBegin);
    m_pBegin = new_begin;
    if (m_pEnd == nullptr) {
      m_pEnd = m_pBegin;
    }
  }

  T popFront() {
    T tmp;
    if (m_pBegin != nullptr) {
      tmp = m_pBegin->data;
      leaf *beg = m_pBegin;
      m_pBegin = m_pBegin->pnext;
      if (m_pBegin == nullptr) {
        m_pEnd = nullptr;
      }
      delete beg;
      beg = nullptr;
    }
    return tmp;
  }

  // изменяет состояние итератора. выставляет предыдущую позицию.
  void erase(CIterator &it) {
    if (!it.isValid()) {
      return;
    }

    leaf *cur_leaf = it.getLeaf();
    if (cur_leaf == m_pBegin) {
      m_pBegin = m_pBegin->pnext;
      if (cur_leaf == m_pEnd) {  // if only one leaf in list
        m_pEnd = nullptr;
      }
      it.setLeafPreBegin(m_pBegin);
    } else {
      leaf *prev_leaf = m_pBegin;
      while (prev_leaf->pnext != cur_leaf) {
        prev_leaf = prev_leaf->pnext;
      }
      prev_leaf->pnext = cur_leaf->pnext;
      it.setLeaf(prev_leaf);

      if (cur_leaf == m_pEnd) {
        m_pEnd = prev_leaf;
      }
    }

    delete cur_leaf;
  }

  int getSize() {
    int size = 0;
    leaf *current_leaf = m_pBegin;
    while (current_leaf != nullptr) {
      ++size;
      current_leaf = current_leaf->pnext;
    }

    return size;
  }

  void clear() {
    while (m_pBegin != nullptr) {
      leaf *next = m_pBegin->pnext;
      delete m_pBegin;
      m_pBegin = next;
    }
    m_pBegin = nullptr;
    m_pEnd = nullptr;
  }

  CIterator begin() { return CIterator(m_pBegin); }

 private:
  leaf *m_pBegin, *m_pEnd;
};

template <class T>
class CDualLinkedList {
 private:
  struct leaf {
    T data;
    leaf *pnext, *pprev;
    leaf(T &_data, leaf *_pprev, leaf *_pnext)
        : data(_data), pprev(_pprev), pnext(_pnext) {}
  };

 public:
  class CIterator {
   public:
    CIterator() : m_pCurrent(nullptr), m_pBegin(nullptr), m_pEnd(nullptr) {}

    CIterator(leaf *p) {
      m_pCurrent = p;
      m_pBegin = nullptr;
      m_pEnd = nullptr;
    }

    CIterator(const CIterator &src) {
      m_pBegin = src.m_pBegin;
      m_pCurrent = src.m_pCurrent;
      m_pEnd = src.m_pEnd;
    }

    ~CIterator() {
      m_pBegin = nullptr;
      m_pEnd = nullptr;
      m_pCurrent = nullptr;
    }

    CIterator &operator=(const CIterator &src) {
      this->m_pBegin = src.m_pBegin;
      this->m_pCurrent = src.m_pCurrent;
      this->m_pEnd = src.m_pEnd;

      return *this;
    }

    bool operator!=(const CIterator &it) const {
      return !(this->m_pBegin == it.m_pBegin &&
               this->m_pCurrent == it.m_pCurrent && this->m_pEnd == it.m_pEnd);
    }

    void operator++() {
      if (m_pCurrent == nullptr) {
        m_pCurrent = m_pBegin;
        m_pBegin = nullptr;
      } else {
        m_pCurrent = m_pCurrent->pnext;
      }
    }

    void operator--() {
      if (m_pCurrent == nullptr) {
        m_pCurrent = m_pEnd;
        m_pEnd = nullptr;
      } else {
        m_pCurrent = m_pCurrent->pprev;
      }
    }

    T &getData() {
      if (m_pCurrent != nullptr) {
        return m_pCurrent->data;
      }
      T tmp = T();
      return tmp;
    }

    T &operator*() { return m_pCurrent->data; }

    leaf *getLeaf() { return m_pCurrent; }

    // применяется в erase и eraseAndNext
    void setLeaf(leaf *p) {
      m_pCurrent = p;
      m_pBegin = nullptr;
      m_pEnd = nullptr;
    }

    // применяется в erase и eraseAndNext
    void setLeafPreBegin(leaf *p) {
      m_pBegin = p;
      m_pCurrent = nullptr;
    }

    // применяется в erase и eraseAndNext
    void setLeafPostEnd(leaf *p) {
      m_pEnd = p;
      m_pCurrent = nullptr;
    }

    bool isValid() { return m_pCurrent != nullptr; }

   private:
    //храним голову списка, если мы находимся перед началом
    leaf *m_pBegin;
    // храним текущее положение
    leaf *m_pCurrent;
    //храним конец списка, если мы находимся после конца
    leaf *m_pEnd;
  };

 public:
  CDualLinkedList() {
    m_pBegin = nullptr;
    m_pEnd = nullptr;
  };

  virtual ~CDualLinkedList() { clear(); };

  void pushBack(T &data) {
    leaf *new_end = new leaf(data, m_pEnd, nullptr);
    if (m_pEnd != nullptr) {
      m_pEnd->pnext = new_end;
    } else {
      m_pBegin = new_end;
    }
    m_pEnd = new_end;
  }

  T popBack() {
    T tmp;
    if (m_pEnd != nullptr) {
      tmp = m_pEnd->data;
      leaf *end = m_pEnd;
      m_pEnd = m_pEnd->pprev;
      if (m_pEnd == nullptr) {
        m_pBegin = nullptr;
      } else {
        m_pEnd->pnext = nullptr;
      }
      delete end;
      end = nullptr;
    }
    return tmp;
  }

  void pushFront(T &data) {
    leaf *new_begin = new leaf(data, nullptr, m_pBegin);
    if (m_pBegin != nullptr) {
      m_pBegin->pprev = new_begin;
    }
    m_pBegin = new_begin;
    if (m_pEnd == nullptr) {
      m_pEnd = m_pBegin;
    }
  }

  T popFront() {
    T tmp;
    if (m_pBegin != nullptr) {
      tmp = m_pBegin->data;
      leaf *beg = m_pBegin;
      m_pBegin = m_pBegin->pnext;
      if (m_pBegin == nullptr) {
        m_pEnd = nullptr;
      } else {
        m_pBegin->pprev = nullptr;
      }
      delete beg;
      beg = nullptr;
    }
    return tmp;
  }

  // изменяет состояние итератора. выставляет предыдущую позицию.
  void erase(CIterator &it) {
    if (!it.isValid()) {
      return;
    }

    leaf *cur_leaf = it.getLeaf();
    if (cur_leaf == m_pBegin) {
      m_pBegin = m_pBegin->pnext;
      if (cur_leaf == m_pEnd) {  // if only one leaf in list
        m_pEnd = nullptr;
      } else {
        m_pBegin->pprev = nullptr;
      }
      it.setLeafPreBegin(m_pBegin);
    } else {
      leaf *prev_leaf = cur_leaf->pprev;
      prev_leaf->pnext = cur_leaf->pnext;

      if (cur_leaf == m_pEnd) {
        m_pEnd = prev_leaf;
        m_pEnd->pnext = nullptr;
      } else {
        leaf *next_leaf = cur_leaf->pnext;
        next_leaf->pprev = cur_leaf->pprev;
      }

      it.setLeaf(prev_leaf);
    }

    delete cur_leaf;
    cur_leaf = nullptr;
  }

  // изменяет состояние итератора. выставляет следующую позицию.
  void eraseAndNext(CIterator &it) {
    if (!it.isValid()) {
      return;
    }

    leaf *cur_leaf = it.getLeaf();
    if (cur_leaf == m_pEnd) {
      m_pEnd = m_pEnd->pprev;
      if (cur_leaf == m_pBegin) {  // if only one leaf in list
        m_pBegin = nullptr;
      } else {
        m_pEnd->pnext = nullptr;
      }
      it.setLeafPostEnd(m_pEnd);
    } else {
      leaf *next_leaf = cur_leaf->pnext;
      next_leaf->pprev = cur_leaf->pprev;

      if (cur_leaf == m_pBegin) {
        m_pBegin = next_leaf;
        m_pBegin->pprev = nullptr;
      } else {
        leaf *prev_leaf = cur_leaf->pprev;
        prev_leaf->pnext = cur_leaf->pnext;
      }

      it.setLeaf(next_leaf);
    }

    delete cur_leaf;
    cur_leaf = nullptr;
  }

  int getSize() {
    int size = 0;
    leaf *current_leaf = m_pBegin;
    while (current_leaf != nullptr) {
      ++size;
      current_leaf = current_leaf->pnext;
    }

    return size;
  }

  void clear() {
    while (m_pBegin != nullptr) {
      leaf *next = m_pBegin->pnext;
      delete m_pBegin;
      m_pBegin = next;
    }
    m_pBegin = nullptr;
    m_pEnd = nullptr;
  }

  CIterator begin() { return CIterator(m_pBegin); }

  CIterator end() { return CIterator(m_pEnd); }

 private:
  leaf *m_pBegin, *m_pEnd;
};
};      // namespace lab618
#endif  //#ifndef TEMPLATES_LIST_2022_02_03
