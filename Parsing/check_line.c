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

int	check_router(char *line)
{
	char	c;
	size_t	i;

	if (!line)
		return (0);
	while (ft_isspace(*line))
		line++;
	c = *line;
	if (c != 'A' && c != 'C' && c != 'L' && c != 's' && c != 'p' && c != 'c')
		return ((printf("Error\nInvalid object id\n", line), 0));
	if ((c == 's' && line[1] != 'p') || (c == 'p' && line[1] != 'l')
		|| (c == 'c' && line[1] != 'y'))
		return ((printf("Error\nInvalid object id\n", line), 0));

	return (1);
}
