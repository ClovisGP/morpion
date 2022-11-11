#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_


struct gameBoard {
    int lenght;
    char currentPlayer;
    char **board;
    char **(*board_generation)(int lenght);
    int (*case_modification)(struct gameBoard *thisStruct, char *str_msg);
};

int gameBoardDestroy(struct gameBoard *);
struct gameBoard gameBoardConstruct(void);
#endif /* !GAME_BOARD_H_ */