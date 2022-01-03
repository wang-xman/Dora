/*
* SOURCE errors.cpp
*/
#include "errors.hpp"

namespace dora { // namespace dora


/// Constructors
AssertionError::AssertionError(const std::string& msg) : message_body_(msg) {}

AssertionError::AssertionError(const std::string& msg, const int& line)
        : message_body_(msg), line_number_(line) {}

AssertionError::AssertionError(const std::string& msg, const std::string& fname)
        : message_body_(msg), file_name_(fname) {}

AssertionError::AssertionError(const std::string& msg, const std::string& fname,
        const int& line) : message_body_(msg), file_name_(fname), line_number_(line) {}

/// Setters
void AssertionError::set_line(const int& line) { line_number_ = line; }

void AssertionError::set_header(const std::string& header) { header_ = header; }

void AssertionError::set_file_name(const std::string& fname) {
    file_name_ = fname; 
}

/// Getters
std::string AssertionError::get_header() { return header_; }

std::string AssertionError::get_file_name() { return file_name_; }

std::string AssertionError::get_message_body() { return message_body_; }

std::string AssertionError::full_message() {
    std::string without_header = get_message_body() + ")";
    if (line_number_ > 0) { // append line number
        without_header = "Line: " + std::to_string(line_number_)
                         + ", " + without_header; 
    }
    if (file_name_ != "") { // append file name
        without_header = "File: " + file_name_ + ", " + without_header;
    }
    return header_ + "(" + without_header;
}

void AssertionError::make_show() {
    std::cout << full_message() << std::endl;
}


} // end namespace dora