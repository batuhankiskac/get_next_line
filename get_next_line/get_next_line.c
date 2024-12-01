/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhankiskac <batuhankiskac@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:17:40 by batuhankisk       #+#    #+#             */
/*   Updated: 2024/12/01 18:40:22 by batuhankisk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(char **buf_static)
{
	char	*new_line_pos;
	char	*temp;
	char	*line;

	if (!buf_static || !*buf_static)
		return (NULL);
	new_line_pos = ft_strchr(*buf_static, '\n');
	if (new_line_pos)
	{
		line = ft_substr(*buf_static, 0, new_line_pos - *buf_static + 1);
		temp = ft_substr(*buf_static,
				new_line_pos - *buf_static + 1,
				ft_strlen(*buf_static)
				- (new_line_pos - *buf_static + 1));
		free(*buf_static);
		*buf_static = temp;
		return (line);
	}
	line = ft_strdup(*buf_static);
	free(*buf_static);
	*buf_static = NULL;
	return (line);
}

char	*ft_allocate_buf(void)
{
	char	*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf_static;
	char		*buf;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_allocate_buf();
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		buf_static = ft_strjoin(buf_static, buf);
		if (!buf_static || ft_strchr(buf_static, '\n'))
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (bytes_read < 0 || (!buf_static && bytes_read == 0))
	{
		free(buf_static);
		buf_static = NULL;
		return (NULL);
	}
	return (ft_extract_line(&buf_static));
}
