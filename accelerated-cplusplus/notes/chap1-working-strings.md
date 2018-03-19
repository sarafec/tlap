###  Accelerated C++ - Chapter 1 - Working with Strings

```
// asks for a person's name, and generates a greeting
#incldue <iostream>
#include <string>

int main() 
{	
	std::string name; // define name
	std::cin >> name; // read into name

	std::cout << "Hello, " << name << "!" << std:: endl;
	return 0;
}
```
  
* A variable is an object that has a name. An object, in turn, is a part of the computer's memory that has a type. The distinction between objects and variables is important. 
* `std::string name` defines a variable with the type of string, as defined by the standard library. 
  
* The input-output library saves its output in an internal data structure called a buffer, which it uses to optimize output oepration. Most systems take a significant amoutn of time to write characters to an output device, regardless of how many characters there are to write. 
* To avoid the overhead of writing to responses to each output request, the library uses the buffer to accumulate the characters to be written, and flushes the buffer, by writing its contents to the output device, only when necessary. By doing so, it can combine several output operations into a single write.
* There are three events that cause teh system to flush the buffer. First, the buffer might be full, in which case the library will flush it automatically. Second, the library might be asked to read from the standard input stream. In that case, the lirbary immeduately flushes the output buffer without waiting for the buffer to become full. The third occasion for flushing the buffer is when we explicitly say to do so.
* Flushing output buffers at opportune moments is an important habit when you are writing programs that might take a long time to run. Otherwise, some of the program's output might languish in the system's buffers for a long time between when your porgram writes it and when you see it.


```
// asks for person's name, and generates a framed greeding
#include <iostream>
#include <string>

int main() 
{
	std::cout << "Please enter your first name: ";
	std:string name;
	std::cin >> name;

	const std::string greeting = "Hello, " + name + "!";
	const std::string spaces (greeting.size(), ' ');
	const std::string second = "* " + spaces + " *";
	const std::string first(second.size(), '*');

	std::cout << std::endl;
	std::cout << first << std::endl;
	std::cout << second << std::endl;
	std::cout << "* " << greeting << " *" << std::endl;
	std::cout << second << std::endl;
	std::cout << first << std::endl;
	return 0;
}
```

* A character literals are distinct from string literals - character literals are always enclosed in single quotes, whereas a string literal is always enclosed in double quotes. 
* A character literal represents a single character. The characters that have special meaning inside a string literal have the same special meaning in a character literals.
  
* The string type is defined in the standard header <string>. An object of type string contains a sequence of zero or more characters. If `n` is an integer, `c` is a char, `is` is an input string, and `os` is an output stream, then the string operations include - 
- `std::string t = s;` -  defines `t` as a variable of type `std::string` that initially contains a copy of the characters in `s`, where `s` can either be a `string` or a string literal.
- `std::string z(n, c);` - defines `z` as a variable fo type `std::string` that initially contains `n` copies of the character `c`. Here, `c` must be a char, not a `string` or string literal.
- `os << s` - writes the characters contained in s, without any formatting changes, on the output stream denoted by `os`. The result of the expression is `os.
- `is >> s` - reads and discards characters from teh stream denoted by `is` until encountaring a character that is not whitespace. Then reads successive characters from `is` into `s`, overwriting whatever value `s` might ahve had, until the next character read would be whitespace. The result is `is`.
- `s + t` - the result of this expression is an std::string that contains a copy of the characters in `s` followed by a copy of the characters in `t`. Either `s` or `t`, but not both, may be a string literal or a value of type `char`.
- `s.size()` - the number of characters is s. 
  
* Variables can be defined in one of three ways - `std::string hello = "hello";` or `std::string stars(100, '*');` or `std::string name;`.
* Variables defined inside a pairof curly braces are local variables, which exist only while executing the part of the proram within the braces. When teh implementation reaches the }, it destroys the variables, and returns any memory that they occupied to the system.
* Defining a variable as `const` promises that the variable's value will not change during its lifetime. Such a variable must be initialzied as part of its deifnition, because there is no way to do so later.
  
* Excuting `std::cin >> v` discards any whitespace characters in tehs tandard input stream, then reads from teh standard input into variable v. It returns std::cin, which has type `istream`, in order to allow chained input operators. 
