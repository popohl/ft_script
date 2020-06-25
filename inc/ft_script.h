#ifndef PARSER_H
# define PARSER_H

#include <strings.h>

typedef struct	s_str {
	char	*str;
	size_t	len;
}				t_str;

typedef struct	s_params {
	char	append;
	char	disable_delay;
	char	playback;
	char	quiet;
	char	record;
	char	flush_file;
	t_str	filename;
	int		fd;
	int		cmd;
}				t_params;

int			error(int err_code);
t_str		get_time();
void		print_footer(t_params params);
void		print_header(t_params params, int argc, char **argv);

#endif
