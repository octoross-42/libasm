#include "test.h"

void	test_strlen(int argc, char **argv)
{
	unsigned int len_block = 24;

	write_code("\n╔════ ft_strlen ═══════════════════════════════════════════════════════════════════════════════════╗\n║", BOLD);
	write_code("       size_t	ft_strlen(const char *s);", GREY);
	block_write("", RESET, 0, 0, 58);
	write(1, "║", 3);
	write(1, "\n║", 4);
	block_write("", RESET, 0, 0, 98);
	write(1, "║\n║       ", 14);
	block_write("char *str", BOLD, 0, 0, len_block);
	write_code("ft_strlen", BOLD);
	block_write("", RESET, 0, 0, 82 - len_block);
	write(1, "║\n║", 7);
	
	int i = 0;
	while (i < argc)
	{
		write(1, "       ", 7);
		block_write(argv[i], BLUE, 1, 1, len_block);
		
		block_write_int(ft_strlen(argv[i]), CYAN, len_block);  //	<------------- CALL HERE ------------------------------------
		
		block_write("", RESET, 0, 0, 91 - 2 * len_block);
		write(1, "║\n║", 7);
		
		// comparison with the real function
		write(1, "       ", 7);
		block_write("Real strlen  ->", IGREY, 0, 0, len_block);
		block_write_int(strlen(argv[i]), CYAN, len_block);
		
		block_write("", RESET, 0, 0, 91 - 2 * len_block);
		write(1, "║\n║", 7);

		i ++;
	}
	
	block_write("", RESET, 0, 0, 98);
	write(1, "\n", 1);
}

void	test_strcpy(int argc, char **argv)
{
	// invalid read sur le strlen si src > dest -> normal
	unsigned int len_block = 24;

	write_code("\n╔════ ft_strcpy ═══════════════════════════════════════════════════════════════════════════════════╗\n║", BOLD);
	write_code("       char	*ft_strcpy(char *restrict dst, const char *restrict src);", GREY);
	block_write("", RESET, 0, 0, 26);
	write(1, "║", 3);
	write(1, "\n║", 4);
	block_write("", RESET, 0, 0, 98);
	write(1, "║\n║       ", 14);
	block_write("unsigned char *dest", BOLD, 0, 0, len_block);
	block_write("unsigned char *src", BOLD, 0, 0, len_block);
	write_code("ft_strcpy", BOLD);
	block_write("", RESET, 0, 0, 82 - len_block * 2);
	write(1, "║\n║", 7);

	int i = 1;
	char *res;
	char *dest;
	char *src;
	while (i + 1 < argc)
	{
		write(1, "       ", 7);
		dest = strdup(argv[i]);
		if (!dest)
		{
			write_code("malloc failed\n", RED);
			return ;
		}
		src = strdup(argv[i + 1]);
		if (!src)
		{
			free(dest);
			write_code("malloc failed\n", RED);
			return ;
		}
		block_write(dest, BLUE, 1, 1, len_block);
		block_write(src, BLUE, 1, 1, len_block);

		res = ft_strcpy(dest, src);	//				<----------------------------------------- CALL HERE ------------------------
		
		free(src);
		block_write(res, CYAN, 1, 1, len_block);
		free(dest);

		block_write("", RESET, 0, 0, 91 - len_block * 3);
		write(1, "║\n║", 7);
		i ++;
	}
	
	block_write("", RESET, 0, 0, 98);
	write(1, "\n", 1);
}

void	test_strcmp(int argc, char **argv)
{
	unsigned int len_block = 24;

	write_code("\n╔════ ft_strcmp ═══════════════════════════════════════════════════════════════════════════════════╗\n║", BOLD);
	write_code("       int		ft_strcmp(const char *s1, const char *s2);", GREY);
	block_write("", RESET, 0, 0, 33);
	write(1, "║", 3);
	write(1, "\n║", 4);
	block_write("", RESET, 0, 0, 98);
	write(1, "║\n║       ", 14);
	block_write("unsigned char *dest", BOLD, 0, 0, len_block);
	block_write("unsigned char *src", BOLD, 0, 0, len_block);
	write_code("ft_strcmp", BOLD);
	block_write("", RESET, 0, 0, 82 - len_block * 2);
	write(1, "║\n║", 7);
	
	int i = 0;
	while (i + 1 < argc)
	{
		write(1, "       ", 7);
		block_write(argv[i], BLUE, 1, 1, len_block);
		block_write(argv[i + 1], BLUE, 1, 1, len_block);

		block_write_int(ft_strcmp(argv[i], argv[i + 1]), CYAN, len_block); //	<------------- CALL HERE ------------------------
		
		block_write("", RESET, 0, 0, 91 - len_block * 3);
		write(1, "║\n║", 7);

		// comparison with the real function
		write(1, "       ", 7);
		block_write("Real strcmp  ->", IGREY, 0, 0, 2 * len_block);
		block_write_int(strcmp(argv[i], argv[i + 1]), CYAN, len_block);
		block_write("", RESET, 0, 0, 91 - len_block * 3);
		write(1, "║\n║", 7);
		i ++;
	}
	
	block_write("", RESET, 0, 0, 98);
	write(1, "\n", 1);
}

int	get_arg_fd(char *arg)
{
	size_t i;
	int fd;
	
	fd = atoi(arg);
	if (fd < 0)
		return (open(arg, O_RDONLY, 0));
	else if (fd == 0)
	{
		while (*arg && (*arg == '0'))
			arg ++;
		if (*arg == 0)
			return (0);
		return (open(arg, O_RDONLY, 0));
	}
	return (fd);
}

void	function_write_test(int fd, char **argv, int mine, int terminal, int len_block)
{
	int n;
	int err;
	char buf[4096];

	buf[0] = 0;
	if (terminal)
		write(1, " '", 2);
	else
		block_write("(no write here)", ITALIC, 0, 0, len_block);
	write(1, YELLOW, strlen(YELLOW));

	if (mine)
		n = ft_write(fd, buf, (size_t)atoi(argv[2]));  //	<----------------------------- CALL HERE ------------------------
	else
		n = write(fd, buf, (size_t)atoi(argv[2]));
	err = errno;
	
	if(n >= 0)
		buf[n] = 0;
	else
		buf[0] = 0; 
	write(1, RESET, strlen(RESET));
	if (terminal)
	{
		write(1, "'", 1);
		if (n >= 0)
			block_write("", RESET, 0, 0, len_block - n - 3);
		else
			block_write("", RESET, 0, 0, len_block - 3);
	}
	block_write_int(n, CYAN, 12);
	block_write_int(err, BOLD, 9);
	block_write(buf, BOLD, 1, 1, len_block);

	// block_write("", RESET, 0, 0, 44 - 2 * len_block);
	write(1, "\n║", 4);
}

void	test_write(int argc, char **argv)
{
	int len_block = 16;
	write_code("\n╔════ ft_write ════════════════════════════════════════════════════════════════════════════════════╗\n║", BOLD);
	write_code("       int		ft_write(int fd, const void *buf, size_t count);", GREY);
	block_write("", RESET, 0, 0, 27);
	write(1, "║", 3);
	write(1, "\n║", 4);
	block_write("", RESET, 0, 0, 98);
	write(1, "║\n║       ", 14);
	block_write("int fd", BOLD, 0, 0, 10);
	block_write("size_t count", BOLD, 0, 0, 16);
	block_write("write", BOLD, 0, 0, len_block);
	block_write("ft_write", BOLD, 0, 0, 12);
	block_write("errno", BOLD, 0, 0, 9);
	write_code("buffer", BOLD);
	block_write("", RESET, 0, 0, 38 - len_block);
	write(1, "║\n║", 7);

	int fd;
	int terminal = 0;
	if (argc > 2)
	{
		write(1, "       ", 7);
		fd = get_arg_fd(argv[1]);
		if ((0 <= fd) && (fd <= 2))
			terminal = 1;
		block_write_int(atoi(argv[1]), BLUE, 10);
		block_write_int(atoi(argv[2]), BLUE, 16);
		
		function_write_test(fd, argv, 1, terminal, len_block);

		// comparaison avec vraie fonction
		write(1, "       ", 7);
		block_write("Real write  ->", IGREY, 0, 0, 26);
		
		function_write_test(fd, argv, 0, terminal, len_block);
	}
	write(1, "\n", 1);
}

void	test_read(int argc, char **argv)
{
	int len_block = 16;
	write_code("\n╔════ ft_read ═════════════════════════════════════════════════════════════════════════════════════╗\n║", BOLD);
	write_code("       ssize_t	ft_read(int fd, const void *buf, size_t count);", GREY);
	block_write("", RESET, 0, 0, 36);
	write(1, "║", 3);
	write(1, "\n║", 4);
	block_write("", RESET, 0, 0, 98);
	write(1, "║\n║       ", 14);
	block_write("int fd", BOLD, 0, 0, 10);
	block_write("size_t count", BOLD, 0, 0, 16);
	block_write("read", BOLD, 0, 0, len_block);
	block_write("ft_read", BOLD, 0, 0, 11);
	block_write("errno", BOLD, 0, 0, 9);
	write_code("buffer", BOLD);
	block_write("", RESET, 0, 0, 39 - len_block);
	write(1, "║\n║", 7);

	int n;
	int err = 0;
	int fd;
	int terminal = 0;
	int count;
	if (argc > 2)
	{
		char buf[4096];
		fd = get_arg_fd(argv[1]);
		if ((0 <= fd) && (fd <= 2))
			terminal = 1;

		write(1, "       ", 7);
		block_write_int(fd, BLUE, 10);
		count = atoi(argv[2]);
		block_write_int(count, BLUE, 16);
		if (terminal)
			write(1, "-> '", 4);
		else
			block_write("(no read here)", ITALIC, 0, 0, len_block);
		write(1, YELLOW, strlen(YELLOW));
		
		n = ft_read(fd, buf, count);  //	<------------------------- CALL HERE ------------------------
		
		err = errno;
		write(1, RESET, strlen(RESET));
		if (terminal)
		{
			write(1, "'", 1);
			if (n + 5 < len_block)
			{
				if (n >= 0)
					block_write("", RESET, 0, 0, len_block - n - 5);
				else
					block_write("", RESET, 0, 0, len_block - 5);
			}
		}
		block_write_int(n, CYAN, 11);
		block_write_int(err, BOLD, 9);
		if (n >= 0)
			buf[n] = 0;
		else
			buf[0] = 0;
		block_write(buf, BOLD, 1, 1, len_block);
		write(1, "\n║", 4);
	}
	write(1, "\n", 1);
}

void	test_strdup(int argc, char **argv)
{
	unsigned int len_block = 24;

	write_code("\n╔════ ft_strdup ═══════════════════════════════════════════════════════════════════════════════════╗\n║", BOLD);
	write_code("       char	*ft_strdup(const char *s);", GREY);
	block_write("", RESET, 0, 0, 57);
	write(1, "║\n║", 7);
	block_write("", RESET, 0, 0, 98);
	write(1, "║\n║       ", 14);
	block_write("unsigned char *s", BOLD, 0, 0, len_block);
	block_write("ft_strdup", BOLD, 0, 0, len_block);
	write_code("errno", BOLD);
	block_write("", RESET, 0, 0, 86 - 2 * len_block);
	write(1, "║\n║", 7);

	int i = 1;
	char *res;
	int err;
	while (i < argc)
	{
		write(1, "       ", 7);
		block_write(argv[i], BLUE, 1, 1, len_block);
		res = ft_strdup(argv[i]);   //	<--------------------------------------------- CALL HERE ------------------------
		err = errno;
		if (res)
		{
			block_write(res, CYAN, 1, 1, len_block);
			free(res);
		}
		else
			block_write("(null)", BOLD, 1, 1, len_block);
		block_write_int(err, BOLD, len_block);
		
		block_write("", RESET, 0, 0, 91 - len_block * 3);
		write(1, "║\n║", 7);
		
		i ++;
	}
	block_write("", RESET, 0, 0, 98);
	write(1, "║\n", 4);
}

int	main(int argc, char **argv)
{
	write_code("arguments\n", BLUE);
	write_code("return value\n", CYAN);
	write_code("inside print\n", YELLOW);
	write_code("error\n", RED);

	test_strlen(argc, argv);
	test_strcpy(argc, argv);
	test_strcmp(argc, argv);
	test_write(argc, argv);
	test_read(argc, argv);
	test_strdup(argc, argv);

}
