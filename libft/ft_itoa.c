/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:57:02 by ggasset-          #+#    #+#             */
/*   Updated: 2025/01/29 15:10:57 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	number_length(int n)
{
	size_t	output;

	output = 0;
	while (n)
	{
		n /= 10;
		output++;
	}
	return (output);
}

char	*ft_itoa(int n)
{
	char	*output;
	size_t	n_len;
	int		tmp;
	size_t	i;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (!n)
		return (ft_strdup("0"));
	n_len = number_length(n);
	output = malloc(n_len + (n < 0) + 1);
	if (output)
		output[n_len + (n < 0)] = 0;
	i = 0;
	while (n && output)
	{
		output[0] = output[0] * (n >= 0) + '-' * (n < 0);
		tmp = n / 10 * 10;
		tmp = ft_abs(n - tmp);
		output[n_len - i - 1 + (n < 0)] = '0' + tmp;
		n /= 10;
		i++;
	}
	return (output);
}
