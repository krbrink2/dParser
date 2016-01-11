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
 * Non-method function definitions: not in a class
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
    
    // First: check if expression starts with opening paren
    if(expression[0] == '('){
        // If does not end with closing paren, found issue.
    }
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
    // Actually free this node
    delete ptr;    
    return;
}


/* main method
 * 
 */
int main(int argc, char** argv) {
    cout << "You have entered main()" << endl;
    
    // argc is 1 + number of program arguments
    // argv contains program name, followed by arguments
    // @TODO: check for number of arguments
    parse(root, argv[1]);
    root->evaluate();
    cleanup(root);
    
    return 0;
}

/* ================
 * Method definitions: functions in classes
 * ================ */

/* getChildren()
 * Returns pointer to array of children pointers.
 */
Node ** Node::getChildren(){
   return children; 
}

/* AddNode constructor
 */
AddNode::AddNode(string exp){
    expression = exp;
    children[0] = NULL;
    children[1] = NULL;    
}

/* AddNode::evaluate()
 * Returns num represented by this node
 */
num AddNode::evaluate(){
    //@TODO: implement
    return -1;
}

/* DivideNode constructor
 */
DivideNode::DivideNode(string exp){
    expression = exp;
    children[0] = NULL;
    children[1] = NULL;    
}

/* DivideNode::evaluate()
 * Returns num represented by this node
 */
num DivideNode::evaluate(){
    //@TODO: implement
    return -1;
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

/* MultiplyNode constructor
 */
MultiplyNode::MultiplyNode(string exp){
    expression = exp;
    children[0] = NULL;
    children[1] = NULL;    
}

/* MultiplyNode::evaluate()
 * Returns num represented by this node
 */
num MultiplyNode::evaluate(){
    //@TODO: implement
    return -1;
}

/* ParenNode constructor
 */
ParenNode::ParenNode(string exp){
    expression = exp;
    children[0] = NULL;
    children[1] = NULL;    
}

/* ParenNode::evaluate()
 * Returns num represented by this node
 */
num ParenNode::evaluate(){
    //@TODO: implement
    return -1;
}

/* SubtractNode constructor
 */
SubtractNode::SubtractNode(string exp){
    expression = exp;
    children[0] = NULL;
    children[1] = NULL;    
}

/* SubtractNode::evaluate()
 * Returns num represented by this node
 */
num SubtractNode::evaluate(){
    //@TODO: implement
    return -1;
}

