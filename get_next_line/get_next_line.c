/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhankiskac <batuhankiskac@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:40:22 by batuhankisk       #+#    #+#             */
/*   Updated: 2024/12/02 16:18:21 by batuhankisk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*parse(char *line, char c)
{
	char	*left;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != c)
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	left = (char *)malloc(sizeof(char) * (ft_strlen(c) - i + 1));
	if (!left)
		return (NULL);
	i++;
	while (line[i])
		left[j++] = line[i++];
	left[j] = '\0';
	free(line);
	return (left);
}

static char	*new_line(char *line, char c)
{
	char	*new;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != c)
		new[i++] = line[i++];
	if (line[i] == c)
	{
		new[i] = c;
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	*next_line(int fd, char *line, char c)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(line, c) && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == - 1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return(line);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = next_line(fd, line, '\n');
	if (line)
	{
		str = new_line(line, '\n');
		line = parse(line, '\n');
		return (str);
	}
	return (NULL);
}
