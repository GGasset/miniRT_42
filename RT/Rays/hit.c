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
