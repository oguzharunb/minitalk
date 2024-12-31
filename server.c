#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
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
	if (nb < 10) ft_putchar(nb + 48);
}

void	ft_putstr(char *str)
{
    int i;

    while(str[i] != '\0')
    {
        write(1, &str[i], 1);
        i++;
    }
}
void	listener(int sig)
{
	static int	status;
	static int	number;
	static int	counter;

	if (sig == SIGUSR1)
		number = number + (1 << counter);
	counter++;

	if (status == 1)
	{
		if (counter == 32)
		{
			kill(number, SIGUSR1);
			counter = 0;
			number = 0;
			status = 0;
		}
	}
	else if (status == 0)
	{
		if (counter == 8)
		{
			if (number == 0)
				status = 1;
			ft_putchar(number);
			counter = 0;
			number = 0;
		}
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
