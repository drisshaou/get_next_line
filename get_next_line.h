/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:05:38 by drhaouha          #+#    #+#             */
/*   Updated: 2024/05/30 17:49:24 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

char	*get_next_line(int fd);
int		read_file(char **line, char *cat, int fd);
char	*update_buffer(char *buf, char **trunc, char *cat);
char	*get_trunc(unsigned int size, char *cat, int fd, int *ret);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);

#endif
