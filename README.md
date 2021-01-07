vector<int> myVector(20); //all zeros
vector<int> myVector(20, 1); //all ones

vector<int> myVector = {0, 100, 50};

myVector[i]

myVector.at(i) with exception out_of_range

myVector.size()

myVector.clear()

myVector.push_back()

myVector.pop_back()

myVector.capacity()

myVector.reserve(100)

myVector.shrink_to_fit()

myVector.empty() //has elements or not true|false


myVector.resize(20, 1) //like initialization



Итераторы

vector<int>::iterator it;

it = myVector.cbegin();
it = myVector.begin();
it = myVector.cend();
it = myVector.end();

*it = 1000;

it++;

it += 2;

it--;

it -= 2;


it != myVector.end()


______________________________

for(vector<int>::reverse_iterator i = myVector.rbegin(); i != myVector.rend(); i++ ) {
    cout << *i << endl;
}



advance(it, 3); //list::it += 3



__________________________________

myVector.insert(it, 999);
myVector.erase(itErase);
myVector.erase(itErase, advance(itErase, 3));


#include <list>

list<int> myList;

myList.push_back()
myList.push_front()

list<int>::iterator it myList.begin();


myList.sort();

myList.pop_back()

myList.pop_front()

myList.size()


myList.unique()//Удаляет дубли рядом

myList.reverse()

myList.clear()

myList.insert(it, 6)
myList.erase(it)

myList.remove(99)


myList.assign(3, 0);
myList.assign(myList2.begin(), myList2.end());





======================================

#include <deque>

double ended queque

Двусторонняя очередь

#include <stack>

stack<int, list<int>> st;

st.push()//создает копию объекта
st.emplace() 

