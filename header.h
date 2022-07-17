#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

typedef struct stats
{
	int hits;
	int misses;
	int shots;
	char win_or_lose[100];
} Stats;


int welcome_screen(void);

void initialize_game_board(char board[10][10], int rows, int columns);

int select_who_starts_first(void);

void manually_place_ships_on_board(char board[10][10], char ship);

void randomly_place_ships_on_board(char board[10][10], char ship);

void check_shot(char board[][10], int target_row, int target_column, int player, int* x, int* y, int* shot);

int is_winner(char board[][10]);

void sunk_ship_message(int check, char ship);

void update_board(char board[][10], int x, int y, int hit_or_miss);

void display_board(char board[10][10], int row, int column, int player_board);

void output_current_move(int x, int y, int hit_or_miss, FILE* outfile, int player, int number_of_ships);

int check_if_sunk_ship(char board[][10], int row, int column, char ship);

void input_stats(struct stats player, int hit_or_miss, int number_of_ships);

void send_stats(struct stats player, FILE* outfile, int players);

void rand_index(int length, int direction, int* row_start, int* column_start);

FILE* open_file_write(void);

void get_target(int* target_row, int* target_column);

void random_target(int* target_row, int* target_column);

void run_app();
