CLIENT_SRCS = client.c helper_client.c
SERVER_SRCS = server.c
BONUS_CLIENT_SRCS = client_bonus.c helper_client_bonus.c
BONUS_SERVER_SRCS = server_bonus.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
BONUS_CLIENT_OBJS = $(BONUS_CLIENT_SRCS:.c=.o)
BONUS_SERVER_OBJS = $(BONUS_SERVER_SRCS:.c=.o)
CLIENT = client
SERVER = server
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) -o $(CLIENT)

$(SERVER): $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) -o $(SERVER)

bonus: fclean $(BONUS_CLIENT_OBJS) $(BONUS_SERVER_OBJS)
	$(CC) $(BONUS_CLIENT_OBJS) -o $(CLIENT)
	$(CC) $(BONUS_SERVER_OBJS) -o $(SERVER)

%o: %c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(CLIENT_OBJS) $(SERVER_OBJS)
	rm -rf $(BONUS_CLIENT_OBJS) $(BONUS_SERVER_OBJS)

fclean: clean
	rm -rf $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re