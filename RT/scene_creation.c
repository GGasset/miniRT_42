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
	static const char	*type_info[] = {
		"rf:0-1,vi:0-255",
		"vf:i-i,vf:-1-1,ri:0-180",
		"vf:i-i,rf:0-1,vi:0-255",
		"vf:i-i,rf:0-1,vi:0-255",
		"vf:i-i,vf:-1-1,vi:0-255",
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
	ft_free((void **) dims, 1);
	return (vec);
}

void	fill_ambient_ligth(t_light *ambient, char **argv)
{
	char		**info_struct;

	info_struct = get_info_struct("A");
	
	asign_vec3(&ambient->coords, 0.0, 0.0, 0.0); //Por poner algo
	ambient->brightness = get_scalar(info_struct, *argv++);
	copy_vec3(&ambient->color, get_vector(info_struct, *argv++));
	
	ft_free((void **) info_struct, 1);
}

void	fill_ligth(t_light *light, char **argv)
{
	char		**info_struct;

	info_struct = get_info_struct("L");
	
	light->coords =  get_vector(info_struct, *argv++); //Por poner algo
	light->brightness = get_scalar(info_struct, *argv++);
	copy_vec3(&light->color, get_vector(info_struct, *argv++));
	
	ft_free((void **) info_struct, 1);
}

int	main(int argc, char **argv)
{
	// t_light	ambient;
	t_light	light;
	//Aqui iria la logica para determinar que tipo es.
	argv += 2;
	// fill_ambient_ligth(&ambient, argv);
	// printf("coords: ");
	// print_vec3(&ambient.coords);
	// printf("brightness: %lf\n", ambient.brightness);
	// printf("color: ");
	// print_vec3(&ambient.color);

	fill_ligth(&light, argv);
	printf("coords: ");
	print_vec3(light.coords);
	printf("brightness: %lf\n", light.brightness);
	printf("color: ");
	print_vec3(light.color);
}

// void	merge_in_formatted()
// {

// }


// int	main(void)
// {
// 	char	line[] = "L -50.2,45.3,5.8   	0.6 34,67,197  ";
// 	char	**line_formatted = format_line(line);

// 	while (*line_formatted)
// 	{
// 		printf("line_formatted: %s  ", *line_formatted);
// 		line_formatted++;
// 	}
// }
