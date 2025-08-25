/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:23:20 by ggasset-          #+#    #+#             */
/*   Updated: 2025/07/23 18:20:36 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vec3.h"

enum	e_object
{
	Sphere,
	Cylinder,
	Plane,
};

typedef struct t_hit_args	t_hit_args;
typedef struct t_hit_info	t_hit_info;

typedef struct t_object
{
	t_point3		coords;
	t_rotation		rotation;
	t_color			color;
	t_vec3			sizes;
	enum e_object	kind;
	int				(*hit)(t_hit_args hit_args);
}		t_object;

t_object	object(enum e_object kind);

typedef struct t_object_list
{
	t_object	*objs;
	size_t		len;
}		t_object_list;

void		free_object_list(t_object_list list);

/*
### Distance (a.k.a. t)
*/
typedef struct t_hit_info
{
	t_point3	p;
	t_vec3		normal;
	t_data		distance;
	t_object	hit_obj;
	int			did_hit;
}		t_hit_info;

typedef struct t_hit_args
{
	t_object	object;
	t_interval	distance_range;
	t_ray		ray;
	t_hit_info	*hit_info;
}		t_hit_args;

int			hit_sphere(t_hit_args args);
int			world_hit(t_object_list world_objs, t_hit_args args);

#endif
