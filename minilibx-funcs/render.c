/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 16:52:59 by ggasset-          #+#    #+#             */
/*   Updated: 2025-05-22 16:52:59 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_funcs.h"
#include "camera.h"

int	render_image(t_render_data *render_d, t_scene scene)
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
	if (draw(render_d))
		return (0);
	mlx_put_image_to_window(render_d->mlx, render_d->win, render_d->img.img,
		0, 0);
	free_img(render_d);
	mlx_loop(render_d->mlx);
	return (0);
}

void	render_loop(t_render_data *render_d)
{
	create_hooks(render_d);
	mlx_loop_hook(render_d->mlx, render_image, render_d);
	mlx_loop(render_d->mlx);
}
