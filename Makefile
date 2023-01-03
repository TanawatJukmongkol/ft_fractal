
run:
	gcc main.c -lX11 -lXext -lmlx -g -Wall -Werror -Wextra
	./a.out

# Minilibx installer

mlx-linux: install-libaray install-manpage
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
