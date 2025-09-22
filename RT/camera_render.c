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

void print_loading_bar(size_t i, size_t pixel_count)
{
	size_t	bar_char_count;
	t_data	percentage_completed;
	size_t	j;

	if (i % 700)
		return ;
	bar_char_count = 10;
	percentage_completed = (t_data)i / (pixel_count);
	printf("[");
	j = 0;
	while (j < bar_char_count)
	{
		if ((float)j / bar_char_count > percentage_completed)
			printf(" ");
		else
			printf("#");
		j++;
	}
	printf("] ");
	printf("%i%%", (int)(percentage_completed * 100));
	printf("\r");
}

int	render(t_render_data *render_d)
{
	size_t	pixel_count;
    size_t	i;
	t_ray	ray;

	printf("\n\n");
	pixel_count = render_d->scene.camera.height * render_d->scene.camera.width;
	i = 0;
    while (i < pixel_count)
    {
		ray = create_ray(render_d->scene.camera, i);
		((int *)render_d->img.addr)[i] = world_get_color(render_d, 0, i, ray);
        i++;
		print_loading_bar(i, pixel_count);
	}
	i = 0;
	while (i++ < 100)
		printf(" ");
	printf("\r");
	return (0);
}
