/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:27:06 by ggasset-          #+#    #+#             */
/*   Updated: 2024/11/21 12:34:51 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int main() 
{
	char ** a = ft_split("\0aa\0bbb", '\0');
	printf("%s\n", a[0]);
}*/

static size_t	skip_dups(char const *s1, size_t i)
{
	char	initial_value;

	if (!s1[i])
		return (i);
	initial_value = s1[i];
	i++;
	while (initial_value == s1[i])
	{
		(i)++;
	}
	return (i);
}

static size_t	count_values(char const *s1, char c)
{
	size_t	output;
	size_t	i;

	output = 0;
	i = 0;
	if (s1[0] == c)
		i = skip_dups(s1, 0);
	while (s1[i])
	{
		output += s1[i] == c;
		i = skip_dups(s1, i);
	}
	if (i)
		output -= (s1[i - 1] == c);
	return (output);
}

static char	free_if_error(char *array, char **base_arr)
{
	char	error;
	size_t	i;

	error = !array;
	i = 0;
	while (base_arr[i] && !array)
	{
		free(base_arr[i]);
		i++;
	}
	if (!array)
		free(base_arr);
	return (error);
}

static void	set_s_len(size_t *s_len, size_t s_start, char const *s1)
{
	if (!*s_len)
		*s_len = ft_strlen((char *)s1 + s_start);
	else
		*s_len -= (size_t)((char *)s1 + s_start);
}

char	**ft_split(char const *s1, char c)
{
	char	**out;
	size_t	a_c;
	size_t	s_start;
	size_t	s_len;
	size_t	i;

	if (!s1[0])
		return (ft_calloc(1, sizeof(char *)));
	a_c = count_values(s1 + (skip_dups(s1, 0) - 1) * (s1[0] == c), c) + 1;
	out = ft_calloc(a_c + 1, sizeof(char *));
	s_start = skip_dups(s1, 0) * (s1[0] == c);
	i = 0;
	while (i < a_c && out)
	{
		s_len = (size_t)ft_strchr((char *)s1 + s_start, c);
		set_s_len(&s_len, s_start, s1);
		out[i] = ft_calloc(s_len + 1, 1);
		if (free_if_error(out[i], out))
			return (0);
		ft_memcpy(out[i], (char *)s1 + s_start, s_len);
		s_start = skip_dups(s1, s_start + s_len);
		i++;
	}
	return (out);
}

/*if (!s_len)
	s_len = ft_strlen((char *)s1 + s_start);
else
	s_len -= (size_t)((char *)s1 + s_start);*/

/*char	**ft_split(char const *s1, char c)
{
	char	**output;
	size_t	a_c;
	size_t	split_start;
	size_t	split_len;
	size_t	i;

	a_c = count_values(s1, c) + 1;
	a_c -= ((s1[ft_strlen(s1) - 1] == c) + (s1[0] == c)) * (a_c != 1);
	output = ft_calloc(a_c + 1 * (a_c != 1), sizeof(char *));
	i = 0;
	split_start = skip_dups(s1, 0) * (s1[0] == c);
	while (i < a_c && output)
	{
		split_len = (size_t)ft_strchr((char *)s1 + split_start, c);
		if (!split_len)
			split_len = ft_strlen((char *)s1 + split_start);
		else
			split_len -= (size_t)((char *)s1 + split_start);
		output[i] = ft_calloc(split_len + 1, 1);
		ft_memcpy(output[i], ((char *)s1) + split_start, split_len);
		split_start += split_len;
		split_start = skip_dups(s1, split_start);
		i++;
	}
	return (output);
}*/
