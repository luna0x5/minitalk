# -*- MakeFile -*-

SERVER = server
CLIENT = client
CC = cc
FLAGS = -Wall -Wextra -Werror
SSOURCES = mandatory/server.c \
		mandatory/ft_putnbr_fd.c 
CSOURCES = mandatory/client.c \
		mandatory/ft_atoi.c
BSSOURCES = bonus/server_bonus.c \
		mandatory/ft_putnbr_fd.c
BCSERVER = bonus/client_bonus.c \
		mandatory/ft_atoi.c

all : $(SERVER) $(CLIENT)

$(SERVER) : $(SSOURCES) mandatory/minitalk.h
	$(CC) $(FLAGS) $(SSOURCES) -o server

$(CLIENT) : $(CSOURCES) mandatory/minitalk.h
	$(CC) $(FLAGS) $(CSOURCES) -o client

bonus : $(BSSOURCES) $(BCSERVER) bonus/minitalk_bonus.h
	$(CC) $(FLAGS) $(BSSOURCES) -o server_bonus
	$(CC) $(FLAGS) $(BCSERVER) -o client_bonus

fclean :
	$(RM) $(SERVER) $(CLIENT) server_bonus client_bonus

re : fclean all

.PHONY : clean
