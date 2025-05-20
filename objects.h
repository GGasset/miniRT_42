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
}		t_object;

#endif
