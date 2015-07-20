##
## Makefile for  in /home/quach_a/rendu/PSU_2014_myftp/test
## 
## Made by Jonathan Quach
## Login  <jonathan.quach@epitech.eu>
## 
## Started on  Sun Mar 15 19:27:33 2015 Jonathan Quach
## Last update Thu Mar 26 22:42:18 2015 Jonathan Quach
##

CC = gcc

RM = rm -f

CFLAGS += -W -Wall -Werror

CLIENT_SRC = 	src_client/client.c \
		src_client/utils.c \
		src_client/signal_client.c \

SERVER_SRC = 	src_server/server.c \
		src_server/commands.c \
		src_server/utils_server.c \
		src_server/exec_utils.c \
		src_server/loop.c \
		src_server/exec_login.c \

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_NAME = client

SERVER_NAME = serveur

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJ)
		$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJ)

$(SERVER_NAME): $(SERVER_OBJ)
		$(CC) -o $(SERVER_NAME) $(SERVER_OBJ)

clean:
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ)

fclean: clean
	$(RM) $(CLIENT_NAME) $(SERVER_NAME)

re: fclean all

.PHONY: all clean fclean re
