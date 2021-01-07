#include "headers/list.hpp"
#include <list>

#include <iostream>

// 1. Placement new
// new (ptr) T();

// 2. Явный вызов деструктора
// p->~T();

// 3. Перегрузка оператора new
// static void* operator new(size_t n) {
//     ::operator new( );
// }




int main(void) {

    // ft::list<int> hey;
    ft::list<int> hey1(3, 100);
    std::list<int> hey2(3, 100);

    // std::list<int>::iterator it;

    for(std::list<int>::iterator i = hey2.begin(); i != hey2.end(); i++ ) {
        std::cout << *i << std::endl;
    }

    return (0);
}