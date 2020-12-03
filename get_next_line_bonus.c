/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <denis.c1@live.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 05:53:43 by dchheang          #+#    #+#             */
/*   Updated: 2020/12/03 07:18:39 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list  *ft_lstnew(int fd)
{
    t_list *new;

    new = malloc(sizeof(*new));
    new->fd = fd;
    new->linebuf = NULL;
    new->next = NULL;
    return (new);
}

void    push_front(t_list **fdlist, t_list *new)
{
	if (new)
	{
		if (*fdlist)
			new->next = *fdlist;
		*fdlist = new;
	}
}

int     is_in_list(t_list *fdlist, int fd)
{
    while (fdlist)
    {
        if (fdlist->fd == fd)
            return (1);
        fdlist = fdlist->next;
    }
    return (0);
}

char    **get_linebuf(t_list *fdlist, int fd)
{
    while (fdlist)
    {
        if (fdlist->fd == fd)
            return (&fdlist->linebuf);
        fdlist = fdlist->next;
    }
    return (NULL);
}

void    ft_lstdelone(t_list **fdlist, int fd)
{
    t_list *tmp;

    if (!(*fdlist)->next)
    {
        free((*fdlist)->linebuf);
        free(*fdlist);
        *fdlist = NULL;
    }
    else
    {
        while ((*fdlist)->next)
        {
            if ((*fdlist)->next->fd == fd)
            {
                tmp = (*fdlist)->next;
                (*fdlist)->next = (*fdlist)->next->next;
                free(tmp->linebuf);
                free(tmp);
                tmp = NULL;
                break;
            }
        }
    }
}

int		get_next_line(int fd, char **line)
{
	int			    read_value;
    static t_list   *fdlist;
    char            **linebuf;

	if (!line || BUFFER_SIZE <= 0)
		return (-1);
    if (!is_in_list(fdlist, fd))
        push_front(&fdlist, ft_lstnew(fd));
    linebuf = get_linebuf(fdlist, fd);

	if (!*linebuf)
		*linebuf = ft_strdup("");
	if (!*linebuf)
		return (-1);
	read_value = read_line(fd, linebuf);
	if (read_value < 0)
		return (-1);
	if (ft_strchr(*linebuf, '\n'))
		read_value = 1;
	*line = trim_line(linebuf);
	if (!line || !read_value)
	{
		ft_lstdelone(&fdlist, fd);
		if (!line)
			return (-1);
	}
	return (read_value);
}
