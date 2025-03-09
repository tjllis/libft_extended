/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:21:50 by tsemenov          #+#    #+#             */
/*   Updated: 2025/01/03 16:21:52 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_line(int fd, char *buffer, char *line);
char	*update_str(char *line);

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*left_str[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = read_to_line(fd, buffer, left_str[fd]);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	left_str[fd] = update_str(line);
	return (line);
}

char	*read_to_line(int fd, char *buffer, char *left_str)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!left_str)
			left_str = ft_strdup("");
		temp = left_str;
		left_str = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_str);
}

char	*update_str(char *line)
{
	unsigned int	i;
	size_t			len;
	char			*new_str;

	i = 0;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	len = ft_strlen(line) - i;
	new_str = ft_substr(line, i + 1, len);
	if (new_str[0] == '\0')
	{
		free(new_str);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (new_str);
}
