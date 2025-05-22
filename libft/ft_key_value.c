/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:33:37 by ggasset-          #+#    #+#             */
/*   Updated: 2024/12/09 14:10:10 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_key_value(char *str, char **key, char **value, int free_str)
{
	size_t	del_pntr;
	size_t	relative_pos;

	free_str = free_str != 0;
	del_pntr = (size_t)ft_strchr(str, '=');
	relative_pos = (size_t)ft_strchr(str, 0);
	if (del_pntr == (size_t)str || del_pntr == relative_pos || !del_pntr)
	{
		free((void *)(((size_t)str) * free_str));
		return (1);
	}
	relative_pos = del_pntr - (size_t)str;
	*key = ft_substr(str, 0, relative_pos);
	*value = ft_substr((char *)del_pntr + 1, 0, -1);
	free((void *)(((size_t)str) * free_str));
	return (0);
}
