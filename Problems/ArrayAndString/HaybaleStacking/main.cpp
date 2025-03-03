/**
https://vjudge.net/contest/690993#problem/F
https://usaco.org/index.php?page=viewproblem2&cpid=104

Feeling sorry for all the mischief she has caused around the farm recently, Bessie has agreed to help Farmer John stack up an incoming shipment of hay bales.
FJ then gives her a sequence of K instructions (1 <= K <= 25,000), each of the form "A B", meaning that Bessie should add one new haybale to the top of each stack in the range A..B. For example, if Bessie is told "10 13", then she should add a haybale to each of the stacks 10, 11, 12, and 13.

After Bessie finishes stacking haybales according to his instructions, FJ would like to know the median height of his N stacks -- that is, the height of the middle stack if the stacks were to be arranged in sorted order (conveniently, N is odd, so this stack is unique). Please help Bessie determine the answer to FJ's question.
 */

#include <iostream>
#include <vector>
#include <algorithm>

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
    std::vector<int> stacks(n, 0);
    for (int i = 0; i < k; i++)
    {
        int left, right;
        std::cin >> left >> right;

        stacks[left - 1]++;
        if (right < n)
        {
            stacks[right]--;
        }
    }

    for (int i = 1; i < n; i++)
    {
        stacks[i] += stacks[i - 1];
    }
    
    std::sort(stacks.begin(), stacks.end());
    std::cout << stacks[n / 2] << std::endl;

    return 0;
}