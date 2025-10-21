/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:08:33 by ggasset-          #+#    #+#             */
/*   Updated: 2024/12/09 17:11:54 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_dup_zeros(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == '0')
		i++;
	return (i);
}

static double	after_dot(char *dot_pos)
{
	double	out;
	int		out_cpy;
	size_t	nbr_l;

	out = 0;
	if (!dot_pos)
		return (0);
	out = ft_atoi(dot_pos + 1);
	out_cpy = (int)out;
	nbr_l = 0;
	while (out_cpy)
	{
		out_cpy /= 10;
		nbr_l++;
	}
	nbr_l += count_dup_zeros(dot_pos + 1);
	while (nbr_l)
	{
		out /= 10;
		nbr_l--;
	}
	*dot_pos = 0;
	return (out);
}

static double	under_dot(double f, char *str)
{
	double	tmp;

	if (ft_strlen(str) == 1 && str[0] == '-')
		return (f * -1);
	tmp = ft_atoi(str);
	if (tmp < 0)
		f *= -1;
	tmp += f;
	return (tmp);
}

static double	inner_atod(char *str, int *error)
{
	size_t	i;
	char	*dot_pos;
	double	out;

	dot_pos = ft_strchr(str, '.');
	if (ft_strchr(dot_pos + ((size_t)dot_pos > 0), '.'))
		return (*error = 1, 0);
	i = 0;
	while (ft_isdigit(str[i]) || str[i] == '.' || (i == 0 && str[i] == '-'))
		i++;
	str = ft_strdup(str);
	dot_pos = ft_strchr(str, '.');
	if (!str)
		return (*error = 1, 0);
	out = after_dot(dot_pos);
	out = under_dot(out, str);
	free(str);
	return (out);
}

double	ft_atod_s(char *str, int *error)
{
	char	*trimmed_str;
	char	tmp[2];
	double	out;

	if (!error)
		return (0);
	*error = 0;
	if (!str)
		return (*error = 1, 0);
	ft_bzero(tmp, 2);
	trimmed_str = 0;
	while (ft_isdigit(*str) || *str == '.' || *str == '-')
	{
		tmp[0] = *str;
		trimmed_str = ft_strjoin_free(trimmed_str, tmp, TRUE, FALSE);
		str++;
	}
	out = inner_atod(trimmed_str, error);
	free(trimmed_str);
	return (out);
}
