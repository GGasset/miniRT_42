/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: germangasset <germangasset@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:28:26 by ggasset-          #+#    #+#             */
/*   Updated: 2024/11/20 16:09:15 by germangasse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	size_t	l1;
	size_t	l2;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	output = malloc(l1 + l2 + 1);
	i = 0;
	while (i < l1 && output)
	{
		output[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < l2 && output)
	{
		output[l1 + i] = s2[i];
		i++;
	}
	if (output)
		output[l1 + l2] = 0;
	return (output);
}
