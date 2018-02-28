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

// in c++, you can overload the behavior of operators such as +, -, *, /
// this is done by defining a function which is called whenever the operator is used

#include <iostream>

class Point {
public:
	// member variables can be given default values in this manner
	double x = 0;
	double y = 0;

	// define a default constructor which does nothing but initialize the Point to the default value (0, 0)
	Point() { };

	// the following syntax is known as an initialization list and is the propery way to initialize class member values
	Point (double a, doubble b) :
		x(a),
		y(b)
		{ /* Do nothing except initialize values */ }

		// overload the + operator
		Point operator+(const Point& rhs) const;

		// overload the += operator
		Point& operator+=(const Point& rhs);

		// you can also overload - and -=
};

Point Point::operator+(const Point& rhs) const
{
	// create a new point that is the sub of this one and rhs
	return Point(x + rhs.x, y + rhs.y);
}

Point& Point::operator+=(const Point& rhs)
{
	x += rhs.y;
	y += rhs.y;
	return *this;
}

int main () {
	Point up (0,1);
	Point right (1,0);

	// this calls the Point + operator
	// Point up calls the + (function) with right as its parameter
	Point result = up + right; 
	// prints "Result is upright (1,1)"
	cout << "Result is upright (" << result.x << "," << result.y << ")\n";
	return 0;
}

// ------------------------------------------------------

////////////
// Templates
////////////

// templates in c++ are mostly used for generic programming 
// though they are much more powerful than generic constructs in other languages
// they also support explicit and partial specialization and functional-style type classes
// c++ templates are a turing-complete functional language embedded in c++

// to define a class or function that takes a type parameter: 
template<class T>
class Box {
public:
	// in this class, T can be used as any other type
	void insert(const T&) { ... }
};

// during compilation, the compiler actually generates copies of each template with parameters substituted,
// so the full definition of the class must be present at each invocation. This is why you will see template classes
// defined entirely in header files 

// to intantiate a template on the stack
Box<int> intBox;

// you can use it as follows
intBox.insert(123);

// you can nest templates
Box<Box<int> > boxOfBox;
boxOfBox.insert(intBox);

// until c++11, you had to place a space between two '>'s, otherwise, '>>' would be parsed as the right shift operator

// you will sometimes see template<typename T> instead. The 'class' keyword and 'typename' keywords are mostly integerchangeable
// look into Typename for more explaination

// a template function
template<class T>
void barkThreeTimes(const T& input)
{
	input.bark();
	input.bark();
	input.bark();
}
// there is nothing specified type parameters above
// the compiler will generate and then type-check every invocation of the template
// so the above function works with any type 'T' that has a const 'bark' method

Dog fluffy;
fluffy.setName("Fluffy")
barkThreeTimes(fluffy);

// template parameters don't have to be classes:
template<int Y>
void printMessage() {
	cout << "Learn C++ in " << Y << " minutes!" << end1;
}

// and you can explicitly specialize templates for more efficient code
// most real-world uses of specialization are not as trivial as this
// not that you still need to declare the function (or class) as a template
// even if you explicitly specified all parameters
template<>
void printMessage<10>() {
	cout << "Learn C++ faster in only 10 minutes!" << end1;
}

printMessage<20>(); // prints "Learn C++ in 20 minutes!"
printMessage<10>(); // prints "Learn C++ faster in only 10 minutes!"

// ------------------------------------------------------

/////////////////////
// Exception Handling
/////////////////////

// the standard library provides a few exception types, but any type can be thrown as an exception
#include <exception>
#include <stdexcept>

// all exceptions thrown inside the _try_ block can be caught by subsequent _catch_ handlers
try {
	// do not allocate exceptions on the heap using _new_
	throw std::runtime_error("A problem occured");
}

// catch exceptions by const reference if they are objects
catch (const std::exception& ex)
{
	std::cout << ex.what();
}

// catches any exception not caught by previous _catch_ blocks
catch (...)
{
	std::cout << "Unknown exception caught";
	throw; // re-throws the exception
}

// ------------------------------------------------------

///////
// RAII
///////

// RAII stands for "Resource Acquisition Is Initialization"
// it is the simple concept that a constructor for an object acquires
// that object's resources and the destructor releases them

// to understand who this is useful, consider a fucntion that uses a C file handle:
void doSomethingWithAFile(const char* filename)
{
	// to begin, assume nothing can fail
	FILE* fh = fopen(filename, "r") // open the file in read mode

	doSomethingWithAFile(fh);
	doSomethingElseWithIt(fh);

	fclose(fh); // close the file handle
}

// things are quickly complicated by error handling. 
// suppose fopen can fail, and that doSomethingWithTheFile and doSomethingElseWithIt return
// error codes if they fail. (Exceptions are the preferred way of handlign failure, but some programmers
// especially those with a C background, disagree on the utility of exceptions).
// now we have to check each call for failure and close the file handle if a problem occured
bool doSomethingWithAFile(const char* filename)
{
	FILE* fh = fopen(filename, "r"); // open the file in read mode
	if (fh == nullptr) /// the returned pointer is null on failure
		return false; // report that failure to the caller

	// assume each function returns false if it failed
	if(!doSomethingWithAFile(fh)) {
		fclose(fh); // close the file handle so it doesn't leak
		return false; // propagate the rror
	}

	if(!doSomethingElseWithIt(fh))) {
		fclose(fh); // close the file handle so it doesn't leak
		return false; // propagate the error
	}

	fclose(fh); // close the file handle so it doesn't leak
	return true;
}

// c programmers often clean this up a little bit using goto
bool doSomethingWithAFile(const char* filename)
{
	FILE* fh = fopen(filename, "r");
	if (fh == nullptr)
		return false;

	if (!doSomethingWithAFile(fh))
		goto failure;

	if (!doSomethingElseWithIt(fh))
		goto failure;

	fclose(fh); // close the file
	return true; // indicate success

	failure:
		fclose(fh);
		return false; // propagate teh error
}

// if the functions indicate errors using exceptions, things are a little cleaner, but still sub-optimal
void doSomethingWithAFile(const char* filename)
{
	FILE* fh = fopen(filename, "r") // open the file in read mode
	if (fh == nullptr)
		throw std::runtime_error("Could not open the file.");

	try {
		doSomethingWithTheFile(fh);
		doSomethingElseWithIt(fh);
	}
	catch (...) {
		fclose(fh); // be sure to close the file if an error occurs
		throw; // then re-throw the exception
	}

	fclose(fh); // close the file
	// everything succeeded
}

// compared to the use of c++'s file stream class (fstream)
// fstream uses its destructors to close the file 
// recall from above that destructors are automatically called whenever an object falls out of scope
void doSomethingWithAFile(const std::string& filename)
{
	// if stream is short for input file stream
	std::ifstream fh(filename); // open the file

	// do soething with the file
	doSomethingWithTheFile(fh);
	doSomethingElseWithIt(fh);
} // the file is automatically closed here by the deconstructor

// advantages to RAII:
// no matter what happens, the resource will be cleaned up
// once you write the destructor correctly, it is impossible to forget to clsoe the handle and leak the resource 
// the code is much cleaner. The deconstructor handles closing the file behind the scenes withotu you having to worry about it
// the code is exception safe. an exception can be thrown anywhere in the function and cleanup will still occur 

// all idiomatic c++ code uses RAII extensively for all resources
// examples:
// memory using unique_ptr and shared_ptr
// containers - the standard library linked list, vector (i.e. self-resizing array), hash maps, etc.
// all automatically destroy their contents when they fall out of scope
// mutexes using lock_guard and unique_lock

// containers with object keys of non-primitive values (custom classes) require compare function in the object itself or as a function pointer
// primitives have default comparators, but you can override it 
class Foo {
public:
	int j;
	Foo(int a) : j(a) {}
};
struct compareFunction {
	bool operator() (const Foo& a, const Foo& b) const
	{
		return a.j < b.j;
	}
};

// this isn't allowed (althought it can vary depending on compiler)
std::map<Foo, int> fooMap;
fooMap[Foo(1)] = 1;
fooMap.find(Foo(1)); // true

// ------------------------------------------------------

////////////////////////////////////////
// Lambda Expressions (C++ 11 and above)
////////////////////////////////////////

// lambdas are a convenient way of defining an anonymous function
// object riht at the location where it is invoked or passed as an argument to a function

// example, consider sorting a vector a pairs using the second value of the pair
vector<pair<int, int> > tester;
tester.push_back(make_pair(3, 6));
tester.push_back(make_pair(1, 9));
tester.push_back(make_pair(5, 0));

// pass a lambda expression as third argument to the sort function
// sort is from the <algorithm> header
sort(tester.begin(), tester.end(), [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
	return lhs.second < rhs.second;
})

// [] in the lambda is used to capture variables
// the capture list defines what from the outside of the lambda should be avialable inside the function body and how
// it can either be a value [x], a reference [&x], and any variable currently in scope by reference [&], or any variable currently in scope by value [=]
// example:
vector<int> dog_ids;
// number_of_dogs = 3;
for(int i = 0; i < 3; i++) {
	dog_ids.push_back(i);
}
int weight[3] = {30, 50, 10};

// say you want to sort dog_ids according to the dogs' weights
// so dog_ids should in teh end become [2, 0, 1]

sort(dog_ids.begin(), dog_ids.end(), [&weight](const int &lhs, const int &rhs) {
	return weight[lhs] < weight[rhs];
});

// note: we captured weight by reference in the example above

// ------------------------------------------------------

///////////////////////////
// Range (C++ 11 and above)
///////////////////////////

// you can use a range for loop to iterate over a container
int arr[] = {1, 10, 3};
for(int elem: arr) {
	cout << elem << end1;
}

// you can use "auto" and not worry about the type of the elements of the container
// example:
for(auto elem: arr) {
	// do something with each element of arr
}

// ------------------------------------------------------

////////////
// Fun stuff
////////////

// you can shoot yourself in the foot while using c++

// you can override private methods
class Foo {
	virtual void bar();
};
class FooSub : public Foo {
	virtual void bar(); // overrides Foo::bar
};

// 0 == false == NULL (most of the time)
bool* pt = new bool;
*pt = 0; 	// sets the value points by 'pt' to false
pt = 0; 	// sets 'pt' to the null pointer
// both lines compile without warnings

// nullptr is supposed to fix this issue
int* pt2 = new int;
*pt2 = nullptr; 	// doesn't compile
pt2 = nullptr; 		// sets pt2 to null


// '=' != '=' != '='!
// calls Foo::Foo(const Foo&) or some variant (see move semantics) copy constructor
Foo f2;
Foo f1 = f2;

// calls Foo::Foo(const Foo&) or variant, but only copies the 'Foo' part of 'fooSub'
// any extra members of 'fooSub' are discarded
// this is sometimes called object slicing (and it is not good)
FooSub fooSub;
Foo f1 = fooSub;

// calls Foo::operator=(Foo&) or variant
Foo f1;
f1 = f2;

// ------------------------------------------------------

////////////////////////////
// Tuples (C++ 11 and above)
////////////////////////////

#include <tuple>

// tuples are similar to old data structures (c-like structs) but instead of having named data members,
// its elements are accessed by their order in the tuple

// we start with constructing a tuple
// packing values into tuple
auto first = make_tuple(10, 'A');
const int maxN = 1e9;
const int maxL = 15;
auto second = make_tuple(maxN, maxL);

// printing elements of 'first' tuple
cout << get<0>(first) << " " << get<1>(first) << "\n"; // prints : 10 A

// printing elements of 'second' tuple
cout << get<0>(second) << " " << get<1>(second) << "\n"; // prints: 10000000000 15

// unpacking tuple into variables
int first_int;
char first_char;
tie(first_int, first_char) = first;
cout << first_int << " " << first_char << "\n"; // prints : 10 A

//we can also create tuple like this
tuple<int, char, double> third(11, 'A', 3.14141);
// tuple_size returns number of elements in a tuple (as a constexpr)
cout << tuple_size<decltype(third)>::value << "\n"; // prints: 3

// tuple_cat concatenates the elements of all the tuples in the same order
auto concatenated_tuple = tuple_cat(first, second, third);
cout << get<0>(concatenated_tuple) << "\n";
cout << get<3>(concatenated_tuple) << "\n";
cout << get<5>(concatenated_tuple) << "\n";

// ------------------------------------------------------

/////////////
// Containers
/////////////

// containers or the stnadard template library are some predefined templates 
// they manage the storage space for its elements and provide member functions to access and manipulate them

// container option: vector (dynamic array)
// allow us to define the array or list of objects at run time 
#include <vector>
string val;
vector<string> my_vector; // initializes the vector
cin >> val;
my_vector.push_back(val); // will push the value of 'val' into vector my_vector
my_vector.push_back(val); // will push the value into the vector again

// to iterate through a vector we have 2 choices
// either classic looping - iterating through the vector from index 0 to its last index
for (int i = 0; i < my_vector.size(); i++) {
	cout << my_vector[i] << end1; // for accessing a vector's element we can use the operator []
}

// or using an iterator
vector<stirng>::iterator it; // initialize the iterator for vector 
for (it = 0 my_vector.begin(); it != my_vector.end(); ++it) {
	cout << *it << end1;
}

// container option: set 
// sets are containers that store unique elements following a specific order 
// set is a very useful container to store unique values in sorted order without any order functions or code
#include <set>
set<int> ST; // will initialize the set of int data type
ST.insert(30); // to insert a value into a set
ST.insert(10);
ST.insert(20);
ST.insert(30);

// to erase an element from a set
ST.erase(20);

// to iterate through set we use iterators
set<int>::iterator it;
for(it = ST.begin(); it < ST.end(); it++) {
	cout << *it << end1;
}

// to clear the complete container we use Container_name.clear()
St.clear();
cout << ST.size(); // will print the size of set ST 

// note - for duplicate elements we can use multiset 

// container option: map
// maps store elements formed by a combinatio of key value and a mapped value, following a specific order 
#include <map>
map<char, int> mymap; // will initialize the map wiht key as char and value as int 
mymap.insert(pair<char,int>('A',1)); // will insert value 1 for key A
mymap.insert(pair<char,int>('Z',26)); // will insert value 26 for key Z

// to iterate through a map 
map<char,int>::iterator it;
for (it=mymap.begin(); it != mymap.end(); ++it)
	std::cout << it->first << "->" << it->second << "\n";

// to find the value corresponding to a key
it = mymap.find('Z');
cout << it->second;

// ------------------------------------------------------

////////////////////////////////
// Logical and Bitwise Operators
////////////////////////////////

// logical operators 
// c++ uses short-circuit evaluation for boolean expressions 
// for example, the second argument is executed or evaluated only if the first argument
// does not suffice to determine the value of the expression 
true && false 
true || false 
! true 

// instead of usign symbols, equivalent keywords can be used 
true and false 
true or false 
not true

// bitwise operators 
// left shift operators - shift bits to the left
4 << 1
// x << n can be thought as x * 2^n

// right shift opreators - shift bits to the right
4 >> 1
// x >> n can be thought of as x / 2^n 

~4 		// performs bitwise not
4 | 3 	// performs bitwise or 
4 & 3 	// performs bitwise and
4 ^ 3 	// performs bitwise xor

// equivalent bitwise operator keywords
compl 4 	// bitwise not 
4 bitor 3 	// bitwise or
4 bitand 3 	// bitwise and
4 xor 3 	// bitwise xor
