//
// Created by airat on 14.06.2021.
//

#include "test_map.hpp"

TEST(Map_constructor_iterators, map_default) {
    ft::map<int, int> v1;
    std::map<int, int> v2;

    ASSERT_MAPS_EQ(v1, v2);

    v1[1] = v2[1] = 1;
    v1[3] = v2[3] = 3;
    v1[100500] = v2[100500] = 100500;
    v1[100500] = v2[100500] = 0;
    ASSERT_MAPS_EQ(v1, v2);

    ////

    ft::map<std::string, int> s1;
    std::map<std::string, int> s2;

    ASSERT_MAPS_EQ(s1, s2);

    s1["1"] = s2["1"] = 1;
    s1["3"] = s2["3"] = 3;
    s1["100500"] = s2["100500"] = 100500;
    s1["100500"] = s2["100500"] = 0;
    ASSERT_MAPS_EQ(s1, s2);

}

TEST(Map_constructor_iterators, range_and_copy_1) {
    ft::map<int, int> v1;
    std::map<int, int> v2;

    ASSERT_MAPS_EQ(v1, v2);

    v1[1] = v2[1] = 1;
    v1[3] = v2[3] = 3;
    v1[100500] = v2[100500] = 100500;
    v1[100500] = v2[100500] = 0;
    ASSERT_MAPS_EQ(v1, v2);

    const ft::map<int, int> r1(v1.begin(), v1.end());
    const std::map<int, int> r2(v2.begin(), v2.end());
    ASSERT_MAPS_EQ(r1, r2);

    const ft::map<int, int> rr1(v1.begin(), v1.end());
    const std::map<int, int> rr2(v2.begin(), v2.end());
    ASSERT_MAPS_EQ(rr1, rr2);

    const ft::map<int, int> cp1(v1);
    const std::map<int, int> cp2(v2);
    ASSERT_MAPS_EQ(cp1, cp2);

    // iterators
    ASSERT_EQ(*(v1.begin()), *(v2.begin()));
    ASSERT_EQ(*(v1.rbegin()), *(v2.rbegin()));
    ASSERT_EQ(*(--v1.end()), *(--v2.end()));
    ASSERT_EQ(*(--v1.rend()), *(--v2.rend()));

    ASSERT_EQ(*(cp1.begin()), *(cp2.begin()));
    ASSERT_EQ(*(cp1.rbegin()), *(cp2.rbegin()));
    ASSERT_EQ(*(--cp1.end()), *(--cp2.end()));
    ASSERT_EQ(*(--cp1.rend()), *(--cp2.rend()));

}

TEST(Map_constructor_iterators, range_and_copy_2) {
    ft::map<std::string, int> s1;
    std::map<std::string, int> s2;

    ASSERT_MAPS_EQ(s1, s2);

    s1["1"] = s2["1"] = 1;
    s1["3"] = s2["3"] = 3;
    s1["100500"] = s2["100500"] = 100500;
    s1["100500"] = s2["100500"] = 0;
    ASSERT_MAPS_EQ(s1, s2);

    const ft::map<std::string, int> r1(s1.begin(), s1.end());
    const std::map<std::string, int> r2(s2.begin(), s2.end());
    ASSERT_MAPS_EQ(r1, r2);

    const ft::map<std::string, int> rr1(s1.begin(), s1.end());
    const std::map<std::string, int> rr2(s2.begin(), s2.end());
    ASSERT_MAPS_EQ(rr1, rr2);

    const ft::map<std::string, int> cp1(s1);
    const std::map<std::string, int> cp2(s2);
    ASSERT_MAPS_EQ(cp1, cp2);

    // iterators
    ASSERT_EQ(*(s1.begin()), *(s2.begin()));
    ASSERT_EQ(*(s1.rbegin()), *(s2.rbegin()));
    ASSERT_EQ(*(--s1.end()), *(--s2.end()));
    ASSERT_EQ(*(--s1.rend()), *(--s2.rend()));

    ASSERT_EQ(*(cp1.begin()), *(cp2.begin()));
    ASSERT_EQ(*(cp1.rbegin()), *(cp2.rbegin()));
    ASSERT_EQ(*(--cp1.end()), *(--cp2.end()));
    ASSERT_EQ(*(--cp1.rend()), *(--cp2.rend()));
}


TEST(Map_capacity_clear_access, all) {
    ft::map<std::string, int> s1;
    std::map<std::string, int> s2;

    ASSERT_MAPS_EQ(s1, s2);

    // When empty
    {
        s1.clear();
        s2.clear();
        ASSERT_MAPS_EQ(s1, s2);

        ASSERT_EQ(s1.empty(), s2.empty());
        ASSERT_EQ(s1.size(), s2.size());
        ASSERT_EQ(s1.max_size(), s2.max_size());
    }


    s1["1"] = s2["1"] = 1;
    s1["3"] = s2["3"] = 3;
    s1["100500"] = s2["100500"] = 100500;
    s1["100500"] = s2["100500"] = 0;

    {
        ASSERT_EQ(s1["1"], s2["1"]);
        ASSERT_EQ(s1["2"], s2["2"]);
    }

    ASSERT_MAPS_EQ(s1, s2);

    // When no empty
    {
        ASSERT_EQ(s1.empty(), s2.empty());
        ASSERT_EQ(s1.size(), s2.size());
        ASSERT_EQ(s1.max_size(), s2.max_size());
    }

    // When empty again
    {
        s1.clear();
        s2.clear();
        ASSERT_MAPS_EQ(s1, s2);

        ASSERT_EQ(s1.empty(), s2.empty());
        ASSERT_EQ(s1.size(), s2.size());
        ASSERT_EQ(s1.max_size(), s2.max_size());
    }


    // Access with const
    {
        const ft::map<std::string, int> s1_const = s1;
        const std::map<std::string, int> s2_const = s2;

        // access by operator is not const, discarding qualifiers
        // ASSERT_EQ(s1_const["1"], s2_const["1"]);
        // ASSERT_EQ(s1_const["2"], s2_const["2"]);
    }
}


TEST(Map_insert_erase_swap, all) {
    ft::map<std::string, int> s1;
    std::map<std::string, int> s2;

    ASSERT_MAPS_EQ(s1, s2);

    s1["1"] = s2["1"] = 1;
    s1["2"] = s2["2"] = 2;
    s1["100500"] = s2["100500"] = 100500;
    s1["100500"] = s2["100500"] = 0;

    ASSERT_MAPS_EQ(s1, s2);

// single element (1)
    // 1

    {
        std::pair<std::string, int> new_pair("2", 2);

        std::pair<ft::map<std::string, int>::iterator, bool> res1 = s1.insert(new_pair);
        std::pair<std::map<std::string, int>::iterator, bool> res2 = s2.insert(new_pair);
        ASSERT_EQ(*(res1.first), *(res2.first));
        ASSERT_EQ((res1.second), (res2.second));


        // 2
        std::pair<std::string, int> old_pair("2", 2);

        res1 = s1.insert(new_pair);
        res2 = s2.insert(new_pair);
        ASSERT_EQ(*(res1.first), *(res2.first));
        ASSERT_EQ((res1.second), (res2.second));

        ASSERT_MAPS_EQ(s1, s2);
    }

// with hint (2)
    {
        std::pair<std::string, int> pair1("3", 3);
        std::pair<std::string, int> pair2("3", 3);

        ASSERT_EQ(*(s1.insert(s1.begin(), pair1)), *(s2.insert(s2.begin(), pair1)));
        ASSERT_EQ(*(s1.insert(s1.end(), pair2)), *(s2.insert(s2.end(), pair2)));
        ASSERT_MAPS_EQ(s1, s2);
    }

// range (3)
    {
        s1.insert(s1.begin(), s1.end());
        s2.insert(s2.begin(), s2.end());
        ASSERT_MAPS_EQ(s1, s2);

        s1.insert(s2.begin(), s2.end());
        s2.insert(s1.begin(), s1.end());
        ASSERT_MAPS_EQ(s1, s2);
    }

// SWAP

    {
        ft::map<std::string, int> ss1;
        std::map<std::string, int> ss2;
        ASSERT_MAPS_EQ(ss1, ss2);

        ss1.swap(s1);
        ss2.swap(s2);
        ASSERT_MAPS_EQ(ss1, ss2);

        ss1.swap(s1);
        ss2.swap(s2);
        ASSERT_MAPS_EQ(ss1, ss2);
    }


// ERASE
    {
        s1.erase(s1.begin());
        s2.erase(s2.begin());
        ASSERT_MAPS_EQ(s1, s2);

        ASSERT_EQ(s1.erase("3"), s2.erase("3"));
        ASSERT_MAPS_EQ(s1, s2);

        ASSERT_EQ(s1.erase("3"), s2.erase("3"));
        ASSERT_MAPS_EQ(s1, s2);

        s1.erase(s1.begin(), --(s1.end()));
        s2.erase(s2.begin(), --(s2.end()));
        ASSERT_MAPS_EQ(s1, s2);
    }
}


TEST(Map_observers_and_others, key_compare) {
// KEY COMPARE
    {
        std::map<char,int> mymap;

        std::map<char,int>::key_compare mycomp = mymap.key_comp();

        mymap['a']=100;
        mymap['b']=200;
        mymap['c']=300;

        std::cout << "mymap contains:\n";

        char highest = mymap.rbegin()->first;     // key value of last element

        std::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mycomp((*it++).first, highest) );

        std::cout << '\n';
    }

    {
        ft::map<char,int> mymap;

        ft::map<char,int>::key_compare mycomp = mymap.key_comp();

        mymap['a']=100;
        mymap['b']=200;
        mymap['c']=300;

        std::cout << "mymap contains:\n";

        char highest = mymap.rbegin()->first;     // key value of last element

        ft::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mycomp((*it++).first, highest) );

        std::cout << '\n';
    }

}


TEST(Map_observers_and_others, value_compare) {
    {
        std::map<char,int> mymap;

        mymap['x']=1001;
        mymap['y']=2002;
        mymap['z']=3003;

        std::cout << "mymap contains:\n";

        std::pair<char,int> highest = *mymap.rbegin();          // last element

        std::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mymap.value_comp()(*it++, highest) );
    }

    {
        ft::map<char,int> mymap;

        mymap['x']=1001;
        mymap['y']=2002;
        mymap['z']=3003;

        std::cout << "mymap contains:\n";

        std::pair<char,int> highest = *mymap.rbegin();          // last element

        ft::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mymap.value_comp()(*it++, highest) );
    }
}


TEST(Map_observers_and_others, find_and_count) {

    std::map<char,int> mymap1;
    std::map<char,int>::iterator it1;

    ft::map<char,int> mymap2;
    ft::map<char,int>::iterator it2;


    mymap1['a'] = mymap2['a'] = 50;
    mymap1['b'] = mymap2['b'] = 100;
    mymap1['c'] = mymap2['c'] = 150;
    mymap1['d'] = mymap2['d'] = 200;

    it1 = mymap1.find('b');
    it2 = mymap2.find('b');
    ASSERT_EQ(*it1, *it2);
    ASSERT_EQ(mymap1.count('b'), mymap2.count('b'));
    ASSERT_MAPS_EQ(mymap2, mymap1);


    if (it1 != mymap1.end())
        mymap1.erase (it1);
    if (it2 != mymap2.end())
        mymap2.erase (it2);

    it1 = mymap1.find('b');
    it2 = mymap2.find('b');
    ASSERT_EQ(it1, mymap1.end());
    ASSERT_EQ(it2, mymap2.end());
    ASSERT_EQ(mymap1.count('b'), mymap2.count('b'));
    ASSERT_MAPS_EQ(mymap2, mymap1);
}

TEST(Map_observers_and_others, upper_lower_bound) {

    {
        std::map<char,int> mymap;
        std::map<char,int>::iterator itlow,itup;

        mymap['a']=20;
        mymap['b']=40;
        mymap['c']=60;
        mymap['d']=80;
        mymap['e']=100;

        itlow=mymap.lower_bound ('b');  // itlow points to b
        itup=mymap.upper_bound ('d');   // itup points to e (not d!)

        mymap.erase(itlow,itup);        // erases [itlow,itup)

        // print content:
        for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

    }

    {
        ft::map<char,int> mymap;
        ft::map<char,int>::iterator itlow,itup;

        mymap['a']=20;
        mymap['b']=40;
        mymap['c']=60;
        mymap['d']=80;
        mymap['e']=100;

        itlow=mymap.lower_bound ('b');  // itlow points to b
        itup=mymap.upper_bound ('d');   // itup points to e (not d!)

        mymap.erase(itlow,itup);        // erases [itlow,itup)

        // print content:
        for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

    }
}



TEST(Map_observers_and_others, equal_range) {
    {
        std::map<char,int> mymap;

        mymap['a']=10;
        mymap['b']=20;
        mymap['c']=30;

        std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
        ret = mymap.equal_range('b');

        std::cout << "lower bound points to: ";
        std::cout << ret.first->first << " => " << ret.first->second << '\n';

        std::cout << "upper bound points to: ";
        std::cout << ret.second->first << " => " << ret.second->second << '\n';
    }

    {
        ft::map<char,int> mymap;

        mymap['a']=10;
        mymap['b']=20;
        mymap['c']=30;

        std::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
        ret = mymap.equal_range('b');

        std::cout << "lower bound points to: ";
        std::cout << ret.first->first << " => " << ret.first->second << '\n';

        std::cout << "upper bound points to: ";
        std::cout << ret.second->first << " => " << ret.second->second << '\n';
    }
}

TEST(Map_observers_and_others, get_allocator) {
    {
        int psize;
        std::map<char,int> mymap;
        std::pair<const char,int>* p;

        // allocate an array of 5 elements using mymap's allocator:
        p=mymap.get_allocator().allocate(5);

        // assign some values to array
        psize = sizeof(std::map<char,int>::value_type)*5;

        std::cout << "The allocated array has a size of " << psize << " bytes.\n";

        mymap.get_allocator().deallocate(p,5);
    }

    {
        int psize;
        ft::map<char,int> mymap;
        std::pair<const char,int>* p;

        // allocate an array of 5 elements using mymap's allocator:
        p=mymap.get_allocator().allocate(5);

        // assign some values to array
        psize = sizeof(ft::map<char,int>::value_type)*5;

        std::cout << "The allocated array has a size of " << psize << " bytes.\n";

        mymap.get_allocator().deallocate(p,5);
    }
}


TEST(Map_observers_and_others, operators_of_equality) {

    {
        ft::map<char,int> map1;
        ft::map<char,int> map2;

        map1['a'] = map2['a'] = 10;
        map1['b'] = map2['b'] = 20;
        map1['c'] = map2['c'] = 30;
        ASSERT_TRUE(map1 == map2);
    }

    {
        ft::map<char,int> map1;
        ft::map<char,int> map2;

        map1['a'] = map2['a'] = 10;
        map1['b'] = map2['b'] = 20;
        map1['c'] = 20;
        map2['c'] = 30;
        ASSERT_TRUE(map1 < map2);
        ASSERT_TRUE(map1 <= map2);

        ASSERT_TRUE(map1 != map2);

        ASSERT_TRUE(map2 > map1);
        ASSERT_TRUE(map2 >= map1);
    }
}


