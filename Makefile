CLIENT_SRCS = server.c
SERVER_SRCS = client.c
CLIENT_OBJS = $($(CLIENT_SRCS:.c=.o))
SERVER_OBJS = $($(SERVER_SRCS:.c=.o))
CLIENT = client
SERVER = server
CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_OBJS)
	cc $(CLIENT_OBJS) -o $(CLIENT)

$(SERVER): $(SERVER_OBJS)
	cc $(SERVER_OBJS) -o $(SERVER)

clean:
	rm $(CLIENT_OBJS) $(SERVER_OBJS)

fclean: clean
	rm $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re