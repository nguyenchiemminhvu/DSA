/**
https://vjudge.net/contest/690986#problem/H
https://usaco.org/index.php?page=viewproblem2&cpid=857

Farmer John has two milking barns, each of which has a large milk tank as well as a storage closet containing 10 buckets of various sizes. He likes to carry milk back and forth between the two barns as a means of exercise.
On Monday, Farmer John measures exactly 1000 gallons of milk in the tank of the first barn, and exactly 1000 gallons of milk in the tank of the second barn.

On Tuesday, he takes a bucket from the first barn, fills it, and carries the milk to the second barn, where he pours it into the storage tank. He leaves the bucket at the second barn.

On Wednesday, he takes a bucket from the second barn (possibly the one he left on Tuesday), fills it, and carries the milk to the first barn, where he pours it into the storage tank. He leaves the bucket at the first barn.

On Thursday, he takes a bucket from the first barn (possibly the one he left on Wednesday), fills it, and carries the milk to the second barn, where he pours it into the tank. He leaves the bucket at the second barn.

On Friday, he takes a bucket from the second barn (possibly the one he left on Tuesday or Thursday), fills it, and carries the milk to the first barn, where he pours it into the tank. He leaves the bucket at the first barn.

Farmer John then measures the milk in the tank of the first barn. How many possible different readings could he see?
 */

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    int backAndForth(std::vector<int>& left_buckets, std::vector<int>& right_buckets)
    {
        std::unordered_set<int> possible_readings;
        DFS(left_buckets, right_buckets, 0, 1000, possible_readings);
        return possible_readings.size();
    }
private:
    void DFS(std::vector<int>& left_buckets, std::vector<int>& right_buckets, int day, int gallon, std::unordered_set<int>& res)
    {
        if (day > 3)
        {
            res.insert(gallon);
            return;
        }

        std::vector<int>& from = (day == 0 || day == 2) ? left_buckets : right_buckets;
        std::vector<int>& to = (day == 0 || day == 2) ? right_buckets : left_buckets;

        for (int i = 0; i < from.size(); i++)
        {
            int bucket = from[i];

            from.erase(from.begin() + i);
            to.push_back(bucket);

            if (day == 0 || day == 2)
            {
                DFS(left_buckets, right_buckets, day + 1, gallon - bucket, res);
            }
            else
            {
                DFS(left_buckets, right_buckets, day + 1, gallon + bucket, res);
            }

            from.insert(from.begin() + i, bucket);
            to.pop_back();
        }
    }
};

int main()
{
    freopen("backforth.in", "r", stdin);
    freopen("backforth.out", "w", stdout);

    std::vector<int> left_buckets(10);
    std::vector<int> right_buckets(10);
    for (int i = 0; i < 10; i++)
    {
        std::cin >> left_buckets[i];
    }

    for (int i = 0; i < 10; i++)
    {
        std::cin >> right_buckets[i];
    }

    Solution solution;
    cout << solution.backAndForth(left_buckets, right_buckets) << endl;

    return 0;
}