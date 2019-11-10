#ifndef STACK_H
#define STACK_H

template<class T>
struct NodeStack
{
    T data;
    NodeStack *next;
    NodeStack(): next(nullptr) {}
    NodeStack(const T& data): data(data), next(nullptr) {}
    NodeStack(const T& data, NodeStack* next): data(data), next(next) {}
};

/**
    Important note:
    NEVER, EVER try to request a COPY from this implementation, i.e:
    void foo(Stack<int> st)
    because it doesnt support copy and move constructor (yet)
*/

template <class T>
class Stack
{
private:
    int m_size;
    NodeStack<T> *pTop;

public:
    Stack(): m_size(0), pTop(nullptr) {}
    virtual ~Stack() {
        while (m_size) pop();
    }

    int getSize() const { return m_size; }
    bool isEmpty() const {return m_size == 0;}

    T top() const {return pTop->data;}
    T& top() {return pTop->data;}
    void push(const T& x)
    {
        NodeStack<T> *p = new NodeStack<T>(x, pTop);
        pTop = p;
        ++m_size;
    }
    void pop()
    {
        if (!pTop) throw std::out_of_range("Stack is empty");
        NodeStack<T> *p = pTop;
        pTop = pTop->next;
        delete p;
        --m_size;
    }
};

#endif // STACK_H
