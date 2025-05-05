/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:50:53 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/05 09:50:55 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int	ft_putstr(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_count_num(long long int num, int base)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	if (num < 0 && base == 10)
	{
		count++;
		num *= -1;
	}
	while (num)
	{
		num /= base;
		count++;
	}
	return (count);
}

int	ft_number(long long int num, int base)
{
	int		len;
	int		i;
	char	*hex;
	char	str[40];

	hex = "0123456789abcdef";
	len = ft_count_num(num, base);
	str[len] = '\0';
	i = len;
	if (num == 0)
	{
		write (1, "0", 1);
		return (1);
	}
	if (num < 0 && base == 10)
	{
		num *= -1;
		str[0] = '-';
	}
	while (num)
	{
		str[--len] = hex[num % base];
		num /= base;
	}
	write (1, str, i);
	return (i);
}

int	ft_handler(const char *format, va_list args)
{
	int	count;

	count = 0;
	if (*format == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (*format == 'd')
		count += ft_number(va_arg(args, int), 10);
	else if (*format == 'x')
		count += ft_number((long long int)va_arg(args, unsigned int), 16);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	va_start(args, format);
	count = 0;

	if (!format)
		return (0);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			count += ft_handler(format, args);
		}
		else
		{
			count++;
			write(1, format, 1);
		}
		format++;

	}
	va_end(args);
	return (count);
}
