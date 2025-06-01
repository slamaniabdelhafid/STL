#include <catch2/catch_test_macros.hpp>
#include "../include/circular_list.hpp"
#include <vector>
#include <algorithm>

TEST_CASE("Circular List Construction", "[construction]") {
    SECTION("Default constructor") {
        cls::circular_list<int> list;
        REQUIRE(list.empty());
        REQUIRE(list.size() == 0);
    }
    
    SECTION("Initializer list constructor") {
        cls::circular_list<int> list{1, 2, 3};
        REQUIRE(list.size() == 3);
        
        std::vector<int> result;
        for (const auto& item : list) {
            result.push_back(item);
        }
        REQUIRE(result == std::vector<int>{1, 2, 3});
    }
}

TEST_CASE("Element Access", "[access]") {
    cls::circular_list<int> list{10, 20, 30};
    
    SECTION("Front and back") {
        REQUIRE(list.front() == 10);
        REQUIRE(list.back() == 30);
    }
    
    SECTION("Front and back on const list") {
        const auto& clist = list;
        REQUIRE(clist.front() == 10);
        REQUIRE(clist.back() == 30);
    }
    
    SECTION("Empty list access throws") {
        cls::circular_list<int> empty;
        REQUIRE_THROWS_AS(empty.front(), std::out_of_range);
        REQUIRE_THROWS_AS(empty.back(), std::out_of_range);
    }
}

TEST_CASE("Modifiers", "[modifiers]") {
    SECTION("Push back") {
        cls::circular_list<int> list;
        list.push_back(1);
        REQUIRE(list.size() == 1);
        REQUIRE(list.front() == 1);
        REQUIRE(list.back() == 1);
        
        list.push_back(2);
        REQUIRE(list.size() == 2);
        REQUIRE(list.front() == 1);
        REQUIRE(list.back() == 2);
    }
    
    SECTION("Push front") {
        cls::circular_list<int> list;
        list.push_front(1);
        REQUIRE(list.size() == 1);
        REQUIRE(list.front() == 1);
        REQUIRE(list.back() == 1);
        
        list.push_front(2);
        REQUIRE(list.size() == 2);
        REQUIRE(list.front() == 2);
        REQUIRE(list.back() == 1);
    }
    
    SECTION("Pop back") {
        cls::circular_list<int> list{1, 2, 3};
        list.pop_back();
        REQUIRE(list.size() == 2);
        REQUIRE(list.back() == 2);
        
        list.pop_back();
        REQUIRE(list.size() == 1);
        REQUIRE(list.back() == 1);
        
        list.pop_back();
        REQUIRE(list.empty());
    }
    
    SECTION("Pop front") {
        cls::circular_list<int> list{1, 2, 3};
        list.pop_front();
        REQUIRE(list.size() == 2);
        REQUIRE(list.front() == 2);
        
        list.pop_front();
        REQUIRE(list.size() == 1);
        REQUIRE(list.front() == 3);
        
        list.pop_front();
        REQUIRE(list.empty());
    }
    
    SECTION("Clear") {
        cls::circular_list<int> list{1, 2, 3};
        list.clear();
        REQUIRE(list.empty());
        REQUIRE(list.size() == 0);
    }
}

TEST_CASE("Operations", "[operations]") {
    SECTION("Merge") {
        cls::circular_list<int> list1{1, 3, 5};
        cls::circular_list<int> list2{2, 4, 6};
        
        list1.merge(list2);
        REQUIRE(list1.size() == 6);
        REQUIRE(list2.empty());
        
        std::vector<int> result;
        for (const auto& item : list1) {
            result.push_back(item);
        }
        REQUIRE(result.size() == 6);
    }
    
    SECTION("Reverse") {
        cls::circular_list<int> list{1, 2, 3};
        list.reverse();
        
        std::vector<int> result;
        for (const auto& item : list) {
            result.push_back(item);
        }
        REQUIRE(result == std::vector<int>{3, 2, 1});
    }
    
    SECTION("Swap") {
        cls::circular_list<int> list1{1, 2, 3};
        cls::circular_list<int> list2{4, 5};
        
        list1.swap(list2);
        REQUIRE(list1.size() == 2);
        REQUIRE(list2.size() == 3);
        
        std::vector<int> result1;
        for (const auto& item : list1) {
            result1.push_back(item);
        }
        REQUIRE(result1 == std::vector<int>{4, 5});
        
        std::vector<int> result2;
        for (const auto& item : list2) {
            result2.push_back(item);
        }
        REQUIRE(result2 == std::vector<int>{1, 2, 3});
    }
}
