/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:02:28 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/19 20:20:41 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*output;

	if (!s)
		return (0);
	len = ft_strlen(s);
	output = malloc(len + 1);
	i = 0;
	while (i < len && output)
	{
		output[i] = s[i];
		i++;
	}
	if (output)
		output[len] = 0;
	return (output);
}
