#include <unistd.h>
#include <stdarg.h>

void	put_string(char *str, int *length)
{
	int i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
		*length += write(1, &str[i++], 1);

}

void	put_digit(long long int number, int base, int *length)
{
	char	*hex = "0123456789abcdef";

	if (number < 0)
	{
		number *= -1;
		*length += write(1, "-", 1);
	}
	if (number >= base)
		put_digit((number / base), base, length);
	*length += write(1, &hex[number % base], 1);
}

int	ft_printf(const char *str, ...)
{
	int length = 0;
	int i = 0;
	va_list	pointer;
	va_start(pointer, str);

	while (str[i])
	{
		if ((str[i] == '%') && (str[i + 1] == 's') || (str[i + 1] == 'd') || (str[i + 1] == 'x'))
		{
			i++;
			if (str[i] == 's')
				put_string(va_arg(pointer, char *), &length);
			else if (str[i] == 'd')
				put_digit((long long int)va_arg(pointer, int), 10, &length);
			else if (str[i] == 'x')
				put_digit((long long int)va_arg(pointer, unsigned int), 16, &length);

		}
		else
			length += write(1, &str[i], 1);
		i++;
	}
	return (va_end(pointer), length);
}

