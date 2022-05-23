/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:54:15 by flee              #+#    #+#             */
/*   Updated: 2022/05/07 16:54:18 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	get_player(t_game *game)
{
	int z;
	int s;
	
	z = 0;
	while(game->map.map[z])
	{
		s = 0;
		while(game->map.map[z][s]) 
		{
			if (game->map.map[z][s] == 'P')
			{
				game->player.posX = z;
				game->player.posY = s;
			}
			s++;
		}
		z++;
	}
	game->player.planeX = 0;
	game->player.planeY = 0.66;
}

int render_next_frame(t_game *game)
{
	raycasting(game);
	return (1);
}

int 	color_get(t_img *img, int x, int y)
{
	int rep = (x * img->line_l) / 4 + y;
	int ret;
	ret = create_rgb(img->addr[rep], img->addr[rep + 1], img->addr[rep + 2]);
	return (ret);
}

void	game_loop(t_game *game)
{
	game->mlx.mlx = mlx_init();
	game->mlx.windows = mlx_new_window(game->mlx.mlx,
			windows_x, windows_y, "CUB3333333333D");
 
	/*get_player(game);
	game->player.dirX = -1;
	game->player.dirY = 0;
	game->player.pa = 0;*/
 	
	printf("%f %f\n", game->player.posX, game->player.posY);
	printf("dirX = %f dirY = %f\n", game->player.dirX, game->player.dirY);
	game->player.pa = 0;
	
	open_img(game);

	mlx_loop_hook(game->mlx.mlx, &render_next_frame , game);
	mlx_hook(game->mlx.windows, 2, 1L<<0 , input, game);
	mlx_hook(game->mlx.windows, 33, 1l << 5,0 , game);
	mlx_loop(game->mlx.mlx);
}