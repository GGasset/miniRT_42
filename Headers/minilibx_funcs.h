/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_funcs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:02:48 by ggasset-          #+#    #+#             */
/*   Updated: 2025/10/23 11:26:06 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_FUNCS_H
# define MINILIBX_FUNCS_H

# include "mlx.h"
# include "camera.h"

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 1080
# endif
# ifndef RENDER_WIDTH
#  define RENDER_WIDTH WINDOW_WIDTH
# endif
# ifndef ASPECT_RATIO
// 16:9 default aspect ratio
#  define ASPECT_RATIO 0.5625
# endif
# ifndef MAX_BOUNCES
#  define MAX_BOUNCES 2
# endif
# ifndef MAX_RANGE
#  define MAX_RANGE 10000
# endif
# ifndef SKY_COLOR
#  define SKY_COLOR 0xFF021d28
# endif
# ifndef MOVEMENT_SPD
#  define MOVEMENT_SPD 5
# endif
# ifndef EPSILON
#  define EPSILON 1e-5
# endif

typedef struct s_res
{
	int	x;
	int	y;
}			t_res;

typedef struct s_win_d
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_res	res;
}				t_win_d;

typedef struct t_render_data
{
	int		has_rendered;
	t_scene	scene;
	t_win_d	img;
	void	*mlx;
	void	*win;
}		t_render_data;

void	create_hooks(t_render_data *r_d);
int		render_image(t_render_data *render_d);
void	render_loop(t_render_data *render_d);
int		render(t_render_data *render_d);

// Returns updated color
// ## Params:
// * i: recursive_depth, 0 for for first iter
// * color: starting color, 0 for first iter
int		world_get_color(t_render_data *d, size_t i, t_ray ray);

int		free_mlx(t_render_data *d);
int		free_img(t_render_data *d);
// Does not free scene
void	free_render_data(t_render_data *d);

#endif
