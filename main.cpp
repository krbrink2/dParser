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
#include <cctype>

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
 * Non-method function declarations
 * ================ */

void error(string prompt);

int parse(Node * &ptr, string expression);

void cleanup(Node * ptr);

char getCloser(char opener);

bool isOpener(char c);

bool isCloser(char c);

int findCloser(string s, int openerIndex);

/* ================
 * Non-method function definitions: not in a class
 * ================ */

/* Allows for a custom prompt to be printed to
 * give the user more useful feedback.
 */
void error(string prompt)
{
    cout << prompt << endl;
    cleanup(root);
    exit(EXIT_FAILURE);
}

/* getCloser returns the closing parenthesis corresponding to the given opening
 * parenthesis. ( -> ), { -> }, [ -> ]. If no proper opener was given, then
 * NULL is returned.
 */
char getCloser(char opener)
{
    if (opener == '(')
    {
        return ')';
    }
    if (opener == '{')
    {
        return '}';
    }
    if (opener == '[')
    {
        return ']';
    }
    
    return (char)NULL;
}

/* isOpener returns whether or not the input char is an opening parenthesis 
 * or not.
 */
bool isOpener(char c)
{
    if (c == '(' || c == '{' || c == '[')
    {
        return true;
    }
    
    return false;
}

bool isCloser(char c)
{
    if (c == ')' || c == '}' || c == ']')
    {
        return true;
    }
    
    return false;    
}

/* findCloser returns the location in the string s of the closing parenthesis
 * that balances the opening parenthesis at openerIndex. Openers: (, {, and [.
 * Closers: ), }, and ]. If no correct closing parenthesis is found, -1 is
 * returned. If a non-opener char was given, -2 is returned.
 */
int findCloser(string s, int openerIndex)
{
    /*Define the target char (the closing parenthesis we're looking for).*/
    char target = getCloser(s[openerIndex]);
    if (target == (char)NULL)
    {
        return -2;
    }
    /*Search across s for the appropriate closing parenthesis.*/
    for (int x = openerIndex + 1; x < s.length(); x++)
    {
        /*If the current char matches the target char, then the closer has been
            found. Return x.*/
        if (s[x] == target)
        {
            return x;
        }
        /*If the current char is another opening parenthesis, then we must
            traverse that opener/closer pair to avoid eliminate it from the
            possible solutions.*/
        if (isOpener(s[x]))
        {
            x = findCloser(s, x);
            /*-1 may have been returned if no closer was found. In this case,
                also return -1.*/
            if (x == -1)
            {
                return -1;
            }
        }
    }
    /*If no closer has been found by the end of the string, then the string
            is unbalanced. Return -1.*/
        return -1;
}

/* Given a node pointer and an expression, parse() determines the next
 * operation to be performed and the substring(s) to perform it on. Allocates
 * a new derived node and sets ptr to point to it, then calls parse on any child
 * pointers with their expression strings.
 * Returns 0 on success.
 */
int parse(Node * &ptr, string expression){
    //@TODO; implement generalized parsing of expressions.
    /* Idea: create function to find the first token (first Literal/Paren), 
     * second token (operation/parens), and third token (the rest of the
     * expression).
     */
    /* One token present -> Literal/Paren. 
     * Parenthesis found before an op +,-,*,or / is found -> Mult (special case)
     * Third token begins with (, {, or [ -> Parens. 
     * Otherwise, handle the binary op normally.
     */
    
    // Sanity checks
    // Empty string
    if(expression.empty()){
        error("Error: parse(...) passed empty string!");
    }
    // If does NOT open with opening paren, nor literal
    if( !isdigit(expression.front()) && !isOpener(expression.front()) ){
        error("Error in parse(...): invalid opening character");
    }
    // IF does NOT end with closing paren, nor literal
    if( !isdigit(expression.back()) && !isCloser(expression.back()) ){
        error("Error in parse(...): invalid ending character");
    }
        
    // First, look for +, - outside parens.
    int i;
    for(i = 0; i < expression.length(); i++){
        char curChar = expression[i];
        
        // skip parentheses
        if(isOpener(curChar)){
            i = findCloser(expression, i);
            if(i < 0){
                error("Error: unbalanced parentheses!");
            }
            continue;
        }
        
        // Addition
        if(curChar == '+'){
            ptr = new AddNode(expression);
            Node ** children = ptr->getChildren();
            // This should account for erroneous first/last '+'.
            parse(children[0], expression.substr(0,i));
            parse(children[1], expression.substr(i+1, expression.length() - (i + 1)));
            return 0;
        }
        // Subtraction
        if(curChar == '-'){
            ptr = new SubtractNode(expression);
            Node ** children= ptr->getChildren();
            // This should account for erroneous first/last '-'.
            parse(children[0], expression.substr(0,i));
            parse(children[1], expression.substr(i+1, expression.length() - (i + 1)));
            return 0;
        }
    }
    // No +, - found. Look for * or / operators.
    for(i = 0; i < expression.length(); i++){
        char curChar = expression[i];
        
        // skip parentheses
        if(isOpener(curChar)){
            i = findCloser(expression, i);
            if(i < 0){
                error("Error: unbalanced parentheses!");
            }
            continue;
        }
        
        // Multiplication, via '*' operator
        if(curChar == '*'){
            ptr = new MultiplyNode(expression);
            Node ** children = ptr->getChildren();
            // This should account for erroneous first/last '*'.
            parse(children[0], expression.substr(0,i));
            parse(children[1], expression.substr(i+1, expression.length() - (i + 1)));
            return 0;
        }
        // Division
        if(curChar == '/'){
            ptr = new DivideNode(expression);
            Node ** children= ptr->getChildren();
            // This should account for erroneous first/last '/'.
            parse(children[0], expression.substr(0,i));
            parse(children[1], expression.substr(i+1, expression.length() - (i + 1)));
            return 0;
        }
    }
    // No *, / found. Look for literal-paren adjacency multiplicaiton,
    //  such as (5 + 8)14
    for(i = 0; i < expression.length(); i++){
        char curChar = expression[i];
        
        // skip parentheses
        if(isOpener(curChar)){
            i = findCloser(expression, i);
            if(i < 0){
                error("Error: unbalanced parentheses!");
            }
            continue;
        }
        
        // if curChar is nota digit, continue
        if(!isdigit(curChar)){
            continue;
        }
        
        // curChar is a digit:
        //  See if it is adjacent to a paren
        // Check if curChar trails a parentheses pair
        // But NOT at the begining
        if(i == 0){
            continue;
        }
        if(isCloser(expression[i - 1])){
            ptr = new MultiplyNode(expression);
            Node ** children = ptr->getChildren();
            parse(children[0], expression.substr(0, i));
            parse(children[1], expression.substr(i, expression.length() - i));
            return 0;
        }
        // Check if curChar leads a parentheses pair
        // But NOT at the end
        if(i == expression.length() - 1){
            continue;
        }
        if(isOpener(expression[i + 1])){
            ptr = new MultiplyNode(expression);
            Node ** children = ptr->getChildren();
            parse(children[0], expression.substr(0, i + 1));
            parse(children[1], expression.substr(i+1, expression.length()-(i+1)));
            return 0;
        }
    }
        
    // No literal-adjacency multiplication.
    // Must be full-paren wrapped expression.
    // Make sure it is.
    if(!isOpener(expression.front()) || !isCloser(expression.back())){
        // Something went wrong with parsing
        error("Parsing error: algorithm did not determine statement type!");
        return -1;
    }
    else{
        // Statement must be wrapped in parentheses
        ptr = new ParenNode(expression);
        Node ** children = ptr->getChildren();
        parse(children[0], expression.substr(1, expression.length() - 2));
        return 0;
    }
    
    return -1;      // unreachable line
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
    cout << "argc: " << argc << endl;
    if(argc < 2){
        cout << "Usage: ./dparser {expression}" << endl;
        return 0;
    }        
    
    /* Tests for findCloser:
     * Test 1 - Test if findCloser returns -2 when given a non-opener char.
     * Test 2 - Test if findCloser returns -1 for an unbalanced string.
     * Test 3 - Test if findCloser returns the location of the closer given its
     * corresponding opener in a balanced string.
     */
        //Test 1: Should return -2.
    string testString = "abc(def";
    cout << endl << "Test 1: " << findCloser(testString, 0);
        //Test 2: should return -1.
    cout << endl << "Test 2: " << findCloser(testString, 3);
        //Test 3: should return 7.
    testString += ")ghi";
    cout << endl << "Test 3: " << findCloser(testString, 3);  
    
    // Idea: may want to strip expression of spaces before parsing
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

/* Constructor for LiteralNode. Defines expression. Both children are null since
 a Literal will never have any children.
 */
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
    children[0] = NULL;
    children[1] = NULL;
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
    children[0] = NULL;
    children[1] = NULL;
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
    children[0] = NULL;
    children[1] = NULL;
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
    children[0] = NULL;
    children[1] = NULL;
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
    children[0] = NULL;
    children[1] = NULL;
}

/*ParenNode evaluates by evaluating its child.*/
num ParenNode::evaluate()
{
    return children[0]->evaluate();
}