// Taken from http://www.parashift.com/c++-faq-lite/convert-num-to-string.html
// and subsequently templated.

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

class BadConversion : public std::runtime_error {
public:
  BadConversion(std::string const& s)
    : std::runtime_error(s)
    { }
};

template <class T>
inline std::string stringify(T x)
{
  std::ostringstream o;
  if (!(o << x))
    throw BadConversion("stringify");
  return o.str();
}