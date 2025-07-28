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

/*t_ray create_equidistant_ray(t_camera camera, size_t pixel_i)
{
    t_data aspect_ratio = (t_data)camera.width / camera.height;
    t_data viewport_height = 2.0;pixel0_pos(camera, pixel_i, pixel_delta)0);

    // Dirección en la que mira la cámara (eje Z negativo)
    t_vec3 forward = vec3(0, 0, -1);

    // Centro del viewport a una unidad delante de la cámara
    t_vec3 viewport_center = vec_sum(camera.camera_pos, forward);

    // Esquina superior izquierda
    t_vec3 upper_left = vec_sust(vec_sust(viewport_center,
                                          vec_sdiv(horizontal, 2)),
                                 vec_sdiv(vertical, 2));

    // Coordenadas del píxel
	size_t x = pixel_i % camera.width;
	size_t y = pixel_i / camera.width;

	t_data fx = (t_data)x / (t_data)camera.width;
	t_data fy = (t_data)y / (t_data)camera.height;

	t_vec3 u = vec_smul(horizontal, fx);
	t_vec3 v = vec_smul(vertical, fy);


    // Posición del píxel en el espacio 3D
    t_vec3 pixel_position = vec_sum(vec_sum(upper_left, u), v);

    // Dirección del rayo: desde la cámara al píxel
    t_vec3 direction = norm(vec_sust(pixel_position, camera.camera_pos));

    return ray(camera.camera_pos, direction);
}*/
