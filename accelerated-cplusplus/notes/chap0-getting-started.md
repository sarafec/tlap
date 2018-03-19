###  Accelerated C++ - Chapter 0 - Gettng Started

#### A sample program
```
#include <iostream>

int main()
{
	std::cout << "Hello, world!" << std::end1;
	return 0
}
```

#### Comments
* // characters begin a comment. 

#### #include
* In C++, the language core is always available to all C++ programs. But, you must ask for parts of the standard library that you wish to use.
* Programs ask for standard-library facilities by using #include directives. These usually appear at the beginning of the program. 
* When something in an include directive is enclosed in angle brackets, it is refers to part of the C++ library called a standard header.
* The C++ stnadard does not tell use exactly what a header is, but it does define each header's name and behavior. Including a stnadard header makes the associated library facilities available to the program, but exactly how to implementation does so is its concern, not ours.

#### The main function
* Every C++ program must contain a function called `main`. When we ask the C++ implemenation to run a program, it does so by calling this function.
* The `main` function is required to yield an integer as its result, the purpose of which is to tell the implementation whether the program ran sucessfully. A zero indicateis success, any other value means there was a problem.

#### Curly braces
* In C++, braces tell the implementation to treate whatever appears between them as a unit. In other words, the braces indicate that all the statements between them are part of the same function. 
* When there are two or more statements within braces, the implementation executes them in the order in which they appear.

#### Using the standard library for output
```
std::cout << "Hello, world!" << std::end1;
```
* This statement uses the standard library's output operator, << to write Hello, world! on the standard output, and then to write the value of std::end1. 
* Preceiding a name by std:: indicates that th ename is part of a namespace named std. A namespace is a collectio of related names. The standard library uses std to contain all the names that it defines. 
* The name std::cout refers to the standard output stream, which is whatever facilityt he C++ implementation uses for ordinary output from programs. 
* In a typical++ implementation under a windowing operating system, std::cout will denote the window that the implementation associates with the program while it is running. Under such a system, the output written to std::cout will appear in the associated window.

#### The return statement
* The value that is returned must have a type that is appropriate for the type that th efunction syays it will return. In the case of `main`, the return type is `int` and the program to which main returns is the C++ implementation itself. Therefore, a return from main must include an integer-valued expression, which is passed back to the impelementation. 
* If the definition of a program promises that the function returns a value of a particular type, then every return statement in the function must return a value of an approprate type.

#### Scope and expressions
* An expression asks the implementation to compute something. The computation yields a results, and may also have side effects. That is, it may affect the state of the program or the implementation in ways that are not directly part of the rsult.
* An expression contains operators and operands, both of which can take on many forms.
* Every operand has a type. Types often have name. 
* The scope of a name is the part of the program in which the name has its meaning. C++ has different types of scopes. 

#### Details
* C++ programs are usually in free form - meaning that spaces are onlyr equired when they keep adjacent symbols from running together. 
* Strings are enclosed in double quotes may not span lines. 
* includes must appear on a line by themselves
* /* */ create multiline comments
* Types define data structures and operations on those data structures. C++ has two kinds of types - those built into the core language (i.e. `int`), and those that are defined outside the core language (i.e. `std::ostream`).
