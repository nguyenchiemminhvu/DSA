#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <functional>

template<typename TK, typename TV>
class HashTable
{
public:
    HashTable(std::size_t initial_size = 16U)
        : m_table(initial_size), m_size(0U)
    {

    }

    void swap(HashTable<TK, TV>& another)
    {
        std::swap(m_table, another.m_table);
        std::swap(m_size, another.m_size);
    }

    void insert(const TK& key, const TV& value)
    {
        if (load_factor() >= 0.75)
        {
            resize_table(m_table.size() * 2U);
        }

        std::size_t index = hash_key(key);
        m_table[index].emplace_back(key, value);
        ++m_size;
    }

    TV& retrieve(const TK& key)
    {
        std::size_t index = hash_key(key);
        for (auto& kv : m_table[index])
        {
            if (kv.first == key)
            {
                return kv.second;
            }
        }
        throw std::out_of_range("Key is not found");
    }

    bool contain(const TK& key) const
    {
        std::size_t index = hash_key(key);
        for (const auto& kv : m_table[index])
        {
            if (kv.first == key)
            {
                return true;
            }
        }
        return false;
    }

    void remove(const TK& key)
    {
        std::size_t index = hash_key(key);
        auto& bucket = m_table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == key)
            {
                bucket.erase(it);
                --m_size;
                return;
            }
        }
        throw std::out_of_range("Key is not found");
    }

    void clear()
    {
        for (auto& bucket : m_table)
        {
            bucket.clear();
        }
        m_size = 0U;
    }

    std::size_t size() const
    {
        return m_size;
    }

    bool empty()
    {
        return m_size == 0U;
    }

private:
    std::size_t hash_key(const TK& key) const
    {
        return std::hash<TK>{}(key) % m_table.size();
    }

    double load_factor() const
    {
        return static_cast<double>(m_size) / m_table.size();
    }

    void resize_table(std::size_t new_size)
    {
        std::vector<std::list<std::pair<TK, TV>>> new_table(new_size);
        for (const auto& bucket : m_table)
        {
            for (const auto& kv : bucket)
            {
                std::size_t new_index = std::hash<TK>{}(kv.first) % new_size;
                new_table[new_index].emplace_back(kv.first, kv.second);
            }
        }
        m_table = std::move(new_table);
    }

private:
    std::vector<std::list<std::pair<TK, TV>>> m_table;
    std::size_t m_size;
};

#endif // HASH_TABLE_H