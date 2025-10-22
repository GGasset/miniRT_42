/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:43:49 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 16:45:36 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "vec3.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

/*
	- En object->rotation está el vector normal
	- El vector normal codifica los coeficientes
	  de las dimensiones del plano (A, B, C).
	- El punto que pertenence al plano está object->coords.
	
	La cuestión consiste en determinar si existe algún t
	para que de una posición en la recta que coincida con
	un punto del plano.


*/
int	hit_plane(t_hit_args args)
{
	t_data		numerator;
	t_data		denominator;
	t_data		t;
	t_object	obj;

	obj = args.object;
	numerator = dot(obj.rotation, vec_sust(obj.coords, args.ray.orig));
	denominator = dot(obj.rotation, args.ray.direct);
	t = numerator / denominator;
	args.hit_info->did_hit = 0;
	if (t >= 0 && fabs(denominator) > 1e-6)
	{
		args.hit_info->did_hit = 1;
		args.hit_info->hit_obj = args.object;
		args.hit_info->p = vec_sum(vec_smul(args.ray.direct, t), \
		args.ray.orig);
		args.hit_info->distance = t;
		args.hit_info->normal = obj.rotation;
		if (vec_angle(args.ray.direct, args.hit_info->normal) < 90)
			args.hit_info->normal = vec_smul(args.hit_info->normal, -1);
	}
	return (args.hit_info->did_hit);
}
