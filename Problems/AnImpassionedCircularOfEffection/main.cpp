/**
https://vjudge.net/contest/691168#problem/H
https://usaco.guide/problems/cf-garland/solution

For instance, let's say the garland is represented by "kooomo", and Brother Koyomi's favourite colour is "o". Among all subsegments containing pieces of "o" only, "ooo" is the longest, with a length of 3. Thus the Koyomity of this garland equals 3.

But problem arises as Nadeko is unsure about Brother Koyomi's favourite colour, and has swaying ideas on the amount of work to do. She has q plans on this, each of which can be expressed as a pair of an integer mi and a lowercase letter ci, meanings of which are explained above. You are to find out the maximum Koyomity achievable after repainting the garland according to each plan.
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
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    int num_plans;
    std::cin >> num_plans;
    for (int i = 0; i < num_plans; i++)
    {
        int count;
        char target_color;
        std::cin >> count >> target_color;

        int max_length = count;
        
        int left = 0;
        int right = 0;
        int used_help = 0;
        while (right < n)
        {
            if (s[right] != target_color)
            {
                used_help++;
            }

            while (used_help > count)
            {
                if (s[left] != target_color)
                {
                    used_help--;
                }
                left++;
            }

            max_length = std::max(max_length, right - left + 1);
            right++;
        }

        std::cout << max_length << std::endl;
    }

    return 0;
}