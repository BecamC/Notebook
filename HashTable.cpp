//
// Created by alons on 14/09/2026.
//
#include <bits/stdc++.h>
using namespace std;

/* ============================================================
   FUNCIONES HASH
   Una funcion hash transforma una clave en un indice dentro
   del rango [0, m-1] (m = numero de buckets), distribuyendo las
   claves lo mas uniformemente posible para evitar colisiones.
   ============================================================ */

// --- Metodo de la division ---   h(k) = k mod m
// Simple y rapido. Conviene elegir m PRIMO y lejos de potencias
// de 2. Mala eleccion: m = 2^p (solo usa los p bits bajos de k).
int hashDivision(long long k, int m) {
    return (int)(((k % m) + m) % m);   // el +m evita indices negativos
}

// --- Metodo de la multiplicacion ---   h(k) = floor(m * frac(k*A))
// frac(x) = parte fraccionaria de x.  A = (sqrt(5)-1)/2 ~ 0.6180339887
// (constante de Knuth, da buena dispersion). Aqui m NO tiene que ser primo.
int hashMultiplication(long long k, int m) {
    const double A = 0.6180339887498949;
    double x = (double)k * A;
    double frac = x - floor(x);        // parte fraccionaria en [0,1)
    return (int)(m * frac);            // escalar a [0, m-1]
}

// --- Hash de string (hash polinomial / rolling hash) ---
// h = (s[0]*B^(L-1) + s[1]*B^(L-2) + ... + s[L-1]) mod m
// B = base (tipicamente un primo pequeno como 31 o 131).
long long hashString(const string& s, int m, int B = 31) {
    long long h = 0;
    for (unsigned char c : s) h = (h * B + c) % m;
    return h;
}

/* ============================================================
   TABLA HASH (claves enteras) con ENCADENAMIENTO
   Cada bucket es una lista de pares (clave, valor). Si dos claves
   caen en el mismo indice (colision), conviven en la misma lista.
   insert / find / remove ~ O(1) promedio si el factor de carga
   (n/m) se mantiene bajo.
   ============================================================ */
struct HashTable {
    enum Method { DIVISION, MULTIPLICATION };

    int m;                                  // numero de buckets
    Method method;
    vector<list<pair<int,int>>> table;      // bucket -> lista de (clave, valor)

    HashTable(int buckets = 101, Method meth = DIVISION)
        : m(buckets), method(meth), table(buckets) {}

    int hash(int key) {
        return (method == DIVISION) ? hashDivision(key, m)
                                    : hashMultiplication(key, m);
    }

    // Insertar o actualizar el valor de una clave
    void insert(int key, int value) {
        int idx = hash(key);
        for (auto& p : table[idx])
            if (p.first == key) { p.second = value; return; }
        table[idx].push_back({key, value});
    }

    // Buscar: devuelve puntero al valor, o nullptr si no existe
    int* find(int key) {
        int idx = hash(key);
        for (auto& p : table[idx])
            if (p.first == key) return &p.second;
        return nullptr;
    }

    // Eliminar una clave. Devuelve true si existia.
    bool remove(int key) {
        int idx = hash(key);
        auto& bucket = table[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
            if (it->first == key) { bucket.erase(it); return true; }
        return false;
    }
};

/* ============================================================
   TABLA HASH (claves string) con ENCADENAMIENTO
   Identica a la anterior, pero usa hashString para el indice.
   ============================================================ */
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

    // --- Comparar las funciones hash sobre las mismas claves ---
    cout << "clave        | division | multiplicacion\n";
    for (long long k : {5LL, 101LL, 202LL, 1234LL, 999999937LL})
        cout << setw(12) << k << " | " << setw(8) << hashDivision(k, m)
             << " | " << hashMultiplication(k, m) << "\n";
    cout << "\n";

    // --- Tabla hash de enteros (metodo de la division) ---
    HashTable h(101, HashTable::DIVISION);
    h.insert(10, 100);
    h.insert(20, 200);
    h.insert(111, 999);      // 111 % 101 = 10 -> colisiona con la clave 10
    cout << "find(20)  = " << *h.find(20) << "\n";     // 200
    cout << "find(111) = " << *h.find(111) << "\n";    // 999 (convive con 10 en el bucket)
    h.insert(20, 250);       // actualizar valor existente
    cout << "find(20) tras update = " << *h.find(20) << "\n";        // 250
    h.remove(10);
    cout << "find(10) tras remove = "
         << (h.find(10) ? "existe" : "no existe") << "\n";           // no existe
    cout << "\n";

    // --- Hash de strings ---
    cout << "hashString:\n";
    for (const string& s : {"hola", "mundo", "algoritmos"})
        cout << "  " << s << " -> " << hashString(s, m) << "\n";
    cout << "\n";

    // --- Tabla hash de strings ---
    HashTableStr hs(101);
    hs.insert("manzana", 3);
    hs.insert("pera", 7);
    cout << "find(\"manzana\") = " << *hs.find("manzana") << "\n";   // 3
    hs.remove("pera");
    cout << "find(\"pera\") = "
         << (hs.find("pera") ? "existe" : "no existe") << "\n";      // no existe

    return 0;
}