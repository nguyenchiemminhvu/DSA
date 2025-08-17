/**
https://vjudge.net/contest/690986#problem/A
https://usaco.org/index.php?page=viewproblem2&cpid=1228

Bessie the cow is hiding somewhere along the number line. Each of Farmer John's N other cows (1≤N≤1000) have a piece of information to share: the i-th cow either says that Bessie is hiding at some location less than or equal to pi, or that Bessie is hiding at some location greater than or equal to pi (0≤pi≤10^9).

Unfortunately, it is possible that no hiding location is consistent with the answers of all of the cows, meaning that not all of the cows are telling the truth. Count the minimum number of cows that must be lying.

INPUT FORMAT (input arrives from the terminal / stdin):
The first line contains N.
The next N lines each contain either L or G, followed by an integer pi. L means that the i-th cow says that Bessie's hiding location is less than or equal to pi , and G means that i-th cow says that Bessie's hiding location is greater than or equal to pi
OUTPUT FORMAT (print output to the terminal / stdout):
The minimum number of cows that must be lying.
 */

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution
{
public:
    int countingLiars(const std::vector<std::pair<char, int>>& cows)
    {
        std::vector<int> points;
        for (const std::pair<char, int>& cow : cows)
        {
            points.push_back(cow.second);
        }

        int min_liars = cows.size();

        for (int p : points)
        {
            int liars = 0;
            for (const std::pair<char, int>& cow : cows)
            {
                if (cow.first == 'L' && cow.second < p)
                {
                    liars++;
                }
                else if (cow.first == 'G' && cow.second > p)
                {
                    liars++;
                }
            }
            min_liars = std::min(min_liars, liars);
        }

        return min_liars;
    }
};

int main()
{
    int n;
    std::cin >> n;

    std::vector<std::pair<char, int>> cows(n);
    for (int i = 0; i < n; i++)
    {
        char c;
        int pi;
        std::cin >> c >> pi;

        cows[i] = {c, pi};
    }

    Solution sol;
    std::cout << sol.countingLiars(cows) << std::endl;

    return 0;
}