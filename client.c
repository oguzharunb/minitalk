#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
void	msg_retrieved()
{
	write(STDOUT_FILENO, "message retrieved", 17);
	exit(0);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	register int	i;
	register long	ret;
	char			sign;

	ret = 0;
	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\n' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ret = (ret * 10) + (nptr[i] - '0');
		i++;
	}
	return ((int)ret * sign);
}

void	send_int_to_pid(__pid_t pid, int number)
{
	size_t	i;
	
	printf("number %d sending to pid: %d\n", number, pid);
	i = 0;
	while (i < 32)
	{
		if ((number >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(700);
	}
}

void	send_string_to_pid(int server_pid, const char *str)
{
	size_t	i;

	while (1)
	{
		i = 0;
		printf("char %c sending to process %d\n", *str, server_pid);
		while (i < 8)
		{
			if ((*str >> i) & 1)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			printf("%ld", i);
			i++;
			usleep(700);
		}
		if (!*str)
			break;
		str++;
	}
	send_int_to_pid(server_pid, getpid());
}

int	main(int argc, char const *argv[])
{
	int	pid;

	signal(SIGUSR1, msg_retrieved);
	if (argc != 3)
	{
		write(STDOUT_FILENO, "using: client <server_pid> <text>\n", 34);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	if (!pid)
	{
		write(STDOUT_FILENO, "invalid pid\n", 12);
		return (1);
	}
	send_string_to_pid(pid, argv[2]);
	pause();
	return (0);
}
