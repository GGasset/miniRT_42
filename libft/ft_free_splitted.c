/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_splitted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:33:57 by ggasset-          #+#    #+#             */
/*   Updated: 2024/11/27 17:39:32 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_splitted(char **split_output)
{
	size_t	i;

	if (!split_output)
		return ;
	i = 0;
	while (split_output[i])
	{
		free(split_output[i]);
		i++;
	}
	free(split_output);
}
