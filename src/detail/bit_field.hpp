
#ifndef _SPIRIT_BIT_FIELD_HPP
#define _SPIRIT_BIT_FIELD_HPP

#include <cstdint> 

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>


namespace boost { namespace spirit { namespace qi {


template<typename Iterator, typename ReturnType>
struct bit_field : grammar<Iterator, ReturnType()> {
  static_assert((sizeof(ReturnType) == 1), "size of ReturnType must be 1 byte in size!");
  static_assert((std::is_class<ReturnType>::value), "ReturnType must be struct or class!");

  bit_field() : bit_field::base_type(start) {    

    start = byte_[_val = *boost::phoenix::reinterpret_cast_<ReturnType*>(&_1) ];
  
  }

  rule<Iterator,ReturnType()> start;

};

}}}



namespace boost { namespace spirit { namespace karma {


template<typename Iterator, typename ReturnType>
struct bit_field : grammar<Iterator, ReturnType()> {
  static_assert((sizeof(ReturnType) == 1), "size of ReturnType must be 1 byte in size!");
  static_assert((std::is_class<ReturnType>::value), "ReturnType must be struct or class!");

  bit_field() : bit_field::base_type(start) {    

	  start = byte_[_1 = *boost::phoenix::reinterpret_cast_<const uint8_t*>(&_val) ];

  }

  rule<Iterator, ReturnType()> start;

};

}}}


#endif
