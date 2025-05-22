/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:33:35 by ggasset-          #+#    #+#             */
/*   Updated: 2024/11/18 13:27:43 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	if (*s1 != *s2 || n == 1 || !*s1)
	{
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	}
	return (ft_strncmp(s1 + 1, s2 + 1, n - 1));
}
