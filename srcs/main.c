#include "ft_script.h"
#include "libft.h"
#include "debug.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

// Goal: set settings in a struct from command line arguments
int		init_pty(int fdm)
{
	int			fds;
	char		slavename[128];
	struct stat	sbuf;

	if (ioctl(fdm, TIOCPTYGRANT) || ioctl(fdm, TIOCPTYUNLK))
		return (-1);
	if (ioctl(fdm, TIOCPTYGNAME, slavename) || stat(slavename, &sbuf))
		return (-1);
	fds = open(slavename, O_RDWR);
	return (fds);
}

void	print_params(t_params cfg)
{
	printf("cfg.append: %d\n", cfg.append);
	printf("cfg.disable_delay: %d\n", cfg.disable_delay);
	printf("cfg.playback: %d\n", cfg.playback);
	printf("cfg.quiet: %d\n", cfg.quiet);
	printf("cfg.record: %d\n", cfg.record);
	printf("cfg.flush_file: %d\n", cfg.flush_file);
	printf("cfg.filename: %s, len: %zu\n", cfg.filename.str, cfg.filename.len);
	printf("cfg.cmd: %d\n", cfg.cmd);
}

void	set_str_param(t_params *cfg, int argc, char **argv, int i)
{
	cfg->flush_file = 1;
	if (argv[cfg->cmd][++i] != 0)
		cfg->filename = (t_str){argv[cfg->cmd] + i,
			ft_strlen(argv[cfg->cmd] + i)};
	else if (cfg->cmd + 1 < argc)
	{
		cfg->cmd++;
		cfg->filename = (t_str){argv[cfg->cmd], ft_strlen(argv[cfg->cmd])};
	}
	else
		cfg->flush_file = 0;
}

int		set_param(int argc, char **argv, t_params *cfg)
{
	int		i;

	i = 0;
	while (argv[cfg->cmd][++i] != 0)
	{
		if (argv[cfg->cmd][i] == 'a')
			cfg->append = 1;
		else if (argv[cfg->cmd][i] == 'd')
			cfg->disable_delay = 1;
		else if (argv[cfg->cmd][i] == 'p')
			cfg->playback = 1;
		else if (argv[cfg->cmd][i] == 'q')
			cfg->quiet = 1;
		else if (argv[cfg->cmd][i] == 'r')
			cfg->record = 1;
		else if (argv[cfg->cmd][i] == 'F')
			set_str_param(cfg, argc, argv, i);
		else
			return (error(2));
	}
	return (0);
}

int		parse_args(int argc, char **argv, t_params *cfg)
{
	int		n;

	while (++cfg->cmd < argc)
	{
		if (argv[cfg->cmd][0] == '-' && argv[cfg->cmd][1])
		{
			if ((n = set_param(argc, argv, cfg)))
				return (n);
		}
		else
			argc = --cfg->cmd;
	}
	return (0);
}

int			main(int argc, char **argv) //, char **envp)
{
	t_params	cfg;
	int			fdm, fds;

	ft_bzero(&cfg, sizeof(cfg));
	cfg.filename.str = "typescript";
	cfg.filename.len = 10;
	if ((n = parse_args(argc, argv, &cfg)))
		return (n);
	if (!cfg.flush_file && cfg.cmd < argc)
		cfg.filename = (t_str){argv[cfg.cmd], ft_strlen(argv[cfg.cmd++])};
	// print_params(cfg);
	cfg.fd = open(cfg.filename.str, O_WRONLY | O_CREAT |
			(cfg.append ? O_APPEND : O_TRUNC), 0644);
	if (cfg.fd == -1)
		error(1);
	if (!cfg.quiet)
		print_header(cfg, argc - cfg.cmd, argv + cfg.cmd);
	// transférer input et output vers le fichier
	if ((fdm = open("/dev/ptmx", O_RDWR)) < 0)
		return (1);
	if ((fds = init_pty(fdm) < 0))
		return (1);
	if (!cfg.quiet)
		print_footer(cfg);
}
