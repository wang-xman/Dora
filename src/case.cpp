/*
    SOURCE case.cpp
*/
#include <iostream>
#include <string>
#include <vector>
#include "case.hpp"

namespace dora {

// Case pool
void CasePool::operator=( void(*ptr)() )
{
    function_ptr.push_back(ptr);
}

// Test case constructor
TestCase::TestCase(const std::string fname, const std::string funcname)
        : current_test_file(fname), current_test_func(funcname) {}

// Test case: run all tests
void TestCase::all()
{
    for (auto& func_ptr : pool.function_ptr) {
        try {
            func_ptr();
        } catch (AssertionError& err){
            if (current_test_file != "") {
                err.set_file_name(current_test_file);
            }
            err.make_show();
        }
    }
}

} // end dora