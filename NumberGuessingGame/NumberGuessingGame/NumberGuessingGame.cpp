// 1231602667 Eray Tuna A sube
// Tum kodu ingilizce yazma sebebim yazarken daha rahat ve uygun gelmesidir.

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


FILE* scoredata;
errno_t err;

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
	{"'M' (Medium): Guess in a range from 0 to 50\n"},
	{"'H' (hard): Guess in a range from 0 to 100\n"},
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

char hintMessage[5][100] =
{
	{"You can get a hint by typing '0' for 10 points.\n"},
	{"\nThe selected number is lower than "},
	{"\nThe selected number is higher than "},
	{"\nThe number is an odd number.\n"},
	{"\nThe number is an even number.\n"}
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
	err =  fopen_s(&scoredata, "scoredata.txt", "w");
	_itoa_s(score, buffer, 10);
	fprintf(scoredata, buffer);
	fclose(scoredata);
}

// Ilk calistirmada kayitli skoru dosyadan okuan fonksiyon
int ReadScore()
{
	if (!&scoredata)
	{
		WriteScore(0);
	}
	char buffer[20];
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
		menuSelection = NULL;
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
				printf("%d\n", ReadScore());	// display total achieved score.
				TypeWriter(selection_1, 1, true, 6);
				printf("%d\n", sessionPoints);	// display current achieveable score.
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
					upperBound = 50;
					currentPoints = 50;
				}
				else if (difficultySelection == 'H' || difficultySelection == 'h')
				{
					upperBound = 100;
					currentPoints = 100;
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
				
				selectedNumber = rand() % (upperBound - 1 + 1);
				system("cls");
				TypeWriter(hasGuessed, 1, true, rand() % 3);
				system("PAUSE");
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
				TypeWriter(errorMessage, 1, true, 0);
				system("PAUSE");
				Clear();
				break;
			}
			
			while (true) // game loop
			{
				system("cls");
				printf("Current Number: %d (for debug purpose)\n", selectedNumber);
				TypeWriter(hintMessage, 1, true, 0);
				printf("\nCurrent points: %d\n", currentPoints);
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

				else if (playerGuess == 0)
				{
					int hint; //ipucu bilgisi icin degisken

					if (difficultySelection == 'E' || difficultySelection == 'e')
					{
						if (selectedNumber % 2 == 0)
						{
							TypeWriter(hintMessage, 1, true, 4);
							currentPoints -= 3;
							printf("\nCurrent points: %d\n", currentPoints);
							system("PAUSE");
						}

						else
						{
							TypeWriter(hintMessage, 1, true, 3);
							currentPoints -= 3;
							printf("\nCurrent points: %d\n", currentPoints);
							system("PAUSE");
						}
					}
					
					else /*if (difficultySelection == 'M' || difficultySelection == 'm')*/
					{
						hint = upperBound / 2;
						if (selectedNumber > hint)
						{
							TypeWriter(hintMessage, 1, true, 2);
						}
						else
						{
							TypeWriter(hintMessage, 1, true, 1);
						}
						printf("%d\n", hint);
						currentPoints -= 10;
						system("PAUSE");
					}
				}

				else
				{
					currentPoints--;
					system("cls");
					printf("Wrong Guess! Current Points: %d\n", currentPoints);
					system("PAUSE");
					continue;
				}	
			}
		}
	}

	//	Ekran ciktisi olarak ilk calistirdiginizda menu gorursunuz.
	//	Menuden 1 girerek oyunu oynayabilir, 2 girerek simdiye kadarki skoru
	//	veya o calistirma icinde kazandiginiz skoru gorebilirsiniz.
	//	Oyun secilen zorluga gore tavan puandan baslar ve her yanlis tahminde 1 azalir.
	//	Puan karsiligi ipucu satin alabilirsiniz.
	//	Kod en basta her calistirmada scoredata.txt dosyasinda tutulan toplam skoru ceker
	//	ve en basta menude 2 ye girerek kontrol edebilirsiniz. Dosya mevcut degilse olusturur
	//	ve icinde 0 yazar. Menude 3 girerek oyunun tam aciklamasini gorebilirsiniz.

	return 0;
}