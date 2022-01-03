/*
* HEADER errors.hpp
* 
* AssertionError is the base class to all errors thrown by
* all assertion functions.
*/
#ifndef DORA_ERRORS_HPP_
#define DORA_ERRORS_HPP_

#include <iostream>
#include <string>

namespace dora { // namespace dora


/*
* Assertion error
* 
* A very simple base class that stores error message body and
* line number.
*/
class AssertionError : public std::exception {
protected:
    std::string header_       = "ASSERTION_ERROR";
    std::string message_body_ = "";
    int line_number_          = -99;
    std::string file_name_    = "";

public:
/// Constructors
    explicit AssertionError(const std::string&);
    explicit AssertionError(const std::string&, const int&);
    explicit AssertionError(const std::string&, const std::string&);
    explicit AssertionError(const std::string&, const std::string&, const int&);
    ~AssertionError() throw() {} // both g++ and clang

/// Setters
    void set_line(const int&);
    void set_header(const std::string&);
    void set_file_name(const std::string&);

/// Getters
    std::string get_header();
    std::string get_file_name();
    std::string get_message_body();

/// Representation
    virtual std::string full_message();
    void make_show();
};


} // end namespace dora
#endif