#include <iostream>

#include "DSA/Vector.h"
#include "DSA/String.h"

int main()
{
    Vector<int> v = {1, 2, 3, 4, 5};
    v.push_back(6);
    v.erase(v.begin() + 1);
    v.push_back(7);

    Vector<int> another_v = {6, 7, 8};
    v.insert(v.end(), v.begin(), v.end());
    Vector<int>::iterator vit = v.begin();
    while (vit != v.end())
    {
        std::cout << *vit << std::endl;
        vit++;
    }

    return 0;
}