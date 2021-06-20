//
// Created by airat on 17.01.2021.
//

#include "test_vector.hpp"

TEST(Vector_constructor, default_ctr_plus_iterators) {
    {
        ft::vector<int> v1;
        std::vector<int> v2;

        ASSERT_VECTORS_EQ(v1, v2);

        v1.push_back(1);
        v1.push_back(3);
        v1.push_back(7);

        v2.push_back(1);
        v2.push_back(3);
        v2.push_back(7);

        ASSERT_VECTORS_EQ(v1, v2);

        // iterators testing
        ASSERT_EQ(*(v1.begin()), *(v2.begin()));
        ASSERT_EQ(*(--(v1.end())), *(--(v2.end())));
        ASSERT_EQ(*(v1.rbegin()), *(v2.rbegin()));
        ASSERT_EQ(*(--(v1.rend())), *(--(v2.rend())));

        {
            const ft::vector<int>& rv1 =  v1;
            const std::vector<int>& rv2 = v2;

            ASSERT_EQ(*(rv1.begin()), *(rv2.begin()));
            ASSERT_EQ(*(--(rv1.end())), *(--(rv2.end())));
            ASSERT_EQ(*(rv1.rbegin()), *(rv2.rbegin()));
            ASSERT_EQ(*(--(rv1.rend())), *(--(rv2.rend())));

        }

    }

    {
        ft::vector<std::string> v1;
        std::vector<std::string> v2;

        ASSERT_VECTORS_EQ(v1, v2);

        v1.push_back("1");
        v1.push_back("3");
        v1.push_back("7");

        v2.push_back("1");
        v2.push_back("3");
        v2.push_back("7");

        ASSERT_VECTORS_EQ(v1, v2);

        // iterators testing
        ASSERT_EQ(*(v1.begin()), *(v2.begin()));
        ASSERT_EQ(*(--(v1.end())), *(--(v2.end())));
        ASSERT_EQ(*(v1.rbegin()), *(v2.rbegin()));
        ASSERT_EQ(*(--(v1.rend())), *(--(v2.rend())));

        {
            const ft::vector<std::string>& rv1 =  v1;
            const std::vector<std::string>& rv2 = v2;

            ASSERT_EQ(*(rv1.begin()), *(rv2.begin()));
            ASSERT_EQ(*(--(rv1.end())), *(--(rv2.end())));
            ASSERT_EQ(*(rv1.rbegin()), *(rv2.rbegin()));
            ASSERT_EQ(*(--(rv1.rend())), *(--(rv2.rend())));

        }

    }

}


TEST(Vector_constructor, fill_ctr) {
    size_t count = 3;
    std::string str = "hello";

    ft::vector<std::string> v1(count, str);
    std::vector<std::string> v2(count, str);
    ASSERT_VECTORS_EQ(v1, v2);
}

TEST(Vector_constructor, range_ctr)
{
    ft::vector<std::string> v1;
    std::vector<std::string> v2;

    ASSERT_VECTORS_EQ(v1, v2);

    v1.push_back("1");
    v1.push_back("3");
    v1.push_back("7");

    v2.push_back("1");
    v2.push_back("3");
    v2.push_back("7");

    ASSERT_VECTORS_EQ(v1, v2);

    {
        ft::vector<std::string> rv1(v1.begin(), v1.end());
        std::vector<std::string> rv2(v2.begin(), v2.end());

        ASSERT_VECTORS_EQ(rv1, rv2);
    }

    {
        ft::vector<std::string> rv1(v2.begin(), v2.end());
        std::vector<std::string> rv2(v1.begin(), v1.end());

        ASSERT_VECTORS_EQ(rv1, rv2);
    }
    ASSERT_VECTORS_EQ(v1, v2);
}


TEST(Vector_constructor, copy_ctr_operator)
{
    ft::vector<std::string> v1;
    std::vector<std::string> v2;

    ASSERT_VECTORS_EQ(v1, v2);

    v1.push_back("1");
    v1.push_back("3");
    v1.push_back("7");

    v2.push_back("1");
    v2.push_back("3");
    v2.push_back("7");

    ASSERT_VECTORS_EQ(v1, v2);

    {
        ft::vector<std::string> rv1(v1);
        std::vector<std::string> rv2(v2);

        ASSERT_VECTORS_EQ(rv1, rv2);
    }

    {
        ft::vector<std::string> rv1 = v1;
        std::vector<std::string> rv2 = v2;

        ASSERT_VECTORS_EQ(rv1, rv2);
    }
    ASSERT_VECTORS_EQ(v1, v2);
}


TEST(Vector, capacity)
{
    ft::vector<std::string> v1;
    std::vector<std::string> v2;

    ASSERT_EQ(v1.size(), v2.size()); // SIZE
    ASSERT_EQ(v1.capacity(), v2.capacity()); // CAPACITY
    ASSERT_EQ(v1.empty(), v2.empty()); // EMPTY
    ASSERT_VECTORS_EQ(v1, v2);

    v1.push_back("1");
    v1.push_back("3");
    v1.push_back("7");

    v2.push_back("1");
    v2.push_back("3");
    v2.push_back("7");

    ASSERT_EQ(v1.size(), v2.size()); // SIZE
    ASSERT_EQ(v1.empty(), v2.empty()); // EMPTY
    ASSERT_VECTORS_EQ(v1, v2);

    {
        // RESIZE 1
        v1.resize(0);
        v2.resize(0);
        ASSERT_EQ(v1.size(), v2.size()); // SIZE
        ASSERT_EQ(v1.empty(), v2.empty()); // EMPTY
        ASSERT_VECTORS_EQ(v1, v2);

        // RESIZE 2
        v1.resize(5, std::string("hello"));
        v2.resize(5, std::string("hello"));
        ASSERT_EQ(v1.size(), v2.size()); // SIZE
        ASSERT_EQ(v1.empty(), v2.empty()); // EMPTY
        ASSERT_VECTORS_EQ(v1, v2);
    }

    {
        // RESERVE 1
        v1.reserve(0);
        v2.reserve(0);
        ASSERT_EQ(v1.size(), v2.size()); // SIZE
        ASSERT_EQ(v1.empty(), v2.empty()); // EMPTY
        ASSERT_VECTORS_EQ(v1, v2);

        // RESERVE 2
        v1.reserve(5);
        v2.reserve(5);
        ASSERT_EQ(v1.size(), v2.size()); // SIZE
        ASSERT_EQ(v1.empty(), v2.empty()); // EMPTY
        ASSERT_VECTORS_EQ(v1, v2);
    }
}


TEST(Vector, elements_access)
{
    ft::vector<std::string> v1;
    std::vector<std::string> v2;

    ASSERT_VECTORS_EQ(v1, v2);

    v1.push_back("1");
    v1.push_back("3");
    v1.push_back("7");

    v2.push_back("1");
    v2.push_back("3");
    v2.push_back("7");
    ASSERT_VECTORS_EQ(v1, v2);

    {
        for (int i = 0; i < 3; ++i) {
            ASSERT_EQ(v1[i], v2[i]);
            ASSERT_EQ(v1.at(i), v2.at(i));

            v1[i] = v2[i] = "temp_string_after_index";
            v1.at(i) = v2.at(i) = "temp_string_after_at_method";
        }

        ASSERT_THROW(v1.at(3), std::out_of_range);
        ASSERT_THROW(v2.at(3), std::out_of_range);
        ASSERT_VECTORS_EQ(v1, v2);

        const ft::vector<std::string>& rv1 = v1;
        const std::vector<std::string>& rv2 = v2;
        for (int i = 0; i < 3; ++i) {
            ASSERT_EQ(rv1[i], rv2[i]);
            ASSERT_EQ(v1.at(i), v2.at(i));

//            v1[i] = v2[i] = "temp_string_after_index";
//            v1.at(i) = v2.at(i) = "temp_string_after_at_method";
        }

        ASSERT_THROW(v1.at(3), std::out_of_range);
        ASSERT_THROW(v2.at(3), std::out_of_range);

        ASSERT_THROW(rv1.at(3), std::out_of_range);
        ASSERT_THROW(rv2.at(3), std::out_of_range);

        ASSERT_VECTORS_EQ(v1, v2);
        ASSERT_VECTORS_EQ(rv1, rv2);


    // FRONT, BACK

        ASSERT_EQ(v1.front(), v2.front());
        ASSERT_EQ(rv1.front(), rv2.front());

        ASSERT_EQ(v1.back(), v2.back());
        ASSERT_EQ(rv1.back(), rv2.back());
    }
}

TEST(Vector, modifiers_assign)
{
    // RANGE
    {
        ft::vector<std::string> v1;
        std::vector<std::string> v2;

        ASSERT_VECTORS_EQ(v1, v2);

        v1.push_back("1");
        v1.push_back("3");
        v1.push_back("7");

        v2.push_back("1");
        v2.push_back("3");
        v2.push_back("7");
        ASSERT_VECTORS_EQ(v1, v2);

        ft::vector<std::string> cv1;
        std::vector<std::string> cv2;

        cv1.assign(v1.begin(), v1.end());
        cv2.assign(v2.begin(), v2.end());

        ASSERT_VECTORS_EQ(cv1, cv2);
    }

    // FILL
    {
        ft::vector<std::string> v1;
        std::vector<std::string> v2;

        v1.assign(3, "three");
        v2.assign(3, "three");

        ASSERT_VECTORS_EQ(v1, v2);
    }
}

TEST(Vector, push_pop_back_insert_erase_swap)
{
    ft::vector<std::string> v1;
    std::vector<std::string> v2;

// PUSH POP BACK
    ASSERT_VECTORS_EQ(v1, v2);
    {
        v1.push_back("1");
        v1.push_back("7");

        v2.push_back("1");
        v2.push_back("7");
        ASSERT_VECTORS_EQ(v1, v2);

        v1.pop_back();
        v2.pop_back();

        ASSERT_VECTORS_EQ(v1, v2);
    }

// INSERT
    ASSERT_VECTORS_EQ(v1, v2);
    {
        // single element (1)
        v1.insert(v1.begin(), "test_single_element_insert");
        v2.insert(v2.begin(), "test_single_element_insert");
        ASSERT_VECTORS_EQ(v1, v2);

        // fill (2)
        v1.insert(v1.begin(), 4, "test_fill_insert");
        v2.insert(v2.begin(), 4, "test_fill_insert");
        ASSERT_VECTORS_EQ(v1, v2);

        // range (3)
        v1.insert(v1.begin(), v1.begin(), v1.end());
        v2.insert(v2.begin(), v2.begin(), v2.end());
        ASSERT_VECTORS_EQ(v1, v2);
    }

// ERASE
    ASSERT_VECTORS_EQ(v1, v2);
    {
        // 1
        ASSERT_EQ(*(v1.erase(v1.begin())), *(v2.erase(v2.begin())));
        ASSERT_VECTORS_EQ(v1, v2);

        // 2

        ft::vector<std::string>::iterator it_erase1 = v1.erase(v1.begin(), v1.end());
        std::vector<std::string>::iterator it_erase2 = v2.erase(v2.begin(), v2.end());
        ASSERT_EQ(it_erase1, v1.end());
        ASSERT_EQ(it_erase2, v2.end());
        ASSERT_VECTORS_EQ(v1, v2);
    }

// SWAP
    {
        ft::vector<int> foo_ft (3,100);   // three ints with a value of 100
        ft::vector<int> bar_ft (5,200);   // five ints with a value of 200

        std::vector<int> foo_std (3,100);   // three ints with a value of 100
        std::vector<int> bar_std (5,200);   // five ints with a value of 200

        ASSERT_VECTORS_EQ(foo_ft, foo_std);
        ASSERT_VECTORS_EQ(bar_ft, bar_std);

        // method
        foo_std.swap(bar_std);
        foo_ft.swap(bar_ft);

        ASSERT_VECTORS_EQ(foo_ft, foo_std);
        ASSERT_VECTORS_EQ(bar_ft, bar_std);

        // function
        std::swap(foo_std, bar_std);
        std::swap(foo_ft, bar_ft);
        ASSERT_VECTORS_EQ(foo_ft, foo_std);
        ASSERT_VECTORS_EQ(bar_ft, bar_std);

// CLEAR
        foo_std.clear();
        bar_std.clear();
        foo_ft.clear();
        bar_ft.clear();

        ASSERT_VECTORS_EQ(foo_ft, foo_std);
        ASSERT_VECTORS_EQ(bar_ft, bar_std);

        foo_std.clear();
        bar_std.clear();
        foo_ft.clear();
        bar_ft.clear();

        ASSERT_VECTORS_EQ(foo_ft, foo_std);
        ASSERT_VECTORS_EQ(bar_ft, bar_std);

    }
}



TEST(Vector, get_allocator)
{
    {
        std::vector<int> myvector;
        int * p;
        unsigned int i;

        // allocate an array with space for 5 elements using vector's allocator:
        p = myvector.get_allocator().allocate(5);

        // construct values in-place on the array:
        for (i=0; i<5; i++)
            myvector.get_allocator().construct(&p[i],i);

        std::cout << "The allocated array contains:";
        for (i=0; i<5; i++)
            std::cout << ' ' << p[i];
        std::cout << '\n';

        // destroy and deallocate:
        for (i=0; i<5; i++)
            myvector.get_allocator().destroy(&p[i]);
        myvector.get_allocator().deallocate(p,5);
    }

    {
        ft::vector<int> myvector;
        int * p;
        unsigned int i;

        // allocate an array with space for 5 elements using vector's allocator:
        p = myvector.get_allocator().allocate(5);

        // construct values in-place on the array:
        for (i=0; i<5; i++)
            myvector.get_allocator().construct(&p[i],i);

        std::cout << "The allocated array contains:";
        for (i=0; i<5; i++)
            std::cout << ' ' << p[i];
        std::cout << '\n';

        // destroy and deallocate:
        for (i=0; i<5; i++)
            myvector.get_allocator().destroy(&p[i]);
        myvector.get_allocator().deallocate(p,5);
    }
}


TEST(Vector, operators_of_equality) {

    {
        ft::vector<char> v1(3);
        ft::vector<char> v2(3);

        v1[0] = v2[0] = 'a';
        v1[1] = v2[1] = 'b';
        v1[2] = v2[2] = 'c';
        ASSERT_TRUE(v1 == v2);
    }

    {
        ft::vector<char> v1(3);
        ft::vector<char> v2(3);

        v1[0] = v2[0] = 'a';
        v1[1] = v2[1] = 'b';
        v1[2] = 'c';
        v2[2] = 'd';

        ASSERT_TRUE(v1 < v2);
        ASSERT_TRUE(v1 <= v2);

        ASSERT_TRUE(v1 != v2);

        ASSERT_TRUE(v2 > v1);
        ASSERT_TRUE(v2 >= v1);
    }
}


