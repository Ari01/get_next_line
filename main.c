/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 06:32:36 by user42            #+#    #+#             */
/*   Updated: 2020/12/03 06:48:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd[] = {open("test1", O_RDONLY), open("test2", O_RDONLY)};
    char *line = NULL;
    int rd0;
    int rd1;

    rd0 = 1;
    rd1 = 1;
    while (rd0 > 0 && rd1 > 0)
    {
        rd0 = get_next_line(fd[0], &line);
        rd1 = get_next_line(fd[1], &line);
    }
    if (rd0 < 0 || rd1 < 0)
        printf("erreur rd\n");
    return (0);
}
