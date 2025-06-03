/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 17:10:56 by ggasset-          #+#    #+#             */
/*   Updated: 2025-05-22 17:10:56 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_funcs.h"

static double	fov_to_zoom(size_t fov)
{
	double	out;

	out = fov;
	out = 180 - out;
	out /= 180.0;
	return (out);
}

static int	key_hook(int keycode, t_render_data *render_d)
{
	double	zoom;

	if (keycode == 65307)
		mlx_loop_end(render_d->mlx);
	return (0);
}

static int	mouse_hook(int button, int x, int y, t_render_data *render_d)
{
	double	zoom;
	double	centralizer;

	x = x;
	y = y;
	zoom = fov_to_zoom(render_d->scene.camera.fov);
	centralizer = 2 * fabs(.5 - zoom) / 5;
	centralizer *= zoom >= .5 && button == 4;
	centralizer *= zoom < .5 && button == 5;
	if (button == 4)
		render_d->scene.camera.fov += .05 * 180 * zoom + centralizer;
	else if (button == 5)
		render_d->scene.camera.fov -= .05 * 180 * zoom + centralizer;
	mlx_loop(render_d->mlx);
	return (0);
}

static int	close_hook(t_render_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

void	create_hooks(t_render_data *r_d)
{
	mlx_key_hook(r_d->win, key_hook, r_d);
	mlx_mouse_hook(r_d->win, mouse_hook, r_d);
	mlx_hook(r_d->win, 17, (1L << 17), close_hook, r_d);
}
