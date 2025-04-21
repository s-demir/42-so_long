/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedemir <sedemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:07:48 by sedemir           #+#    #+#             */
/*   Updated: 2025/03/28 12:12:26 by sedemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct s_game
{
	char	**map;

	int		width;
	int		height;
	int		collectables;
	int		exit;
	int		player;
	int		player_x;
	int		player_y;
	int		counter;

	void	*mlxstart;
	void	*mlxcontinue;
	void	*player_img;
	void	*coin_img;
	void	*exit_img;
	void	*wall_img;
}	t_game;

void	error_msg(char *str, int check, void *data);
void	map_size(t_game *game, char *map);
void	map_read(t_game *game, char *map);
void	around_by_wall(t_game *game);
void	game_texture(t_game *game);
void	add_graphics(t_game *game);
void	map_count_item(t_game *game);
void	map_is_correct(t_game *game, int y, int x);

int		game_exit(t_game *data);
int		map_tracking(int key, t_game *game);

#endif
