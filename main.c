/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 10:45:47 by user42            #+#    #+#             */
/*   Updated: 2021/01/03 12:08:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	int read_value;
	int	fd;
	char *line;

	fd = open("3balls.rt", O_RDONLY);
	line = NULL;
	if (!fd)
		perror(strerror(errno));
	while ((read_value = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	free(line);
	return (0);
}
