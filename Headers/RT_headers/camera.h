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

# include "objects.h"

typedef struct t_render_data
{
}		t_render_data;

typedef struct t_light
{
	t_point3	coords;
	double		brightness;
	t_color		color;
}		t_light;

typedef struct t_camera
{
	size_t		width;
	double		aspect_ratio;
	size_t		fov;
	size_t		max_bounces;
	t_point3	camera_pos;
	t_rotation	rotation;
}		t_camera;

typedef struct t_scene
{
	t_camera		camera;
	t_object_list	objects;
	t_light			ambient_light;
	t_light			light;
}		t_scene;

t_color	ray_color(t_ray ray, t_camera camera, t_object_list objs);
void	render(t_scene scene, t_render_data *render_data);

#endif
