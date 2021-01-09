#include <iostream>
#include <list>

#include "source/list.hpp"


// 1. Placement new
// new (ptr) T();

// 2. Явный вызов деструктора
// p->~T();

// 3. Перегрузка оператора new
// static void* operator new(size_t n) {
//     ::operator new( );
// }




int main(void) {

//    ft::list<int> hey;
    ft::list<int> hey2(5, 4);

//    std::cout << hey2.size() << std::endl;
    // ft::list<int> hey1(3, 100);
//    std::list<int> hey2(3, 100);

    // std::list<int>::iterator it;

//    for(std::list<int>::iterator i = hey2.begin(); i != hey2.end(); i++ ) {
//        std::cout << *i << std::endl;
//    }
    std::cout << hey2.size() << std::endl;
    hey2.push_back(10);
    std::cout << hey2.size() << std::endl;

    std::list<int> hey;
    std::cout << "SIZE" << hey.size() << std::endl;
    hey.push_back(1);
    std::cout << "SIZE" << hey.size() << std::endl;

    return (0);
}