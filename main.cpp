#include "bitset.h"
#include <iostream>
std::ostream& operator<<(std::ostream& os, const Bitset& bs) {
    bs.print(os);
    return os;
}
int main(){
    std::string st = "";
    Bitset bs(145, 33);
    bs.reset(31);
    std::cout << bs << std::endl;
  return 0;
}
