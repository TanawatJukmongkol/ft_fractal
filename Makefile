NAME		= fractol
SRCS		= fractol.c event_listener.c MLXTras.c graphics.c
SRC_DIR		= ./src/
BUILD_DIR	= ./build/

SRC			= ${addprefix ${BUILD_DIR},${SRCS}}
OBJ			= ${SRC:.c=.o}

CC			= gcc
CFLAG		= -g -lX11 -lXext -lmlx -Wall -Werror -Wextra -O3

all: ${BUILD_DIR} ${NAME}

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ${NAME}

re: fclean all

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BUILD_DIR}%.o:${SRC_DIR}%.c
	$(CC) -c -o $@ $^

${NAME}: ${OBJ}
	$(CC) ${OBJ} -o ${NAME} $(CFLAG)

# Minilibx installer
mlx-linux:
	git clone git@github.com:42Paris/minilibx-linux.git mlx-linux
	make -C ./mlx-linux

mlx-test:
	./mlx-linux/test/run_tests.sh

install-library:
	sudo mkdir -p /usr/include
	sudo mkdir -p /usr/lib
	sudo cp ./mlx-linux/*.h /usr/include
	sudo cp ./mlx-linux/libmlx*.a /usr/lib

install-manpage:
	gzip ./mlx-linux/man/man*/*
	sudo mkdir -p /usr/man/man1 /usr/man/man3
	sudo cp -r ./mlx-linux/man/man1/* /usr/man/man1
	sudo cp -r ./mlx-linux/man/man3/* /usr/man/man3

mlx-uninstall: /usr/man/man1/mlx.1.gz
	sudo rm -f /usr/include/mlx*
	sudo rm -f /usr/lib/libmlx*.a
	sudo rm -f $(subst ./mlx-linux/man,/usr/share/man,$(shell ls ./mlx-linux/man/man*/*))

.PHONY:	all clean fclean re mlx-linux mlx-test install-library install-manpage mlx-uninstall