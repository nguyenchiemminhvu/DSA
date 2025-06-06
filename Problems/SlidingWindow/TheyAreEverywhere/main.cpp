/**
https://vjudge.net/contest/691168#problem/F
https://usaco.guide/problems/cf-they-are-everywhere/solution

Sergei B., the young coach of Pokemons, has found the big house which consists of n flats ordered in a row from left to right. It is possible to enter each flat from the street. It is possible to go out from each flat. Also, each flat is connected with the flat to the left and the flat to the right. Flat number 1 is only connected with the flat number 2 and the flat number n is only connected with the flat number n - 1.

There is exactly one Pokemon of some type in each of these flats. Sergei B. asked residents of the house to let him enter their flats in order to catch Pokemons. After consulting the residents of the house decided to let Sergei B. enter one flat from the street, visit several flats and then go out from some flat. But they won't let him visit the same flat more than once.

Sergei B. was very pleased, and now he wants to visit as few flats as possible in order to collect Pokemons of all types that appear in this house. Your task is to help him and determine this minimum number of flats he has to visit.
 */

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

int main()
{
    int n;
    std::cin >> n;

    std::string input;
    std::cin >> input;

    std::unordered_set<char> us(input.begin(), input.end());
    std::unordered_map<char, int> freq;

    int min_length = input.length();
    int left = 0;
    for (int right = 0; right < n; right++)
    {
        freq[input[right]]++;
        while (freq.size() == us.size())
        {
            min_length = std::min(min_length, right - left + 1);

            freq[input[left]]--;
            if (freq[input[left]] <= 0)
            {
                freq.erase(input[left]);
            }
            left++;
        }
    }

    std::cout << min_length << std::endl;

    return 0;
}