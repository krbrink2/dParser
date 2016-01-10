/*
 *  dParser
 */

/* 
 * File:   main.cpp
 * Author: Kyle
 *
 * Created on January 8, 2016, 6:01 PM
 */

#include <cstdlib>
#include <iostream>
//#include <string>

#include "dmath.h"

using namespace std;

// Represents a node on the expression tree.
// Because node has a pure virtual function, it is an abstract class, and thus 
// cannot have any instances. Only its children can be instantiated.
class Node{
public:
// public attributes can be seen by anyone
    
    // returns expression assigned to this node
    string getExpression(){
        return expression;
    }
    
    // returns value represented by this expression
    // This is a pure virtual function: it must be defined by a child.
    virtual num evaluate() = 0;
    
    // Idea:
    // We may want to add a function that returns an array of pointers to 
    // children nodes, so we can easily navigate the tree for cleanup.
    virtual Node* getChildren() = 0;
    
protected:    
// protected attributes can only be seen by their owner and its children
    // string representing the mathematical expression for this node
    string expression;    
    // Pointers to children nodes. NULL if child does not exist.
    Node* children[2]; 
    
private:
// private attributes can only be seen by their owner
    
};

class LiteralNode : public Node
{
    public:
        /*LiteralNode constructor: stores expression.*/
        LiteralNode(string exp);
        /*getNum returns the num stored in this literal.*/
        num getValue();
    private:
        /*value contains the num that should be represented by expression.
            May not be necessary since evaluate() should return value anyway.*/
        num value;
};



/*
 * 
 */
int main(int argc, char** argv) {

    cout << "TOP KEK 2016" << endl;
    int num_men_at_arms = 5;
    for(int i = 0; i < num_men_at_arms; i++){
        cout << "No, mi'lord!" << endl;
    }
    
    function();
    
    return 0;
}

LiteralNode::LiteralNode(string exp)
{
    expression = exp;
}

