/*
    SOURCE errors.cpp
*/
#include "errors.hpp"

namespace dora {

// Constructors
AssertionError::AssertionError(const std::string& msg) : message_body(msg) {}

AssertionError::AssertionError(const std::string& msg, const int& line)
        : message_body(msg), line_number(line) {}

AssertionError::AssertionError(const std::string& msg, const std::string& fname)
        : message_body(msg), file_name(fname) {}

AssertionError::AssertionError(const std::string& msg, const std::string& fname,
        const int& line) : message_body(msg), file_name(fname), line_number(line) {}

// Setters
void AssertionError::set_line(const int& line)
{
    line_number = line;
}

void AssertionError::set_header(const std::string& header_str)
{
    header = header_str;
}

void AssertionError::set_file_name(const std::string& fname)
{
    file_name = fname; 
}

// Getters
std::string AssertionError::get_header()
{
    return header;
}

std::string AssertionError::get_file_name()
{
    return file_name;
}

std::string AssertionError::get_message_body()
{
    return message_body;
}

std::string AssertionError::full_message()
{
    std::string without_header = get_message_body() + ")";
    if (line_number > 0) { // append line number
        without_header = "Line: " + std::to_string(line_number)
                         + ", " + without_header; 
    }
    if (file_name != "") { // append file name
        without_header = "File: " + file_name + ", " + without_header;
    }
    return header + "(" + without_header;
}

void AssertionError::make_show()
{
    std::cout << full_message() << std::endl;
}

} // end dora