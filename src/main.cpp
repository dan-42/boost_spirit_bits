#include <vector>
#include <iostream>
#include <cstdint>
#include <string>
#include <bitset>


#include <detail/bit_field.hpp>

/**
 *
 * this struct must only use one byte!
 *
 */
struct BitField {
  uint8_t type : 4;
  uint8_t flag1 : 1;
  uint8_t flag2 : 1;
  uint8_t flag3 : 1;
  uint8_t flag4 : 1;

};

  
  void print(const BitField& bf) {

    std::cout << "type: " << std::to_string((int)bf.type) << std::endl;

    std::cout << "flag1: ";
    if(bf.flag1) { std::cout << "true";  }    
    else { std::cout << "false" ;  }    
    std::cout  << std::endl;

    std::cout << "flag2: ";
    if(bf.flag2) { std::cout << "true";  }    
    else { std::cout << "false" ;  }    
    std::cout  << std::endl;

    std::cout << "flag3: ";
    if(bf.flag3) { std::cout << "true";  }    
    else { std::cout << "false" ;  }    
    std::cout  << std::endl;

    std::cout << "flag4: ";
    if(bf.flag4) { std::cout << "true";  }    
    else { std::cout << "false" ;  }    
    std::cout  << std::endl;
  }


int main() {


  BitField bf;
  
  std::string data;
  data.push_back(0b10101010);
  std::cout << "data(" <<  data.size() << ") " << (std::bitset<8>)data[0] << std::endl;

  auto start = data.begin();
  auto end = data.end();

  boost::spirit::qi::bit_field<decltype(start), BitField > bit_parser;
  bool r = false;
  r =   boost::spirit::qi::parse(start, end, (bit_parser), bf );
  print(bf);



  std::string s;
  std::back_insert_iterator<decltype(s)> sink(s);
  boost::spirit::karma::bit_field<decltype(sink), BitField> bit_generator;

  r = boost::spirit::karma::generate(sink, (bit_generator), bf);

  if(r){

    std::cout << "generated(" <<  s.size() << ") " << (std::bitset<8>)s[0] << std::endl;
  }
  return 0;
}
