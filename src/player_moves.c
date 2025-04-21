/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedemir <sedemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:02:17 by sedemir           #+#    #+#             */
/*   Updated: 2025/03/27 15:52:27 by sedemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../libs/Ft_Printf/ft_printf.h"

static int	player_move_control(t_game *game, int i, int j)
{
	if (game->map[i][j] == 'E')
	{
		if (game->collectables != 0)
			return (0);
		error_msg("YOU WIN!\n", 3, game);
	}
	if (game->map[i][j] == 'C')
		game->collectables--;
	game->map[game->player_y][game->player_x] = '0';
	game->map[i][j] = 'P';
	game->player_y = i;
	game->player_x = j;
	game->counter++;
	return (1);
}

static int	player_movement(t_game *game, int direction_x, int direction_y)
{
	int	new_y;
	int	new_x;

	new_y = game->player_y + direction_y;
	new_x = game->player_x + direction_x;
	if (new_x < 0 || new_y < 0 || new_x >= game->width || new_y >= game->height)
		return (0);
	if (game->map[new_y][new_x] == '1')
		return (0);
	return (player_move_control(game, new_y, new_x));
}

static int	game_key_movement(t_game *game, int movement)
{
	if (movement == KEY_W)
		return (player_movement(game, 0, -1));
	else if (movement == KEY_S)
		return (player_movement(game, 0, 1));
	else if (movement == KEY_A)
		return (player_movement(game, -1, 0));
	else if (movement == KEY_D)
		return (player_movement(game, 1, 0));
	return (0);
}

int	map_tracking(int key, t_game *game)
{
	int	result;

	result = 0;
	if (key == KEY_ESC)
		game_exit(game);
	result = game_key_movement(game, key);
	if (result)
	{
		ft_printf("Step Count: %d\n", game->counter);
		add_graphics(game);
	}
	return (1);
}
