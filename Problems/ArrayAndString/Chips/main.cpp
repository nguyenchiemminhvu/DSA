/**
https://vjudge.net/contest/691170#problem/I

There are n chips arranged in a circle, numbered from 1 to n.

Initially each chip has black or white color. Then k iterations occur. During each iteration the chips change their colors according to the following rules. For each chip i, three chips are considered: chip i itself and two its neighbours. If the number of white chips among these three is greater than the number of black chips among these three chips, then the chip i becomes white. Otherwise, the chip i becomes black.

Note that for each i from 2 to (n−1) two neighbouring chips have numbers (i−1) and (i+1). The neighbours for the chip i=1 are n and 2. The neighbours of i=n are (n−1) and 1.

The following picture describes one iteration with n=6. The chips 1, 3 and 4 are initially black, and the chips 2, 5 and 6 are white. After the iteration 2, 3 and 4 become black, and 1, 5 and 6 become white.
Your task is to determine the color of each chip after k iterations.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

int main()
{
    int n, k;
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;

    std::string next_state(n, 'B');
    int count_iter = 0;
    int cycle_start_idx = -1;
    std::unordered_map<std::string, int> cycle_detection;
    std::unordered_map<int, std::unordered_map<std::string, int>::const_iterator> indexing;
    while (cycle_detection.find(s) == cycle_detection.end())
    {
        auto rc = cycle_detection.insert({s, count_iter});
        indexing[count_iter] = rc.first;
        count_iter++;

        // build next state
        for (int i = 0; i < n; i++)
        {
            int prev_idx = ((i - 1) + n) % n;
            int next_idx = (i + 1) % n;
            next_state[i] = (s[prev_idx] == s[next_idx] ? s[prev_idx] : s[i]);
        }
        s.swap(next_state);
    }

    cycle_start_idx = cycle_detection[s];

    if (k < cycle_start_idx)
    {
        std::cout << indexing[k]->first << std::endl;
    }
    else
    {
        int cycle_length = count_iter - cycle_start_idx;
        int remaining_iterations = (k - cycle_start_idx) % cycle_length;
        std::cout << indexing[cycle_start_idx + remaining_iterations]->first << std::endl;
    }

    return 0;
}