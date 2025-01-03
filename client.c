/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:29:06 by obastug           #+#    #+#             */
/*   Updated: 2024/12/31 15:11:22 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int	ft_atoi(const char *nptr);
int	ft_strlen(const char *str);

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
}

int	main(int argc, char const *argv[])
{
	int	pid;

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
	return (0);
}
