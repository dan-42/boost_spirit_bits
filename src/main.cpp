#include <vector>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <iomanip>
#include <string>



#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>





namespace boost { namespace spirit { namespace qi {


template<typename Iterator, typename ReturnType>
//template<typename Iterator>
struct bit_ : grammar<Iterator, ReturnType()> {
//  static_assert((sizeof(ReturnType) == 1), "bit_ size of ReturnType must be 1 byte in size!");

  bit_() : bit_::base_type(start)  {    
      
    _8bits = byte_;

    //   start = _8bits[_val = static_cast<ReturnType>(_1)]  ;
    start = _8bits;
 //      start = byte_;

    start.name("start");
    _8bits.name("_8bits");
  
//    debug(start);
//    debug(_8bits);
  }

  rule<Iterator,ReturnType()> start;
  rule<Iterator, uint8_t()> _8bits;
};

}}}



struct BitField {
  uint8_t type : 4;
  uint8_t flag1 : 1;
  uint8_t flag2 : 1;
  uint8_t flag3 : 1;
  uint8_t flag4 : 1;

  BitField(){
  }

  BitField(const uint8_t& b){
    (*this) = static_cast<BitField>(b);
  }

  void print() {
    std::cout << "type: " << std::to_string(type) << std::endl;
    std::cout << "flag1: "; flag1 ? (std::cout << "true") :( std::cout << "false") ; std::cout  << std::endl;
    std::cout << "flag2: "; flag2 ? (std::cout << "true") :( std::cout << "false") ; std::cout  << std::endl;
    std::cout << "flag3: "; flag3 ? (std::cout << "true") :( std::cout << "false") ; std::cout  << std::endl;
    std::cout << "flag4: "; flag4 ? (std::cout << "true") :( std::cout << "false") ; std::cout  << std::endl;
  }
};




int main() {


  BitField bf;
  BitField bf_test;

  bf_test.type = 2;
  bf_test.flag1 = 1;
  bf_test.flag2 = 1;
  bf_test.flag3 = 1;
  bf_test.flag4 = 1;

  bf_test.print();

  uint8_t test_u8 = 0;
  std::cout << "sizeof(bf) = " << sizeof(bf) << std::endl;
  
  std::string data;
  data.push_back(0b10101010);
  std::cout << "data(" <<  data.size() << ") "  <<  std::hex << (int)data[0] << std::endl;


  auto start = data.begin();
  auto end = data.end();

boost::spirit::qi::bit_<decltype(start), BitField > bit_parser;
  bool r = false;
 r =   boost::spirit::qi::parse(start, end, (bit_parser), bf );

 if(r) {
   std::cout << "juhu woot!" << std::endl;
   std::cout << test_u8 << std::endl;
 }

 bf.print();
  return 0;
}
