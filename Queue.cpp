//
// Created by alons on 4/09/2026.
//
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Queue {
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int sz = 0;

    void push(T value) {
        Node* node = new Node(value);
        if (!head) head = tail = node;
        else { tail->next = node; tail = node; }
        sz++;
    }

    void pop() {
        if (!head) return;
        Node* tmp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete tmp;
        sz--;
    }

    T& front() { return head->data; }
    T& back()  { return tail->data; }

    bool empty() const { return sz == 0; }
    int size() const { return sz; }

    ~Queue() {
        while (head) { Node* tmp = head; head = head->next; delete tmp; }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << "front: " << q.front() << "\n";
    cout << "back: "  << q.back()  << "\n";
    q.pop();
    cout << "front: " << q.front() << "\n";

    // Vaciar en orden de llegada
    while (!q.empty()) { cout << q.front() << " "; q.pop(); }
    cout << "\n";

    return 0;
}