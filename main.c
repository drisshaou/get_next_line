#include "./get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>

int	main(int argc, char const *argv[])
{
	if (argc > 3)
		return (0);
	int		fd;
	int		i;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	/* test invalid file descriptor, stdin*/
	if (argc == 3)
	{
		fd = atoi(argv[2]);
		printf("fd: %d\n", fd);
	}
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
		i++;
		/* test if still reachable (memory)*/
		if (i == 2)
			break ;
	}
	close(fd);
	return (1);
}