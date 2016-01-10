/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include "dmath.h"

using namespace std;

void function(){
    cout << "This is in function()!" << endl;
    cout << "I added this line!" << endl;
}

num stringToNum(string s)
{    
<<<<<<< HEAD
    return strtod(s.c_str(), NULL);
=======
    return stod(s);
>>>>>>> 9538c18ba812e53f9abe0e055a277c4f5a059dac
}