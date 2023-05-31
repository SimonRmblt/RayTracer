##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##


SRCS =	src/main.cpp	\
		src/point.cpp	\
		src/vector.cpp	\
		src/ray.cpp	\
		src/sphere.cpp	\
		src/rectangle.cpp	\
		src/camera.cpp	\
		src/directionalLight.cpp	\
		src/fileParsing.cpp	\
		src/plane.cpp	\
		src/cone.cpp	\
		src/cylinder.cpp	\
		src/pointLight.cpp	\
		src/raytracer.cpp	\

HEADS 	=	include/point.hpp	\
			include/vector.hpp	\
			include/ray.hpp	\
			include/sphere.hpp	\
			include/rectangle.hpp	\
			include/camera.hpp	\
			include/raytracer.hpp	\
			include/IObject.hpp	\
			include/fileParsing.hpp	\
			include/plane.hpp	\
			include/cone.hpp	\
			include/cylinder.hpp	\
			include/pointLight.hpp	\
			include/ILight.hpp	\

INCLUDE_PATH	=	./include/

FILES = $(SRCS)	\

TEST_FILES	=	\

OBJ =	$(FILES:.cpp=.o)

NAME	=	 raytracer

CC	=	g++ -lsfml-graphics -lsfml-window -lsfml-system -lconfig++

LIB	=	\

CPPFLAGS	+=	-std=c++20 -Wall -Wextra -I $(INCLUDE_PATH) -lsfml-graphics -lsfml-window -lsfml-system -O3 -lconfig++

TEST_EXT = $(LIB) --coverage -lcriterion

all:	$(NAME)

debug:	CPPFLAGS += -g
debug:	fclean all

clean:
	rm -f $(OBJ)
	rm -f vgcore*

fclean: clean
	rm -f $(NAME)

tests_run:
	$(CC) -o unit_tests $(FILES) $(TEST_FILES) $(CFLAGS) -L./lib $(TEST_EXT)
	./unit_tests
	gcovr -r .
	rm -f unit_tests*

re: fclean all

$(NAME):    $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L./lib $(LIB)