#include "Solver.hpp"
#include <memory>
#include <future>
#include <stack>
#include <iostream>

// Solver::Solver(std::vector<Entry> allEntries) {
    
// }

//Solves the problems and returns all the answers
// std::unique_ptr<std::vector<unsigned int>> Solver::Solve(){
    // std::unique_ptr<std::vector<unsigned int>> answers
    //     (new std::vector<unsigned int>());

    // answers->reserve(entries.size()); //Make this the size of entries

    // for(Entry entry : entries){
    //     // answers->push_back(this->SolveSingleMT(entry, 0));
    // }

    // return std::move(answers);
// }

unsigned int SolveSingleMT(
    std::shared_ptr<std::vector<Entry>> entries, 
    std::shared_ptr<PrimeGen> primes,
    std::shared_ptr<std::mutex> mut,
    std::shared_ptr<unsigned int> sols){
    
    Entry entry;
    bool moreEntries = true;
    unsigned int solutions = 0;

    while(moreEntries){
        std::cout << "Before\n";
        moreEntries = true;
        {
            std::lock_guard<std::mutex> lock(*mut);
            if(entries->size() > 0){
                entry = entries->at(entries->size() - 1);
                entries->pop_back();
            }else{
                moreEntries = false;
            }
        }

        if(moreEntries){
            solutions += SolveSingle(entry, *primes);
        }
    }

    {
        std::lock_guard<std::mutex> lock(*mut);
        *sols += solutions; 
    }

    return solutions;
}

//Solves a single entry
unsigned int SolveMT(
    std::shared_ptr<std::vector<Entry>> entries, 
    std::shared_ptr<PrimeGen> primes, unsigned int threads){
    
    std::shared_ptr<std::mutex> mut;
    std::shared_ptr<unsigned int> sols;

    if(threads == 0) //Don't start any new threads
        threads = 1;
        // return SolveSingle(std::ref(entry), std::ref(primes));

    std::vector<std::thread*> liveThreads;

    for(unsigned int i = 0; i < threads; i++){
        std::thread *th = 
            new std::thread(SolveSingleMT, entries, primes, mut, sols);
        // liveThreads
        liveThreads.push_back(th);
    }

    for(auto thr : liveThreads)
        thr->join();

    unsigned int solsCopy = *sols;

    return solsCopy;
}

unsigned int SolveSingle(Entry &entry, PrimeGen &primes){
    unsigned int solutions = 0;
    for(unsigned int i = entry.minCoins; i <= entry.maxCoins; i++)
        solutions += SolveSingleRec(entry.amount, std::ref(primes), 0, i);
    return solutions;
}

unsigned int SolveSingleRec(
    unsigned int totAmount, PrimeGen &primes, 
    unsigned int primeIndex, unsigned int spacesLeft){
    
    if(spacesLeft == 0 || primes.GetPrime(primeIndex) > totAmount)
        return 0;

    unsigned int solutions = 0;    
    spacesLeft--;
    
    for(unsigned int i = primeIndex; i < primes.TotalPrimes(); i++){
        if(primes.GetPrime(i) > totAmount)
            break;
        //We've reached the end and found a solution
        if(spacesLeft == 0 && totAmount == primes.GetPrime(i))
            return 1;

        if(spacesLeft > 0){
            // for(unsigned int j = 0; j < spacesLeft; j++){
                solutions += SolveSingleRec(
                    totAmount - primes.GetPrime(i),
                    std::ref(primes), i, spacesLeft 
                );
            // }
        }
    }
    return solutions;
}