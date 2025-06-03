/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:16:23 by ggasset-          #+#    #+#             */
/*   Updated: 2024/09/26 12:51:48 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min(size_t a, size_t b)
{
	return (a * (a <= b) + b * (b < a));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*output;
	size_t	i;

	if (start >= ft_strlen(s) || !len)
		return (ft_strdup(""));
	len = min(ft_strlen(s + start), len);
	output = 0;
	if (len)
		output = malloc(len + 1);
	i = 0;
	while (i < len && s[i] && output)
	{
		output[i] = s[start + i];
		i++;
	}
	if (output)
		output[len] = 0;
	return (output);
}
