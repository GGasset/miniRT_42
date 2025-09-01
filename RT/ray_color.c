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

t_color	get_color(t_vec3 in)
{
	t_color	out;

	out = 0xFF << 24;
	out += (int)in.vs[2] << 16;
	out += (int)in.vs[1] << 8;
	out += (int)in.vs[0];
	return (out);
}

t_vec3	get_rgb(t_color in)
{
	t_vec3	out;

	out.vs[0] = in & 255;
	out.vs[1] = in >> 8 & 255;
	out.vs[2] = in >> 16 & 255;
	return (out);
}

t_color	point_ilum(t_color current, t_hit_info info, t_scene s, t_light l)
{
	t_vec3	light_direction;
	t_data	light_normal_angle;
	t_hit_info	hit_info;
	t_hit_args	hit_args;

	ft_bzero(&hit_info, sizeof(t_hit_info));
	ft_bzero(&hit_args, sizeof(t_hit_args));
	light_direction = norm(vec_sust(l.coords, info.p));
	light_normal_angle = vec_angle(light_direction, info.normal);
	l.brightness *= (190 - light_normal_angle) / 180;
	hit_args.hit_info = &hit_info;
	hit_args.ray.orig = vec_sum(info.p, info.normal);
	hit_args.ray.direct = light_direction;
	hit_args.distance_range.min = 0;
	hit_args.distance_range.max = modulus(vec_sust(info.p, l.coords));
	if (world_hit(s.objects, hit_args))
		l.brightness *= 0;
	return (iluminate(current, info.hit_obj.color, l));
}

t_color	iluminate(t_color current, t_color object_color, t_light light)
{
	t_vec3	object_rgb;
	t_vec3	light_rgb;
	t_vec3	out_rgb;

	light.brightness += (1 - light.brightness) * (light.brightness > 1)
		- light.brightness * (light.brightness < 0);
	object_rgb = get_rgb(object_color);
	light_rgb = get_rgb(light.color);
	out_rgb = element_mult(vec_sdiv(object_rgb, 255), vec_sdiv(light_rgb, 255));
	out_rgb = vec_smul(out_rgb, light.brightness * 255);
	out_rgb = vec_sum(get_rgb(current), out_rgb);
	out_rgb.vs[0] += (255 - out_rgb.vs[0]) * (out_rgb.vs[0] > 255)
		- out_rgb.vs[0] * (out_rgb.vs[0] < 0);
	out_rgb.vs[1] += (255 - out_rgb.vs[1]) * (out_rgb.vs[1] > 255)
		- out_rgb.vs[1] * (out_rgb.vs[1] < 0);
	out_rgb.vs[2] += (255 - out_rgb.vs[2]) * (out_rgb.vs[2] > 255)
		- out_rgb.vs[2] * (out_rgb.vs[2] < 0);
	return (get_color(out_rgb));
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
