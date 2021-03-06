#include "Solver.hpp"
#include <memory>
#ifdef MT
    #include <future>
#endif
#include <stack>
#include <iostream>
#include <chrono>
#include "MathMore.hpp"
using namespace std::chrono;


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

//This function will not be globally avaliable
//and should not be avaliable outsie this source file
#ifdef MT
void SolveSingleMT(
    std::shared_ptr<std::vector<Entry>> entries, 
    std::shared_ptr<PrimeGen> primes, unsigned int *index,
    std::mutex *srcMut, std::mutex *destMut,
    std::shared_ptr<std::vector<unsigned long>> sols){
    
    Entry entry;
    bool moreEntries = true;

    while(moreEntries){
        moreEntries = true;
        {
            std::lock_guard<std::mutex> lock(*srcMut);
            if(*index < entries->size()){
                entry = entries->at(*index);
                entry.SetIndex(*index);
                (*index)++;
                // std::cout << "Index: " << entry.GetIndex() << "\n";
            }else{
                moreEntries = false;
            }
        }

        if(moreEntries){
            unsigned long solutions = SolveSingle(entry, *primes);
            // std::cout << "Found: " << solutions << "sols\n";
            {
                std::lock_guard<std::mutex> lock(*destMut);
                (*sols)[entry.GetIndex()] = solutions;
            }
        }
    }

    // {
    //     std::lock_guard<std::mutex> lock(*mut);
    //     std::cout << "Before\n";
    //     *sols = *sols + solutions; 
    // }

    // return solutions;
}
#endif

#ifdef MT
//Solves a single entry, returns list of solution counts
 std::shared_ptr<std::vector<unsigned long>> SolveMT(
    std::shared_ptr<std::vector<Entry>> entries, 
    std::shared_ptr<PrimeGen> primes, unsigned int threads){
    
    std::mutex *srcMut = new std::mutex();
    std::mutex *destMut = new std::mutex();
    
    std::shared_ptr<std::vector<unsigned long>> sols(
        new std::vector<unsigned long>());
    sols->reserve(entries->size()); //It's usually good to reserve space first
    sols->resize(entries->size()); //Prepare the size of this array
    unsigned int *index =  new unsigned int(0);

    if(threads == 0) //Don't start any new threads
        threads = 1;

    std::vector<std::thread*> liveThreads;

    for(unsigned int i = 0; i < threads; i++){
        std::thread *th = 
            new std::thread(SolveSingleMT, entries, primes, 
                index, srcMut, destMut, sols);
        // liveThreads
        liveThreads.push_back(th);
    }

    for(auto thr : liveThreads)
        thr->join();


    return sols;
}
#endif

unsigned long cycles = 0;

unsigned int SolveSingle(Entry &entry, PrimeGen &primes){
    unsigned int solutions = 0;
    //for(unsigned int i = entry.minCoins; i <= entry.maxCoins; i++)
    cycles = 0;
    auto clock_start = steady_clock::now();
    
    solutions += SolveSingleRec(entry.amount, std::ref(primes), 0, 
        entry.maxCoins, entry.minCoins);
    

    std::cout <<
        "Problem:   " << entry.amount << ' ' << entry.minCoins << ' ' << 
            entry.maxCoins << '\n' <<
        "Cycles:    " << cycles << '\n' <<
        "Solutions: " << solutions << '\n' <<
        "Time:      " << GetTime(clock_start) << "\n\n";
    
    // std::cout << entry.minCoins << '\t' << cycles << '\n';
    

    return solutions;
}

unsigned int SolveSingleRec(
    unsigned int totAmount, PrimeGen &primes, 
    unsigned int primeIndex, unsigned int spacesLeft, unsigned int spacesLeftMin){

    if(spacesLeft == 0 || primes.GetPrime(primeIndex) > totAmount)
        return 0;

    unsigned int solutions = 0;    
    //spacesLeft--;
    // unsigned long subproblems = 0;


    for(unsigned int i = primeIndex; i < primes.TotalPrimes(); i++){
        if(primes.GetPrime(i) > totAmount)
            break;
        
        cycles++;

        //We've reached the end and found a solution
        if(spacesLeftMin == 1 && totAmount == primes.GetPrime(i))
            solutions++;

        if(spacesLeft > 0){
            // for(unsigned int j = 0; j < spacesLeft; j++){
                solutions += SolveSingleRec(
                    totAmount - primes.GetPrime(i),
                    std::ref(primes), i, spacesLeft - 1, 
                    spacesLeftMin > 1 ? spacesLeftMin - 1 : 1
                );
            // }
        }
        // subproblems++;
    }

    return solutions;
}