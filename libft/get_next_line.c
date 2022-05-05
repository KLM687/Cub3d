/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 17:08:35 by flee              #+#    #+#             */
/*   Updated: 2021/07/20 17:24:58 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

int 	count_line(char *buf)
{
	int i;
	int line;

	i = 0;
	line = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			line++;
		i++;
	}
	return (line);
}

char 	**create(char *buf)
{
	int a;
	int b;
	int c;

	a = 0;
	c = 0;
	while (buf[b])
	{
		while(buf[b] != '\n' && buf[a])
			b++;
		map[c] = ft_substr(buf, a, b);
		a = 
	}
}

char	**get_next_line(int fd)
{
	char		buf[99999];
	char		**map;
	int 		read_ret;

	if (!fd)
		return (NULL);
	read_ret = read(fd,buf, 99999);
	if (read_ret == -1)
	{
		write(1, "read fail\n", 10);
		return (NULL);
	}
	map = malloc(sizeof(char *) * (count_line(buf) + 1));
	map = create(buf);
	return (map);
}