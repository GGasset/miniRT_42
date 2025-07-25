#include "../../Headers/RT_headers/camera.h"
#include "../../Headers/minilibx_funcs.h"

void	fill_ambient_ligth(t_light *ambient, char **argv)
{
	asign_vec3(&ambient->coords, 0.0, 0.0, 0.0); // Por poner algo
	ambient->brightness = get_scalar(*argv++);
	copy_vec3(&ambient->color, get_vector(*argv++));
}

void	fill_ligth(t_light *light, char **argv)
{
	light->coords = get_vector(*argv++); // Por poner algo
	light->brightness = get_scalar(*argv++);
	copy_vec3(&light->color, get_vector(*argv++));
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