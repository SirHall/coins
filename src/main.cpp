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
    //std::cout << argv[0] << 'n';
    std::ifstream file(std::string(argv[1]), std::ifstream::in);
    
    if(file.is_open()){
        while(std::getline(file, line)){
            line += ' ';
            std::vector<std::string> words({""});
            unsigned int wordIndex = 0;
            
            for(unsigned int i = 0; i < line.length(); i++){
                if(line[i] == ' ' || line[i] == '\t'){
                    std::cout << words[words.size() - 1] << '\n';
                    words.push_back(std::string(""));
                    continue;
                }
                words[words.size() - 1] += line[i];
            }
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
