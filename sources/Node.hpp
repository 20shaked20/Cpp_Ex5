/**
 * @file Node.hpp
 * @author shaked levi
 * @brief Node.hpp header file
 * @version 0.1
 * @date 2022-05-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <vector>
#include <iostream>
#pragma once
namespace shaked
{
    class Node
    {
        /**
         * @brief each node has a : title, a father and his own kids map, to acess it on o(1).
         *
         */
    private:
        std::string _title;
        std::vector<Node *> _children;
        Node *_father;

    public:
        /**
         * @brief Construct a new Node object
         *
         * @param title
         * @param father
         */
        Node(std::string &title, Node *father);

        /**
         * @brief Construct a new Node object
         *
         * @param title
         */
        Node(std::string &title);

        /**
         * @brief Get the title object
         *
         * @return std::string
         */
        std::string get_title();

        /**
         * @brief Get the father object
         *
         * @return Node*
         */
        Node *get_father();

        /**
         * @brief Get the children object
         *
         * @return std::vector<Node*>
         */
        std::vector<Node *> get_children();

        /**
         * @brief add child to the node vector.
         *
         * @param new_child
         */
        void add_child(Node *new_child);

        /**
         * @brief Set the title object
         *
         * @param new_title
         */
        void set_title(std::string &new_title);

        /**
         * @brief search if the title exist in the curr node tree.
         *
         * @param title
         * @return Node*
         */
        Node *search_title_in_tree(std::string &title);

        friend std::ostream& operator<<(std::ostream& input, Node* const &node);
    };
}