/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:31:51 by ggasset-          #+#    #+#             */
/*   Updated: 2025/04/03 18:33:46 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min(size_t a, size_t b)
{
	return (a * (a <= b) + b * (b < a));
}

void	*ft_realloc(void *old, size_t old_len, size_t new_len, int free_old)
{
	char	*out;
	size_t	i;

	out = ft_calloc(new_len, 1);
	i = 0;
	while (old && out && i < min(old_len, new_len))
	{
		out[i] = ((char *)old)[i];
		i++;
	}
	if (free_old)
		free(old);
	return (out);
}
