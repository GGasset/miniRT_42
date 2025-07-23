/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-05 13:08:48 by ggasset-          #+#    #+#             */
/*   Updated: 2025-06-05 13:08:48 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_ray	create_ray(t_camera camera, size_t pixel_i)
{
	size_t	row_i;
	t_data	drot[2];
	t_ray	out;

	drot[0] = camera.fov / 180 / camera.width * 1;
	drot[1] = camera.fov / 180 / (camera.width * camera.aspect_ratio) * 1;
	out.orig = camera.camera_pos;
	//out.direct.vs[]
}
