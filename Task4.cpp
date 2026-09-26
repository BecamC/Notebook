#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SingleLinkedList {
private:
    struct Node {
        T     data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int   sz;

public:
    SingleLinkedList() : head(nullptr), tail(nullptr), sz(0) {}

    SingleLinkedList(const SingleLinkedList& o) : head(nullptr), tail(nullptr), sz(0) {
        for (Node* c = o.head; c; c = c->next) push_back(c->data);
    }
    SingleLinkedList& operator=(const SingleLinkedList& o) {
        if (this == &o) return *this;
        clear();
        for (Node* c = o.head; c; c = c->next) push_back(c->data);
        return *this;
    }
    ~SingleLinkedList() { clear(); }

    void push_front(const T& v) {
        Node* n = new Node(v);
        n->next = head;
        head = n;
        if (!tail) tail = n;
        sz++;
    }

    void push_back(const T& v) {
        Node* n = new Node(v);
        if (!head) head = tail = n;
        else { tail->next = n; tail = n; }
        sz++;
    }

    void pop_front() {
        if (!head) return;
        Node* t = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete t;
        sz--;
    }

    void pop_back() {
        if (!head) return;
        if (head == tail) { delete head; head = tail = nullptr; sz--; return; }
        Node* c = head;
        while (c->next != tail) c = c->next;
        delete tail;
        tail = c;
        tail->next = nullptr;
        sz--;
    }

    int search(const T& v) const {
        int i = 0;
        for (Node* c = head; c; c = c->next, ++i)
            if (c->data == v) return i;
        return -1;
    }

    void insert(int pos, const T& v) {
        if (pos <= 0)  { push_front(v); return; }
        if (pos >= sz) { push_back(v);  return; }
        Node* c = head;
        for (int i = 0; i < pos - 1; ++i) c = c->next;
        Node* n = new Node(v);
        n->next = c->next;
        c->next = n;
        sz++;
    }

    bool remove(const T& v) {
        Node* c = head; Node* prev = nullptr;
        while (c) {
            if (c->data == v) {
                if (prev) prev->next = c->next; else head = c->next;
                if (c == tail) tail = prev;
                delete c;
                sz--;
                return true;
            }
            prev = c; c = c->next;
        }
        return false;
    }

    void merge(const SingleLinkedList& o) {
        int n = o.sz; Node* c = o.head;
        for (int i = 0; i < n; ++i) { push_back(c->data); c = c->next; }
    }

    void clear() {
        while (head) { Node* t = head; head = head->next; delete t; }
        tail = nullptr; sz = 0;
    }
    int  size()  const { return sz; }
    bool empty() const { return sz == 0; }
    T&   front()       { return head->data; }
    T&   back()        { return tail->data; }
    void print() const {
        for (Node* c = head; c; c = c->next) cout << c->data << " ";
        cout << "\n";
    }
};

template <typename T>
class DoubleLinkedList {
private:
    struct Node {
        T     data;
        Node* prev;
        Node* next;
        Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int   sz;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), sz(0) {}

    DoubleLinkedList(const DoubleLinkedList& o) : head(nullptr), tail(nullptr), sz(0) {
        for (Node* c = o.head; c; c = c->next) push_back(c->data);
    }
    DoubleLinkedList& operator=(const DoubleLinkedList& o) {
        if (this == &o) return *this;
        clear();
        for (Node* c = o.head; c; c = c->next) push_back(c->data);
        return *this;
    }
    ~DoubleLinkedList() { clear(); }

    void push_front(const T& v) {
        Node* n = new Node(v);
        n->next = head;
        if (head) head->prev = n; else tail = n;
        head = n;
        sz++;
    }

    void push_back(const T& v) {
        Node* n = new Node(v);
        n->prev = tail;
        if (tail) tail->next = n; else head = n;
        tail = n;
        sz++;
    }

    void pop_front() {
        if (!head) return;
        Node* t = head;
        head = head->next;
        if (head) head->prev = nullptr; else tail = nullptr;
        delete t;
        sz--;
    }

    void pop_back() {
        if (!tail) return;
        Node* t = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr; else head = nullptr;
        delete t;
        sz--;
    }

    int search(const T& v) const {
        int i = 0;
        for (Node* c = head; c; c = c->next, ++i)
            if (c->data == v) return i;
        return -1;
    }

    void insert(int pos, const T& v) {
        if (pos <= 0)  { push_front(v); return; }
        if (pos >= sz) { push_back(v);  return; }
        Node* c = head;
        for (int i = 0; i < pos; ++i) c = c->next;
        Node* n = new Node(v);
        n->prev = c->prev;
        n->next = c;
        c->prev->next = n;
        c->prev = n;
        sz++;
    }

    bool remove(const T& v) {
        for (Node* c = head; c; c = c->next) {
            if (c->data == v) {
                if (c->prev) c->prev->next = c->next; else head = c->next;
                if (c->next) c->next->prev = c->prev; else tail = c->prev;
                delete c;
                sz--;
                return true;
            }
        }
        return false;
    }

    void merge(const DoubleLinkedList& o) {
        int n = o.sz; Node* c = o.head;
        for (int i = 0; i < n; ++i) { push_back(c->data); c = c->next; }
    }

    void clear() {
        while (head) { Node* t = head; head = head->next; delete t; }
        tail = nullptr; sz = 0;
    }
    int  size()  const { return sz; }
    bool empty() const { return sz == 0; }
    T&   front()       { return head->data; }
    T&   back()        { return tail->data; }
    void print() const {
        for (Node* c = head; c; c = c->next) cout << c->data << " ";
        cout << "\n";
    }

    void print_reverse() const {
        for (Node* c = tail; c; c = c->prev) cout << c->data << " ";
        cout << "\n";
    }
};

template <typename T>
class CircularLinkedList {
private:
    struct Node {
        T     data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int   sz;

public:
    CircularLinkedList() : head(nullptr), tail(nullptr), sz(0) {}

    CircularLinkedList(const CircularLinkedList& o) : head(nullptr), tail(nullptr), sz(0) {
        Node* c = o.head;
        for (int i = 0; i < o.sz; ++i) { push_back(c->data); c = c->next; }
    }
    CircularLinkedList& operator=(const CircularLinkedList& o) {
        if (this == &o) return *this;
        clear();
        Node* c = o.head;
        for (int i = 0; i < o.sz; ++i) { push_back(c->data); c = c->next; }
        return *this;
    }
    ~CircularLinkedList() { clear(); }

    void push_front(const T& v) {
        Node* n = new Node(v);
        if (!head) { head = tail = n; n->next = n; }
        else { n->next = head; head = n; tail->next = head; }
        sz++;
    }

    void push_back(const T& v) {
        Node* n = new Node(v);
        if (!head) { head = tail = n; n->next = n; }
        else { n->next = head; tail->next = n; tail = n; }
        sz++;
    }

    void pop_front() {
        if (!head) return;
        if (head == tail) { delete head; head = tail = nullptr; sz--; return; }
        Node* t = head;
        head = head->next;
        tail->next = head;
        delete t;
        sz--;
    }

    void pop_back() {
        if (!head) return;
        if (head == tail) { delete head; head = tail = nullptr; sz--; return; }
        Node* c = head;
        while (c->next != tail) c = c->next;
        delete tail;
        tail = c;
        tail->next = head;
        sz--;
    }

    int search(const T& v) const {
        Node* c = head;
        for (int i = 0; i < sz; ++i, c = c->next)
            if (c->data == v) return i;
        return -1;
    }

    void insert(int pos, const T& v) {
        if (pos <= 0)  { push_front(v); return; }
        if (pos >= sz) { push_back(v);  return; }
        Node* c = head;
        for (int i = 0; i < pos - 1; ++i) c = c->next;
        Node* n = new Node(v);
        n->next = c->next;
        c->next = n;
        sz++;
    }

    bool remove(const T& v) {
        if (!head) return false;
        Node* c = head; Node* prev = tail;
        for (int i = 0; i < sz; ++i) {
            if (c->data == v) {
                if (c == head && c == tail) { delete c; head = tail = nullptr; sz--; return true; }
                if (c == head) head = c->next;
                if (c == tail) tail = prev;
                prev->next = c->next;
                delete c;
                sz--;
                return true;
            }
            prev = c; c = c->next;
        }
        return false;
    }

    void merge(const CircularLinkedList& o) {
        Node* c = o.head;
        int n = o.sz;
        for (int i = 0; i < n; ++i) { push_back(c->data); c = c->next; }
    }

    void clear() {
        if (!head) return;
        Node* c = head;
        for (int i = 0; i < sz; ++i) { Node* t = c; c = c->next; delete t; }
        head = tail = nullptr; sz = 0;
    }
    int  size()  const { return sz; }
    bool empty() const { return sz == 0; }
    T&   front()       { return head->data; }
    T&   back()        { return tail->data; }
    void print() const {
        Node* c = head;
        for (int i = 0; i < sz; ++i, c = c->next) cout << c->data << " ";
        cout << "\n";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "===== SINGLE LINKED LIST =====\n";
    SingleLinkedList<int> s;
    s.push_back(2); s.push_back(3); s.push_front(1);
    cout << "tras push: "; s.print();
    s.insert(2, 99);
    cout << "insert(2,99): "; s.print();
    cout << "search(99) = " << s.search(99) << "\n";
    s.remove(99);
    cout << "remove(99): "; s.print();
    s.pop_front(); s.pop_back();
    cout << "pop_front+pop_back: "; s.print();
    SingleLinkedList<int> s2;
    s2.push_back(7); s2.push_back(8);
    s.merge(s2);
    cout << "merge con [7 8]: "; s.print();

    cout << "\n===== DOUBLE LINKED LIST =====\n";
    DoubleLinkedList<int> d;
    d.push_back(10); d.push_back(20); d.push_front(5);
    cout << "tras push: "; d.print();
    cout << "en reversa: "; d.print_reverse();
    d.insert(1, 7);
    cout << "insert(1,7): "; d.print();
    cout << "search(20) = " << d.search(20) << "\n";
    d.remove(10);
    cout << "remove(10): "; d.print();
    d.pop_front(); d.pop_back();
    cout << "pop_front+pop_back: "; d.print();

    cout << "\n===== CIRCULAR LINKED LIST =====\n";
    CircularLinkedList<int> c;
    c.push_back(1); c.push_back(2); c.push_back(3);
    c.push_front(0);
    cout << "tras push: "; c.print();
    cout << "front=" << c.front() << " back=" << c.back() << " (back apunta a front)\n";
    c.insert(2, 50);
    cout << "insert(2,50): "; c.print();
    cout << "search(3) = " << c.search(3) << "\n";
    c.remove(0);
    cout << "remove(0): "; c.print();
    c.pop_back();
    cout << "pop_back: "; c.print();
    CircularLinkedList<int> c2;
    c2.push_back(100); c2.push_back(200);
    c.merge(c2);
    cout << "merge con [100 200]: "; c.print();

    return 0;
}

// Pruebas generadas con la ayuda de la ia