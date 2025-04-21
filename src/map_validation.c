/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedemir <sedemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:15:09 by sedemir           #+#    #+#             */
/*   Updated: 2025/03/28 12:14:13 by sedemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include "../libs/GetNextLine/get_next_line.h"

static char	**create_new_map(t_game *game)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (game->height));
	if (!new_map)
		error_msg("Memory allocation failed!", 0, game);
	i = 0;
	while (i < game->height)
	{
		new_map[i] = ft_strdup(game->map[i]);
		if (new_map[i] == NULL)
		{
			i = 0;
			while (i < game->height)
				free(new_map[i++]);
			free(new_map);
			error_msg("Memory allocation failed!", 0, game);
		}
		i++;
	}
	return (new_map);
}

static void	map_flood_fill(char **new_map, int *count, int y, int x)
{
	if (new_map[y][x] == '1')
		return ;
	if (new_map[y][x] == 'C' || new_map[y][x] == 'E')
		(*count)++;
	if (new_map[y][x] == 'E')
	{
		new_map[y][x] = '1';
		return ;
	}
	new_map[y][x] = '1';
	map_flood_fill(new_map, count, y + 1, x);
	map_flood_fill(new_map, count, y - 1, x);
	map_flood_fill(new_map, count, y, x + 1);
	map_flood_fill(new_map, count, y, x - 1);
}

void	map_is_correct(t_game *game, int y, int x)
{
	char	**new_map;
	int		count;
	int		i;

	count = 0;
	new_map = create_new_map(game);
	map_flood_fill(new_map, &count, y, x);
	if (count != game->collectables + 1)
	{
		i = 0;
		while (i < game->height)
			free(new_map[i++]);
		free(new_map);
		error_msg("Not all collectables are accessible!", 0, game);
	}
	i = 0;
	while (i < game->height)
		free(new_map[i++]);
	free(new_map);
}

void	map_count_item(t_game *game)
{
	char	location;
	int		index;
	int		x;
	int		y;

	index = 0;
	while (index < game->height * game->width)
	{
		y = index / game->width;
		x = index % game->width;
		location = game->map[y][x];
		if (location == 'E')
			game->exit++;
		else if (location == 'P')
			game->player++;
		else if (location == 'C')
			game->collectables++;
		else if (location != '1' && location != '0' && location != '\n')
			error_msg("Invalid map character!", 0, game);
		index++;
	}
	if (game->player != 1 || game->exit != 1 || game->collectables == 0)
		error_msg("Wrong equipment in map!", 0, game);
}
