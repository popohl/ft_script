#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

int		init_pty(int fdm)
{
	int			fds;
	char		slavename[128];
	struct stat	sbuf;

	if (ioctl(fdm, TIOCPTYGRANT) || ioctl(fdm, TIOCPTYUNLK))
		return (-1);
	if (ioctl(fdm, TIOCPTYGNAME, slavename) || stat(slavename, &sbuf))
		return (-1);
	printf("slavename: %s\n", slavename);
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
	char	*args[2] = {"/bin/zsh", NULL};
}
