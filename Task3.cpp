#include "Task3.h"
#include <iostream>
int main() {
    my_vector<int> v = {1,2,3};
    v.push_back(4);
    for (int& x : v) std::cout << x << " ";
    std::cout << "\nsize=" << v.size() << " cap=" << v.capacity() << "\n";
}