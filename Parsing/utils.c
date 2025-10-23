/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:36:55 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/23 11:59:48 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/RT_headers/camera.h"
#include "../../Headers/dynamic_array.h"

/*
	Helper: para pintar la estructura t_scene y ver si va bien.
*/
// void	print_t_scene(t_scene s)
// {
// 	// Printeo de light //
// 	printf("[Light]:\n");
// 	printf("coords: ");
// 	print_vec3(s.light.coords);
// 	printf("brightness: %lf\n", s.light.brightness);
// 	printf("color: %u", s.light.color);
// 	printf("\n------------------------------------\n");
// 	// Printeo de ambien//
// 	printf("[Ambient Light]:\n");
// 	printf("coords: ");
// 	print_vec3(s.ambient_light.coords);
// 	printf("brightness: %lf\n", s.ambient_light.brightness);
// 	printf("color: %u", s.ambient_light.color);
// 	printf("\n------------------------------------\n");
// 	// Printeo de Cámara
// 	printf("[Camera]:\n");
// 	printf("width: %zu\n", s.camera.width);
// 	printf("aspect_ratio: %lf\n", s.camera.aspect_ratio);
// 	printf("fov: %zu\n", s.camera.fov);
// 	printf("max_bounces: %zu\n", s.camera.max_bounces);
// 	printf("camera_pos: ");
// 	print_vec3(s.camera.camera_pos);
// 	printf("rotation: ");
// 	print_vec3(s.camera.rotation);
// 	printf("\n------------------------------------\n");

// 	//Printeo de objeto
// 	char	obj_names [3][40] = {"Sphere", "Cylinder", "Plane"};
// 	for (size_t i = 0; i < s.objects.len; i++)
// 	{
// 		printf("[%s]:\n", obj_names[s.objects.objs[i].kind]);
// 		printf("coords: ");
// 		print_vec3(s.objects.objs[i].coords);
// 		printf("rotation: ");
// 		print_vec3(s.objects.objs[i].rotation);
// 		printf("color: %u", s.objects.objs[i].color);
// 		printf("sizes: %lf  %lf\n", s.objects.objs[i].sizes.vs[0], 
		// s.objects.objs[i].sizes.vs[1]);
// 		printf("\n------------------------------------\n");
// 	}
// 	// print_vec3(&s.objects);
// }

size_t	ft_atoui(const char *str)
{
	unsigned int	value;

	value = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		value = (*str - '0') + value * 10;
		str++;
	}
	return (value);
}

t_data	get_scalar(char *value)
{
	return (ft_atod(value));
}

size_t	get_scalar_size_t(char *value)
{
	return (ft_atoui(value));
}

t_vec3	get_vector(char *dim)
{
	char	**dims;
	t_vec3	vec;

	ft_bzero(&vec, sizeof(vec));
	dims = ft_split(dim, ',');
	if (dims)
		vec = vec3(ft_atod(dims[0]), \
					ft_atod(dims[1]), \
					ft_atod(dims[2]));
	ft_free_splitted(dims);
	return (vec);
}
