#include <iostream>
#include <limits>
#include <sstream>
#include "test_runner.h"

using namespace std;


bool Increment(int64_t& num){
    if(num<INT64_MAX){
        num++;
        return true;
    }
    return false;
}

bool Decrement(int64_t& num){
    if(num>INT64_MIN){
        num--;
        return true;
    }
    return false;
}


void Process(istream& input=cin, ostream& output=cout){
    int64_t lhs, rhs;
    input >> lhs >> rhs;
    bool success = true;
    if(rhs>0){
        while(rhs!=0 && success){
            success = Increment(lhs);
            rhs--;
        }
    }
    else {
        while(rhs!=0 && success){
            success = Decrement(lhs);
            rhs++;
        }
    }

    if(success){
        output << lhs;
    }
    else {
        output << "Overflow!";
    }
}


void Tests(){
    {
        stringstream in;
        in << 5 << -3;
        stringstream out;
        Process(in, out);
        ASSERT_EQUAL(out.str(), "2");
    }
    {
        stringstream in;
        in << 4567890123456789012 << 5678901234567890123;
        stringstream out;
        Process(in, out);
        ASSERT_EQUAL(out.str(), "Overflow!");
    }
    {
        stringstream in;
        in << 1 << 9223372036854775807;
        stringstream out;
        Process(in, out);
        ASSERT_EQUAL(out.str(), "Overflow!");
    }
    {
        stringstream in;
        in << "-9223372036854775808" << -1;
        stringstream out;
        Process(in, out);
        ASSERT_EQUAL(out.str(), "Overflow!");
    }
    {
        stringstream in;
        in << "-9223372036854775808" << 1;
        stringstream out;
        Process(in, out);
        ASSERT_EQUAL(out.str(), "-9223372036854775807");
    }


}


int main(){
    TestRunner tr;
    RUN_TEST(tr, Tests);

//    int64_t x, y;
//    cin >> x >> y;
//    SummarizeVals(x, y);
    //SummarizeVals(5, -6);
    //SummarizeVals(4567890123456789012, 5678901234567890123 );
    return 0;
}
