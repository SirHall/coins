#include "Entry.hpp"

Entry::Entry(){

}

// Entry::Entry(const Entry& other) :
//     amount(other.amount), minCoins(other.minCoins), maxCoins(other.maxCoins){
    
//     this->solutions = other.solutions;
// }

Entry::Entry(unsigned long totalAmount) : 
    amount(totalAmount), minCoins(1), maxCoins(totalAmount){

}

Entry::Entry(unsigned long totalAmount, unsigned long coinCount):
    amount(totalAmount), minCoins(coinCount), maxCoins(coinCount){

}

Entry::Entry(unsigned long totalAmount, unsigned long minimumCoins, 
    unsigned long maximumCoins):
        amount(totalAmount), minCoins(minimumCoins), maxCoins(maximumCoins){
}

// Entry& Entry::operator=(const Entry& other){
//     return std::ref(Entry(other);
// }

Entry::~Entry(){

}

void Entry::SetSolutions(unsigned long sols){
    // std::unique_lock lock(mut);
    solutions = sols;
}

unsigned long Entry::GetSolutions(){
    // std::shared_lock lock(mut);
    return solutions;
}

void Entry::SetIndex(unsigned int index){
    i = index;
}

unsigned long Entry::GetIndex(){
    return i;
}