/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:08:26 by ggasset-          #+#    #+#             */
/*   Updated: 2025/09/22 18:32:23y alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_funcs.h"
#include "camera.h"
#include "stdio.h"

int	render(t_render_data *render_d)
{
    size_t	i;
	t_ray	ray;

	i = 0;
    printf("Render loop started...  \n");
    while (i < render_d->scene.camera.height * render_d->scene.camera.width)
    {
		ray = create_ray(render_d->scene.camera, i);
		// printf("i: %zu  ray orig: %lf  direct: %lf\n",i,  y(ray.orig), y(ray.direct));
		((int *)render_d->img.addr)[i] = world_get_color(render_d, 0, i, ray);
        i++;
	}
	//render_d->scene.camera.rotation.vs[0] += 90;
	return (0);
}
