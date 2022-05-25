/**
 * @file Node.cpp
 * @author shaked levi
 * @brief Node implement class file
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Node.hpp"

shaked::Node::Node(std::string &title, shaked::Node *father){

    this->_title = std::move(title);
    this->_father = father;

}

shaked::Node::Node(std::string &title){

    this->_title = std::move(title);
    this->_father = nullptr;

}

std::string shaked::Node::get_title(){

    return this->_title;
}

shaked::Node* shaked::Node::get_father(){
    
    return this->_father;

}

std::vector<shaked::Node*> shaked::Node::get_sub_employees(){

    return this->_sub_employees;
}

void shaked::Node::add_sub_employee(shaked::Node *new_sub){

    if(new_sub ->get_father()!=this){
        throw "Cant add new node, its not this child node";
    }
    _sub_employees.push_back(new_sub);

}

void shaked::Node::set_title(std::string &new_title){

    this->_title = new_title;
}

shaked::Node* shaked::Node::search_title_in_tree(std::string &title){
    
    if( get_title() == title){
        return this;
    }
    Node *ans = nullptr;
    for(Node *emp : get_sub_employees()){

        ans = emp->search_title_in_tree(title);
        if(ans != nullptr){
            return ans;
        }
    }
    return nullptr;
}

std::ostream& shaked::operator<<(std::ostream& input, shaked::Node* const &node){

    input << node->get_title();
    return input;

}