/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:08:26 by ggasset-          #+#    #+#             */
/*   Updated: 2025/07/23 20:23:44 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_funcs.h"
#include "camera.h"
#include "stdio.h"

int	render(t_render_data *render_d)
{
    size_t      i;
    t_hit_args  hit_args;
	t_hit_info	hit_info;

    ft_bzero(&hit_args, sizeof(t_hit_args));
    ft_bzero(&hit_info, sizeof(t_hit_info));
    hit_args.hit_info = &hit_info;
    i = 0;
	hit_args.distance_range.max = 10000;
	hit_args.distance_range.min = 1E-2;
    while (i < render_d->scene.camera.height * render_d->scene.camera.width)
    {
        hit_args.ray = create_ray(render_d->scene.camera, i);
        world_hit(render_d->scene.objects, hit_args);
        if (!hit_info.did_hit)
            ((int *)render_d->img.addr)[i] = 0xF010490;
        else
            ((int *)render_d->img.addr)[i] = 0xFFFFFFF;
        i++;
	}
	//render_d->scene.camera.rotation.vs[0] += 90;
	return (0);
}
