/* 
* Integrated test
* 
* Only need to include dora.hpp header file.
*/
#include<iostream>
#include "dora.hpp"


/* 
* Test assert_equal
* 
* Objects to be asserted must implement operator == and !=.
*/
void test_assert_equal() {
    dora::TestCase test_case(__FILE__, __func__);

/// Objects of the same numeric type
    test_case.pool = [](){
        dora::assert_equal(__LINE__, 5, 6);
    };

/// Variables of the same numeric type
    test_case.pool = [](){
        int a = 0;
        int b = 0;
        dora::assert_equal(__LINE__, a, b);
    };

/// Variables of different numeric types
    test_case.pool = [](){
        int aa = 10;
        float bb = 10.0;
        dora::assert_equal(__LINE__, aa, bb);
    };

    test_case.all();
}


/* 
* Test assert_true with expression
* 
* Expression can be
*     1. Any expression that is evaluated to be a boolean;
*     2. A lambda function that returns a boolean.
*     3. A regular function that returns a boolean. See next example.
*     4. A method that returns a boolean. See test_assert_true_with_method.
*/
void test_assert_true() {
    dora::TestCase test_case(__FILE__, __func__);

/// Can be a simple expression
    test_case.pool = [](){
        // Failed.
        dora::assert_true(__LINE__, 5==6);
    };

/// Can be a lambda function that returns bool
    test_case.pool = [](){
        // Failed. Not true.
        dora::assert_true(__LINE__, [](){ return (5==7);}());
    };

    test_case.all();
}


// Test function
bool bool_func_test(int a, int b) {
    if (a == b) {
        return true;
    } else {
        return false;
    }
}

void test_assert_true_with_function() {
    dora::TestCase test_case(__FILE__, __func__);

/// Pass function as a parameter
    test_case.pool = [](){
        // True
        dora::assert_true(__LINE__, &bool_func_test, 2, 3);
    };
    test_case.all();
}


// A class for testing assert true with method
class Speelgoed {
public:
    bool func(int a, int b) {
        if (a != b) {
            return false;
        } else {
            return true;
        }
    }

    int func_int(int a, int b) {
        if (a != b) {
            return 10;
        } else {
            return 111;
        }
    }
};

/// When passing a method to assert_true, must pass an object as the second
/// argument.
void test_assert_true_with_method() {
    dora::TestCase test_case(__FILE__, __func__);

    test_case.pool = [](){
        Speelgoed test_object;
        // Assert true with method
        dora::assert_true(__LINE__, test_object, &Speelgoed::func, 4, 5);
    };
    test_case.all();
}


/* 
* Assert throw
* 
* Function assert_throw invokes a function or method using the parameters passed
* in to assert if an error, type of which is given as a template parameter, is
* thrown.
*/
// Test error type to be thrown.
class TestError : public std::exception {
public:
    virtual std::string get_header() {
        return "TestError";
    }
};

// Test func that throws error.
void func(int a, int b) {
    if (a != b) {
        throw TestError();
    }
}

/// Use assert_throw on a free function.
void test_assert_throw() {
    dora::TestCase test_case(__FILE__, __func__);

/// Expects an error to be thrown, and it does.
    test_case.pool = [](){
        dora::assert_throw<TestError>(__LINE__, func, 4, 5);
    };

/// Expects an error to be thrown, but it doesn't.
    test_case.pool = [](){
        dora::assert_throw<TestError>(__LINE__, func, 5, 5);
    };

    test_case.all();
}


// A class for testing method throw
class Toy {
public:
    bool func(int a, int b) {
        if (a != b) {
            throw TestError();
        }    
        return false;
    }
};

/// Use assert_throw with a method.
void test_assert_throw_with_method() {
    dora::TestCase test_case(__FILE__, __func__);

/// Expects method to throw error, and it does. Okay
    test_case.pool = [](){
        Toy test_object;
        dora::assert_throw<TestError>(__LINE__, test_object, &Toy::func, 4, 5);
    };

/// Expects method to throw an error, but it doesn't. Assertion failed.
    test_case.pool = [](){
        Toy test_object;
        dora::assert_throw<TestError>(__LINE__, test_object, &Toy::func, 5, 5);
    };
    test_case.all();
}


/*
* Run all test functions in one place.
*/
int main(int argc, char *argv[]) {
/// Assert equal
    test_assert_equal();

/// Assert true
    test_assert_true();
    test_assert_true_with_function();
    test_assert_true_with_method();

/// Assert throw
    test_assert_throw();
    test_assert_throw_with_method();
}