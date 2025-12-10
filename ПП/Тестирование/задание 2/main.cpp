//подключаем макросы catch2
#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <iostream>

#include <iostream>
//код
struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

//тесты для PushBack
TEST_CASE("Pushback function tests", "[List]") {
    List list;

    SECTION("PushBack to empty list") {
        list.PushBack(42)
        REQUIRE(list.Size() == 1);
        REQUIRE(list.Empty() == false);
        REQUIRE(list.PopBack() == 42);

    }

    SECTION("PushBack multiple elements") {
        list.PushBack(10);
        list.PushBack(20);
        list.PushBack(30);

        REQUIRE(list.Size() == 3);
        REQUIRE(list.PopBack() == 30);
        REQUIRE(list.PopBack() == 20);
        REQUIRE(list.PopBack() == 10);


    }

    SECTION("PushBack mains order") {
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);

        REQUIRE(list.PopFront() == 1);
        REQUIRE(list.PopFront() == 2);
        REQIURE(list.PopFront() == 3);

    }

}

//тесты для PushFront
TEST_CASE("PushFront function tests", "[List]") {
    List list;

    SECTION("PushFront to empty list") {
        list.PushFront(99);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.Empty() == false);
        REQUIRE(list.PopFront() == 99);
    }

    SECTION("PushFront multiple elements") {
        list.PushFront(30);
        list.PushFront(20);
        list.PushFront(10);

        REQUIRE(list.Size() == 3);
        REQUIRE(list.PopFront() == 10);
        REQUIRE(list.PopFront() == 20);
        REQUIRE(list.PopFront() == 30);

    }

    SECTION("PushFront maintains order") {

        list.PushFront(3);
        list.PushFront(2); 
        list.PushFront(1);

        REQUIRE(list.PopFront() == 1);
        REQUIRE(list.PopFront() == 2);
        REQUIRE(list.PopFront() == 3);
    }
}
//тест для PopBlack
TEST_CASE("PopBack function tests", "[List]"){
    List list;

    SECTION("PopBack from empty list throws exception") {
        list.PushBack(100);
        REQUIRE(list.PopBack() == 100);
        REQUIRE(list.PopBack() == true);
        REQUIRE(list.Size() == 0);
    }

    SECCTION("PopBack from multiple elements") {
        list.PushBack(10);
        list.PushBack(20);
        list.PushBack(30);

        REQUIRE(list.PopBack() == 30);
        REQUIRE(list.Size() == 2);
        REQUIRE(list.PopBack() == 20);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.PopBack() == 10);
        REQUIRE(list.Size() == 0);

    }
    SECTION("PopBack correct order") {
        list.PushFront(1);
        list.PushBack(2);
        list.PushFront(3);

        REQUIRE(list.PopBack() == 2);
        REQUIRE(list.PopBack() == 1);
        REQUIRE(list.PopBack() == 3);
    }
}
// СЛОЖНЫЙ СЦЕНАРИЙ ИСПОЛЬЗОВАНИЯ
TEST_CASE("Complex usage scenario", "[List]")
{
    List list;

    SECTION("Mixed operations complex test")
    {
        REQUIRE(list.Empty() == true);
        
        list.PushBack(100);    
        list.PushFront(50);    
        list.PushBack(200);
        list.PushFront(25);
        list.PushBack(300);

        REQUIRE(list.Size() == 5);
        REQUIRE(list.Empty() == false);

       
        REQUIRE(list.PopFront() == 25);
        REQUIRE(list.PopBack() == 300); 
        REQUIRE(list.Size() == 3);

        list.PushFront(10);
        list.PushBack(400);    
        REQUIRE(list.Size() == 5);

        
        REQUIRE(list.PopFront() == 10); 
        REQUIRE(list.PopFront() == 50); 
        REQUIRE(list.PopBack() == 400); 

        REQUIRE(list.Size() == 2);

        REQUIRE(list.PopFront() == 100);
        REQUIRE(list.PopBack() == 200); 

        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);

        
        REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
        REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);

        
        list.PushBack(999); 
        list.PushFront(888);

        REQUIRE(list.PopBack() == 999);  
        REQUIRE(list.PopFront() == 888); 

        REQUIRE(list.Empty() == true);
    }

    SECTION("Alternating push/pop operations")
    {
        
        list.PushFront(1);
        list.PushBack(2);
        REQUIRE(list.PopFront() == 1);  

        list.PushFront(3);
        list.PushBack(4);
        REQUIRE(list.PopBack() == 4);

        REQUIRE(list.PopFront() == 3); 
        REQUIRE(list.PopBack() == 2);

        list.PushBack(5);
        list.PushFront(6);
        REQUIRE(list.Size() == 2);      

        REQUIRE(list.PopBack() == 5);
        REQUIRE(list.PopFront() == 6);
    }
}
