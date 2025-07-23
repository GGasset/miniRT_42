/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:20:03 by ggasset-          #+#    #+#             */
/*   Updated: 2025/06/03 01:44:20 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "libft.h"
# include <stddef.h>
# include <math.h>

typedef double	t_data;

typedef struct t_vec3
{
	t_data	vs[3];
}		t_vec3;

typedef t_vec3	t_point3;
typedef t_vec3	t_color;
typedef t_vec3	t_rotation;

typedef struct t_ray
{
	t_point3	orig;
	t_vec3		direct;
}		t_ray;

t_ray		bounce_ray(t_ray in, t_rotation surface_normal);
t_point3	ray_at(t_data t);

typedef struct t_interval
{
	t_data	min;
	t_data	max;
}		t_interval;

t_vec3		*alloc_vec3(t_data x, t_data y, t_data z);
t_vec3		*asign_vec3(t_vec3 *vec, t_data x, t_data y, t_data z);
void		copy_vec3(t_vec3 *dest, t_vec3 *src);
void		destroy_vec3(t_vec3 *vec);
t_data  	x(t_vec3 *vec);
t_data  	y(t_vec3 *vec);
t_data  	z(t_vec3 *vec);
void    	print_vec3(t_vec3 *vec);
void    	vec_sum(t_vec3 *v1, t_vec3 *v2);

#endif
