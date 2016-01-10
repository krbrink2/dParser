/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <string>
#include "dmath.h"

using namespace std;

void function(){
    cout << "This is in function()!" << endl;
    cout << "I added this line!" << endl;
}

num stringToNum(string s)
{    
    return stod(s, NULL);
}