/**
https://leetcode.com/problems/display-table-of-food-orders-in-a-restaurant/description/

Given the array orders, which represents the orders that customers have done in a restaurant. More specifically orders[i]=[customerNamei,tableNumberi,foodItemi] where customerNamei is the name of the customer, tableNumberi is the table customer sit at, and foodItemi is the item customer orders.

Return the restaurant's “display table”. The “display table” is a table whose row entries denote how many of each food item each table ordered. The first column is the table number and the remaining columns correspond to each food item in alphabetical order. The first row should be a header whose first column is “Table”, followed by the names of the food items. Note that the customer names are not part of the table. Additionally, the rows should be sorted in numerically increasing order.

Example 1:

Input: orders = [["David","3","Ceviche"],["Corina","10","Beef Burrito"],["David","3","Fried Chicken"],["Carla","5","Water"],["Carla","5","Ceviche"],["Rous","3","Ceviche"]]
Output: [["Table","Beef Burrito","Ceviche","Fried Chicken","Water"],["3","0","2","1","0"],["5","0","1","0","1"],["10","1","0","0","0"]] 
Explanation:
The displaying table looks like:
Table,Beef Burrito,Ceviche,Fried Chicken,Water
3    ,0           ,2      ,1            ,0
5    ,0           ,1      ,0            ,1
10   ,1           ,0      ,0            ,0
For the table 3: David orders "Ceviche" and "Fried Chicken", and Rous orders "Ceviche".
For the table 5: Carla orders "Water" and "Ceviche".
For the table 10: Corina orders "Beef Burrito". 

Example 2:

Input: orders = [["James","12","Fried Chicken"],["Ratesh","12","Fried Chicken"],["Amadeus","12","Fried Chicken"],["Adam","1","Canadian Waffles"],["Brianna","1","Canadian Waffles"]]
Output: [["Table","Canadian Waffles","Fried Chicken"],["1","2","0"],["12","0","3"]] 
Explanation: 
For the table 1: Adam and Brianna order "Canadian Waffles".
For the table 12: James, Ratesh and Amadeus order "Fried Chicken".

Example 3:

Input: orders = [["Laura","2","Bean Burrito"],["Jhon","2","Beef Burrito"],["Melissa","2","Soda"]]
Output: [["Table","Bean Burrito","Beef Burrito","Soda"],["2","1","1","1"]]

Constraints:

1 <= orders.length <= 5 * 10^4
orders[i].length == 3
1 <= customerNamei.length, foodItemi.length <= 20
customerNamei and foodItemi consist of lowercase and uppercase English letters and the space character.
tableNumberi is a valid integer between 1 and 500.
 */

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders)
    {
        std::vector<std::vector<std::string>> res;

        std::set<std::string> set_food;
        std::map<int, std::map<std::string, int>> table_map;
        for (const std::vector<std::string>& order : orders)
        {
            table_map[std::stoi(order[1])][order[2]]++;
            set_food.insert(order[2]);
        }

        std::vector<std::string> header;
        header.push_back("Table");
        for (const std::string& food : set_food)
        {
            header.push_back(food);
        }
        res.push_back(header);

        for (auto& pair : table_map)
        {
            std::vector<std::string> row;
            row.push_back(std::to_string(pair.first));

            std::map<std::string, int>& row_data = pair.second;
            for (const std::string& food : set_food)
            {
                if (row_data.find(food) != row_data.end())
                {
                    row.push_back(std::to_string(row_data[food]));
                }
                else
                {
                    row.push_back("0");
                }
            }

            res.push_back(row);
        }

        return res;    
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<std::string>> orders = {
        {"David","3","Ceviche"},
        {"Corina","10","Beef Burrito"},
        {"David","3","Fried Chicken"},
        {"Carla","5","Water"},
        {"Carla","5","Ceviche"},
        {"Rous","3","Ceviche"},
    };
    std::vector<std::vector<std::string>> res = sol.displayTable(orders);
    for (const std::vector<std::string>& row : res)
    {
        for (const std::string& data : row)
        {
            std::cout << data << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}