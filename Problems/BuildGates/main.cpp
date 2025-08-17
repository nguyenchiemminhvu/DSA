/**
https://vjudge.net/contest/691177#problem/E
https://usaco.guide/problems/usaco-596-build-gates/solution

Farmer John decides to build a new fence around parts of his farm, but he keeps getting distracted and ends up building the fence into a much stranger shape than he intended!
Specifically, FJ starts at position (0,0) and takes N steps, each moving one unit of distance north, south, east, or west. Each step he takes, he lays a unit of fence behind him. For example, if his first step is to the north, he adds a segment of fence from (0,0) to (0,1). FJ might re-visit points multiple times and he may even lay the same segment of fence multiple times. His fence might even cross over itself if his path cuts through a run of fencing he has already built.

Needless to say, FJ is rather dismayed at the result after he completes the fence. In particular, he notices that it may be the case that he has now partitioned off some areas of the farm from others, so that one can no longer walk from one region to another without crossing a fence. FJ would like to add gates to his fences to fix this problem. A gate can be added to any unit-length segment of fence he has built, allowing passage between the two sides of this segment.

Please determine the minimum number of gates FJ needs to build so that every region of the farm is once again reachable from every other region.
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

const int NN = 4003;
const int MID_ROW = 2001;
const int MID_COL = 2001;
int max_r = MID_ROW;
int min_r = MID_ROW;
int max_c = MID_ROW;
int min_c = MID_ROW;
int N;
std::vector<std::vector<int>> grid(NN, std::vector<int>(NN, 0));

std::vector<int> dir_r = {-1, 1, 0, 0};
std::vector<int> dir_c = {0, 0, -1, 1};

void DFS(int r, int c)
{
    if (r < min_r || r > max_r || c < min_c || c > max_c || grid[r][c] != 0)
    {
        return;
    }

    grid[r][c] = 2;
    for (int i = 0; i < 4; i++)
    {
        DFS(r + dir_r[i], c + dir_c[i]);
    }
}

int main()
{
    freopen("gates.in", "r", stdin);
    freopen("gates.out", "w", stdout);

    std::cin >> N;
    std::string path;
    std::cin >> path;

    int r = MID_ROW;
    int c = MID_COL;
    std::unordered_map<char, std::pair<int, int>> moves{
        {'N', {-1, 0}},
        {'S', {1, 0}},
        {'E', {0, 1}},
        {'W', {0, -1}}
    };
    
    grid[r][c] = 1;
    for (int i = 0; i < N; i++)
    {
        char ch = path[i];
        grid[r + moves[ch].first][c + moves[ch].second] = 1;
        grid[r + 2 * moves[ch].first][c + 2 * moves[ch].second] = 1;
        r += 2 * moves[ch].first;
        c += 2 * moves[ch].second;

        max_r = std::max(max_r, r);
        min_r = std::min(min_r, r);
        max_c = std::max(max_c, c);
        min_c = std::min(min_c, c);
    }

    max_r++;
    min_r--;
    max_c++;
    min_c--;

    int count_region = 0;
    for (int i = min_r; i <= max_r; i++)
    {
        for (int j = min_c; j <= max_c; j++)
        {
            if (grid[i][j] == 0)
            {
                DFS(i, j);
                count_region++;
            }
        }
    }

    std::cout << count_region - 1 << std::endl;

    return 0;
}