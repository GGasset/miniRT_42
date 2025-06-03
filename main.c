/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-03 10:35:13 by ggasset-          #+#    #+#             */
/*   Updated: 2025-06-03 10:35:13 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minilibx_funcs.h"
#include "stdio.h"

static void	render_loop(t_render_data *render_d)
{
	create_hooks(render_d);
	mlx_loop_hook(render_d->mlx, render_image, render_d);
	mlx_loop(render_d->mlx);
}

int main()
{
	t_render_data	render_d;

	ft_bzero(&render_d, sizeof(t_render_data));
	render_d.mlx = mlx_init();
	if (!render_d.mlx)
		return (1);
	render_d.img.res.x = WINDOW_WIDTH;
	render_d.img.res.y = WINDOW_WIDTH * 0.5625;
	render_d.win = mlx_new_window(render_d.mlx, render_d.img.res.x,
			render_d.img.res.y, "MiniRT");
	if (!render_d.win)
		return (free_mlx(render_d.mlx));
	render_loop(&render_d);
	printf("Delete in future, exited loop.");
	free_render_data(&render_d);
}
