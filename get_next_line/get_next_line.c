/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhankiskac <batuhankiskac@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:17:40 by batuhankisk       #+#    #+#             */
/*   Updated: 2024/11/21 15:29:53 by batuhankisk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char ft_extract_line(char *buf_static)
{
	char *newline_pos;
	char *new_buf_static;
	char *line;

	newline_pos = ft_strchr(buf_static, '\n');
	if(!newline_pos)
	{
		line = ft_substr(buf_static, 0, newline_pos - buf_static + 1);
	}
	return (line);
}

char *get_next_line(int fd)
{
	char *buf;
	static char *buf_static;
	ssize_t bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		buf_static = ft_strjoin(buf_static, buf);
		if(!buf_static)
		{
			free(buf_static);
			return (NULL);
		}
	}
	free(buf);
	return (NULL);
}
