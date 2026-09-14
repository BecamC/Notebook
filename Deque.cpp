//
// Created by alons on 4/09/2026.
//
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Deque {
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int sz = 0;

    void push_back(T value) {
        Node* node = new Node(value);
        if (!head) head = tail = node;
        else { node->prev = tail; tail->next = node; tail = node; }
        sz++;
    }

    void push_front(T value) {
        Node* node = new Node(value);
        if (!head) head = tail = node;
        else { node->next = head; head->prev = node; head = node; }
        sz++;
    }

    void pop_back() {
        if (!tail) return;
        Node* tmp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete tmp;
        sz--;
    }

    void pop_front() {
        if (!head) return;
        Node* tmp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete tmp;
        sz--;
    }

    T& front() { return head->data; }
    T& back()  { return tail->data; }

    bool empty() const { return sz == 0; }
    int size() const { return sz; }

    void print() const {
        for (Node* cur = head; cur; cur = cur->next) cout << cur->data << " ";
        cout << "\n";
    }

    ~Deque() {
        while (head) { Node* tmp = head; head = head->next; delete tmp; }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Deque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_front(0);
    dq.print();
    cout << "front: " << dq.front() << " | back: " << dq.back() << "\n"; // 0 | 2
    dq.pop_front();
    dq.pop_back();
    dq.push_front(-1);
    dq.print();
    cout << "tamano: " << dq.size() << "\n";

    return 0;
}