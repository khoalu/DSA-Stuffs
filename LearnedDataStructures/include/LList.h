#ifndef LLIST_H
#define LLIST_H

#include<functional>

template <class T>
struct NodeLList
{
    T data;
    NodeLList *next;
    NodeLList(): next(nullptr) {}
    NodeLList(const T& data): data(data), next(nullptr) {}
    NodeLList(const T& data, NodeLList* next): data(data), next(next) {}
};

template<class T>
class LList
{
    private:
        NodeLList<T> *pHead;
        int m_size;
    public:
        LList(): pHead(nullptr), m_size(0) {}
        virtual ~LList() {clear(); m_size = 0;}

        int getSize() {return m_size;}

        void clear()
        {
            while (pHead)
            {
                NodeLList<T> *p = pHead;
                pHead = pHead->next;
                delete p;
            }
        }


        void insert(const T& x, int pos)
        {
            if (pos == 0 || m_size == 0)
            {
                insertHead(x);
            }
            else if (pos >= 0 && pos <= m_size)
            {
                NodeLList<T> *p = pHead;
                NodeLList<T> *pp = nullptr;
                while (pos--)
                {
                    pp = p;
                    p = p->next;
                }
                p = new NodeLList<T>(x, p);
                pp->next = p;
            }
            else
                throw std::out_of_range(
                        "try to insert out of bound of singly linked list"
                        );
            ++m_size;
        }
        void insertHead(const T& x) {pHead = new NodeLList<T>(x, pHead); }
        void insertTail(const T& x) {insert(x, m_size); }

        void remove(int pos)
        {
            if (pos == 0 || m_size == 1)
            {
                NodeLList<T> *p = pHead;
                pHead = pHead->next;
                delete p;
            }
            else if (pos >= 0 || pos < m_size)
            {
                NodeLList<T> *p = pHead;
                NodeLList<T> *pp = nullptr;
                while (pos--)
                {
                    pp = p;
                    p = p->next;
                }
                pp->next = p->next;
                delete p;
            }
            else
            {
                throw std::out_of_range(
                        "try to delete out of bound of singly linked list"
                        );
            }
            --m_size;
        }

        void removeHead() {remove(0); }
        void removeTail() {remove(m_size-1); }

        void reverse()
        {
            NodeLList<T> *pre = nullptr;
            NodeLList<T> *cur = pHead;
            NodeLList<T> *next = nullptr;
            while (cur)
            {
                next = cur->next;
                cur->next = pre;
                pre = cur;
                cur = next;
            }
            pHead = pre;
        }

        NodeLList<T>* find(const T& x, int& pos)
        {
            NodeLList<T> *p = pHead;
            while (p)
            {
                if (p->data == x) return p;
                ++pos;
            }
            return nullptr;
        }

        T& operator[] (int i)
        {
            NodeLList<T> *p = pHead;
            while (i--)
            {
                p = p->next;
            }
            return p->data;
        }
        T& at (int i)
        {
            if (i < 0 || i >= m_size)
                throw std::out_of_range(
                        "access out of range of singly linked list"
                        );
            NodeLList<T> *p = pHead;
            while (i--)
            {
                p = p->next;
            }
            return p->data;
        }

        void traverse(void (*op)(T&))
        {
            NodeLList<T> *p = pHead;
            while (p)
            {
                op(p);
                p = p->next;
            }
        }

        void traverse(std::function<void()> op)
        {
            NodeLList<T> *p = pHead;
            while (p)
            {
                op(p);
                p = p->next;
            }
        }
};

#endif // LLIST_H
