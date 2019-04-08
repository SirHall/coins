#ifndef MathMore_hpp
#define MathMore_hpp

#include <chrono>
using namespace std::chrono;
#include <cmath>

double Remap(
    double value, 
    double inMin, double inMax, 
    double outMin, double outMax);
    
//No I will not be using recursion, too many allocations
unsigned long Factorial(unsigned long val);

unsigned long Pow(unsigned long n);

//unsigned long SearchSpace(u_char n);

double GetTime(steady_clock::time_point start);
double GetTime(steady_clock::time_point start, steady_clock::time_point now);


#endif
