/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-08 16:40:45 by ggasset-          #+#    #+#             */
/*   Updated: 2025-09-08 16:40:45 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

// Does not make the actual sqrt, just the inner part
static t_data	calculate_quadratic_sqrt(t_ray ray, t_hit_args args)
{
	t_vec3	nxa;
	t_data	r;
	t_data	tmp;
	t_data	out;

	r = args.object.sizes.vs[0] / 2;
	nxa = cross_product(ray.direct, args.object.rotation);
	out = dot(nxa, nxa) * r * r;
	tmp = dot(vec_sust(args.object.coords, ray.orig), nxa);
	tmp *= tmp;
	out -= dot(args.object.rotation, args.object.rotation) * tmp;
	return (out);
}

// Does not include end caps
static int	calculate_cylinder(t_ray ray, t_hit_args args, t_hit_info *out_data)
{
	t_vec3	b;
	t_data	sqrt_in;
	t_vec3	nxa;
	t_data	t;
	t_vec3	tmp;

	if (!out_data)
		return (0);
	b = vec_sust(args.object.coords, ray.orig);
	sqrt_in = calculate_quadratic_sqrt(ray, args);
	if (sqrt_in < 0)
	return (0);
	nxa = cross_product(ray.direct, args.object.rotation);
	out_data->distance = (dot(nxa, cross_product(b, args.object.rotation))
	+ sqrt(sqrt_in)) / dot(nxa, nxa);
	out_data->p = vec_sum(ray.orig, vec_smul(ray.direct, out_data->distance));
	t = dot(args.object.rotation, vec_sum(vec_smul(ray.direct, out_data->distance), args.object.coords));
	if (t >= 0 && t <= args.object.sizes.vs[1])
		return (0);
	out_data->did_hit = 1;
	tmp = vec_smul(args.object.rotation, -t);
	tmp = vec_sum(tmp, vec_smul(ray.direct, out_data->distance));
	out_data->normal = vec_sum(tmp, args.object.coords);
	return (out_data->did_hit);
}

int	hit_cylinder(t_ray ray, t_hit_args args)
{
	return (calculate_cylinder(ray, args, args.hit_info));
}
