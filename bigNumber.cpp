#include <iostream>
#include <cmath>
#include <string>
using namespace std;




class bigNumber
{
private:
    int* num;
    int len;
    bool sign;
public:
    
    bigNumber();
    bigNumber(int number);
    bigNumber(string number);
    bigNumber(int* number, int len, bool sign);
    bigNumber(const bigNumber& number);
    ~bigNumber();
    void shiftLeft();
    void shiftRight();
    friend ostream& operator<<(ostream& output, const bigNumber& number);
    friend bool isBigger(const bigNumber& number1, const  bigNumber& number2);
    bigNumber& operator=(const bigNumber& number2);
    friend bool operator==(const bigNumber& number1, const bigNumber& number2);
    friend bigNumber operator+(const bigNumber& number1, const  bigNumber& number2);
    friend bigNumber operator-(const bigNumber& number1, const  bigNumber& number2);
    friend bigNumber operator /(const bigNumber& dividend, const bigNumber& divisor);
    friend bigNumber operator*(const bigNumber& number1, const bigNumber& number2 );
    bigNumber karatsubaMultiply(const bigNumber& number2);
    void splitAt(int m, bigNumber& low, bigNumber& high) const;
    static bigNumber factoriel(int n);
    bigNumber pow(int n);

};

bigNumber::bigNumber()
{
    sign = false;
    len = 1;
    num = new int[len];
    num[0] = 0;
}

bigNumber::bigNumber(const bigNumber& number){
    len = number.len;
    num = new int[len];
    sign = number.sign;
    for(int i = 0; i < len; i++){
        num[i] = number.num[i];
    }
}

bigNumber::bigNumber(int number){
    if(number == 0){
        sign = false;
        len = 1;
        num = new int[len];
        num[0] = 0;
    } else {
        sign = number < 0;
        number = abs(number);
        len = (int) log10(number) + 1;
        num = new int[len];
        
        for(int i = 0; i < len; i++){
            num[i] = number % 10;
            number /= 10;
        }
    }
}

bigNumber::bigNumber(int* number, int len, bool sign){
    for (int i = 0; i < len; i++) {
        if (number[i] < 0 || number[i] > 9) {
            throw std::invalid_argument("Invalid input: array contains non-digit values.");
        }
    }

    this->len = len;
    this->sign = sign;
    num = new int[len];
    for(int i = 0; i < len; i++){
        num[i] = number[i];
    }

}



bigNumber::bigNumber(string number){
    
    if(number[0] == '-'){
        sign = true;
        number.erase(number.begin());
    }
    else if(number[0]== '+'){
        sign = false;
        number.erase(number.begin());
    }
    else{
        sign = false;
    }
    len = number.length();
    num = new int[len];
    
    for(int i = 0 ; i < number.length(); i++){
        num[len - i - 1] = number[i] - '0';
    }

}

bigNumber::~bigNumber(){
    delete[] num;
}

ostream& operator<< (ostream& output, const bigNumber& number){
    if(number.len == 1 && number.num[0] == 0){
        output<<0<<endl;
        return output;
    }
    !number.sign ? output<<"" : output<<"-";
    for(int i = number.len - 1; i >= 0; i--){
        output<<number.num[i];
    }
    output<<endl;

    return output;
    
}


bool isBigger(const bigNumber& number1, const  bigNumber& number2){
    if(number1.len != number2.len){
        return number1.len > number2.len;
    }
    else{
        for(int i = number1.len - 1; i >= 0; i--){
            if(number1.num[i] != number2.num[i]){
                return number1.num[i] > number2.num[i];
            }
        }
    }
    return false;
}


bigNumber operator +(const bigNumber& number1, const  bigNumber& number2){
    

    
    if(number1.sign == number2.sign){
        int maxLen = number1.len > number2.len ? number1.len : number2.len;

        int* sumRes = new int[maxLen + 1];
        int carry = 0;

        for(int i = 0; i < maxLen ; i++){

            int digit1 = (i < number1.len) ? number1.num[i] : 0;
            int digit2 = (i < number2.len) ? number2.num[i] : 0;
            
                int res = digit1 + digit2 + carry;
                if(res >= 10){
                    carry = 1;
                    res -= 10;
                }
                else{
                    carry = 0;
                }
                sumRes[i] = res;
                
        }

        if(carry == 1){
            sumRes[maxLen] = 1;
            bigNumber result(sumRes, maxLen + 1, number1.sign);
            delete[] sumRes;
            return result;
        }
        else{
            bigNumber result(sumRes, maxLen, number1.sign);
            delete[] sumRes;
            return result;
        }
    }
    else{   //age alamat adad motavafet bashad az hamdige kam mikonim
            return number1 - bigNumber(number2.num, number2.len, !number2.sign);
        
    }
}


bigNumber& bigNumber::operator=(const bigNumber& number2){
    if(this == &number2){
        return *this;
    }

    delete[] num;

    len = number2.len;
    sign = number2.sign;
    num = new int[len];
    
    for(int i = 0; i <len ; i++){
        num[i] = number2.num[i];
    }

    return *this;
}


bigNumber operator -(const bigNumber& number1, const  bigNumber& number2){
    if(number1.sign == number2.sign){
        bool resSign = number1.sign;
        const bigNumber*  larger;
        const bigNumber*  smaller;
        

        if(isBigger(number1, number2)){  //age adad aval bozorgtar bashad be halat adi menha mishavad
            larger = &number1;
            smaller = &number2;
        }

        else{           //age adad dovom bozorg tar bashe alamat nahaii manfi mishe va mitonim addad dovom ro menhaye adad aval konim
            larger = &number2;
            smaller = &number1;
            resSign = !resSign;
        }

        int maxLen = larger->len;

        int* subtractionRes = new int[maxLen];
        int borrow = 0;

        for(int i = 0; i < maxLen; i++){
            int digit1 = (i < larger->len) ? larger->num[i] : 0;
            int digit2 = (i < smaller->len) ? smaller->num[i] : 0;

            digit1 -= borrow;

            if(digit2 > digit1){
                borrow = 1;
                digit1 += 10;
            }
            else{
                borrow = 0;
            }
            subtractionRes[i] = digit1 - digit2;
        }
    int resultLen = maxLen;
    while(resultLen > 1 && subtractionRes[resultLen - 1] == 0) {
        resultLen--;
    }
    bigNumber result (subtractionRes, resultLen, resSign);
    delete[] subtractionRes;
    return result;
    }

    
    else{   //age alamat motafavet bashad ba ham jam mikonim
        return number1 + bigNumber(number2.num, number2.len, !number2.sign);
    }
}

void bigNumber::shiftLeft(){
    //yek araye jadid be tool yeki bishtar sakhte mishe ke onsor avalesh 0 hast
    int* newNum = new int[len + 1];
    newNum[0] = 0;
    for(int i = 0; i < len; i++){
        newNum[i + 1] = num[i];
    }
    len++;
    delete [] num;
    num = newNum;
}

void bigNumber::shiftRight(){
    if(len <= 1){     //age add 1 raghami bashe tabdil be 0 mishe
        num[0] = 0;
        len = 1;
        return;
    }
    //yek araye jadid sakhte shode bedone onsor aval be be jaye arraye feli gozashte mishe
    int* newNum = new int[len - 1];
    for(int i = 1; i < len; i++){
        newNum[i - 1] = num[i];
    }
    len--;
    delete [] num;
    num = newNum;
}

bool operator==(const bigNumber& number1, const bigNumber& number2) {
    
    if (number1.sign != number2.sign) {
        return false;
    }

    
    if (number1.len != number2.len) {
        return false;
    }

    
    for (int i = 0; i < number1.len; i++) {
        if (number1.num[i] != number2.num[i]) {
            return false;
        }
    }

    
    return true;
}

void bigNumber::splitAt(int m, bigNumber& low, bigNumber& high) const {

    low.len = m;
    low.num = new int[low.len];
    for (int i = 0; i < m; ++i) {
        low.num[i] = num[i];
    }

    
    high.len = len - m;
    high.num = new int[high.len];
    for (int i = 0; i < high.len; ++i) {
        high.num[i] = num[m + i];
    }
}


bigNumber bigNumber::karatsubaMultiply(const bigNumber& number2){ //anjam zarb be ravesh karatsuba
    bool resSign = sign == number2.sign ? false: true;
    //check kardan halat haye sade
    if((len == 1 && num[0] == 0) || (number2.len == 1 && number2.num[0] == 0)){
        return bigNumber();
    }
    if(len == 1 && num[0] == 1){
        return bigNumber(number2.num, number2.len, resSign);
    }
    if(number2.len == 1 && number2.num[0] == 1){
        return bigNumber(num, len, resSign);
    }
    
    if(len == 1 || number2.len == 1){
        return *this * number2;
    }

    int m = len > number2.len ? number2.len / 2 : len / 2;
    
    bigNumber X0, X1, Y0, Y1;

    this->splitAt(m, X0, X1);
    number2.splitAt(m, Y0, Y1);

    bigNumber P1 = X0.karatsubaMultiply(Y0);
    bigNumber P2 = X1.karatsubaMultiply(Y1);
    bigNumber P3 = (X0 + X1).karatsubaMultiply(Y0 + Y1) - P1 - P2;

    for(int i = 0; i < 2 * m; i++){
        P2.shiftLeft();
    }
    for(int i = 0; i < m; i++){
        P3.shiftLeft();
    }

    bigNumber res = P2 + P3 + P1;
    return res;

}

bigNumber operator *(const bigNumber& number1, const  bigNumber& number2){ //anjam zarb be ravesh mamoli
    bool resSign = number1.sign == number2.sign ? false: true;
    if((number1.len == 1 && number1.num[0] == 0) || (number2.len == 1 && number2.num[0] == 0)){
        return bigNumber();
    }
    if(number1.len == 1 && number1.num[0] == 1){
        return bigNumber(number2.num, number2.len, resSign);
    }
    if(number2.len == 1 && number2.num[0] == 1){
        return bigNumber(number1.num, number1.len, resSign);
    }
    
    int* res = new int[number1.len + number2.len] {};



    
    for(int i = 0 ; i < number2.len; i++){
        int carry = 0;
        for(int j = 0; j < number1.len; j++){
            int current = number1.num[j] * number2.num[i] + carry + res[i + j];
            res[i + j] = current % 10;
            carry = current / 10;
        }
        res[i + number1.len] += carry;
    }

    int resultLen = number1.len + number2.len;
    while(resultLen > 1 && res[resultLen - 1] == 0) {
        resultLen--;
    }

    bigNumber ans(res, resultLen, resSign);
    delete [] res;
    return ans;
    
}


bigNumber operator/(const bigNumber& dividend, const bigNumber& divisor){
    bool resSign = dividend.sign == divisor.sign ? false: true;
    if(divisor.len == 1 && divisor.num[0] == 0){
        throw std::invalid_argument("division by zero");
    }

    if(divisor.len == 1 && divisor.num[0] == 1){
        return dividend;
    }

    if(isBigger(divisor, dividend)){
        return bigNumber();
    }

    bigNumber remainder;
    bigNumber result;


    bigNumber newDivisor = divisor.sign ? bigNumber(divisor.num, divisor.len, false): divisor;

    
    remainder.len = 0;
    remainder.num = new int[dividend.len] {0};

    
    int* quotientDigits = new int[dividend.len];

    for (int i = dividend.len - 1; i >= 0; --i) {
        
        remainder.shiftLeft();
        remainder.num[0] = dividend.num[i];

        
        int q = 0;
        while (isBigger(remainder, newDivisor) || remainder == newDivisor) {
            remainder = remainder - newDivisor;
            ++q;
        }

        
        quotientDigits[i] = q;
    }


    int resultLen = dividend.len;
    while (resultLen > 1 && quotientDigits[resultLen - 1] == 0) {
        --resultLen;
    }

    
    result.num = new int[resultLen];
    for (int i = 0; i < resultLen; i++) {
        result.num[i] = quotientDigits[i];
    }
    result.len = resultLen;
    result.sign = resSign;

    delete[] quotientDigits;
    return result;
}



bigNumber bigNumber::factoriel(int n){
    bigNumber res(1);
    for(int i = 1; i <= n; i++){
        res = res.karatsubaMultiply(i);
    }
    return res;
}


bigNumber bigNumber::pow(int n){
    if(n == 0){
        return bigNumber(1);
    }
    if(n == 1){
        return *this;
    }

    
    
    bigNumber half = this->pow(n / 2);
    half = half.karatsubaMultiply(half);

    if(n % 2 == 1){
        half = half.karatsubaMultiply(*this);
    }

    if(this->sign && n % 2 == 1){
        half = half * -1;
    }

    return half;
}

int main(){
    bigNumber num(32412);
    bigNumber num2("-165");
    bigNumber num3 = num / num2;
    
    bigNumber num4 = bigNumber::factoriel(20);

    bigNumber num5 = num * num2;
    bigNumber num6 = num.karatsubaMultiply(num2);

    bigNumber num7(-75);
    bigNumber num8 = num7.pow(11);

    cout<<num<<num2<<num3<<"factoriel of 20: "<<num4<<"multiplication of nums: "<<num5<<"kartasuba: "<<num6<<"pow: "<<num8;
}
