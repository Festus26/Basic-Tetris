#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int M,N,loc,line,score,r;
int isPlaying = 1;
int isRandom = 1;
int highScore = 0;
int gameMat[100][100] = {0};
int placeMat[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};
int blockMat0[3][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 1, 0}
};
int blockMat1[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {1, 1, 1}
};
int blockMat2[3][3] = {
    {1, 0, 0},
    {1, 0, 0},
    {1, 1, 0}
};
int blockMat3[3][3] = {
    {0, 0, 0},
    {1, 1, 0},
    {1, 1, 0}
};
int blockMat4[3][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {1, 0, 0}
};
int blockMat5[3][3] = {
    {1, 0, 0},
    {1, 0, 0},
    {1, 0, 0}
};
int blockMat6[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {1, 0, 0}
};

void matPrint();
void lineControl();
void organizeMat(int pivot);
void blockSelecter(int type);
void placer();
void rotateBlock(int mat[3][3]);
void menu();
void clearGameMat();
int blockLenght(int block[3][3]);

int main() {
    srand(time(NULL));      // Seed for rand() function
    menu:
    menu();                 //Displays menu texts and instructions
    if(isPlaying == 0) {
        goto quit;
    }
    while(isPlaying == 1) {
        if(isRandom == 1) {
            r = (rand() % 7);
        }
        isRandom = 1;
        blockSelecter(r);      //Picks a random block
        rotate:
        matPrint();                     //Prints the game area as a 2D matrix
        scanf(" %d", &loc);
        loc = loc-1;
        if(loc == -1) {
            clearGameMat();
            goto menu;
        }
        else if(loc == -2) {
            rotateBlock(placeMat);      //Rotates the given matrix
            goto rotate;
        }
        placer();                       //Checks and places the placeMat to given coordinates
    }
    printf("Game Over \nYour Score: %d\n", score);
    clearGameMat(); 
    goto menu;
    quit:
    return 0;
}

void menu() {
    if(score > highScore) {
        highScore = score;
        score = 0;
    }
    printf("\nTetris\nBest Score: %d\n", highScore);
    printf("Controls:\nType the x location (1 to N) to place the blocks\n'0' to Quit the Game\n'-1' to Rotate Blocks\n'1' to Start\n");
    int key;
    scanf(" %d", &key);
    if(key == 1) {
        isPlaying = 1;
        printf("Enter the dimensions:\n");
        printf("Rows: \n");  
        scanf(" %d", &M);
        printf("Columns: \n");
        scanf(" %d", &N);
    }
    else if( key == 0) {
        isPlaying = 0;
    }
    else {
        menu();
    }
}
void placer() {
    if( loc + blockLenght(placeMat) <= N) {             //Checks if the block fits the matrix
        //Aligns the block to the first 1
        int i = 0;
        for(i = 0; gameMat[i][loc] != 1 && i <= (M-1); i++) {
            line = i;
        }
        //Aligns the bottom of the first column of the block to the fist 1
        for(i = 2; placeMat[i][0] == 0 && line+1 < M; i--) {
            line++;
        }
        //Checks if the other columns of the block have any 1s 
        //if so places the block above of the first 1 of that column
        for(i = 2; i >= 0; i--) {
            int j = 1;
            for(j = 1; j < 3; j++) { 
                int l = 0;              
                for(l = 0; l <= line; l++) {
                    if(gameMat[l][loc+j] == 1 && placeMat[i][j] == 1) {
                        line = (l-1) + (2-i);
                        break;
                    }
                }            
            }
        }
        //Places the block to the gameMat
        for(i = 2; i >= 0 && line >= 0; i--) {
            int j = 0;
            for(j = 0; j < 3; j++) {
                if (placeMat[i][j] == 1) {
                    gameMat[line][loc+j] = 1;
                }
            }
            line--;
        }
        lineControl();      //Checks the lines if any of them is filled
    }
    else {
        isRandom = 0;
    }

}
void lineControl() {
    //if every colomn of a row is not 1 continues with the next block
    int i = 0;
    for(i = 0; i < M; i++) {
        int control = 0;
        int j = 0;
        for(j = 0; j < N; j++) {
            if(gameMat[i][j] == 1) {        
                if(i!=0) {
                    control++;                 
                }
                else {
                    isPlaying = 0;
                    break;
                }
            }
        }
        if(control == N) {      //A row is filled
            organizeMat(i);
        }
    }
}
void matPrint() {
    printf("\n");
    int i = 0;
    for(i = 0; i < M; i++) {
        int j = 0;
        for(j = 0; j < N; j++) {
            printf("%d", gameMat[i][j]);
        }
         printf("\n");
    }
    for(i = 0; i < N; i++) {
        printf("%d", ((i+1)%10));
    }
    printf("\n");
    printf("\nScore: %d\n", score);
    printf("Next piece:\n");
    i = 0;
    for(i = 0; i < 3; i++) {
        int j = 0;
        for(j = 0; j < 3; j++) {
            printf("%d", placeMat[i][j]);
        }
         printf("\n");
    }
}
void organizeMat(int pivot) {
    matPrint();
    //Destroys the filled row and brings down the upper rows
    int i = pivot;
    for(i = pivot; i > 0; i--) {
        int j = 0;
        for(j = 0; j < N; j++) {
            gameMat[i][j] = gameMat[i-1][j];
        }
    }
    score = score + N;
}
void blockSelecter(int type) {
    //Picks a random block 
    switch (type) {
        int i = 0;
        int j = 0;
        case 0:
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    placeMat[i][j] = blockMat0[i][j];
                }
            }
            break;
        case 1:
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    placeMat[i][j] = blockMat1[i][j];
                }
            }
            break;
        case 2:
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    placeMat[i][j] = blockMat2[i][j];
                }
            }
            break;
        case 3:
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    placeMat[i][j] = blockMat3[i][j];
                }
            }
            break;
        case 4:
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    placeMat[i][j] = blockMat4[i][j];
                }
            }
            break;
        case 5:
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    placeMat[i][j] = blockMat5[i][j];
                }
            }
            break;
        case 6:
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    placeMat[i][j] = blockMat6[i][j];
                }
            }
            break;
    }
}
void rotateBlock(int mat[3][3]) {
    //Transpose the matrix
    int i = 0;
    for (i = 0; i < 3; i++) {
        int j = i +1;
        for (j = i+1; j < 3; j++) {
            //Swap mat[i][j] and mat[j][i]
            int temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }
    }
    //Reverse each row
    i = 0;
    for (i = 0; i < 3; i++) {
            //Swap mat[i][start] and mat[i][end]
            int temp = mat[i][0];
            mat[i][0] = mat[i][2];
            mat[i][2] = temp;
    }
    i = 0;
    for (i = 0; i < 3; i++) {
        int j = 0;
        for (j = 0; j < 3; j++) {
            placeMat[i][j] = mat[i][j];
        }
    }
    //Arrange the block position to the left
    int c = 0;
    for(c = 0; c < 2; c++) {
        int z = 0;
        int j = 0;
        for(j = 0; j < 3; j++) {
            if(placeMat[2][j] == 1) {
                break;
            }
            else {
                z++;
                if(z == 3) {
                    int i = 2;
                    for(i = 2; i >= 0; i--) {
                        int k = 0;
                        for(k = 0; k < 3; k++) {
                            placeMat[i][k] = placeMat[i-1][k];
                        }
                    }
                }
            }
        }
    }
    //Arrange the block position to the bottom
    c = 0;
    for(c = 0; c < 2; c++) {
        int z = 0;
        int j = 0;
        for(j = 0; j < 3; j++) {
            if(placeMat[j][0] == 1) {
                break;
            }
            else {
                z++;
                if(z == 3) {
                    int i = 2;
                    for(i = 2; i >= 0; i--) {
                        int k = 0;
                        for(k = 0; k < 3; k++) {
                            placeMat[i][k] = placeMat[i][k+1];
                        }
                    }
                }
            }
        }
    }
}
int blockLenght(int block[3][3]) {
    //Calculates the lenght of a block in the x axis
    int j = 2;
    for(j = 2; j >= 0; j--) {
        int i = 0;
        for(i = 0; i < 3; i++) {
            if(block[i][j] == 1) {
                return j+1;
            }
        }
    }
    return 0;
}
void clearGameMat() {
    int i = 0;
    for(i = 0; i < M; i++) {
        int j = 0;
        for (j = 0; j < N; j++) {
            gameMat[i][j] = 0;
        }  
    }
}
