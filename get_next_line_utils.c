/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:35:10 by user42            #+#    #+#             */
/*   Updated: 2020/11/23 18:08:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** LIBFT UTILS
*/
size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	if (!c)
		return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	if (!size)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t dstlen;
	size_t srclen;

	i = 0;
	j = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size <= dstlen)
		return (size + srclen);
	while (dst[i])
		i++;
	while (src[j] && j < size - dstlen - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = 0;
	return (dstlen + srclen);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	size;

	size = sizeof(*dup) * (ft_strlen(s) + 1);
	dup = malloc(size);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, size);
	return (dup);
}

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

/*
** GET_NEXT_LINE_UTILS
*/

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
			freeptr = NULL;
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
	len = ft_strchr(*linebuf, '\n') - *linebuf + 1;
	line = ft_substr(*linebuf, 0, len);
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
