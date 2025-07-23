/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:35:13 by ggasset-          #+#    #+#             */
/*   Updated: 2025/07/23 19:09:58 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minilibx_funcs.h"
#include "stdio.h"

int main()
{
	t_render_data	render_d;

	ft_bzero(&render_d, sizeof(t_render_data));
	render_d.mlx = mlx_init();
	if (!render_d.mlx)
		return (1);
	render_d.img.res.x = WINDOW_WIDTH;
	render_d.img.res.y = WINDOW_WIDTH * 0.5625;
	render_d.scene.camera.width = render_d.img.res.x;
	render_d.scene.camera.height = render_d.img.res.y;
	render_d.win = mlx_new_window(render_d.mlx, render_d.img.res.x,
			render_d.img.res.y, "MiniRT");	
	if (!render_d.win)
		return (free_mlx(render_d.mlx));
	render_loop(&render_d);
	printf("Delete in future, exited loop.");
	free_render_data(&render_d);
	return (0);
}
