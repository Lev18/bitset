#ifndef BITSET_H
#define BITSET_H

#include <string>

class Bitset {
private:
    unsigned int* m_arr; 
    size_t m_size;
    std::string m_bits;
    const char* m_bts;
    
public:    
    Bitset(const size_t s);
    Bitset(long long val, const int s) ;
    Bitset(const char* bts, const int s) ;
       
    Bitset(const std::string& bt, const int s) ;
    ~Bitset();

    void print (std::ostream& os) const;    
    void set(const int pos);
    void reset (const int pos);
    void set();
    void reset();
};
#endif
