/**
 * @file Test.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "doctest.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "OrgChart.hpp"
using namespace std;
using namespace ariel;

TEST_CASE("Organization 1")
{

    /*Sample level order tests*/
    OrgChart organization;
    size_t i = 0;
    organization.add_root("1")
        .add_sub("1", "2")
        .add_sub("1", "3")
        .add_sub("1", "4")
        .add_sub("2", "5")
        .add_sub("2", "6")
        .add_sub("2", "7")
        .add_sub("3", "8")
        .add_sub("3", "9")
        .add_sub("4", "10");
    /**
     * 1
     * |
     * 2------3------4
     * |      |      |
     * 5-6-7  8-9    10
     *
     */
    cout << organization << endl;
    /*the iterator is not functining right now properly, so i will leave it as this and just test 1...21*/
    SUBCASE("Level Order")
    {
        i = 0;
        for (auto iter = organization.begin_level_order(); iter != organization.end_level_order(); ++iter)
        {
            ++i;
            CHECK_EQ(to_string(i), (*iter));
        }
    }
    SUBCASE("Reverse Level Order")
    {
        i = 0;
        std::vector<int> check = {5, 6, 7, 8, 9, 10, 2, 3, 4, 1};
        for (auto iter = organization.begin_reverse_order(); iter != organization.reverse_order(); ++iter)
        {
            CHECK_EQ(to_string(check.at(i)), (*iter));
            ++i;
        }
    }
    SUBCASE("Preorder")
    {
        i = 0;
        std::vector<int> check = {1, 2, 5, 6, 7, 3, 8, 9, 4, 10};
        for (auto iter = organization.begin_preorder(); iter != organization.end_preorder(); ++iter)
        {
            CHECK_EQ(to_string(check.at(i)), (*iter));
            ++i;
        }
    }
}

TEST_CASE("Organization 2")
{

    /*Sample level order tests*/
    OrgChart organization;
    size_t i = 0;
    organization.add_root("CEO")
        .add_sub("CEO", "CTO")    // Now the CTO is subordinate to the CEO
        .add_sub("CEO", "CFO")    // Now the CFO is subordinate to the CEO
        .add_sub("CEO", "COO")    // Now the COO is subordinate to the CEO
        .add_sub("CTO", "VP_SW")  // Now the VP Software is subordinate to the CTO
        .add_sub("COO", "VP_BI"); // Now the VP_BI is subordinate to the COO

    cout << organization << endl; /* Prints the org chart in a reasonable format. For example:
         CEO
         |--------|--------|
         CTO      CFO      COO
         |                 |
         VP_SW             VP_BI
   */
    /*the iterator is not functining right now properly, so i will leave it as this and just test 1...21*/
    SUBCASE("Level Order")
    {
        i = 0;
        std::vector<std::string> check = {"CEO", "CTO", "CFO", "COO", "VP_SW", "VP_BI"};
        for (auto iter = organization.begin_level_order(); iter != organization.end_level_order(); ++iter)
        {
            CHECK_EQ(check.at(i), (*iter));
            ++i;
        }
    }
    SUBCASE("Reverse Level Order")
    {
        i = 0;
        std::vector<std::string> check = {"VP_SW", "VP_BI", "CTO", "CFO", "COO", "CEO"};
        for (auto iter = organization.begin_reverse_order(); iter != organization.reverse_order(); ++iter)
        {
            CHECK_EQ(check.at(i), (*iter));
            ++i;
        }
    }
    SUBCASE("Preorder")
    {
        i = 0;
        std::vector<std::string> check = {"CEO", "CTO", "VP_SW", "CFO", "COO", "VP_BI"};
        for (auto iter = organization.begin_preorder(); iter != organization.end_preorder(); ++iter)
        {
            CHECK_EQ(check.at(i), (*iter));
            ++i;
        }
    }
    SUBCASE("Arrow Operator")
    {   
        i = 0;
        std::vector<int> check = {3,3,3,3,5,5};
        for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
        {
            CHECK_EQ(check.at(i),it->size());
            ++i;
        } 
    }
}

TEST_CASE("Bad Case Trees")
{
    OrgChart organization;
    size_t i = 0;

    SUBCASE("Empty Tree")
    {
        /*Empty charts*/
        CHECK_THROWS_MESSAGE(organization.begin_reverse_order(), "chart is empty!");
        CHECK_THROWS_MESSAGE(organization.reverse_order(), "chart is empty!");

        CHECK_THROWS_MESSAGE(organization.begin_level_order(), "chart is empty!");
        CHECK_THROWS_MESSAGE(organization.end_level_order(), "chart is empty!");

        CHECK_THROWS_MESSAGE(organization.begin_preorder(), "chart is empty!");
        CHECK_THROWS_MESSAGE(organization.end_preorder(), "chart is empty!");

        /*cannot add sub to empty tree*/
        CHECK_THROWS(organization.add_sub("shaked", "shaked"));
    }
    SUBCASE("One head tree")
    {
        CHECK_NOTHROW(organization.add_root("shaked"));
        for (size_t i = 0; i < 11; i++)
        {
            CHECK_NOTHROW(organization.add_sub("shaked", "shaked"));
        }
    }

    SUBCASE("Special Chars"){
        CHECK_THROWS(organization.add_root(" "));
        CHECK_THROWS(organization.add_root("\n"));
        CHECK_THROWS(organization.add_root("\t"));
        CHECK_THROWS(organization.add_root("\r"));
        
        CHECK_NOTHROW(organization.add_root("shaked"));
        CHECK_THROWS(organization.add_sub("shaked"," "));
        CHECK_THROWS(organization.add_sub("shaked","\n"));
        CHECK_THROWS(organization.add_sub("shaked","\t"));
        CHECK_THROWS(organization.add_sub("shaked","\r"));
    }

}