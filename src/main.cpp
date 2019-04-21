#include <iostream>
#include "PrimeGen.hpp"
#include "Solver.hpp"
#include "Entry.hpp"
#include <chrono>
#include "MathMore.hpp"
#include <string>
#include <fstream>
using namespace std::chrono;

int main(int argc, char* argv[]){
    std::shared_ptr<PrimeGen> primes (new PrimeGen());
    
    std::shared_ptr<std::vector<Entry>> entries(
        new std::vector<Entry>()
    );
    
    std::string line = "";
    std::cout << argv[0] << '\n';
    std::ifstream file(std::string(argv[1]), std::ifstream::in);
    
    if(file.is_open()){
        std::cout << "Input lines:\n";
        while(std::getline(file, line)){
            line += ' ';
            std::vector<std::string> words({""});
            
            for(unsigned int i = 0; i < line.length(); i++){
                if(line[i] == ' ' || line[i] == '\t'){
                    words.push_back(std::string(""));
                    continue;
                }
                words[words.size() - 1] += line[i];
            }
            std::cout << '\t';
            for(auto word : words)
                std::cout << word << ' ';
            std::cout << '\n';
            switch(words.size()){
                case 2:
                    entries->push_back(Entry(std::stoi(words[0])));
                    break;
                case 3:
                    entries->push_back(Entry(
                        std::stoi(words[0]),
                        std::stoi(words[1])
                    ));
                    break;
                case 4:
                    entries->push_back(Entry(
                        std::stoi(words[0]),
                        std::stoi(words[1]),
                        std::stoi(words[2])
                        ));
                    break;
            }
        }
        file.close();
    }else{
        std::cout << "Could not find\n";
    }

    unsigned int highestPrime = 11; //Just a low, default prime number
    //Find highest prime that needs to be generated
    for(auto entry : *entries)
        if(entry.amount > highestPrime)
            highestPrime = entry.amount;

    auto clock_start = steady_clock::now();
    
    primes->GeneratePrimes(highestPrime);
#ifdef MT
//Generate using multithreading (Not Windows compatible)
    std::shared_ptr<std::vector<unsigned long>> solutions = 
        SolveMT(
            entries,
            primes,
            4
        );
#else
//Generate using a single thread (Windows compatible)
    std::shared_ptr<std::vector<unsigned long>> solutions(new std::vector<unsigned long> ());
    solutions->reserve(entries->size());
    for(auto entry : *entries){
        solutions->push_back(SolveSingle(std::ref(entry), std::ref(*primes)));
    }

#endif

    std::ofstream outputFile;
    outputFile.open("Output.txt");

    std::cout << "Completed in: " << GetTime(clock_start) << "s\n";
    for(unsigned long sol : *solutions){
        std::cout << '\t' << sol << "\n";
        outputFile << sol << '\n';
    }

    outputFile.close();
    
}
