#include "params.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

// Goal: set settings in a struct from command line arguments
int		error(int err_code)
{
	printf("Error: %d\n", err_code);
	return (err_code);
}
// "Rules": There are 2 types of parameters: Bools, strings
int		check_param(char c)
{
	static char *valid = "adpqrF";

	if (ft_strchr(valid, c))
		return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_params	params;
	int			arg_num;
	int			i;

	arg_num = 0;
	// read each argument
	while (++arg_num < argc)
	{
		i = 0;
		// if the argument starts with only one '-'
		if (argv[arg_num][0] == '-')
		{
			while (i != -1 && argv[arg_num][++i] != 0)
			{
				// interpret each coming character as a parameter to be set
				if (check_param(argv[arg_num][i]))
				{
					if (argv[arg_num][i] == 'F' && (i = -1) != 42)
						printf("F parameter : %s\n", argv[++arg_num]);
					else
						printf("parameter %c set\n", argv[arg_num][i]);
				}
				else
					// if character not a parameter => throw an error
					return (error(2));
			}
		}
	}
	// if bool: set parameter and read next character
	// Multiple bool parameters can be set within a single argument
	// if str: value of parameter is "x bonjour"
	// anything else is invalid and will throw an error
}
