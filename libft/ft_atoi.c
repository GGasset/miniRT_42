/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:58:56 by ggasset-          #+#    #+#             */
/*   Updated: 2024/09/25 16:42:19 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	is_blank(char c)
{
	char	output;

	output = c == ' ';
	output = c == '\t' || output;
	output = c == '\n' || output;
	output = c == '\v' || output;
	output = c == '\f' || output;
	output = c == '\r' || output;
	return (output);
}

static void	skip_blanks(int *i, const char *nptr)
{
	*i = 0;
	while (is_blank(nptr[*i]) && nptr[*i])
	{
		++*i;
	}
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	output;
	int	i;

	output = 0;
	skip_blanks(&i, nptr);
	sign = 1 - 2 * (nptr[i] == '-');
	i += nptr[i] == '-' || nptr[i] == '+';
	while (ft_isdigit(nptr[i]))
	{
		output *= 10;
		output += (nptr[i] - '0') * sign;
		i++;
	}
	return (output);
}
