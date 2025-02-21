/**
https://leetcode.com/problems/reward-top-k-students/description/

You are given two string arrays positive_feedback and negative_feedback, containing the words denoting positive and negative feedback, respectively. Note that no word is both positive and negative.

Initially every student has 0 points. Each positive word in a feedback report increases the points of a student by 3, whereas each negative word decreases the points by 1.

You are given n feedback reports, represented by a 0-indexed string array report and a 0-indexed integer array student_id, where student_id[i] represents the ID of the student who has received the feedback report report[i]. The ID of each student is unique.

Given an integer k, return the top k students after ranking them in non-increasing order by their points. In case more than one student has the same points, the one with the lower ID ranks higher.

Example 1:

Input: positive_feedback = ["smart","brilliant","studious"], negative_feedback = ["not"], report = ["this student is studious","the student is smart"], student_id = [1,2], k = 2
Output: [1,2]
Explanation: 
Both the students have 1 positive feedback and 3 points but since student 1 has a lower ID he ranks higher.

Example 2:

Input: positive_feedback = ["smart","brilliant","studious"], negative_feedback = ["not"], report = ["this student is not studious","the student is smart"], student_id = [1,2], k = 2
Output: [2,1]
Explanation: 
- The student with ID 1 has 1 positive feedback and 1 negative feedback, so he has 3-1=2 points. 
- The student with ID 2 has 1 positive feedback, so he has 3 points. 
Since student 2 has more points, [2,1] is returned.

Constraints:

1 <= positive_feedback.length, negative_feedback.length <= 104
1 <= positive_feedback[i].length, negative_feedback[j].length <= 100
Both positive_feedback[i] and negative_feedback[j] consists of lowercase English letters.
No word is present in both positive_feedback and negative_feedback.
n == report.length == student_id.length
1 <= n <= 104
report[i] consists of lowercase English letters and spaces ' '.
There is a single space between consecutive words of report[i].
1 <= report[i].length <= 100
1 <= student_id[i] <= 109
All the values of student_id[i] are unique.
1 <= k <= n
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    vector<int> topStudents(vector<string>& positive_feedback, vector<string>& negative_feedback, vector<string>& report, vector<int>& student_id, int k)
    {
        std::vector<int> res;

        std::unordered_set<std::string> set_pos(positive_feedback.begin(), positive_feedback.end());
        std::unordered_set<std::string> set_neg(negative_feedback.begin(), negative_feedback.end());

        std::unordered_map<int, int> student_score;
        for (int i = 0; i < report.size(); i++)
        {
            if (student_score.find(student_id[i]) == student_score.end())
            {
                student_score[student_id[i]] = 0;
            }

            std::stringstream ss(report[i]);
            std::string word;
            while (ss >> word)
            {
                if (set_pos.find(word) != set_pos.end())
                {
                    student_score[student_id[i]] += 3;
                }
                else if (set_neg.find(word) != set_neg.end())
                {
                    student_score[student_id[i]] -= 1;
                }
            }
        }

        std::vector<std::pair<int, int>> sorted;
        for (const auto& p : student_score)
        {
            sorted.push_back({p.second, p.first});
        }

        std::sort(sorted.begin(), sorted.end(), [](const auto& s1, const auto& s2) {
            if (s1.first > s2.first)
                return true;
            if (s1.first < s2.first)
                return false;
            return s1.second < s2.second;
        });

        for (int i = 0; i < k; i++)
        {
            res.push_back(sorted[i].second);
        }
        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::string> pos = {"smart", "brilliant", "studious"};
    std::vector<std::string> neg = {"not"};
    std::vector<std::string> report = {"this student is studious", "the student is smart"};
    std::vector<int> students = {1, 2};
    int k = 2;
    std::vector<int> res = sol.topStudents(pos, neg, report, students, k);
    for (int id : res)
    {
        std::cout << id << " ";
    }
    std::cout << std::endl;
    return 0;
}