#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define arSIZE 9

char board[arSIZE];
//function prototypes
void writeFile(struct Queue *q);
void readFile();
struct QNode* newQueNode(int k);
struct Queue *createQueue();
void enQueue(struct Queue *q, int k);
int deQueFront(struct Queue *q);
void deQueBack(struct Queue *q);
struct sNode* newStackNode(int data);
int stackEmpty(struct sNode *root);
void push(struct sNode** root, int data);
int pop(struct sNode** top);
void printInstructions();
void innitBoard(char *board);
void displayBoard(char *board);
int isBoardFull(char *board);
int isBoardEmpty(char *board,int move);
void makeEmptyCell(char *board, int move);
int getMoveInput();
int checkWin(char *board);
void runPvP();
//-------------------------------------------------------LL QUEUE----------------------------------------------- 
struct QNode 
{ 
    int key; 
    struct QNode *next; 
}; 

struct Queue 
{ 
    struct QNode *front, *rear; 
}; 
   
struct QNode* newQueNode(int k) 
{ 
    struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode)); 
    temp->key = k; 
    temp->next = NULL; 
    return temp;  
} 

//create queue  
struct Queue *createQueue() 
{ 
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue)); 
    q->front = q->rear = NULL; 
    return q; 
}

//enQueue item
void enQueue(struct Queue *q, int k) 
{ 
    struct QNode *temp = newQueNode(k); 
    if (q->rear == NULL) 
    { 
       q->front = q->rear = temp; 
       return; 
    } 
    q->rear->next = temp; 
    q->rear = temp; 
} 

//deQueue item  
int deQueFront(struct Queue *q) 
{  
    int key;
    if (q->front == NULL) 
       return -1;

    key = q->front->key;
    struct QNode *temp = q->front;
    q->front = q->front->next; 
    free(temp);

    if (q->front == NULL) 
       q->rear = NULL; 
    return key; 
}
void deQueBack(struct Queue *q)
{
    if (q->rear == NULL) 
    return;

    struct QNode *temp = q->rear;
    q->rear = q->rear->next; 
    free(temp);

    if (q->rear == NULL) 
       q->front = NULL;
}

//--------------------------------------------------------END OF QUEUE-------------------------------------------

//--------------------------------------------------------LL STACK----------------------------------------------
//linked list implementation of stack
struct sNode 
{ 
    int data; 
    struct sNode* next; 
}; 
  
struct sNode* newStackNode(int data) 
{ 
    struct sNode* sNode = 
              (struct sNode*) malloc(sizeof(struct sNode)); 
    sNode->data = data; 
    sNode->next = NULL; 
    return sNode; 
} 
  
int stackEmpty(struct sNode *root) 
{ 
    return !root; 
} 
  
void push(struct sNode** root, int data) 
{ 
    struct sNode* sNode = newStackNode(data); 
    sNode->next = *root; 
    *root = sNode;  
} 
  
int pop(struct sNode** top) 
{ 
    if (stackEmpty(*top)) 
        return 0; 
    struct sNode* temp = *top; 
    *top = (*top)->next; 
    int popped = temp->data; 
    free(temp); 
  
    return popped; 
} 
  
//-------------------------------------------------- END of LL STACK----------------------------------------------------
//----------------------------------------------------START OF GAME FUNCTIONS--------------------------------------------
//instructions
void printInstructions()
{
    printf("\nChose cell from (1-9), Player[X] plays first, Player[O] is second\n\n");
    printf("\n\t     |     |     \n");
    printf("\t  1  |  2  |  3  \n");
    printf("\t_____|_____|_____\n");
    printf("\t     |     |     \n");
    printf("\t  4  |  5  |  6  \n");
    printf("\t_____|_____|_____\n");
    printf("\t     |     |     \n");
    printf("\t  7  |  8  |  9  \n");
    printf("\t     |     |     \n\n");
}

//initialise board
void innitBoard(char *board)
{
    for(int i=0; i<arSIZE; i++)
    board[i] = ' ';
}
//Dispaly board
void displayBoard(char *board)
{
    printf("\n\t     |     |     \n");
    printf("\t  %c  |  %c  |  %c  \n", board[0], board[1], board[2]);
    printf("\t_____|_____|_____\n");
    printf("\t     |     |     \n");
    printf("\t  %c  |  %c  |  %c \n", board[3], board[4], board[5]);
    printf("\t_____|_____|_____\n");
    printf("\t     |     |     \n");
    printf("\t  %c  |  %c  |  %c \n", board[6], board[7], board[8]);
    printf("\t     |     |     \n\n");
}

//update board
void updateBoard(char *board, int move,char mark)
{
    if(board[move-1]== ' ')
    {
        board[move-1] = mark;
    }
    else printf("Cell is occupied\n");
}

//checking for empty space
int isBoardFull(char *board)
{
    int i;
    for(i=0; i<arSIZE; i++)
    {
        if(board[i] == ' ')
        return 0;
    }
    return 1;
}

//checking if the place is taken
int isBoardEmpty(char *board,int move)
{
    if(board[move-1] == ' ')
    {
        return 1;
    }
    return 0;
}

void makeEmptyCell(char *board, int move)
{
    if(board[move-1]!= ' ')
    board[move-1] = ' ';
    else printf("Undo/Redo not possible\n");
}

//getting user input for the moves
int getMoveInput()
{
    int moveFlag = 0;
    int move = -1;
    while(!moveFlag)
    {
        printf("\nPlease choose cell (1-9): ");		

        if(scanf("%d",&move) <0 && scanf("%d",&move) >10)
        {
            move = -1;
            printf("\nInvalid input\n");
            continue;
        }
        moveFlag = 1;
    }
    return move;
}

//checks for a winner
int checkWin(char *board)
{
    //rows
    if(board[0] == board[1] && board[0] == board[2] && board[0] != ' ')
    {
        return 1;
    }
    if(board[3] == board[4] && board[3] == board[5] && board[3] != ' ')
    {
        return 1;
    }
    if(board[6] == board[7] && board[6] == board[8] && board[6] != ' ')
    {
        return 1;
    }
    //columns
    if(board[0] == board[3] && board[0] == board[6] && board[0] != ' ')
    {
        return 1;
    }
    if(board[1] == board[4] && board[1] == board[7] && board[1] != ' ')
    {
        return 1;
    }
    if(board[2] == board[5] && board[2] == board[8] && board[2] != ' ') 
    {
        return 1;
    }
    //diagonals
    if(board[0] == board[4] && board[0] == board[8] && board[0] != ' ')
    {
        return 1;
    }
    if(board[6] == board[4] && board[6] == board[2] && board[6] != ' ')
    {
        return 1;
    }
    return 0;
}

//PLayer vs player function game loop
void runPvP()
{
    struct Queue *newReplay = createQueue();
    struct sNode *sUndo = NULL;
    struct sNode *sRedo = NULL;
    int playFlag = 1;
    int mark = 'X';
    printInstructions();
    innitBoard(board);
    do
    {
        printf("\nPlayer[%c] turn!", mark);
        int move = getMoveInput();
        if(move > 0 && move <= 9 && isBoardEmpty(board,move)) 
        {
            updateBoard(board, move, mark);
            push(&sUndo, move);
            enQueue(newReplay,move);
            displayBoard(board);
            mark = (mark == 'X')? 'O' : 'X';
        }
        else if(move == 0)
        {
            int undoneMove;
            undoneMove = pop(&sUndo);
            push(&sRedo,undoneMove);
            deQueBack(newReplay);
            makeEmptyCell(board,undoneMove);
            displayBoard(board);
            mark = (mark == 'X')? 'O' : 'X';
        }
        else if(move == 10)
        {
            int redoMove;
            redoMove = pop(&sRedo);
            if(isBoardEmpty(board,redoMove))
            {
                updateBoard(board,redoMove,mark);
                enQueue(newReplay,redoMove);
                displayBoard(board);
                mark = (mark == 'X')? 'O' : 'X';
            }
            else printf("Undo/redo unavaialable\n");
        }
        else
        {
            printf("\nInvalid input");
        }
        
            if(checkWin(board) == 1)
            {
                mark = (mark == 'X')? 'O' : 'X';
                printf("\nPlayer[%c] is a WINNER!!!",mark);
                playFlag = 0;
                break;
            }
                if(isBoardFull(board) == 1)
                {
                    printf("\nIt is a Draw!!!\n");
                    playFlag = 0;
                    break;
                }
    }
    while(playFlag);
    {
        writeFile(newReplay);
    }

}
//-----------------------------------------------END OF GAME FUNCTIONS-----------------------------------
void readFile()
{
    char replayBoard[arSIZE];
    innitBoard(replayBoard);
    int lines = 100;
    int i,pick;
    char * token;
    char repMark = 'X';
    char **games = (char **)malloc(sizeof(char*)*lines);

    FILE *rFile = fopen("replays.txt", "r");
    if (rFile == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    else
    {
        
        for (i=0;1;i++)
        {
            int j;
            games[i] = malloc(lines);
            
            if (fgets(games[i],lines,rFile)==NULL)
                break;

            //replacing last char with full stop "\0"
            for (j=strlen(games[i])-1;j>=0 && (games[i][j]=='\n' || games[i][j]=='\r');j--)
            {
                games[i][j+1]='\0';
            }
        }
    }
    fclose(rFile);

    
    for(int x = 0; x < i; x++)
    {
        printf("Game Number %d:  %s\n", x,games[x]);
    }

    printf("Pick game number to check replay: ");
    scanf("%d", &pick);
    token = strtok(games[pick],",");
    while(token != NULL)
    {
        for(int z=0; z<strlen(token); z++)
        {
            if(atoi(token))
            {
                int m = atoi(token);
                updateBoard(replayBoard,m,repMark);
                displayBoard(replayBoard);
                repMark = (repMark == 'X') ? 'O':'X';
            }
        }

        token = strtok(NULL,",");
    }
    free(games);
}

void writeFile(struct Queue *q)
{
    int writeFlag = 1;
    FILE *wFile;
    wFile = fopen("replays.txt","a");
    if(wFile==NULL)
    {
        perror("Error opening file\n");
        exit(1);
    }
    else
    {
        do
        {
            int i = deQueFront(q);
            if(i ==-1)
            {
                writeFlag = 0;
                break;
            }
            fprintf(wFile,"%d,",i);

        }while(writeFlag);
        fprintf(wFile,"\n");
    }
    fclose(wFile);
}

int main(void)
{
    int exitFlag = 1;
    while(exitFlag)
    {
        int choice;
        printf("Choose option\nPress [1] for new game\nPress [2] to check replay\nPress [0] to quit\nChoice: ");
        scanf("%d",&choice);

        if(choice==1)
        {
            runPvP();
        }
        else if(choice==2)
        {
            readFile();
        }
        else if(choice==0)
        {
            exitFlag=0;
            break;
        }
        else if(choice != 1 || choice !=2 || choice !=0)
        {
            continue;
        }
    }
    return 0;
}