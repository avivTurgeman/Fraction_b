#include "Fraction.hpp"
#define cast_ll static_cast<long long>
#define ll long long
#define max_int std::numeric_limits<int>::max()
#define min_int std::numeric_limits<int>::min()


using namespace std;

namespace ariel{

    Fraction::Fraction():numerator_(0), denominator_(1){}

    Fraction::Fraction(float num){
        Fraction other = floatToFraction(num);
        numerator_ = other.getNumerator();
        denominator_ = other.getDenominator();
    }

    Fraction::Fraction(int numerator, int denominator):
    numerator_(numerator), denominator_(denominator){
        if(denominator_ == 0){
            throw std::invalid_argument("denominator cannot be 0");
        }
        reduce();
        negative_handler();
    }

    void Fraction::negative_handler(){
        if(numerator_ < 0 && denominator_ < 0){
            numerator_ *= -1;
            denominator_ *= -1;
        }
        if(numerator_ >= 0 && denominator_ < 0){
            numerator_ *= -1;
            denominator_ *= -1;
        }
    }

    void Fraction::reduce(){
        int gcd = __gcd(numerator_, denominator_);
        numerator_ /= gcd;
        denominator_ /= gcd;
    }

    Fraction Fraction::floatToFraction(float  num){
        int integer_part = (int) num;
        float dummy;
        float frac = modf(num, &dummy);
        int fractional_part = round(frac * 1000);

        Fraction rv(fractional_part + (integer_part * 1000), 1000);
        
        return rv;    
    }

    float Fraction::fractionToFloat(const Fraction& frac){
        float numerator = static_cast<float>(frac.getNumerator());
        float denominator = static_cast<float>(frac.getDenominator());
        float rv = numerator/denominator;
        return round(rv * 1000) / 1000;
    }

    Fraction Fraction::operator+(const Fraction& other) const{

        ll numerator1 = cast_ll(this->numerator_) * cast_ll(other.denominator_);
        ll numerator2 = cast_ll(other.numerator_) * cast_ll(this->denominator_);
        ll rv_numerator = numerator1 + numerator2;
        ll rv_denominator = cast_ll(this->denominator_ ) * cast_ll(other.denominator_);

        if((rv_numerator > max_int) ||
            (rv_denominator > max_int) ||
            (rv_numerator < min_int) ||
            (rv_denominator < min_int)){
            throw overflow_error("Fraction addition overflowed");
        }

        Fraction rv(rv_numerator, rv_denominator);
        return rv;
    }

    Fraction operator+(float  num, const Fraction& frac){
        Fraction numF = Fraction::floatToFraction(num) ;
        Fraction rv = numF + frac;
        return rv;
    }

    Fraction operator+(const Fraction& frac, float  num){
        Fraction numF = Fraction::floatToFraction(num);
        Fraction rv = numF + frac;
        return rv;
    }

    Fraction Fraction::operator-(const Fraction& other) const{
        if((*this > 0.0) && 
            (other.getNumerator() == min_int)){
            throw overflow_error("Fraction subtraction overflowed");
        }
        Fraction negative_other = other * (-1.0);
        Fraction rv = *this + negative_other;
        return rv;
    }

    Fraction operator-(float num, const Fraction& frac){
        Fraction numF = Fraction::floatToFraction(num);
        Fraction rv = numF - frac;
        return rv;
    }

    Fraction operator-(const Fraction& frac, float num){
        Fraction numF = Fraction::floatToFraction(num);
        Fraction rv = frac - numF;
        return rv;
    }

    Fraction Fraction::operator*(const Fraction& other) const{
        long long rv_numerator = cast_ll(this->numerator_) * cast_ll(other.numerator_);
        long long rv_denominator = cast_ll(this->denominator_) * cast_ll(other.denominator_);
        
        if((rv_numerator > max_int) || 
            (rv_denominator > max_int)){
                throw overflow_error("Fraction multiplication overflowed");
            }
        
        Fraction rv(rv_numerator, rv_denominator);
        return rv;
    }

    Fraction operator*(float num, const Fraction& frac){
        Fraction numF = Fraction::floatToFraction(num) ;
        Fraction rv = numF * frac;
        return rv;
    }

    Fraction operator*(const Fraction& frac, float num){
        Fraction numF = Fraction::floatToFraction(num) ;
        Fraction rv = numF * frac;
        return rv;
    }

    Fraction Fraction::operator/(const Fraction& other) const{
        if(other.getNumerator() == 0){
            throw std::runtime_error("cannot divide by zero!\n");
        }
        Fraction other_flipped(other.denominator_, other.numerator_);
        Fraction rv = *this * other_flipped;
        return rv;
    }

    Fraction operator/(float num, const Fraction& frac){
        if(frac.getNumerator() == 0){
            throw std::runtime_error("cannot divide by zero!\n");
        }
        Fraction numF = Fraction::floatToFraction(num) ;
        Fraction frac_flipped(frac.denominator_, frac.numerator_);
        Fraction rv = numF * frac_flipped;
        return rv;
    }

    Fraction operator/(const Fraction& frac, float num){
        if(num == 0){
            throw std::runtime_error("cannot divide by zero!\n");
        }
        Fraction numF = Fraction::floatToFraction(num) ;
        Fraction numF_flipped(numF.denominator_, numF.numerator_);
        Fraction rv = numF_flipped * frac;
        return rv;
    }

    bool Fraction::operator==(const Fraction& other) const{
        float thisFloat = Fraction::fractionToFloat(*this);
        float otherFloat = Fraction::fractionToFloat(other);

        if(thisFloat == otherFloat){
            return true;
        }
        return false;
    }

    bool operator==(const Fraction& frac, float num){
        Fraction numF = Fraction::floatToFraction(num);
        return (frac == numF);
    }

    bool operator==(float num, const Fraction& frac){
        Fraction numF = Fraction::floatToFraction(num);
        return (frac == numF);
    }

    bool Fraction::operator>(const Fraction& other) const{
        float thisFloat = Fraction::fractionToFloat(*this);
        float otherFloat = Fraction::fractionToFloat(other);

        if(thisFloat > otherFloat){
            return true;
        }
        return false;
    }

    bool operator>(const Fraction& frac, float num){
        Fraction numF = Fraction::floatToFraction(num);
        return (frac > numF);
    }

    bool operator>(float num, const Fraction& frac){
        Fraction numF = Fraction::floatToFraction(num);
        return (numF > frac);
    }

    bool Fraction::operator<(const Fraction& other) const{
        float thisFloat = Fraction::fractionToFloat(*this);
        float otherFloat = Fraction::fractionToFloat(other);

        if(thisFloat < otherFloat){
            return true;
        }
        return false;
    }

    bool operator<(const Fraction& frac, float num){
        Fraction numF = Fraction::floatToFraction(num);
        return (frac < numF);
    }

    bool operator<(float num, const Fraction& frac){
        Fraction numF = Fraction::floatToFraction(num);
        return (numF < frac);
    }

    bool Fraction::operator>=(const Fraction& other) const{
        float thisFloat = Fraction::fractionToFloat(*this);
        float otherFloat = Fraction::fractionToFloat(other);

        if(thisFloat >= otherFloat){
            return true;
        }
        return false;
    }

    bool operator>=(const Fraction& frac, float num){
        Fraction numF = Fraction::floatToFraction(num);
        return (frac >= numF);
    }

    bool operator>=(float num, const Fraction& frac){
        Fraction numF = Fraction::floatToFraction(num);
        return (numF >= frac);
    }

    bool Fraction::operator<=(const Fraction& other) const{
        float thisFloat = Fraction::fractionToFloat(*this);
        float otherFloat = Fraction::fractionToFloat(other);

        if(thisFloat <= otherFloat){
            return true;
        }
        return false;
    }
    
    bool operator<=(const Fraction& frac, float num){
        Fraction numF = Fraction::floatToFraction(num);
        return (frac <= numF);
    }

    bool operator<=(float num, const Fraction& frac){
        Fraction numF = Fraction::floatToFraction(num);
        return (numF <= frac);
    }

    ostream& operator<<(ostream& output, const Fraction& frac) {
        return output << frac.getNumerator() << '/' << frac.getDenominator();
    }

    istream& operator>>(istream& input, Fraction& frac){
        int numerator ,denominator;

        input >> numerator >> denominator;

        if((input.fail()) || (denominator == 0)){
            throw std::runtime_error("2 arguments needed: <numerator>  <denominator>\n");
        }
        else{
            frac = Fraction(numerator, denominator);
        }
        return input;
    }
}