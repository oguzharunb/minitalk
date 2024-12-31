/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:44:50 by obastug           #+#    #+#             */
/*   Updated: 2024/12/31 14:44:50 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int	ft_atoi(const char *nptr);
int	ft_strlen(const char *str);

void	msg_retrieved(int sig)
{
	if (sig == SIGUSR1)
	{
		write(STDOUT_FILENO, "message retrieved", 17);
		exit(0);
	}
}

void	send_int_to_pid(__pid_t pid, int number)
{
	size_t	i;

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
		while (i < 8)
		{
			if ((*str >> i) & 1)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			i++;
			usleep(700);
		}
		if (!*str)
			break ;
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
