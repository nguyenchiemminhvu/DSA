#include <iostream>
#include "DSA/Array.h"

int main()
{
    Array<int, 5U> arr;
    for (int i = 0; i < 5; i++)
    {
        arr[i] = i + 1;
    }

    Array<int, 5U>::iterator it = arr.begin();
    while (it != arr.end())
    {
        std::cout << *it++ << std::endl;
    }

    return 0;
}