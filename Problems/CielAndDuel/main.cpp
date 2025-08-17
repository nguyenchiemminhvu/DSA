/**
https://vjudge.net/contest/690988#problem/H
https://forum.usaco.guide/t/ciel-and-duel/5352

Fox Ciel is playing a card game with her friend Jiro.

Jiro has n cards, each one has two attributes: position (Attack or Defense) and strength. Fox Ciel has m cards, each one has these two attributes too. It's known that position of all Ciel's cards is Attack.

Now is Ciel's battle phase, Ciel can do the following operation many times:

Choose one of her cards X. This card mustn't be chosen before.
If Jiro has no alive cards at that moment, he gets the damage equal to (X's strength). Otherwise, Ciel needs to choose one Jiro's alive card Y, then:
If Y's position is Attack, then (X's strength)  ≥  (Y's strength) must hold. After this attack, card Y dies, and Jiro gets the damage equal to (X's strength) - (Y's strength).
If Y's position is Defense, then (X's strength)  >  (Y's strength) must hold. After this attack, card Y dies, but Jiro gets no damage.
Ciel can end her battle phase at any moment (so, she can use not all her cards). Help the Fox to calculate the maximal sum of damage Jiro can get.
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    long long maxDamageToJiro(std::vector<long long>& ciel_atk_cards, std::vector<long long>& jiro_atk_cards, std::vector<long long>& jiro_def_cards)
    {
        std::sort(jiro_atk_cards.begin(), jiro_atk_cards.end());
        std::sort(jiro_def_cards.begin(), jiro_def_cards.end());
        return std::max(defeat_jiro_atk_cards_only(ciel_atk_cards, jiro_atk_cards), defeat_all_jiro_cards(ciel_atk_cards, jiro_atk_cards, jiro_def_cards));
    }
private:
    long long defeat_jiro_atk_cards_only(const std::vector<long long>& ciel_atk_cards, const std::vector<long long>& jiro_atk_cards)
    {
        long long res = 0LL;
        std::multiset<long long> powers(ciel_atk_cards.begin(), ciel_atk_cards.end());
        for (int i = 0; i < jiro_atk_cards.size(); i++)
        {
            if (powers.empty())
            {
                return res;
            }

            auto it = std::prev(powers.end()); // pointer to strongest card
            if (*it > jiro_atk_cards[i])
            {
                res += *it - jiro_atk_cards[i];
            }
            else
            {
                break;
            }
            powers.erase(it);
        }
        return res;
    }

    long long defeat_all_jiro_cards(const std::vector<long long>& ciel_atk_cards, const std::vector<long long>& jiro_atk_cards, const std::vector<long long>& jiro_def_cards)
    {
        std::multiset<long long> powers(ciel_atk_cards.begin(), ciel_atk_cards.end());
        for (int i = 0; i < jiro_def_cards.size(); i++)
        {
            if (powers.empty())
            {
                return 0LL;
            }

            auto it = powers.upper_bound(jiro_def_cards[i]);
            if (it == powers.end())
            {
                return 0LL;
            }
            powers.erase(it);
        }

        long long res = 0LL;
        for (int i = 0; i < jiro_atk_cards.size(); i++)
        {
            auto it = powers.lower_bound(jiro_atk_cards[i]);
            if (it == powers.end())
            {
                return 0LL;
            }

            res += *it - jiro_atk_cards[i];
            powers.erase(it);
        }

        for (int power : powers)
        {
            res += power;
        }

        return res;
    }
};

int main()
{
    long long n, m;
    std::cin >> n >> m;

    std::vector<long long> ciel_atk_cards;
    std::vector<long long> jiro_atk_cards;
    std::vector<long long> jiro_def_cards;

    for (long long i = 0; i < n; i++)
    {
        std::string pos;
        long long val;
        std::cin >> pos >> val;
        if (pos == "ATK")
        {
            jiro_atk_cards.push_back(val);
        }
        else
        {
            jiro_def_cards.push_back(val);
        }
    }

    for (long long i = 0; i < m; i++)
    {
        long long val;
        std::cin >> val;
        ciel_atk_cards.push_back(val);
    }

    Solution sol;
    std::cout << sol.maxDamageToJiro(ciel_atk_cards, jiro_atk_cards, jiro_def_cards) << std::endl;

    return 0;
}