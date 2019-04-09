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
            // Entry(300, 10, 15),
            // Entry(300, 10, 15),
            // Entry(300, 10, 15),
            // Entry(300, 12),
            // Entry(300, 11),
            // Entry(300, 10, 15),
            // Entry(300, 10, 15),
            // Entry(300, 10, 15),
            // Entry(300, 12),
            // Entry(300, 11)
            Entry(5),
            Entry(6, 2, 5),
            Entry(6, 1, 6),
            Entry(8, 3),
            Entry(8, 2, 5),
            Entry(20, 10, 15),
            Entry(100, 5, 10),
            Entry(100, 8, 25),
            Entry(300, 12),
            Entry(300, 10, 15)
        })
    );

//     5
// 6 2 5
// 6 1 6
// 8 3
// 8 2 5
// 20 10 15
// 100 5 10
// 100 8 25
// 300 12
// 300 10 15


    auto clock_start = steady_clock::now();
    
    primes->GeneratePrimes(500);
     std::shared_ptr<std::vector<unsigned long>> solutions = 
        SolveMT(
            entries,
            primes,
            4
        );

    std::cout << "\tCompleted in: " << GetTime(clock_start) << "s\n";
    for(unsigned long sol : *solutions){
        std::cout << sol << "\n";
    }
}