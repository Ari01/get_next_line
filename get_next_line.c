/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:34:58 by user42            #+#    #+#             */
/*   Updated: 2020/11/22 17:48:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	get_next_line(int fd, char **line)
{
	char buff[BUFFER_SIZE + 1];
	int readvalue;
	(void)line;

	readvalue = read(fd, buff, BUFFER_SIZE);
	if (readvalue >= 0 && readvalue <= BUFFER_SIZE)
		buff[readvalue] = 0;
	write(STDOUT_FILENO, buff, ft_strlen(buff));
	return (1);
}

int main()
{
	char *line = malloc(sizeof(*line) * 100);
	get_next_line(STDIN_FILENO, &line);

	return (0);
}
