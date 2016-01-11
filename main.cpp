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
#include <string>

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
    
    // Returns pointer to member array children. Will be double pointer.
    Node ** getChildren();
    
    // frees children pointers
    void freeChildren();
    
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
        // Inherited from parent class
        num evaluate();
    private:
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

/*root will point to the root Node of the tree which will be constructed by
    parse.*/
Node * root;

/* ================
 * Function definitions
 * ================ */

/* Given a node pointer and an expression, parse() determines the next
 * operation to be performed and the substring(s) to perform it on. Allocates
 * a new derived node and sets ptr to point to it, then calls parse on any child
 * pointers with their expression strings.
 */
num parse(Node * &ptr, string expression){
    //@TODO; implement generalized parsing of expressions.
    /*Idea: create function to find the first token (first Literal), 
        second token (operation/parens), and third token (the rest of the
        expression).*/
    /*One token present -> Literal. Parenthesis found before an op +,-,*, or /
        is found -> Mult (special case). Third token begins with (, {, or [ ->
        Parens. Otherwise, handle the binary op normally*/
    
    /*Assuming input belongs to a LiteralNode (FIX LATER):*/
    LiteralNode* nextNode = new LiteralNode(expression);
    ptr = nextNode;
    return ptr->evaluate();
}

/* cleanup
 * Given a pointer to a node, frees that subtree.
 * To free entire tree, call cleanup(root);
 */
void cleanup(Node * ptr){
    // Given NULL?
    if(!ptr){
        return;
    }
    // recursively cleanup children
    Node ** children = ptr->getChildren();
    cleanup(children[0]);
    cleanup(children[1]);
    // Actually free children nodes
    ptr->freeChildren();
    
    return;
}


/* main method
 * 
 */
int main(int argc, char** argv) {
    cout << "You have entered main()" << endl;
    
    /*Test function().*/
    cout << endl << "function() test: " << endl;
    function();
    
    /*Test stringToNum.*/
    cout << endl << "stringToNum test: " << endl;
    string strang = "2.2221111";
    cout << stringToNum(strang);
    
    /*Test construction of LiteralNode.*/
    cout << endl << "LiteralNode construction test: " << endl;
    LiteralNode* testNode = new LiteralNode("2.12345");
    cout << parse(root, testNode->getExpression());
    
    cleanup(testNode);
    cleanup(root);
    
    return 0;
}

/*getChildren()
 * Returns pointer to array of children pointers.
 */
Node ** Node::getChildren(){
   return children; 
}

// ONLY deletes children of this node. NOT recursive.
void Node::freeChildren(){
    delete children[0];
    delete children[1];
}


/* Constructor for LiteralNode. Defines expression. Both children are null since
    a Literal will never have any children.*/
LiteralNode::LiteralNode(string exp)
{
    expression = exp;
    children[0] = NULL;
    children[1] = NULL;
}

/*Returns expression represented as a num type*/
num LiteralNode::evaluate()
{
    return stringToNum(expression);
}


/*Constructor for AddNode. Defines expression.*/
AddNode::AddNode(string exp)
{
    expression = exp;
}

/*AddNode evaluates by adding together its two children.*/
num AddNode::evaluate()
{
    return children[0]->evaluate() + children[1]->evaluate();
}


/*Constructor for SubtractNode. Defines expression.*/
SubtractNode::SubtractNode(string exp)
{
    expression = exp;
}

/*SubtractNode evaluates by subtracting the right child from the left child.*/
num SubtractNode::evaluate()
{
    return children[0]->evaluate() - children[1]->evaluate();
}


/*Constructor for MultiplyNode. Defines expression.*/
MultiplyNode::MultiplyNode(string exp)
{
    expression = exp;
}

/*MultiplyNode evaluates by multiplying its two children together.*/
num MultiplyNode::evaluate()
{
    return children[0]->evaluate() * children[1]->evaluate();
}


/*Constructor for DivideNode. Defines expression.*/
DivideNode::DivideNode(string exp)
{
    expression = exp;
}

/*DivideNode evaluates by dividing the left child by the right child.*/
num DivideNode::evaluate()
{
    return children[0]->evaluate() / children[1]->evaluate();
}


/*Constructor for ParenNode. Defines expression.*/
ParenNode::ParenNode(string exp)
{
    expression = exp;
}

/*ParenNode evaluates by evaluating its child.*/
num ParenNode::evaluate()
{
    return children[0]->evaluate();
}