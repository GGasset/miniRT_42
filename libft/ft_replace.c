/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:09:20 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/19 17:04:08 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace(char *s, char *old, char *new, int free_s)
{
	size_t	s_len;
	size_t	old_len;
	size_t	new_len;
	size_t	replace_start;

	if (!s || !old || !new)
		return (0);
	s_len = ft_strlen(s);
	old_len = ft_strlen(old);
	new_len = ft_strlen(new);
	replace_start = (size_t)ft_strnstr(s, old, s_len);
	if (replace_start)
		replace_start -= (size_t)s;
	s = ft_strdup_free(s, free_s);
	free_s = 1;
	while (ft_strnstr(s, old, s_len))
	{
		s = ft_strdup_free(s, 1);
		s = ft_index_replace(s, replace_start, old_len, new);
		replace_start = (size_t)ft_strnstr(s + replace_start + new_len, old,
				s_len - replace_start);
		if (replace_start)
			replace_start -= (size_t)s;
	}
	return (s);
}
