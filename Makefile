CC =	gcc

SRC_DIR = src

SRC =	$(SRC_DIR)/main.c	\
		$(SRC_DIR)/game_board.c	\
		$(SRC_DIR)/serv_socket_info.c \
		$(SRC_DIR)/new_client.c			\
		$(SRC_DIR)/msg_management.c

BINARY	=	my_morpion


all:
	$(CC) -o $(BINARY) $(SRC)
clean:
	rm -rf *.o *.a *.so

fclean: clean
	rm -rf $(BINARY)

re:	clean all