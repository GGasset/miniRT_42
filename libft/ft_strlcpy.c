/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:58:20 by ggasset-          #+#    #+#             */
/*   Updated: 2024/09/24 17:26:38 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 1;
	while (i < size && src[i - 1])
	{
		dst[i - 1] = src[i - 1];
		i++;
	}
	if (size)
		dst[i - 1] = 0;
	return (ft_strlen(src));
}
