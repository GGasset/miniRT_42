/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:43:36 by ggasset-          #+#    #+#             */
/*   Updated: 2024/09/26 15:38:14 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	overlap;

	overlap = src + n > dest && dest > src;
	i = overlap * (n);
	while (i < n && !overlap && src != dest)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	while (i >= 1 && overlap && src != dest)
	{
		((char *)dest)[i - 1] = ((char *)src)[i - 1];
		i--;
	}
	return (dest);
}
