#include "Map.hpp"

#include <iostream>
#include <cassert>

// unrealistic examples
void access_by_key() {
    cs540::Map<int, long> m;
    
    m.insert({10, 10});
    m.insert({3, 3});
    m.insert({20, 20});
    m.insert({15, 15});

    //This works to insert
    /*
    int a[] = {10,3,20,15};
    for(int i=0; i < 4; i++)
    {
        std::pair<int, long> ins = std::make_pair(a[i],a[i]);
        m.insert(ins);
    }
    */
    auto iter = m.find(3);
    std::cout << iter->first << ":" << iter->second << std::endl;
    assert((*iter).second == 3);
}

int main () {
    access_by_key();
    return 0;
}
