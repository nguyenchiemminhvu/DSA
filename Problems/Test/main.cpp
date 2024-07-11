#include <iostream>

#include "DSA/Vector.h"
#include "DSA/String.h"

int main()
{
    Vector<int> v = {1, 2, 3, 4, 5};
    v.push_back(6);
    v.push_back(7);

    Vector<int> another_v = {6, 7, 8};
    v.insert(v.end(), another_v.begin(), another_v.end());
    Vector<int>::iterator vit = v.begin();
    while (vit != v.end())
    {
        std::cout << *vit << std::endl;
        vit++;
    }

    std::cout << v.front() << " " << v.back() << std::endl;

    String s = "NguyenVu";
    s.insert(6, " Chiem Minh ");
    s += "0934359954";
    std::cout << s.c_str() << std::endl;

    String another_s = "Something wrong";
    s.swap(another_s);
    std::cout << s.c_str() << std::endl;

    return 0;
}