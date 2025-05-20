/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-20 12:50:09 by ggasset-          #+#    #+#             */
/*   Updated: 2025-05-20 12:50:09 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

#include "objects.h"

typedef struct t_light
{
	t_point3	coords;
	double		brightness;
	t_color		color;
}		t_light;

typedef struct t_camera
{
	size_t	width;
	double	aspect_ratio;
	size_t	FOV;
	size_t	max_bounces;
}		t_camera;

t_color	ray_color(t_ray ray, t_camera camera, t_object_list objs);

#endif
