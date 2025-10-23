/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:33:25 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/23 11:57:22 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/RT_headers/camera.h"
#include "../../Headers/RT_headers/vec3.h"
#include "../../Headers/dynamic_array.h"
#include "../../libft/libft.h"
#include <stdio.h>

int	is_empty(char *fline)
{
	int	i;

	i = 0;
	while (fline[i])
	{
		if (!ft_isspace(fline[i]))
			return (0);
		i++;
	}
	return (1);
}

int	fill_dispatcher(t_scene *s, char *line)
{
	char	**formatted_line;

	if (is_empty(line))
		return (1);
	formatted_line = format_line(line);
	if (!formatted_line)
		return (0);
	if (!ft_strcmp(formatted_line[0], "A"))
		fill_ambient_ligth(&s->ambient_light, formatted_line + 1);
	else if (!ft_strcmp(formatted_line[0], "L"))
		fill_ligth(&s->light, formatted_line + 1);
	else if (!ft_strcmp(formatted_line[0], "C"))
		fill_camera(&s->camera, formatted_line + 1);
	else if (formatted_line[0][0] != '#')
		fill_obj_list(&s->objects, formatted_line);
	ft_free_splitted(formatted_line);
	return (1);
}
