/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:41:24 by flee              #+#    #+#             */
/*   Updated: 2022/05/16 14:41:26 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

bool    check_side(t_game *game)
{
    int x;
    int y;

    x = 0;
    while (game->map.map[0][x])
    {
        if (game->map.map[0][x] != ' ' && game->map.map[0][x] != '1')
            return (0);
        x++;
    }
    while(game->00)
    
}

void    parse_wall(t_game *game)
{
    if (!check_side(game));
}


