#include "game.h"

int main(int argc, char **argv) {

    int OTHER_CLIENT;
    struct response res;
    struct gameboard board;
    int chosen;

    board_setup(&board);

    if (argc == 1) {
        int listen_socket = client_listen();

        printf("Waiting for player...\n");

        OTHER_CLIENT = client_accept(listen_socket);

        printf("Player connected!\n");

        chosen_setup(&chosen);

        write(OTHER_CLIENT, &(board.characters), sizeof(board.characters));

        print_board(&board, chosen);

        printf("Ask a question: ");
        ask_initial_question(OTHER_CLIENT, res);

        while(1) {
            game_logic(OTHER_CLIENT, res, chosen, &board);
        }
    }
    else if (argc == 2) {
        OTHER_CLIENT = client_connect( argv[1] );

        printf("You have successfuly connected!\n");

        chosen_setup(&chosen);

        read(OTHER_CLIENT, &(board.characters), sizeof(board.characters));

        while(1) {
            game_logic(OTHER_CLIENT, res, chosen, &board);
        }
    }
    close(OTHER_CLIENT);
}
