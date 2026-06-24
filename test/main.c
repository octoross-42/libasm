#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

unsigned int	ft_strlen(const char *str);
int				ft_strcmp(const unsigned char *dest, const unsigned char *src);
char			*ft_strcpy(char *restrict dest, char *restrict src);
int				ft_write(int fd, const void *buf, size_t count);
int				ft_read(int fd, const void *buf, size_t count);
char			*ft_strdup(const char *s);

# define BLACK "\x1B[30m"
# define BGBLACK "\x1B[40m"
# define RED "\x1B[31m"
# define BGRED "\x1B[41m"
# define GREEN "\x1B[32m"
# define BGGREEN "\x1B[42m"
# define BROWN "\x1B[33m"
# define BGBROWN "\x1B[43m"
# define BLUE "\x1B[34m"
# define BGBLUE "\x1B[44m"
# define PURPLE "\x1B[35m"
# define BGPURPLE "\x1B[45m"
# define LBLUE "\x1B[36m"
# define BGLBLUE "\x1B[46m"
# define LGREY "\x1B[37m"
# define BGLGREY "\x1B[47m"
# define GREY "\x1B[90m"
# define BGGREY "\x1B[100m"
# define ORANGE "\x1B[91m"
# define BGORANGE "\x1B[101m"
# define LGREEN "\x1B[92m"
# define BGLGREEN "\x1B[102m"
# define YELLOW "\x1B[93m"
# define BGYELLOW "\x1B[103m"
# define BLUEPURPLE "\x1B[94m"
# define BGBLUEPURPLE "\x1B[104m"
# define ROSE "\x1B[95m"
# define BGROSE "\x1B[105m"
# define CYAN "\x1B[96m"
# define BGCYAN "\x1B[106m"
# define WHITE "\x1B[97m"
# define BGWHITE "\x1B[107m"

# define RESET "\x1B[0m"
# define BOLD "\x1B[1m"
# define LIGHT "\x1B[2m"
# define ITALIC "\x1B[3m"
# define UNDERLINE "\x1B[4m"
# define LINETHROUGH "\x1B[9m"
# define FWRESET "\x1B[22m" // FONT-WEIGHT-RESET
# define FSRESET "\x1B[23m" // FONT-STYLE-RESET
# define RMUNDERLINE "\x1B[24m"
# define RMLINETHROUGH "\x1B[29m"
# define CPRESET "\x1B[39m" // COLOR-PROPERTY-RESET
# define BGRESET "\x1B[49m"
# define OVERLINE "\x1B[53m"
# define RMOVERLINE "\x1B[55m"

void	*malloc(size_t size)
{
	(void)size;
    errno = ENOMEM;
    return NULL;
}

unsigned int	write_ulong(unsigned long n)
{
	unsigned int len = 0;
	if (n > 9)
		len += write_ulong(n / 10);
	char c = (n % 10) + '0';
	write(1, &c, 1);
	return (len + 1);
}


void	write_code(char *s, char *code)
{
	write(1, code, strlen(code));
	write(1, s, strlen(s));
	write(1, RESET, strlen(RESET));
}

void	block_write_int(long n, char *code, unsigned int len_block)
{
	write(1, " ", 1);
	write(1, code, strlen(code));
	long long pos = n;
	
	unsigned int len = 1;
	if (pos < 0)
	{
		write(1, "-", 1);
		pos = -pos;
		len += 1;
	}
	len += write_ulong((unsigned int) pos);
	write(1, RESET, strlen(RESET));
	
	if (len >= len_block)
		return ;
	unsigned int i = 0;
	while (i ++ < len_block - len)
		write(1, " ", 1);
}

void	block_write(char *s, char *code, int quote, int data, unsigned int len_block)
{
	if (data)
		write(1, " ", 1);
	write(1, code, strlen(code));
	if (quote)
	{
		write(1, "'", 1);
		write(1, s, strlen(s));
		write(1, "'", 1);
	}
	else
		write(1, s, strlen(s));		
	write(1, RESET, strlen(RESET));
	
	unsigned int len = strlen(s) + (quote ? 2: 0) + (data ? 1: 0);
	if (len >= len_block)
		return ;
	unsigned int i = 0;
	while (i ++ < len_block - len)
		write(1, " ", 1);
}

void	test_strlen(int argc, char **argv)
{
	unsigned int len_block = 24;

	write_code("╔════ ft_strlen ═══════════════════════════════════════════════════════════╗\n\t", BOLD);
	block_write("char *str", BOLD, 0, 0, len_block);
	write_code("ft_strlen\n", BOLD);
	
	int i = 0;
	while (i < argc)
	{
		write(1, "\t", 1);
		block_write(argv[i], BLUE, 1, 1, len_block);
		block_write_int(ft_strlen(argv[i]), WHITE, len_block);
		write(1, "\n", 1);
		i ++;
	}
	
	// maybe segfault sans doute pas
	write(1, "\t", 1);
	block_write("argv", RED, 0, 1, len_block);
	block_write_int(ft_strlen((char *)argv), WHITE, len_block);
	write(1, "\n", 1);
}

void	test_strcmp(int argc, char **argv)
{
	unsigned int len_block = 24;

	write_code("╔════ ft_strcmp ═══════════════════════════════════════════════════════════╗\n\t", BOLD);
	block_write("unsigned char *dest", BOLD, 0, 0, len_block);
	block_write("unsigned char *src", BOLD, 0, 0, len_block);
	write_code("ft_strcmp\n", BOLD);
	int i = 0;
	while (i + 1 < argc)
	{
		write(1, "\t", 1);
		block_write(argv[i], BLUE, 1, 1, len_block);
		block_write(argv[i + 1], BLUE, 1, 1, len_block);
		block_write_int(ft_strcmp((unsigned char *)argv[i], (unsigned char *)argv[i + 1]), WHITE, len_block);
		write(1, "\n", 1);
		i ++;
	}
}

void	test_strcpy(int argc, char **argv)
{
	// invalid read sur le strlen si src > dest -> normal
	unsigned int len_block = 24;

	write_code("╔════ ft_strcpy ═══════════════════════════════════════════════════════════╗\n\t", BOLD);
	block_write("unsigned char *dest", BOLD, 0, 0, len_block);
	block_write("unsigned char *src", BOLD, 0, 0, len_block);
	write_code("ft_strcpy\n", BOLD);
	int i = 1;
	char *res;
	char *dest;
	char *src;
	while (i + 1 < argc)
	{
		write(1, "\t", 1);
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
		res = ft_strcpy(dest, src);
		free(src);
		write(1, " '", 2);
		write_code(res, BOLD);
		free(dest);
		write(1, "'\n", 2);
		i ++;
	}
}

void	test_write(int argc, char **argv)
{
	int len_block = 16;
	write_code("╔════ ft_write ════════════════════════════════════════════════════════════════════════════════════╗\n\t", BOLD);
	block_write("int fd", BOLD, 0, 0, len_block);
	block_write("void *buf", BOLD, 0, 0, len_block);
	block_write("size_t count", BOLD, 0, 0, len_block);
	block_write("write", BOLD, 0, 0, len_block);
	block_write("ft_write", BOLD, 0, 0, len_block);
	write_code("errno\n", BOLD);

	int n;
	int err = 0;
	if (argc > 3)
	{
		write(1, "\t", 1);
		block_write_int(atoi(argv[1]), BLUE, len_block);
		block_write(argv[2], BLUE, 1, 1, len_block);
		block_write_int(atoi(argv[3]), BLUE, len_block);
		write(1, " '", 2);
		n = ft_write(atoi(argv[1]), argv[2], (size_t)atoi(argv[3]));
		err = errno;
		write(1, "'", 1);
		if (n >= 0)
			block_write("", RESET, 0, 0, len_block - n - 2);
		else
			block_write("", RESET, 0, 0, len_block - 2);
		block_write_int(n, BOLD, len_block);
		block_write_int(err, BOLD, len_block);
		write(1, "\n", 1);
	}
}

void	test_read(int argc, char **argv)
{
	int len_block = 16;
	write_code("╔════ ft_read ════════════════════════════════════════════════════════════════════════════════════╗\n\t", BOLD);
	block_write("int fd", BOLD, 0, 0, len_block);
	block_write("size_t count", BOLD, 0, 0, len_block);
	block_write("read", BOLD, 0, 0, len_block);
	block_write("ft_read", BOLD, 0, 0, len_block);
	block_write("errno", BOLD, 0, 0, len_block);
	write_code("buffer\n", BOLD);

	int n;
	int err = 0;
	if (argc > 2)
	{
		char buf[4096];

		write(1, "\t", 1);
		block_write_int(atoi(argv[1]), BLUE, len_block);
		block_write_int(atoi(argv[2]), BLUE, len_block);
		write(1, "-> '", 4);
		n = ft_read(atoi(argv[1]), buf, (size_t)atoi(argv[2]));
		err = errno;
		write(1, "'", 1);
		if (n + 5 < len_block)
		{
			if (n >= 0)
				block_write("", RESET, 0, 0, len_block - n - 5);
			else
				block_write("", RESET, 0, 0, len_block - 5);
		}
		block_write_int(n, BOLD, len_block);
		block_write_int(err, BOLD, len_block);
		if (n >= 0)
			buf[n] = 0;
		block_write(buf, BOLD, 1, 1, len_block);
		write(1, "\n", 1);
	}
}


void	test_read_open(int argc, char **argv)
{
	int len_block = 16;
	write_code("╔════ ft_read ════════════════════════════════════════════════════════════════════════════════════╗\n\t", BOLD);
	block_write("int fd", BOLD, 0, 0, len_block);
	block_write("size_t count", BOLD, 0, 0, len_block);
	block_write("read", BOLD, 0, 0, len_block);
	block_write("ft_read", BOLD, 0, 0, len_block);
	block_write("errno", BOLD, 0, 0, len_block);
	write_code("buffer\n", BOLD);

	int n;
	int err = 0;
	if (argc > 2)
	{
		char buf[4096];
		write(1, "\t", 1);
		int fd = open(argv[1], O_RDONLY, 0);
		if (fd < 0)
			return ;
		block_write_int(fd, BLUE, len_block);
		block_write_int(atoi(argv[2]), BLUE, len_block);
		write(1, "-> '", 4);
		n = ft_read(fd, buf, (size_t)atoi(argv[2]));
		err = errno;
		write(1, "'", 1);
		if ((n + 5 < len_block) || (fd >= 3))
		{
			if ((n >= 0) && (fd < 3))
				block_write("", RESET, 0, 0, len_block - n - 5);
			else
				block_write("", RESET, 0, 0, len_block - 5);
		}
		block_write_int(n, BOLD, len_block);
		block_write_int(err, BOLD, len_block);
		if (n >= 0)
			buf[n] = 0;
		block_write(buf, BOLD, 1, 1, len_block);
		write(1, "\n", 1);
	}
}

void	test_strdup(int argc, char **argv)
{
	unsigned int len_block = 24;

	write_code("╔════ ft_strdup ═══════════════════════════════════════════════════════════╗\n\t", BOLD);
	block_write("unsigned char *s", BOLD, 0, 0, len_block);
	block_write("ft_strdup", BOLD, 0, 0, len_block);
	write_code("errno\n", BOLD);
	int i = 1;
	char *res;
	int err;
	while (i < argc)
	{
		write(1, "\t", 1);
		block_write(argv[i], BLUE, 1, 1, len_block);
		res = ft_strdup(argv[i]);
		err = errno;
		if (res)
		{
			block_write(res, BOLD, 1, 1, len_block);
			free(res);
		}
		else
			block_write("(null)", BOLD, 1, 1, len_block);
		block_write_int(err, BOLD, len_block);
		write(1, "\n", 1);
		
		i ++;
	}
}

int	main(int argc, char **argv)
{
	// test_strlen(argc, argv);
	// test_strcmp(argc, argv);
	// test_write(argc, argv);
	// test_read(argc, argv);
	// test_read_open(argc, argv);
	test_strcpy(argc, argv);
	test_strdup(argc, argv);
}
