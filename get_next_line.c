/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:03:07 by kangkim           #+#    #+#             */
/*   Updated: 2021/11/25 17:18:47 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	char	*buf;
	ssize_t	size;
	char	*ret;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (NULL);
	size = read(fd, buf, BUFFER_SIZE);
	if (size == -1)
		return (NULL);
	ret = buf;
	free(buf);
	buf = NULL;
	return (ret);
}

int	main(void)
{
	char	*ret;
	int		fd;

	fd = open("text", O_RDONLY);
	ret = get_next_line(fd);
	printf("------------------------------------\n");
	printf("Result\n%s\n", ret);
	while (*ret)
		printf("%d ", *ret++);
	/*
	system("leaks a.out");
	*/
	return (0);
}
