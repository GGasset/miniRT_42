/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-02 11:09:23 by ggasset-          #+#    #+#             */
/*   Updated: 2025-09-02 11:09:23 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minilibx_funcs.h"

static int	is_valid_nbr_char(char c)
{
	return ((ft_isalnum(c) && !ft_isalpha(c)) || c == '.' || c == '-');
}

int	expect_vec3(char *line, size_t *i, t_interval range)
{
	if (!expect_number(line, i, range, 0))
		return ((printf("Number error\n"), 0));
	if (line[*i] != ',' || !is_valid_nbr_char(line[*i - 1]))
		return ((printf("Error\nExpected comma\n"), 0));
	(*i)++;
	if (!expect_number(line, i, range, 0))
		return ((printf("Number error\n"), 0));
	if (line[*i] != ',' || !is_valid_nbr_char(line[*i - 1]))
		return ((printf("Error\nExpected comma\n"), 0));
	(*i)++;
	if (!expect_number(line, i, range, 1))
		return ((printf("Number error\n"), 0));
	return (1);
}

int	check_nbr_err(int err, t_data nbr, t_interval range)
{
	if (err)
	{
		printf("%.2lf: Number parsing err\n", nbr);
		return (0);
	}
	if (nbr > range.max + EPSILON || nbr < range.min - EPSILON)
	{
		printf("%.2lf: Number out of range'\n", nbr);
		return (0);
	}
	return (1);
}

int	expect_number(char *line, size_t *i, t_interval range, int expect_space)
{
	int		dot_count;
	t_data	number;
	int		nbr_err;

	if (!line || !i)
		return (0);
	dot_count = 0;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (!line[*i])
		return (printf("Error\nMissing expected number\n"), 0);
	number = ft_atod_s(line + *i, &nbr_err);
	if (!check_nbr_err(nbr_err, number, range))
		return (0);
	while (line[*i] && is_valid_nbr_char(line[*i]))
	{
		dot_count += line[*i] == '.';
		(*i)++;
	}
	if (expect_space && !ft_isspace(line[*i]) && line[*i] != '\n' && line[*i])
		return (printf("Error\nExpected space after number\n"), 0);
	while (line[*i] && (ft_isspace(line[*i]) && line[*i]))
		(*i)++;
	write(1, "Error\nToo many dots in number\n", 30 * (dot_count >= 2));
	return (dot_count < 2);
}
