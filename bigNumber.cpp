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
    void printNum();
    friend bool isBigger(const bigNumber& number1, const  bigNumber& number2);
    friend bigNumber operator+(const bigNumber& number1, const  bigNumber& number2);
    friend bigNumber operator-(const bigNumber& number1, const  bigNumber& number2);

};

bigNumber::bigNumber()
{
    sign = true;
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
    this->len = len;
    this->sign = sign;
    num = new int[len];
    for(int i = 0; i < len; i++){
        num[i] = number[i];
    }
    // delete [] number;
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

void bigNumber::printNum(){
    !sign ? cout<<"" : cout<<"-";
    for(int i = len - 1; i >= 0; i--){
        cout<<num[i];
    }
    cout<<endl;
    
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
    

    int maxLen = number1.len > number2.len ? number1.len : number2.len;

    int* sumRes = new int[maxLen + 1];
    int carry = 0;
    if(number1.sign == number2.sign){
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
            return bigNumber(sumRes, maxLen + 1, number1.sign);
        }
        else{
            return bigNumber(sumRes, maxLen, number1.sign);
        }
    }
    else{   //age alamat adad motavafet bashad az hamdige kam mikonim
            return number1 - bigNumber(number2.num, number2.len, !number2.sign);
        
    }
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

    return bigNumber(subtractionRes, resultLen, resSign);
    }

    
    else{   //age alamat motafavet bashad ba ham jam mikonim
        return number1 + bigNumber(number2.num, number2.len, !number2.sign);
    }
}



int main(){
    bigNumber num(-100);
    bigNumber num2("50");
    bigNumber num3 = num + num2;
    
    num.printNum();
    num2.printNum();
    num3.printNum();
    // num2.printNum();
}