/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:29:10 by obastug           #+#    #+#             */
/*   Updated: 2024/12/31 13:37:10 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		nb = nb % 10;
	}
	if (nb < 10)
		ft_putchar(nb + 48);
}

void	ft_putstr(char *str)
{
	int	i;

	while (str[i])
		i++;
	write(STDOUT_FILENO, str, i);
}

void	listener(int sig)
{
	static int	status;
	static int	number;
	static int	counter;

	if (sig == SIGUSR1)
		number = number + (1 << counter);
	counter++;
	if ((status == 1) && (counter == 32))
	{
		kill(number, SIGUSR1);
		counter = 0;
		number = 0;
		status = 0;
	}
	else if ((status == 0) && (counter == 8))
	{
		ft_putchar(number);
		counter = 0;
		if (number == 0)
			status = 1;
		number = 0;
	}
}

int	main(void)
{
	ft_putnbr(getpid());
	signal(SIGUSR1, listener);
	signal(SIGUSR2, listener);
	while (1)
		pause();
	return (0);
}
