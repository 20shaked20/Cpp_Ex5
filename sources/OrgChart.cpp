#include <iostream>
#include "OrgChart.hpp"



ariel::OrgChart::OrgChart() : _org_chart(nullptr) {}

ariel::OrgChart::~OrgChart(){}

ariel::OrgChart& ariel::OrgChart::add_root(std::string name)
{
    if (this->_org_chart == nullptr)
    {
        this->_org_chart = new Node(name);
    }
    else
    {
        std::__throw_logic_error("Tree Already Exists");
    }
    // this->string_to_node.insert(name,this->_org_chart);
    return *this;
}

ariel::OrgChart& ariel::OrgChart::add_sub(std::string root, std::string sub)
{   
    return *this;
}

std::ostream &ariel::operator<<(std::ostream &output, const ariel::OrgChart &chart)
{

    output << "Tmp";
    return output;
}

/*Iterator class implement*/

ariel::OrgChart::iterator::iterator(Node* &nodes, int type){
    
    this->nodes_to_iterate = std::move(nodes);
    this->_type = type;

}

std::string ariel::OrgChart::iterator::operator*() const{

    return this->nodes_to_iterate->get_title();

}

std::string* ariel::OrgChart::iterator::operator->() const{
    
    std::string *tmp;
    return tmp;
}

ariel::OrgChart::iterator& ariel::OrgChart::iterator::operator++(){ /* ++i */
    /*TODO: implement via the type*/
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
    Node *tmp = nullptr;

    return (ariel::OrgChart::iterator{tmp, 0});
    
}

ariel::OrgChart::iterator ariel::OrgChart::end_level_order()
{  
    Node *tmp = nullptr;

    return (ariel::OrgChart::iterator{tmp, 0});
    
}

/*Level order, diff name?*/
ariel::OrgChart::iterator ariel::OrgChart::begin()
{
    Node *tmp = nullptr;

    return (ariel::OrgChart::iterator{tmp, 0});
    
}

ariel::OrgChart::iterator ariel::OrgChart::end()
{
    Node *tmp = nullptr;

    return (ariel::OrgChart::iterator{tmp, 0});
    
}

/*reverse order*/
ariel::OrgChart::iterator ariel::OrgChart::begin_reverse_order()
{

    Node *tmp = nullptr;

    return (ariel::OrgChart::iterator{tmp, 0});
    
}

ariel::OrgChart::iterator ariel::OrgChart::end_reverse_order()
{
    Node *tmp = nullptr;

    return (ariel::OrgChart::iterator{tmp, 0});
    
}

/*preorder*/
ariel::OrgChart::iterator ariel::OrgChart::begin_preorder()
{
    Node *tmp = nullptr;

    return (ariel::OrgChart::iterator{tmp, 0});
    
}

ariel::OrgChart::iterator ariel::OrgChart::end_preorder()
{

    Node *tmp = nullptr;

    return (ariel::OrgChart::iterator{tmp, 0});
    
}

