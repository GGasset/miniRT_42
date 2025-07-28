/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-28 14:33:15 by ggasset-          #+#    #+#             */
/*   Updated: 2025-07-28 14:33:15 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_ray	ray(t_point3 position, t_rotation direction)
{
	t_ray	out;

	out.orig = position;
	out.direct = direction;
	return (out);
}

static void	get_viewport(t_camera camera, t_vec3 viewport[2])
{
	double	aspect_ratio;
	double	h;
	double	viewport_width;

	if (!viewport)
		return ;
	aspect_ratio = (double)camera.width / camera.height;
	h = tan(camera.fov * 3.14159 / 180 / 2);
	viewport_width = 2.0 * aspect_ratio * 2 * h * camera.focal_len;
	viewport[0] = vec3(viewport_width, 0, 0);
	viewport[1] = vec3(0, -(viewport_width / aspect_ratio), 0);
}

static t_vec3	get_pixel0_pos(t_camera c, size_t i, t_vec3 d[2])
{
	t_vec3	viewport[2];
	t_vec3	upper_left;
	t_vec3	upper_left_pixel_pos;

	get_viewport(c, viewport);
	d[0] = vec_sdiv(viewport[0], c.width);
	d[1] = vec_sdiv(viewport[1], c.height);
	upper_left = vec_sust(vec_sust(vec_sust(c.camera_pos,
					vec3(0, 0, c.focal_len)),
				vec_sdiv(viewport[0], 2)),
			vec_sdiv(viewport[1], 2));
	upper_left_pixel_pos = vec_sum(upper_left, vec_smul(
				vec_sum(d[0], d[1]), .5));
	return (upper_left_pixel_pos);
}

t_ray	create_ray(t_camera camera, size_t pixel_i)
{
	t_vec3	pixel_delta[2];
	t_vec3	upper_left_pixel_pos;
	t_vec3	pixel_center;
	t_vec3	pixel0_pos;

	pixel0_pos = get_pixel0_pos(camera, pixel_i, pixel_delta);
	pixel_center = vec_sum(vec_sum(pixel0_pos,
				vec_smul(pixel_delta[0], pixel_i % camera.width)),
			vec_smul(pixel_delta[1], pixel_i / camera.width));
	return (ray(camera.camera_pos, vec_sust(pixel_center, camera.camera_pos)));
}
