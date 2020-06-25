#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>

int			error(int err_code)
{
	// en cas d'erreur: formattage: "program_name: filename: erreur"
	printf("ft_script: error: %d\n", err_code);
	return (err_code);
}

int		init_pty(int fdm)
{
	int			fds;
	char		slavename[128];

	if (ioctl(fdm, TIOCPTYGRANT) || ioctl(fdm, TIOCPTYUNLK))
		return (-1);
	if (ioctl(fdm, TIOCPTYGNAME, slavename))
		return (-1);
	fds = open(slavename, O_RDWR);
	return (fds);
}

int		main(int argc, char **argv, char **envp)
{
	int		fdm;
	int		fds;
	int		n;
	char	*buffer;

	if ((fdm = open("/dev/ptmx", O_RDWR)) < 0)
		return (1);
	grantpt(fdm);
	unlockpt(fdm);
	buffer = ptsname(fdm);
	fds = open(buffer, O_RDWR);
	int tmpfd = open("typescript", O_CREAT | O_RDWR | O_TRUNC);
	// if ((fds = init_pty(fdm) < 0))
		// return (1);
	if ((n = fork()) > 0)
	{
		// master
		close(fds);
		while (1)
		{
			read(fdm, buffer, 1);
			write(1, buffer, 1);
			write(tmpfd, buffer, 1);
		}
	}
	else if (n == 0)
	{
		// slave
		close(fdm);
		dup2(fds, 1);
		dup2(fds, 2);
		execve("/bin/bash", argv, envp);
	}
	else
		return (error(404));
}
