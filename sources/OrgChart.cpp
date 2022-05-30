/**
 * @file OrgChart.cpp
 * @author shaked levi
 * @brief this is the cpp file for the orgchart class
 * @version 0.1
 * @date 2022-05-18
 *
 * credits:
 * 1. i used the help of geeks for geeks to implement the level_order
 *    see -> https://www.geeksforgeeks.org/level-order-tree-traversal/
 * 2. i used the help of geeks for geeks to implement to pre_order
 *    see -> https://www.geeksforgeeks.org/iterative-preorder-traversal/
 * 
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <bits/stdc++.h>
#include "OrgChart.hpp"

ariel::OrgChart::OrgChart() : _org_chart(nullptr), _employee_count(0) {}

ariel::OrgChart::~OrgChart() {

    /**
     * @brief iterate over the entire tree and kill all the children.
     * 
     * @param it 
     */

    for(size_t i = 0; i<_todelete.size(); ++i){
        delete _todelete.at(i);
    }
}

ariel::OrgChart &ariel::OrgChart::add_root(std::string root)
{

    if(root == " " || root == "\n" || root == "\t" || root == "\r")
    {
        std::__throw_invalid_argument("Cant insert special chars as root..\n");
    }

    if (this->_org_chart == nullptr)
    {
        this->_org_chart = new Node(root);
        this->_employee_count += 1;

        _todelete.push_back(this->_org_chart);
    }
    else 
    {   
        this->_org_chart->set_title(root);

        _todelete.at(0) = this->_org_chart;
    }
    
    return *this;
}

ariel::OrgChart &ariel::OrgChart::add_sub(std::string root, std::string sub)
{

    if(sub == " " || sub == "\n" || sub == "\t" || sub == "\r")
    {
        std::__throw_invalid_argument("Cant insert special chars as root..\n");
    }

    if(this->_employee_count == 0){

        std::__throw_length_error("Tree is empty and cannot add sub before root!");

    }
    /*chekcs if the root exists*/
    Node *pnode = _org_chart->search_title_in_tree(root);
    
    if (pnode == nullptr)
    {
        std::__throw_out_of_range("There is no parent in this tree to match this title");
    }

    /*simply create the new node and add it to the after sons*/
    Node *add_sub = new Node(sub, pnode);
    pnode->add_sub_employee(add_sub);
    this->_employee_count += 1;

    _todelete.push_back(add_sub);

    return *this;
}

std::ostream &ariel::operator<<(std::ostream &output, const ariel::OrgChart &chart)
{
    // std::vector<Node*> temp_childs = chart._org_chart->get_children();
      if (chart._employee_count == 0)
    {
        std::__throw_length_error("Tree is empty");
    }
    
    std::queue<Node *> Q;
    Node *curr = nullptr;
    size_t i = 0;
    std::vector<Node *> temp_childs;
    int nodes = 0;

    Q.push(chart._org_chart);

    while (!Q.empty())
    {
        
        nodes = Q.size();
       
        while(nodes > 0){

            curr = Q.front();
            output << curr->get_title() << "       ";
            Q.pop();

            temp_childs = curr->get_sub_employees();

            for (i = 0; i < temp_childs.size(); ++i)
            {
                Q.push(temp_childs.at(i));
            }
            --nodes;
        }
        int const five = 5;
        output << std::endl;
        if(temp_childs.size() != 1){
        for(size_t k = 0; k<temp_childs.size(); ++k){
            int word_curr_child_size = temp_childs.at(k)->get_title().length();
            output<<"|";
            for(int x = 1; x<word_curr_child_size+five; ++x){
                output<<"-";
            }
            output<<"|";
        }
        }else{
            output <<"|";
        }
        output <<"\n";
    }
    return output;
}

/*Iterator class implement*/

ariel::OrgChart::iterator::iterator(std::vector<Node *> &nodes, int type)
{

    this->nodes_to_iterate = std::move(nodes);

    /*this state indicates which type we operate on:
     * type = 0 -> its end()...
     * type = 1 -> its begin()...
     */
    this->_type = type;
    if (type == 0)
    {
        this->_node_pos = nodes_to_iterate.size() - 1;
    }
    else
    {
        this->_node_pos = 0;
    }
}

std::string ariel::OrgChart::iterator::operator*() const
{

    if (this->_node_pos >= nodes_to_iterate.size() - 1)
    {

        std::__throw_out_of_range("Operator * out of bounds...");
    }

    return this->nodes_to_iterate.at(this->_node_pos)->get_title();
}

std::string *ariel::OrgChart::iterator::operator->() const
{

    /*i did a trick to convert it to a pointer so it will fetch the ptr instead of & and keep the data*/
    std::string *ptr = new std::string(nodes_to_iterate.at(_node_pos)->get_title());
    // std::string *ptr2 = &ptr;
    return ptr;
    
}

ariel::OrgChart::iterator &ariel::OrgChart::iterator::operator++()
{ /* ++i */

    if (_node_pos >= nodes_to_iterate.size() - 1)
    {
        std::__throw_out_of_range("Operator prefix ++ out of bounds...");
    }

    this->_node_pos++;
    return *this;
}

ariel::OrgChart::iterator ariel::OrgChart::iterator::operator++(int)
{ /* i++ */

    if (_node_pos >= nodes_to_iterate.size() - 1)
    {
        std::__throw_out_of_range("Operator suffix ++ out of bounds...");
    }
    ariel::OrgChart::iterator suffix = *this;
    this->_node_pos++;
    return suffix;
}

bool ariel::operator==(const ariel::OrgChart::iterator &left, const ariel::OrgChart::iterator &right)
{

    return left.nodes_to_iterate.at(left._node_pos) == right.nodes_to_iterate.at(right._node_pos);
}

bool ariel::OrgChart::iterator::operator!=(const ariel::OrgChart::iterator &cpy) const
{

    return !(*this == cpy);
}

/*iterators begin - end */

/*Level order*/
ariel::OrgChart::iterator ariel::OrgChart::begin_level_order()
{
    if (this->_employee_count == 0)
    {
        std::__throw_length_error("Tree is empty");
    }

    std::vector<Node *> level_ordered;
    std::queue<Node *> Q;
    Node *curr = nullptr;
    size_t i = 0;
    std::vector<Node *> temp_childs;

    Q.push(this->_org_chart);

    while (!Q.empty())
    {
        curr = Q.front();

        Q.pop();
        level_ordered.push_back(curr);

        temp_childs = curr->get_sub_employees();

        for (i = 0; i < temp_childs.size(); ++i)
        {

            Q.push(temp_childs.at(i));
        }
    }
    /*indicates the last node in the list, so i will know when to stop*/
    Node *null_node = nullptr;
    level_ordered.push_back(null_node);

    return (ariel::OrgChart::iterator{level_ordered, 1});
}

ariel::OrgChart::iterator ariel::OrgChart::end_level_order() const
{   
    if (this->_employee_count == 0)
    {
        std::__throw_length_error("Tree is empty");
    }

    std::vector<Node *> null_vector;
    // for(size_t i = 0; i<_employee_count; ++i){
    //     null_vector.push_back(nullptr);
    // }
    null_vector.push_back(nullptr);
    return (ariel::OrgChart::iterator{null_vector, 0});
}

/*Level order, diff name?*/
ariel::OrgChart::iterator ariel::OrgChart::begin()
{
    return begin_level_order();
}

ariel::OrgChart::iterator ariel::OrgChart::end() const
{
    return end_level_order();
}

/*reverse order*/
/*
 * i implement this as the same of level_order, the trick here is just to use reverse on the vector
 * of employees i created.
 */
ariel::OrgChart::iterator ariel::OrgChart::begin_reverse_order()
{
    /*is the same as level_order just with reverse methoding at the end*/
    if (this->_employee_count == 0)
    {
        std::__throw_length_error("Tree is empty");
    }
    std::vector<Node *> reverse_ordered;
    std::queue<Node *> Q;
    Node *curr = nullptr;
    size_t i = 0;
    std::vector<Node *> temp_childs;

    Q.push(this->_org_chart);

    while (!Q.empty())
    {
        curr = Q.front();

        Q.pop();
        reverse_ordered.push_back(curr);

        temp_childs = curr->get_sub_employees();

        /*This is from right to left*/
        // for (i = 0; i < temp_childs.size(); ++i)
        // {

        //     Q.push(temp_childs.at(i));
        // }

        /*This is from left to right (as tests wanted)*/
        for (i = temp_childs.size(); i > 0; --i)
        {

            Q.push(temp_childs.at(i-1));
        }
    }
    /*the only diffrence*/
    std::reverse(reverse_ordered.begin(), reverse_ordered.end());

    /*indicates the last node in the list, so i will know when to stop*/
    Node *null_node = nullptr;
    reverse_ordered.push_back(null_node);

    return (ariel::OrgChart::iterator{reverse_ordered, 1});
}

ariel::OrgChart::iterator ariel::OrgChart::reverse_order() const
{
    return end_level_order();
}

/*preorder*/
ariel::OrgChart::iterator ariel::OrgChart::begin_preorder()
{

    if (this->_employee_count == 0)
    {
        std::__throw_length_error("Tree is empty");
    }
    
    std::vector<Node *> preordered;
    std::stack<Node *> S;
    Node *curr = nullptr;
    size_t i = 0;
    std::vector<Node *> temp_childs;

    S.push(this->_org_chart);

    while (!S.empty())
    {
        curr = S.top();
        S.pop();

        preordered.push_back(curr);

        temp_childs = curr->get_sub_employees();

        /*the order here is backwards because it needs to start always with the first boi*/
        for (i = temp_childs.size(); i > 0; --i)
        {

            S.push(temp_childs.at(i-1));
        }
    }

    /*indicates the last node in the list, so i will know when to stop*/
    Node *null_node = nullptr;
    preordered.push_back(null_node);

    return (ariel::OrgChart::iterator{preordered, 1});
}

ariel::OrgChart::iterator ariel::OrgChart::end_preorder() const
{

    return end_level_order();
}
