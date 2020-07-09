/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgomez-r <bgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 09:51:32 by bgomez-r          #+#    #+#             */
/*   Updated: 2020/02/11 09:51:43 by bgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
	int i = 1;
	fd = open("test.txt", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		printf("%d", i);
		printf("%s\n", line);
		free(line);
		line = NULL;
		i++;
	}
	system("leaks a.out");
	return (0);
}
