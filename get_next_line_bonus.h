/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <denis.c1@live.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 05:55:46 by dchheang          #+#    #+#             */
/*   Updated: 2020/12/03 06:58:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

typedef struct       s_list
{
    int              fd;
    char            *linebuf;
    struct s_list   *next;
}                    t_list;

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);

char	*ft_strcat_alloc(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		read_line(int fd, char **linebuf);
char	*trim_line(char **linebuf);

int		get_next_line(int fd, char **line);

#endif
