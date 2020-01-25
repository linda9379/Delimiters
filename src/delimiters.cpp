#include <iostream>
#include <cassert>
#include <cmath>
#include "project_1.hpp"

// Function declarations
int main();
void print_program();
bool does_delimiter_match( char del );
bool do_delimiters_nest();

// Function definitions
int main() {
	print_program();
	std::cout << does_delimiter_match( '(' ) << std::endl;
	std::cout << does_delimiter_match( '[' ) << std::endl;
	std::cout << does_delimiter_match( '{' ) << std::endl;
	std::cout << do_delimiters_nest() << std::endl;

	return 0;
}

void print_program(){
	char c {};
	ece150::start_reading_file();
	while (ece150::at_eof() == false){

		c = ece150::get_next_character();
		std::cout << c;
	}
	std::cout << std::endl;
}

bool does_delimiter_match( char del ){
	// Initialize counter and boolean flag for error message
	int counter {0};
	bool error_message{false};

	ece150::start_reading_file();

	// Check if parameter "del" is an opening delimiter
	if (del == '(' || del == '[' || del == '{'){
		while (ece150::at_eof() == false){
			char c {ece150::get_next_character()};

			if (del == '('){
				// If character from file is an opening delimiter, add one to counter
				// If character from file is a closing delimiter, subtract one to counter
				if (c==del){
					++counter;
				} else if (c == ')'){
					--counter;
					// Check if counter is negative, if yes, then output error message
					// and reset counter to zero and change boolean flag to be true for printing an error message
					if (counter < 0){
						std:: cout << "Unmatched )" << std::endl;
						counter = 0;
						error_message = true;
					}
				}
			}else if (del == '['){
				if (c == del){
					++counter;
				} else if (c == ']'){
					--counter;
					if (counter < 0){
						std:: cout << "Unmatched ]" << std::endl;
						counter = 0;
						error_message = true;
					}
				}
			}else if (del == '{'){
				if (c == del){
					++counter;
			} else if (c == '}'){
					--counter;
					if (counter < 0){
						std:: cout << "Unmatched }" << std::endl;
						counter = 0;
						error_message = true;
					}
				}
			}
		}

		// Check if counter is positive after reading file
		// If yes, then print error message and change boolean flag to be true
		if (del == '(' && counter > 0){
			std::cout << "Missing ";
			for (int i{0}; i < counter; ++i){
				std::cout << ")";
			}
			std::cout << std::endl;
			error_message = true;
		} else if (del == '[' && counter > 0){
			std::cout << "Missing ";
			for (int i{0}; i < counter; ++i){
				std::cout << "]";
			}
			std::cout << std::endl;
			error_message = true;
		} else if (del == '{' && counter > 0){
			std::cout << "Missing ";
			for (int i{0}; i < counter; ++i){
				std::cout << "}";
			}
			std::cout << std::endl;
			error_message = true;
		}

		// Check for value of boolean flag, if an error message was displayed, return false
		// if error message was not displayed then return true
		if (error_message == true){
			return false;
		}else{
			return true;
		}

	// If given parameter was not an opening delimiter then return false.
	}else{
		return false;
	}
}

bool do_delimiters_nest(){
	// Initialize boolean flag for whether the delimiters nest or match
	bool delimiters_nest {true};

	ece150::initialize_table();
	ece150::start_reading_file();

	while (ece150::at_eof() == false){
		char c {ece150::get_next_character()};
		// Initialize the value for the right most character in the table
		char right_delimiter {};

		// Check if table is empty, if not, then assign the right most character in the table to the variable
		if (ece150::is_table_empty() == false){
			right_delimiter = ece150::get_right_most_character();
		}

		// Check if the character in the file is an opening delimiter, if yes, then place it in the table
		if (c == '(' || c == '[' || c == '{'){
			ece150::place_character( c );
		// Check if the character in the file is a closing delimiter
		}else if (c == ')' || c == ']' || c == '}'){
			if (right_delimiter == '('){
				// Check if delimiter matches opening delimiter, if not then print error message and change boolean flag to false
				if (c != ')'){
					std::cout << "Unmatched " << c << std::endl;
					delimiters_nest = false;
				// If opening and closing delimiters match, then remove the opening delimiter from the table
				}else{
					ece150::erase_right_most_character();
				}
			}else if (right_delimiter == '['){
				if (c != ']'){
					std::cout << "Unmatched " << c << std::endl;
					delimiters_nest = false;
				}else{
					ece150::erase_right_most_character();
				}
			}else if (right_delimiter == '{'){
				if (c != '}'){
					std::cout << "Unmatched " << c << std::endl;
					delimiters_nest = false;
				}else{
					ece150::erase_right_most_character();
				}
			// If found a closing delimiter and table is empty, then print error message and change boolean flag to false
			}else if (ece150::is_table_empty() == true){
				std::cout << "Unmatched " << c << std::endl;
				delimiters_nest = false;
			}
		}
	}

	// Check if table is not empty after reading file, if yes, then print error message with the missing closing delimiters and change boolean flag to false
	if ( ece150::is_table_empty() != true){
		delimiters_nest = false;
		std::cout<< "Missing ";
		while (ece150::is_table_empty() != true){
			char missing {ece150::get_right_most_character()};

			if (missing == '('){
				std::cout << ')';
			}else if (missing == '['){
				std::cout << ']';
			}else if (missing == '{'){
				std::cout << '}';
			}
			ece150::erase_right_most_character();
		}
		std::cout << std::endl;
	}

	// Check for boolean flag value, if the delimiters nest and match then return true
	// if delimiters do not nest and match then return false
	if (delimiters_nest == true){
		return true;
	}else{
		return false;
	}

}




