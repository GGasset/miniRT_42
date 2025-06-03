/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:05:22 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/20 13:05:50 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_index_replace(char *s, size_t start, size_t replace_len, char *new)
{
	size_t	new_len;
	size_t	s_new_len;
	char	*out;

	if (!s)
		return (0);
	new_len = ft_strlen(new);
	s_new_len = ft_strlen(s);
	if (start + replace_len > s_new_len)
		replace_len = s_new_len - start;
	s_new_len = s_new_len - replace_len + new_len;
	out = malloc(s_new_len + 1);
	if (!out)
		return (0);
	out[s_new_len] = 0;
	ft_memcpy(out, s, start);
	ft_memcpy(out + start, new, new_len);
	ft_memcpy(out + start + new_len, s + start + replace_len,
		ft_strlen(s + start + replace_len));
	free(s);
	return (out);
}
