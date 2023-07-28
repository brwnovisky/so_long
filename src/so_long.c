/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluiz-al <bluiz-al@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:01:36 by bluiz-al          #+#    #+#             */
/*   Updated: 2022/11/24 17:04:43 by bluiz-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --verbose ./so_long_b ./map/bonus3.ber 

#include "so_long.h"

void	map_build(t_data *data, char *map);

void	map_scan(t_data *data, int i, int direction);

void	verify(t_data *data, char *line);

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	data->error[1] = (argc != 2);
	data->error[2] = (argc == 2 && ft_strncmp(ft_strrchr(argv[1], '.'), \
	".ber", 5));
	if (--data->fd && argc == 2)
		data->fd = open(argv[1], O_RDONLY);
	map_build(data, NULL);
	perror_map_validate(data);
	map_scan(data, data->p_play, 1);
	data->error[14] = (data->s_coin != data->c_coin || !data->s_exit);
	data->mlx = mlx_init();
	data->error[15] = (data->mlx == NULL);
	data->win = mlx_new_window(data->mlx, data->width * BITS, \
	data->map_len / data->width * BITS, argv[0]);
	data->error[16] = (data->win == NULL);
	load_assets(data);
	perror_map_validate(data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, close_hook, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_hook, data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	clean_data(data);
	return (0);
}


char	*append(t_data *data, char *f_line)
{
	char	*f_map;
	int		i;	

	i = -1;
	f_map = data->map;
	data->map = (char *)ft_calloc(data->map_len + data->t_width + 1, sizeof(char));
	while (++i < data->map_len && f_map[i] != '\n')
		data->map[i] = f_map[i];
	while (++i <= data->map_len + data->t_width)
		data->map[i - 1] = f_line[i - data->map_len - 1];
	data->map_len = i - 1;
	free(f_map);
	free(f_line);
	return (data->map);
}

void	verify(t_data *data, char *line)
{
	int	i;

	i = -1;
	while (line[++i] && line[i] != '\n')
	{
		data->c_coin += (!data->error[0] && line[i] == COIN);
		data->c_exit += (!data->error[0] && line[i] == EXIT);
		data->c_play += (!data->error[0] && line[i] == PLAY);
		data->p_play += (data->c_play == 0);
		data->error[5] += (line[i] != WALL && line[i] != EXIT && line[i] \
		!= COIN && line[i] != PLAY && line[i] != PATH && line[i] != BAD);
		data->error[8] += (data->error[0] && line[i] != WALL);
		data->error[9] += (data->c_exit > 1);
		data->error[10] += (data->c_play > 1);
	}
	data->width += (data->width == 0) * i;
	data->t_width = i;
	data->error[6] += (i == 0);
	data->error[7] += (data->t_width != data->width);
	data->error[8] += (line[0] != WALL || line[data->t_width - 1] != WALL);
	data->error[11] += (data->error[0] == -1 && !data->c_coin);
	data->error[12] += (data->error[0] == -1 && !data->c_exit);
	data->error[13] += (data->error[0] == -1 && !data->c_play);
}

void	map_build(t_data *data, char *map)
{
	char	*line;

	data->error[3] = (data->fd < 0);
	line = get_next_line(data->fd);
	if (data->error[3] || !line)
	{
		if (map != NULL)
		{
			data->error[0] = -1;
			verify(data, map + (data->map_len - data->t_width));
		}
		data->error[4] = (map == NULL);
		return ;
	}
	if (map == NULL)
	{
		data->map = line;
		data->error[0] = 1;
		verify(data, line);
		data->map_len = data->width;
		return (map_build(data, data->map));
	}
	data->error[0] = 0;
	verify(data, line);
	return (map_build(data, append(data, line)));
}

void	map_scan(t_data *data, int i, int direction)
{
	int	idx;

	data->s_coin += (data->map[i] == COIN);
	data->map[i] = (data->map[i] == COIN) * V_COIN + (data->map[i] != COIN) \
	* data->map[i];
	data->map[i] = (data->map[i] == PATH) * V_PATH + (data->map[i] != PATH) \
	* data->map[i];
	while (direction <= 4)
	{
		idx = 0;
		idx += (direction == 1) * (i - 1);
		idx += (direction == 2) * (i - data->width);
		idx += (direction == 3) * (i + 1);
		idx += (direction++ == 4) * (i + data->width);
		data->s_exit += (data->s_exit == 0 && data->map[idx] == EXIT);
		if (data->s_coin == data->c_coin && data->s_exit)
			return ;
		if (data->map[idx] == COIN || data->map[idx] == PATH)
			map_scan(data, idx, 1);
	}
}
