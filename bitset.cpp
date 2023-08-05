#include "bitset.h"
#include <iostream>
#include <deque>
#include <string>
#include <cstring>
#include <climits>

static const int u_int_bits = 32;

Bitset::Bitset(const size_t s): m_arr(nullptr), m_size(s){
    size_t sz = (m_size + 31) / u_int_bits;
    m_arr = new unsigned int [sz];
    
    for(size_t i = 0; i < sz; ++i) {
        m_arr[i] = 0;
    }
}

Bitset::Bitset(long long val, const int s) : m_arr(nullptr), m_size(s) {
    size_t sz = (m_size + 31) / u_int_bits;
    m_arr = new unsigned int[sz];
    if(val > UINT_MAX) {
        for (size_t i = sz; i > 0; --i) {
            m_arr[i - 1] = val & UINT_MAX;
            val >>= u_int_bits;
        }

    } else{
        for(size_t i = sz; i > 0; --i) {
            m_arr[i - 1] = 0;
        }
        m_arr[sz -1] = val;
    }
}
    
Bitset::Bitset(const char* bts, const int s) : m_arr(nullptr), m_size(s), m_bts(bts) {
    unsigned int sz = ((m_size + 31)/u_int_bits);
    unsigned int i = 0, t {0};
    int j = strlen(m_bts) - 1;
    unsigned int val = 0;
  
    m_arr = new unsigned int [sz];
    for(size_t i = sz; i > 0; --i) {
        m_arr[i - 1] = 0;
    }
    try {    
        while (j > 0 && sz > 0 ){
            i = 0;
            while(i < u_int_bits && j >= 0) {
                if ('0' == m_bts[j]  || '1' == m_bts[j]) {
                    val = (val << 1) | (m_bts[j] - '0');// Convert character to integer (0 or 1) and add it to val
                    ++i;
                    --j;
                } else {
                         throw std::invalid_argument("Invalid argument: Non-binary argument");
                }
            }
                m_arr[sz - 1] = val;
                val = 0;
                --sz;
        }   
    }
    catch(const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
    }
}   

Bitset::Bitset(const std::string& bt, const int s) : m_arr(nullptr), m_size(s), m_bits(bt) {
    unsigned int sz = ((m_size + 31)/u_int_bits);
    unsigned int i = 0, t {0};
    int j = m_bits.size() - 1;
    unsigned int val = 0;
      
    m_arr = new unsigned int [sz];
    
    for(size_t i = sz; i > 0; --i) {
        m_arr[i - 1] = 0;
    }

    try {    
        while (j > 0 && sz > 0 ){
            i = 0;
            while(i < u_int_bits && j >= 0) {
                if ('0' == m_bits[j]  || '1' == m_bits[j]) {
                    val = (val << 1) | (m_bits[j] - '0');// Convert character to integer (0 or 1) and add it to val
                    ++i;
                    --j;
                } else {
                    throw std::invalid_argument("Invalid argument: Non-binary argument");
                }
            }
        m_arr[sz - 1] = val;
        val = 0;
        --sz;
        }   
    }
    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
} 

Bitset::~Bitset() {
        delete[] m_arr;
    }

    
void Bitset::print (std::ostream& os) const {
    std::deque <int> car {};
    int remaining_bits = m_size;
    int offset = (((m_size +31) / u_int_bits) * u_int_bits) - m_size;

    for(int i = (m_size +31) / u_int_bits - 1; i >= 0; --i) {
        unsigned int mask = m_arr[i];
        int carry {0};
        int bits_to_proc = std::min(remaining_bits, u_int_bits);

        for(int j = 0; j < bits_to_proc; ++j) {
            carry = (mask & 1);
            mask >>= 1;
            car.push_front(carry);
        }

        remaining_bits -= bits_to_proc;
    }

    for(auto num : car) {
        os << num;
    }
}

void Bitset::set(const int pos) {
    unsigned int mask {1};

    int rem_pos = pos;
     mask <<= (pos - 1);

    int t = ((m_size + 31) / u_int_bits) - 1;
    while(rem_pos > u_int_bits) {
        --t;
        rem_pos -= 32;
    }

    m_arr[t] |= mask;
}

void Bitset::reset (const int pos) {
    unsigned int mask {1};
    int rem_pos = pos;
    mask <<= (pos - 1);

    int t = ((m_size + 31) / u_int_bits) - 1;
    while(rem_pos > u_int_bits) {
        --t;
        rem_pos -= 32;
    }
    m_arr [t] &= ~mask;
}

void Bitset::set() {
    int t = (m_size + 31) / u_int_bits ;
    for(int i = 0; i < t; ++i) {
        m_arr[i] |= UINT_MAX;
    }
}

void Bitset::reset() {
    int t = (m_size + 31) / u_int_bits;
    for(int i = 0; i < t; ++i) {
        m_arr[i] &= 0;
    }
}
