// https://leetcode.com/problems/range-product-queries-of-powers

#include <iostream>
#include <vector>

using namespace std;

#define MOD 1000000007
class Solution
{
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries)
    {
        std::vector<int> powers;
        build_powers(powers, n);

        std::vector<int> res;
        for (const std::vector<int>& query : queries)
        {
            long long val = 1;
            for (int i = query[0]; i <= query[1]; i++)
            {
                val = ((val % MOD) * (powers[i] % MOD)) % MOD;
            }
            res.push_back(val);
        }
        return res;
    }
private:
    void build_powers(std::vector<int>& powers, int n)
    {
        int bit = 0;
        while (n)
        {
            if ((n & 1) > 0)
            {
                powers.push_back((1 << bit));
            }
            bit++;
            n >>= 1;
        }
    }
};

int main()
{
    Solution sol;
    int n = 5;
    vector<vector<int>> queries = {{0, 0}, {1, 1}, {0, 1}, {2, 3}};
    vector<int> result = sol.productQueries(n, queries);
    for (int res : result)
    {
        cout << res << " ";
    }
    return 0;
}