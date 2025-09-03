/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-03 14:44:02 by ggasset-          #+#    #+#             */
/*   Updated: 2025-09-03 14:44:02 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_property(char *line, t_object_counter *counter)
{
	size_t	i;

	i = 1;
	if (!ft_isspace(line[i]))
		return ((printf("Error\nInvalid object id\n"), 0));
	if (*line == 'A')
		if (!expect_number(line, &i, interval(0, 1), 1)
			|| !expect_vec3(line, &i, interval(0, 255)))
			return (0);
	if (*line == 'C' || *line == 'L')
		if (!expect_vec3(line, &i, interval(-1E30, 1E30)))
			return (0);
	if (*line == 'C')
		if (!expect_vec3(line, &i, interval(-1, 1))
				|| !expect_number(line, &i, interval(0, 180), 1))
			return (0);
	if (*line == 'L')
		if (!expect_number(line, &i, interval(0, 1), 1)
			|| !expect_vec3(line, &i, interval(0, 255)))
			return (0);
	if (!counter)
		return (1);
	counter->n_a += *line == 'A';
	counter->n_c += *line == 'C';
	counter->n_l += *line == 'L';
	if (counter->n_a > 1 || counter->n_c > 1 || counter->n_l > 1)
		return ((printf("Error\nMultiple definitions of a property\n"), 0));
	return (1);
}

static int	check_object(char *line)
{
	size_t	i;

	i = 2;
	if (!ft_isspace(line[i]))
		return ((printf("Error\nInvalid object id\n"), 0));
	if (!expect_vec3(line, &i, interval(-1E30, 1E30)))
		return (0);
	if (*line == 's' && !expect_number(line, &i, interval(-1E30, 1E30), 1))
		return (0);
	if (*line == 'p' || *line == 'c')
		if (!expect_vec3(line, &i, interval(-1, 1)))
			return (0);
	if (*line == 'c')
		if (!expect_number(line, &i, interval(-1E30, 1E30), 1)
			|| !expect_number(line, &i, interval(-1E30, 1E30), 1))
				return (0);
	if (!expect_vec3(line, &i, interval(0, 255)))
		return (0);
	return (1);
}

int	check_router(char *line, t_object_counter *counter)
{
	char	c;
	size_t	i;

	if (!line)
		return (0);
	while (ft_isspace(*line))
		line++;
	c = *line;
	if (c != 'A' && c != 'C' && c != 'L' && c != 's' && c != 'p' && c != 'c')
		return ((printf("Error\nInvalid object id\n%s\n", line), 0));
	if ((c == 's' && line[1] != 'p') || (c == 'p' && line[1] != 'l')
		|| (c == 'c' && line[1] != 'y'))
		return ((printf("Error\nInvalid object id\n%s\n", line), 0));
	if (!check_property(line, counter) || !check_object(line))
		return (printf("In line %s\n", line));
	return (1);
}
