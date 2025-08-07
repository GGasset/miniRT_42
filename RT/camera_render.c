/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:08:26 by ggasset-          #+#    #+#             */
/*   Updated: 2025/07/23 20:23:44by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_funcs.h"
#include "camera.h"
#include "stdio.h"

int	render(t_render_data *render_data)
{
    size_t      i;
    size_t      height;
    size_t      width;
    t_hit_args  hit_args;
    t_hit_info  hit_info;
    t_data      distance;

    ft_bzero(&hit_args, sizeof(t_hit_args));
    i = 0;
    hit_info.did_hit = 0;
    hit_args.hit_info = &hit_info;
    width = render_data->scene.camera.width;
    height = render_data->scene.camera.height;
    
    printf("h: %ld  w: %ld", height, width);
    while (i < height * width)
    {
        hit_args.ray = create_ray(render_data->scene.camera, i);
        distance = hit_sphere(&hit_args);
        if (distance <= 0.0)
            ((int *)render_data->img.addr)[i] = 0xF010490;
        else
            ((int *)render_data->img.addr)[i] = 0xFFFFFFF;
        // printf("i: %ld ray_dir: ", i);
        // print_vec3(hit_args.ray.direct);
        i++;
	}
	return (0);
}
