#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


char *get_line(char *str)
{
	char	*buffer;
	size_t	i;

	i = 0;
	if (!str[i])
		return ('\0');
	while (str[i] && str[i] != '\n')
		i++;
	buffer = (char *)malloc((i + 2) * sizeof(char));
	if (!buffer)
		return ('\0');
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		buffer[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		buffer[i] = '\n';
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char *data_not_use(char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (buffer[i] != '\n')
	{
		if (!buffer[i])
		{
			free(buffer);
			return ('\0');
		}
		i++;
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!str)
		return ('\0');
	i++;
	j = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(buffer);
	return (str);	
}

char *data_in_line(int fd, char *str)
{
	char	*buffer;
	int	num_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return ('\0');
	num_read = 1;
	while (!ft_strchr(str, '\n') && num_read != 0)
	{
		num_read = read(fd, buffer, BUFFER_SIZE);
		if (num_read < 0)
		{
			free (buffer);
			return ('\0');
		}
		buffer[num_read] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free (buffer);
	return (str);
}

char *get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return ('\0');
	str = data_in_line(fd, str);
	if (!str)
		return ('\0');
	line = get_line(str);
	str = data_not_use(str);
	return (line);
}

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("test.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}
