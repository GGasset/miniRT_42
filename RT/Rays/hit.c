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

int	world_get_color(t_render_data *d, size_t i, size_t pixel_i, int color)
{
    t_hit_args  hit_args;
	t_hit_info	hit_info;

	if (i > MAX_BOUNCES)
		return color;
    ft_bzero(&hit_args, sizeof(t_hit_args));
    ft_bzero(&hit_info, sizeof(t_hit_info));
	hit_args.distance_range.max = 10000;
	hit_args.distance_range.min = 1E-3;
    hit_args.hit_info = &hit_info;
	hit_args.ray = create_ray(d->scene.camera, pixel_i);

	if (world_hit(d->scene.objects, hit_args))
		return hit_info.hit_obj.color; // call this function recursively
	else
		return d->scene.ambient_light.color;
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
