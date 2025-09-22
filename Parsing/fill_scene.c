#include "../../Headers/RT_headers/camera.h"
#include "../../Headers/minilibx_funcs.h"

void	fill_ambient_ligth(t_light *ambient, char **argv)
{
	asign_vec3(&ambient->coords, 0.0, 0.0, 0.0); // Por poner algo
	ambient->brightness = get_scalar(*argv++);
	ambient->color = get_color(get_vector(*argv++));
}

void	fill_ligth(t_light *light, char **argv)
{
	light->coords = get_vector(*argv++); // Por poner algo
	light->brightness = get_scalar(*argv++);
	light->color = get_color(get_vector(*argv++));
}

/*
	∗ identifier: C
	∗ x, y, z coordinates of the viewpoint: -50.0,0,20
	∗ 3D normalized orientation vector, in the range [-1,1] for each x, y,
		z axis:
	0.0,0.0,1.0
	∗ FOV: Horizontal field of view in degrees in the range [0,180]
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
	if (!ft_strcmp(*argv, "sp"))
	{
		obj->kind = Sphere;
		obj->rotation = vec3(0.0f, 0.0f, 5.0f);
		obj->hit = &hit_sphere;
	}
	else if (!ft_strcmp(*argv, "pl"))
	{
		obj->kind = Plane;
		obj->hit = &hit_plane;
	}
	else if (!ft_strcmp(*argv, "cy"))
	{
		obj->kind = Cylinder;
		obj->hit = &hit_cylinder;
	}
	argv++;
	obj->coords = get_vector(*argv++);
	if (obj->kind == Sphere)
		asign_vec3(&obj->rotation, 0, 0, 0);
	else
		obj->rotation = get_vector(*argv++);
	if (obj->kind != Plane)
	{
		obj->sizes.vs[0] = get_scalar(*argv++);
		if (obj->kind == Cylinder)
			obj->sizes.vs[1] = get_scalar(*argv++);
	}
	obj->color = get_color(get_vector(*argv++));
}

void fill_obj_list(t_object_list *objs, char **argv)
{
	size_t		obj_to_alloc;

	obj_to_alloc = ((objs->len == 0) * 2 + (objs->len != 0) * (objs->len + 1)) * sizeof(t_object);
	objs->objs = ft_realloc(objs->objs, objs->len * sizeof(t_object), obj_to_alloc, 0);
	fill_obj(&objs->objs[objs->len], argv);
	write(1, "Rotacion: ", 11);
	print_vec3(objs->objs[objs->len].rotation);
	objs->len++;
	return (objs);
}