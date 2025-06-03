/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:39:54 by ggasset-          #+#    #+#             */
/*   Updated: 2025/03/24 15:28:04 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	in(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*create_output(char const *s1, size_t strt_trim, size_t out_len)
{
	char	*output;

	output = malloc(out_len + 1);
	if (!output)
		return (0);
	ft_memcpy(output, (char *)s1 + strt_trim, out_len);
	output[out_len] = 0;
	return (output);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	out_len;
	size_t	start_trim_len;
	size_t	end_trim_len;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s1);
	if (!set[0])
		return (ft_strdup(s1));
	if (!s_len)
		return (ft_strdup(""));
	start_trim_len = 0;
	while (s1[start_trim_len] && in(s1[start_trim_len], set))
		start_trim_len++;
	i = s_len;
	while (i > 0 && in(s1[i - 1], set))
		i--;
	end_trim_len = (s_len - i);
	if (start_trim_len == s_len)
		return (ft_strdup(""));
	out_len = s_len - start_trim_len - end_trim_len;
	return (create_output(s1, start_trim_len, out_len));
}
