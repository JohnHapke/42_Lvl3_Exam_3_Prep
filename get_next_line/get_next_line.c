/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:53:06 by jhapke            #+#    #+#             */
/*   Updated: 2025/05/05 11:38:33 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_strlen(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char	*str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

void	ft_strcpy(char *s1, char *s2)
{
	while (*s2)
		*s1++ = *s2++;
	*s1 = '\0';
}

char	*ft_strdup(char *src)
{
	char	*dst;

	dst = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strcpy(dst, src);
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2)+ 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcpy((str + ft_strlen(s1)), s2);
	free(s1);
	return (str);

}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*new_line;
	int			bytes;
	int			to_copy;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = ft_strdup(buffer);
	while (!(new_line = ft_strchr(line, '\n'))
		&& (bytes = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[bytes] = '\0';
		line = ft_strjoin(line, buffer);
	}
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	if (new_line != NULL)
	{
		to_copy = new_line - line + 1;
		ft_strcpy(buffer, new_line + 1);
	}
	else
	{
		to_copy = ft_strlen(line);
		buffer[0] = '\0';	
	}
	line[to_copy] = '\0';
	return (line);
}


