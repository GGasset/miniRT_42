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
	quadratic(&out_data->distance, args, sqrt_in);
	out_data->p = vec_sum(args.ray.orig, vec_smul(args.ray.direct, out_data->distance));
	t = dot(args.object.rotation, vec_sust(out_data->p, vec_sust(args.object.coords, args.ray.orig)));
	if (t < 0 || t > args.object.sizes.vs[1])
		return (0);
	out_data->did_hit = 1;
	tmp = vec_smul(args.object.rotation, -t);
	tmp = vec_sum(tmp, vec_smul(args.ray.direct, out_data->distance));
	out_data->normal = norm(vec_sum(tmp, args.object.coords));
	out_data->hit_obj = args.object;
	return (out_data->did_hit);
}

static int	calculate_caps(t_hit_args args, t_hit_info *out, int is_end_cap)
{
	t_vec3	c;
	t_vec3	b;
	t_vec3	nd;
	t_data	d;
	t_data	r;

	r = x(args.object.sizes) / 2;
	b = vec_sust(args.object.coords, args.ray.orig);
	is_end_cap = is_end_cap != 0;
	c = vec_sum(b, vec_smul(vec_smul(args.object.rotation,
					y(args.object.sizes)), is_end_cap));
	d = dot(args.object.rotation, c)
		/ dot(args.object.rotation, args.ray.direct);
	nd = vec_smul(args.ray.direct, d);
	if (dot(vec_sust(nd, c), vec_sust(nd, c)) >= r * r)
		return (0);
	out->did_hit = 1;
	out->distance = d;
	out->hit_obj = args.object;
	out->normal = norm(vec_smul(args.object.rotation, 1 - 2 * (!is_end_cap)));
	return (1);
}

int	hit_cylinder(t_hit_args args)
{
	t_hit_info	tmp[3];
	t_hit_info	closest_hit;
	int			did_hit;
	int			is_closer;
	size_t		i;

	args.object.rotation = norm(args.object.rotation);
	ft_bzero(&closest_hit, sizeof(t_hit_info));
	ft_bzero(&tmp, sizeof(t_hit_info) * 3);
	did_hit = calculate_cylinder(args, &tmp[0]);
	did_hit = calculate_caps(args, &tmp[1], 0) || did_hit;
	did_hit = calculate_caps(args, &tmp[2], 1) || did_hit;
	if (!did_hit)
		return (0);
	closest_hit.distance = args.distance_range.max + 1;
	i = 0;
	while (i < 3)
	{
		is_closer = tmp[i].did_hit && tmp[i].distance > args.distance_range.min;
		if (is_closer && (tmp[i].distance < closest_hit.distance))
			closest_hit = tmp[i];
		i++;
	}
	*args.hit_info = closest_hit;
	return (args.hit_info->did_hit);
}
