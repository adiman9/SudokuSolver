
#include<stdio.h>
#include<conio.h>

#define MIN_VALUE '1'
#define MAX_VALUE '9'
#define EMPTY_VALUE '.'
#define NUM_VALUES (MAX_VALUE - MIN_VALUE + 1)
#define GRID_SIZE (NUM_VALUES * NUM_VALUES)
#define MAX_CELL (GRID_SIZE - 1)

#define TRUE 1
#define FALSE 0

typedef char value;
typedef int cell;
typedef value sudokuGrid[GRID_SIZE];

int hasSolution(sudokuGrid game);
void readGame(int game);
void showGame(int game);
int isFull(sudokuGrid game);
int getEmptyCell(sudokuGrid game);
int isLegal(sudokuGrid game, int candidateCell, int trialValue);
void setCell(sudokuGrid game, int candidateCell, int trialValue);
void clearCell(sudokuGrid game, int candidateCell);
int topLeftColumn(sudokuGrid game, int candidateCell);
int checkBox(int randCell, sudokuGrid game, int candidateCell, int trialValue);

int main(int argc, const char * argv[]){

    sudokuGrid sample;

    readGame(sample);

    showGame(sample);
    printf("\n\n\n\n");

    if(hasSolution(sample)){
        showGame(sample);
    }

    getch();
    return 0;
}

int hasSolution(sudokuGrid game){
    int solved;
    cell candidateCell;
    value trialValue;

    if(isFull(game)){
        solved = TRUE;
    }else{
        candidateCell = getEmptyCell(game);
        trialValue = MIN_VALUE;
        solved = FALSE;
        while(!solved && (trialValue <= MAX_VALUE)){
            if(isLegal(game, candidateCell, trialValue)){
                setCell(game, candidateCell, trialValue);

                if(hasSolution(game)){
                    solved = TRUE;
                }else{
                    clearCell(game, candidateCell);
                }
            }
            trialValue++;
        }
    }
    return solved;
}

void readGame(sudokuGrid game){
    int i = 0;
    printf("Enter the grid: ");
    scanf("%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c \
          %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c \
          %c %c %c %c %c %c %c %c %c",\
          &game[0], &game[1],&game[2], &game[3], &game[4], &game[5], &game[6], &game[7], &game[8],\
          &game[9], &game[10],&game[11], &game[12], &game[13], &game[14], &game[15], &game[16], &game[17],\
          &game[18], &game[19],&game[20], &game[21], &game[22], &game[23], &game[24], &game[25], &game[26],\
          &game[27], &game[28],&game[29], &game[30], &game[31], &game[32], &game[33], &game[34], &game[35],\
          &game[36], &game[37],&game[38], &game[39], &game[40], &game[41], &game[42], &game[43], &game[44],\
          &game[45], &game[46],&game[47], &game[48], &game[49], &game[50], &game[51], &game[52], &game[53],\
          &game[54], &game[55],&game[56], &game[57], &game[58], &game[59], &game[60], &game[61], &game[62],\
          &game[63], &game[64],&game[65], &game[66], &game[67], &game[68], &game[69], &game[70], &game[71],\
          &game[72], &game[73],&game[74], &game[75], &game[76], &game[77], &game[78], &game[79], &game[80]
    );
}

void showGame(sudokuGrid game){
    int i, j;
    for(i = 0; i < 81; i++){
        if((i) % 9 == 0){
            printf("\n  ");
            for(j = 0; j < 37; j++){
                printf("%c", 196);
            }
            printf("\n  %c %c %c ", 179,  game[i], 179);
        }else{
            printf("%c %c ", game[i], 179);
        }
    }
    printf("\n  ");
    for(j = 0; j < 37; j++){
        printf("%c", 196);
    }
}

int isFull(sudokuGrid game){
    int i;

    for(i = 0; i < 81; i++){
        if(game[i] == '.'){
            return FALSE;
        }
    }
    return TRUE;
}

int getEmptyCell(sudokuGrid game){
    int i;

    for(i = 0; i < 81; i++){
        if(game[i] == '.'){
            return i;
        }
    }
}

int isLegal(sudokuGrid game, int candidateCell, int trialValue){
    int rowStart = (candidateCell/9)*9;
    int columnStart = candidateCell % 9;
    int i, k, temp;
    int topLeft;
    int topLeftElement;

    for(i = rowStart; i < (rowStart +9); i++){
        if((candidateCell != i) && (trialValue == game[i])){
            return FALSE;
        }
    }
    for(i = columnStart; i < 81; i+=9){
        if((candidateCell != i) && (trialValue == game[i])){
            return FALSE;
        }
    }

    if(candidateCell >= 0 && candidateCell < 27){

        topLeftElement = 0 +  topLeftColumn(game, candidateCell);

    }else if(candidateCell >= 27 && candidateCell < 54){

        topLeftElement = 27 +  topLeftColumn(game, candidateCell);

    }else if(candidateCell >= 54 && candidateCell < 81){

        topLeftElement = 54 +  topLeftColumn(game, candidateCell);

    }


    for(k = 0; k < 3; k++){
        int randCell = topLeftElement + k;

        temp = checkBox(randCell, game, candidateCell, trialValue);
        if(!temp){
            return FALSE;
        }
    }
    return TRUE;
}


void setCell(sudokuGrid game, int candidateCell, int trialValue){
    game[candidateCell] = trialValue;
}

void clearCell(sudokuGrid game, int candidateCell){
    game[candidateCell] = '.';
}

int topLeftColumn(sudokuGrid game, int candidateCell){
    if(candidateCell%9 >= 0 && candidateCell%9 <3){
        return 0;
    }else if(candidateCell%9 >= 3 && candidateCell%9 <6){
        return 3;
    }else if(candidateCell%9 >= 6 && candidateCell%9 <9){
        return 6;
    }
}

int checkBox(int randCell, sudokuGrid game, int candidateCell, int trialValue){
    int i;
    for(i = randCell; i < (randCell + 20); i+=9){

        if(i != candidateCell && game[i] == trialValue){
            return FALSE;
        }
    }
    return TRUE;
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Deals with top left corner of all nine smaller cells
    if ((rowStart ==(0 || 27 ||54)) && (columnStart == (0 || 3 || 6))){
    J = candiateCell;
for(J;J<(J+3);J++){
if((candidateCell != J) && (trialValue == game[J])){
            return FALSE;
        }
for(J+9;J<(J+12);J++){
if(((trialValue == game[J])){
            return FALSE;
        }
for(J+18;J<(J+21);J++){
if(((trialValue == game[J])){
            return FALSE;
        }
    }
    }





//Deals with top middle cell of all nine smaller cells
    if ((rowStart ==(9 || 36 ||63)) && (columnStart == (1 || 4 || 7))){
    J = candiateCell-1;
for(J;J<(J+3);J++){
if((candidateCell != J) && (trialValue == game[J])){
            return FALSE;
for(J+9;J<(J+12);J++){
if(((trialValue == game[J])){
            return FALSE;
for(J+18;J<(J+21);J++){
if(((trialValue == game[J])){
            return FALSE;
        }
    }

//Deals with top right cell of all nine smaller cells
    if ((rowStart ==(18 || 45 ||72)) && (columnStart == (2 || 5 || 8))){
    J = candiateCell-2;
for(J;J<(J+3);J++){
if((candidateCell != J) && (trialValue == game[J])){
            return FALSE;
for(J+9;J<(J+12);J++){
if(((trialValue == game[J])){
            return FALSE;
for(J+18;J<(J+21);J++){
if(((trialValue == game[J])){
            return FALSE;
        }
    }

    }
    return TRUE;
}

void setCell(sudokuGrid game, int candidateCell, int trialValue){
    game[candidateCell] = trialValue;
}

void clearCell(sudokuGrid game, int candidateCell){
    game[candidateCell] = '.';
}


