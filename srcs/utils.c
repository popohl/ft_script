#include "debug.h"
#include "ft_script.h"
#include "libft.h"
#include <sys/time.h>
#include <unistd.h>

int			error(int err_code)
{
	// en cas d'erreur: formattage: "program_name: filename: erreur"
	printf("ft_script: error: %d\n", err_code);
	return (err_code);
}

t_str		get_time()
{
	struct timeval	tp;
	char			*time_of_day;

	if (gettimeofday(&tp, NULL))
		return ((t_str){0, 0});
	time_of_day = ctime(&tp.tv_sec);
	return ((t_str){time_of_day, ft_strlen(time_of_day)});
}

void		print_header(t_params params, int argc, char **argv)
{
	t_str		time;
	int			n;

	// écrire le header
	write(1, "Script started, output file is ", 31);
	write(1, params.filename.str, params.filename.len);
	write(1, "\n", 1);
	// Le header dans le fichier est au format: "Script started on Wed Jun 24 18:13:39 2020"
	time = get_time();
	write(params.fd, "Script started on ", 18);
	write(params.fd, time.str, time.len);
	if (params.cmd)
	{
		write(params.fd, "command:", 8);
		n = 0;
		while (n < argc)
		{
			write(params.fd, " ", 1);
			write(params.fd, argv[n], ft_strlen(argv[n]));
			n++;
		}
	}
	write(params.fd, "\n", 1);
}

void		print_footer(t_params params)
{
	t_str		time;

	write(1, "Script done, output file is ", 28);
	write(1, params.filename.str, params.filename.len);
	write(1, "\n", 1);
	time = get_time();
	write(params.fd, "\nScript done on ", 16);
	write(params.fd, time.str, time.len);
	write(params.fd, "\n", 1);
}
