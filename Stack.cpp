//
// Created by alons on 4/09/2026.
//
#include <bits/stdc++.h>
using namespace std;


template <typename T>
struct Stack {
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* topNode = nullptr;
    int sz = 0;

    void push(T value) {
        Node* node = new Node(value);
        node->next = topNode;
        topNode = node;
        sz++;
    }

    void pop() {
        if (!topNode) return;
        Node* tmp = topNode;
        topNode = topNode->next;
        delete tmp;
        sz--;
    }

    // Ver el elemento de arriba (sin quitarlo)
    T& top() { return topNode->data; }

    bool empty() const { return sz == 0; }
    int size() const { return sz; }

    ~Stack() {
        while (topNode) { Node* tmp = topNode; topNode = topNode->next; delete tmp; }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    cout << "top: " << s.top() << "\n";
    s.pop();
    cout << "top: " << s.top() << "\n";
    cout << "tamano: " << s.size() << "\n";

    // Vaciar imprimiendo de arriba hacia abajo
    while (!s.empty()) { cout << s.top() << " "; s.pop(); }
    cout << "\n";

    return 0;
}