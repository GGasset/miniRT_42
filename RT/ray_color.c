/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-27 11:32:47 by ggasset-          #+#    #+#             */
/*   Updated: 2025-08-27 11:32:47 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "camera.h"
#include "libft.h"
#include "stdio.h"

t_color	iluminate(t_color current, t_color object_color, t_light light)
{
	t_color	out;

	out = current;
	if (!out || out == 0xFF000000)
	{
		out = shift(0, object_color, light.brightness, 1);
		//printf("Yes, a hit!\n");
	}
	out = shift(out, light.color, light.brightness, 0);
	return (out);
}

t_color	shift(t_color old, t_color target, t_data factor, int reflects)
{
	int	r;
	int	g;
	int	b;

	reflects = reflects != 0;
	factor += (1 - factor) * (factor > 1) - factor * (factor < 0);
	b = old & 255;
	g = (old & (255 << 8)) >> 8;
	r = (old & (255 << 16)) >> 16;
	r += ((target & 255)) * ((r / 255.) * factor * !reflects);
	r += ((target & 255) - r) * factor * reflects;
	g += (((target & (255 << 8)) >> 8)) * ((g / 255.) * factor * !reflects);
	g += ((target & (255 << 8)) >> 8) * factor * reflects;
	b += (((target & (255 << 16)) >> 16)) * ((b / 255.) * factor * !reflects);
	b += ((target & (255 << 16)) >> 16) * factor * reflects;
	r += (255 - r) * (r > 255) - r * (r < 0);
	g += (255 - g) * (g > 255) - g * (g < 0);
	b += (255 - b) * (b > 255) - b * (b < 0);
	return ((0xFF << 24) + (r << 16) + (g << 8) + b);
}

t_color	get_sky_color(t_camera camera, size_t pixel_y)
{
	int	out;
	int	to_add;

	out = 0xFF154f8c;
	to_add = (255 - (out & 255)) * pixel_y / (t_data)camera.height / 1.8;
	out += (to_add << 16) + (to_add << 8) + to_add;
	return (out);
}
