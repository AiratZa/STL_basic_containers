//
// Created by Great Drake on 6/20/21.
//

#include "test_list.hpp"


TEST(List, constructors_and_assign ) {

// default (1)
    {
        ft::list<int> l1;
        std::list<int> l2;

        ASSERT_LISTS_EQ(l1, l2);

        l1.push_back(1);
        l1.push_back(2);
        l1.push_back(3);

        l2.push_back(1);
        l2.push_back(2);
        l2.push_back(3);

        ASSERT_LISTS_EQ(l1, l2);
    }

// fill (2)
    {
        ft::list<int> l1(300, 42);
        std::list<int> l2(300, 42);

        ASSERT_LISTS_EQ(l1, l2);
    }


// range (3)
    {
        ft::list<int> l1(42, 21);
        std::list<int> l2(42, 21);

        ASSERT_LISTS_EQ(l1, l2);

        ft::list<int> cp_l1(l1.begin(), l1.end());
        std::list<int> cp_l2(l2.begin(), l2.end());

        ASSERT_LISTS_EQ(cp_l1, cp_l2);
    }

// copy (4)
    {
        ft::list<int> l1(42, 21);
        std::list<int> l2(42, 21);

        ASSERT_LISTS_EQ(l1, l2);

        ft::list<int> cp_l1(l1);
        std::list<int> cp_l2(l2);

        ASSERT_LISTS_EQ(cp_l1, cp_l2);
    }

// operator = (assign)
    {
        ft::list<int> l1(42, 21);
        std::list<int> l2(42, 21);

        ASSERT_LISTS_EQ(l1, l2);

        ft::list<int> cp_l1 = l1;
        std::list<int> cp_l2 = l2;

        ASSERT_LISTS_EQ(cp_l1, cp_l2);
    }
}


// CAPACITY

TEST(List_size, zero_size) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    ASSERT_EQ(l1.size(), l2.size());
}

TEST(List_size, preinitialized_values) {
    ft::list<int> l1(100, 100);
    std::list<int> l2(100, 100);

    ASSERT_EQ(l1.size(), l2.size());
}

TEST(List_size, default_values) {
    ft::list<int> l1(100);
    std::list<int> l2(100);

    ASSERT_EQ(l1.size(), l2.size());
}

// EMPTY CLEAR
TEST(List_size, empty_clear) {
    ft::list<int> l1(100);
    std::list<int> l2(100);

    ASSERT_EQ(l1.empty(), l2.empty());

    l1.clear();
    l2.clear();

    ASSERT_EQ(l1.empty(), l2.empty());
}


bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

// MERGE
TEST(List, merge) {

    {
        std::list<double> first, second;

        first.push_back (3.1);
        first.push_back (2.2);
        first.push_back (2.9);

        second.push_back (3.7);
        second.push_back (7.1);
        second.push_back (1.4);

        first.sort();
        second.sort();

        first.merge(second);

        // (second is now empty)

        second.push_back (2.1);

        first.merge(second,mycomparison);

        std::cout << "first contains:";
        for (std::list<double>::iterator it=first.begin(); it!=first.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    {
        ft::list<double> first, second;

        first.push_back (3.1);
        first.push_back (2.2);
        first.push_back (2.9);

        second.push_back (3.7);
        second.push_back (7.1);
        second.push_back (1.4);

        first.sort();
        second.sort();

        first.merge(second);

        // (second is now empty)

        second.push_back (2.1);

        first.merge(second,mycomparison);

        std::cout << "first contains:";
        for (ft::list<double>::iterator it=first.begin(); it!=first.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }


}




// SORT

// comparison, not case sensitive.
bool compare_nocase (const std::string& first, const std::string& second)
{
    unsigned int i=0;
    while ( (i<first.length()) && (i<second.length()) )
    {
        if (tolower(first[i])<tolower(second[i])) return true;
        else if (tolower(first[i])>tolower(second[i])) return false;
        ++i;
    }
    return ( first.length() < second.length() );
}

TEST(List, sort) {
    {
        std::list<std::string> mylist;
        std::list<std::string>::iterator it;
        mylist.push_back ("one");
        mylist.push_back ("two");
        mylist.push_back ("Three");

        mylist.sort();

        std::cout << "mylist contains:";
        for (it=mylist.begin(); it!=mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';

        mylist.sort(compare_nocase);

        std::cout << "mylist contains:";
        for (it=mylist.begin(); it!=mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }


    {
        ft::list<std::string> mylist;
        ft::list<std::string>::iterator it;
        mylist.push_back ("one");
        mylist.push_back ("two");
        mylist.push_back ("Three");

        mylist.sort();

        std::cout << "mylist contains:";
        for (it=mylist.begin(); it!=mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';

        mylist.sort(compare_nocase);

        std::cout << "mylist contains:";
        for (it=mylist.begin(); it!=mylist.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

}

// REVERSE

TEST(List, reverse) {
    {
        std::list<int> mylist;

        for (int i=1; i<10; ++i) mylist.push_back(i);

        mylist.reverse();

        std::cout << "mylist contains:";
        for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
            std::cout << ' ' << *it;

        std::cout << '\n';
    }

    {
        ft::list<int> mylist;

        for (int i=1; i<10; ++i) mylist.push_back(i);

        mylist.reverse();

        std::cout << "mylist contains:";
        for (ft::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
            std::cout << ' ' << *it;

        std::cout << '\n';
    }

}


// GET ALLOCATOR
TEST(List, get_allocator) {
    {
        std::list<int> mylist;
        int * p;

        // allocate an array of 5 elements using mylist's allocator:
        p=mylist.get_allocator().allocate(5);

        // assign some values to array
        for (int i=0; i<5; ++i) p[i]=i;

        std::cout << "The allocated array contains:";
        for (int i=0; i<5; ++i) std::cout << ' ' << p[i];
        std::cout << '\n';

        mylist.get_allocator().deallocate(p,5);
    }

    {
        ft::list<int> mylist;
        int * p;

        // allocate an array of 5 elements using mylist's allocator:
        p=mylist.get_allocator().allocate(5);

        // assign some values to array
        for (int i=0; i<5; ++i) p[i]=i;

        std::cout << "The allocated array contains:";
        for (int i=0; i<5; ++i) std::cout << ' ' << p[i];
        std::cout << '\n';

        mylist.get_allocator().deallocate(p,5);
    }
}







