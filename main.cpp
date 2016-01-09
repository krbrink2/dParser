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

class Node{
public:
// public attributes can be seen by anyone
    
    // returns expression assigned to this node
    string getExpression(){
        return expression;
    }
    
    // returns value represented by this expression
    // This is a pure virtual function: it must be defined by a child.
    num evaluate() = 0;
    
protected:    
// protected attributes can only be seen by their owner and its children
    string expression;    
    
private:
// private attributes can only be seen by their owner
    
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
