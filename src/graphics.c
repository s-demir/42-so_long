/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedemir <sedemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:11:27 by sedemir           #+#    #+#             */
/*   Updated: 2025/03/28 12:12:54 by sedemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stddef.h>
#include "../libs/minilibx-linux/mlx.h"

static void	*textures_image(t_game *game, char *path)
{
	int		x;
	int		y;
	void	*image;

	image = mlx_xpm_file_to_image(game->mlxstart, path, &x, &y);
	if (!image)
		error_msg("Image failed", 0, game);
	return (image);
}

void	game_texture(t_game *game)
{
	game->coin_img = textures_image(game, "./textures/coin.xpm");
	game->wall_img = textures_image(game, "./textures/wall.xpm");
	game->player_img = textures_image(game, "./textures/player.xpm");
	game->exit_img = textures_image(game, "./textures/exit.xpm");
}

static void	render_image(t_game *game, char location, int x, int y)
{
	void	*img;

	img = NULL;
	if (location == '1')
		img = game->wall_img;
	else if (location == 'C')
		img = game->coin_img;
	else if (location == 'P')
	{
		game->player_x = x;
		game->player_y = y;
		img = game->player_img;
	}
	else if (location == 'E')
		img = game->exit_img;
	if (img)
		mlx_put_image_to_window(game->mlxstart, game->mlxcontinue,
			img, x * 64, y * 64);
}

void	add_graphics(t_game *game)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	mlx_clear_window(game->mlxstart, game->mlxcontinue);
	while (i < game->height * game->width)
	{
		y = i / game->width;
		x = i % game->width;
		render_image(game, game->map[y][x], x, y);
		i++;
	}
}
