/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhankiskac <batuhankiskac@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:39:15 by batuhankisk       #+#    #+#             */
/*   Updated: 2024/12/02 18:31:41 by batuhankisk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*parse(char *line, char c)
{
	char	*left;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (left[i] && left[i] != c)
		i++;
	if (!left[i])
	{
		free(line);
		return (NULL);
	}
	
}

static char	*new_line(char *line, char c)
{

}

static char	*next_line(int fd, char *line, char c)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(buffer, c) && i != '\0')
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*line[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = next_line(fd, line[fd], '\n');
	if (line[fd])
	{
		str = new_line(line[fd], '\n');
		line[fd] = parse(line[fd], '\n');
		return (str);
	}
	return (NULL);
}
