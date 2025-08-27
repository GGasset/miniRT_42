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
	hit_args.distance_range.max = 10000;
	hit_args.distance_range.min = 1E-3;
    hit_args.hit_info = &hit_info;
	hit_args.ray = ray;
	out = get_sky_color(d->scene.camera, pixel_i / d->scene.camera.height);
	out *= !i;
	if (world_hit(d->scene.objects, hit_args))
	{
		out = shift(hit_info.hit_obj.color, scene.ambient_light.color,
			scene.ambient_light.brightness, 0);
		out = shift(out, scene.light.color, scene.light.brightness * 1, 0);
		//out = shift(out, world_get_color(d, ++i, pixel_i, bounced_ray), .1, 0);
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
