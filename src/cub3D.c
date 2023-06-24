/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 08:22:44 by yrimah            #+#    #+#             */
/*   Updated: 2023/06/24 08:22:48 by yrimah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/cub3d.h"

int	help(int *fd, int *index, char *path_cub, char **str)
{
	*index = 0;
	*str = ft_calloc(1, 1);
	*fd = open(path_cub, O_RDONLY);
	if (*fd < 0)
	{
		free(*str);
		return (1);
	}
	return (0);
}

void	ft_init_struct(t_game *data)
{
	data->time.old_time = 0;
	data->time.time = 0;
	data->instr = malloc(sizeof(char *) * 7);
	data->instr[6] = NULL;
}

char	*ft_init_game(t_game *data, int ac, char **av)
{
	char	*str;

	if (ac != 2)
	{
		ft_error("Error\nWrong number of arguments");
		exit(1);
	}
	else if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		ft_error("Error\nWrong file extension");
		exit(1);
	}
	ft_init_struct(data);
	str = ft_get_map(av[1]);
	if (!str)
	{
		free(str);
		free(data->instr);
		ft_error("Error\nWrong file");
		exit(0);
	}
	return (str);
}

void	check(t_game *data)
{
	int	counter;
	int	fd;

	counter = 0;
	while (counter < 4)
	{
		fd = open((char *)data->instr[counter], O_RDONLY);
		if (fd == -1)
		{
			printf("Invalid texture(s)\n");
			exit(1);
		}
		else
		{
			close(fd);
			counter++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_game	data;
	char	*str;
	char	**temp;

	str = ft_init_game(&data, argc, argv);
	temp = ft_split(str, '\n');
	ft_divide_map(&data, temp);
	free(str);
	ft_find_pl(&data);
	ft_check_map_border(&data);
	ft_init_door(&data);
	check(&data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, SCREENWIDTH, SCREENHEIGHT, "My Game");
	mlx_hook(data.win, 17, 0, ft_close, &data);
	data.img.img = mlx_new_image(data.mlx, SCREENWIDTH, SCREENHEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel,
			&data.img.line_length, &data.img.endian);
	ft_draw_ray_3d(&data);
	ft_draw_map(data);
	ft_draw_player(data);
	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	mlx_hook(data.win, 6, 1L << 6, &mouse_move, &data);
	mlx_hook(data.win, 2, 1L << 0, &key_input, &data);
	mlx_loop(data.mlx);
}
