/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:07:48 by agruet            #+#    #+#             */
/*   Updated: 2025/02/06 11:31:20 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

int	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return (write(1, "(null)", 6));
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int nb)
{
	unsigned int	n;
	static int		count;

	count = 0;
	n = nb;
	if (nb < 0)
	{
		write(1, "-", 1);
		n = -nb;
	}
	if (n > 10)
		ft_putnbr(n / 10);
	n = n % 10 + '0';
	write(1, &n, 1);
	count++;
	if (nb < 0)
		count++;
	return (count);
}

int	ft_putnbr_base(unsigned int n, char *base)
{
	static int	count;

	count = 0;
	if (n > 16)
		ft_putnbr_base(n / 16, base);
	n = base[n % 16];
	write(1, &n, 1);
	count++;
	return (count);
}

int	get_conversion(char c, va_list ap)
{
	if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	if (c == 'd')
		return (ft_putnbr(va_arg(ap, int)));
	if (c == 'x')
		return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef"));
	return (0);
}

int	ft_printf(char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	if (!format)
		return (-1);
	va_start(ap, format);
	count = 0;
	while (*format)
	{
		i = 0;
		if (*format == '%')
		{
			count += get_conversion(*(format + 1), ap);
			i += 2;
		}
		else
		{
			while (format[i] && format[i] != '%')
				i++;
			write(1, format, i);
			count += i;
		}
		format += i;
	}
	va_end(ap);
	return (count);
}

/* #include <stdio.h>

int	main(void)
{
	char	*str = NULL;
	printf("%d\n", printf("salut: %d %d %x %x %s %d %s\n", 42, 2147483647, 42, -1, "salut", -2147483648, str));
	ft_printf("%d\n", ft_printf("salut: %d %d %x %x %s %d %s\n", 42, 2147483647, 42, -1, "salut", -2147483648, str));
} */
