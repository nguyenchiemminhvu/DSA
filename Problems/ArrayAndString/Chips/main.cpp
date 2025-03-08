/**
https://vjudge.net/contest/691170#problem/I
https://codeforces.com/problemset/problem/1244/F

There are n chips arranged in a circle, numbered from 1 to n.

Initially each chip has black or white color. Then k iterations occur. During each iteration the chips change their colors according to the following rules. For each chip i, three chips are considered: chip i itself and two its neighbours. If the number of white chips among these three is greater than the number of black chips among these three chips, then the chip i becomes white. Otherwise, the chip i becomes black.

Note that for each i from 2 to (n−1) two neighbouring chips have numbers (i−1) and (i+1). The neighbours for the chip i=1 are n and 2. The neighbours of i=n are (n−1) and 1.

The following picture describes one iteration with n=6. The chips 1, 3 and 4 are initially black, and the chips 2, 5 and 6 are white. After the iteration 2, 3 and 4 become black, and 1, 5 and 6 become white.
Your task is to determine the color of each chip after k iterations.
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Solution
{
public:
    std::string simulateIterations(std::string& chip_colors, int n, int total_iterations)
    {
        std::vector<bool> stable(n, false);
        std::queue<std::pair<int, bool> > q_process; // <index, is_right>

        // iterate on the segments of stable chips, find left and right boundary of each segment
        for (int left = 0; left < n; left++)
        {
            int right = left;
            while (right + 1 < n && chip_colors[right + 1] == chip_colors[right])
            {
                right++;
            }

            if (right - left + 1 >= 2)
            {
                for (int i = left; i <= right; i++)
                {
                    stable[i] = true;
                }

                q_process.push({left, false});
                q_process.push({right, true});
                left = right;
            }
        }

        if (!stable[0] && !stable[n - 1] && chip_colors[0] == chip_colors[n - 1])
        {
            stable[0] = stable[n - 1] = true;
            q_process.push({n - 1, false});
            q_process.push({0, true});
        }

        bool flip = false;
        std::queue<std::pair<int, bool> > q_temp;
        for (int iter = 0; iter < total_iterations; iter++, flip = !flip)
        {
            if (q_process.empty())
            {
                break;
            }

            while (!q_process.empty())
            {
                std::pair<int, bool> cur_stable = q_process.front();
                q_process.pop();

                if (!cur_stable.second) // not the right side
                {
                    q_process.push(cur_stable);
                    continue;
                }

                std::pair<int, bool> right_bound = cur_stable;
                std::pair<int, bool> left_bound = q_process.front();
                q_process.pop();

                int left_stable = left_bound.first;
                int next_left = get_left_idx(n, left_stable);
                int next_next_left = get_left_idx(n, next_left);
                int right_stable = right_bound.first;
                int next_right = get_right_idx(n, right_stable);

                if (next_left != right_stable && next_next_left != right_stable)
                {
                    chip_colors[next_right] = chip_colors[right_stable];
                    q_temp.push({next_right, true});
                    stable[next_right] = true;

                    chip_colors[next_left] = chip_colors[left_stable];
                    q_temp.push({next_left, false});
                    stable[next_left] = true;
                }
                else if (next_next_left == right_stable)
                {
                    int mid_unstable = next_left;
                    stable[mid_unstable] = true;
                    if (chip_colors[left_stable] == chip_colors[right_stable])
                    {
                        chip_colors[mid_unstable] = chip_colors[left_stable];
                    }
                    else if (flip)
                    {
                        chip_colors[mid_unstable] = (chip_colors[mid_unstable] == 'B' ? 'W' : 'B');
                    }
                }
            }

            std::swap(q_process, q_temp);
        }

        if (flip)
        {
            for (int i = 0; i < n; i++)
            {
                if (!stable[i])
                {
                    chip_colors[i] = (chip_colors[i] == 'B' ? 'W' : 'B');
                }
            }
        }

        return chip_colors;
    }
private:
    int get_left_idx(int n, int idx)
    {
        return ((idx - 1) + n) % n;
    }

    int get_right_idx(int n, int idx)
    {
        return (idx + 1) % n;
    }
};

int main()
{
    int n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;

    Solution sol;
    std::string res = sol.simulateIterations(s, n, k);
    std::cout << res << std::endl;

    return 0;
}