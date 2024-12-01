// 1231602667 Eray Tuna A sube

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string.h>
#define welcome_length 5
#define info_length 8
#define select_1_length 7
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE

// input olarak i girildiginde puan karsiligi bilgi ipucu alabilme ozelligi

int menuSelection; // menude gezinmemizi saglayan degisken
char difficultySelection; // zorlugu secmemizi saglayan degisken
int selectedNumber = 0; // tahmin etmemiz gereken sayi
int upperBound = 0; // zorluga gore belirlenecek ust sinir
int currentPoints = 0; // raunt icin verilecek puan
int playerGuess; // oyuncunun tahminini tutan degisken
int totalPoints = 0; // baslangictan beri kazanilan toplam puan
int sessionPoints = 0; // oyunun simdiki instance'inda kazanilan puan
char resetSelection[6]; // puani sifirlamak icin onay yazisi
char confirmation; // ekstra onay degiskeni (Y/N)

// Daktilo efekti icin gerekli bilgi yazilarinin dizileri ------------------------------------------------------
char welcome_message[welcome_length][100] = 
{ 
	{"Welcome to the number guessing game!\n"}, 
	{"Please select a mode to play\n"},
	{"1: Start guessing numbers.\n"}, 
	{"2: Check your total and current score for this session.\n"}, 
	{"3: Read how scoring is calculated.\n"} 
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
	{"Total points achieved: "},
	{"\nCurrent points achieved for this session: "}
};

char hasGuessed[3][100] =
{
	{"Alright, I have got a number! Now it's your turn to guess!\n"},
	{"Okay, I have a number in my mind! Try and find it!\n"},
	{"I have chosen a number for you! Try to guess it!\n"}
};

char errorMessage[2][100] =
{
	{"\nInvalid selection. Please Select again.\n"},
	{"\nYou failed to guess the number! No points rewarded.\n"}
};

char returnMessage[1][100] =
{
	{"Press any key to return to the main menu.\n"}
};

char resetMessage[4][100] =
{
	{"Type 'Reset' to reset your total saved score.\nType anything else to return to the main menu.\n"},
	{"\nAre you sure that you want to clear your total score? (Y/N)\n"},
	{"Score has been successfully cleared. Press any key to return to the main menu.\n"},
	{"No changes have been made. Press any key to return to the main menu.\n\n"}
};
// Daktilo efekti icin gerekli bilgi yazilarinin dizileri -------------------------------------------------------

// Daktilo efekti yaratan fonksiyon, parametre olarak iki boyutlu bir dizi(cumle sayisi ve harfler), cumle sayisi,
// 1 kez yazilip yazilmayacagini belirten boolean ve 1 kez yazilacaksa yazilacak olan dizinin indeksini alir.
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

// input buffer temizleme fonksiyonu.
void ClearBuffer()
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

void Clear(void)
{
	while (getchar() != '\n');
}

// Toplam skoru dosyaya yazan ve kaydeden fonksiyon.
void WriteScore(int score)
{
	char buffer[20];
	FILE* scoredata;
	errno_t err;
	err =  fopen_s(&scoredata, "scoredata.txt", "w");
	_itoa_s(score, buffer, 10);
	fprintf(scoredata, buffer);
	fclose(scoredata);
}

// Ilk calistirmada kayitli skoru dosyadan okuan fonksiyon
int ReadScore()
{
	char buffer[20];
	FILE* scoredata;
	errno_t err;
	err = fopen_s(&scoredata, "scoredata.txt", "r");
	totalPoints = atoi(fgets(buffer,20,scoredata));
	fclose(scoredata);
	return totalPoints;
}

int main()
{	
	while (true) // main menu loop
	{
		difficultySelection = ' ';
		system("cls");
		srand((unsigned)(time(NULL)));
		TypeWriter(welcome_message, welcome_length, false, 0);
		printf("\nSelection > ");
		scanf_s("%d", &menuSelection);

		while (true) // difficulty menu loop
		{
			if (menuSelection == 1)
			{
				if (difficultySelection == 'X' || difficultySelection == 'x') { break; }
				system("cls");
				TypeWriter(selection_1, 5, false, 0);
				printf("%d\n", ReadScore());
				TypeWriter(selection_1, 1, true, 6);
				printf("%d\n", sessionPoints);
				printf("\nDifficulty > ");
				Clear();
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
					continue;
				}
				else
				{
					TypeWriter(errorMessage, 1, true, 0);
					system("PAUSE");
					continue;
				}
				
				selectedNumber = rand() % (upperBound - 0 + 1);
				system("cls");
				printf("Current Number: %d (for debug purpose)\n", selectedNumber);
				TypeWriter(hasGuessed, 1, true, rand() % 3);
			}

			else if (menuSelection == 2)
			{
				system("cls");
				TypeWriter(selection_1, 1, true, 5);
				printf("%d\n", ReadScore());
				TypeWriter(selection_1, 1, true, 6);
				printf("%d\n", sessionPoints);
				TypeWriter(resetMessage, 1, true, 0);
				ClearBuffer();
				printf("Selection > ");
				gets_s(resetSelection, 6);

				if (!strcmp(resetSelection, "Reset") || !strcmp(resetSelection, "reset"))
				{
					printf("Selection > ");
					system("cls");
					TypeWriter(resetMessage, 1, true, 1);
					scanf_s("%c", &confirmation, 1);
					if (confirmation == 'Y' || confirmation == 'y') 
					{
						system("cls");
						WriteScore(0);
						currentPoints = 0;
						TypeWriter(resetMessage, 1, true, 2);
						system("Pause");
					}

					else
					{
						system("cls");
						TypeWriter(resetMessage, 1, true, 3);
						system("Pause");
					}
				}

				break;
			}
			
			else if (menuSelection == 3)
			{
				system("cls");
				TypeWriter(score_info_message, info_length - 1, false, 0);
				TypeWriter(returnMessage, 1, false, 0);
				system("PAUSE");
				break;
			}

			else 
			{ 
				TypeWriter(errorMessage, 1, false, 0);
				system("PAUSE");
				break;
			}
			
			while (menuSelection == 1) // game loop
			{
				printf("\nGuess > ");
				scanf_s("%d", &playerGuess);
				if (currentPoints == 0)
				{
					TypeWriter(errorMessage, 1, true, 1);
					break;
				}

				if (playerGuess == selectedNumber)
				{
					char buffer[20];
					system("cls");
					printf("Correct Guess! Current Points Achieved: %d\n", currentPoints);
					totalPoints += currentPoints;
					sessionPoints += currentPoints;
					WriteScore(totalPoints);
					system("PAUSE");
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
		}
	}

	return 0;
}