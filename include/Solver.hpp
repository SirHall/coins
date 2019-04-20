#ifndef Solver_hpp
#define Solver_hpp

#include <vector>
#include "Entry.hpp"
#include <memory>
#include "PrimeGen.hpp"

// class Solver{
//     private:
//         // std::queue<Entry> entries;
//         // std::queue<Entry> finishedEntries;
//     public:
//         Solver(std::vector<Entry> allEntries);
//         ~Solver() = default;

//         //Solves the problems and returns all the answers
//         std::unique_ptr<std::vector<Entry>> Solve();

// };

//Solves a single entry with multithreading
#ifdef MT
std::shared_ptr<std::vector<unsigned long>> SolveMT(
    std::shared_ptr<std::vector<Entry>> entries, 
    std::shared_ptr<PrimeGen> primes, unsigned int threads);
#endif

//Solves a single entry without multithreading
unsigned int SolveSingle(Entry &entry, PrimeGen &primes);

unsigned int SolveSingleRec(
    unsigned int totAmount, PrimeGen &primes, 
    unsigned int primeIndex, unsigned int spacesLeft, unsigned int spacesLeftMin);

#endif
