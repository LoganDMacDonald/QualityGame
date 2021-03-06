#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include "main.h"

//initialize all variables
const int mapwidth = 10,mapheight=10;
char map[10][10];
int charx = 0,chary = 0, score = 0, coinx,coiny, gamestate = 1, stepcount = 0;


// Initialize simple bitmap of where walls are supposed to go
short maze[10][10]={
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,0,0,1,1,1,0},
	{0,1,0,0,0,0,0,0,1,0},
	{0,1,0,0,0,0,0,0,1,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,1,0,0,0,0,0,0,1,0},
	{0,1,0,0,0,0,0,0,1,0},
	{0,1,1,1,0,0,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0}};



// the following is the workaround for linux to be able to use getch commands

//----------------------------------------
static struct termios old, new;
/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
	tcgetattr(0, &old); /* grab old terminal i/o settings */
	new = old; /* make new settings same as old settings */
	new.c_lflag &= ~ICANON; /* disable buffered i/o */
	new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
	tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
	tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();


	return ch;
}

/* Read 1 character without echo */
char getchc() 
{
	return getch_(0);
}

//----------------------------------------


// clears the screen then prints the map array, along with other game messages
void printMap(){

	printf("\033[H\033[J");


	for(int i = 0;i<mapwidth;i++){
		for(int j = 0; j<mapheight;j++){
			printf("%c",map[i][j]);
		}
		printf("\n");
	}
	printf("Score is : %i\n",score);

	if (score == 5){
		printf("wow! half way there!");
	}

	if (score >= 10){
		printf("Congratulations! You Won!\nfinished in %i steps\nPress enter to end\n",stepcount);
		getchar();
		printf("\033[H\033[J");
		exit(0);
	}

}

//returns 1 if in bounds, 0 if out of bounds
int inBounds(int x, int y){
	if(x < mapwidth && x >= 0 && y < mapheight && y >= 0){
		return 1;
	}
	return 0;
}

//checks if space being moved to is either empty or contains a coin
int isLegalMove(int x,int y){
	if (map[x][y] ==  '*' || map[x][y] ==  '0'){return 1;}
	else {return 0;}
}

// generates a new coin in an open space
void newCoin(){


	int rx = rand()%mapwidth;
	int ry = rand()%mapheight;

	do{
		if(map[rx][ry] != '*'){
			rx = rand()%mapwidth;
			ry = rand()%mapheight;}
	} while(map[rx][ry] != '*');

	map[rx][ry] = '0';
	coinx = rx;
	coiny = ry;

}

// removes coin, updates score, calls to place a new coin
void claimCoin(int x, int y){
	if (map[x][y] == '0'){
		score++;
		newCoin();
	}

}





//checks if desired direction is a valid spot to move to, then calls to move
void movedir(int dir){


	switch(dir){
		case 1:
			if(inBounds(charx -1, chary) && isLegalMove(charx-1,chary)){
				map[charx][chary] = '*';
				charx--; 
				claimCoin(charx,chary);
				map[charx][chary] = '@';
			}
			break;
		case 2:
			if(inBounds(charx, chary+1) && isLegalMove(charx,chary+1)){
				map[charx][chary] = '*';
				chary++; 
				claimCoin(charx,chary);
				map[charx][chary] = '@';
			}
			break;

		case 3:
			if(inBounds(charx +1, chary) && isLegalMove(charx+1,chary)){
				map[charx][chary] = '*';
				charx++; 
				claimCoin(charx,chary);
				map[charx][chary] = '@';
			}
			break;
		case 4:
			if(inBounds(charx, chary-1)&& isLegalMove(charx,chary-1)){
				map[charx][chary] = '*';
				chary--; 
				claimCoin(charx,chary);
				map[charx][chary] = '@';
			}
			break;
	}
	stepcount++;
}


 //initialize the map with all asterisks and puts walls into place
void initialize_map(){



	for(int i = 0;i<mapwidth;i++){
		for(int j = 0; j<mapheight;j++){
			map[i][j] = '*';
			if(maze[i][j] == 1){
				map[i][j] = 'W';
			}

		}

	}
}


int main(){
	time_t t;
	char ch;
	srand((unsigned) time(&t)); //seed the random number generator

	//opening screen
	printf("Welcome to COIN MAN\nCollect 10 coins to win\nPress enter to continue\n");
	getchar(); //waits for user to press enter

	initialize_map();

	map[charx][chary]='@'; //puts character in place
	int choice;

	newCoin(); // places first coin

	//main game loop, continues until game stops
	while(gamestate){
		printMap();
		ch = getchc(); //immediately reads input upon keystroke



		choice = (int)ch;
		switch(choice){ // choses which direction to attempt to move
			case 52: movedir(4);break;
			case 56: movedir(1); break;
			case 54: movedir(2); break;
			case 50: movedir(3); break;
			default: {printf("List of Valid Keys\n\t 8\n 4\t\t 6\n\t 2\n"); sleep(1);}
		}

	}

	return 0;
}
