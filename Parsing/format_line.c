/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:20:38 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/23 13:01:45 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "dynamic_array.h"

int	traversing_field(int *new, t_darray **line_field, char curr, size_t *i)
{
	int		flag;

	flag = 0;
	*new -= (*new == 2 && !ft_isspace(curr)) * 1;
	if (*new == 2 && !ft_isspace(curr))
	{
		*i = *i - 1;
		flag = 1;
	}
	else if (!ft_isspace(curr) && curr)
	{
		*new = 1;
		if (curr == ',')
			*new = 2;
		append_darray(line_field, &curr);
		flag = 1;
	}
	return (flag);
}

/*
	fomat_line: función para extraer como array de strings
	los componentes de una línea del archivo .rt
*/
char	**format_line(char *line)
{
	t_darray	*line_field;
	t_darray	*format_line;
	char		*next_field;
	size_t		i;
	int			new;

	new = 0;
	i = -1;
	line_field = alloc_darray(3, sizeof(char));
	format_line = alloc_darray(24, sizeof(char *));
	while (++i < ft_strlen(line) + 1)
	{
		if (!traversing_field(&new, &line_field, line[i], &i) && new == 1)
		{
			new--;
			append_darray(&line_field, &new);
			next_field = dstr(line_field);
			append_darray(&format_line, &next_field);
			line_field = alloc_darray(3, sizeof(char));
		}
	}
	next_field = NULL;
	append_darray(&format_line, &next_field);
	return (free_darray(line_field, 1), dpstr(format_line));
}
