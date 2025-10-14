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

static int	key_hook(int keycode, t_render_data *render_d)
{
	if (keycode == 65307)
		mlx_loop_end(render_d->mlx);
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
	mlx_hook(r_d->win, 17, (1L << 17), close_hook, r_d);
}
