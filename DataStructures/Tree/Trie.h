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
        bool completed;
        std::unordered_map<char, Node*> children;
    };

    Trie()
        : m_root(nullptr)
    {
    }

    Trie(const std::string& str)
        : Trie()
    {

    }

    Trie(const std::vector<std::string>& strs)
        : Trie()
    {

    }

    ~Trie()
    {
        clear();
    }

    void swap(Trie& another)
    {

    }

    void insert(const std::string& str)
    {

    }

    bool contain(const std::string& str)
    {
        return false;
    }

    bool contain_wildcards(const std::string& str)
    {
        return false;
    }

    std::vector<std::string> get_list()
    {
        return {};
    }

    std::vector<std::string> get_list_prefix(const std::string& prefix)
    {
        return {};
    }

    void erase(const std::string& str)
    {
        
    }

    void clear()
    {

    }

    bool empty()
    {
        return true;
    }

private:
    Node* m_root;
};

#endif // TRIE_H