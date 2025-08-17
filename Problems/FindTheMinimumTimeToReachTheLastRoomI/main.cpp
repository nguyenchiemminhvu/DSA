// https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/description/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int dr[4] = {-1, 1, 0, 0}; // row movement: up, down
int dc[4] = {0, 0, -1, 1}; // col movement: left, right

#define ppi std::pair<int, std::pair<int, int>>
class Solution
{
public:
    int minTimeToReach(vector<vector<int>>& moveTime)
    {
        int m = moveTime.size();
        int n = moveTime[0].size();

        std::vector<std::vector<int>> dist(m, std::vector<int>(n, INT_MAX));
        dist[0][0] = 0;

        std::priority_queue<ppi, std::vector<ppi>, std::greater<ppi>> pq;
        pq.push({0, {0, 0}});

        while (!pq.empty())
        {
            ppi cur = pq.top();
            pq.pop();

            int r = cur.second.first;
            int c = cur.second.second;
            int time = cur.first;

            if (r == m - 1 && c == n - 1)
            {
                return time;
            }

            if (time > dist[r][c])
            {
                continue;
            }

            for (int i = 0; i < 4; i++)
            {
                int next_r = r + dr[i];
                int next_c = c + dc[i];
                if (next_r >= 0 && next_r < m && next_c >= 0 && next_c < n)
                {
                    int arrived_time = time;
                    if (arrived_time < moveTime[next_r][next_c])
                    {
                        arrived_time = moveTime[next_r][next_c];
                    }
                    arrived_time++;

                    if (arrived_time < dist[next_r][next_c])
                    {
                        dist[next_r][next_c] = arrived_time;
                        pq.push({arrived_time, {next_r, next_c}});
                    }
                }
            }
        }

        return INT_MAX;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> moveTime = {
        {0, 2, 4},
        {1, 3, 5},
        {2, 1, 0}
    };
    int result = sol.minTimeToReach(moveTime);
    cout << "Minimum time to reach the last room: " << result << endl;
    return 0;
}