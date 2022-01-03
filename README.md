# Dora - A super light-weight C++ unittest library
Dora, the explorer! Dora provides easy-to-use test case containers and
assertion functions. Without heavy overhead, Dora is suitable for small
projects.

## Version information
Version: 0.0.1
Updated: 3 January 2022.
Compile: g++ 9.3.0 on Ubuntu 20.04 / clang Apple LLVM 9.1.0 (clang-902.0.39.2)

## Quick start guide
To create a test case pool, simply instantiate
`dora::TestCase` class,
```
dora::TestCase test_case([File_name], [Function_name]);
```
or just use the builtin identifiers
```
dora::TestCase test_case(__FILE__, __func__);
```

A test case can be added to the pool by assigning a lambda function to
`test_case.pool`, for example,
```
test_case.pool = [](){ // test 1
    dora::assert_equal(__LINE__, 5, 6);
};

test_case.pool = [](){ // test 2
    int a = 0;
    int b = 0;
    dora::assert_equal(__LINE__, a, b);
};

test_case.pool = [](){ // test 3
    int aa = 10;
    float bb = 10.0;
    dora::assert_equal(__LINE__, aa, bb);
};

test_case.all(); // run all tests 1, 2, 3.
```
where `test_case.all()` runs all test cases stored in the pool. See examples
in unit test for details.

## Assertion functions
In order to record the line number in the test file, the first argument of
all assert functions is an integer and it is usually given the builtin
identifier `__LINE__`. All assertion functions thrown `ASSERTION_ERROR` if
assertion fails.

* Assert equal
```
assert_equal(int line, const Ta&, const Tb&)
``` 
compares two objects of types `Ta` and `Tb` by calling operator `==` on them.
Two objects in the comparison are not required to be the same type, yet both
objects must implement operators `==` and `!=`.

* Assert true
```
assert_true(int line, bool expr)
``` 
asserts if `expr` is evaluated to be `true`.

* Assert true on free function
```
assert_true(int line, bool (*func)(Args...), Args... args)
```
asserts if function invocation returns `true`.

* Assert true on method
```
assert_true(int line, C& obj, bool (C::*method)(Args...), Args... args)
```
asserts if method invocation returns `true`. The second argument must be
an object on which the method is called.

* Assert false
```
assert_false(int, bool expr)
``` 
asserts if `expr` is evaluated to be `false`.

* Assert false on free function
```
assert_false(int line, bool (*func)(Args...), Args... args)
```
asserts if function invocation returns `false`.

* Assert false on method
```
assert_false(int line, C& obj, bool (C::*method)(Args...), Args... args)
```
asserts if method invocation returns `false`. The second argument must be
an object on which the method is called.

* Assert throw on a free function
```
template <class E, class T, class... Args>
void assert_throw(int line, T (*function)(Args...), Args... args)
```
asserts if function invocation throws an error of type `E`.

* Assert throw on a method
```
template <class E, class C, typename T, typename... Args>
void assert_throw(int line, C& obj, T (C::*method)(Args...), Args... args)
```
asserts if method invocation throws an error of type `E`. The second argument
is an object on which the method is invoked.