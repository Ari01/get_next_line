/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:34:58 by user42            #+#    #+#             */
/*   Updated: 2020/11/23 18:24:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	*linebuf;
	int			read_value;

	read_value = 1;
	if (!line)
		return (-1);
	if (!linebuf || !*linebuf)
		read_value = read_line(fd, &linebuf);
	if (read_value < 0)
		return (-1);
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	*line = get_line(&linebuf);
	if (!*line)
	{
		free(linebuf);
		return (-1);
	}
	return (read_value);
}

int main()
{
	char *line = NULL;
	get_next_line(STDIN_FILENO, &line);

	return (0);
}
