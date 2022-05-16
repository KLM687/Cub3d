/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:28:37 by flee              #+#    #+#             */
/*   Updated: 2022/05/16 09:28:40 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	raycasting(t_game *game)
{
	double w = 1920;
		for(int x = 0; x < w; x++)
    	{
      		double cameraX = 2 * x / w - 1;
      		double rayDirX = game->player.dirX + game->player.planeX * cameraX;
      		double rayDirY = game->player.dirY + game->player.planeY * cameraX;

			int mapX = (int)game->player.posX;
      		int mapY = (int)game->player.posY;
			
			double sideDistX;
      		double sideDistY;

      		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
      		double perpWallDist;

      		int stepX;
      		int stepY;
			int hit = 0;
      		int side; 

     		if (rayDirX < 0)
      		{
        		stepX = -1;
        		sideDistX = (game->player.posX - mapX) * deltaDistX;
      		}
      		else
      		{
      			stepX = 1;
    			sideDistX = (mapX + 1.0 - game->player.posX) * deltaDistX;
     		}
      		if (rayDirY < 0)
      		{
       			stepY = -1;
        		sideDistY = (game->player.posY - mapY) * deltaDistY;
      		}
      		else
      		{
        		stepY = 1;
        		sideDistY = (mapY + 1.0 - game->player.posY) * deltaDistY;
    		}
			while (hit == 0)
      		{
        		if (sideDistX < sideDistY)
        		{
        		  sideDistX += deltaDistX;
        		  mapX += stepX;
        		  side = 0;
        		}
        		else
        		{
        		  sideDistY += deltaDistY;
        		  mapY += stepY;
        		  side = 1;
        		}
        		if (game->map.map[mapX][mapY] == '1')
					hit = 1;
			}
			if(side == 0) 
				perpWallDist = (sideDistX - deltaDistX);
   	   		else        
			  	perpWallDist = (sideDistY - deltaDistY);

			int h = 1280;

			int lineHeight = (int)(h / perpWallDist);

    		int drawStart = -lineHeight / 2 + h / 2;
      		if(drawStart < 0)
			  	drawStart = 0;
      		int drawEnd = lineHeight / 2 + h / 2;
      		if (drawEnd >= h || drawEnd < 0)
			  	drawEnd = h;
			if(side == 1)
				verline(x, drawStart, drawEnd, side, game);
			else
				verline(x , drawStart, drawEnd, side, game);
		}
		printf("%f %f\n",game->player.posX, game->player.posY);
		mlx_put_image_to_window(game->mlx.mlx, game->mlx.windows, game->windows.img , 0, 0);
}