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
    size_t	i;

	i = 0;
    printf("Render loop started...  ");
    while (i < render_d->scene.camera.height * render_d->scene.camera.width)
    {
		((int *)render_d->img.addr)[i] = world_get_color(render_d, 0, i, 0);
        i++;
	}
	//render_d->scene.camera.rotation.vs[0] += 90;
	printf("Render loop over\n");
	return (0);
}
