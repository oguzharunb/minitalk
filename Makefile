CLIENT_SRCS = client.c
SERVER_SRCS = server.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT = client
SERVER = server
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) -o $(CLIENT)

$(SERVER): $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) -o $(SERVER)

clean:
	rm $(CLIENT_OBJS) $(SERVER_OBJS)

%o: %c
	$(CC) $(FLAGS) -c $< -o $@

fclean: clean
	rm $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re