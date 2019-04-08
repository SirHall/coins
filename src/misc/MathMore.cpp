#include "MathMore.hpp"
#include <chrono>
#include <cmath>
using namespace std::chrono;

double Remap(
    double value, 
    double inMin, double inMax, 
    double outMin, double outMax){

    return ((value - inMin) / (outMin - inMin) * (outMax - inMax) + inMax);
}

unsigned long Factorial(unsigned long val){
    unsigned long fact = val;
    for(unsigned long i = val - 1; i > 1; i--)
        fact *= i;
    return fact;
}

unsigned long Pow(unsigned long n){
    unsigned long finalVal = 1;
    for(unsigned long i = 1; i <= n; i++)
        finalVal *= n;
    return finalVal;
}

/*unsigned long SearchSpace(u_char n){
    unsigned long searchSpace = 1;
    for(u_char i = 1; i <= n; i++){ //The power
        unsigned long add = n;
        for(u_char mul = 1; mul < i; mul++)
            add *= n;
        searchSpace += add;
    }
    return searchSpace;
}*/

double GetTime(steady_clock::time_point start){
    return GetTime(start, steady_clock::now());
}

double GetTime(steady_clock::time_point start, steady_clock::time_point now){
    steady_clock::duration duration = now - start;
    return double(duration.count()) * 
        steady_clock::period::num / steady_clock::period::den;
}
