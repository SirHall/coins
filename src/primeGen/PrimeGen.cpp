#include "PrimeGen.hpp"

PrimeGen::PrimeGen(){
    // primes.push_back(1);
    primes.push_back(1);
    primes.push_back(2);
    primes.push_back(3);
}

void PrimeGen::GeneratePrimes(unsigned int max){
    for(unsigned int i = primes[primes.size() - 1]; i <= max; i+=2){
        bool isPrime = true;
        //i = new number we're testing to see if it is a new prime number
        for(unsigned int j = 1; j < primes.size(); j++){
            if(i % primes[j] == 0){ //We found a prime!
                isPrime = false;
                break;
            }
        }
        if(isPrime)
            primes.push_back(i);
    }
}