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

#include "../Headers/RT_headers/camera.h"
#include "../Headers/RT_headers/vec3.h"
#include "../Headers/dynamic_array.h"
#include "../libft/libft.h"
#include <stdio.h>

int	get_index(char *id)
{
	if (!ft_strcmp(id, "A"))
		return (0);
	if (!ft_strcmp(id, "C"))
		return (1);
	if (!ft_strcmp(id, "L"))
		return (2);
	if (!ft_strcmp(id, "sp"))
		return (3);
	if (!ft_strcmp(id, "cy"))
		return (4);
	if (!ft_strcmp(id, "pl"))
		return (5);
	return (-1);
}

const char	*get_type_info(char *type)
{
	static const char	*type_info[] = {"rf:0-1,vi:0-255",
			"vf:i-i,vf:-1-1,ri:0-180", "vf:i-i,rf:0-1,vi:0-255",
			"vf:i-i,rf:0-1,vi:0-255", "vf:i-i,vf:-1-1,vi:0-255",
			"vf:i-i,vf:-1-1,rf:i,rf:i,vi:0-255"};

	return (type_info[get_index(type)]);
}

char	**get_info_struct(char *type)
{
	const char	*info;
	char		**info_struct;

	info = get_type_info(type);
	info_struct = ft_split(info, ',');
	return (info_struct);
}

int	get_next_field(char **info_struct, char *field)
{
	static int	i = 0;

	if (info_struct[i] == NULL)
	{
		i = 0;
		ft_bzero(field, 8);
		return (0);
	}
	else
	{
		ft_strlcpy(field, info_struct[i], ft_strlen(info_struct[i]));
		i++;
		return (1);
	}
}

// union scalar_type
// {
// 	size_t;
// 	t_data;
// };

t_data	get_scalar(char **info_struct, char *value)
{
	char	field[9];

	get_next_field(info_struct, field);
	return (ft_atod(value));
}

t_vec3	get_vector(char **info_struct, char *dim)
{
	char	**dims;
	char	field[9];
	t_vec3	vec;

	get_next_field(info_struct, field);
	dims = ft_split(dim, ',');
	if (dims)
		vec = vec3(ft_atod(dims[0]), ft_atod(dims[1]), ft_atod(dims[2]));
	ft_free((void **)dims, 1);
	return (vec);
}

void	fill_ambient_ligth(t_light *ambient, char **argv)
{
	char	**info_struct;

	info_struct = get_info_struct("A");
	asign_vec3(&ambient->coords, 0.0, 0.0, 0.0); // Por poner algo
	ambient->brightness = get_scalar(info_struct, *argv++);
	copy_vec3(&ambient->color, get_vector(info_struct, *argv++));
	ft_free((void **)info_struct, 1);
}

void	fill_ligth(t_light *light, char **argv)
{
	char	**info_struct;

	info_struct = get_info_struct("L");
	light->coords = get_vector(info_struct, *argv++); // Por poner algo
	light->brightness = get_scalar(info_struct, *argv++);
	copy_vec3(&light->color, get_vector(info_struct, *argv++));
	ft_free((void **)info_struct, 1);
}

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
		if (new == 2)
		{
			if (!ft_isspace(line[i]))
			{
				new = 1;
				i--;
			}
		}
		else if (!ft_isspace(line[i]) && line[i])
		{
			new = 1;
			if (line[i] == ',')
				new = 2;
			append_darray(&line_field, &line[i]);
		}
		else if (new == 1)
		{
			new = 0;
			next_field = dstr(line_field);
			append_darray(&format_line, &next_field);
			line_field = alloc_darray(3, sizeof(char));
		}
	}
	free_darray(line_field, 1);
	return (dpstr(format_line));
}

void	print_t_scene(t_scene s);

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
	return (1);
}

int	main(void)
{
	t_scene	s;
	char	lineL[] = "L -50.2,  45.3,5.8   	0.6 34,67,197  ";
	char	lineA[] = "A 0.2 255,255,255";
	fill_dispatcher(&s, lineA);
	fill_dispatcher(&s, lineL);
	print_t_scene(s);
}

/*
	Helper: para pintar la estructura t_scene y ver si va bien.
*/
void	print_t_scene(t_scene s)
{
	//Printeo de light //
	printf("coords: ");
	print_vec3(s.light.coords);
	printf("brightness: %lf\n", s.light.brightness);
	printf("color: ");
	print_vec3(s.light.color);

	printf("\n------------------------------------\n");
	//Print//
	printf("coords: ");
	print_vec3(s.ambient_light.coords);
	printf("brightness: %lf\n", s.ambient_light.brightness);
	printf("color: ");
	print_vec3(s.ambient_light.color);
}