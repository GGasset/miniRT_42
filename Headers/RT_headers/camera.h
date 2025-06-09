/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:50:09 by ggasset-          #+#    #+#             */
/*   Updated: 2025/06/09 15:14:40 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "objects.h"
# include "stdlib.h"
// # include "../minilibx_funcs.h"

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
// int		render(t_render_data *render_data);

void			print_t_scene(t_scene s);
char			**format_line(char *line);
unsigned int	ft_atoui(const char *str);
t_data			get_scalar(char *value);
size_t			get_scalar_size_t(char *value);
t_vec3			get_vector(char *dim);


void	fill_ambient_ligth(t_light *ambient, char **argv);
void	fill_ligth(t_light *light, char **argv);
void	fill_camera(t_camera *cam, char **argv);
void	fill_obj(t_object *obj, char **argv);
void	fill_obj_list(t_object_list *objs, char **argv);
#endif
