/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-22 09:52:16 by ggasset-          #+#    #+#             */
/*   Updated: 2025-10-22 09:52:16 by ggasset-         ###   ########student.  */
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

static void	get_viewport(t_camera cam, t_vec3 viewport[2])
{
	double	aspect_ratio;
	double	h;
	double	viewport_width;
	double	viewport_height;
	t_vec3	u;

	if (!viewport)
		return ;
	aspect_ratio = (double)cam.width / cam.height;
	h = tan(cam.fov * 3.14159 / 180 / 2);
	viewport_width = 2.0 * aspect_ratio * 2 * h * cam.focal_len;
	viewport_height = viewport_width / aspect_ratio;
	u = norm(cross_product(vec3(0, 1, 0), cam.rotation));
	viewport[0] = vec_smul(u, viewport_width);
	viewport[1] = vec_smul(cross_product(cam.rotation, u), -1);
	viewport[1] = vec_smul(viewport[1], viewport_height);
}

static t_vec3	get_pixel0_pos(t_camera c, t_vec3 delta[2])
{
	t_vec3	viewport[2];
	t_vec3	upper_left;
	t_vec3	upper_left_pixel_pos;

	get_viewport(c, viewport);
	delta[0] = vec_sdiv(viewport[0], c.width);
	delta[1] = vec_sdiv(viewport[1], c.height);
	upper_left = vec_smul(c.rotation, c.focal_len);
	upper_left = vec_sust(c.camera_pos, upper_left);
	upper_left = vec_sust(upper_left, vec_sdiv(viewport[0], 2));
	upper_left = vec_sust(upper_left, vec_sdiv(viewport[1], 2));
	upper_left_pixel_pos = vec_sum(upper_left, vec_smul(
				vec_sum(delta[0], delta[1]), .5));
	return (upper_left_pixel_pos);
}

static t_ray	assemble_ray(t_camera camera, t_vec3 pixel_center)
{
	t_ray		out;

	out = ray(camera.camera_pos, vec_sust(pixel_center, camera.camera_pos));
	return (out);
}

t_ray	create_ray(t_camera camera, size_t pixel_i)
{
	t_vec3	pixel_delta[2];
	t_vec3	pixel_center;
	t_vec3	pixel0_pos;

	camera.rotation = norm(camera.rotation);
	camera.rotation = element_mult(camera.rotation, vec3(1, -1, -1));
	pixel0_pos = get_pixel0_pos(camera, pixel_delta);
	pixel_center = vec_sum(vec_sum(pixel0_pos,
				vec_smul(pixel_delta[0], pixel_i % camera.width)),
			vec_smul(pixel_delta[1], pixel_i / camera.width));
	return (assemble_ray(camera, pixel_center));
}
