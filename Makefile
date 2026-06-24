NAME = libasm.a

SRCS    = src/ft_strlen.s \
		src/ft_strcmp.s \
		src/ft_strcpy.s \
		src/ft_write.s \
		src/ft_read.s \
		src/ft_strdup.s
BUILD   = build

OBJS	 = $(patsubst src/%.s,$(BUILD)/%.o,$(SRCS))

ASM = nasm
ASMFLAGS = -f elf64

RUN_NAME = run

CC = gcc
CFLAGS   = -Wall -Wextra -Werror -g3

SRCS_RUN = test/main.c \
		test/test_write.c
OBJS_RUN = $(patsubst src/%.s,$(BUILD)/%.o,$(SRCS_RUN))



$(BUILD)/%.o: src/%.s
	@mkdir -p $(BUILD)
	$(ASM) $(ASMFLAGS) $< -o $@

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

s: ${OBJS}
	ld -m elf_x86_64 ${OBJS} -o ${RUN_NAME}

all : ${NAME}

clean:
	rm -fr ${OBJS} ${BUILD}

fclean: clean
	rm -f ${NAME} ${RUN_NAME}

re: fclean all


$(BUILD)/%.o: test/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(OBJS_RUN) $(NAME)
	${CC} -I src -I test ${OBJS_RUN} ${NAME} -o ${RUN_NAME}