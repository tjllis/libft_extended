#include "ft_printf.h"

int	ft_printchar(int c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (1);
}

int	ft_printstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*s != '\0')
	{
		//if (write(1, s, 1) < 0)
		//	return (-1);
		//i += 1;
		i += write(1, s, 1);
		++s;
	}
	return (i);
}

int	ft_printnum(int c)
{
	char	*s;
	int		i;

	i = 0;
	s = ft_itoa(c);
	if (!s)
	{
		ft_printstr("(null)");
		return (6);
	}
	i = ft_printstr(s);
	free(s);
	return (i);
}

int	ft_printpercent(void)
{
	if (write (1, "%", 1) < 0)
		return (-1);
	return (1);
}