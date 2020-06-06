#include <iostream>
#include <limits>
#include <sstream>
#include <optional>
#include <utility>
#include <deque>
#include <unordered_map>
//#include "test_runner.h"

using namespace std;


class Combiner
{
public:
    Combiner() = delete;
    Combiner(int64_t, int64_t);
    void PerformSum();
    void PrintResult(std::ostream&);

private:
    const int64_t first_;
    const int64_t second_;

    std::optional<int64_t> result_ = std::nullopt;

    bool sum_is_overflow() const;
};


Combiner InitCombiner(std::istream&);


Combiner::Combiner(int64_t f, int64_t s) : first_(f), second_(s) {}


Combiner InitCombiner(std::istream& input)
{
    int64_t f, s;
    input >> f >> s;
    return Combiner(f, s);
}


void Combiner::PerformSum()
{
    if (!sum_is_overflow())
        result_ = first_ + second_;
}


void Combiner::PrintResult(std::ostream& output)
{
    if (result_)
    {
        output << *result_;
    }
    else
    {
        output << "Overflow!";
    }
}


bool Combiner::sum_is_overflow() const
{
    if (first_ >= 0 && second_ >= 0)
    {
        const int64_t max_ = INT64_MAX;
        const int64_t diff = max_ - first_;
        return second_ > diff;
    }
    if (first_ < 0 && second_ < 0)
    {
        const int64_t min_ = INT64_MIN;
        const int64_t diff = min_ - first_;
        return second_ < diff;
    }
    return false;
}


int main(){
    Combiner cmb = InitCombiner(cin);
    cmb.PerformSum();
    cmb.PrintResult(cout);
    return 0;
}



/*
enum SIGN{
    PLUS,
    MINUS
};

struct Number{
    deque<int> value;
    SIGN sign;
};

const Number LOWLIM = {{9,2,2,3,3,7,2,0,3,6,8,5,4,7,7,5,8,0,9}, SIGN::MINUS};
const Number UPLIM  = {{9,2,2,3,3,7,2,0,3,6,8,5,4,7,7,5,8,0,8}, SIGN::PLUS};

bool LeftBigger(const Number& lhs, const Number& rhs){
    if(lhs.sign!=rhs.sign){
        return lhs.sign==SIGN::PLUS;
    }
    if(lhs.value.size() != rhs.value.size()){
        return lhs.sign==SIGN::PLUS ? lhs.value.size()>rhs.value.size() : lhs.value.size()<rhs.value.size();
    }
    for(size_t i=0; i<lhs.value.size(); i++){
        if(lhs.value[i]!=rhs.value[i]){
            return lhs.value[i]>rhs.value[i];
        }
    }
    return false; 	//here numbers equal
}

ostream& operator<<(ostream& out, const Number& num){
    if(num.sign==SIGN::MINUS){out << "-";}
    for(size_t i=0; i<num.value.size(); i++){
        out << num.value[i];
    }
    return out;
}

const unordered_map<SIGN, uint64_t> LIMIT = {{SIGN::PLUS, 9223372036854775807u}, {SIGN::MINUS, 9223372036854775808u}};

deque<int> ReadValue(istream& input){
   deque <int> value;
    size_t idx = 0;
    while (isdigit(input.peek())) {
      value.push_back(input.get() - '0');
      idx++;
    }
    return value;
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


void ExtrapolateZeros(Number& num, size_t new_size){
    size_t old_size = num.value.size();
    for(size_t i=0; i<new_size - old_size; i++){
        num.value.push_front(0);
    }
}

Number AddNumbers(Number lhs, Number rhs){
    size_t new_len = max(lhs.value.size(), rhs.value.size())+1;
    ExtrapolateZeros(lhs, new_len);
    ExtrapolateZeros(rhs, new_len);
    Number res;
    res.value = rhs.value;
    int residue = 0;
    for(int i=rhs.value.size()-1; i>=0; i--){
        int num = lhs.value[i] + rhs.value[i];
        if(num>10){
            res.value[i] = num-10 + residue;
            residue = 1;
        }
        else{
            res.value[i] = num + residue;
            residue = 0;
        }
    }
    if(res.value[0]==0){res.value.pop_front();}
    res.sign = lhs.sign;
    return res;
}


int64_t ConvertToInt(const Number& num){
    int64_t res = 0;
    for(size_t i=0; i<num.value.size(); i++){
        res*=10;
        res-=num.value[i];
    }
    if(num.sign==SIGN::PLUS){
        res*=-1;
    }
    return res;
}


void Process(istream& input=cin, ostream& output=cout){
    Number lhs = ReadNumber(input);
    Number rhs = ReadNumber(input);
    if(lhs.sign==rhs.sign){
        Number res = AddNumbers(lhs, rhs);
        if(LeftBigger(res, LOWLIM) && LeftBigger(UPLIM, res)){
            output << res;
        }
        else{
            output << "Overflow!";
        }
    }
    else{
        int64_t num_1 = ConvertToInt(lhs);
        int64_t num_2 = ConvertToInt(rhs);
        int64_t res = num_1 + num_2;
        output << res;
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
//        in << "79 34";
//        stringstream out;
//        Process(in, out);
//        ASSERT_EQUAL(out.str(), "113");
//    }
//    {
//        stringstream in;
//        in << "-459 -500";
//        stringstream out;
//        Process(in, out);
//        ASSERT_EQUAL(out.str(), "-959");
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
*/
