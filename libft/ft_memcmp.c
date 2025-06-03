/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:14:19 by ggasset-          #+#    #+#             */
/*   Updated: 2024/09/26 14:02:47 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*tmp_s1;
	const unsigned char	*tmp_s2;
	size_t				i;

	tmp_s1 = s1;
	tmp_s2 = s2;
	if (!n)
		return (0);
	i = 0;
	while (i < n - 1 && tmp_s1[i] == tmp_s2[i])
	{
		i++;
	}
	return (tmp_s1[i] - tmp_s2[i]);
}
