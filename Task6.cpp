#include <bits/stdc++.h>
using namespace std;

template <typename T>
class my_vector {
private:
    T*     m_data;
    size_t m_size;
    size_t m_cap;
    void reallocate(size_t nc) {
        if (nc <= m_cap) return;
        T* nd = new T[nc];
        for (size_t i = 0; i < m_size; ++i) nd[i] = move(m_data[i]);
        delete[] m_data;
        m_data = nd; m_cap = nc;
    }
public:
    my_vector() : m_data(nullptr), m_size(0), m_cap(0) {}
    my_vector(const my_vector& o) : m_data(nullptr), m_size(o.m_size), m_cap(o.m_cap) {
        m_data = m_cap ? new T[m_cap] : nullptr;
        for (size_t i = 0; i < m_size; ++i) m_data[i] = o.m_data[i];
    }
    my_vector& operator=(const my_vector& o) {
        if (this == &o) return *this;
        delete[] m_data;
        m_size = o.m_size; m_cap = o.m_cap;
        m_data = m_cap ? new T[m_cap] : nullptr;
        for (size_t i = 0; i < m_size; ++i) m_data[i] = o.m_data[i];
        return *this;
    }
    my_vector(my_vector&& o) noexcept : m_data(o.m_data), m_size(o.m_size), m_cap(o.m_cap) {
        o.m_data = nullptr; o.m_size = 0; o.m_cap = 0;
    }
    my_vector& operator=(my_vector&& o) noexcept {
        if (this == &o) return *this;
        delete[] m_data;
        m_data = o.m_data; m_size = o.m_size; m_cap = o.m_cap;
        o.m_data = nullptr; o.m_size = 0; o.m_cap = 0;
        return *this;
    }
    ~my_vector() { delete[] m_data; }

    void push_back(const T& v) {
        if (m_size == m_cap) reallocate(m_cap == 0 ? 1 : m_cap * 2);
        m_data[m_size++] = v;
    }
    void pop_back() { if (m_size) --m_size; }
    T&       operator[](size_t i)       { return m_data[i]; }
    const T& operator[](size_t i) const { return m_data[i]; }
    T&       back()                     { return m_data[m_size - 1]; }
    size_t   size()  const { return m_size; }
    bool     empty() const { return m_size == 0; }
    void     clear() { m_size = 0; }
};

template <typename T>
class LinkedList {
private:
    struct Node {
        T data; Node* prev; Node* next;
        Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
    };
    Node* head; Node* tail; int sz;
public:
    LinkedList() : head(nullptr), tail(nullptr), sz(0) {}
    LinkedList(const LinkedList& o) : head(nullptr), tail(nullptr), sz(0) {
        for (Node* c = o.head; c; c = c->next) push_back(c->data);
    }
    LinkedList& operator=(const LinkedList& o) {
        if (this == &o) return *this;
        clear();
        for (Node* c = o.head; c; c = c->next) push_back(c->data);
        return *this;
    }
    ~LinkedList() { clear(); }

    void push_front(const T& v) {
        Node* n = new Node(v);
        n->next = head;
        if (head) head->prev = n; else tail = n;
        head = n; sz++;
    }
    void push_back(const T& v) {
        Node* n = new Node(v);
        n->prev = tail;
        if (tail) tail->next = n; else head = n;
        tail = n; sz++;
    }
    void pop_front() {
        if (!head) return;
        Node* t = head; head = head->next;
        if (head) head->prev = nullptr; else tail = nullptr;
        delete t; sz--;
    }
    void pop_back() {
        if (!tail) return;
        Node* t = tail; tail = tail->prev;
        if (tail) tail->next = nullptr; else head = nullptr;
        delete t; sz--;
    }
    T&   front()       { return head->data; }
    T&   back()        { return tail->data; }
    bool empty() const { return sz == 0; }
    int  size()  const { return sz; }
    void clear() { while (head) { Node* t = head; head = head->next; delete t; } tail = nullptr; sz = 0; }
};

template <typename T>
class StackLinkedList {
    LinkedList<T> lst;
public:
    void push(const T& v) { lst.push_back(v); }
    void pop()            { lst.pop_back(); }
    T&   top()            { return lst.back(); }
    bool empty() const    { return lst.empty(); }
    int  size()  const    { return lst.size(); }
};

template <typename T>
class StackVector {
    my_vector<T> v;
public:
    void push(const T& x) { v.push_back(x); }
    void pop()            { v.pop_back(); }
    T&   top()            { return v.back(); }
    bool empty() const    { return v.empty(); }
    int  size()  const    { return (int)v.size(); }
};

template <typename T>
class QueueLinkedList {
    LinkedList<T> lst;
public:
    void push(const T& x) { lst.push_back(x); }
    void pop()            { lst.pop_front(); }
    T&   front()          { return lst.front(); }
    T&   back()           { return lst.back(); }
    bool empty() const    { return lst.empty(); }
    int  size()  const    { return lst.size(); }
};

template <typename T>
class QueueVector {
    my_vector<T> v;
    int head = 0;
public:
    void push(const T& x) { v.push_back(x); }
    void pop()            { if (head < (int)v.size()) head++; }
    T&   front()          { return v[head]; }
    bool empty() const    { return head >= (int)v.size(); }
    int  size()  const    { return (int)v.size() - head; }
};

template <typename T>
class StackTwoQueues {
    QueueLinkedList<T> q1, q2;
    bool useFirst = true;
public:
    void push(const T& x) {
        QueueLinkedList<T>& main = useFirst ? q1 : q2;
        QueueLinkedList<T>& aux  = useFirst ? q2 : q1;
        aux.push(x);
        while (!main.empty()) { aux.push(main.front()); main.pop(); }
        useFirst = !useFirst;
    }
    void pop()         { (useFirst ? q1 : q2).pop(); }
    T&   top()         { return (useFirst ? q1 : q2).front(); }
    bool empty() const { return q1.empty() && q2.empty(); }
    int  size()  const { return q1.size() + q2.size(); }
};

template <typename T>
class QueueTwoStacks {
    StackLinkedList<T> in, out;
    void shift() { if (out.empty()) while (!in.empty()) { out.push(in.top()); in.pop(); } }
public:
    void push(const T& x) { in.push(x); }
    void pop()            { shift(); out.pop(); }
    T&   front()          { shift(); return out.top(); }
    bool empty() const    { return in.empty() && out.empty(); }
    int  size()  const    { return in.size() + out.size(); }
};

template <typename T>
class DequeDoublyLinked {
    LinkedList<T> lst;
public:
    void push_front(const T& x) { lst.push_front(x); }
    void push_back(const T& x)  { lst.push_back(x); }
    void pop_front()            { lst.pop_front(); }
    void pop_back()             { lst.pop_back(); }
    T&   front()                { return lst.front(); }
    T&   back()                 { return lst.back(); }
    bool empty() const          { return lst.empty(); }
    int  size()  const          { return lst.size(); }
};

template <typename T>
class DequeVector {
    my_vector<T> v;
public:
    void push_back(const T& x) { v.push_back(x); }
    void pop_back()            { v.pop_back(); }
    void push_front(const T& x) {
        v.push_back(x);
        for (int i = (int)v.size() - 1; i > 0; --i) v[i] = v[i - 1];
        v[0] = x;
    }
    void pop_front() {
        if (v.empty()) return;
        for (int i = 0; i + 1 < (int)v.size(); ++i) v[i] = v[i + 1];
        v.pop_back();
    }
    T&   front()       { return v[0]; }
    T&   back()        { return v.back(); }
    bool empty() const { return v.empty(); }
    int  size()  const { return (int)v.size(); }
};

template <typename T>
class DequeCircularBuffer {
    T*  buf;
    int cap;
    int head;
    int cnt;
    void resize(int nc) {
        T* nb = new T[nc];
        for (int i = 0; i < cnt; ++i) nb[i] = buf[(head + i) % cap];
        delete[] buf;
        buf = nb; cap = nc; head = 0;
    }
public:
    explicit DequeCircularBuffer(int initial = 4)
        : cap(initial < 1 ? 1 : initial), head(0), cnt(0) { buf = new T[cap]; }
    DequeCircularBuffer(const DequeCircularBuffer& o) : cap(o.cap), head(0), cnt(o.cnt) {
        buf = new T[cap];
        for (int i = 0; i < cnt; ++i) buf[i] = o.buf[(o.head + i) % o.cap];
    }
    DequeCircularBuffer& operator=(const DequeCircularBuffer& o) {
        if (this == &o) return *this;
        delete[] buf;
        cap = o.cap; cnt = o.cnt; head = 0;
        buf = new T[cap];
        for (int i = 0; i < cnt; ++i) buf[i] = o.buf[(o.head + i) % o.cap];
        return *this;
    }
    ~DequeCircularBuffer() { delete[] buf; }

    void push_back(const T& x) {
        if (cnt == cap) resize(cap * 2);
        buf[(head + cnt) % cap] = x;
        cnt++;
    }
    void push_front(const T& x) {
        if (cnt == cap) resize(cap * 2);
        head = (head - 1 + cap) % cap;
        buf[head] = x;
        cnt++;
    }
    void pop_front() { if (cnt) { head = (head + 1) % cap; cnt--; } }
    void pop_back()  { if (cnt) { cnt--; } }
    T&   front()       { return buf[head]; }
    T&   back()        { return buf[(head + cnt - 1) % cap]; }
    bool empty() const { return cnt == 0; }
    int  size()  const { return cnt; }
};

template <typename Stack>
void testStack(const string& name) {
    Stack s;
    for (int x : {1, 2, 3, 4, 5}) s.push(x);
    cout << name << ": top=" << s.top() << " size=" << s.size() << " -> pop all: ";
    while (!s.empty()) { cout << s.top() << " "; s.pop(); }
    cout << "\n";
}

template <typename Queue>
void testQueue(const string& name) {
    Queue q;
    for (int x : {1, 2, 3, 4, 5}) q.push(x);
    cout << name << ": front=" << q.front() << " size=" << q.size() << " -> pop all: ";
    while (!q.empty()) { cout << q.front() << " "; q.pop(); }
    cout << "\n";
}

template <typename Deque>
void testDeque(const string& name) {
    Deque d;
    d.push_back(1); d.push_back(2);
    d.push_front(0);
    d.push_back(3);
    cout << name << ": front=" << d.front() << " back=" << d.back()
         << " size=" << d.size() << " -> (pop_front): ";
    while (!d.empty()) { cout << d.front() << " "; d.pop_front(); }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "===== STACKS (esperado LIFO: 5 4 3 2 1) =====\n";
    testStack<StackLinkedList<int>>("linked list ");
    testStack<StackTwoQueues<int>> ("dos queues  ");
    testStack<StackVector<int>>    ("vector      ");

    cout << "\n===== QUEUES (esperado FIFO: 1 2 3 4 5) =====\n";
    testQueue<QueueLinkedList<int>>("linked list ");
    testQueue<QueueTwoStacks<int>> ("dos stacks  ");
    testQueue<QueueVector<int>>    ("vector      ");

    cout << "\n===== DEQUES (esperado: 0 1 2 3) =====\n";
    testDeque<DequeDoublyLinked<int>>  ("doubly linked ");
    testDeque<DequeVector<int>>        ("vector        ");
    testDeque<DequeCircularBuffer<int>>("buffer circular");

    return 0;
}

// Pruebas generadas con la ayuda de la ia