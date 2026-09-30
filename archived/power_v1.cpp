#include <iostream>
#include <cmath>
#include <cstdlib>
#include <numeric>
#include <string>
#include <stdexcept>
#include <regex>
#include <iomanip>
using namespace std;

struct irrational_number : runtime_error{
    irrational_number() : runtime_error("its meaning less"){}
};

struct zeroPoweredBy_zero : runtime_error{
    zeroPoweredBy_zero() : runtime_error("0 powered by 0 is meaningless"){}
};

struct even_dominator : runtime_error{
    even_dominator() : runtime_error("even root of negative number is meaningless"){}
};

struct Numbers{
    string first{};
    string second{};
};

struct Fraction{
    long long numerator{};
    long long denominator{1};
};

Fraction get_fraction(){
    struct Fraction f{};
    return f;
}



bool is_validNum(const string& num){
    // 注意+-和.n是可有可无的，要用"?"
    static const regex re (R"(^[+-]?[0-9]+(\.[0-9]+)?$)");
    return regex_match(num, re);
}

Numbers get_number(){
    struct Numbers num{};
    while (true){
        // 初始化为double类型，否则string永远good
        cin >> num.first >> num.second;
        if (is_validNum(num.second) && is_validNum(num.first)){
            break;
        }
        else{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "must be a number" << '\n';
            continue;
        }
    }
    return num;
}

Fraction reduction(const Numbers& num, Fraction& f){
    int numerator{};
    int common_factor{};
    int result{};
    double is_zero{};
    is_zero = stod(num.second);
    // 如果num.second是0，则会删除0导致空字符，从而输出stod，走不到throw
    if (is_zero != 0){
        int digits{};
        // 复制一份再改
        string firstNumber = num.second;
        if (firstNumber.find('.') != string::npos){
            // stod进行显示转换
            size_t position1 = firstNumber.find('.');
            digits = size(firstNumber) - position1 - 1;
            numerator = stod(firstNumber.erase(position1, 1));
        }
        /* 行不通，因为如果是12.34等就失效
        int digits{};
        digits = size(firstNumber) - 1;
        */
        for (int i{}; i < digits; ++i){
            f.denominator *= 10;
        }
        int zero1_count{};
        for (int i{0}; i < firstNumber.size() && firstNumber[i] == '0'; ++i){
            ++zero1_count;
        }
        numerator = stod(firstNumber.erase(0, zero1_count));
        /* 可惜的是这里判断的是去掉零之后的数字的长度，很显然错误
        int digits{};
        while (numerator > 0){
            numerator /= 10;
            ++digits;
        }
        for (int i{}; i < digits; ++i){
            denominator *= 10;
        }
        */
        common_factor = gcd(numerator, f.denominator);
        result = f.denominator / common_factor;
        numerator = numerator / common_factor;
    }
    f.denominator = result;
    f.numerator = numerator;
    return f;
}

double power(double x, const Numbers& num){
    return pow(x, stod(num.second));
}

double read_input(const Numbers& num, Fraction& f){
    double result{};
    double x = stod(num.first);
    f = reduction(num, f);
    if (stod(num.first) <= 0 && !isfinite(stod(num.second)) 
        && floor(stod(num.second)) != stod(num.second)){
        throw irrational_number();
    }
    else if (stod(num.first) == 0 && stod(num.second) <= 0){
        throw zeroPoweredBy_zero();
    }
    else if (stod(num.first) <= 0 && f.denominator % 2 == 0 && f.denominator != 0){
        throw even_dominator();
    }
    else if (stod(num.first) <= 0 && f.denominator & 2 != 0 && f.numerator){
        double first_number{};
        first_number = abs(stod(num.first));
        result = power(first_number, num);
        if (f.numerator % 2 == 0){
            result = result;
        }
        else if (f.numerator % 2 != 0){
            result = -result;
        }
    }
    else{
        result = power(x, num);
    }
    return result;
}

char ask_user(){    
    char user_input{};
    cout << "continue(Y/n)";
    while (true){
        cin >> user_input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (user_input == 'Y' || user_input == 'y'||
            user_input == 'n' || user_input == 'N'){
            return user_input;
        }
        else{
            cerr << "only in Y and n" << '\n';
            continue;
        }
    }
}

void calculate(){
    while (true){
        while (true){
        Numbers num = get_number();
        Fraction f = get_fraction();
        try{
            cout << read_input(num, f) << '\n';
            break;
            }
        catch (const exception& e){
            cout << e.what() << '\n';
            continue;
            }
        }
        char user_input{};
        user_input = ask_user();
        if (user_input == 'n' || user_input == 'N'){
            break;
        }
        else if (user_input == 'y' || user_input == 'Y'){
            continue;
        }
    }
}

int main(){
    cout << fixed << setprecision(10);
    calculate();
    return 0;
}