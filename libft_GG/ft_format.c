/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaz-pri <apaz-pri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:51:56 by apaz-pri          #+#    #+#             */
/*   Updated: 2025/05/19 17:59:26 by apaz-pri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static int	ft_choose(va_list args, char format, int fd)
{
	if (format == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	return (0);
}

int	ft_printf_fd(int fd, char const *format, ...)
{
	va_list args;
	int formatt;
	int i;
	int counter;

	i = -1;
	counter = 0;
	formatt = 0;
	va_start(args, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			formatt += ft_choose(args, format[i + 1], fd);
			i++;
		}
		else
		{
			ft_putchar_fd(format[i], fd);
			counter++;
		}
	}
	return (counter + formatt);
}