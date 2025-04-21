/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedemir <sedemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:36:26 by sedemir           #+#    #+#             */
/*   Updated: 2025/03/28 12:19:56 by sedemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stddef.h>
#include "../libs/minilibx-linux/mlx.h"
#include "../libs/Libft/libft.h"
#include "../libs/Ft_Printf/ft_printf.h"

static void	game_start(t_game *game)
{
	game->width = 0;
	game->height = 0;
	game->collectables = 0;
	game->exit = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->player = 0;
	game->counter = 0;
	game->map = NULL;
	game->player_img = NULL;
	game->coin_img = NULL;
	game->exit_img = NULL;
	game->wall_img = NULL;
	game->mlxstart = NULL;
	game->mlxcontinue = NULL;
}

static void	game_func(t_game *game, char *map)
{
	game_start(game);
	map_size(game, map);
	map_read(game, map);
	around_by_wall(game);
	game->mlxstart = mlx_init();
	if (!game->mlxstart)
		error_msg("MLX initialization failed", 0, game);
	game->mlxcontinue = mlx_new_window(game->mlxstart, game->width * 64,
			game->height * 64, "so_long");
	if (!game->mlxcontinue)
		error_msg("MLX initialization failed", 0, game);
	game_texture(game);
	map_count_item(game);
	add_graphics(game);
	map_is_correct(game, game->player_y, game->player_x);
}

int	main(int ac, char **av)
{
	t_game	game;
	int		ext_len;

	if (ac == 2)
	{
		ext_len = ft_strlen(av[1]);
		if ((av[1][ext_len - 1] != 'r') || !(av[1][ext_len - 2] == 'e')
			|| !(av[1][ext_len - 3] == 'b') || !(av[1][ext_len - 4] == '.')
			|| !(ft_isprint(av[1][ext_len - 5])) || (ext_len == 9))
			return (ft_printf("The file extension is incorrect\n"), 1);
		game_func(&game, av[1]);
		mlx_key_hook(game.mlxcontinue, &map_tracking, &game);
		mlx_hook(game.mlxcontinue, 17, 0, (void *) &game_exit, &game);
		mlx_loop(game.mlxstart);
	}
	else
		ft_printf("Wrong argument!\n");
}
