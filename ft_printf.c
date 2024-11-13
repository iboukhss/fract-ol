/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:21:50 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/13 16:16:26 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PRIBUF_SIZE 4096

#include "libft.h"

#include <stdarg.h>
#include <unistd.h>

// NOTE: All loops are upper-bounded, making this code eco-friendly.

static void	write_char(char *buf, int *buf_len, int c)
{
	if (*buf_len < PRIBUF_SIZE)
	{
		buf[*buf_len] = c;
		(*buf_len)++;
	}
}

static void	write_str(char *buf, int *buf_len, const char *str)
{
	while (*str && *buf_len < PRIBUF_SIZE)
	{
		write_char(buf, buf_len, *str);
		str++;
	}
}

// NOTE: Careful with negative integer overflow.
static void	write_int(char *buf, int *buf_len, int n)
{
	char	tmp[20];
	char	*end;

	if (n == 0)
	{
		write_char(buf, buf_len, '0');
		return ;
	}
	if (n < 0)
	{
		write_char(buf, buf_len, '-');
	}
	else
	{
		n = -n;
	}
	end = tmp + 20;
	*--end = '\0';
	while (n != 0)
	{
		*--end = -(n % 10) + '0';
		n /= 10;
	}
	write_str(buf, buf_len, end);
}

static void	handle_modifier(char *buf, int *buf_len, int mod, va_list ap)
{
	if (mod == '%')
	{
		write_char(buf, buf_len, '%');
	}
	else if (mod == 'c')
	{
		write_char(buf, buf_len, va_arg(ap, int));
	}
	else if (mod == 's')
	{
		write_str(buf, buf_len, va_arg(ap, char *));
	}
	else if (mod == 'd')
	{
		write_int(buf, buf_len, va_arg(ap, int));
	}
}

// NOTE: Using `int` instead of `ptrdiff_t` makes sense here because the buffer
// size is well within `int` range for any platform.
int	ft_printf(const char *format, ...)
{
	char	buf[PRIBUF_SIZE];
	int		buf_len;
	va_list	ap;

	va_start(ap, format);
	buf_len = 0;
	while (*format && buf_len < PRIBUF_SIZE)
	{
		if (*format == '%')
		{
			format++;
			handle_modifier(buf, &buf_len, *format, ap);
		}
		else
		{
			write_char(buf, &buf_len, *format);
		}
		format++;
	}
	va_end(ap);
	return (write(1, buf, buf_len));
}

/*
#include <limits.h>
#include <stdio.h>

int	main(void)
{
	int ret;

	ret = ft_printf("Hello, world!\n");
	printf("Return value: %d\n", ret);
	ret = printf("Hello, world!\n");
	printf("Return value: %d\n", ret);

	ret = ft_printf("%d\n", INT_MAX);
	printf("Return value: %d\n", ret);
	ret = printf("%d\n", INT_MAX);
	printf("Return value: %d\n", ret);

	ret = ft_printf("%d\n", INT_MIN);
	printf("Return value: %d\n", ret);
	ret = printf("%d\n", INT_MIN);
	printf("Return value: %d\n", ret);

	ret = ft_printf("%d\n", 42);
	printf("Return value: %d\n", ret);
	ret = printf("%d\n", 42);
	printf("Return value: %d\n", ret);

	ret = ft_printf("%d\n", 0);
	printf("Return value: %d\n", ret);
	ret = printf("%d\n", 0);
	printf("Return value: %d\n", ret);
}
*/
