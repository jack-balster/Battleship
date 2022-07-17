#include "header.h"


int welcome_screen(void)
{
	int choice = 0;
	printf("\n Welcome!\n\n");
	printf(" Rules of the game:\n\n");
	printf(" This is a two player game. Player 1 is you and Player 2 is the computer.\n");
	printf(" A player wins by sinking all of their opponent's ships before their opponent sinks theirs\n");
	printf(" There are five ships you must place: Carrier (5 spaces), Battleship (4 spaces),\n");
	printf(" Cruiser (3 spaces), Submarine (3 spaces), and a Destroyer (2 spaces).\n");
	printf(" You can place the ships vertically or horizontally, but not diagonally.\n");
	printf(" To shoot at your opponent's ship, simply enter the coordinates where you think their ships are.\n");
	printf(" The game will indicate whether you hit or missed their ships every turn.\n\n");
	printf(" Press enter to start the game...\n");
	getchar();
	
	system("cls");

	printf("\n Ship Menu\n\n");
	printf(" 1. Manually place your ships\n");
	printf(" 2. Randomly place your ships\n\n");
	printf(" Select option 1 or 2: ");
	scanf("%d", &choice);

	return choice;
}


void initialize_game_board(char board[10][10], int rows, int columns)
{
	int row_position = 0, column_position = 0;
	for (row_position = 0; row_position < rows; row_position++)
	{
		for (column_position = 0; column_position < columns; column_position++)
		{
			board[row_position][column_position] = '-';
		}
	}
}


int select_who_starts_first(void)
{
	int first = 0;
	first = rand() % 2;
	return first;
}


void manually_place_ships_on_board(char board[][10], char ship)
{
	int length = 0, row_position = 0, column_position = 0, count = 0;
	switch (ship)
	{
	case 'c': length = 5;
		printf(" Please enter the coordinates for your Carrier (size 5): \n");
		break;
	case 'b': length = 4;
		printf(" Please enter the coordinates for your Battleship (size 4): \n");
		break;
	case 'r': length = 3;
		printf(" Please enter the coordinates for your Cruiser (size 3): \n");
		break;
	case 's': length = 3;
		printf(" Please enter the coordinates for your Submarine (size 3): \n");
		break;
	case 'd': length = 2;
		printf(" Please enter the coordinates for your Destroyer (size 2): \n");
		break;
	default: break;
	}
	while (count < length)
	{
		printf(" Enter the coordinate you would like to place your ship ONE # AT A TIME (vertically then horizontally): ", count + 1);
		scanf("%d %d", &row_position, &column_position);

		if (board[row_position][column_position] == '-')
		{
			board[row_position][column_position] = ship;
			count++;
		}
		else
		{
			printf(" Please enter a valid set of coordinates\n");
		}
	}
}


void randomly_place_ships_on_board(char board[][10], char ship)
{
	int length = 0, row_start = 0, column_start = 0, count = 0, row_check = 0,
		column_check = 0, orientation = 0;
	switch (ship)
	{
	case 'c': //Carrier
		length = 5;
		break;
	case 'b': //Battlership
		length = 4;
		break;
	case 'r': //Cruiser
		length = 3;
		break;
	case 's': //Submarine
		length = 3;
		break;
	case 'd': //Destroyer
		length = 2;
		break;
	default: break;
	}
	orientation = rand() % 2;

	rand_index(length, orientation, &row_start, &column_start);
	row_check = row_start;
	column_check = column_start;

	while (count < length)
	{
		if (orientation == 0)
		{
			if (board[row_check][column_check] == '-')
			{
				row_check++;
				count++;
			}
			else
			{
				rand_index(length, orientation, &row_start, &column_start);
				row_check = row_start;
				column_check = column_start;
				count = 0;
			}
		}
		else if (orientation == 1)
		{
			if (board[row_check][column_check] == '-')
			{
				column_check++;
				count++;
			}
			else
			{
				rand_index(length, orientation, &row_start, &column_start);
				row_check = row_start;
				column_check = column_start;
				count = 0;
			}
		}
	}
	count = 0;
	while (count < length)
	{
		if (orientation == 0)
		{
			board[row_start++][column_start] = ship;
		}
		else if (orientation == 1)
		{
			board[row_start][column_start++] = ship;
		}
		count++;
	}
}


void check_shot(char board[][10], int target_row, int target_column, int player, int* x, int* y, int* shot)
{
	int row_check = 0, column_check = 0;
	if (board[target_row][target_column] == 'o' || board[target_row][target_column] == 'X')
	{
		if (player == 1)
		{
			do
			{
				printf(" Invalid input\n");
				get_target(&row_check, &column_check);
			} while (board[row_check][column_check] == 'o' || board[row_check][column_check] == 'X');
		}
		else
		{
			do
			{
				random_target(&row_check, &column_check);
			} while (board[row_check][column_check] == 'o' || board[row_check][column_check] == 'X');
		}

		if (board[row_check][column_check] == '-')
		{
			printf(" Miss!\n");
			*shot = 2;
		}
		else
		{
			printf(" Hit!\n");
			*shot = 1;
		}
		*x = row_check;
		*y = column_check;
	}
	else if (board[target_row][target_column] == '-')
	{
		printf(" Miss!\n");
		*shot = 2;
		*x = target_row;
		*y = target_column;
	}
	else
	{
		printf(" Hit!\n");
		*shot = 1;
		*x = target_row;
		*y = target_column;
	}
}


int is_winner(char board[][10])
{
	int number_of_ships = 0;
	number_of_ships += check_if_sunk_ship(board, 10, 10, 'c');
	number_of_ships += check_if_sunk_ship(board, 10, 10, 'b');
	number_of_ships += check_if_sunk_ship(board, 10, 10, 'r');
	number_of_ships += check_if_sunk_ship(board, 10, 10, 's');
	number_of_ships += check_if_sunk_ship(board, 10, 10, 'd');
	return number_of_ships;
}


void sunk_ship_message(int check, char ship)
{
	if (check == 1)
	{
		switch (ship)
		{
		case 'c': printf(" The Carrier has been sunk!\n");
			break;
		case 'b': printf(" The Battleship has been sunk!\n");
			break;
		case 'r': printf(" The Cruiser has been sunk!\n");
			break;
		case 's': printf(" The Submarine has been sunk!\n");
			break;
		case 'd': printf(" The Destroyer has been sunk!\n");
			break;
		default: break;
		}
	}
}


void update_board(char board[][10], int x, int y, int hit_or_miss)
{
	if (hit_or_miss == 1)
	{
		board[x][y] = 'X';
	}
	else
	{
		board[x][y] = 'o';
	}
}


void display_board(char board[][10], int row, int column, int player_board)
{
	int row_position = 0, column_position = 0;

	if (player_board == 1)
	{
		printf(" Player 1's board\n");
		printf(" ");
		for (column_position = 0; column_position < column; column_position++)
		{
			printf(" %d", column_position);
		}
		putchar('\n');

		for (row_position = 0; row_position < row; row_position++)
		{
			printf("%d", row_position);
			for (column_position = 0; column_position < column; column_position++)
			{
				printf(" %c", board[row_position][column_position]);
			}
			putchar('\n');
		}
		printf("\n");
	}
	else
	{
		printf(" Player 2's board\n");
		printf(" ");
		for (column_position = 0; column_position < column; column_position++)
		{
			printf(" %d", column_position);
		}
		putchar('\n');

		for (row_position = 0; row_position < row; row_position++)
		{
			printf("%d", row_position);
			for (column_position = 0; column_position < column; column_position++)
			{
				if (board[row_position][column_position] == 'c' || board[row_position][column_position] == 'b' || board[row_position][column_position] == 'r' || board[row_position][column_position] == 's' || board[row_position][column_position] == 'd')
				{
					printf(" %c", '-');
				}
				else
				{
					printf(" %c", board[row_position][column_position]);
				}
			}
			putchar('\n');
		}
		printf("\n");
	}
}


void output_current_move(int x, int y, int hit_or_miss, FILE* outfile, int player, int number_of_ships)
{
	if (hit_or_miss == 1)
	{
		fprintf(outfile, " Player %d shot at coordinates (%d, %d) and it was a hit\n", player, x, y);
	}
	else
	{
		fprintf(outfile, " Player %d shot at coordinates (%d, %d) and it was a miss\n", player, x, y);
	}
}


int check_if_sunk_ship(char board[][10], int row, int column, char ship)
{
	int check = 1, row_position = 0, column_position = 0;
	for (row_position = 0; row_position < row; row_position++)
	{
		for (column_position = 0; column_position < column; column_position++)
		{
			if (board[row_position][column_position] == ship)
			{
				check = 0;
			}
		}
	}
	return check;
}


void input_stats(struct stats player, int hit_or_miss, int number_of_ships)
{
	if (hit_or_miss == 1)
	{
		(player.hits)++;
	}
	else
	{
		(player.misses)++;
	}

	(player.shots)++;

	if (number_of_ships == 5)
	{
		strcpy(player.win_or_lose, " Winner");
	}
	else
	{
		strcpy(player.win_or_lose, " Loser");
	}
}


void send_stats(struct stats player, FILE* outfile, int players)
{
	if (players == 1)
	{
		fprintf(outfile, "\n Player 1 stats:\n");
	}
	else
	{
		fprintf(outfile, "\n Player 2 stats:\n");
	}
	fprintf(outfile, " number of shots: %d\n", player.shots); 
	fprintf(outfile, " number of hits: %d\n", player.hits);
	fprintf(outfile, " number of misses: %d\n", player.misses);
	fprintf(outfile, "%s\n", player.win_or_lose);
}


void rand_index(int length, int orientation, int* row_start, int* column_start)
{
	if (orientation == 0) 
	{
		*column_start = rand() % 10;
		*row_start = rand() % (10 - length + 1);
	}
	else
	{
		*column_start = rand() % (10 - length + 1);
		*row_start = rand() % 10;
	}
}


FILE* open_file_write(void)
{
	FILE* outfile = NULL;
	outfile = fopen("battlelog.txt", "w");
	return outfile;
}

void get_target(int* target_row, int* target_column)
{
	printf(" Please enter the coordinate you would like to shoot at (ONE # AT A TIME, vertically then horizontally): ");
	scanf("%d%d", target_row, target_column);
}


void random_target(int* target_row, int* target_column)
{
	*target_row = rand() % 10;
	*target_column = rand() % 10;
}


void run_app()
{
	FILE* output = NULL;
	int choice = 0, p1 = 1, p2 = 2, turn = 0, target_row = 0,
		target_column = 0, hit_or_miss = 0, x = 0, y = 0;
	int ships_p1 = 0, ships_p2 = 0, ships = 5;
	int check_c = 0, check_b = 0, check_r = 0,
		check_s = 0, check_d = 0;
	char p1_board[10][10] = { {'\0', '\0'}, {'\0'} };
	char p2_board[10][10] = { {'\0', '\0'}, {'\0'} };
	struct stats player1[10];
	struct stats player2[10];

	srand((unsigned int)time(NULL));

	output = open_file_write();

	choice = welcome_screen();
	system("cls");

	//manual user board
	switch (choice)
	{
	case 1: initialize_game_board(p1_board, 10, 10);
		display_board(p1_board, 10, 10, p1);

		manually_place_ships_on_board(p1_board, 'c');
		system("pause");
		system("cls");
		display_board(p1_board, 10, 10, p1);

		manually_place_ships_on_board(p1_board, 'b');
		system("pause");
		system("cls");
		display_board(p1_board, 10, 10, p1);

		manually_place_ships_on_board(p1_board, 'r');
		system("pause");
		system("cls");
		display_board(p1_board, 10, 10, p1);

		manually_place_ships_on_board(p1_board, 's');
		system("pause");
		system("cls");
		display_board(p1_board, 10, 10, p1);

		manually_place_ships_on_board(p1_board, 'd');
		system("pause");
		system("cls");
		display_board(p1_board, 10, 10, p1);
		
		system("pause");
		system("cls");
		break;

	case 2: initialize_game_board(p1_board, 10, 10);
		//User's random board
		randomly_place_ships_on_board(p1_board, 'c');
		randomly_place_ships_on_board(p1_board, 'b');
		randomly_place_ships_on_board(p1_board, 'r');
		randomly_place_ships_on_board(p1_board, 's');
		randomly_place_ships_on_board(p1_board, 'd');

		display_board(p1_board, 10, 10, p1);
		system("pause");
		system("cls");
		break;
	default: printf(" Invalid input");
		break;
	}

	initialize_game_board(p2_board, 10, 10);
	//computer's random board
	randomly_place_ships_on_board(p2_board, 'c');
	randomly_place_ships_on_board(p2_board, 'b');
	randomly_place_ships_on_board(p2_board, 'r');
	randomly_place_ships_on_board(p2_board, 's');
	randomly_place_ships_on_board(p2_board, 'd');

	turn = select_who_starts_first();
	if (turn == 0)
	{
		printf(" Player 1 will go first!\n");
	}
	else
	{
		printf(" Player 2 will go first!\n");
	}
	system("pause");
	system("cls");
	//Gameplay
	while (ships_p1 != ships && ships_p2 != ships)
	{
		if (turn % 2 == 0)
		{
			display_board(p1_board, 10, 10, p1);
			display_board(p2_board, 10, 10, p2);
			printf(" Player 1: \n");
			get_target(&target_row, &target_column);
			check_shot(p2_board, target_row, target_column, p1, &x, &y, &hit_or_miss);
			update_board(p2_board, x, y, hit_or_miss);
			system("pause");
			system("cls");

			check_c = check_if_sunk_ship(p2_board, 10, 10, 'c');
			check_b = check_if_sunk_ship(p2_board, 10, 10, 'b');
			check_r = check_if_sunk_ship(p2_board, 10, 10, 'r');
			check_s = check_if_sunk_ship(p2_board, 10, 10, 's');
			check_d = check_if_sunk_ship(p2_board, 10, 10, 'd');

			printf(" Player 2's sunken ships: \n");
			sunk_ship_message(check_c, 'c');
			sunk_ship_message(check_b, 'b');
			sunk_ship_message(check_r, 'r');
			sunk_ship_message(check_s, 's');
			sunk_ship_message(check_d, 'd');

			ships_p2 = is_winner(p2_board);
			output_current_move(x, y, hit_or_miss, output, p1, ships_p1);
			system("pause");
			system("cls");
			input_stats(player1[9], hit_or_miss, ships_p2);
			turn++;
		}
		else
		{
			display_board(p1_board, 10, 10, p1);
			display_board(p2_board, 10, 10, p2);
			printf(" Player 2: \n");
			random_target(&target_row, &target_column);
			check_shot(p1_board, target_row, target_column, p2, &x, &y, &hit_or_miss);
			update_board(p1_board, x, y, hit_or_miss);
			system("pause");
			system("cls");

			check_c = check_if_sunk_ship(p1_board, 10, 10, 'c');
			check_b = check_if_sunk_ship(p1_board, 10, 10, 'b');
			check_r = check_if_sunk_ship(p1_board, 10, 10, 'r');
			check_s = check_if_sunk_ship(p1_board, 10, 10, 's');
			check_d = check_if_sunk_ship(p1_board, 10, 10, 'd');

			printf(" Player 1's sunken ships: \n");
			sunk_ship_message(check_c, 'c');
			sunk_ship_message(check_b, 'b');
			sunk_ship_message(check_r, 'r');
			sunk_ship_message(check_s, 's');
			sunk_ship_message(check_d, 'd');

			ships_p2 = is_winner(p1_board);
			output_current_move(x, y, hit_or_miss, output, p2, ships_p2);
			system("pause");
			system("cls");
			input_stats(player2[9], hit_or_miss, ships_p1);
			turn++;
		}
	}
	//Determines who won
	ships_p1 = is_winner(p2_board);
	ships_p2 = is_winner(p1_board);
	if (ships_p1 == ships)
	{
		printf(" Player 1 wins!\n\n");
	}
	else
	{
		printf(" Player 2 wins!\n\n");
	}
	
	send_stats(player1[9], output, p1);
	send_stats(player2[9], output, p2);
	fclose(output);
	return 0;
 }
