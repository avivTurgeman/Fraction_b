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
            static Fraction floatToFraction(const float);
            static float fractionToFloat(Fraction frac);
            

        public:
            //Constructors
            Fraction():
            numerator_(0), denominator_(1){}

            Fraction(float num){
                *this = floatToFraction(num);
            }

            Fraction(int numerator, int denominator):
            numerator_(numerator), denominator_(denominator){
                if(denominator_ == 0){
                    throw std::invalid_argument("denominator cannot be 0");
                }
                reduce();
                negative_handler();
            }
            
            //copy Constructor
            Fraction(const Fraction& other):
            numerator_(other.numerator_), denominator_(other.denominator_){}

            //destructor
            ~Fraction();

            //Arithmetic Operators
            Fraction operator+(const Fraction&) const;
            friend Fraction operator+(const float, const Fraction&);
            friend Fraction operator+(const Fraction&, const float);
 
            Fraction operator-(const Fraction&) const;
            friend Fraction operator-(const float, const Fraction&);
            friend Fraction operator-(const Fraction&, const float);
 
            Fraction operator*(const Fraction&) const;
            friend Fraction operator*(const float, const Fraction&);
            friend Fraction operator*(const Fraction&, const float);
            
            Fraction operator/(const Fraction&) const;
            friend Fraction operator/(const float, const Fraction&);
            friend Fraction operator/(const Fraction&, const float);

            //Comparison Operators
            bool operator==(const Fraction&) const;
            friend bool operator==(const Fraction&, const float);
            friend bool operator==(const float, const Fraction&);
            
            bool operator>(const Fraction&) const;
            friend bool operator>(const Fraction&, const float);
            friend bool operator>(const float, const Fraction&);

            bool operator<(const Fraction&) const;
            friend bool operator<(const Fraction&, const float);
            friend bool operator<(const float, const Fraction&);

            bool operator>=(const Fraction&) const;
            friend bool operator>=(const Fraction&, const float);
            friend bool operator>=(const float, const Fraction&);
            
            bool operator<=(const Fraction&) const;
            friend bool operator<=(const Fraction&, const float);
            friend bool operator<=(const float, const Fraction&);

            //Assignment Operator
            Fraction& operator=(const Fraction& other){
                if(this != &other){
                    this->numerator_ = other.numerator_;
                    this->denominator_ = other.denominator_;
                }
                negative_handler();
                reduce();
                return *this;
            }

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