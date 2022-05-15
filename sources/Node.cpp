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

}

std::string shaked::Node::get_title(){

    return this->_title;
}

shaked::Node* shaked::Node::get_father(){
    
    return this->_father;

}

std::vector<shaked::Node*> shaked::Node::get_children(){

    return this->_children;
}

void shaked::Node::add_child(shaked::Node *new_child){

    if(new_child ->get_father()!=this){
        throw "Cant add new node, its not this child node";
    }
    _children.push_back(new_child);

}

void shaked::Node::set_title(std::string &new_title){

    this->_title = new_title;
}

shaked::Node* shaked::Node::search_title_in_tree(std::string &title){
    
    Node *temp = nullptr;
    return temp;
}

std::ostream& shaked::operator<<(std::ostream& input, shaked::Node* const &node){

    input << node->get_title();
    return input;

}