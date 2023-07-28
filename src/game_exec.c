/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluiz-al <bluiz-al@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:23:18 by bluiz-al          #+#    #+#             */
/*   Updated: 2022/11/24 17:23:31 by bluiz-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_hook(t_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

int	patrol_move(t_data *data, int i, int idx)
{
	int	direction;

	data->r_bad += (data->r_bad == 0) * M_BAD;
	if (data->map[i] != data->r_bad && ++data->time != time(NULL) \
	&& data->time % 240 == 0)
	{
		data->time = 0;
		srand(time(NULL));
		direction = (rand() % 4) + 1;
		idx += (direction == 1) * (i - 1);
		idx += (direction == 2) * (i - data->width);
		idx += (direction == 3) * (i + 1);
		idx += (direction++ == 4) * (i + data->width);
		if (data->map[idx] == PATH || data->map[idx] == V_PATH \
		|| data->map[idx] == PLAY)
		{
			data->catch += (data->map[idx] == PLAY);
			data->map[idx] = data->r_bad;
			data->map[i] = PATH;
			return (1);
		}
		data->map[i] = data->r_bad;
	}
	return (0);
}

int	key_hook(int key, t_data *data)
{
	data->n_play = data->p_play;
	data->n_play -= (key == XK_Left || key == XK_a);
	data->n_play -= (key == XK_Up || key == XK_w) * data->width;
	data->n_play += (key == XK_Right || key == XK_d);
	data->n_play += (key == XK_Down || key == XK_s) * data->width;
	data->c_coin -= (data->map[data->n_play] == V_COIN);
	if (data->map[data->n_play] == WALL || (data->map[data->n_play] == EXIT \
	&& data->c_coin))
		return (0);
	data->moves += (key > 0xff50 && key < 0xff55);
	data->moves += (key == XK_a || key == XK_w || key == XK_s || key == XK_d);
	if (key == XK_Escape || data->map[data->n_play] == EXIT || \
	data->map[data->n_play] == BAD || data->map[data->n_play] == M_BAD)
		mlx_loop_end(data->mlx);
	data->map[data->p_play] = PATH;
	if (data->map[data->n_play] == EXIT)
		data->map[data->n_play] = EXIT;
	else if (data->map[data->n_play] == BAD || data->map[data->n_play] == M_BAD)
		data->map[data->n_play] = BAD;
	else if (data->map[data->n_play] != EXIT || \
	data->map[data->n_play] != BAD || data->map[data->n_play] == M_BAD)
		data->map[data->n_play] = PLAY;
	data->p_play = data->n_play;
	return (0);
}

int	render(t_data *data, int i)
{
	i = -1;
	while (++i < data->map_len)
	{
		if (data->map[i] == V_COIN)
			data->img = data->coin.img;
		if ((data->map[i] == BAD || data->map[i] == M_BAD) && \
		!patrol_move(data, i, 0))
			data->img = data->bad.img;
		if (data->map[i] == PATH || data->map[i] == V_PATH)
			data->img = data->path.img;
		if (data->map[i] == WALL)
			data->img = data->wall.img;
		if (data->map[i] == EXIT)
			data->img = data->exit.img;
		if (data->map[i] == PLAY)
			data->img = data->player.img;
		mlx_put_image_to_window(data->mlx, data->win, data->img, \
		i % data->width * BITS, i / data->width * BITS);
		print_moves(data);
	}
	data->r_bad = (data->r_bad == M_BAD) * BAD;
	data->time += time(NULL);
	if (data->catch)
		mlx_loop_end(data->mlx);
	return (0);
}

void	load_assets(t_data *data)
{
	data->bad.img = mlx_xpm_file_to_image(data->mlx, "./assets/bad.xpm", \
	&data->bad.width, &data->bad.height);
	data->coin.img = mlx_xpm_file_to_image(data->mlx, "./assets/coin.xpm", \
	&data->coin.width, &data->coin.height);
	data->exit.img = mlx_xpm_file_to_image(data->mlx, "./assets/exit.xpm", \
	&data->exit.width, &data->exit.height);
	data->path.img = mlx_xpm_file_to_image(data->mlx, "./assets/path.xpm", \
	&data->path.width, &data->path.height);
	data->player.img = mlx_xpm_file_to_image(data->mlx, \
	"./assets/player.xpm", &data->player.width, &data->player.height);
	data->wall.img = mlx_xpm_file_to_image(data->mlx, "./assets/wall.xpm", \
	&data->wall.width, &data->wall.height);
}
