//
// Created by alons on 14/09/2026.
//
#include <bits/stdc++.h>
using namespace std;

/* ============================================================
   BINARY SEARCH TREE (BST) - Arbol Binario de Busqueda
   Invariante: para cada nodo, todo lo del subarbol izquierdo es MENOR
   MENOR que su clave, y todo lo del derecho es MAYOR.

   Height (h): longitud (en aristas) del camino mas largo desde
               la raiz hasta una hoja. Arbol vacio = -1, hoja = 0.
   Depth (d):  distancia (en aristas) desde la raiz a un nodo.
               La raiz tiene profundidad 0.

   Forma vs. eficiencia:
   - BST balanceado:  h = O(log n)  -> insert/search/remove O(log n)
   - BST degenerado:  h = O(n)      -> si se insertan datos ordenados,
                                       se comporta como una lista enlazada.
   ============================================================ */
struct BST {
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    // ---------- INSERT ----------
    void insert(int key) { root = insert(root, key); }
    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);          // lugar encontrado
        if (key < node->key)      node->left  = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        // si key == node->key: no insertamos duplicados (se puede cambiar)
        return node;
    }

    // ---------- SEARCH ----------
    // 1) Si node es nullptr o node->key == target, retornar node.
    // 2) Si target < node->key, buscar en el subarbol izquierdo.
    // 3) Si target > node->key, buscar en el subarbol derecho.
    Node* find(Node* node, int target) {
        if (!node || node->key == target) return node;
        if (target < node->key) return find(node->left, target);
        else                    return find(node->right, target);
    }
    bool contains(int target) { return find(root, target) != nullptr; }

    // ---------- REMOVE ----------
    void remove(int key) { root = remove(root, key); }
    Node* remove(Node* node, int key) {
        if (!node) return nullptr;                       // no esta
        if (key < node->key)      node->left  = remove(node->left, key);
        else if (key > node->key) node->right = remove(node->right, key);
        else {
            // nodo encontrado
            // Caso 1: hoja (0 hijos)  y  Caso 2: un solo hijo
            if (!node->left)  { Node* r = node->right; delete node; return r; }
            if (!node->right) { Node* l = node->left;  delete node; return l; }
            // Caso 3: dos hijos -> reemplazar por el SUCESOR inorden
            // (el minimo del subarbol derecho) y luego borrarlo.
            Node* succ = node->right;
            while (succ->left) succ = succ->left;
            node->key = succ->key;
            node->right = remove(node->right, succ->key);
        }
        return node;
    }

    // ---------- RECORRIDOS DFS ----------
    // In-order (L - Raiz - R): produce las claves en orden ascendente.
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
    // Pre-order (Raiz - L - R): util para clonar/serializar el arbol.
    void preorder(Node* node) {
        if (!node) return;
        cout << node->key << " ";
        preorder(node->left);
        preorder(node->right);
    }
    // Post-order (L - R - Raiz): util para liberar memoria / evaluar expresiones.
    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->key << " ";
    }

    // ---------- RECORRIDO BFS ----------
    // Level-order: nivel por nivel, de izquierda a derecha (usa una queue).
    void levelorder() {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            cout << cur->key << " ";
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }

    // ---------- HEIGHT / DEPTH ----------
    // Altura: aristas del camino mas largo raiz->hoja. Vacio = -1.
    int height(Node* node) {
        if (!node) return -1;
        return 1 + max(height(node->left), height(node->right));
    }
    // Profundidad de una clave: aristas desde la raiz. -1 si no existe.
    int depth(int key) {
        int d = 0;
        Node* cur = root;
        while (cur) {
            if (key == cur->key) return d;
            cur = (key < cur->key) ? cur->left : cur->right;
            d++;
        }
        return -1;
    }

    // ---------- Atajos que arrancan desde la raiz ----------
    void inorder()   { inorder(root);   cout << "\n"; }
    void preorder()  { preorder(root);  cout << "\n"; }
    void postorder() { postorder(root); cout << "\n"; }
    int  height()    { return height(root); }

    // ---------- Liberar memoria (post-orden) ----------
    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    ~BST() { destroy(root); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BST t;
    for (int x : {50, 30, 70, 20, 40, 60, 80}) t.insert(x);
    /*
                50
               /  \
             30    70
            / \   / \
           20 40 60 80
    */

    cout << "In-order   (ascendente): "; t.inorder();      // 20 30 40 50 60 70 80
    cout << "Pre-order  (raiz-L-R):   "; t.preorder();      // 50 30 20 40 70 60 80
    cout << "Post-order (L-R-raiz):   "; t.postorder();     // 20 40 30 60 80 70 50
    cout << "Level-order (BFS):       "; t.levelorder(); cout << "\n"; // 50 30 70 20 40 60 80

    cout << "\nAltura del arbol:   " << t.height() << "\n"; // 2
    cout << "Profundidad de 20:  " << t.depth(20) << "\n";  // 2
    cout << "Profundidad de 70:  " << t.depth(70) << "\n";  // 1
    cout << "Contiene 40? " << (t.contains(40) ? "si" : "no") << "\n"; // si
    cout << "Contiene 99? " << (t.contains(99) ? "si" : "no") << "\n"; // no

    cout << "\n--- Eliminaciones ---\n";
    t.remove(20);   // Caso 1: hoja
    cout << "Tras borrar 20 (hoja):     "; t.inorder();     // 30 40 50 60 70 80
    t.remove(30);   // Caso 2: un hijo (40)
    cout << "Tras borrar 30 (1 hijo):   "; t.inorder();     // 40 50 60 70 80
    t.remove(50);   // Caso 3: dos hijos (sucesor = 60)
    cout << "Tras borrar 50 (2 hijos):  "; t.inorder();     // 40 60 70 80

    return 0;
}