En este caso, para hacerlo mas sencillo, le estamos metiendo el archivo directamente dentro del main para no tener que estar pasándoselo por parámetro cuando ejecutemos el a.out en la terminal. pero si nos pidieran el archivo de fuera seria asi

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int i = 1;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line))
	{
		printf("%d", i);
		printf("%s\n", line);
		free(line);
		line = NULL;
		i++;
	}
	system("leaks a.out");
	return (0);
}
