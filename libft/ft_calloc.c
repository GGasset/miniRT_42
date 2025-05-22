/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:53:34 by ggasset-          #+#    #+#             */
/*   Updated: 2024/10/02 17:59:49 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	char	*output;
	size_t	i;

	if ((nmeb * size < nmeb || nmeb * size < size) && size && nmeb)
		return (0);
	output = malloc(nmeb * size);
	i = 0;
	while (i < nmeb * size && output)
	{
		output[i] = 0;
		i++;
	}
	return (output);
}
