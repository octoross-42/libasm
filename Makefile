NAME = libasm.a

SRCS = ft_strlen.s
BUILD = build

OBJS = $(SRCS:%.s=$(BUILD)/%.o)

ASM = nasm
ASMFLAGS = -f elf64

RUN_NAME = run

CC = gcc
CFLAGS = -Wall -Wextra 
# -Werror

SRCS_RUN = main.c
OBJS_RUN = $(SRCS_RUN:%.c=$(BUILD)/%.o)


$(BUILD)/%.o: %.s
	@mkdir -p $(BUILD)
	$(ASM) $(ASMFLAGS) $< -o $@

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

s: ${OBJS}
	ld -m elf_x86_64 ${OBJS} -o ${RUN_NAME}

all : ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all


$(BUILD)/%.o: %.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

c: $(OBJS_RUN) $(NAME)
	${CC} ${OBJS_RUN} ${NAME} -o ${RUN_NAME}