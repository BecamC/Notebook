#include <bits/stdc++.h>
using namespace std;

int hashDivision(long long k, int m) {
    return (int)(((k % m) + m) % m);
}

int hashMultiplication(long long k, int m) {
    const double A = 0.6180339887498949;
    double x = (double)k * A;
    double frac = x - floor(x);
    return (int)(m * frac);
}

long long hashString(const string& s, int m, int B = 31) {
    long long h = 0;
    for (unsigned char c : s) h = (h * B + c) % m;
    return h;
}

struct HashTable {
    enum Method { DIVISION, MULTIPLICATION };

    int m;
    Method method;
    vector<list<pair<int,int>>> table;

    HashTable(int buckets = 101, Method meth = DIVISION)
        : m(buckets), method(meth), table(buckets) {}

    int hash(int key) {
        return (method == DIVISION) ? hashDivision(key, m)
                                    : hashMultiplication(key, m);
    }

    void insert(int key, int value) {
        int idx = hash(key);
        for (auto& p : table[idx])
            if (p.first == key) { p.second = value; return; }
        table[idx].push_back({key, value});
    }

    int* find(int key) {
        int idx = hash(key);
        for (auto& p : table[idx])
            if (p.first == key) return &p.second;
        return nullptr;
    }

    bool remove(int key) {
        int idx = hash(key);
        auto& bucket = table[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
            if (it->first == key) { bucket.erase(it); return true; }
        return false;
    }
};

struct HashTableStr {
    int m;
    vector<list<pair<string,int>>> table;

    HashTableStr(int buckets = 101) : m(buckets), table(buckets) {}

    int hash(const string& key) { return (int)hashString(key, m); }

    void insert(const string& key, int value) {
        int idx = hash(key);
        for (auto& p : table[idx])
            if (p.first == key) { p.second = value; return; }
        table[idx].push_back({key, value});
    }

    int* find(const string& key) {
        int idx = hash(key);
        for (auto& p : table[idx])
            if (p.first == key) return &p.second;
        return nullptr;
    }

    bool remove(const string& key) {
        int idx = hash(key);
        auto& bucket = table[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
            if (it->first == key) { bucket.erase(it); return true; }
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m = 101;

    cout << "clave        | division | multiplicacion\n";
    for (long long k : {5LL, 101LL, 202LL, 1234LL, 999999937LL})
        cout << setw(12) << k << " | " << setw(8) << hashDivision(k, m)
             << " | " << hashMultiplication(k, m) << "\n";
    cout << "\n";

    HashTable h(101, HashTable::DIVISION);
    h.insert(10, 100);
    h.insert(20, 200);
    h.insert(111, 999);
    cout << "find(20)  = " << *h.find(20) << "\n";
    cout << "find(111) = " << *h.find(111) << "\n";
    h.insert(20, 250);
    cout << "find(20) tras update = " << *h.find(20) << "\n";
    h.remove(10);
    cout << "find(10) tras remove = "
         << (h.find(10) ? "existe" : "no existe") << "\n";
    cout << "\n";

    cout << "hashString:\n";
    for (const string& s : {"hola", "mundo", "algoritmos"})
        cout << "  " << s << " -> " << hashString(s, m) << "\n";
    cout << "\n";

    HashTableStr hs(101);
    hs.insert("manzana", 3);
    hs.insert("pera", 7);
    cout << "find(\"manzana\") = " << *hs.find("manzana") << "\n";
    hs.remove("pera");
    cout << "find(\"pera\") = "
         << (hs.find("pera") ? "existe" : "no existe") << "\n";

    return 0;
}

// Pruebas generadas con la ayuda de la ia
