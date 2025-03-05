/**
https://vjudge.net/contest/690993#problem/I
https://usaco.guide/problems/cf-running-miles/solution

There is a street with n sights, with sight number i being i miles from the beginning of the street. Sight number i has beauty bi. You want to start your morning jog l miles and end it r miles from the beginning of the street. By the time you run, you will see sights you run by (including sights at l and r miles from the start). You are interested in the 3 most beautiful sights along your jog, but every mile you run, you get more and more tired.

So choose l and r, such that there are at least 3 sights you run by, and the sum of beauties of the 3 most beautiful sights minus the distance in miles you have to run is maximized.
 */

#include <iostream>
#include <vector>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

/**
B[left] + B[mid] + B[right] - (right - left)
B[left] + B[mid] + B[right] - (right - mid + mid - left)
B[left] + B[mid] + B[right] - (right - mid) - (mid - left)
B[left] - (mid - left) + B[mid] + B[right] - (right - mid)

For each index mid, find max of:
(1) B[left] - (mid - left)
and
(2) B[right] - (right - mid)

(1) prefix_left[n]
prefix_left[0] = B[0] - 1; because when mid start at 1, max of B[left] - (mid - left) is B[0] - (1 - 0)
prefix_left[1] = max(prefix_left[0] - 1, B[0] - 1);
prefix_left[2] = max(prefix_left[1] - 1, B[1] - 1);
...
prefix_left[i] = max(prefix_left[i - 1] - 1, B[i - 1] - 1);

(2) suffix_right[n]
suffix_right[n - 1] = B[n - 1] - 1; because when mid start at n - 2, max of B[right] - (right - mid) is B[n - 1] - (n - 1 - n - 2)
...
suffix_right[i] = max(B[i + 1] - 1, B[i + 1] - 1);

=> for each index mid from 1 to (n - 2)
res = max(res, prefix_left[mid_index] + B[mid_index] + suffix_right[mid_index])
 */
class Solution
{
public:
    int maxThreeBeautifulPlace(int n, const std::vector<int>& beauty)
    {
        std::vector<int> prefix_left(n, 0);
        std::vector<int> suffix_right(n, 0);

        prefix_left[0] = beauty[0] - 1;
        suffix_right[n - 1] = beauty[n - 1] - 1;

        for (int i = 1; i < n; i++)
        {
            prefix_left[i] = std::max(prefix_left[i - 1] - 1, beauty[i - 1] - 1);
        }

        for (int i = n - 2; i >= 0; i--)
        {
            suffix_right[i] = std::max(suffix_right[i + 1] - 1, beauty[i + 1] - 1);
        }

        int res = 0;
        for (int i = 1; i < n - 1; i++)
        {
            res = std::max(res, prefix_left[i] + beauty[i] + suffix_right[i]);
        }
        return res;
    }
};

int main()
{
    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++)
    {
        int n;
        std::cin >> n;

        std::vector<int> beauty(n);
        for (int i = 0; i < n; i++)
        {
            std::cin >> beauty[i];
        }

        Solution sol;
        std::cout << sol.maxThreeBeautifulPlace(n, beauty) << std::endl;
    }

    return 0;
}