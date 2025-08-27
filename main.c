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
	t_object		object;

	// Setup

	ft_bzero(&render_d, sizeof(t_render_data));
	render_d.mlx = mlx_init();
	if (!render_d.mlx)
		return (1);
	render_d.img.res.x = WINDOW_WIDTH;
	render_d.img.res.y = WINDOW_WIDTH * ASPECT_RATIO;

	// Parsing

	render_d.scene.camera.fov = 90;
	render_d.scene.camera.rotation = vec3(0, 0, 0);
	render_d.scene.camera.camera_pos = vec3(0, 0, 10);
	render_d.scene.camera.focal_len = 1;
	render_d.scene.ambient_light.brightness = 1;
	render_d.scene.ambient_light.color = 0xFFFF0000;

	render_d.scene.light.brightness = 0;
	render_d.scene.light.color = 0xFF30BA8D;

	ft_bzero(&object, sizeof(t_object));
	object.kind = Sphere;
	object.sizes.vs[0] = 6;
	object.hit = &hit_sphere;
	object.color = 0xFF88ba30;

	render_d.scene.objects.len = 1;
	render_d.scene.objects.objs = &object;

	// Execution

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
