#include <iostream>
#include <iomanip>
#include <string_view>
#include <limits>
using namespace std;

struct Numbers{
    double first{};
    double second{};
};

Numbers get_numbers(){
    struct Numbers num{};
    while (true){
        cin >> num.first >> num.second;
        // 检测输入的值是否是double类型
        if (cin.good()){
            break;
        }
        else{
            cin.clear();
            // 清除极大个字符，遇到换行符就停止
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "must be a number" << '\n';
            continue;
        }
    }
    return num;
}

string get_operation(){
    string operation{};
    cout << "plz choose your operation in '+-*/'" << '\n';
    while (true){
        cin >> operation;
        // 判断 operation 是否在 "+-*/" 之内
        // 这里面的 != string::npos 是不等于"找不到"的意思
        if (string("+-*/").find(operation) != string::npos){
            break;
        }
        else{
            cerr << "not supported" << '\n';
            continue;
        }
    }
    return operation;
}

double addition(const Numbers& num){
    return num.first + num.second;
}

double subtraction(const Numbers& num){
    return num.first - num.second;
}

double multiplication(const Numbers& num){
    return num.first * num.second;
}

double division(const Numbers& num){
    return num.first / num.second;
}

int main(){
    Numbers num = get_numbers();
    string operation = get_operation();
    if (operation == "+"){
        cout << addition(num) << '\n';
    }
    else if (operation == "-"){
        cout << subtraction(num) << '\n';
    }
    else if (operation == "*"){
        cout << multiplication(num) << '\n';
    }
    else if (operation == "/"){
        if (num.second != 0){
            cout << division(num) << '\n';
        }
        else{
            cerr << "being divided by zero is wrong";
        }
    }
    return 0;
}