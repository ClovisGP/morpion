CC =	gcc

SRC_DIR_SERV = server/src

SRC_SERV =	$(SRC_DIR_SERV)/main.c	\
		$(SRC_DIR_SERV)/game_board.c	\
		$(SRC_DIR_SERV)/serv_socket_info.c \
		$(SRC_DIR_SERV)/new_client.c			\
		$(SRC_DIR_SERV)/msg_management.c		\
		$(SRC_DIR_SERV)/arg_management.c

BINARY_SERV	=	my_morpion_server

SRC_DIR_CLIE = client/src

SRC_CLIE =	$(SRC_DIR_CLIE)/main.c			\
			$(SRC_DIR_CLIE)/clie_socket_info.c	\
			$(SRC_DIR_SERV)/arg_management.c

BINARY_CLIE	=	my_morpion_client

all:
	$(CC) -o $(BINARY_SERV) $(SRC_SERV)
	$(CC) -o $(BINARY_CLIE) $(SRC_CLIE)
clean:
	rm -rf *.o *.a *.so

fclean: clean
	rm -rf $(BINARY_SERV)
	rm -rf $(BINARY_CLIE)

re:	clean all