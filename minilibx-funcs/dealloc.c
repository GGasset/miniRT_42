/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 17:30:39 by ggasset-          #+#    #+#             */
/*   Updated: 2025-05-22 17:30:39 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_funcs.h"

static int	free_img(t_render_data *d)
{
	if (!d->img.img || !d->mlx)
		return (1);
	mlx_destroy_image(d->mlx, d->img.img);
	d->img.img = 0;
	return (1);
}

static int	free_mlx(t_render_data *d)
{
	if (!d->mlx)
		return (1);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	d->mlx = 0;
	return (1);
}

static int	free_win(t_render_data *d)
{
	if (!d->win || !d->mlx)
		return (1);
	mlx_destroy_window(d->mlx, d->win);
	d->win = 0;
	return (1);
}

void	free_all(t_render_data *d)
{
	free_img(d);
	free_win(d);
	free_mlx(d);
}
