#include <iostream>
#include "DSA/Array.h"
#include "DSA/Vector.h"

int main()
{
    Array<int, 5U> arr = {5, 4, 3, 2, 1};
    for (int i = 0; i < 5; i++)
    {
        arr[i] = i + 1;
    }

    Array<int, 5U>::iterator it = arr.begin();
    while (it != arr.end())
    {
        std::cout << *it++ << std::endl;
    }

    Vector<int> v = {1, 2, 3, 4, 5};
    v.push_back(6);
    v.erase(v.begin() + 1);
    v.push_back(7);
    Vector<int>::iterator vit = v.begin();
    while (vit != v.end())
    {
        std::cout << *vit << std::endl;
        vit++;
    }

    return 0;
}