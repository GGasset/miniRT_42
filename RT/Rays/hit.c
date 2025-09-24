/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-03 13:25:00 by ggasset-          #+#    #+#             */
/*   Updated: 2025-06-03 13:25:00 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minilibx_funcs.h"

t_ray	get_bounce(t_hit_args info)
{
	t_vec3	d;
	t_vec3	n;
	t_ray	out;

	ft_bzero(&out, sizeof(t_ray));
	if (!info.hit_info || !info.hit_info->did_hit)
		return (out);
	out.orig = info.hit_info->p;
	d = info.ray.direct;
	n = info.hit_info->normal;
	out.direct = vec_sust(d, vec_smul(d, 2 * dot(d, n)));
	out.direct = element_mult(out.direct, vec3(1, 1, -1));
	return (out);
}

static t_color	bounce(t_render_data *d, size_t i, t_hit_args hit, t_color in)
{
	t_data		reflectiveness;
	t_hit_args	hit_args;
	t_hit_info	hit_info;
	t_light		bounce_light;
	t_color		out;

	if (i > MAX_BOUNCES || !d)
		return (0);
	ft_bzero(&hit_args, sizeof(t_hit_args));
    ft_bzero(&hit_info, sizeof(t_hit_info));
	hit_args.distance_range.max = 10000;
	hit_args.distance_range.min = 1E-3;
    hit_args.hit_info = &hit_info;
	hit_args.ray = get_bounce(hit);
	if (!world_hit(d->scene.objects, hit_args))
		return (in);
	reflectiveness = .4;
	bounce_light.brightness = (10 - hit_info.distance) / 10 * reflectiveness;
	bounce_light.brightness /= !i + (i + 1) * (i + 1);
	bounce_light.color = world_get_color(d, ++i, 0, get_bounce(hit));
	out = iluminate(in, hit.hit_info->hit_obj.color, bounce_light);
	return (out);
}

int	world_get_color(t_render_data *d, size_t i, size_t pixel_i, t_ray ray)
{
	t_scene		scene;
    t_hit_args  hit_args;
	t_hit_info	hit_info;
	t_color		out;

	if (i > MAX_BOUNCES || !d)
		return (0);
	scene = d->scene;
    ft_bzero(&hit_args, sizeof(t_hit_args));
    ft_bzero(&hit_info, sizeof(t_hit_info));
	hit_args.distance_range.max = 1E4;
	hit_args.distance_range.min = 1E-3;
    hit_args.hit_info = &hit_info;
	hit_args.ray = ray;
	out = get_sky_color(d->scene.camera, pixel_i / d->scene.camera.height);
	out *= !i;
	if (world_hit(d->scene.objects, hit_args))
	{
		out = 0xFF000000;
		out = iluminate(out, hit_info.hit_obj.color, scene.ambient_light);
		out = point_ilum(out, hit_args, scene, scene.light, ray);
		out = bounce(d, i, hit_args, out);
	}
	return (out);
}

int	world_hit(t_object_list world_objs, t_hit_args args)
{
	size_t		i;
	t_hit_args	tmp_args;
	t_hit_info	closest_hit;
	t_hit_info	tmp_hit;

	tmp_args = args;
	ft_bzero(&closest_hit, sizeof(t_hit_info));
	tmp_args.hit_info = &tmp_hit;
	closest_hit.distance = args.distance_range.max;
	i = 0;
	while (i < world_objs.len)
	{
		tmp_args.object = world_objs.objs[i];
		if (tmp_args.object.hit(tmp_args)
			&& tmp_args.hit_info->distance < closest_hit.distance
			&& tmp_args.hit_info->distance > args.distance_range.min)
			closest_hit = *tmp_args.hit_info;
		i++;
	}
	*args.hit_info = closest_hit;
	return (closest_hit.did_hit);
}
