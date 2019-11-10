#ifndef QUEUE_H
#define QUEUE_H

template<class T>
struct NodeQueue
{
    T data;
    NodeQueue *next;
    NodeQueue(): next(nullptr) {}
    NodeQueue(const T& data): data(data), next(nullptr) {}
    NodeQueue(const T& data, NodeQueue* next): data(data), next(next) {}
};

/**
    Important note:
    NEVER, EVER try to request a COPY from this implementation, i.e:
    void foo(Queue<int> st)
    because it doesnt support copy and move constructor (yet)
*/

template <class T>
class Queue
{
private:
    int m_size;
    NodeQueue<T> *pFront, *pBack;
public:
    Queue(): m_size(0), pFront(nullptr), pBack(nullptr) {}
    virtual ~Queue()
    {
        while (m_size) pop();
    }

    T front() const {return pFront->data;}
    T& front() {return pFront->data;}

    T back() const {return pBack->data;}
    T& back() {return pBack->data;}

    int getSize() {return m_size;}
    bool isEmpty() {return m_size == 0;}

    void push(const T& x)
    {
        ++m_size;
        if (pFront == nullptr)
        {
            NodeQueue<T> *p = new NodeQueue<T>(x);
            pFront = pBack = p;
        }
        else
        {
            pBack->next = new NodeQueue<T>(x);
            pBack = pBack->next;
        }
    }

    void pop()
    {
        if (!m_size) throw std::out_of_range("Queue is empty");
        --m_size;
        if (pFront == pBack)
        {
            delete pFront;
            pFront = pBack = nullptr;
        }
        else
        {
            NodeQueue<T> *p = pFront;
            pFront=pFront->next;
            delete p;
        }
    }
};

#endif // QUEUE_H
