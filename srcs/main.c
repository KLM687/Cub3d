/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:08:08 by flee              #+#    #+#             */
/*   Updated: 2021/07/20 16:17:39 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int main (int argc, char **argv)
{
	int fd;
	char **line;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	/*int i = 0;
	while (line[i])
	{
		printf("%s\n",line[i]);
		i++;
	}
	ft_free_tab(line);*/
	return (0);
	
}
