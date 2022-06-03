/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:06:09 by flee              #+#    #+#             */
/*   Updated: 2022/05/04 11:06:26 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

# define windows_x 	1920
# define windows_y 	1280
# define tex_size	64

typedef struct s_ray
{
	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
    double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	double step;
	int stepX;
    int stepY;
	int hit;
	int lineHeight;
	int drawStart;
	int drawEnd;
	double wallX;
	int texX;
	int texY;
	double texPos;
	int	side;
}	t_ray;

typedef struct s_map
{
	char **map;
	int  grid_size;
}	t_map;

typedef struct s_texture
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	int floor[3];
	int f_rgb;
	int sky[3];
	int s_rgb;
}	t_texture;

typedef struct s_player
{
	float posX;
	float posY;
	double	dirX;
	double	dirY;
	double pa;
	float planeX;
	float planeY;
	int mapX;
	int mapY;
}	t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*windows;
	size_t	w_x;
	size_t	w_y;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		byte_p;
	int		line_l;
	int		end;
}	t_img;

typedef struct s_game
{
	t_mlx		mlx;
	t_map		map;
	t_texture	texture;
	t_player	player;
	t_img		windows;
	t_img		NO;
	t_img		SO;
	t_img		WE;
	t_img		EA;
	t_ray		ray;
}	t_game;

void			get_file(char *map, t_game *game);
void 			parse_map(t_game *game);
void			square_map(t_game *game);
void			game_loop(t_game *game);
void			open_img(t_game *game);
void			raycasting(t_game *game);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
unsigned int	img_pix_get(t_img *img, int x, int y);
int				create_rgb(int r, int g, int b);
int 			input(int key, t_game *game);
void    		parse_wall(t_game *game);
bool			parse_element(t_game *game);
bool			check_move(t_game *game);
void			verline(t_game *game, int x, int sky);
void			ray_draw(t_game *game);
void			ray_hit(t_game *game);
void			ray_sideDist(t_game *game);
void			ray_init(t_game *game, int x);
int				free_and_destroy(t_game *game);
void			free_parse(t_game *game);
char			*whitespace(char *str);
bool			str_is_digit(char **str);
bool			line_is_empty(char *str);
bool			check_info(t_game *game);
bool			check_void(t_game *game);
void			clean_img(t_game *game);

#endif
