#include "get_next_line_bonus.h"

char	*checkostatok(char **line, char **ostatok, int fd)
{
	char	*reminder;

	reminder = NULL;
	if (ostatok[fd])
	{
		reminder = ft_strchr(ostatok[fd], '\n');
		if (reminder)
		{
			*reminder = '\0';
			*line = ft_strdup(ostatok[fd]);
			ft_strcpy(ostatok[fd], ++reminder);
		}
		else
		{
			*line = ft_strdup(ostatok[fd]);
			free(ostatok[fd]);
			ostatok[fd] = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (reminder);
}

int	proverka(int fd, char **line, char *buf)
{
	int			i;
	char		*simv_kontsa_stroki;
	static char	*ostatok[256];

	i = 1;
	simv_kontsa_stroki = checkostatok(line, ostatok, fd);
	while (!simv_kontsa_stroki && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		buf[i] = '\0';
		simv_kontsa_stroki = ft_strchr(buf, '\n');
		if (simv_kontsa_stroki)
		{
			*simv_kontsa_stroki = '\0';
			ostatok[fd] = ft_strdup(++simv_kontsa_stroki);
		}
		*line = ft_strjoin(*line, buf);
	}
	free(buf);
	return (i && ostatok[fd]);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;

	if (read(fd, NULL, 0) < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	return (proverka(fd, line, buf));
}
