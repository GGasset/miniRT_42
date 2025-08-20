/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:33:25 by alvmoral          #+#    #+#             */
/*   Updated: 2025/06/03 02:48:08by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/RT_headers/camera.h"
#include "../../Headers/RT_headers/vec3.h"
#include "../../Headers/dynamic_array.h"
#include "../../libft/libft.h"
#include <stdio.h>

int	fill_dispatcher(t_scene *s, char *line)
{
	char	**formatted_line;

	formatted_line = format_line(line);
	if (!formatted_line)
		return (0);
	if (!ft_strcmp(formatted_line[0], "A"))
		fill_ambient_ligth(&s->ambient_light, formatted_line + 1);
	else if (!ft_strcmp(formatted_line[0], "L"))
		fill_ligth(&s->light, formatted_line + 1);
	else if (!ft_strcmp(formatted_line[0], "C"))
		fill_camera(&s->camera, formatted_line + 1);
	else
		fill_obj_list(&s->objects, formatted_line);
	return (1);
}

t_scene	create_scene_from_map(void)
{
	t_scene	s;
	// char	lineL[] = "L -50.2,  45.3,5.8   	0.6 34,67,197  ";
	// char	lineA[] = "A 0.2 255,255,255";
	char	lineC[] = "C  -4.5,5,-7  0,0,1 120";
	char	line_sp[] = "sp 0,0,10  4.0  255,255,255";
	// char	line_pl[] = "pl   0.0,0.0,  -10.0  0.0,1.0,0.0   0,0,225";
	// char	line_cy[] = "cy   50.0,0.0,20.6   0.0,0.0,1.0   14.2   21.42   10,0,255";

	// fill_dispatcher(&s, lineA);
	// fill_dispatcher(&s, lineL);
	fill_dispatcher(&s, lineC);
	ft_bzero((char *) &s.objects, sizeof(t_object_list));
	fill_dispatcher(&s, line_sp);
	// fill_dispatcher(&s, line_pl);
	// fill_dispatcher(&s, line_cy);
	print_t_scene(s);
	return (s);
}
