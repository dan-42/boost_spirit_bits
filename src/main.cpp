#include <vector>
#include <iostream>
#include <cstdint>
#include <string>
#include <bitset>

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <boost/phoenix/bind/bind_member_variable.hpp>


namespace boost { namespace spirit { namespace qi {

namespace detail {

  template<typename ReturnType>
  union bit_field_container {

    static_assert((sizeof(ReturnType) == 1), "bit_ size of ReturnType must be 1 byte in size!");

    bit_field_container() : _native(0) {    }
    bit_field_container(const uint8_t& native_value): _native(native_value){   }

    ReturnType bitfield() { return _bitfield; }

    uint8_t _native;
    ReturnType _bitfield;
  };

} //detail

template<typename Iterator, typename ReturnType>
struct bit_field : grammar<Iterator, ReturnType()> {
  static_assert((sizeof(ReturnType) == 1), "bit_ size of ReturnType must be 1 byte in size!");


  bit_field() : bit_field::base_type(start) {    

    _8bits = byte_;
    start = _8bits[_val = boost::phoenix::bind(&detail::bit_field_container<ReturnType>::bitfield, _1) ];
  
  }

  rule<Iterator,ReturnType()> start;
  rule<Iterator, detail::bit_field_container<ReturnType>()> _8bits;

};

}//qi

namespace karma {


namespace detail {

  template<typename ReturnType>
  union bit_field_container {

    static_assert((sizeof(ReturnType) == 1), "bit_ size of ReturnType must be 1 byte in size!");

    bit_field_container() : _native(0) {    }
    bit_field_container(const ReturnType& type) : _bitfield(type) {    }
    bit_field_container(const uint8_t& native_value): _native(native_value){   }

    ReturnType bitfield() { return _bitfield; }

    uint8_t native_value()  { return _native; }

    uint8_t _native;
    ReturnType _bitfield;
  };

} //detail




template<typename Iterator, typename ReturnType>
struct bit_field : grammar<Iterator, ReturnType()> {
  static_assert((sizeof(ReturnType) == 1), "size of ReturnType must be 1 byte in size!");


  bit_field() : bit_field::base_type(start) {    

//    _8bits = byte_[_1 = 0x00  ];
    _8bits = byte_[_1 = boost::phoenix::bind(&detail::bit_field_container<ReturnType>::_native, _val) ];

    start = _8bits;
    //start = _8bits[_1 = boost::phoenix::bind(&detail::bit_field_container<ReturnType>::native_value, _val) ];
    //start = _8bits[_1 =  detail::bit_field_container<ReturnType>(_val)];
  
  }

  rule<Iterator, ReturnType()> start;
  rule<Iterator, detail::bit_field_container<ReturnType>()> _8bits;

};



}


}}



struct BitField {
  uint8_t type : 4;
  uint8_t flag1 : 1;
  uint8_t flag2 : 1;
  uint8_t flag3 : 1;
  uint8_t flag4 : 1;

  
  void print() {

    std::cout << "type: " << std::to_string((int)type) << std::endl;

    std::cout << "flag1: ";
    if(flag1) { std::cout << "true";  }    
    else { std::cout << "false" ;  }    
    std::cout  << std::endl;

    std::cout << "flag2: ";
    if(flag2) { std::cout << "true";  }    
    else { std::cout << "false" ;  }    
    std::cout  << std::endl;

    std::cout << "flag3: ";
    if(flag3) { std::cout << "true";  }    
    else { std::cout << "false" ;  }    
    std::cout  << std::endl;

    std::cout << "flag4: ";
    if(flag4) { std::cout << "true";  }    
    else { std::cout << "false" ;  }    
    std::cout  << std::endl;
  }
};



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
   bf.print();



  std::string s;
  std::back_insert_iterator<decltype(s)> sink(s);
  boost::spirit::karma::bit_field<decltype(sink), BitField> bit_generator;

  r = boost::spirit::karma::generate(sink, (bit_generator), bf);

  if(r){

    std::cout << "generated(" <<  s.size() << ") " << (std::bitset<8>)s[0] << std::endl;
  }
  return 0;
}
