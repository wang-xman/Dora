/*
    HEADER case.hpp
*/
#ifndef DORA_CASE_HPP_
#define DORA_CASE_HPP_

#include <string>
#include <vector>
#include "errors.hpp"

namespace dora {

// Case pool is a container of function pointers.
class CasePool {
public:
    CasePool() {}
    std::vector<void (*)()> function_ptr;
    
    void operator=( void(*)() );
};


class TestCase {
protected:
    std::string current_test_file = "";
    std::string current_test_func = "";

public:
    CasePool pool;
    TestCase(const std::string, const std::string);
    virtual void all();
};


} // end dora
#endif