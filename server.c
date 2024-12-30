#include <signal.h>
#include <unistd.h>
void	bit_handle(int bit)
{
	static	int	i;
	static	int	c;

	c += ((bit & 1) << i);
	i++;
	if (i == 7)
	{
		write(STDOUT_FILENO, &c, 1);
		if (!c)
		{
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}

int main(int argc, char const *argv[])
{
	
	return 0;
}
