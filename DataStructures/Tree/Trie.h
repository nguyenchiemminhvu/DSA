#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Trie
{
public:
    struct Node
    {
        char key;
        std::size_t count;
        std::unordered_map<char, Node*> children;

        Node(char k)
            : key(k), count(0U)
        {
        }

        ~Node()
        {
            for (auto& child : children)
            {
                delete child.second;
            }
        }
    };

    Trie()
    {
        m_root = new Node(0);
    }

    Trie(const std::string& str)
        : Trie()
    {
        insert(str);
    }

    Trie(const std::vector<std::string>& strs)
        : Trie()
    {
        for (const std::string& str : strs)
        {
            insert(str);
        }   
    }

    ~Trie()
    {
        delete m_root;
    }

    void swap(Trie& another)
    {
        std::swap(m_root, another.m_root);
    }

    void insert(const std::string& str)
    {
        Node* cur = m_root;
        for (std::size_t i = 0U; i < str.length(); i++)
        {
            if (cur->children.find(str[i]) == cur->children.end())
            {
                cur->children[str[i]] = new Node(str[i]);
            }

            cur = cur->children[str[i]];

            if (i == str.length() - 1U)
            {
                cur->count++;
            }
        }
    }

    bool contain(const std::string& str)
    {
        Node* cur = m_root;
        for (std::size_t i = 0U; i < str.length(); i++)
        {
            if (cur->children.find(str[i]) == cur->children.end())
            {
                return false;
            }
            else
            {
                cur = cur->children[str[i]];
            }
        }

        return cur->count > 0U;
    }

    std::size_t count(const std::string& str)
    {
        Node* cur = m_root;
        for (std::size_t i = 0U; i < str.length(); i++)
        {
            if (cur->children.find(str[i]) == cur->children.end())
            {
                return 0U;
            }
            else
            {
                cur = cur->children[str[i]];
            }
        }
        
        return cur->count;
    }

    bool contain_wildcards(const std::string& str)
    {
        return recursive_contain_wildcards(m_root, str, 0U);
    }

    std::size_t count_wildcards(const std::string& str)
    {
        return recursive_count_wildcards(m_root, str, 0U);
    }

    std::vector<std::string> get_list()
    {
        std::vector<std::string> res;
        std::string temp;
        recursive_get_list(m_root, temp, res);

        return res;
    }

    std::vector<std::string> get_list_prefix(const std::string& prefix)
    {
        std::vector<std::string> res;

        Node* cur = m_root;
        for (std::size_t i = 0U; i < prefix.length(); i++)
        {
            if (cur->children.find(prefix[i]) == cur->children.end())
            {
                return res;
            }
            else
            {
                cur = cur->children[prefix[i]];
            }
        }

        std::string temp = prefix;
        recursive_get_list(cur, temp, res);

        return res;
    }

    void erase(const std::string& str)
    {
        recursive_erase(m_root, str, 0U);
    }

    void clear()
    {
        if (m_root != nullptr)
        {
            delete m_root;
            m_root = nullptr;
        }
    }

    bool empty()
    {
        return m_root == nullptr || m_root->children.empty();
    }

private:
    bool recursive_contain_wildcards(Node* cur, const std::string& str, std::size_t idx)
    {
        if (cur == nullptr)
        {
            return false;
        }

        if (idx >= str.length())
        {
            return cur->count > 0U;
        }

        if (str[idx] == '*')
        {
            for (auto& child : cur->children)
            {
                if (recursive_contain_wildcards(child.second, str, idx + 1))
                {
                    return true;
                }
            }
        }
        else
        {
            if (cur->children.find(str[idx]) != cur->children.end())
            {
                return recursive_contain_wildcards(cur->children[str[idx]], str, idx + 1);
            }
        }

        return false;
    }

    std::size_t recursive_count_wildcards(Node* cur, const std::string& str, std::size_t idx)
    {
        if (cur == nullptr)
        {
            return 0U;
        }

        if (idx >= str.length())
        {
            return cur->count;
        }

        std::size_t count = 0U;
        if (str[idx] == '*')
        {
            for (auto& child : cur->children)
            {
                count += recursive_count_wildcards(child.second, str, idx + 1);
            }
        }
        else
        {
            if (cur->children.find(str[idx]) != cur->children.end())
            {
                count += recursive_count_wildcards(cur->children[str[idx]], str, idx + 1);
            }
        }

        return count;
    }

    void recursive_get_list(Node* cur, std::string temp, std::vector<std::string>& res)
    {
        if (cur == nullptr)
        {
            return;
        }

        for (std::size_t count = 0U; count < cur->count; count++)
        {
            res.push_back(temp);
        }

        for (auto& child : cur->children)
        {
            temp.push_back(child.first);
            recursive_get_list(child.second, temp, res);
            temp.pop_back();
        }
    }

    bool recursive_erase(Node* cur, const std::string& str, std::size_t idx)
    {
        if (idx == str.size())
        {
            if (cur->count > 0U)
            {
                cur->count--;
            }

            return cur->children.empty() && cur->count == 0U;
        }

        if (cur->children.find(str[idx]) == cur->children.end())
        {
            return false;
        }

        bool should_delete = recursive_erase(cur->children[str[idx]], str, idx + 1);

        if (should_delete)
        {
            delete cur->children[str[idx]];
            cur->children.erase(str[idx]);
            return cur->children.empty() && cur->count == 0U;
        }

        return false;
    }

private:
    Node* m_root;
};

#endif // TRIE_H