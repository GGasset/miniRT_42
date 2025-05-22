/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:17:40 by ggasset-          #+#    #+#             */
/*   Updated: 2024/09/26 13:43:57 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	tmp;

	i = 0;
	while (i < n && (src != dest))
	{
		tmp = ((char *)src)[i];
		((char *)dest)[i] = tmp;
		i++;
	}
	return (dest);
}
