#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>


const int mapwidth = 10,mapheight=10;
char map[10][10];
int charx = 0,chary = 0, score = 0, coinx,coiny;


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

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}




void printMap(){

printf("\033[H\033[J");


for(int i = 0;i<mapwidth;i++){
    for(int j = 0; j<mapheight;j++){
        printf("%c",map[i][j]);
    }
    printf("\n");
}
printf("Score is : %i\n",score);
printf("coin position: %i , %i",coinx,coiny);
}

//returns 1 if in bounds, 0 if out of bounds
int inBounds(int x, int y){
    if(x < mapwidth && x >= 0 && y < mapheight && y >= 0){
        return 1;
    }
    return 0;
}

void newCoin(){


int rx = rand()%mapwidth;
int ry = rand()%mapheight;

if(map[rx][ry] == '@'){rx= mapwidth -rx;}
map[rx][ry] = '0';
coinx = rx;
coiny = ry;
}


void claimCoin(int x, int y){
if (map[x][y] == '0'){
    score++;
    newCoin();
} 

}


void movedir(int dir){
// 1 left, 2 up , 3 right , 4 down

switch(dir){
case 1:
if(inBounds(charx -1, chary)){
    map[charx][chary] = '*';
    charx--; 
    claimCoin(charx,chary);
    map[charx][chary] = '@';
}
break;
case 2:
if(inBounds(charx, chary+1)){
    map[charx][chary] = '*';
    chary++; 
    claimCoin(charx,chary);
    map[charx][chary] = '@';
}
break;

case 3:
if(inBounds(charx +1, chary)){
    map[charx][chary] = '*';
    charx++; 
    claimCoin(charx,chary);
    map[charx][chary] = '@';
}
break;
case 4:
if(inBounds(charx, chary-1)){
    map[charx][chary] = '*';
    chary--; 
    claimCoin(charx,chary);
    map[charx][chary] = '@';
}
break;
}
}





int main(){
    time_t t;
    char ch;
srand((unsigned) time(&t));

printf("hello, welcome to MAZE GAME\n");


//initialize the map with all asterisks
for(int i = 0;i<mapwidth;i++){
    for(int j = 0; j<mapheight;j++){
       map[i][j] = '*';
    }

}
map[charx][chary]='@';
int choice;

newCoin();
while(1){
printMap();
ch = getchc();

choice = (int)ch;
switch(choice){
case 52: movedir(4);break;
case 56: movedir(1); break;
case 54: movedir(2); break;
case 50: movedir(3); break;
default: printf("not a valid key\n");
}

}

    return 0;
}