/**
https://vjudge.net/contest/691168#problem/G

A school has to decide on its team for an international quiz. There are n students in the school. We can describe the students using an array a where ai is the smartness of the i-th (1≤i≤n) student.

There are m topics 1,2,3,…,m from which the quiz questions will be formed. The i-th student is considered proficient in a topic T if (ai modT)=0. Otherwise, he is a rookie in that topic.

We say that a team of students is collectively proficient in all the topics if for every topic there is a member of the team proficient in this topic.

Find a team that is collectively proficient in all the topics such that the maximum difference between the smartness of any two students in that team is minimized. Output this difference.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <climits>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int minSmartnessDifference(std::vector<int>& students, int num_topic)
    {
        std::vector<std::vector<int>> proficient(num_topic + 1);
        for (int smartness : students)
        {
            for (int d = 1; d <= num_topic && d * d <= smartness; d++)
            {
                if (smartness % d == 0)
                {
                    proficient[d].push_back(smartness);
                    if (smartness / d <= num_topic && smartness / d != d)
                    {
                        proficient[smartness / d].push_back(smartness);
                    }
                }
            }
        }

        std::set<int> collective_students;
        for (int d = 1; d <= num_topic; d++)
        {
            if (proficient[d].empty())
            {
                return -1;
            }

            collective_students.insert(proficient[d].begin(), proficient[d].end());
        }

        std::vector<int> sorted_students(collective_students.begin(), collective_students.end());
        std::unordered_map<int, int> topic_freq;
        int covered_topics = 0;
        int min_diff_smartness = INT_MAX;
        int left = 0;
        for (int right = 0; right < sorted_students.size(); right++)
        {
            int cur_smartness = sorted_students[right];

            for (int d = 1; d <= num_topic && d * d <= cur_smartness; d++)
            {
                if (cur_smartness % d == 0)
                {
                    if (topic_freq.find(d) == topic_freq.end())
                    {
                        covered_topics++;
                    }
                    topic_freq[d]++;

                    if (cur_smartness / d <= num_topic && cur_smartness / d != d)
                    {
                        if (topic_freq.find(cur_smartness / d) == topic_freq.end())
                        {
                            covered_topics++;
                        }
                        topic_freq[cur_smartness / d]++;
                    }
                }
            }

            while (covered_topics == num_topic)
            {
                min_diff_smartness = std::min(min_diff_smartness, sorted_students[right] - sorted_students[left]);

                int left_smartness = sorted_students[left];
                for (int d = 1; d <= num_topic && d * d <= left_smartness; d++)
                {
                    if (left_smartness % d == 0)
                    {
                        topic_freq[d]--;
                        if (topic_freq[d] <= 0)
                        {
                            topic_freq.erase(d);
                            covered_topics--;
                        }

                        if (left_smartness / d <= num_topic && left_smartness / d != d)
                        {
                            topic_freq[left_smartness / d]--;
                            if (topic_freq[left_smartness / d] <= 0)
                            {
                                topic_freq.erase(left_smartness / d);
                                covered_topics--;
                            }
                        }
                    }
                }

                left++;
            }
        }

        return min_diff_smartness;
    }
};

int main()
{
    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++)
    {
        int n, m;
        std::cin >> n >> m;

        std::vector<int> students(n);
        for (int i = 0; i < n; i++)
        {
            std::cin >> students[i];
        }

        Solution sol;
        std::cout << sol.minSmartnessDifference(students, m) << std::endl;
    }

    return 0;
}