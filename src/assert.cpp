/*
* SOURCE assert.cpp
*/
#include "assert.hpp"

namespace dora { // namespace dora


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
void assert_true(int line, bool expr) {
    if (expr != true) {
        std::string errmsg = "Assert true failed. "
                             "Expression evaluated false.";
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
void assert_false(int line, bool expr) {
    if (expr == true) {
        std::string errmsg = "Assert false failed. "
                             "Expression evaluated true.";
        throw AssertionError(errmsg, line);
    }
}


} // end namespace dora