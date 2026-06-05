#include <stdio.h>
#include <string.h>

unsigned int	ft_strlen(char *str);

void	test_ft_strlen(int argc, char **argv)
{
	printf("ft_strlen -------------------------------------------------------\n");
	if (argc > 1)
		printf("\t'%s': %d %ld\n", argv[1], ft_strlen(argv[1]), strlen(argv[1]));
	printf("\t'(null)': %d segfault\n", ft_strlen(NULL));

}

int	main(int argc, char **argv)
{
	test_ft_strlen(argc, argv);
}