#include "params.h"

// Goal: set settings in a struct from command line arguments

// "Rules": There are 3 types of parameters: Bools, strings and ints

int		main(int argc, char *argv)
{
// read each argument
	int i;

	i = 0;
	while (++i < argc)
		 parse_arg(params, argv[i]);
// if the argument starts with only one '-'
//		interpret each coming character except space as a parameter to be set
//			if character not a parameter => throw an error
//		if bool: set parameter and read next character
//			Multiple bool parameters can be set within a single argument
//		if str: value of parameter is in one of 3 formats:
//		-x=bonjour ; -x="bonjour" or -x bonjour,
//		anything else is invalid and will throw an error
//			=> set value of parameter with strdup
//		if int: 3 possible formats: -x=3; -x 3 or -x3,
//		anything else is invalid, including letters
//			=> set value of parameter with atoi
// if the argument starts with two '--'
//		interpret the whole coming word as a parameter,
//		using the same rules as with a single '-'
}
