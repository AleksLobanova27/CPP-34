//подключаем макросы catch2
#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include "list.h"

TEST_CASE("Empty function tests", "[List]")
{
    List list; 

    // Раздел: Проверка что новый список пустой
    SECTION("New list should be empty")
    {
        REQUIRE(list.Empty() == true); 
    }

    // Раздел: Проверка что список с элементами не пустой
    SECTION("List with elements should not be empty")
    {
        list.PushFront(1);          
        REQUIRE(list.Empty() == false); 

        list.PopFront();           
        REQUIRE(list.Empty() == true); 

    // Раздел: Проверка очистки списка
    SECTION("List after clearing should be empty")
    {
        list.PushBack(10);
        list.PushBack(20);
        REQUIRE(list.Empty() == false);

        list.Clear();
        REQUIRE(list.Empty() == true);
    }
}

TEST_CASE("Size function tests", "[List]")
{
    List list;

    // Раздел: Проверка размера нового списка
    SECTION("New list should have size 0")
    {
        REQUIRE(list.Size() == 0); 
    }

    // Раздел: Проверка изменения размера при добавлении элементов
    SECTION("Size after push operations")
    {
        list.PushFront(1);
        REQUIRE(list.Size() == 1);

        list.PushBack(2);
        REQUIRE(list.Size() == 2);

        list.PushFront(3);
        REQUIRE(list.Size() == 3);
    }

    SECTION("Size after pop operations")
    {
        // Добавляем три элемента
        list.PushFront(1);
        list.PushBack(2);
        list.PushFront(3);
        REQUIRE(list.Size() == 3);

        list.PopFront();
        REQUIRE(list.Size() == 2);

        list.PopBack();
        REQUIRE(list.Size() == 1);

        list.PopBack();
        REQUIRE(list.Size() == 0);
    }

    // Раздел: Проверка размера после очистки
    SECTION("Size after clear operation")
    {
        // Добавляем три элемента
        list.PushFront(1);
        list.PushBack(2);
        list.PushFront(3);
        REQUIRE(list.Size() == 3);

        list.Clear();
        REQUIRE(list.Size() == 0);
    }
}

TEST_CASE("Clear function tests", "[List]")
{
    List list;

    // Раздел: Очистка пустого списка (не должна вызывать ошибок)
    SECTION("Clear empty list")
    {
        REQUIRE_NOTHROW(list.Clear());
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }

    // Раздел: Очистка списка с одним элементом
    SECTION("Clear list with one element")
    {
        list.PushFront(42);
        list.Clear(); 

        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }

    // Раздел: Очистка списка с несколькими элементами
    SECTION("Clear list with multiple elements")
    {
        // Добавляем четыре элемента разными способами
        list.PushFront(1);
        list.PushBack(2);
        list.PushFront(3);
        list.PushBack(4);

        REQUIRE(list.Size() == 4);
        list.Clear();

        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }

    // Раздел: Проверка работы после очистки
    SECTION("Operations after clear should work correctly")
    {
        list.PushFront(10);
        list.PushBack(20);
        REQUIRE(list.Size() == 2);

        list.Clear();
        REQUIRE(list.Empty() == true);

        list.PushFront(30);
        list.PushBack(40);
        REQUIRE(list.Size() == 2); 
        REQUIRE(list.Empty() == false);

        REQUIRE(list.PopFront() == 30);
        REQUIRE(list.PopBack() == 40);  
        REQUIRE(list.Empty() == true); 
    }
}

TEST_CASE("Integration tests for all functions", "[List]")
{
    List list;

    SECTION("Complete workflow test")
    {
        REQUIRE(list.Empty() == true);  
        REQUIRE(list.Size() == 0); 

        list.PushFront(3);
        list.PushFront(2);
        list.PushFront(1);
        REQUIRE(list.Size() == 3); 
        REQUIRE(list.Empty() == false);

        list.PushBack(4);
        list.PushBack(5);
        REQUIRE(list.Size() == 5); 
        
        REQUIRE(list.PopFront() == 1);  
        REQUIRE(list.PopBack() == 5);  
        REQUIRE(list.Size() == 3); 

        list.Clear();
        REQUIRE(list.Empty() == true); 
        REQUIRE(list.Size() == 0);    

        list.PushBack(10);
        REQUIRE(list.Size() == 1); 
        REQUIRE(list.PopFront() == 10); 
    }

    // Раздел: Тестирование обработки исключений
    SECTION("Exception handling test")
    {
        REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
        REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);

        list.PushFront(1);
        list.PopFront();

        REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
    }
}

// Тестирование граничных случаев и нагрузочное тестирование
TEST_CASE("Edge cases and stress tests", "[List]")
{
    List list;

    SECTION("Multiple clear operations")
    {
        list.Clear(); 
        list.Clear(); 
        REQUIRE(list.Empty() == true); 

        list.PushFront(1);
        list.Clear(); 
        list.Clear();
        REQUIRE(list.Empty() == true);
    }

    SECTION("Large number of operations")
    {
        const int NUM_OPERATIONS = 1000; 

        for (int i = 0; i < NUM_OPERATIONS; ++i)
        {
            if (i % 2 == 0)
                list.PushFront(i); 
            else
                list.PushBack(i);  
        }

        REQUIRE(list.Size() == NUM_OPERATIONS); 

        for (int i = 0; i < NUM_OPERATIONS; ++i)
        {
            if (i % 2 == 0)
                list.PopFront();
            else
                list.PopBack(); 
        }

        REQUIRE(list.Empty() == true);
    }
}