/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:45:49 by flee              #+#    #+#             */
/*   Updated: 2022/05/23 14:45:51 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void    player_dir2(t_game *game , char dir)
{
    if (dir == 'W')
    {
        game->player.dirX = 0;
        game->player.dirY = -1;
        game->player.planeX = -0.66;
        game->player.planeY = 0;
    }
    if (dir == 'E')
    {
        game->player.dirX = 0;
        game->player.dirY = 1;
        game->player.planeX = 0.66;
        game->player.planeY = 0;
    }
}

void    player_dir(t_game *game, char dir)
{
    if (dir == 'N')
    {
        game->player.dirX = -1;
        game->player.dirY = 0;
        game->player.planeX = 0;
        game->player.planeY = 0.66;
    }
    if (dir == 'S')
    {
        game->player.dirX = 1;
        game->player.dirY = 0;
        game->player.planeX = 0;
        game->player.planeY = -0.66;
    }
    player_dir2(game, dir);
}

bool    check_character(t_game *game, int x, int y, char c)
{
    static int count;

    if (c == 'N' || c == 'S' || c == 'E' ||  c == 'W')
    {
        count++;
        if (count > 1)
        {
            game->player.posX = -1;
            return (0);
        }
        game->player.posX = x + 0.5;
        game->player.posY = y + 0.5;
        player_dir(game, game->map.map[x][y]);
    }
    return (1);
}

bool    check_element(char c)
{
    if (c != ' ' && c != '0' && c != '1' && c != 'N' && 
                c != 'S' && c != 'E' &&  c != 'W')
        return (0);
    return (1);
}    

bool    parse_element(t_game *game)
{
    int x;
    int y;

    x = 0;
    while (game->map.map[x])
    {
        y = 0;
        while (game->map.map[x][y])
        {
            if (!check_element(game->map.map[x][y]))
                return (0);
            if (!check_character(game, x, y, game->map.map[x][y]))
                return (0);
            y++;
        }
        x++;
    }
    return (1);
}

