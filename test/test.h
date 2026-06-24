#ifndef TEST_H

#define TEST_H

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

# define IGREY "\x1B[3;90m"

# include "libasm.h"

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

unsigned int	write_ulong(unsigned long n);
void			write_code(char *s, char *code);
void			block_write_int(long n, char *code, unsigned int len_block);
void			block_write(char *s, char *code, int quote, int data, unsigned int len_block);

#endif