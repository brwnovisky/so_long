/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluiz-al <bluiz-al@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:10:37 by bluiz-al          #+#    #+#             */
/*   Updated: 2022/11/24 17:30:09 by bluiz-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void print_moves(t_data *data)
{
	char	*moves;

	moves = ft_itoa(data->moves);
	mlx_string_put(data->mlx, data->win, (data->p_play % data->width) \
	* BITS + 20, (data->p_play / data->width) * BITS + 9, 0xffffff, moves);
	free(moves);
}

void	print_end_messages(t_data *data)
{
	if (data->map[data->p_play] == BAD || data->map[data->p_play] == M_BAD)
			ft_printf("\n\n  *_* THE BAD-CARROT CATCH YOU!!! *_*\n\n");
	else if (data->map[data->n_play] == EXIT && !data->c_coin)
	{
		ft_printf("\n\n  \\0/ YOU WIN with %d moves!\\0/\n\n", data->moves);
		ft_printf("   Now, sleep in peace sweet bunny... ^.^ zzzzz\n\n");
	}
	else if (data->p_play != BAD && data->p_play != EXIT)
	{
		ft_printf("\n\n  0_0 YOU SKIPED THE GAME!");
		ft_printf(" But, don't forget the losted carrots, ok? -_0 \n\n");
	}
}

void	clean_data(t_data *data)
{
	if (data->mlx)
	{
		print_end_messages(data);
		mlx_destroy_image(data->mlx, data->bad.img);
		mlx_destroy_image(data->mlx, data->path.img);
		mlx_destroy_image(data->mlx, data->wall.img);
		mlx_destroy_image(data->mlx, data->coin.img);
		mlx_destroy_image(data->mlx, data->player.img);
		mlx_destroy_image(data->mlx, data->exit.img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
	}
	free(data->map);
	free(data->mlx);
	free(data);
}

void	perror_map_content(t_data *data)
{
	if (data->error[6] && ++data->error[17])
		ft_printf("\nError\n- Too many empty lines!\n\n");
	else if (data->error[7] && ++data->error[17])
		ft_printf("\nError\n- The map should be a rectangle!\n\n");
	if (data->error[8] && ++data->error[17])
		ft_printf("\nError\n- The map should be surrounded by a wall!\n\n");
	if (data->error[9] && ++data->error[17])
		ft_printf("\nError\n- The map needs only one exit position!\n\n");
	if (data->error[10] && ++data->error[17])
		ft_printf("\nError\n- The map needs only one player position!\n\n");
	if (data->error[11] && ++data->error[17])
		ft_printf("\nError\n- The map needs at least one coin!\n\n");
	if (data->error[12] && ++data->error[17])
		ft_printf("\nError\n- The map needs at least one exit position!\n\n");
	if (data->error[13] && ++data->error[17])
		ft_printf("\nError\n- The map needs at least one player position!\n\n");
	if (data->error[17])
	{
		clean_data(data);
		exit(1);
	}
}

void	perror_map_validate(t_data *data)
{
	if (data->error[1] && ++data->error[17])
		ft_printf("\nError\n- The program needs only one argument!\n\n");
	if (data->error[2] && ++data->error[17])
		ft_printf("\nError\n- Wrong extension file! Correct: \".ber\"!\n\n");
	if (data->error[3] && ++data->error[17])
		ft_printf("\nError\n- The file can't be read!\n\n");
	if (data->error[4] && ++data->error[17])
		ft_printf("\nError\n- The map is empty!\n\n");
	if (data->error[5] && ++data->error[17])
		ft_printf("\nError\n- Invalid character's file!\n\n");
	if (!data->error[5])
		perror_map_content(data);
	if (data->error[14] && ++data->error[17])
		ft_printf("\nError\n- The map has no valid path to win!\n\n");
	if (data->error[15] && ++data->error[17])
		ft_printf("\nError\n- The program can't be initialized!\n\n");
	if (data->error[16] && ++data->error[17])
		ft_printf("\nError\n- The program's window can't be crated!\n\n");
	if (data->error[17])
	{
		clean_data(data);
		exit(1);
	}
}


