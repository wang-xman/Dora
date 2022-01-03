/*
* HEADER case.hpp
* 
* INCLUDE errors.hpp
*/
#ifndef DORA_CASE_HPP_
#define DORA_CASE_HPP_

#include <string>
#include <vector>
#include "errors.hpp"


namespace dora { // namespace dora


// Case pool is a container of function pointers.
class CasePool {
public:
    CasePool() {}
    std::vector<void (*)()> function_ptr;
    
    void operator=(void(*)());
};


class TestCase {
protected:
    std::string current_test_file_ = "";
    std::string current_test_func_ = "";

public:
    CasePool pool;
    TestCase(const std::string, const std::string);
    virtual void all();
};


} // end namespace dora
#endif