#include "libft.h"
#include "minilibx_funcs.h"
#include <stdio.h>

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char    *strjoin_and_free(char *s1, char *s2)
{
	char    *joined;
	int             i;
	size_t  j;

	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
			return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
			joined[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
			joined[i++] = s2[j++];
	joined[i] = '\0';
	free(s1);
	return (joined);
}

char    *get_next_line(int fd)
{
	static char     buffer[1];
	static int      buffer_read = 0;
	static int      buffer_pos = 0;
	char            *line;
	char            temp[2];

	line = NULL;
	if (fd < 0 || 1 <= 0)
			return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, 1);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		temp[0] = buffer[buffer_pos++];
		temp[1] = '\0';
		line = strjoin_and_free(line, temp);
		if (temp[0] == '\n')
			break ;
	}
	return (line);
}

int main()
{
	t_render_data	render_d;
	// Setup

	ft_bzero(&render_d, sizeof(t_render_data));
	render_d.mlx = mlx_init();
	if (!render_d.mlx)
		return (1);
	render_d.img.res.x = WINDOW_WIDTH;
	render_d.img.res.y = WINDOW_WIDTH * ASPECT_RATIO;

	// Parsing
	int fd;
	fd = open("map.rt", O_RDONLY);
	if (fd == -1)
		return (1);
	char *line;
	while (1)	
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		fill_dispatcher(&render_d.scene, line);
	}
	print_t_scene(render_d.scene);

	// Execution

	render_d.scene.camera.width = render_d.img.res.x;
	render_d.scene.camera.height = render_d.img.res.y;
	render_d.win = mlx_new_window(render_d.mlx, render_d.img.res.x,
			render_d.img.res.y, "MiniRT");	
	if (!render_d.win)
		return (free_mlx(render_d.mlx));
	render_loop(&render_d);
	printf("Delete in future, exited loop.");
	free_render_data(&render_d);
	return (0);
}
