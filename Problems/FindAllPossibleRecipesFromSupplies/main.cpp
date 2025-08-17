/**
https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/description/

You have information about n different recipes. You are given a string array recipes and a 2D string array ingredients. The ith recipe has the name recipes[i], and you can create it if you have all the needed ingredients from ingredients[i]. A recipe can also be an ingredient for other recipes, i.e., ingredients[i] may contain a string that is in recipes.

You are also given a string array supplies containing all the ingredients that you initially have, and you have an infinite supply of all of them.

Return a list of all the recipes that you can create. You may return the answer in any order.

Note that two recipes may contain each other in their ingredients.

Example 1:

Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
Output: ["bread"]
Explanation:
We can create "bread" since we have the ingredients "yeast" and "flour".

Example 2:

Input: recipes = ["bread","sandwich"], ingredients = [["yeast","flour"],["bread","meat"]], supplies = ["yeast","flour","meat"]
Output: ["bread","sandwich"]
Explanation:
We can create "bread" since we have the ingredients "yeast" and "flour".
We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".

Example 3:

Input: recipes = ["bread","sandwich","burger"], ingredients = [["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]], supplies = ["yeast","flour","meat"]
Output: ["bread","sandwich","burger"]
Explanation:
We can create "bread" since we have the ingredients "yeast" and "flour".
We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".
We can create "burger" since we have the ingredient "meat" and can create the ingredients "bread" and "sandwich".

Constraints:

n == recipes.length == ingredients.length
1 <= n <= 100
1 <= ingredients[i].length, supplies.length <= 100
1 <= recipes[i].length, ingredients[i][j].length, supplies[k].length <= 10
recipes[i], ingredients[i][j], and supplies[k] consist only of lowercase English letters.
All the values of recipes and supplies combined are unique.
Each ingredients[i] does not contain any duplicate values.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies)
    {
        std::vector<std::string> res;
        std::unordered_set<std::string> available_items(supplies.begin(), supplies.end());
        std::unordered_map<std::string, std::vector<std::string>> graph;
        std::unordered_map<std::string, int> in_degree;
        std::queue<std::string> Q;

        for (const std::string& recipe : recipes)
        {
            in_degree[recipe] = 0;
        }

        for (int i = 0; i < recipes.size(); i++)
        {
            std::string to = recipes[i];
            for (const std::string& from : ingredients[i])
            {
                graph[from].push_back(to);
                in_degree[to]++;
            }
        }

        for (const std::string& supply : supplies)
        {
            Q.push(supply);
        }

        while (!Q.empty())
        {
            std::string cur_ingredient = Q.front();
            Q.pop();

            if (available_items.find(cur_ingredient) == available_items.end())
            {
                continue;
            }

            for (const std::string& next : graph[cur_ingredient])
            {
                if (in_degree.find(next) != in_degree.end())
                {
                    in_degree[next]--;
                    if (in_degree[next] == 0)
                    {
                        res.push_back(next);
                        available_items.insert(next);
                        Q.push(next);
                    }
                }
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    vector<string> recipes = {"bread", "sandwich", "burger"};
    vector<vector<string>> ingredients = {{"yeast", "flour"}, {"bread", "meat"}, {"sandwich", "meat", "bread"}};
    vector<string> supplies = {"yeast", "flour", "meat"};

    vector<string> result = sol.findAllRecipes(recipes, ingredients, supplies);

    cout << "Possible recipes: ";
    for (const string& recipe : result)
    {
        cout << recipe << " ";
    }
    cout << endl;
    return 0;
}