/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:18:06 by ggasset-          #+#    #+#             */
/*   Updated: 2025/04/03 12:22:10 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

static size_t	count_values(char const *s1, char value)
{
	size_t	output;
	size_t	i;

	output = 0;
	i = 0;
	while (s1[i])
	{
		output += s1[i] == value;
		i++;
	}
	return (output);
}

static char	in(char value, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == value)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static void	skip_trimmed_indexes(char const *s1, char const *set, size_t *j)
{
	while (in(s1[*j], set))
	{
		j[0]++;
	}
}

char	*ft_strfilter(char const *s1, char const *set)
{
	char	*output;
	size_t	new_len;
	size_t	i;
	size_t	j;

	i = 0;
	new_len = ft_strlen(s1);
	while (set[i])
	{
		if (ft_strchr(set, set[i]) == set + i)
			new_len -= count_values(s1, set[i]);
		i++;
	}
	output = calloc(new_len + 1, 1);
	i = 0;
	j = 0;
	while (i < new_len && output)
	{
		skip_trimmed_indexes(s1, set, &j);
		output[i] = s1[j];
		i++;
		j++;
	}
	return (output);
}
