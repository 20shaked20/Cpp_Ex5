/**
 * @file OrgChart.cpp
 * @author shaked levi
 * @brief this is the cpp file for the orgchart class
 * @version 0.1
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <bits/stdc++.h>
#include "OrgChart.hpp"



ariel::OrgChart::OrgChart() : _org_chart(nullptr) {}

ariel::OrgChart::~OrgChart(){}

ariel::OrgChart& ariel::OrgChart::add_root(std::string name)
{
    if (this->_org_chart == nullptr)
    {
        this->_org_chart = new Node(name);
        this->_employee_count+=1;
    }
    else
    {
        std::__throw_logic_error("Tree Already Exists");
    }
    return *this;
}

ariel::OrgChart& ariel::OrgChart::add_sub(std::string root, std::string sub)
{   

    /*chekcs if the root exists*/
    Node *pnode = _org_chart->search_title_in_tree(root);

    if(pnode == nullptr){
        std::__throw_out_of_range("There is no parent in this tree to suffice this title");
    }

    /*simply create the new node and add it to the after sons*/
    Node *add_sub = new Node(sub,pnode);
    pnode->add_child(add_sub);
    this->_employee_count+=1;
    return *this;
}

std::ostream &ariel::operator<<(std::ostream &output, const ariel::OrgChart &chart)
{
    // std::vector<Node*> temp_childs = chart._org_chart->get_children();
    output << "TMP";
    return output;
}

/*Iterator class implement*/

ariel::OrgChart::iterator::iterator(std::vector<Node*> &nodes, int type){
    
    this->nodes_to_iterate = std::move(nodes);
    this->_type = type;
    this->_node_pos = 0;

}

std::string ariel::OrgChart::iterator::operator*() const{

    return this->nodes_to_iterate.at(this->_node_pos)->get_title();

}

std::string* ariel::OrgChart::iterator::operator->() const{
    
    std::string *tmp;
    return tmp;
}

ariel::OrgChart::iterator& ariel::OrgChart::iterator::operator++(){ /* ++i */

    this->_node_pos++;
    return *this;
}

ariel::OrgChart::iterator ariel::OrgChart::iterator::operator++(int){ /* i++ */
    /*TODO: implement via the type*/
    ariel::OrgChart::iterator temp = *this;
    return temp;
}

bool ariel::OrgChart::iterator::operator==(const ariel::OrgChart::iterator &cpy) const{

    return this->nodes_to_iterate == cpy.nodes_to_iterate;

}

bool ariel::OrgChart::iterator::operator!=(const ariel::OrgChart::iterator &cpy) const{

    return !(*this == cpy);

}


/*iterators begin - end */

/*Level order*/
ariel::OrgChart::iterator ariel::OrgChart::begin_level_order()
{
    
    std::vector<Node*> level_ordered;
    std::queue<Node*> Q;
    Node *curr;
    size_t i = 0;
    std::vector<Node*> temp_childs;

    Q.push(this->_org_chart);
    Q.push(nullptr);

    while(Q.size() > 1)
    {
        curr = Q.front();
        Q.pop();
        level_ordered.push_back(curr);

        if(curr == nullptr)
        {
            Q.push(nullptr);
        }
        else
        {
            temp_childs = curr->get_children();
            for(i = 0; i<temp_childs.size(); ++i){
                Q.push(temp_childs.at(i));
            }
        }
    }
    

    return (ariel::OrgChart::iterator{level_ordered, 1});
    
}

ariel::OrgChart::iterator ariel::OrgChart::end_level_order()
{  
    std::vector<Node*> null_vector;
    for(size_t i = 0; i<this->_employee_count; ++i){
        null_vector.push_back(nullptr);
    }
    
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

// /*reverse order*/
// ariel::OrgChart::iterator ariel::OrgChart::begin_reverse_order()
// {

//     Node *tmp = nullptr;

//     return (ariel::OrgChart::iterator{tmp, 0});
    
// }

// ariel::OrgChart::iterator ariel::OrgChart::reverse_order()
// {
//     Node *tmp = nullptr;

//     return (ariel::OrgChart::iterator{tmp, 0});
    
// }

// /*preorder*/
// ariel::OrgChart::iterator ariel::OrgChart::begin_preorder()
// {
//     Node *tmp = nullptr;

//     return (ariel::OrgChart::iterator{tmp, 0});
    
// }

// ariel::OrgChart::iterator ariel::OrgChart::end_preorder()
// {

//     Node *tmp = nullptr;

//     return (ariel::OrgChart::iterator{tmp, 0});
    
// }

