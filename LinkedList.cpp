//
// Created by alons on 4/09/2026.
//
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct LinkedList {
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int sz = 0;

    // Insertar al final
    void push_back(T value) {
        Node* node = new Node(value);
        if (!head) head = tail = node;
        else { tail->next = node; tail = node; }
        sz++;
    }

    // Insertar al inicio
    void push_front(T value) {
        Node* node = new Node(value);
        if (!head) head = tail = node;
        else { node->next = head; head = node; }
        sz++;
    }

    // Eliminar del inicio
    void pop_front() {
        if (!head) return;
        Node* tmp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete tmp;
        sz--;
    }

    // Eliminar del final (recorremos hasta el penultimo)
    void pop_back() {
        if (!head) return;
        if (head == tail) { delete head; head = tail = nullptr; sz--; return; }
        Node* cur = head;
        while (cur->next != tail) cur = cur->next;
        delete tail;
        tail = cur;
        tail->next = nullptr;
        sz--;
    }

    // Invertir la lista
    void reverse() {
        Node* prev = nullptr;
        Node* cur = head;
        tail = head;
        while (cur) {
            Node* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        head = prev;
    }

    // Eliminar la primera aparicion de un valor
    void remove(T value) {
        Node* cur = head;
        Node* prev = nullptr;
        while (cur) {
            if (cur->data == value) {
                if (prev) prev->next = cur->next;
                else head = cur->next;
                if (cur == tail) tail = prev;
                delete cur;
                sz--;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
    }

    bool empty() const { return sz == 0; }
    int size() const { return sz; }

    void print() const {
        for (Node* cur = head; cur; cur = cur->next) cout << cur->data << " ";
        cout << "\n";
    }

    ~LinkedList() {
        while (head) { Node* tmp = head; head = head->next; delete tmp; }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    LinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_front(0);
    l.print();
    l.pop_back();
    l.pop_front();
    l.push_back(3);
    l.push_back(4);
    l.print();
    l.reverse();
    l.print();
    l.remove(3);
    l.print();
    cout << "tamano: " << l.size() << "\n";

    return 0;
}