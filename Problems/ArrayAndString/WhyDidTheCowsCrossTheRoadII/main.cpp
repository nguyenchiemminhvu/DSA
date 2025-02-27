/**
https://vjudge.net/contest/690986#problem/E
https://usaco.org/index.php?page=viewproblem2&cpid=712

The layout of Farmer John's farm is quite peculiar, with a large circular road running around the perimeter of the main field on which his cows graze during the day. Every morning, the cows cross this road on their way towards the field, and every evening they all cross again as they leave the field and return to the barn.
As we know, cows are creatures of habit, and they each cross the road the same way every day. Each cow crosses into the field at a different point from where she crosses out of the field, and all of these crossing points are distinct from each-other. Farmer John owns exactly 26 cows, which he has lazily named A through Z (he is not sure what he will do if he ever acquires a 27th cow...), so there are precisely 52 crossing points around the road. Farmer John records these crossing points concisely by scanning around the circle clockwise, writing down the name of the cow for each crossing point, ultimately forming a string with 52 characters in which each letter of the alphabet appears exactly twice. He does not record which crossing points are entry points and which are exit points.

Looking at his map of crossing points, Farmer John is curious how many times various pairs of cows might cross paths during the day. He calls a pair of cows (a,b) a "crossing" pair if cow a's path from entry to exit must cross cow b's path from entry to exit. Please help Farmer John count the total number of crossing pairs.

INPUT FORMAT (file circlecross.in):
The input consists of a single line containing a string of 52 upper-case characters. Each letter of the alphabet appears exactly twice.
OUTPUT FORMAT (file circlecross.out):
Please print the total number of crossing pairs.
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    int countCrossLines(const std::string& habit)
    {
        int count = 0;
        
        std::unordered_map<char, std::vector<int>> entry_points;
        for (int i = 0; i < habit.size(); i++)
        {
            entry_points[habit[i]].push_back(i);
        }

        for (char c = 'A'; c <= 'Z'; c++)
        {
            int left = entry_points[c][0];
            int right = entry_points[c][1];

            for (char c1 = 'A'; c1 <= 'Z'; c1++)
            {
                if (c1 == c)
                {
                    continue;
                }

                int left1 = entry_points[c1][0];
                int right1 = entry_points[c1][1];

                if (left < left1 && left1 < right && right < right1)
                {
                    count++;
                }
            }
        }

        return count;
    }
};

int main()
{
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);

    std::string s;
    std::cin >> s;

    Solution sol;
    std::cout << sol.countCrossLines(s) << std::endl;

    return 0;
}