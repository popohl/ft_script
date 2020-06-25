#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

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
	struct stat	sbuf;

	if (ioctl(fdm, TIOCPTYGRANT) || ioctl(fdm, TIOCPTYUNLK))
		return (-1);
	if (ioctl(fdm, TIOCPTYGNAME, slavename) || stat(slavename, &sbuf))
		return (-1);
	fds = open(slavename, O_RDWR);
	return (fds);
}

int		main(void)
{
	int		fdm;
	int		fds;
	int		n;
	char	buffer[150];

	if ((fdm = open("/dev/ptmx", O_RDWR)) < 0)
		return (1);
	if ((fds = init_pty(fdm) < 0))
		return (1);
	if ((n = fork()))
	{
		close(fdm);
	}
	else if (n != -1)
	{
		close(fds);
	}
	else
		return (error(123));
}
