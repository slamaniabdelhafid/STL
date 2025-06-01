#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
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
        cls::circular_list<int> list{1, 2, 3, 4};
        REQUIRE(list.size() == 4);
        REQUIRE(std::equal(list.begin(), list.end(), std::begin({1, 2, 3, 4})));
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

TEST_CASE("Iterators", "[iterators]") {
    cls::circular_list<int> list{1, 2, 3};
    const auto& clist = list;
    
    SECTION("Forward iteration") {
        std::vector<int> result;
        for (auto it = list.begin(); it != list.end(); ++it) {
            result.push_back(*it);
        }
        REQUIRE(result == std::vector<int>{1, 2, 3});
    }
    
    SECTION("Const forward iteration") {
        std::vector<int> result;
        for (auto it = clist.begin(); it != clist.end(); ++it) {
            result.push_back(*it);
        }
        REQUIRE(result == std::vector<int>{1, 2, 3});
    }
    
    SECTION("Range-based for loop") {
        std::vector<int> result;
        for (const auto& item : list) {
            result.push_back(item);
        }
        REQUIRE(result == std::vector<int>{1, 2, 3});
    }
    
    SECTION("Bidirectional iteration") {
        auto it = list.begin();
        ++it; // points to 2
        --it; // should point to 1 again
        REQUIRE(*it == 1);
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
        
        std::vector<int> expected{1, 3, 5, 2, 4, 6};
        REQUIRE(std::equal(list1.begin(), list1.end(), expected.begin()));
    }
    
    SECTION("Reverse") {
        cls::circular_list<int> list{1, 2, 3};
        list.reverse();
        
        std::vector<int> expected{3, 2, 1};
        REQUIRE(std::equal(list.begin(), list.end(), expected.begin()));
    }
    
    SECTION("Swap") {
        cls::circular_list<int> list1{1, 2, 3};
        cls::circular_list<int> list2{4, 5};
        
        list1.swap(list2);
        REQUIRE(list1.size() == 2);
        REQUIRE(list2.size() == 3);
        
        REQUIRE(std::equal(list1.begin(), list1.end(), std::begin({4, 5})));
        REQUIRE(std::equal(list2.begin(), list2.end(), std::begin({1, 2, 3})));
    }
}

TEST_CASE("Copy and Move Semantics", "[semantics]") {
    SECTION("Copy constructor") {
        cls::circular_list<int> original{1, 2, 3};
        cls::circular_list<int> copy(original);
        
        REQUIRE(copy.size() == 3);
        REQUIRE(std::equal(original.begin(), original.end(), copy.begin()));
    }
    
    SECTION("Move constructor") {
        cls::circular_list<int> original{1, 2, 3};
        cls::circular_list<int> moved(std::move(original));
        
        REQUIRE(moved.size() == 3);
        REQUIRE(original.empty());
    }
    
    SECTION("Copy assignment") {
        cls::circular_list<int> original{1, 2, 3};
        cls::circular_list<int> copy;
        copy = original;
        
        REQUIRE(copy.size() == 3);
        REQUIRE(std::equal(original.begin(), original.end(), copy.begin()));
    }
    
    SECTION("Move assignment") {
        cls::circular_list<int> original{1, 2, 3};
        cls::circular_list<int> moved;
        moved = std::move(original);
        
        REQUIRE(moved.size() == 3);
        REQUIRE(original.empty());
    }
}
