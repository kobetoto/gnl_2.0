#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 
#endif


char    *ft_strdup(char *src)
{
    int        i;
    char    *new;

    i = 0;
    while (src[i])
        i++;
    new = malloc(sizeof(char)* (i + 1));
    i = 0;
    while (src[i])
    {
        new[i] = src[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

char    *get_next_line(int fd)
{
    static char        buffer[BUFFER_SIZE];
    char            line[70000];
    static int      buffer_read = 0;
    static int      buffer_pos = 0;
    int             i;

    i = 0;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_read <= 0)
                break;
        }
        line[i] = buffer[buffer_pos++];
        if (line[i++] == '\n')
            break;
    }
    line[i] = '\0';
    if (i == 0)
        return (NULL);
    return (ft_strdup(line));
}

int	main()
{
	int	fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
		return (1);
printf("\n==fd is %i==\n",fd);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s", line);
		free(line);
	}
	return (0);
}
