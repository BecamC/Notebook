//
// Created by alons on 4/09/2026.
//
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct DoublyLinkedList {
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

    void pop_front() {
        if (!head) return;
        Node* tmp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete tmp;
        sz--;
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

    void reverse() {
        Node* cur = head;
        while (cur) {
            swap(cur->prev, cur->next);
            cur = cur->prev;
        }
        swap(head, tail);
    }

    void remove(T value) {
        Node* cur = head;
        while (cur) {
            if (cur->data == value) {
                if (cur->prev) cur->prev->next = cur->next;
                else head = cur->next;
                if (cur->next) cur->next->prev = cur->prev;
                else tail = cur->prev;
                delete cur;
                sz--;
                return;
            }
            cur = cur->next;
        }
    }

    bool empty() const { return sz == 0; }
    int size() const { return sz; }

    void print() const {
        for (Node* cur = head; cur; cur = cur->next) cout << cur->data << " ";
        cout << "\n";
    }

    void print_reverse() const {
        for (Node* cur = tail; cur; cur = cur->prev) cout << cur->data << " ";
        cout << "\n";
    }

    ~DoublyLinkedList() {
        while (head) { Node* tmp = head; head = head->next; delete tmp; }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    DoublyLinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_front(0);
    l.print();
    l.print_reverse();
    l.pop_front();
    l.pop_back();
    l.push_back(5);
    l.push_back(9);
    l.print();
    l.reverse();
    l.print();
    l.remove(5);
    l.print();
    cout << "tamano: " << l.size() << "\n";

    return 0;
}