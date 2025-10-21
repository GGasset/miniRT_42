/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-16 16:01:14 by ggasset-          #+#    #+#             */
/*   Updated: 2025-10-16 16:01:14 by ggasset-         ###   ########student.  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minilibx_funcs.h"
#include "parsing.h"

#include <stdio.h>

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define USF "%s %s %s %s %s %s %s%s"
#define USAGE "Usage:\n./miniRT map_path\n"
#define L "\tL pos(x,y,z) brightness[0,1](x) color[0,255](r,g,b)\n"
#define A "\tA brightness[0,1](x) color[0,255](r,g,b)\n"
#define C "\tC pos(x,y,z) norm_direction[-1,1](x,y,z) FOV[0,180](x)\n"
#define PL "\tpl pos(x,y,z) norm_direct[-1,1](x,y,z) color[0,255](r,g,b)\n"
#define SP "\tsp pos(x,y,z) size[0,∞](x) color[0,255](r,g,b)\n"
#define CY "\tcy pos(x,y,z) norm_dir[-1,1](x,y,z) diameter[0,∞](x)"
#define CY1 "height[0,∞](x) color[0,255](r,g,b)\n"

static char	**read_lines(int fd)
{
	char	**out;
	char	*buff;
	char	tmp[2];

	ft_bzero(tmp, 2);
	buff = 0;
	if (read(fd, tmp, 0) == -1)
		return (0);
	while (read(fd, tmp, 1) > 0)
		buff = ft_strjoin_free(buff, tmp, TRUE, FALSE);
	out = ft_split(buff, '\n');
	free(buff);
	return (out);
}

static int	parse(int argc, char **argv, t_render_data *d)
{
	char				**lines;
	int					fd;
	size_t				i;
	t_object_counter	counter;

	ft_bzero(&counter, sizeof(t_object_counter));
	if (argc != 2)
		return (printf(USF, USAGE, L, A, C, PL, SP, CY, CY1), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Could not open file %s\n", argv[1]), 1);
	lines = read_lines(fd);
	if (!lines)
		return (printf("Empty file err\n"), 1);
	i = 0;
	while (lines[i])
		if (!check_router(lines[i++], &counter))
			return (ft_free_splitted(lines), 1);
	if (!counter.n_a || !counter.n_c || counter.n_l)
		return (printf("Missing id\n"), ft_free_splitted(lines), 1);
	i = 0;
	while (lines[i])
		fill_dispatcher(&d->scene, lines[i++]);
	ft_free_splitted(lines);
	return (0);
}

int main(int argc, char **argv)
{
	t_render_data	render_d;

	ft_bzero(&render_d, sizeof(t_render_data));
	if (parse(argc, argv, &render_d))
		return (0);
	render_d.mlx = mlx_init();
	if (!render_d.mlx)
		return (1);
	render_d.img.res.x = WINDOW_WIDTH;
	render_d.img.res.y = WINDOW_WIDTH * ASPECT_RATIO;
	render_d.scene.camera.width = render_d.img.res.x;
	render_d.scene.camera.height = render_d.img.res.y;
	render_d.win = mlx_new_window(render_d.mlx, render_d.img.res.x,
			render_d.img.res.y, "MiniRT");	
	if (!render_d.win)
		return (free_mlx(render_d.mlx));
	render_loop(&render_d);
	free_render_data(&render_d);
	return (0);
}
