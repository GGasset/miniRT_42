/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:56:03 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/19 16:09:35 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_free(char *s, int free_s)
{
	char	*out;

	out = ft_strdup(s);
	if (free_s)
		free(s);
	return (out);
}
