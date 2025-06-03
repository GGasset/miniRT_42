/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:27:51 by ggasset-          #+#    #+#             */
/*   Updated: 2024/12/06 17:41:01 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	c = (char)c;
	i = 0;
	if (!s)
		return (0);
	while (s)
	{
		if (c == s[i])
			break ;
		if (s[i] == 0)
			return (0);
		i++;
	}
	return ((char *)s + i);
}
