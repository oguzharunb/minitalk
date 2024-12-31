CLIENT_SRCS = client.c helper_client.c
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

%o: %c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -r $(CLIENT_OBJS) $(SERVER_OBJS)

fclean: clean
	rm -r $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re