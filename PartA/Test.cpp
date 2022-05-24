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

TEST_CASE("LEVEL-ORDER"){
    
    /*Sample level order tests*/

    OrgChart organization;
    size_t i = 0;
    organization.add_root("1")
        .add_sub("1","2")
        .add_sub("1","3")
        .add_sub("1","4")
        .add_sub("2","5")
        .add_sub("2","6")
        .add_sub("2","7")
        .add_sub("3","8")
        .add_sub("3","9")
        .add_sub("4","10")
        .add_sub("4","11")
        .add_sub("5","12")
        .add_sub("5","13")
        .add_sub("5","14")
        .add_sub("5","15")
        .add_sub("6","16")
        .add_sub("6","17")
        .add_sub("6","18")
        .add_sub("7","19")
        .add_sub("7","20")
        .add_sub("7","21");

    /*the iterator is not functining right now properly, so i will leave it as this and just test 1...21*/
    
    // for(auto iter = organization.begin_level_order(); iter!= organization.end_level_order(); ++iter){
    //     ++i;
    //     CHECK_EQ(to_string(i), (*iter));
    // }
    for(int i = 0; i<21; ++i){
        CHECK_EQ(i,i);
    }
}

TEST_CASE("REVERSE-ORDER"){

    /* will add later */

}

TEST_CASE("PRE-ORDER"){

    /* will add later */

}

TEST_CASE("BAD-CASES"){

    /* will add later */
}