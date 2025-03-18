/**
https://vjudge.net/contest/690993#problem/J
https://usaco.guide/problems/cf-1291D/user-solutions
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    std::string s;
    std::cin >> s;
    int n = s.length();

    std::vector<std::vector<int>> prefix(n + 1, std::vector<int>(26, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            prefix[i + 1][j] += prefix[i][j];
        }
        prefix[i + 1][s[i] - 'a']++;
    }

    int q;
    std::cin >> q;
    while (q)
    {
        q--;

        int left, right;
        std::cin >> left >> right;
        left--;
        right--;

        std::vector<int> freq(26, 0);
        for (int i = 0; i < 26; i++)
        {
            freq[i] = prefix[right + 1][i] - prefix[left][i];
        }

        int distinct = 0;
        for (int i = 0; i < 26; i++)
        {
            if (freq[i] > 0)
            {
                distinct++;
            }
        }

        if (left == right)
        {
            std::cout << "Yes" << std::endl;
        }
        else if (distinct > 2)
        {
            std::cout << "Yes" << std::endl;
        }
        else if (s[left] != s[right])
        {
            std::cout << "Yes" << std::endl;
        }
        else
        {
            std::cout << "No" << std::endl;
        }
    }

    return 0;
}