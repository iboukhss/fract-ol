/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:59:31 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/14 16:34:43 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_sign(const char **pos)
{
	const char	*ch;

	ch = *pos;
	if (*ch == '+' || *ch == '-')
	{
		*pos = ch + 1;
	}
	if (*ch == '-')
	{
		return (-1);
	}
	return (1);
}

double	ft_atof(const char *str)
{
	double	result;
	double	decimal;
	int		sign;

	result = 0.0;
	decimal = 1.0;
	sign = parse_sign(&str);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			decimal /= 10;
			result = result + (*str - '0') * decimal;
			str++;
		}
	}
	return (result * sign);
}

/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		double flo = ft_atof(argv[1]);
		printf("flo: %f\n", flo);
		return (0);
	}
	return (1);
}
*/
