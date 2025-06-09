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
#include "../Headers/minilibx_funcs.h"
#include "../libft/libft.h"
#include <stdio.h>

// int	get_index(char *id)
// {
// 	if (!ft_strcmp(id, "A"))
// 		return (0);
// 	if (!ft_strcmp(id, "C"))
// 		return (1);
// 	if (!ft_strcmp(id, "L"))
// 		return (2);
// 	if (!ft_strcmp(id, "sp"))
// 		return (3);
// 	if (!ft_strcmp(id, "cy"))
// 		return (4);
// 	if (!ft_strcmp(id, "pl"))
// 		return (5);
// 	return (-1);
// }

// const char	*get_type_info(char *type)
// {
// 	static const char	*type_info[] = {"rf:0-1,vi:0-255",
// 			"vf:i-i,vf:-1-1,ri:0-180", "vf:i-i,rf:0-1,vi:0-255",
// 			"vf:i-i,rf:0-1,vi:0-255", "vf:i-i,vf:-1-1,vi:0-255",
// 			"vf:i-i,vf:-1-1,rf:i,rf:i,vi:0-255"};

// 	return (type_info[get_index(type)]);
// }

// char	**get_info_struct(char *type)
// {
// 	const char	*info;
// 	char		**info_struct;

// 	info = get_type_info(type);
// 	info_struct = ft_split(info, ',');
// 	return (info_struct);
// }

// int	get_next_field(char **info_struct, char *field)
// {
// 	static int	i = 0;

// 	if (info_struct[i] == NULL)
// 	{
// 		i = 0;
// 		ft_bzero(field, 8);
// 		return (0);
// 	}
// 	else
// 	{
// 		ft_strlcpy(field, info_struct[i], ft_strlen(info_struct[i]));
// 		i++;
// 		return (1);
// 	}
// }

t_data	get_scalar(char *value)
{
	char	field[9];

	// get_next_field(info_struct, field);
	return (ft_atod(value));
}


unsigned int	ft_atoui(const char *str);

size_t	get_scalar_size_t(char *value)
{
	char	field[9];

	// get_next_field(info_struct, field);
	return (ft_atoui(value));
}

t_vec3	get_vector(char *dim)
{
	char	**dims;
	char	field[9];
	t_vec3	vec;

	// get_next_field(info_struct, field);
	dims = ft_split(dim, ',');
	if (dims)
		vec = vec3(ft_atod(dims[0]), ft_atod(dims[1]), ft_atod(dims[2]));
	ft_free((void **)dims, 1);
	return (vec);
}

void	fill_ambient_ligth(t_light *ambient, char **argv)
{
	// char	**info_struct;
	// info_struct = get_info_struct("A");
	asign_vec3(&ambient->coords, 0.0, 0.0, 0.0); // Por poner algo
	ambient->brightness = get_scalar(*argv++);
	copy_vec3(&ambient->color, get_vector(*argv++));
	// ft_free((void **)info_struct, 1);
}

void	fill_ligth(t_light *light, char **argv)
{
	// char	**info_struct;
	// info_struct = get_info_struct("L");
	light->coords = get_vector(*argv++); // Por poner algo
	light->brightness = get_scalar(*argv++);
	copy_vec3(&light->color, get_vector(*argv++));
	// ft_free((void **)info_struct, 1);
}

/*
	∗ identifier: C
	∗ x, y, z coordinates of the viewpoint: -50.0,0,20
	∗ 3D normalized orientation vector, in the range [-1,1] for each x, y,
		z axis:
	0.0,0.0,1.0
	∗ FOV: Horizontal field of view in degrees in the range [0,18
*/
void	fill_camera(t_camera *cam, char **argv)
{
	cam->camera_pos = get_vector(*argv++);
	cam->rotation = get_vector(*argv++);
	cam->fov = get_scalar_size_t(*argv++);
	cam->aspect_ratio = ASPECT_RATIO;
	cam->width = WINDOW_WIDTH;
	cam->max_bounces = MAX_BOUNCES;
}

void	fill_obj(t_object *obj, char **argv)
{
	t_data		*sizes;

	sizes = ft_calloc(2, sizeof(t_data));
	obj->sizes = sizes;

	if (!ft_strcmp(*argv, "sp"))
		obj->kind = Sphere;
	else if (!ft_strcmp(*argv, "pl"))
		obj->kind = Plane;
	else if (!ft_strcmp(*argv, "cy"))
		obj->kind = Cylinder;
	argv++;
	obj->coords = get_vector(*argv++);
	if (obj->kind == Sphere)
		asign_vec3(&obj->rotation, 0, 0, 0);
	else
		obj->rotation = get_vector(*argv++);
	if (obj->kind != Plane)
	{
		obj->sizes[0] = get_scalar(*argv++);
		if (obj->kind == Cylinder)
			obj->sizes[1] = get_scalar(*argv++);
	}
	obj->color = get_vector(*argv++);
}

void	fill_obj_list(t_object_list *objs, char **argv)
{
	t_object	obj;
	size_t		obj_to_alloc;

	obj_to_alloc = ((objs->len == 0) * 2 + (objs->len != 0) * (objs->len + 1)) * sizeof(t_object);
	objs->objs = ft_realloc(objs->objs, objs->len * sizeof(t_object), obj_to_alloc, 0);
	fill_obj(&objs->objs[objs->len], argv);
	objs->len++;
}

void			print_t_scene(t_scene s);
char			**format_line(char *line);

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

int	main(void)
{
	t_scene	s;
	char	lineL[] = "L -50.2,  45.3,5.8   	0.6 34,67,197  ";
	char	lineA[] = "A 0.2 255,255,255";
	char	lineC[] = "C   -50.0,0,20   0,0,1 70";
	char	line_pl[] = "pl   0.0,0.0,  -10.0  0.0,1.0,0.0   0,0,225";
	char	line_cy[] = "cy   50.0,0.0,20.6   0.0,0.0,1.0   14.2   21.42   10,0,255";

	fill_dispatcher(&s, lineA);
	fill_dispatcher(&s, lineL);
	fill_dispatcher(&s, lineC);
	ft_bzero((char *) &s.objects, sizeof(t_object_list));
	fill_dispatcher(&s, line_pl);
	fill_dispatcher(&s, line_cy);
	print_t_scene(s);
}

/*
	Helper: para pintar la estructura t_scene y ver si va bien.
*/
void	print_t_scene(t_scene s)
{
	// Printeo de light //
	printf("coords: ");
	print_vec3(s.light.coords);
	printf("brightness: %lf\n", s.light.brightness);
	printf("color: ");
	print_vec3(s.light.color);
	printf("\n------------------------------------\n");
	// Printeo de ambien//
	printf("coords: ");
	print_vec3(s.ambient_light.coords);
	printf("brightness: %lf\n", s.ambient_light.brightness);
	printf("color: ");
	print_vec3(s.ambient_light.color);
	printf("\n------------------------------------\n");
	// Printeo de Cámara
	printf("width: %zu\n", s.camera.width);
	printf("aspect_ratio: %lf\n", s.camera.aspect_ratio);
	printf("fov: %zu\n", s.camera.fov);
	printf("max_bounces: %zu\n", s.camera.max_bounces);
	printf("camera_pos: ");
	print_vec3(s.camera.camera_pos);
	printf("rotation: ");
	print_vec3(s.camera.rotation);
	printf("\n------------------------------------\n");

	//Printeo de objeto
	char	obj_names [3][40] = {"Sphere", "Cylinder", "Plane"};
	for (int i = 0; i < s.objects.len; i++)
	{
		printf("[%s]:\n", obj_names[s.objects.objs[i].kind]);
		printf("coords: ");
		print_vec3(s.objects.objs[i].coords);
		printf("rotation: ");
		print_vec3(s.objects.objs[i].rotation);
		printf("color: ");
		print_vec3(s.objects.objs[i].color);
		printf("sizes: %lf  %lf\n", s.objects.objs[i].sizes[0], s.objects.objs[i].sizes[1]);
		printf("\n------------------------------------\n");
	}
	// print_vec3(&s.objects);
}

/*
	fomat_line: función para extraer como array de strings
	los componentes de una línea del archivo .rt
*/
char	**format_line(char *line)
{
	t_darray *line_field;
	t_darray *format_line;
	char *next_field;
	size_t i;
	int new;

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

unsigned int	ft_atoui(const char *str)
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
