#include <iostream>
#include "DSA/Array.h"

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

    return 0;
}