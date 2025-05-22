/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:07:19 by ggasset-          #+#    #+#             */
/*   Updated: 2024/09/27 17:16:22 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*s_tmp;
	size_t		i;

	c = (char)c;
	s_tmp = s;
	i = 0;
	while (i < n)
	{
		if (s_tmp[i] == c)
			return ((void *)s_tmp + i);
		i++;
	}
	return (0);
}
