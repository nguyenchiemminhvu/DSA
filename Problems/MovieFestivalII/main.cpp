/**
https://vjudge.net/contest/690988#problem/C
https://usaco.guide/problems/cses-1632-movie-festival-ii/solution

In a movie festival, n movies will be shown. Syrjälä's movie club consists of k members, who will be all attending the festival.

You know the starting and ending time of each movie. What is the maximum total number of movies the club members can watch entirely if they act optimally?
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int maximumTotalOfMovies(std::vector<std::pair<int, int>>& movies, int k)
    {
        std::sort(movies.begin(), movies.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            if (a.second < b.second)
                return true;
            if (a.second > b.second)
                return false;
            return a.first < b.first;
        });

        int res = 0;
        std::multiset<int> end_times;
        for (int i = 0; i < movies.size(); i++)
        {
            auto it = end_times.upper_bound(movies[i].first);
            if (it != end_times.begin())
            {
                --it;
                end_times.erase(it);
                end_times.insert(movies[i].second);
                res++;
            }
            else if (end_times.size() < k)
            {
                res++;
                end_times.insert(movies[i].second);
            }
        }

        return res;
    }
};

int main()
{
    int n, k;
    std::cin >> n >> k;

    std::vector<std::pair<int, int>> movies(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> movies[i].first >> movies[i].second;
    }

    Solution sol;
    std::cout << sol.maximumTotalOfMovies(movies, k) << std::endl;

    return 0;
}