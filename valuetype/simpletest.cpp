#include "Map.hpp"

#include <iostream>
#include <cassert>

// unrealistic examples
void access_by_key() {
    cs540::Map<int, long> m;
    /*
    int a[] = {6000, 3000, 1500, 15, 154};

    for(int i=0; i<5; i++)
    {

        m.print();
        m.insert({a[i], a[i]});

        m.print();
        if(rand()%2)
        {
            std::cout << "----------------------REMOVE: " << a[i] << std::endl;
            m.erase(a[i]);
        }

        m.print();
    }
    */
    m.insert({21741, 50});
    m.insert({1378, 5});
    m.insert({19941, 5});
    m.insert({5768, 10});
    
    m.erase(19941);
    //m.print();
    m.erase(5768);
    //m.print();
    m.insert({1994, 2});
    m.insert({20994, 2});
    m.print();
}

int main () {
    access_by_key();
    return 0;
}
