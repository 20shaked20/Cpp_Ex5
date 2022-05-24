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


void ariel::OrgChart::free(Node *root){

    size_t subs = root->get_sub_employees().size();

    for(size_t i = 0; i<subs ; ++i){
        free(root->get_sub_employees().at(i));
    }
    delete root;
}

ariel::OrgChart::~OrgChart() {

    /**
     * @brief iterate over the entire tree and kill all the children.
     * 
     * @param it 
     */
    // if (this->_employee_count == 0)
    // {
    //     std::__throw_length_error("Tree is empty");
    // }

    // for (auto it=reverse_order(); it!=end_preorder(); ++it) {

    //     delete -it;

    // }  
    free(this->_org_chart);

}

ariel::OrgChart &ariel::OrgChart::add_root(std::string name)
{
    if (this->_org_chart == nullptr)
    {
        this->_org_chart = new Node(name);
        this->_employee_count += 1;
    }
    else 
    {   
        this->_org_chart->set_title(name);
    }
    // else{
    //     std::__throw_logic_error("Tree Already Exists");
    // }
    return *this;
}

ariel::OrgChart &ariel::OrgChart::add_sub(std::string root, std::string sub)
{

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
    return *this;
}

std::ostream &ariel::operator<<(std::ostream &output, const ariel::OrgChart &chart)
{
    // std::vector<Node*> temp_childs = chart._org_chart->get_children();
    output << "TMP";
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
    std::string ptr = nodes_to_iterate.at(_node_pos)->get_title();
    std::string *ptr2 = &ptr;
    return ptr2;
    
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

Node* ariel::OrgChart::iterator::operator-(){
    
    return this->nodes_to_iterate.at(_node_pos);
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
    Node *curr;
    size_t i = 0;
    std::vector<Node *> temp_childs;

    Q.push(this->_org_chart);

    while (Q.empty() == false)
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

ariel::OrgChart::iterator ariel::OrgChart::end_level_order()
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

ariel::OrgChart::iterator ariel::OrgChart::end()
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
    Node *curr;
    size_t i = 0;
    std::vector<Node *> temp_childs;

    Q.push(this->_org_chart);

    while (Q.empty() == false)
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

ariel::OrgChart::iterator ariel::OrgChart::reverse_order()
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
    Node *curr;
    size_t i = 0;
    std::vector<Node *> temp_childs;

    S.push(this->_org_chart);

    while (S.empty() == false)
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

ariel::OrgChart::iterator ariel::OrgChart::end_preorder()
{

    return end_level_order();
}
