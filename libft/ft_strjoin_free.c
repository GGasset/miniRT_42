/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:07:06 by germangasse       #+#    #+#             */
/*   Updated: 2024/11/27 15:33:43 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Perfect to append file contents to a buffer
char	*ft_strjoin_free(char *s1, char *s2, int free1, int free2)
{
	char	*out;

	out = ft_strjoin(s1, s2);
	if (s1 && !s2)
		out = ft_strdup(s1);
	if (!s1 && s2)
		out = ft_strdup(s2);
	if (s1 && free1)
		free(s1);
	if (s2 && free2)
		free(s2);
	return (out);
}
