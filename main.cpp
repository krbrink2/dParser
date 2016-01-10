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

/* ================
 * Globals and class declarations
 * ================ */

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
        // Inherited from parent class
        num evaluate();
    private:
        /*value contains the num that should be represented by expression.
            May not be necessary since evaluate() should return value anyway.*/
        num value;
};

class ParenNode : public Node{
public:
    // constructor
    ParenNode(string exp);
    // inherited from parent class
    num evaluate();
};

class AddNode : public Node{
public:
    // constructor
    AddNode(string exp);
    // inherited from parent class
    num evaluate();
};

class SubtractNode : public Node{
public:
    // constructor
    SubtractNode(string exp);
    // inherited from parent class
    num evaluate();
};

class MultiplyNode : public Node{
public:
    // constructor
    MultiplyNode(string exp);
    // inherited from parent class
    num evaluate();
};

class DivideNode : public Node{
public:
    // constructor
    DivideNode(string exp);
    // inherited from parent class
    num evaluate();
};

/* ================
 * Function definitions
 * ================ */

/* Given a node pointer and an expression, parse() determines the next
 * operation to be performed and the substring(s) to perform it on. Allocates
 * a new derived node and sets ptr to point to it, then calls parse on any child
 * pointers with their expression strings.
 */
num parse(Node * &ptr, string expression){
    //@TODO; implement
    return -1;
}

/* main method
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

/* Constructor for LiteralNode
 */
LiteralNode::LiteralNode(string exp)
{
    expression = exp;
}

/*Returns expression represented as a num type*/
num LiteralNode::evaluate(){
    //@TODO: write
}
