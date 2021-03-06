#ifndef Entry_hpp
#define Entry_hpp

// #include <thread>
// #include <shared_mutex>
// #include <mutex>

class Entry{
    private:
        unsigned long 
            solutions = 0,
            i = 0; //Stores order index, for multithreading
        // mutable std::shared_mutex mut;

    public:
        //We can make these public as they are immutable
        unsigned long amount, minCoins, maxCoins;
        
        Entry();

        // Entry(const Entry& other);

        Entry(unsigned long totalAmount);

        Entry(unsigned long totalAmount, unsigned long coinCount);

        Entry(unsigned long totalAmount, unsigned long minimumCoins, 
            unsigned long maximumCoins);

        ~Entry();

        // Entry& operator=(const Entry&);

        void SetSolutions(unsigned long sols);
        unsigned long GetSolutions();

        void SetIndex(unsigned int index);
        unsigned long GetIndex();

};

#endif