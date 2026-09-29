#include <iostream>
#include <iomanip>
#include <string_view>
#include <limits>
#include <map>
using namespace std;

struct Numbers{
    double first{};
    double second{};
};

Numbers get_numbers(){
    struct Numbers num{};
    while (true){
        cin >> num.first >> num.second;
        if (cin.good()){
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

string get_operation(){
    string operation{};
    cout << "plz choose your operation in '+-*/'" << '\n';
    while (true){
        cin >> operation;
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
    if (num.second == 0){
        throw invalid_argument("dividing zero is wrong");
    }
    else{
        return num.first / num.second;        
    }
}

int main(){
    /*
    创建一个名字是 operations 的字典
    键类型为string，值类型定为指向double(const Numbers&)类型函数的指针
    类型位置不需要名字，故写 (*)
    */
    map<string, double (*)(const Numbers&)> operations{};
    // 这四行填充字典，注意函数名后面没有括号，因为没有调用函数
    operations["+"] = addition;
    operations["-"] = subtraction;
    operations["*"] = multiplication;
    operations["/"] = division;
    Numbers num = get_numbers();
    string operation = get_operation();
    try{
        // 查找对应的operation然后返回指针，从而根据函数指针调                                                                                                                                                         用函数
        cout << operations[operation](num) << '\n';
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}