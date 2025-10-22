/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:45:58 by alvmoral          #+#    #+#             */
/*   Updated: 2025/10/22 16:49:12 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "libft.h"
#include "vec3.h"

int	hit_sphere(t_hit_args args)
{
	double		a;
	double		h;
	double		c;
	t_vec3		center2r_orig;
	t_object	sphere;

	sphere = args.object;
	center2r_orig = vec_sust(sphere.coords, args.ray.orig);
	a = dot(args.ray.direct, args.ray.direct);
	h = dot(args.ray.direct, center2r_orig);
	c = dot(center2r_orig, center2r_orig) - (sphere.sizes.vs[0]
			* sphere.sizes.vs[0]);
	args.hit_info->did_hit = 0;
	if (h * h - a * c >= 0)
	{
		args.hit_info->distance = (h - sqrt(h * h - a * c)) / a;
		args.hit_info->hit_obj = args.object;
		args.hit_info->p = vec_sum(args.ray.orig, vec_smul(args.ray.direct,
					args.hit_info->distance));
		args.hit_info->normal = norm(vec_sust(args.hit_info->p, sphere.coords));
		args.hit_info->did_hit = 1;
	}
	return (args.hit_info->did_hit);
}
