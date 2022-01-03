/*
* HEADER assert.hpp
* 
* INCLUDE errors.hpp
*/
#ifndef DORA_ASSERT_HPP_
#define DORA_ASSERT_HPP_

#include <string>
#include <vector>
#include "errors.hpp"


namespace dora { // namespace dora


/*
* Assert equal
* 
* TEMPLATE
*     Ta / Tb : Typename of the object to be compared.
*
* ARGUMENTS
*     line (int) : Line number in the test file where
*         this assertion function is invoked.
*
*     a (Ta) / b (Tb) : Objects that are asserted to be equal.
*          However, these two object must have'!=' or '=='
*          operators implemented.
*/
template <typename Ta, typename Tb>
void assert_equal(int line, const Ta& a, const Tb& b) {
    if (a != b) {
        std::string errmsg = "Assert equal failed.";
        throw AssertionError(errmsg, line);
    }
}


/*
* Assert true on expression
*
* ARGUMENTS
*     line : Line number of the line at which assertion
*         function is invoked.
*
*     expr (bool) : A boolean type expression, or a lambda
*         function.
*/
void assert_true(int, bool); 


/*
* Assert true on function pointer
*
* ARGUMENTS
*     line : Line number of the line at which assertion
*         function is invoked.
*
*     func : A function that must return a boolean value.
*
*     args : Arguments for function call.
*/
template <class... Args>
void assert_true(int line, bool (*func)(Args...), Args... args) {
    if ((*func)(args...) != true) {
        std::string errmsg = "Assert true failed. Function returns false.";
        throw AssertionError(errmsg, line);
    }
}

/*
* Assert true on method
* 
* ARGUMENTS
*     line : Line number of the line at which assertion
*         function is invoked.
*
*     obj : An instance of class C.
*
*     method : A method that must return a boolean value.
*
*     args : Arguments for function call.
*/
template <class C, typename... Args>
void assert_true(int line, C& obj, bool (C::*method)(Args...), Args... args) { 
    if ((obj.*method)(args...) != true) {
        std::string errmsg = "Assert true failed. Method returns false.";
        throw AssertionError(errmsg, line);
    }
}


/*
* Assert false on expression
*
* ARGUMENTS
*     line : Line number of the line at which assertion
*         function is invoked.
*
*     expr (bool) : A boolean type expression, or a lambda
*         function.
*/
void assert_false(int, bool);


/*
* Assert false on function pointer
*
* ARGUMENTS
*     line : Line number of the line at which assertion
*         function is invoked.
*
*     func : A function that must return a boolean value.
*
*     args : Arguments for function call.
*/
template <class... Args>
void assert_false(int line, bool (*func)(Args...), Args... args) {
    if ((*func)(args...) == true) {
        std::string errmsg = "Assert false failed. Function returns true.";
        throw AssertionError(errmsg, line);
    }
}


// Assert false on method
template <class C, typename... Args>
void assert_false(int line, C* obj, bool (C::*method)(Args...), Args... args) {
    if ((obj->*method)(args...) == true) {
        std::string errmsg = "Assert false failed. Method returns true.";
        throw AssertionError(errmsg, line);
    }
}



/*
* Assert throw on function
*
* TEMPLATE
*     E : Exception class of which an error is expected
*         to be thrown.
*
*     T : Return type of the function.
*
*     Args : Variadic parameter pack for function invocation.
*
* ARGUMENTS
*     line (int) : Line number to which this assert function
*         is invoked.
*
*     function : Function which is to be invoked inside assertion
*         function.
*
*     args : Arguments for function invocation.
*/
template <class E, class T, class... Args>
void assert_throw(int line, T (*function)(Args...), Args... args) {
    E error_ptr;
    bool error_thrown = false;
    try {
        (*function)(args...);
    } catch (E& error_ptr) {
        error_thrown = true;
    }
    // If error not thrown, raise error.
    if (!error_thrown) {
        std::string errmsg = error_ptr.get_header()
                             + " was not thrown by function.";
        throw AssertionError(errmsg, line);
    }   
}

/*
* Assert throw on method
*
* TEMPLATE
*     E : Exception class in which the error shall be
*         thrown.
*
*     C : Class on which the method is defined.
*
*     T : Return type of the function to be invoked.
*
*     Args : Variadic pack for function invocation arguments.
*
* ARGUMENTS
*     line (int) : Line number to the line where assertion
*         function is invoked.
*
*     obj : An instance of class C.
*
*     method : Pointer to the method to be invoked in assertion
*         function.
*
*     Args : Arguments for method invocation.
*
* EXAMPLE
*     TestClass obj;
*     assert_throw<ErrorClass>(
*         __LINE__, &obj, &TestClass::method, arg1, arg2);
*/
template <class E, class C, typename T, typename... Args>
void assert_throw(int line, C& obj, T (C::*method)(Args...), Args... args) {
    E error_ptr;
    bool error_thrown = false;
    try {
        (obj.*method)(args...);
    } catch (E& error_ptr) {
        error_thrown = true;
    }
    // If error not thrown, raise error.
    if (!error_thrown) {
        std::string errmsg = error_ptr.get_header()
                             + " was not thrown by method.";
        throw AssertionError(errmsg, line);
    }
}


} // end namespace dora
#endif