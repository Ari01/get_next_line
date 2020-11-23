/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:34:58 by user42            #+#    #+#             */
/*   Updated: 2020/11/23 19:04:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcat_alloc(char const *s1, char const *s2)
{
	char	*cat;
	size_t	size;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	size = len1 + len2 + 1;
	cat = malloc(sizeof(*cat) * (size));
	if (!cat)
		return (NULL);
	ft_strlcpy(cat, s1, len1 + 1);
	if (ft_strlcat(cat, s2, size) != len1 + len2)
		return (NULL);
	return (cat);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	sub = malloc(sizeof(*sub) * (len + 1));
	if (!sub || !s)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (i < len && s[start])
		{
			sub[i] = s[start];
			start++;
			i++;
		}
	}
	sub[i] = 0;
	return (sub);
}

int		read_line(int fd, char **linebuf)
{
	char	buf[BUFFER_SIZE];
	char	*freeptr;
	int		read_value;

	read_value = read(fd, buf, BUFFER_SIZE);
	while (read_value > 0)
	{
		buf[read_value] = 0;
		if (*linebuf)
		{
			freeptr = *linebuf;
			*linebuf = ft_strcat_alloc(*linebuf, buf);
			free(freeptr);
		}
		else
			*linebuf = ft_strdup(buf);
		if (!*linebuf)
			return (-1);
		if (ft_strchr(*linebuf, '\n'))
			return (1);
		read_value = read(fd, buf, BUFFER_SIZE);
	}
	if (read_value < 0)
		return (-1);
	return (0);
}

char	*get_line(char **linebuf)
{
	char	*freeptr;
	char	*line;
	size_t	len;

	freeptr = *linebuf;
	len = ft_strchr(*linebuf, '\n') - *linebuf;
	line = ft_substr(*linebuf, 0, len);
	len++;
	if (!line)
		return (NULL);
	*linebuf = ft_substr(*linebuf, len, ft_strlen(*linebuf) - len);
	if (!*linebuf)
	{
		free(freeptr);
		free(line);
		return (NULL);
	}
	free(freeptr);
	return (line);
}

int		get_next_line(int fd, char **line)
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
/*
#include <fcntl.h>
#include <stdio.h>
int		main()
{
	char *line = NULL;
	int fd = open("test_file", O_RDONLY);
	int read_value;

	while ((read_value = get_next_line(fd, &line) > 0))
		printf("%s\n", line);
	close(fd);

	return (0);
}*/
