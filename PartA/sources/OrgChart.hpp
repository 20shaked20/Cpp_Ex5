/**
 * @file OrgChart.hpp
 * @author shaked levi
 * @brief this is the header file for the OrgChart class
 * @version 0.1
 * @date 2022-05-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Node.hpp"
using namespace shaked;
#pragma once

namespace ariel
{

    class OrgChart
    {

    private:
        Node *_org_chart; /*head*/
        size_t _employee_count = 0;

        std::vector<Node*> _todelete;

    public:
        /**
         * @brief Construct a new Org Chart object
         *
         */
        OrgChart();

        /**
         * (IMPLEMENT)
         * @brief Copy Construct a new Org Chart object
         *
         * @param other
         */
        OrgChart(OrgChart &other);

        /**
         * (IMPLEMENT)
         * @brief Move Construct a new Org Chart object
         * 
         * @param other 
         */
        OrgChart(OrgChart &&other) noexcept;

        /**
         * @brief Destroy the Org Chart object
         *
         */
        ~OrgChart();

        /**
         * @brief
         *
         * @param root
         */
        OrgChart &add_root(std::string root);

        /**
         * @brief
         *
         * @param root
         * @param sub
         */
        OrgChart &add_sub(std::string root, std::string sub);
        
        /**
         * @brief (IMPLEMENT)
         *  overloads the operator =, which is copy assignment operator.
         * @param other 
         * @return OrgChart 
         */
        OrgChart& operator=(const OrgChart &other);

         /**
         * @brief (IMPLEMENT)
         *  move overloads the operator =, which is copy assignment operator.
         * @param other 
         * @return OrgChart 
         */
        OrgChart& operator=(OrgChart &&other) noexcept;

        /**
         * @brief override the operator '<<' which is the output operator cout
         * 
         * @param os
         * @param chart
         * @return ostream&
         */
        friend std::ostream &operator<<(std::ostream &output, const OrgChart &chart);

        /**
         * @brief iterator class, it will be implement for the 3 iterators using a flag.
         * 1 - level order.
         * 2 - reverse order.
         * 3 - preorder.
         *
         */
        class iterator
        {

        private:
            std::vector<Node *> nodes_to_iterate;
            int _type;
            size_t _node_pos;

        public:
            /**
             * @brief Construct a new iterator object
             *
             * @param head points to the head of the starting location
             * @param type which type to use:
             *  1 -> begin.
             *  0 -> end.
             */
            iterator(std::vector<Node *> &nodes, int type);

            /**
             * @brief return the string value
             *
             * @return std::string&
             */
            std::string operator*() const;

            /**
             * @brief return pointer to the string value
             *
             * @return std::string*
             */
            std::string *operator->() const;

            /**
             * @brief ++prefix
             *
             * @return iterator&
             */
            ariel::OrgChart::iterator &operator++(); /*switch case is here*/
            /**
             * @brief suffix++
             *
             * @return iterator&
             */
            ariel::OrgChart::iterator operator++(int); /*switch case is here*/

            /**
             * @brief it overloads the method '=='
             *
             * @param cpy another
             * @return true
             * @return false
             */
            friend bool operator==(const ariel::OrgChart::iterator &left, const ariel::OrgChart::iterator &right);
            /**
             * @brief it overloads the method '!='
             *
             * @param cpy another
             * @return true
             * @return false
             */
            bool operator!=(const ariel::OrgChart::iterator &cpy) const;
            
        };

        /**
         * @brief points to the first father and traverses as level order:
         * father - father - father
         * son - son - son ...
         * @return iterator_level_order
         */
        iterator begin_level_order();
        iterator end_level_order() const;

        /**
         * @brief points to the first father and traverses as level order:
         * father - father - father
         * son - son - son ...
         * (this is needed for the for each loop to compile, it is implemented by calling the:
         * 1. begin_level_order(), 2. end_level_order )
         * @return iterator_level_order
         */
        iterator begin();
        iterator end() const;

        /**
         * @brief points to the last child and traverses back wards as reverse order:
         * son - son - son
         * father - father - father ...
         * @return iterator_reverse_order
         */
        iterator begin_reverse_order();
        // iterator end_reverse_order();
        iterator reverse_order() const;

        /**
         * @brief deep traversal, is like dfs traversal, reminds a bit the binary preoder.
         *
         * @return iterator_preorder
         */
        iterator begin_preorder();
        iterator end_preorder() const;
    };
}