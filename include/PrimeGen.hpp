#ifndef PrimeGen_hpp
#define PrimeGen_hpp

#include <vector>

class PrimeGen{
    private:
        std::vector<unsigned int> primes;
    
    public:
        PrimeGen();
        ~PrimeGen() = default;

        void GeneratePrimes(unsigned int max);

        unsigned int TotalPrimes(){
            return primes.size();
        }

        unsigned int GetPrime(unsigned int index){
            return primes[index];
        }
};

#endif