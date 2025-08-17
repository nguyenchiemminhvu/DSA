#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);

    int n;
    cin >> n;
    unordered_map<string, set<string>> rules;
    for (int i = 0; i < n; i++)
    {
        string temp, cow1, cow2;
        cin >> cow1 >> temp >> temp >> temp >> temp >> cow2;
        rules[cow1].insert(cow2);
        rules[cow2].insert(cow1); // Ensure bidirectional constraints
    }

    vector<string> cows = {"Bessie", "Buttercup", "Belinda", "Beatrice", "Bella", "Blue", "Betsy", "Sue"};
    sort(cows.begin(), cows.end());
    
    do
    {
        bool valid = true;
        for (int i = 0; i < cows.size(); i++)
        {
            for (const string &neighbor : rules[cows[i]])
            {
                if ((i > 0 && cows[i - 1] == neighbor)
                 || (i < cows.size() - 1 && cows[i + 1] == neighbor))
                {
                    continue;
                }
                valid = false;
                break;
            }
            if (!valid) break;
        }

        if (valid)
        {
            for (const string &cow : cows)
            {
                cout << cow << endl;
            }
            return 0;
        }
    } while (next_permutation(cows.begin(), cows.end()));

    return 0;
}
