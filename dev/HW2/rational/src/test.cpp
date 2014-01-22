#include "rational.h"

#include <iostream>
#include <iomanip>

int main() {
  auto a = Rational{ 2, 6 }; // the number 1/3
  auto b = Rational{ -6, 7 }; // the number -6/7
  auto c = Rational{ 12, -14 }; // the number -6/7
  auto d = Rational{ -12, -14 }; // the number -6/7
  auto e = Rational{ 15, -100 }; // the number -6/7

  std::cout << a << "\n";
  std::cout << b << "\n";
  std::cout << c << "\n";
  std::cout << d << "\n";
  std::cout << e << "\n";
  
  std::cout << a << " * " << b << " = " << a * b << "\n";
  std::cout << a << " + " << c << " = " << a + c << "\n";
  /*
  std::cout << "Now for something more complicated...\n";  
  std::cout << "a / ( a + b / a ) = " << a / ( a + b / a ) << "\n";

  auto phi = Rational{ 1 };

  for( int i = 0; i < 40; ++i ) {
    phi = 1 / ( 1 + phi );
  }
  std::cout << std::setprecision( 15 );
  std::cout << "phi = " << ( 1 + phi ).to_double() << "\n";
  */
  return 0;
}
