/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedemir <sedemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:00:25 by sedemir           #+#    #+#             */
/*   Updated: 2025/03/28 12:15:04 by sedemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include "../libs/Libft/libft.h"
#include "../libs/GetNextLine/get_next_line.h"

void	map_size(t_game *game, char *map)
{
	char	*line;
	int		fd;
	int		flag;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		error_msg("Map file error!", 0, game);
	flag = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (flag == 1)
			game->width = ft_strlen(line) - 1;
		game->height++;
		free(line);
		line = get_next_line(fd);
		if (flag == 1)
			flag = 0;
	}
	if (game->height == 0)
	{
		close (fd);
		error_msg("Map file is empty!", 0, game);
	}
	close (fd);
}

static void	map_line_control(char *line, t_game *data)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'P'
			&& line[i] != 'E' && line[i] != 'C')
		{
			free(line);
			error_msg("Invalid characters in map!", 0, data);
		}
		i++;
	}
	if (i != data->width)
	{
		free(line);
		error_msg("Map lines are not of equal length!", 0, data);
	}
	line = NULL;
}

static void	map_init(t_game *game)
{
	int	i;

	game->map = malloc(sizeof(char *) * game->height);
	if (!(game->map))
		error_msg("Memory allocation failed!", 0, game);
	i = 0;
	while (i < game->height)
	{
		game->map[i] = NULL;
		i++;
	}
}

void	map_read(t_game *game, char *map)
{
	int		fd;
	int		i;
	char	*line;

	map_init(game);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		error_msg("Failed to open mapfile!", 0, game);
	i = -1;
	while (++i < game->height)
	{
		line = get_next_line(fd);
		if (!line)
			error_msg("Failed to read line from mapfile!", 0, game);
		map_line_control(line, game);
		game->map[i] = ft_strdup(line);
		if (!(game->map[i]))
		{
			free(line);
			error_msg("Memory allocation failed!", 0, game);
		}
		free(line);
	}
	close (fd);
}

void	around_by_wall(t_game *game)
{
	int	i;
	int	w;
	int	h;

	i = 0;
	w = game->width -1;
	h = game->height -1;
	while (i <= h)
	{
		if (game->map[i][0] != '1' || game->map[i][w] != '1')
			error_msg("Invalid map: walls not properly set!", 0, game);
		i++;
	}
	i = 0;
	while (i <= w)
	{
		if (game->map[0][i] != '1' || game->map[h][i] != '1')
			error_msg("Invalid map: walls not properly set!", 0, game);
		i++;
	}
}
