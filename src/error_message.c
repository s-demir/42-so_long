/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedemir <sedemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:52:18 by sedemir           #+#    #+#             */
/*   Updated: 2025/03/28 12:11:15 by sedemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include "../libs/minilibx-linux/mlx.h"
#include "../libs/Ft_Printf/ft_printf.h"

void	error_msg(char *str, int check, void *data)
{
	if (check == 3)
	{
		ft_printf("\n%s\n", str);
		game_exit((t_game *)data);
	}
	else
	{
		ft_printf("Error \n%s\n", str);
		game_exit((t_game *)data);
	}
}

static void	mlx_images_free(t_game *data)
{
	if (data && data->player_img)
	{
		mlx_destroy_image(data->mlxstart, data->player_img);
		data->player_img = NULL;
	}
	if (data && data->coin_img)
	{
		mlx_destroy_image(data->mlxstart, data->coin_img);
		data->coin_img = NULL;
	}
	if (data && data->exit_img)
	{
		mlx_destroy_image(data->mlxstart, data->exit_img);
		data->exit_img = NULL;
	}
	if (data && data->wall_img)
	{
		mlx_destroy_image(data->mlxstart, data->wall_img);
		data->wall_img = NULL;
	}
}

static void	free_map(t_game *data)
{
	int	line;

	line = 0;
	if (data && data->map)
	{
		while (line < data->height)
		{
			if (data->map[line] != NULL)
			{
				free(data->map[line]);
				data->map[line] = NULL;
			}
			line++;
		}
		free(data->map);
		data->map = NULL;
	}
}

static void	free_mlx(t_game *data)
{
	if (data)
		mlx_images_free(data);
	if (data && data->mlxstart)
	{
		if (data->mlxcontinue)
		{
			mlx_clear_window(data->mlxstart, data->mlxcontinue);
			mlx_destroy_window(data->mlxstart, data->mlxcontinue);
			data->mlxcontinue = NULL;
		}
		mlx_destroy_display(data->mlxstart);
		free(data->mlxstart);
		data->mlxstart = NULL;
	}
}

int	game_exit(t_game *data)
{
	free_map(data);
	free_mlx(data);
	exit(0);
}
