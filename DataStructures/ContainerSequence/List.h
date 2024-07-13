#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <initializer_list>

template <typename T>
struct ListNode
{
    T data;
    ListNode* next;
    ListNode* prev;

    ListNode(const T& val)
        : data(val)
        , next(nullptr)
        , prev(nullptr)
    {

    }
};

template <typename T>
class List
{
public:
    using iterator = ListNode<T>*;
    using const_iterator = const ListNode<T>*;

    List()
        : m_head(nullptr)
        , m_tail(nullptr)
        , m_size(0U)
    {

    }

    List(const std::initializer_list<T>& L)
        : m_head(nullptr)
        , m_tail(nullptr)
        , m_size(0U)
    {
        for (const T& val : L)
        {
            push_back(val);
        }
    }

    List(const List<T>& another)
        : m_head(nullptr)
        , m_tail(nullptr)
        , m_size(0U)
    {
        for (iterator it = another.m_head; it != nullptr; it = it->next)
        {
            push_back(it->data);
        }
    }

    ~List()
    {
        clear();
    }

    void swap(List<T>& another)
    {
        std::swap(m_head, another.m_head);
        std::swap(m_tail, another.m_tail);
        std::swap(m_size, another.m_size);
    }

    void push_back(const T& value)
    {
        ListNode<T>* new_node = new ListNode<T>(value);
        if (m_head == nullptr)
        {
            m_head = new_node;
            m_tail = new_node;
        }
        else
        {
            m_tail->next = new_node;
            new_node->prev = m_tail;
            m_tail = new_node;
        }
        m_size++;
    }

    void push_front(const T& value)
    {
        ListNode<T>* new_node = new ListNode<T>(value);
        if (m_head == nullptr)
        {
            m_head = new_node;
            m_tail = new_node;
        }
        else
        {
            m_head->prev = new_node;
            new_node->next = m_head;
            m_head = new_node;
        }
        m_size++;
    }

    void pop_back()
    {
        if (m_head != nullptr)
        {
            ListNode<T>* temp = m_tail;
            m_tail = m_tail->prev;
            if (m_tail != nullptr)
            {
                m_tail->next = nullptr;
            }
            else
            {
                m_head = nullptr;
            }
            delete temp;
            m_size--;
        }
    }

    void pop_front()
    {
        if (m_head)
        {
            ListNode<T>* temp = m_head;
            m_head = m_head->next;
            if (m_head != nullptr)
            {
                m_head->prev = nullptr;
            }
            else
            {
                m_tail = nullptr;
            }
            delete temp;
            m_size--;
        }
    }

    void clear()
    {
        while (!empty())
        {
            pop_back();
        }
    }

    T& front()
    {
        if (m_head == nullptr)
        {
            throw std::out_of_range("Access empty list");
        }

        return m_head->data;
    }

    const T& front() const
    {
        if (m_head == nullptr)
        {
            throw std::out_of_range("Access empty list");
        }

        return m_head->data;
    }

    T& back()
    {
        if (m_tail == nullptr)
        {
            throw std::out_of_range("Access empty list");
        }

        return m_tail->data;
    }

    const T& back() const
    {
        if (m_tail == nullptr)
        {
            throw std::out_of_range("Access empty list");
        }

        return m_tail->data;
    }

    std::size_t size() const
    {
        return m_size;
    }

    bool empty() const
    {
        return m_size == 0U;
    }

private:
    ListNode<T>* m_head;
    ListNode<T>* m_tail;
    std::size_t m_size;
};

#endif // LIST_H