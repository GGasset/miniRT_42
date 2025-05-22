/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_split_count.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:36:42 by ggasset-          #+#    #+#             */
/*   Updated: 2025/01/30 14:47:17 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_get_split_count(char **split_out)
{
	size_t	out;

	if (!split_out)
		return (0);
	out = 0;
	while (split_out[out])
		out++;
	return (out);
}
