/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:05:57 by drhaouha          #+#    #+#             */
/*   Updated: 2024/05/31 12:24:54 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_buffer(char *buffer, char **stock, char *container)
{
	unsigned int	pos;

	pos = 0;
	while (buffer[pos] != '\n' && buffer[pos])
	{
		container[pos] = buffer[pos];
		pos++;
	}
	if (buffer[pos] == '\n')
		container[pos++] = '\n';
	container[pos] = '\0';
	*stock = ft_strcat(*stock, container);
	if (ft_strchr(buffer, '\n'))
		ft_strcpy(buffer, buffer + pos);
	else
		buffer[0] = '\0';
	return (*stock);
}

char	*get_stock(unsigned int size, char *container, int fd, int *ret)
{
	static char		buffer[BUFFER_SIZE + 1] = {0};
	char			*stock;
	unsigned int	i;

	stock = (char *)malloc(sizeof(char) * (BUFFER_SIZE * (size + 1) + 1));
	if (stock == NULL)
		return (NULL);
	stock[0] = '\0';
	i = 0;
	while (i < size)
	{
		if (ft_strlen(buffer) == 0)
		{
			*ret = read(fd, buffer, BUFFER_SIZE);
			if (*ret == -1)
				return (free(stock), NULL);
			buffer[*ret] = '\0';
			i++;
		}
		stock = update_buffer(buffer, &stock, container);
		if (ft_strchr(stock, '\n') || *ret == 0)
			break ;
	}
	return (stock);
}

int	read_file(char **line, char *container, int fd)
{
	char			*stock;
	char			*tmp;
	int				ret;
	unsigned int	size;

	ret = 1;
	size = 1;
	while (ret != 0)
	{
		if (ft_strchr(*line, '\n'))
			break ;
		stock = get_stock(size, container, fd, &ret);
		if (stock == NULL)
			return (-1);
		tmp = *line;
		*line = ft_strjoin(*line, stock);
		free(stock);
		free(tmp);
		if (*line == NULL || ft_strlen(*line) == 0)
			return (-1);
		size += size;
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*container;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	container = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (container == NULL)
		return (NULL);
	line = ft_strjoin("", "");
	if (!line || read_file(&line, container, fd) == -1)
		return (free(container), free(line), NULL);
	return (free(container), line);
}
