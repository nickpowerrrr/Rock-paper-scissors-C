#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const char CHOICES[3][10] = {"Rock", "Paper", "Scissors"};
const int MAX = 100;

typedef struct Player
{
    char name[128];
    char choice[50];
    int rd_num;
} Player;

void generateRandomNumbers(Player *players[], const int length)
{
    for (int i = 0; i < length; i++)
    {
        int value = (rand() % MAX);
        players[i]->rd_num = value;
    }
}

void pickRandomChoice(Player *pPlayer)
{
    int rd_num = pPlayer->rd_num;
    srand(time(0)); // set seed
    char *pChoice = pPlayer->choice;
    if (rd_num < 34)
    { // rock
        strcpy(pChoice, CHOICES[0]);
    }
    else if (rd_num > 33 && rd_num < 67)
    {
        strcpy(pChoice, CHOICES[1]);
    }
    else
    {
        strcpy(pChoice, CHOICES[2]);
    }
}

Player calculateOutCome(Player *players[], const int length)
{
    Player noPlayer = {
        "NULL",
        "NULL",
        0
    };
    Player *pLastPlayer;
    for (int i = 0; i < length; i++)
    {
        // pointer
        Player *pCurrentPlayer = players[i];
        // variables
        if (i > 0)
        {
            if (strcmp(pLastPlayer->choice,pCurrentPlayer->choice) == 0){
                return noPlayer;
            }
            if ((strcmp(pCurrentPlayer->choice, CHOICES[0])== 0 || strcmp(pCurrentPlayer->choice, CHOICES[1]) == 0) && (strcmp(pLastPlayer->choice, CHOICES[0])  == 0 || strcmp(pLastPlayer->choice, CHOICES[1]) == 0))
            { // handles rock and paper
                if (strcmp(pCurrentPlayer->choice, CHOICES[0]) ==0) // if currentplayer has rock
                {
                    return *pLastPlayer;
                    
                }
                else {
                    return *pCurrentPlayer;
                }
            } 
            if ((strcmp(pCurrentPlayer->choice, CHOICES[1])== 0 || strcmp(pCurrentPlayer->choice, CHOICES[2]) == 0) && (strcmp(pLastPlayer->choice, CHOICES[1])  == 0 || strcmp(pLastPlayer->choice, CHOICES[2]) == 0))
            { // handles paper and scissors
                if (strcmp(pCurrentPlayer->choice, CHOICES[1]) ==0) // if currentplayer has paper
                {
                    return *pLastPlayer;
                    
                }
                else {
                    return *pCurrentPlayer;
                }
            }
            if ((strcmp(pCurrentPlayer->choice, CHOICES[0])== 0 || strcmp(pCurrentPlayer->choice, CHOICES[2]) == 0) && (strcmp(pLastPlayer->choice, CHOICES[0])  == 0 || strcmp(pLastPlayer->choice, CHOICES[2]) == 0))
            { // handles rock and paper
                if (strcmp(pCurrentPlayer->choice, CHOICES[2]) ==0) // if currentplayer has scissors
                {
                    return *pLastPlayer;
                    
                }
                else {
                    return *pCurrentPlayer;
                }
            }
        }
        pLastPlayer = pCurrentPlayer;
    }
}

int main()
{

    // initialization

    srand(time(NULL)); // seed with current time
    printf("Pick your choice! %s, %s, %s\n",CHOICES[0],CHOICES[1],CHOICES[2]);
    char input[50] = "\0";
    fgets(input,sizeof(input),stdin);
    input[strlen(input) - 1] = '\0';
    Player player1 = {
        "Player1",
        "None",
        0

    };
    strcpy(player1.choice,input);
    Player player2 = {
        "Player2"
        "None",
        0};

    // pointers
    Player *pPlayer1 = &player1;
    Player *pPlayer2 = &player2;
    Player *players[] = {pPlayer1, pPlayer2};
    int length = 2;
    generateRandomNumbers(players, length);
    //pickRandomChoice(pPlayer1); If two players want to go up against eachother

    pickRandomChoice(pPlayer2);
    printf("Choice of player1 %s\n", player1.choice);
    printf("Choice of player2 %s", player2.choice);
    printf("\n\nCalculating outcome...\n");
    Player winningPlayer = calculateOutCome(players, length);
    if (strcmp(winningPlayer.name,"NULL") == 0) {
        printf("No one won! it was a draw!");
        return 0;
    }
    printf("player that won. %s",winningPlayer.name);
    return 0;
}