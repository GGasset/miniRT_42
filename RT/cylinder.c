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
static t_data	calculate_quadratic_sqrt(t_hit_args args)
{
	t_vec3	nxa;
	t_data	r;
	t_data	tmp;
	t_data	out;

	r = args.object.sizes.vs[0] / 2;
	nxa = cross_product(args.ray.direct, args.object.rotation);
	if (!modulus(nxa))
		return (-1);
	out = dot(nxa, nxa) * r * r;
	tmp = dot(vec_sust(args.object.coords, args.ray.orig), nxa);
	tmp *= tmp;
	out -= dot(args.object.rotation, args.object.rotation) * tmp;
	return (out);
}

static void	quadratic(t_data *out_d, t_hit_args args, t_data sqrt_in)
{
	t_vec3	nxa;
	t_data	nxanxa;
	t_vec3	b;
	t_data	before_sqrt;
	t_data	solutions[2];
	
	b = vec_sust(args.object.coords, args.ray.orig);
	nxa = cross_product(args.ray.direct, args.object.rotation);
	nxanxa = dot(nxa, nxa);
	before_sqrt = dot(nxa, cross_product(b, args.object.rotation));
	solutions[0] = (before_sqrt + sqrt(sqrt_in)) / nxanxa;
	solutions[1] = (before_sqrt - sqrt(sqrt_in)) / nxanxa;
	*out_d = solutions[0] * (solutions[0] <= solutions[1]);
	*out_d += solutions[1] * (solutions[0] > solutions[1]);
}

// Does not include end caps
static int	calculate_cylinder(t_hit_args args, t_hit_info *out_data)
{
	t_data	sqrt_in;
	t_data	t;
	t_vec3	tmp;

	if (!out_data)
		return (0);
	sqrt_in = calculate_quadratic_sqrt(args);
	if (sqrt_in < 0)
		return (0);
	quadratic(&args.hit_info->distance, args, sqrt_in);
	out_data->p = vec_sum(args.ray.orig, vec_smul(args.ray.direct, out_data->distance));
	//t = dot(args.object.rotation, vec_sum(vec_smul(args.ray.direct, out_data->distance), args.object.coords));
	t = dot(args.object.rotation, vec_sust(vec_smul(args.ray.direct, out_data->distance), vec_sust(args.object.coords, args.ray.orig)));

	if (t < 0 || t > args.object.sizes.vs[1])
		return (0);
	out_data->did_hit = 1;
	tmp = vec_smul(args.object.rotation, -t);
	tmp = vec_sum(tmp, vec_smul(args.ray.direct, out_data->distance));
	out_data->normal = vec_sum(tmp, args.object.coords);
	out_data->hit_obj = args.object;
	return (out_data->did_hit);
}

int	hit_cylinder(t_hit_args args)
{
	return (calculate_cylinder(args, args.hit_info));
}
