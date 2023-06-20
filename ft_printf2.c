#include <unistd.h>
#include <stdarg.h>

int put_str(char *str)
{
	int i = 0;
	if(!str)
		str = "(null)";
	while(str[i])
	{
		write(1,&str[i],1);
		i++;	
	}
	return i;
}

int  put_nbr(long long int number, int base)
{
	char *hex = "0123456789abcdef";
	int len = 0;
	if(number < 0)
	{
		number *= -1;
		len += write(1,"-",1);
	}
	if(number >= base)
	{
		put_nbr((number / base),base);
	}
	len += write(1,&hex[number % base],1);
	return len;
}

int ft_printf(const char *str, ...)
{
	int len = 0;
	int i = 0;
	va_list ptr;
	va_start(ptr,str);

	while(str[i])
	{
		if((str[i] == '%') && (str[i + 1] == 's') || (str[i + 1] == 'd') || (str[i + 1] == 'x'))
		{
			i++;
			if(str[i] == 'd')
				len += put_nbr((long long int)va_arg(ptr,int),10);
			else if(str[i] == 's')
				len += put_str(va_arg(ptr,char *));
			else if(str[i] == 'x')
				len += put_nbr((long long int)va_arg(ptr, unsigned int),16);
		}
		else
			len += write(1,&str[i],1);
		i++;
	}
	va_end(ptr);
	return(len);
}
int main()
{
	ft_printf("%s -> %d","sayicik",123123);
}
