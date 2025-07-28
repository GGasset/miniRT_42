/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:08:48 by ggasset-          #+#    #+#             */
/*   Updated: 2025/07/23 20:12:20y alvmoral         ###   ########.fr       */
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

t_ray create_ray(t_camera camera, size_t pixel_i)
{

	t_vec3 viewport[2];
	get_viewport(camera, viewport);

	t_vec3 pixel_delta[2];
	pixel_delta[0] = vec_sdiv(viewport[0], camera.width);
	pixel_delta[1] = vec_sdiv(viewport[1], camera.height);

	t_vec3 upper_left = vec_sust(vec_sust(vec_sust(camera.camera_pos,
											vec3(0, 0, camera.focal_len)),
										vec_sdiv(viewport[0], 2)),
								vec_sdiv(viewport[1], 2));

	t_vec3 upper_left_pixel_pos = vec_sum(upper_left, vec_smul(vec_sum(pixel_delta[0], pixel_delta[1]), .5));

	size_t x = pixel_i % camera.width;
	size_t y = pixel_i / camera.width;
	t_vec3 pixel_center = vec_sum(vec_sum(upper_left_pixel_pos, 
		vec_smul(pixel_delta[0], x))
		, vec_smul(pixel_delta[1], y));

	return ray(camera.camera_pos, vec_sust(pixel_center, camera.camera_pos));
}

t_ray create_equidistant_ray(t_camera camera, size_t pixel_i)
{
    t_data aspect_ratio = (t_data)camera.width / camera.height;
    t_data viewport_height = 2.0;
    t_data viewport_width = aspect_ratio * viewport_height;

    // Ejes del viewport
    t_vec3 horizontal = vec3(viewport_width, 0, 0);       // eje X
    t_vec3 vertical = vec3(0, -viewport_height, 0);       // eje Y (hacia abajo)

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
}


