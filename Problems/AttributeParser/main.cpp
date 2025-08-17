/**
https://www.hackerrank.com/challenges/attribute-parser/problem

This challenge works with a custom-designed markup language HRML. In HRML, each element consists of a starting and ending tag, and there are attributes associated with each tag. Only starting tags can have attributes. We can call an attribute by referencing the tag, followed by a tilde, '~' and the name of the attribute. The tags may also be nested.

The opening tags follow the format:

<tag-name attribute1-name = "value1" attribute2-name = "value2" ...>

The closing tags follow the format:

</tag-name>

The attributes are referenced as:

tag1~value  
tag1.tag2~name
Given the source code in HRML format consisting of  lines, answer  queries. For each query, print the value of the attribute specified. Print "Not Found!" if the attribute does not exist.

Example

HRML listing
<tag1 value = "value">
<tag2 name = "name">
<tag3 another="another" final="final">
</tag3>
</tag2>
</tag1>

Queries
tag1~value
tag1.tag2.tag3~name
tag1.tag2~value
Here, tag2 is nested within tag1, so attributes of tag2 are accessed as tag1.tag2~<attribute>. Results of the queries are:

Query                 Value
tag1~value            "value"
tag1.tag2.tag3~name   "Not Found!"
tag1.tag2.tag3~final  "final"
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <regex>
using namespace std;

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N, Q;
    cin >> N >> Q;
    cin.ignore();

    std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> attributes;
    std::string curTag;
    for (int i = 0; i < N; i++)
    {
        std::string line;
        std::getline(std::cin, line);
        
        if (line[1] == '/')
        {
            std::size_t lastTagPos = curTag.find_last_of(".");
            if (lastTagPos == std::string::npos)
            {
                curTag.erase(curTag.begin(), curTag.end());
            }
            else
            {
                curTag.erase(curTag.begin() + lastTagPos, curTag.end());
            }
        }
        else
        {
            std::size_t firstSpace = line.find_first_of(' ');
            if (firstSpace != std::string::npos)
            {
                if (!curTag.empty())
                {
                    curTag += ".";
                }
                curTag += line.substr(1, firstSpace - 1);
            }
            else
            {
                curTag += line.substr(1, line.length() - 2);
            }
            
            std::regex pattern(R"(\b(\w+)\s*=\s*\"([^\"]*)\")");
            std::smatch matches;
            
            while (std::regex_search(line, matches, pattern))
            {
                attributes[curTag].push_back({matches[1], matches[2]});
                line = matches.suffix().str();
            }
        }
    }
    
    for (int i = 0; i < Q; i++)
    {
        std::string query;
        std::getline(std::cin, query);
        
        size_t tildePos = query.find('~');
    
        if (tildePos != std::string::npos)
        {
            std::string beforeTilde = query.substr(0, tildePos);
            std::string afterTilde = query.substr(tildePos + 1);
            
            if (attributes.find(beforeTilde) == attributes.end())
            {
                cout << "Not Found!" << endl;
            }
            else
            {
                std::vector<std::pair<std::string, std::string>> pairs = attributes[beforeTilde];
                std::string found = "Not Found!";
                for (const auto& p : pairs)
                {
                    if (p.first == afterTilde)
                    {
                        found = p.second;
                        break;
                    }
                }
                cout << found << std::endl;
            }
        }
    }

    return 0;
}
