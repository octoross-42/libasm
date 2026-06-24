#include "test.h"

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


void	write_int(long n, char *code)
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
