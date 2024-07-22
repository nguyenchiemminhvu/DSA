#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

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
        clear();
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

    bool contain_wildcards(const std::string& str)
    {
        return false;
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

        

        return res;
    }

    void erase(const std::string& str)
    {
        recursive_erase(m_root, str, 0U);
    }

    void clear()
    {
        recursive_deallocate(m_root);
        m_root->children.clear();
    }

    bool empty()
    {
        return m_root == nullptr || m_root->children.empty();
    }

private:
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

    void recursive_deallocate(Node* cur)
    {
        if (cur == nullptr)
        {
            return;
        }

        for (auto& child : cur->children)
        {
            recursive_deallocate(child.second);
        }

        if (cur != nullptr)
        {
            delete cur;
            cur = nullptr;
        }
    }

private:
    Node* m_root;
};

#endif // TRIE_H