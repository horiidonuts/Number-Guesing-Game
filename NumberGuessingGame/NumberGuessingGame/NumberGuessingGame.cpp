// 1231602667 Eray Tuna A sube
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string.h>
#define welcome_length 5
#define info_length 8
#define select_1_length 6
//#define _CRT_SECURE_NO_WARNINGS

// input olarak i girildiginde puan karsiligi bilgi ipucu alabilme ozelligi

int menuSelection;
char difficultySelection;
int selectedNumber = 0;
int upperBound = 0;
int currentPoints = 0;
bool singleShot = false;
int playerGuess;
int totalPoints = 0;
int currentSessionPoints = 0;
char buffer[10];


char welcome_message[welcome_length][100] = 
{ 
	{"Welcome to the number guessing game!\n"}, 
	{"Please select a mode to play\n"},
	{"1: You guess and computer chooses\n"}, 
	{"2: You choose and computer guesses\n"}, 
	{"3: Read how scoring is calculated\n"} 
};

char score_info_message[info_length][100] = 
{ 
	{"The game is quite simple! Scoring starts with a base score that decreases with each\n"},
	{"guessing attempt. If you are guessing the number in a bigger range\n"}, 
	{"it rewards you with more points."},
	{"For example, if you are guessing\nbetween 1 to 100 it will start from 100 points and "},
	{"it will decrease\nin every guess. Once you found the right number you will be rewarded\n"},
	{"with remaining points. You can also get hints at cost"}, 
	{" of some points.\n"},
	{"\nGood luck and have fun!!\n"}
};

char selection_1[select_1_length][100] =
{
	{"Please choose a difficulty to play.\n"},
	{"'E'(Easy): Guess in a range from 0 to 25\n"},
	{"'M' (Medium): Guess in a range from 0 to 100\n"},
	{"'H' (hard): Guess in a range from 0 to 250\n"},
	{"'X' to exit to the main menu.\n(The menu accepts lowercase characters)\n"},
	{"\nTotal points achieved: "}
};

char hasGuessed[3][100] =
{
	{"Alright, I have got a number! Now it's your turn to guess!\n"},
	{"Okay, I have a number in my mind! Try and find it!\n"},
	{"I have chosen a number for you! Try to guess it!\n"}
};

char errorMessage[1][100] =
{
	{"Invalid selection. Please Select again."}
};

void TypeWriter(char text_array[][100], int array_length, bool typeOnce, int index)
{
	if (typeOnce)
	{
		for (int i = 0; text_array[index][i] != '\0'; i++)
		{
			printf("%c", text_array[index][i]);
			Sleep(5);
		}
	}

	else 
	{
		for (int i = 0; i <= array_length; i++)
		{
			for (int j = 0; text_array[i][j] != '\0'; j++)
			{
				printf("%c", text_array[i][j]);
				Sleep(5);
			}
		}
	}
}

int main()
{
	FILE* scoredata;
	errno_t err;
	err = fopen_s(&scoredata, "scoredata.txt", "w");

	if (err != 0)
	{
		printf("Failed to open the file. Error code: %d\n", err);
		return 1;
	}

	while (true) // main menu loop
	{
		difficultySelection = ' ';
		system("cls");
		srand((unsigned)(time(NULL)));
		TypeWriter(welcome_message, welcome_length, false, 0);
		printf("\nSelection > ");
		scanf_s("%d", &menuSelection);

		while (true)// difficulty menu loop
		{
			if (menuSelection == 1)
			{
				if (difficultySelection == 'X' || difficultySelection == 'x') { break; }
				system("cls");
				TypeWriter(selection_1, 5, false, 0);
				printf("%d\n", totalPoints);
				printf("\nDifficulty > ");

				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF);

				scanf_s("%c", &difficultySelection, 1);

				if (difficultySelection == 'E' || difficultySelection == 'e')
				{
					upperBound = 25;
					currentPoints = 25;
				}
				else if (difficultySelection == 'M' || difficultySelection == 'm')
				{
					upperBound = 100;
					currentPoints = 100;
				}
				else if (difficultySelection == 'H' || difficultySelection == 'h')
				{
					upperBound = 250;
					currentPoints = 250;
				}
				else if (difficultySelection == 'X' || difficultySelection == 'x')
				{
					//fclose_s(*scoredata);
					continue;
				}
				else
				{
					TypeWriter(errorMessage, 1, true, 0);
					system("PAUSE");
					continue;
				}
			}
			selectedNumber = rand() % (upperBound - 0 + 1);
			system("cls");
			printf("Current Number: %d\n", selectedNumber);
			TypeWriter(hasGuessed, 1, true, rand() % 3);
		
			while (menuSelection == 1) // game loop
			{
				printf("\nGuess > ");
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF);
				scanf_s("%d", &playerGuess);

				if (playerGuess == selectedNumber)
				{
					system("cls");
					printf("Correct Guess! Current Points Achieved: %d\n", currentPoints);
					totalPoints += currentPoints;
					//itoa(difficultySelection, buffer, 10);
					//fprintf(scoredata, buffer);
					break;
				}
				else
				{
					currentPoints--;
					system("cls");
					printf("Wrong Guess! Current Points: %d\n", currentPoints);
					continue;
				}
				
			}

			system("PAUSE");

		}
	}

	return 0;
}