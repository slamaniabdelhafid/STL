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


}
