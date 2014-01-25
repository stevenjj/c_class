#include "rational.h"
#include "gcd.h"

#include <stdexcept>
#include <ostream>
#include <iostream>

// Implement this
const Rational Rational::inverse() const {
  /* Return the Rational number 1 / current rational */
  return Rational{this->den(), this->num() };
}

// Implement this
Rational::sign_type Rational::sign() const {
  if (this->_num >= 0){
    return Rational::POSITIVE;
  }
  else{
    return Rational::NEGATIVE;
  }
  /* Return, as a sign_type, the sign of the Rational */
}

/* Print the value num/den to the supplied output stream, or 0 if 
 * the Rational happens to be identically zero.
 */
std::ostream& operator<<( std::ostream &os, const Rational &ratio ) {
  if( ratio == 0 ) {
    os << "0";
  } else {
    if( ratio.sign() == Rational::NEGATIVE ) {
      os << "-";
    }
    os << std::abs( ratio.num() ) << "/" << std::abs( ratio.den() );
  }
  return os;
}

/* This function will be called whenever the 
 * Rational is constructed from integers that
 * are supplied as numerator and denominator.
 * It should reduce the fraction to lowest terms;
 * for example, when we try to construct a
 * Rational{ 4, -8 }, this is the function that
 * will cause the number to be exactly the same
 * as Rational{ -1, 2 }. Numerators should be
 * the only value potentially negative after
 * the call to ::normalize().
 * Throw bad_rational if there is an attempt
 * to set one with a zero denominator.
 */
void Rational::normalize() {
  intmax_t num_try = this->_num;
  intmax_t den_try = this->_den;

  if (den_try == 0){
    throw bad_rational();
    }

  if ( (num_try < 0 && den_try < 0) ||  (num_try > 0 && den_try < 0) ){
    this->_num = this->_num *-1;
    this->_den = this->_den *-1;
    num_try *= -1; // Make numerator positive/negative
    den_try *= -1; // Make denom always positive

  }
  if (num_try < 0){
    num_try *= -1; //Make it num positive
  }
  intmax_t gcd_number = gcd(num_try, den_try);
  this->_num /= gcd_number; 
  this->_den /= gcd_number;

  // You should implement
}

// Return the float precision number corresponding to the Rational
float Rational::to_float() const {
  float num_try = (float) (this->num());
  float den_try = (float) (this->den());
  return num_try/den_try;
  // You should implement
}

// Return the double precision number corresponding to the Rational
double Rational::to_double() const {
  double num_try = (double) (this->num());
  double den_try = (double) (this->den());
  return num_try/den_try;
  // You should implement
}
