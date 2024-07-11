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

private:
    ListNode<T>* m_head;
    ListNode<T>* m_tail;
};

#endif // LIST_H