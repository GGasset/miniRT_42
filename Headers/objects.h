/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-20 10:23:20 by ggasset-          #+#    #+#             */
/*   Updated: 2025-05-20 10:23:20 by ggasset-         ###   ########student.  */
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

typedef struct t_object
{
	t_point3	coords;
	t_color		color;
	t_data		size1;
	t_data		size2;
	e_object	kind;
}		t_object;

typedef struct t_hit_args
{
	t_object	object;
	t_interval	distance_range;
	t_ray		ray;
}	t_hit_args;


int		hit_sphere(t_hit_args args);
int		hit_cylinder(t_hit_args args);
int		hit_plane(t_hit_args args);

// ## Returns:
// * Wheter it hitted with the specified object
int		object_hit(t_hit_args args);


#endif
