/**
https://leetcode.com/problems/online-election/

You are given two integer arrays persons and times. In an election, the ith vote was cast for persons[i] at time times[i].

For each query at a time t, find the person that was leading the election at time t. Votes cast at time t will count towards our query. In the case of a tie, the most recent vote (among tied candidates) wins.

Implement the TopVotedCandidate class:

TopVotedCandidate(int[] persons, int[] times) Initializes the object with the persons and times arrays.
int q(int t) Returns the number of the person that was leading the election at time t according to the mentioned rules.

Example 1:

Input
["TopVotedCandidate", "q", "q", "q", "q", "q", "q"]
[[[0, 1, 1, 0, 0, 1, 0], [0, 5, 10, 15, 20, 25, 30]], [3], [12], [25], [15], [24], [8]]
Output
[null, 0, 1, 1, 0, 0, 1]

Explanation
TopVotedCandidate topVotedCandidate = new TopVotedCandidate([0, 1, 1, 0, 0, 1, 0], [0, 5, 10, 15, 20, 25, 30]);
topVotedCandidate.q(3); // return 0, At time 3, the votes are [0], and 0 is leading.
topVotedCandidate.q(12); // return 1, At time 12, the votes are [0,1,1], and 1 is leading.
topVotedCandidate.q(25); // return 1, At time 25, the votes are [0,1,1,0,0,1], and 1 is leading (as ties go to the most recent vote.)
topVotedCandidate.q(15); // return 0
topVotedCandidate.q(24); // return 0
topVotedCandidate.q(8); // return 1

Constraints:

1 <= persons.length <= 5000
times.length == persons.length
0 <= persons[i] < persons.length
0 <= times[i] <= 109
times is sorted in a strictly increasing order.
times[0] <= t <= 109
At most 104 calls will be made to q.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
#include <unordered_map>

using namespace std;

class TopVotedCandidate
{
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times)
    {
        this->times = std::move(times);
        int cur_elected = -1;
        int max_election = 0;
        timeline.resize(persons.size());
        std::fill(timeline.begin(), timeline.end(), 0);

        std::unordered_map<int, int> freq;
        for (int i = 0; i < persons.size(); i++)
        {
            freq[persons[i]]++;
            if (freq[persons[i]] >= max_election)
            {
                cur_elected = persons[i];
                max_election = freq[persons[i]];
            }

            timeline[i] = cur_elected;
        }
    }
    
    int q(int t)
    {
        int idx = std::distance(times.begin(), std::upper_bound(times.begin(), times.end(), t));
        return timeline[idx - 1];
    }

private:
    std::vector<int> times;
    std::vector<int> timeline;
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */

int main()
{
    vector<int> persons = {0, 1, 1, 0, 0, 1, 0};
    vector<int> times = {0, 5, 10, 15, 20, 25, 30};
    TopVotedCandidate topVotedCandidate(persons, times);
    
    vector<int> queries = {3, 12, 25, 15, 24, 8};
    for (int t : queries)
    {
        cout << topVotedCandidate.q(t) << endl;
    }
    return 0;
}