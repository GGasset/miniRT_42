/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:26:56 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/23 12:05:47 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/RT_headers/camera.h"
#include "../../Headers/minilibx_funcs.h"

void	fill_kind_hit(t_object *obj, char *prop)
{
	if (!ft_strcmp(prop, "sp"))
	{
		obj->kind = Sphere;
		obj->rotation = vec3(0.0f, 0.0f, 1.0f);
		obj->hit = &hit_sphere;
	}
	else if (!ft_strcmp(prop, "pl"))
	{
		obj->kind = Plane;
		obj->hit = &hit_plane;
	}
	else if (!ft_strcmp(prop, "cy"))
	{
		obj->kind = Cylinder;
		obj->hit = &hit_cylinder;
	}
}

void	fill_obj(t_object *obj, char **argv)
{
	fill_kind_hit(obj, *argv);
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

void	fill_obj_list(t_object_list *objs, char **argv)
{
	size_t		obj_to_alloc;

	obj_to_alloc = ((objs->len == 0) * 2 \
	+ (objs->len != 0) \
	* (objs->len + 1)) * sizeof(t_object);
	objs->objs = ft_realloc(objs->objs, objs->len \
		* sizeof(t_object), obj_to_alloc, 1);
	fill_obj(&objs->objs[objs->len], argv);
	print_vec3(objs->objs[objs->len].rotation);
	objs->len++;
}
