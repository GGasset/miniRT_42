#include "../../Headers/RT_headers/camera.h"
#include "../../Headers/dynamic_array.h"

/*
	Helper: para pintar la estructura t_scene y ver si va bien.
*/
void	print_t_scene(t_scene s)
{
	// Printeo de light //
	printf("coords: ");
	print_vec3(s.light.coords);
	printf("brightness: %lf\n", s.light.brightness);
	printf("color: %u", s.light.color);
	printf("\n------------------------------------\n");
	// Printeo de ambien//
	printf("coords: ");
	print_vec3(s.ambient_light.coords);
	printf("brightness: %lf\n", s.ambient_light.brightness);
	printf("color: %u", s.ambient_light.color);
	printf("\n------------------------------------\n");
	// Printeo de Cámara
	printf("width: %zu\n", s.camera.width);
	printf("aspect_ratio: %zu\n", s.camera.aspect_ratio);
	printf("fov: %zu\n", s.camera.fov);
	printf("max_bounces: %zu\n", s.camera.max_bounces);
	printf("camera_pos: ");
	print_vec3(s.camera.camera_pos);
	printf("rotation: ");
	print_vec3(s.camera.rotation);
	printf("\n------------------------------------\n");

	//Printeo de objeto
	char	obj_names [3][40] = {"Sphere", "Cylinder", "Plane"};
	for (size_t i = 0; i < s.objects.len; i++)
	{
		printf("[%s]:\n", obj_names[s.objects.objs[i].kind]);
		printf("coords: ");
		print_vec3(s.objects.objs[i].coords);
		printf("rotation: ");
		print_vec3(s.objects.objs[i].rotation);
		printf("color: %u", s.objects.objs[i].color);
		printf("sizes: %lf  %lf\n", s.objects.objs[i].sizes.vs[0], s.objects.objs[i].sizes.vs[1]);
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

t_data	get_scalar(char *value)
{
	// char	field[9];

	// get_next_field(info_struct, field);
	return (ft_atod(value));
}

size_t	get_scalar_size_t(char *value)
{
	// char	field[9];

	// get_next_field(info_struct, field);
	return (ft_atoui(value));
}

t_vec3	get_vector(char *dim)
{
	char	**dims;
	// char	field[9];
	t_vec3	vec;

	// get_next_field(info_struct, field);
	dims = ft_split(dim, ',');
	if (dims)
		vec = vec3(ft_atod(dims[0]), ft_atod(dims[1]), ft_atod(dims[2]));
	ft_free((void **)dims, 1);
	return (vec);
}