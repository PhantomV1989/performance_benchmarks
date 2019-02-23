/*
https://stackoverflow.com/questions/42588264/why-is-stdunordered-map-slow-and-can-i-use-it-more-effectively-to-alleviate-t
unordered_map may be O(1), but because of hash fn and cache misses, it is 100x slower than array
*/
#include <cstdio>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

static const auto speedup = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

const int iii = 1000;

void int_test()
{
    int n[iii];
    vector<int> n1;
    std::unordered_map<int, int> m;
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iii; i++)
    {
        n[i] = i;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto tt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Int arr put:" << tt << "\n";
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iii; i++)
    {
        for (int j = 0; j < iii; j++)
        {
            if (n[i] == i)
                break;
        }
    }
    t2 = std::chrono::high_resolution_clock::now();
    tt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Int arr find:" << tt << "\n";
    /////////////////////////////////////////////////////////
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iii; i++)
    {
        n1.push_back(i);
    }
    t2 = std::chrono::high_resolution_clock::now();
    tt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Int vector put:" << tt << "\n";
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iii; i++)
    {
        std::find(n1.begin(), n1.end(), i);
    }
    t2 = std::chrono::high_resolution_clock::now();
    tt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Int vector find:" << tt << "\n";
    ///////////////////////////////////////////////////////////////
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iii; i++)
    {
        m[i] = i;
    }
    t2 = std::chrono::high_resolution_clock::now();
    tt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Int hash put:" << tt << "\n";
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iii; i++)
    {
        std::unordered_map<int, int>::const_iterator got = m.find(i);
    }
    t2 = std::chrono::high_resolution_clock::now();
    tt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Int hash find:" << tt << "\n";
    t1 = std::chrono::high_resolution_clock::now();
}

string random_string(size_t length)
{
    auto randchar = []() -> char {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}
void string_test()
{
    vector<string> o;
    for (int i = 0; i < iii; i++)
        o.push_back(random_string(10));
    string n[iii];
    vector<string> n1;
    std::unordered_map<string, int> m;

    auto t1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iii; i++)
    {
        n[i] = o[i];
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto tt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Str arr put:" << tt << "\n";
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iii; i++)
    {
        for (int j = 0; j < iii; j++)
        {
            if (n[i] == o[i])
                break;
        }
    }
    t2 = std::chrono::high_resolution_clock::now();
    tt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Str arr find:" << tt << "\n";
    /////////////////////////////////////////////////////////
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iii; i++)
    {
        n1.push_back(o[i]);
    }
    t2 = std::chrono::high_resolution_clock::now();
    tt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Str vector put:" << tt << "\n";
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iii; i++)
    {
        std::find(n1.begin(), n1.end(), o[i]);
    }
    t2 = std::chrono::high_resolution_clock::now();
    tt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Str vector find:" << tt << "\n";
    ///////////////////////////////////////////////////////////////
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iii; i++)
    {
        m[o[i]] = i;
    }
    t2 = std::chrono::high_resolution_clock::now();
    tt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Str hash put:" << tt << "\n";
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iii; i++)
    {
        std::unordered_map<string, int>::const_iterator got = m.find(o[i]);
    }
    t2 = std::chrono::high_resolution_clock::now();
    tt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Str hash find:" << tt << "\n";
    t1 = std::chrono::high_resolution_clock::now();
}

int main()
{
    int_test();
    string_test();
}
