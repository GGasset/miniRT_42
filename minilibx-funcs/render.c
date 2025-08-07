/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:52:59 by ggasset-          #+#    #+#             */
/*   Updated: 2025/08/06 17:03:21 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_funcs.h"
#include "camera.h"

int	render_image(t_render_data *render_d)
{
	render_d->img.img = mlx_new_image(render_d->mlx,
			render_d->img.res.x, render_d->img.res.y);
	if (!render_d->img.img)
		return (mlx_loop_end(render_d->mlx), 1);
	render_d->img.addr = mlx_get_data_addr(render_d->img.img,
			&render_d->img.bits_per_pixel, &render_d->img.line_length,
			&render_d->img.endian);
	if (!render_d->img.addr)
		return (free_img(render_d), mlx_loop_end(render_d->mlx), 1);
	if (render(render_d))
		return (0);
	mlx_put_image_to_window(render_d->mlx, render_d->win, render_d->img.img,
		0, 0);
	printf("AAAAAAAAA\n");
	// free_img(render_d);
	return (0);
}

void	render_loop(t_render_data *render_d)
{
	create_hooks(render_d);
	// render_image(render_d);
	mlx_loop_hook(render_d->mlx, render_image, render_d);
	mlx_loop(render_d->mlx);
}

