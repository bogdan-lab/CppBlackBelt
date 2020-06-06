#include <iostream>
#include <limits>
#include <sstream>
#include <optional>
#include <utility>
#include <unordered_map>
//#include "test_runner.h"

using namespace std;

enum SIGN{
    PLUS,
    MINUS
};

struct Number{
    uint64_t value;
    SIGN sign;
};

//                                                        5247764967072089291
const unordered_map<SIGN, uint64_t> LIMIT = {{SIGN::PLUS, 9223372036854775807u}, {SIGN::MINUS, 9223372036854775808u}};

optional<uint64_t> Add(uint64_t lhs, uint64_t rhs, SIGN sign){
    uint64_t res = lhs + rhs;
    if(res < LIMIT.at(sign)){
        return res;
    }
    return nullopt;
}


SIGN GetSign(const int64_t& num){
    if(num>=0){
        return SIGN::PLUS;
    }
    return SIGN::MINUS;
}


uint64_t ReadValue(istream& input){
    uint64_t int_part = 0;
    while (isdigit(input.peek())) {
      int_part *= 10;
      int_part += input.get() - '0';
    }
    return int_part;
}


Number ReadNumber(istream& input){
    Number num;
    while(!isdigit(input.peek()) && input.peek()!='-'){
        input.get();
    }
    if(input.peek()!='-'){
        num.value = ReadValue(input);
        num.sign = SIGN::PLUS;
    }
    else{
        input.ignore(1);
        num.value = ReadValue(input);
        num.sign = SIGN::MINUS;
    }
    return num;
}


pair<Number, Number> ReadNumbers(istream& input){
    Number lhs = ReadNumber(input);
    Number rhs = ReadNumber(input);
    return make_pair(lhs, rhs);
}



void Process(istream& input=cin, ostream& output=cout){
    auto nums = ReadNumbers(input);
    optional<uint64_t> res;
    SIGN res_sign;
    if(nums.first.sign!=nums.second.sign){
        res = max(nums.first.value, nums.second.value) - min(nums.first.value, nums.second.value);
        res_sign = nums.first.value>nums.second.value ? nums.first.sign : nums.second.sign;
    }
    else{
        if(nums.first.value<=INT64_MAX && nums.second.value<=INT64_MAX){
            res = Add(nums.first.value, nums.second.value, nums.first.sign);
            res_sign = nums.first.sign;
        }
    }

    if(res){
        if(res_sign == SIGN::MINUS){output << "-";}
        output << res.value();
    }
    else {
        output << "Overflow!";
    }
}


//void Tests(){
//    {
//        stringstream in;
//        in << 5 << -3;
//        stringstream out;
//        Process(in, out);
//        ASSERT_EQUAL(out.str(), "2");
//    }
//    {
//        stringstream in;
//        in << "-5 3";
//        stringstream out;
//        Process(in, out);
//        ASSERT_EQUAL(out.str(), "-2");
//    }
//    {
//        stringstream in;
//        in << "4567890123456789012 5678901234567890123";
//        stringstream out;
//        Process(in, out);
//        ASSERT_EQUAL(out.str(), "Overflow!");
//    }
//    {
//        stringstream in;
//        in << "1 9223372036854775807";
//        stringstream out;
//        Process(in, out);
//        ASSERT_EQUAL(out.str(), "Overflow!");
//    }
//    {
//        stringstream in;
//        in << "-9223372036854775808 -1";
//        stringstream out;
//        Process(in, out);
//        ASSERT_EQUAL(out.str(), "Overflow!");
//    }
//    {
//        stringstream in;
//        in << "-9223372036854775808\n1";
//        stringstream out;
//        Process(in, out);
//        ASSERT_EQUAL(out.str(), "-9223372036854775807");
//    }
//    {
//        stringstream in;
//        in << "-9223372036854775808 9223372036854775807";
//        stringstream out;
//        Process(in, out);
//        ASSERT_EQUAL(out.str(), "-1");
//    }
//    {
//        stringstream in;
//        in << "-9223372036854775808 -9223372036854775808";
//        stringstream out;
//        Process(in, out);
//        ASSERT_EQUAL(out.str(), "Overflow!");
//    }
//}


int main(){
//    TestRunner tr;
//    RUN_TEST(tr, Tests);

    Process(cin, cout);

    return 0;
}
