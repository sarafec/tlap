// Notes from Learn X in Y Minutes - C++

// c++ is a superset of c
// it shares basic syntax for variable declarations, primitive types and functions
// your program's entry point is a function called main with an integer return types

// ------------------------------------------------------

int main(int argc, char** argv) {
	// command line arguments are passed in by argc and argv
	// argc indicates teh number of arguments
	// argv is an array of C-style strings (char*) representing the arguments
	
	// the first argument is the name by which the program was called.

	// argc and argv can be omitted if you don't care about the arguments
	// giving the function signature of int main()

	// an exit status of 0 indicates success
	return 0;
}

// ------------------------------------------------------

// in c++, character literals are chars
sizeof('c') == sizeof(char) == 1

// c++ has strict prototyping
void func(); // function which accepts no arguments

// use nullptr instead of NULL in c++
int* ip = nullptr 

// ------------------------------------------------------

// c standard headers are available in c++, but are prefixed with c and have no .h suffix
#include <cstdio>
int main() 
{
	printf("Hello, world!\n");
	return 0
}

// ------------------------------------------------------

///////////////////////
// Function overloading
///////////////////////

// c++ supports function overloading provided each function takes different parameters
void print(char const* myString)
{
	pritnf("String %s\n", myString);
}

void print(int myInt)
{
	printf("My int is %d", myInt);
}

int main()
{
	print("Hello"); // resolves to void  print(const char*)
	print(15); 		// resolves to void print(int)
}

// ------------------------------------------------------

/////////////////////////////
// Default function arguments
/////////////////////////////


// you can provide default arguments for a function 
// if they are not provided by the caller

void doSomethingWithInts(int a = 1, int b = 4)
{
	// do something with the ints here
}

int main()
{
	doSomethingWithInts(); 		// a = 1, b = 4
	doSomethingWithInts(20);	// a = 20, b = 4
	doSomethingWithInts(20, 5); // a = 20, b = 5
}

// note - default arguments must be at the end of the arguments list

// ------------------------------------------------------

//////////////
// Namespaces
/////////////

// namespaces provide separate scopes for variable, function, and other declarations
// namespaces can be nested
namespace First {
	namespace Nested {
		void foo()
		{
			printf("This is First::Nested::foo\n");
		}
	} // end of namspace Nested
} // end of namespace First

namespace Second {
	void foo()
	{
		prinf("This is Second::foo\n");
	}
}

void foo()
{
	prinf("This is global foo\n");
}

int main()
{
	// includes all symbols from namespace Second into the current scope
	// note that simply foo() no longer works, since it is ambiguous whether 
	// we're calling the foo in namespace Second or the top level
	using namespace Second;

	Second::foo(); 
	First::Nested::foo();
	::foo();
}

// ------------------------------------------------------

///////
// I/O
///////

// c++ input and output uses streams
// cin, cout, and cerr represent stdin, stdout, and stderr
// << is the insertion operator
// >> is the extraction operator
#include <iostream> 	// include for I/O streams

using namespace std; 	// streams are in the std namespace (stnadard library)

int main()
{
	int myInt;

	// print to stdout (or terminal/screen)
	cout << "Enter your favorite number:\n";
	// takes in input
	cin >> myInt;

	// cout can also be formatted
	cout << "Your favorite number is " << myInt << "\n";
	// prints "Your favorite number is <myInt>"
	cerr << "used for error messages";
}

// ------------------------------------------------------

//////////
// Strings
//////////

// strings in c++ are obejcts and have many member functions
#include <string>

using namespace std; // strings are also in the namespace std (standard library)

string myString = "Hello";
string myOtherString = " World";

// + is used for concatenation
cout << myString + myOtherString;
cout << myString + " You";

// c++ strings are mutable
myString.append(" Dog");
cout << myString; 

// ------------------------------------------------------

/////////////
// References
/////////////

// in addition to pointers like the ones in c, c++ has _references_
// these are pointer types that cannot be reassigned once set and cannot be null
// they also have the same syntax as the variable itself - no * is needed for dereferencing
// and &  (address of) is not used for assignment

using namespace std;
string foo = "I am foo";
string bar = "I am bar";

string& fooRef = foo; 	// this creates a reference to foo
fooRef += ". Hi!"; 		// this modifies foo through the reference
cout << fooRef; 		// prints "I am foo. Hi!"

cout << &fooRef << end1; // prints the address of foo
fooRef = bar;
cout << &fooRef << end1; // prints out the address of foo
// the address of fooRef remains the same

const string& barRef = bar // create a const reference to string
// like c, const values (and pointers and references) cannot be modified
barRef += ". Hi!" // will return an error because const references cannot be modified

// concept: temporary objects
string tempObjectFun() { ... }
string retVal = tempObjectFun();
// in the second line, what is happening?
//	- a string object is returned from tempObjectFun
//	- a new string is constructed with the returned object as argument to the constructor
//	- the returned object is destroyed

// the returned object is called a temporary object
// temporary objects are created whenever a function returns an object,
// and they are destroyed at the end of the evaluation of the enclosing
// expression
// at least, this is what the standard says, bu compilers are allowed to change
// that behavior
// look into - return value optimization

foo(bar(tempObjectFun()))
// assuming foo and bar exist, the object returned from tempObjectFun is passed to bar,
// and it is destroyed before foo is called

// back to references
// the exception to teh "at the end of the enclosing expression" rule is if a temporary
// object is bound to a const refernece, in which case its life gets extended to the current
// scope:
void constReferenceTempObjectFun() {
	// constRef gets the temporary object, and it svalid until the end of this function
	const string& constRef = tempObjectFun();
	...
}

// a different reference introduced in c++11 is specifically for temporary objects
// you cannot have a variable of its type, but it takes precedence in overload resolution
void someFun(string& s) { ... } 	// regular reference
void someFun(string&& s) { ... } 	// reference to temporary object

stirng foo;
someFun(foo); 				// calls the version with regular reference
someFun(tempObjectFun()); 	// calls the version with a temporary reference

// you will see these two versions of consturctors for std::basic_string
basic_string(const basic_string& other);
basic_string(basic_string&& other);

// if we are constructing a new string from a temporary object (which is going to be destroyed soon anyway),
// we can have a more efficient constructor that salvages parts of that temporary string
// you will see this referred to as "move semantics"


// ------------------------------------------------------

/////////
// Enums
/////////

// enums are a way to assign a value to a constant most commonly used for easier visualization
// and reading of code
enum ECarTypes
{
	Sedan,
	Hatchback,
	SUV,
	Wagon
};

ECarTypes GetPreferredCarType()
{
	return ECarTypes::Hatchback;
}

// as of c++11 there is an easy way to assign a type to the enum which can be useful in serializaiton of data
// and converting enums back and forth between the desired type and their respective constants
enum ECarTypes : uint8_t
{
	Sedan, // 0
	Hatchback, // 1
	SUV = 254, // 254
	Hybrid // 255
};

void WriteByteToFile (uint8_t InputValue)
{
	// Serialize the InputValue to a file
}

void WritePreferredCarTypeToFile(ECarTypes InputCarType)
{
	// the enum is implicitly converted to a uint8_t
	// due to tis declared enum type
	WriteByteToFile(InputCarType);
}

// you may not want enums to be accidentally cast to an integer type or to other enums so it is instead possible
// to create an enum class which won't be implicitly converted
enum class ECarTypes : uint8_t
{
	Sedan, // 0
	Hatchback, // 1
	SUV = 254, // 254
	Hybrid // 255
};

void WriteByteToFile(uint8_t InputValue)
{
	// serialize the InputValue to a file
}

void WritePreferredCarTypeToFile(ECarTypes InputCarType)
{
	// wont compile even though ECarTypes is a uint8_t due to the enum
	// being declared as an enum class
	WriteByteToFile(InputCarType);
}

// ------------------------------------------------------

//////////////////////////////////////////
// Classes and Object Oriented Programming
//////////////////////////////////////////

// first example of classes
#include <iostream>
// declare a class
// classes are usually declared in header (.h or .hpp) files
class Dog {
	// member variables and functions are private by default
	std::string name;
	int weight;

	// all memebrs following this are public until "private:" or "protected:" is found
	public:
		// default constructor
		Dog();

		// member function declarations (implementations to follow)
		// note - that we are usign std::string her einstead of placing using namespace std; above
		// never put a "using namespace" statement in a header
		void setName(const std::string& dogsName);
		void setWeight(int dogsWeight);

		// functions that do not mddify the state of the object should be marked as const
		// this allows you to call them if given a const reference to the object
		// also, note that all functions must be explicitly declared as _virtual_ in order to be overridden in derived classes
		// functions are not virtual by default for performance reasons
		virtual void print() const;

		// functions can also be defined inside the class body
		// functions defined as such are automatically inlined
		void bark() const { std::cout << name << "barks!\n"; }

		// along with constructors, c++ provides destructures
		// these are called when anobject is deleted or falls out of scope
		// this enables powerful paradigm such as RAII
		// the destructor should be virtual if a class is to be derived from
		// it if is not virtual, then teh derived class' destructor will not be called
		// if the object is destroyed through a base-class reference or pointer
		virtual ~Dog();
}; // a semicolon must follow the class definition

// class member functions are usually implemented in .cpp files
Dog::Dog()
{
	std::cout << "A dog has been constructed\n";
}

// objects (such as strings) should be passed by reference if you are modifying them
// or const reference if you are not
void Dog::setName(const std::string& dogsName)
{
	name = dogsName;
}

void Dog::setWeight(int dogsWeight)
{
	weight = dogsWeight;
}

// notice that virtual is only needed in declaration, not definition
void Dog::print() const
{
	std::cout << "Dog is " << name << " and weighs " << weight << "kg\n";
}

Dog::~Dog()
{
	std::cout << "Goodbye " << name << "\n";
}

int main() {
	Dog myDog;
	myDog.setName("Barkley");
	myDog.setWeight(10);
	myDog.print();
	return 0;
}

// inheritance
// this class inherits everything public and protected from the Dog class 
// as well as private but may not directly access private members/methods
// without a public or protected method for doing so
class OwnedDog : public Dog {
public:
	void setOwner(const std::string& dogsOwner);

	// override the behavior of the print function for all OwnedDogs
	// see polymorphism for a more general introduction to subtype polymorphism
	// the override keyword is optional but makes sure you are actually overriding the
	// method in a base class
	void print() const override;

private:
	std::string owner;
};

// in the corresponding .cpp file
void OwnedDog::setOwner(const std::string& dogsOwner)
{
	owner = dogsOwner;
}

void OwnedDog::print() const
{
	Dog::print(); // call the print function in the base Dog class
	std::cout << "Dog is owned by " << owner << "\n";
}

// ------------------------------------------------------

//////////////////////////////////////////
// Initialization and Operator Overloading
//////////////////////////////////////////

// to be continued - https://learnxinyminutes.com/docs/c++/