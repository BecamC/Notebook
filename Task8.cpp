#include <bits/stdc++.h>
using namespace std;

struct BST {
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    void insert(int key) { root = insert(root, key); }
    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key)      node->left  = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        return node;
    }

    Node* find(Node* node, int target) {
        if (!node || node->key == target) return node;
        if (target < node->key) return find(node->left, target);
        else                    return find(node->right, target);
    }
    bool contains(int target) { return find(root, target) != nullptr; }

    void remove(int key) { root = remove(root, key); }
    Node* remove(Node* node, int key) {
        if (!node) return nullptr;
        if (key < node->key)      node->left  = remove(node->left, key);
        else if (key > node->key) node->right = remove(node->right, key);
        else {
            if (!node->left)  { Node* r = node->right; delete node; return r; }
            if (!node->right) { Node* l = node->left;  delete node; return l; }
            Node* succ = node->right;
            while (succ->left) succ = succ->left;
            node->key = succ->key;
            node->right = remove(node->right, succ->key);
        }
        return node;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
    void preorder(Node* node) {
        if (!node) return;
        cout << node->key << " ";
        preorder(node->left);
        preorder(node->right);
    }
    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->key << " ";
    }

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

    int height(Node* node) {
        if (!node) return -1;
        return 1 + max(height(node->left), height(node->right));
    }
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

    void inorder()   { inorder(root);   cout << "\n"; }
    void preorder()  { preorder(root);  cout << "\n"; }
    void postorder() { postorder(root); cout << "\n"; }
    int  height()    { return height(root); }

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

    cout << "In-order   (ascendente): "; t.inorder();
    cout << "Pre-order  (raiz-L-R):   "; t.preorder();
    cout << "Post-order (L-R-raiz):   "; t.postorder();
    cout << "Level-order (BFS):       "; t.levelorder(); cout << "\n";

    cout << "\nAltura del arbol:   " << t.height() << "\n";
    cout << "Profundidad de 20:  " << t.depth(20) << "\n";
    cout << "Profundidad de 70:  " << t.depth(70) << "\n";
    cout << "Contiene 40? " << (t.contains(40) ? "si" : "no") << "\n";
    cout << "Contiene 99? " << (t.contains(99) ? "si" : "no") << "\n";

    cout << "\n--- Eliminaciones ---\n";
    t.remove(20);
    cout << "Tras borrar 20 (hoja):     "; t.inorder();
    t.remove(30);
    cout << "Tras borrar 30 (1 hijo):   "; t.inorder();
    t.remove(50);
    cout << "Tras borrar 50 (2 hijos):  "; t.inorder();

    return 0;
}

// Pruebas generadas con la ayuda de la ia
