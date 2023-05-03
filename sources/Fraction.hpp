#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <cmath> 
#include <algorithm>
#include <iomanip> 
#include <limits>

namespace ariel{
    class Fraction
    {
        private:
            int numerator_;
            int denominator_;
            void negative_handler();
            void reduce();
            static Fraction floatToFraction(float);
            static float fractionToFloat(const Fraction& frac);
            

        public:
            //Constructors
            Fraction();

            Fraction(float);

            Fraction(int numerator, int denominator);

            //Arithmetic Operators
            Fraction operator+(const Fraction&) const;
            friend Fraction operator+(float, const Fraction&);
            friend Fraction operator+(const Fraction&, float);
 
            Fraction operator-(const Fraction&) const;
            friend Fraction operator-(float, const Fraction&);
            friend Fraction operator-(const Fraction&, float);
 
            Fraction operator*(const Fraction&) const;
            friend Fraction operator*(float, const Fraction&);
            friend Fraction operator*(const Fraction&, float);
            
            Fraction operator/(const Fraction&) const;
            friend Fraction operator/(float, const Fraction&);
            friend Fraction operator/(const Fraction&, float);

            //Comparison Operators
            bool operator==(const Fraction&) const;
            friend bool operator==(const Fraction&, float);
            friend bool operator==(float, const Fraction&);
            
            bool operator>(const Fraction&) const;
            friend bool operator>(const Fraction&, float);
            friend bool operator>(float, const Fraction&);

            bool operator<(const Fraction&) const;
            friend bool operator<(const Fraction&, float);
            friend bool operator<(float, const Fraction&);

            bool operator>=(const Fraction&) const;
            friend bool operator>=(const Fraction&, float);
            friend bool operator>=(float, const Fraction&);
            
            bool operator<=(const Fraction&) const;
            friend bool operator<=(const Fraction&, float);
            friend bool operator<=(float, const Fraction&);

            //prefix
            Fraction& operator++(){
                numerator_+= denominator_;
                return *this;
            }
            Fraction& operator--(){
                numerator_-= denominator_;
                return *this;
            }

            //postfix
            Fraction operator++(int flag_to_overload){
                Fraction copy = *this;
                numerator_+= denominator_;
                return copy;
            }
            Fraction operator--(int flag_to_overload){
                Fraction copy = *this;
                numerator_-= denominator_;
                return copy;
            }

            int getNumerator() const{
                return numerator_;
            }
            
            int getDenominator() const{
                return denominator_;
            }
            
            friend std::ostream& operator<< (std::ostream& output, const Fraction& frac);
            friend std::istream& operator>> (std::istream& input , Fraction& frac);
    };
}

#endif