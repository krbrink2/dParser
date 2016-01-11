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
    return strtod(s.c_str(), NULL);
}

/* sqrt estimates the square root of N using the Babylonian algorithm for
 * calculating roots. The user may enter a degree of precision.
 */
double sqrt(double N, int precision)
{
    double current = N / 2;
    if (current == 0)
    {
        return 0;
    }
    
    for (int i = 0; i < precision; i++)
    {
        current = 0.5 * (current + (N / current));
    }
    
    return current;
}
/* The default sqrt function assumes precision = 10.*/
double sqrt (double N)
{
    return sqrt(N, 10);
}