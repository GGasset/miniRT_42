/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:35:13 by ggasset-          #+#    #+#             */
/*   Updated: 2025/08/06 19:33:44 by alvmoral         ###   ########.fr       */
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

	render_d.scene.camera.fov = 60;
	render_d.scene.camera.rotation = norm(vec3(-10.0, 46.4, -0.9));
	// render_d.scene.camera.rotation = vec3(0, 0, -1);
	render_d.scene.camera.focal_len = 1;

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
