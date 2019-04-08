#include <iostream>
#include "PrimeGen.hpp"
#include "Solver.hpp"
#include "Entry.hpp"
#include <chrono>
#include "MathMore.hpp"
using namespace std::chrono;

int main(int argc, char* argv[]){
    std::shared_ptr<PrimeGen> primes (new PrimeGen());
    
    std::shared_ptr<std::vector<Entry>> entries(
        new std::vector<Entry>({
            Entry(300, 10, 15),
            Entry(300, 10, 15),
            Entry(300, 10, 15),
            Entry(300, 10, 15)
        })
    );

    auto clock_start = steady_clock::now();
    
    primes->GeneratePrimes(500);
    unsigned int solutions = 
        SolveMT(
            entries,
            primes,
            4
        );

    std::cout << "Found: " << solutions << 
        "\t\t In: " << GetTime(clock_start) << "s\n";
}