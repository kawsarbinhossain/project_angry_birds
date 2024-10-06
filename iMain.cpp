#include "iGraphics.h"
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <fstream>
#include <vector>
#include <string>
#pragma comment(lib, "winmm.lib")

#define pi 3.14159265358;
#define g .4;

bool musicOn = true;
bool isBirdFlying = false;
bool isTriplet = false;
bool isSpeed = false;

char scoreStr[10] = {'0', '0', '0', '0'};
char scoreShow[100];
char playerName[100];

int count = 0, count1 = 1, count2 = 1, count3 = 1, countY = 0, countR = 0, countB = 0;
int lvl2Count = 0;
int lvl3Count = 0;
int lvl2Count1 = 0, lvl2Count2 = 0, lvl2Count3 = 0, lvl2Count4 = 0;
int lvl3Count1 = 0, lvl3Count2 = 0, lvl3Count3 = 0, lvl3Count4 = 0;
int collision1 = 0, collision2 = 0, collision3 = 0;
int level2Collision1 = 0, level2Collision2 = 0, level2Collision3 = 0, level2Collision4 = 0;
int level3Collision1 = 0, level3Collision2 = 0, level3Collision3 = 0, level3Collision4 = 0;
int level3Collision5 = 0, level3Collision6 = 0, level3Collision7 = 0, level3Collision8 = 0;
int clickButton = 0;
int soundImage = 0;
int gameState = 1;
int indexNumber;
int playerScore = 0;
int nameCount = 0;
int difficultyEasy = 2;
int difficultyMedium = 1;
int difficultyHard = 1;
int brick[35] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int brickCheck[35] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int rx = 0, ry = 0, yx = 0, yy = 0, bx = 0, by = 0;
int rt, yt, bt;

double dotVelocity, dotAngle;
double t, x, y, z;
double dotT, redT, yellowT, blueT, yellowT1;
double angle, velocity;
double bird_x = 65.00, bird_y = 130.00;
double bird_ix = 65.0, bird_iy = 130.0;
double red_ix = 65.0, red_iy = 130.0;
double yellow_ix = 65.0, yellow_iy = 130.0;
double blue_ix = 65.0, blue_iy = 130.0;
double red_x, yellow_x, blue_x;
double red_y, yellow_y, blue_y;
double dot_x = 65, dot_y = 130;
double dot_ix = 65, dot_iy = 130;
double pig1_x = 940.00, pig1_y = 160.00;
double pig2_x = 1045.00, pig2_y = 160.00;
double pig3_x = 1160.00, pig3_y = 160.00;
double pig4_x = 830.0, pig4_y = 160.0;
double pig1 = 1, pig2 = 1, pig3 = 1, pig4 = 1;
double blue_x1, blue_y1, blue_x2, blue_y2, blue_x3, blue_y3;
double t1 = 0, t2 = 0, t3 = 0;
double launchAngle(int mx, int my);
double launchVelocity(int mx, int my);

void dotPrediction();
void projectileMotion();
void restart();
void music();
void redCollisionLevel1();
void yellowCollisionLevel1();
void blueCollisionLevel1();
void redCollisionLevel2();
void yellowCollisionLevel2();
void blueCollisionLevel2();
void redCollisionLevel3();
void yellowCollisionLevel3();
void blueCollisionLevel3();
void redBirdPlay1();
void yellowBirdPlay1();
void blueBirdPlay1();
void settingsMenu();
void playMenu();
void mainMenu();
void leaderboardMenu();
void difficultyMenu();
void soundsMenu();
void creditsMenu();
void rulesMenu();
void score();
void showScore();
void levelRestart();
void leaderboard();
void yellowSound();
void updateScore();
void floatingPig();

typedef struct
{
	char name[50];
	int score;
} Player;

void floatingPig()
{

	if (gameState == 4 && difficultyHard % 2 == 0)
	{
		if (pig1_y <= 20 || pig1_y >= 700)
			pig1 = -pig1;
		if (pig2_y <= 20 || pig2_y >= 700)
			pig2 = -pig2;
		if (pig3_y <= 20 || pig3_y >= 700)
			pig3 = -pig3;
		if (pig4_y <= 20 || pig4_y >= 700)
			pig4 = -pig4;

		pig1_y += pig1;
		pig2_y -= pig2;
		pig3_y += pig3;
		pig4_y -= pig4;
	}
}

void yellowSound()
{
	if (musicOn)
		PlaySound("music\\wood_damage_a2.wav", NULL, SND_ASYNC);
	scoreStr[2]++;
	playerScore += 10;
}

void leaderboard()
{

	Player leaderboard[10];
	int size = 0;

	FILE *file = fopen("leaderboard.txt", "r");

	if (file != NULL)
	{
		while ((size < 10) && fscanf(file, "%49[^,],%d\n", leaderboard[size].name, &leaderboard[size].score) == 2)
		{
			size++;
		}

		fclose(file);
	}

	if (size < 10)
	{
		strcpy(leaderboard[size].name, playerName);
		leaderboard[size].score = playerScore;
		size++;
	}
	else
	{
		int lowestScoreIndex = 0;

		for (int i = 1; i < 10; i++)
		{
			if (leaderboard[i].score < leaderboard[lowestScoreIndex].score)
			{
				lowestScoreIndex = i;
			}
		}

		if (playerScore > leaderboard[lowestScoreIndex].score)
		{
			strcpy(leaderboard[lowestScoreIndex].name, playerName);
			leaderboard[lowestScoreIndex].score = playerScore;
		}
	}

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (leaderboard[i].score < leaderboard[j].score)
			{
				Player temp = leaderboard[i];
				leaderboard[i] = leaderboard[j];
				leaderboard[j] = temp;
			}
		}
	}

	FILE *writeFile = fopen("leaderboard.txt", "w");

	if (writeFile != NULL)
	{
		for (int i = 0; i < size; i++)
		{
			fprintf(writeFile, "%s,%d\n", leaderboard[i].name, leaderboard[i].score);
		}

		fclose(writeFile);
	}
}

void score()
{
	if (gameState == 7)
	{
		std::ifstream inputFile("leaderboard.txt");

		if (!inputFile.is_open())
		{
			std::cerr << "Error opening file." << std::endl;
			return;
		}

		std::vector<std::string> lines; // Container for storing lines

		std::string line;
		while (std::getline(inputFile, line))
		{
			lines.push_back(line);
		}

		inputFile.close();

		int yCoordinate = 385;

		for (const auto &currentLine : lines)
		{
			iSetColor(0, 0, 0);
			iText(420, yCoordinate, const_cast<char *>(currentLine.c_str()), GLUT_BITMAP_TIMES_ROMAN_24);
			yCoordinate -= 81;
		}
		// writeScore(lines);
	}
}

void redCollisionLevel1()
{
	if ((red_x - 40 >= 1280 || red_y - 40 > 800 || red_y <= 0))
	{
		if (musicOn)
			PlaySound("music\\birdCollision01.wav", NULL, SND_ASYNC);
		iPauseTimer(x);
		restart();
	}

	if (red_x >= 900 && red_x <= 950 && red_y >= 130 && red_y <= 230 && count1 == 1)
	{
		collision1 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		count1 = 2;
		count++;
		scoreStr[1]++;
		playerScore += 100;
	}

	if (red_x >= 1000 && red_x <= 1045 && red_y >= 130 && red_y <= 230 && count2 == 1)
	{
		collision2 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		count2 = 2;
		count++;
		scoreStr[1]++;
		playerScore += 100;
	}
	if (red_x >= 1120 && red_x <= 1160 && red_y >= 130 && red_y <= 230 && count3 == 1)
	{
		collision3 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		count3 = 2;
		count++;
		scoreStr[1]++;
		playerScore += 100;
	}
}

void yellowCollisionLevel1()
{
	if ((yellow_x - 40 >= 1280 || yellow_y - 40 > 800 || yellow_y <= 0))
	{
		if (musicOn)
			PlaySound("music\\birdCollision01.wav", NULL, SND_ASYNC);
		iPauseTimer(y);
		restart();
	}

	if (yellow_x >= 900 && yellow_x <= 950 && yellow_y >= 130 && yellow_y <= 230 && count1 == 1)
	{
		collision1 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(y);
		count1 = 2;
		count++;
		scoreStr[1]++;
		playerScore += 100;
	}

	if (yellow_x >= 1000 && yellow_x <= 1045 && yellow_y >= 130 && yellow_y <= 230 && count2 == 1)
	{
		collision2 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(y);
		count2 = 2;
		count++;
		scoreStr[1]++;
		playerScore += 100;
	}
	if (yellow_x >= 1120 && yellow_x <= 1160 && yellow_y >= 130 && yellow_y <= 230 && count3 == 1)
	{
		collision3 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		count3 = 2;
		count++;
		scoreStr[1]++;
		playerScore += 100;
	}
}

void blueCollisionLevel1()
{
	if (!isTriplet)
	{
		if ((blue_x - 40 >= 1280 || blue_y - 40 > 800 || blue_y <= 0))
		{
			if (musicOn)
				PlaySound("music\\birdCollision01.wav", NULL, SND_ASYNC);
			iPauseTimer(z);
			restart();
		}

		if (blue_x >= 900 && blue_x <= 950 && blue_y >= 130 && blue_y <= 230 && count1 == 1)
		{
			collision1 = 1;
			if (musicOn)
				PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
			restart();
			iPauseTimer(z);
			count1 = 2;
			count++;
			scoreStr[1]++;
			playerScore += 100;
		}

		if (blue_x >= 1000 && blue_x <= 1045 && blue_y >= 130 && blue_y <= 230 && count2 == 1)
		{
			collision2 = 1;
			if (musicOn)
				PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
			restart();
			iPauseTimer(z);
			count2 = 2;
			count++;
			scoreStr[1]++;
			playerScore += 100;
		}
		if (blue_x >= 1120 && blue_x <= 1160 && blue_y >= 130 && blue_y <= 230 && count3 == 1)
		{
			collision3 = 1;
			if (musicOn)
				PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
			restart();
			iPauseTimer(z);
			count3 = 2;
			count++;
			scoreStr[1]++;
			playerScore += 100;
		}
	}

	if (isTriplet)
	{

		if ((blue_x1 - 40 >= 1280 || blue_y1 - 40 > 800 || blue_y1 <= 50) &&
				(blue_x2 - 40 >= 1280 || blue_y2 - 40 > 800 || blue_y2 <= 50) &&
				(blue_x3 - 40 >= 1280 || blue_y3 - 40 > 800 || blue_y3 <= 50))
		{
			if (musicOn)
				PlaySound("music\\birdCollision01.wav", NULL, SND_ASYNC);
			iPauseTimer(z);
			restart();
		}

		if (count1 == 1 && (blue_x1 >= 900 && blue_x1 <= 950 && blue_y1 >= 130 && blue_y1 <= 230) ||
				(blue_x2 >= 900 && blue_x2 <= 950 && blue_y2 >= 130 && blue_y2 <= 230) ||
				(blue_x3 >= 900 && blue_x3 <= 950 && blue_y3 >= 130 && blue_y3 <= 230))
		{
			collision1 = 1;
			if (musicOn)
				PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
			count1 = 2;
			count++;
			scoreStr[1]++;
			playerScore += 100;
		}

		if (count2 == 1 && (blue_x1 >= 1000 && blue_x1 <= 1045 && blue_y1 >= 130 && blue_y1 <= 230) ||
				(blue_x2 >= 1000 && blue_x2 <= 1045 && blue_y2 >= 130 && blue_y2 <= 230) ||
				(blue_x3 >= 1000 && blue_x3 <= 1045 && blue_y3 >= 130 && blue_y3 <= 230))
		{
			collision2 = 1;
			if (musicOn)
				PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
			count2 = 2;
			count++;
			scoreStr[1]++;
			playerScore += 100;
		}
		if (count3 == 1 && (blue_x1 >= 1120 && blue_x1 <= 1160 && blue_y1 >= 130 && blue_y1 <= 230) ||
				(blue_x2 >= 1120 && blue_x2 <= 1160 && blue_y2 >= 130 && blue_y2 <= 230) ||
				(blue_x3 >= 1120 && blue_x3 <= 1160 && blue_y3 >= 130 && blue_y3 <= 230))
		{
			collision3 = 1;
			if (musicOn)
				PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
			count3 = 2;
			count++;
			scoreStr[1]++;
			playerScore += 100;
		}
	}
}

void redCollisionLevel2()
{

	if ((red_x - 40 >= 1280 || red_y - 40 > 800 || red_y <= 0))
	{
		if (musicOn)
			PlaySound("music\\birdCollision01.wav", NULL, SND_ASYNC);
		iPauseTimer(x);
		restart();
	}
	if (lvl2Count2 == 0 && red_x >= 830 && red_x <= 880 && red_y >= 30 && red_y <= 120)
	{
		level2Collision2 = 1;
		lvl2Count2 = 1;
		lvl2Count++;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		scoreStr[1]++;
		playerScore += 100;
	}
	if (lvl2Count1 == 0 && red_x >= 980 && red_x <= 1030 && red_y >= 80 && red_y <= 165)
	{
		level2Collision1 = 1;
		lvl2Count1 = 1;
		lvl2Count++;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		scoreStr[1]++;
		playerScore += 100;
	}
	if (lvl2Count3 == 0 && red_x >= 1090 && red_x <= 1140 && red_y >= 60 && red_y <= 145)
	{
		level2Collision3 = 1;
		lvl2Count3 = 1;
		lvl2Count++;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		scoreStr[1]++;
		playerScore += 100;
	}
	if (lvl2Count4 == 0 && red_x >= 980 && red_x <= 1030 && red_y >= 150 && red_y <= 235)
	{
		level2Collision4 = 1;
		lvl2Count4 = 1;
		lvl2Count++;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		scoreStr[1]++;
		playerScore += 100;
	}
	if (brickCheck[0] == 0 && red_x >= 790 && red_x <= 840 && red_y >= -10 && red_y <= 75)
	{
		brickCheck[0] = 1;
		brick[0] = 1;
		yellowSound();
	}
	if (brickCheck[1] == 0 && red_x >= 840 && red_x <= 880 && red_y >= -10 && red_y <= 55)
	{
		brickCheck[1] = 1;
		brick[1] = 1;
		yellowSound();
	}
	if (brickCheck[2] == 0 && red_x >= 880 && red_x <= 920 && red_y >= -10 && red_y <= 55)
	{
		brickCheck[2] = 1;
		brick[2] = 1;
		yellowSound();
	}
	if (brickCheck[3] == 0 && red_x >= 920 && red_x <= 960 && red_y >= -10 && red_y <= 55)
	{
		brickCheck[3] = 1;
		brick[3] = 1;
		yellowSound();
	}
	if (brickCheck[4] == 0 && red_x >= 980 && red_x <= 1020 && red_y >= -10 && red_y <= 75)
	{
		brickCheck[4] = 1;
		brick[4] = 1;
		yellowSound();
	}
	if (brickCheck[5] == 0 && red_x >= 1050 && red_x <= 1070 && red_y >= -10 && red_y <= 75)
	{
		brickCheck[5] = 1;
		brick[5] = 1;
		yellowSound();
	}
	if (brickCheck[6] == 0 && red_x >= 1150 && red_x <= 1170 && red_y >= -10 && red_y <= 75)
	{
		brickCheck[6] = 1;
		brick[6] = 1;
		yellowSound();
	}
	if (brickCheck[7] == 0 && red_x >= 840 && red_x <= 880 && red_y >= 15 && red_y <= 75)
	{
		brickCheck[7] = 1;
		brick[7] = 1;
		yellowSound();
	}
	if (brickCheck[8] == 0 && red_x >= 880 && red_x <= 920 && red_y >= 15 && red_y <= 75)
	{
		brickCheck[8] = 1;
		brick[8] = 1;
		yellowSound();
	}
	if (brickCheck[9] == 0 && red_x >= 920 && red_x <= 960 && red_y >= 15 && red_y <= 75)
	{
		brickCheck[9] = 1;
		brick[9] = 1;
		yellowSound();
	}
	if (brickCheck[10] == 0 && red_x >= 880 && red_x <= 920 && red_y >= 30 && red_y <= 120)
	{
		brickCheck[10] = 1;
		brick[10] = 1;
		yellowSound();
	}
	if (brickCheck[11] == 0 && red_x >= 930 && red_x <= 975 && red_y >= 30 && red_y <= 100)
	{
		brickCheck[11] = 1;
		brick[11] = 1;
		yellowSound();
	}
	if (brickCheck[12] == 0 && red_x >= 975 && red_x <= 1020 && red_y >= 30 && red_y <= 100)
	{
		brickCheck[12] = 1;
		brick[12] = 1;
		yellowSound();
	}
	if (brickCheck[13] == 0 && red_x >= 1020 && red_x <= 1065 && red_y >= 30 && red_y <= 100)
	{
		brickCheck[13] = 1;
		brick[13] = 1;
		yellowSound();
	}
	if (brickCheck[14] == 0 && red_x >= 1065 && red_x <= 1110 && red_y >= 30 && red_y <= 100)
	{
		brickCheck[14] = 1;
		brick[14] = 1;
		yellowSound();
	}
	if (brickCheck[15] == 0 && red_x >= 1110 && red_x <= 1155 && red_y >= 30 && red_y <= 100)
	{
		brickCheck[15] = 1;
		brick[15] = 1;
		yellowSound();
	}
	if (brickCheck[16] == 0 && red_x >= 930 && red_x <= 975 && red_y >= 100 && red_y <= 120)
	{
		brickCheck[16] = 1;
		brick[16] = 1;
		yellowSound();
	}
	if (brickCheck[17] == 0 && red_x >= 975 && red_x <= 1020 && red_y >= 100 && red_y <= 120)
	{
		brickCheck[17] = 1;
		brick[17] = 1;
		yellowSound();
	}
	if (brickCheck[18] == 0 && red_x >= 1020 && red_x <= 1065 && red_y >= 100 && red_y <= 120)
	{
		brickCheck[18] = 1;
		brick[18] = 1;
		yellowSound();
	}
	if (brickCheck[19] == 0 && red_x >= 930 && red_x <= 950 && red_y >= 75 && red_y <= 165)
	{
		brickCheck[19] = 1;
		brick[19] = 1;
		yellowSound();
	}
	if (brickCheck[20] == 0 && red_x >= 1050 && red_x <= 1070 && red_y >= 75 && red_y <= 165)
	{
		brickCheck[20] = 1;
		brick[20] = 1;
		yellowSound();
	}
	if (brickCheck[21] == 0 && red_x >= 930 && red_x <= 975 && red_y >= 125 && red_y <= 190)
	{
		brickCheck[21] = 1;
		brick[21] = 1;
		yellowSound();
	}
	if (brickCheck[22] == 0 && red_x >= 975 && red_x <= 1020 && red_y >= 125 && red_y <= 190)
	{
		brickCheck[22] = 1;
		brick[22] = 1;
		yellowSound();
	}
	if (brickCheck[23] == 0 && red_x >= 1020 && red_x <= 1065 && red_y >= 125 && red_y <= 190)
	{
		brickCheck[23] = 1;
		brick[23] = 1;
		yellowSound();
	}
	if (brickCheck[24] == 0 && red_x >= 930 && red_x <= 950 && red_y >= 150 && red_y <= 240)
	{
		brickCheck[24] = 1;
		brick[24] = 1;
		yellowSound();
	}
	if (brickCheck[25] == 0 && red_x >= 1050 && red_x <= 1070 && red_y >= 150 && red_y <= 240)
	{
		brickCheck[25] = 1;
		brick[25] = 1;
		yellowSound();
	}
	if (brickCheck[26] == 0 && red_x >= 930 && red_x <= 975 && red_y >= 195 && red_y <= 260)
	{
		brickCheck[26] = 1;
		brick[26] = 1;
		yellowSound();
	}
	if (brickCheck[27] == 0 && red_x >= 975 && red_x <= 1020 && red_y >= 195 && red_y <= 260)
	{
		brickCheck[27] = 1;
		brick[27] = 1;
		yellowSound();
	}
	if (brickCheck[28] == 0 && red_x >= 1020 && red_x <= 1065 && red_y >= 195 && red_y <= 260)
	{
		brickCheck[28] = 1;
		brick[28] = 1;
		yellowSound();
	}
	if (brickCheck[29] == 0 && red_x >= 930 && red_x <= 975 && red_y >= 215 && red_y <= 305)
	{
		brickCheck[29] = 1;
		brick[29] = 1;
		yellowSound();
	}
	if (brickCheck[30] == 0 && red_x >= 975 && red_x <= 995 && red_y >= 215 && red_y <= 305)
	{
		brickCheck[30] = 1;
		brick[30] = 1;
		yellowSound();
	}
	if (brickCheck[31] == 0 && red_x >= 995 && red_x <= 1020 && red_y >= 215 && red_y <= 305)
	{
		brickCheck[31] = 1;
		brick[31] = 1;
		yellowSound();
	}
	if (brickCheck[32] == 0 && red_x >= 1020 && red_x <= 1055 && red_y >= 215 && red_y <= 305)
	{
		brickCheck[32] = 1;
		brick[32] = 1;
		yellowSound();
	}
}

void yellowCollisionLevel2()
{
	if ((yellow_x - 40 >= 1280 || yellow_y - 40 > 800 || yellow_y <= 0))
	{
		if (musicOn)
			PlaySound("music\\birdCollision01.wav", NULL, SND_ASYNC);
		iPauseTimer(x);
		restart();
	}
	if (lvl2Count2 == 0 && yellow_x >= 830 && yellow_x <= 880 && yellow_y >= 30 && yellow_y <= 120)
	{
		level2Collision2 = 1;
		lvl2Count2 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		scoreStr[2]++;
		playerScore += 10;
	}
	if (lvl2Count1 == 0 && yellow_x >= 980 && yellow_x <= 1030 && yellow_y >= 80 && yellow_y <= 165)
	{
		level2Collision1 = 1;
		lvl2Count1 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		scoreStr[2]++;
		playerScore += 10;
	}
	if (lvl2Count3 == 0 && yellow_x >= 1090 && yellow_x <= 1140 && yellow_y >= 60 && yellow_y <= 145)
	{
		level2Collision3 = 1;
		lvl2Count3 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		scoreStr[2]++;
		playerScore += 10;
	}
	if (lvl2Count4 == 0 && yellow_x >= 980 && yellow_x <= 1030 && yellow_y >= 150 && yellow_y <= 235)
	{
		level2Collision4 = 1;
		lvl2Count4 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		scoreStr[2]++;
		playerScore += 10;
	}
	if (brickCheck[0] == 0 && yellow_x >= 790 && yellow_x <= 840 && yellow_y >= -10 && yellow_y <= 75)
	{
		brickCheck[0] = 1;
		brick[0] = 1;
		yellowSound();
	}
	if (brickCheck[1] == 0 && yellow_x >= 840 && yellow_x <= 880 && yellow_y >= -10 && yellow_y <= 55)
	{
		brickCheck[1] = 1;
		brick[1] = 1;
		yellowSound();
	}
	if (brickCheck[2] == 0 && yellow_x >= 880 && yellow_x <= 920 && yellow_y >= -10 && yellow_y <= 55)
	{
		brickCheck[2] = 1;
		brick[2] = 1;
		yellowSound();
	}
	if (brickCheck[3] == 0 && yellow_x >= 920 && yellow_x <= 960 && yellow_y >= -10 && yellow_y <= 55)
	{
		brickCheck[3] = 1;
		brick[3] = 1;
		yellowSound();
	}
	if (brickCheck[4] == 0 && yellow_x >= 980 && yellow_x <= 1020 && yellow_y >= -10 && yellow_y <= 75)
	{
		brickCheck[4] = 1;
		brick[4] = 1;
		yellowSound();
	}
	if (brickCheck[5] == 0 && yellow_x >= 1050 && yellow_x <= 1070 && yellow_y >= -10 && yellow_y <= 75)
	{
		brickCheck[5] = 1;
		brick[5] = 1;
		yellowSound();
	}
	if (brickCheck[6] == 0 && yellow_x >= 1150 && yellow_x <= 1170 && yellow_y >= -10 && yellow_y <= 75)
	{
		brickCheck[6] = 1;
		brick[6] = 1;
		yellowSound();
	}
	if (brickCheck[7] == 0 && yellow_x >= 840 && yellow_x <= 880 && yellow_y >= 15 && yellow_y <= 75)
	{
		brickCheck[7] = 1;
		brick[7] = 1;
		yellowSound();
	}
	if (brickCheck[8] == 0 && yellow_x >= 880 && yellow_x <= 920 && yellow_y >= 15 && yellow_y <= 75)
	{
		brickCheck[8] = 1;
		brick[8] = 1;
		yellowSound();
	}
	if (brickCheck[9] == 0 && yellow_x >= 920 && yellow_x <= 960 && yellow_y >= 15 && yellow_y <= 75)
	{
		brickCheck[9] = 1;
		brick[9] = 1;
		yellowSound();
	}
	if (brickCheck[10] == 0 && yellow_x >= 880 && yellow_x <= 920 && yellow_y >= 30 && yellow_y <= 120)
	{
		brickCheck[10] = 1;
		brick[10] = 1;
		yellowSound();
	}
	if (brickCheck[11] == 0 && yellow_x >= 930 && yellow_x <= 975 && yellow_y >= 30 && yellow_y <= 100)
	{
		brickCheck[11] = 1;
		brick[11] = 1;
		yellowSound();
	}
	if (brickCheck[12] == 0 && yellow_x >= 975 && yellow_x <= 1020 && yellow_y >= 30 && yellow_y <= 100)
	{
		brickCheck[12] = 1;
		brick[12] = 1;
		yellowSound();
	}
	if (brickCheck[13] == 0 && yellow_x >= 1020 && yellow_x <= 1065 && yellow_y >= 30 && yellow_y <= 100)
	{
		brickCheck[13] = 1;
		brick[13] = 1;
		yellowSound();
	}
	if (brickCheck[14] == 0 && yellow_x >= 1065 && yellow_x <= 1110 && yellow_y >= 30 && yellow_y <= 100)
	{
		brickCheck[14] = 1;
		brick[14] = 1;
		yellowSound();
	}
	if (brickCheck[15] == 0 && yellow_x >= 1110 && yellow_x <= 1155 && yellow_y >= 30 && yellow_y <= 100)
	{
		brickCheck[15] = 1;
		brick[15] = 1;
		yellowSound();
	}
	if (brickCheck[16] == 0 && yellow_x >= 930 && yellow_x <= 975 && yellow_y >= 100 && yellow_y <= 120)
	{
		brickCheck[16] = 1;
		brick[16] = 1;
		yellowSound();
	}
	if (brickCheck[17] == 0 && yellow_x >= 975 && yellow_x <= 1020 && yellow_y >= 100 && yellow_y <= 120)
	{
		brickCheck[17] = 1;
		brick[17] = 1;
	}
	yellowSound();
	if (brickCheck[18] == 0 && yellow_x >= 1020 && yellow_x <= 1065 && yellow_y >= 100 && yellow_y <= 120)
	{
		brickCheck[18] = 1;
		brick[18] = 1;
		yellowSound();
	}
	if (brickCheck[19] == 0 && yellow_x >= 930 && yellow_x <= 950 && yellow_y >= 75 && yellow_y <= 165)
	{
		brickCheck[19] = 1;
		brick[19] = 1;
		yellowSound();
	}
	if (brickCheck[20] == 0 && yellow_x >= 1050 && yellow_x <= 1070 && yellow_y >= 75 && yellow_y <= 165)
	{
		brickCheck[20] = 1;
		brick[20] = 1;
		yellowSound();
	}
	if (brickCheck[21] == 0 && yellow_x >= 930 && yellow_x <= 975 && yellow_y >= 125 && yellow_y <= 190)
	{
		brickCheck[21] = 1;
		brick[21] = 1;
		yellowSound();
	}
	if (brickCheck[22] == 0 && yellow_x >= 975 && yellow_x <= 1020 && yellow_y >= 125 && yellow_y <= 190)
	{
		brickCheck[22] = 1;
		brick[22] = 1;
	}
	if (brickCheck[23] == 0 && yellow_x >= 1020 && yellow_x <= 1065 && yellow_y >= 125 && yellow_y <= 190)
	{
		brickCheck[23] = 1;
		brick[23] = 1;
		yellowSound();
	}
	if (brickCheck[24] == 0 && yellow_x >= 930 && yellow_x <= 950 && yellow_y >= 150 && yellow_y <= 240)
	{
		brickCheck[24] = 1;
		brick[24] = 1;
		yellowSound();
	}
	if (brickCheck[25] == 0 && yellow_x >= 1050 && yellow_x <= 1070 && yellow_y >= 150 && yellow_y <= 240)
	{
		brickCheck[25] = 1;
		brick[25] = 1;
		yellowSound();
	}
	if (brickCheck[26] == 0 && yellow_x >= 930 && yellow_x <= 975 && yellow_y >= 195 && yellow_y <= 260)
	{
		brickCheck[26] = 1;
		brick[26] = 1;
		yellowSound();
	}
	if (brickCheck[27] == 0 && yellow_x >= 975 && yellow_x <= 1020 && yellow_y >= 195 && yellow_y <= 260)
	{
		brickCheck[27] = 1;
		brick[27] = 1;
		yellowSound();
	}
	if (brickCheck[28] == 0 && yellow_x >= 1020 && yellow_x <= 1065 && yellow_y >= 195 && yellow_y <= 260)
	{
		brickCheck[28] = 1;
		brick[28] = 1;
		yellowSound();
	}
	if (brickCheck[29] == 0 && yellow_x >= 930 && yellow_x <= 975 && yellow_y >= 215 && yellow_y <= 305)
	{
		brickCheck[29] = 1;
		brick[29] = 1;
	}
	if (brickCheck[30] == 0 && yellow_x >= 975 && yellow_x <= 995 && yellow_y >= 215 && yellow_y <= 305)
	{
		brickCheck[30] = 1;
		brick[30] = 1;
		yellowSound();
	}
	if (brickCheck[31] == 0 && yellow_x >= 995 && yellow_x <= 1020 && yellow_y >= 215 && yellow_y <= 305)
	{
		brickCheck[31] = 1;
		brick[31] = 1;
		yellowSound();
	}
	if (brickCheck[32] == 0 && yellow_x >= 1020 && yellow_x <= 1055 && yellow_y >= 215 && yellow_y <= 305)
	{
		brickCheck[32] = 1;
		brick[32] = 1;
		yellowSound();
	}
}

void blueCollisionLevel2()
{
}

void redCollisionLevel3()
{
	printf(" %lf %lf \n", pig1_x, pig1_y);
	printf(" %lf %lf \n", red_x, red_y);
	if ((red_x - 40 >= 1280 || red_y - 40 > 800 || red_y <= 0))
	{
		if (musicOn)
			PlaySound("music\\birdCollision01.wav", NULL, SND_ASYNC);
		iPauseTimer(x);
		restart();
	}
	if (lvl3Count1 == 0 && red_x + 70 >= pig1_x && red_x - 70 <= pig1_x && red_y + 70 >= pig1_y && red_y - 70 <= pig1_y)
	{
		level3Collision1 = 1;
		lvl3Count++;
		lvl3Count1 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		lvl3Count++;
		scoreStr[1]++;
		playerScore += 100;
	}
	if (lvl3Count2 == 0 && red_x + 70 >= pig2_x && red_x - 70 <= pig2_x && red_y + 70 >= pig2_y && red_y - 70 <= pig2_y)
	{
		level3Collision2 = 1;
		lvl3Count++;
		lvl3Count2 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		scoreStr[1]++;
		playerScore += 100;
	}
	if (lvl3Count3 == 0 && red_x + 70 >= pig3_x && red_x - 70 <= pig3_x && red_y + 70 >= pig3_y && red_y - 70 <= pig3_y)
	{
		level3Collision3 = 1;
		lvl3Count++;
		lvl3Count3 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		scoreStr[1]++;
		playerScore += 100;
	}
	if (lvl3Count4 == 0 && red_x + 70 >= pig4_x && red_x - 70 <= pig4_x && red_y + 70 >= pig4_y && red_y - 70 <= pig4_y)
	{
		level3Collision4 = 1;
		lvl3Count++;
		lvl3Count4 = 1;
		if (musicOn)
			PlaySound("music\\pigletteDamage.wav", NULL, SND_ASYNC);
		restart();
		iPauseTimer(x);
		scoreStr[1]++;
		playerScore += 100;
	}
}

void redBirdPlay1()
{
	if (gameState == 4 && difficultyEasy % 2 == 0)
	{
		iShowBMP(0, 0, "images\\Play03.bmp");
		iShowBMP2(red_x, red_y, "images\\redBird.bmp", 0);
		if (collision1 != 1)
			iShowBMP2(940, 160, "images\\pig02.bmp", 0);
		if (collision2 != 1)
			iShowBMP2(1045, 160, "images\\pig02.bmp", 0);
		if (collision3 != 1)
			iShowBMP2(1160, 160, "images\\pig02.bmp", 0);
		if (countR == 0 || countR == 1)
		{
			iShowBMP2(00, 40, "images\\redBird.bmp", 0);
			iShowBMP2(40, 40, "images\\redBird.bmp", 0);
			iShowBMP2(80, 40, "images\\redBird.bmp", 0);
		}
		if (countR == 2 || countR == 3)
		{
			iShowBMP2(40, 40, "images\\redBird.bmp", 0);
			iShowBMP2(80, 40, "images\\redBird.bmp", 0);
		}
		if (countR == 4 || countR == 5)
			iShowBMP2(80, 40, "images\\redBird.bmp", 0);

		if (countR <= 8 && count == 3)
		{
			iShowBMP(0, 0, "images\\PlayWin.bmp");
			if (musicOn)
				PlaySound("music\\levelCleared.wav", NULL, SND_SYNC);
		}
		if (countR > 7 && count != 3)
		{
			iShowBMP(0, 0, "images\\PlayLost.bmp");
			if (musicOn)
				PlaySound("music\\levelFailed.wav", NULL, SND_SYNC);
		}
	}
}

void yellowBirdPlay1()
{
	if (gameState == 5 && difficultyEasy % 2 == 0)
	{
		iShowBMP(0, 0, "images\\PLay03.bmp");
		iShowBMP2(yellow_x, yellow_y, "images\\yellowBird.bmp", 0);

		if (collision1 != 1)
			iShowBMP2(pig1_x, pig1_y, "images\\pig02.bmp", 0);
		if (collision2 != 1)
			iShowBMP2(pig1_x + 105, pig1_y, "images\\pig02.bmp", 0);
		if (collision3 != 1)
			iShowBMP2(pig1_x + 220, pig1_y, "images\\pig02.bmp", 0);

		if ((countY == 0) || countY == 1)
		{
			iShowBMP2(00, 40, "images\\yellowBird.bmp", 0);
			iShowBMP2(40, 40, "images\\yellowBird.bmp", 0);
			iShowBMP2(80, 40, "images\\yellowBird.bmp", 0);
		}

		if ((countY == 2) || countY == 3)
		{
			iShowBMP2(40, 40, "images\\yellowBird.bmp", 0);
			iShowBMP2(80, 40, "images\\yellowBird.bmp", 0);
		}
		if ((countY == 4) || countY == 5)
			iShowBMP2(80, 40, "images\\yellowBird.bmp", 0);

		if (countY <= 8 && count == 3)
		{
			iShowBMP(0, 0, "images\\PlayWin.bmp");
			if (musicOn)
				PlaySound("music\\playWin.wav", NULL, SND_SYNC);
		}
		if (countY > 7 && count != 3)
		{
			iShowBMP(0, 0, "images\\PlayLost.bmp");
			if (musicOn)
				PlaySound("music\\levelFailed.wav", NULL, SND_SYNC);
		}
	}
}

void blueBirdPlay1()
{

	if (gameState == 6 && difficultyEasy % 2 == 0)
	{
		iShowBMP(0, 0, "images\\Play03.bmp");
		if (!isTriplet)
		{
			iShowBMP2(blue_x, blue_y, "images\\blueBird.bmp", 0);
		}
		if (isTriplet)
		{
			iShowBMP2(blue_x1, blue_y1, "images\\blueBird.bmp", 0);
			iShowBMP2(blue_x2, blue_y2, "images\\blueBird.bmp", 0);
			iShowBMP2(blue_x3, blue_y3, "images\\blueBird.bmp", 0);
		}
		if (collision1 != 1)
			iShowBMP2(pig1_x, pig1_y, "images\\pig02.bmp", 0);
		if (collision2 != 1)
			iShowBMP2(pig1_x + 105, pig1_y, "images\\pig02.bmp", 0);
		if (collision3 != 1)
			iShowBMP2(pig1_x + 220, pig1_y, "images\\pig02.bmp", 0);

		if ((countB == 0) || countB == 1)
		{
			iShowBMP2(00, 40, "images\\blueBird.bmp", 0);
			iShowBMP2(40, 40, "images\\blueBird.bmp", 0);
			iShowBMP2(80, 40, "images\\blueBird.bmp", 0);
		}
		if ((countB == 2) || countB == 3)
		{
			iShowBMP2(40, 40, "images\\blueBird.bmp", 0);
			iShowBMP2(80, 40, "images\\blueBird.bmp", 0);
		}
		if ((countB == 4) || countB == 5)
			iShowBMP2(80, 40, "images\\blueBird.bmp", 0);

		if (countB <= 8 && count == 3)
		{
			iShowBMP(0, 0, "images\\PlayWin.bmp");
			if (musicOn)
				PlaySound("music\\playWin.wav", NULL, SND_SYNC);
		}
		if (countB > 7 && count != 3)
		{
			iShowBMP(0, 0, "images\\PlayLost.bmp");
			if (musicOn)
				PlaySound("music\\levelFailed.wav", NULL, SND_SYNC);
		}
	}
}

void redBirdPlay2()
{
	if (gameState == 4 && difficultyMedium % 2 == 0)
	{
		iShowBMP(0, 0, "images\\level2.bmp");
		iShowBMP2(red_x, red_y, "images\\redBird.bmp", 0);
		if (level2Collision1 != 1)
			iShowBMP2(1020, 122, "images\\pig02.bmp", 0);
		if (level2Collision4 != 1)
			iShowBMP2(1020, 190, "images\\pig02.bmp", 0);
		if (level2Collision3 != 1)
			iShowBMP2(1135, 100, "images\\pig02.bmp", 0);
		if (level2Collision2 != 1)
			iShowBMP2(875, 75, "images\\pig02.bmp", 0);
		if (brick[0] == 0)
			iShowBMP2(830, 30, "images\\woodTri1.bmp", 0);
		if (brick[1] == 0)
			iShowBMP2(876, 30, "images\\woodBox.bmp", 0);
		if (brick[2] == 0)
			iShowBMP2(924, 30, "images\\woodBox.bmp", 0);
		if (brick[3] == 0)
			iShowBMP2(972, 30, "images\\woodBox.bmp", 0);
		if (brick[4] == 0)
			iShowBMP2(1020, 30, "images\\woodTri2.bmp", 0);
		if (brick[5] == 0)
			iShowBMP2(1094, 30, "images\\woodPillar.bmp", 0);
		if (brick[6] == 0)
			iShowBMP2(1190, 30, "images\\woodPillar.bmp", 0);
		if (brick[7] == 0)
			iShowBMP2(876, 53, "images\\woodBox.bmp", 0);
		if (brick[8] == 0)
			iShowBMP2(924, 53, "images\\woodBox.bmp", 0);
		if (brick[9] == 0)
			iShowBMP2(972, 53, "images\\woodBox.bmp", 0);
		if (brick[10] == 0)
			iShowBMP2(924, 76, "images\\woodTri1.bmp", 0);
		if (brick[11] == 0)
			iShowBMP2(972, 76, "images\\woodBox.bmp", 0);
		if (brick[12] == 0)
			iShowBMP2(1020, 76, "images\\woodBox.bmp", 0);
		if (brick[13] == 0)
			iShowBMP2(1068, 76, "images\\woodBox.bmp", 0);
		if (brick[14] == 0)
			iShowBMP2(1116, 76, "images\\woodBox.bmp", 0);
		if (brick[15] == 0)
			iShowBMP2(1164, 76, "images\\woodBox.bmp", 0);
		if (brick[16] == 0)
			iShowBMP2(972, 99, "images\\woodBox.bmp", 0);
		if (brick[17] == 0)
			iShowBMP2(1020, 99, "images\\woodBox.bmp", 0);
		if (brick[18] == 0)
			iShowBMP2(1068, 99, "images\\woodBox.bmp", 0);
		if (brick[19] == 0)
			iShowBMP2(972, 122, "images\\woodPillar.bmp", 0);
		if (brick[20] == 0)
			iShowBMP2(1094, 122, "images\\woodPillar.bmp", 0);
		if (brick[21] == 0)
			iShowBMP2(972, 169, "images\\woodBox.bmp", 0);
		if (brick[22] == 0)
			iShowBMP2(1020, 169, "images\\woodBox.bmp", 0);
		if (brick[23] == 0)
			iShowBMP2(1068, 169, "images\\woodBox.bmp", 0);
		if (brick[24] == 0)
			iShowBMP2(972, 192, "images\\woodPillar.bmp", 0);
		if (brick[25] == 0)
			iShowBMP2(1094, 192, "images\\woodPillar.bmp", 0);
		if (brick[26] == 0)
			iShowBMP2(972, 239, "images\\woodBox.bmp", 0);
		if (brick[27] == 0)
			iShowBMP2(1020, 239, "images\\woodBox.bmp", 0);
		if (brick[28] == 0)
			iShowBMP2(1068, 239, "images\\woodBox.bmp", 0);
		if (brick[29] == 0)
			iShowBMP2(972, 262, "images\\woodTri1.bmp", 0);
		if (brick[30] == 0)
			iShowBMP2(1020, 262, "images\\woodPillar.bmp", 0);
		if (brick[31] == 0)
			iShowBMP2(1042, 262, "images\\woodPillar.bmp", 0);
		if (brick[32] == 0)
			iShowBMP2(1068, 262, "images\\woodTri.bmp", 0);

		if (countR == 0 || countR == 1)
		{
			iShowBMP2(00, 40, "images\\redBird.bmp", 0);
			iShowBMP2(40, 40, "images\\redBird.bmp", 0);
			iShowBMP2(80, 40, "images\\redBird.bmp", 0);
		}
		if (countR == 2 || countR == 3)
		{
			iShowBMP2(40, 40, "images\\redBird.bmp", 0);
			iShowBMP2(80, 40, "images\\redBird.bmp", 0);
		}
		if (countR == 4 || countR == 5)
			iShowBMP2(80, 40, "images\\redBird.bmp", 0);

		if (countR <= 12 && lvl2Count == 4)
		{
			iShowBMP(0, 0, "images\\level2Win.bmp");
			if (musicOn)
				PlaySound("music\\levelCleared.wav", NULL, SND_SYNC);
		}
		if (countR > 11 && lvl2Count != 4)
		{
			iShowBMP(0, 0, "images\\level2Loss.bmp");
			if (musicOn)
				PlaySound("music\\levelFailed.wav", NULL, SND_SYNC);
		}
	}
}

void yellowBirdPlay2()
{
	if (gameState == 5 && difficultyMedium % 2 == 0)
	{
		iShowBMP(0, 0, "images\\level2.bmp");
		iShowBMP2(yellow_x, yellow_y, "images\\yellowBird.bmp", 0);

		if (level2Collision1 != 1)
			iShowBMP2(1020, 122, "images\\pig02.bmp", 0);
		if (level2Collision2 != 1)
			iShowBMP2(1020, 190, "images\\pig02.bmp", 0);
		if (level2Collision3 != 1)
			iShowBMP2(1135, 100, "images\\pig02.bmp", 0);
		if (level2Collision4 != 1)
			iShowBMP2(875, 75, "images\\pig02.bmp", 0);

		if (brick[0] == 0)
			iShowBMP2(830, 30, "images\\woodTri1.bmp", 0);
		if (brick[1] == 0)
			iShowBMP2(876, 30, "images\\woodBox.bmp", 0);
		if (brick[2] == 0)
			iShowBMP2(924, 30, "images\\woodBox.bmp", 0);
		if (brick[3] == 0)
			iShowBMP2(972, 30, "images\\woodBox.bmp", 0);
		if (brick[4] == 0)
			iShowBMP2(1020, 30, "images\\woodTri2.bmp", 0);
		if (brick[5] == 0)
			iShowBMP2(1094, 30, "images\\woodPillar.bmp", 0);
		if (brick[6] == 0)
			iShowBMP2(1190, 30, "images\\woodPillar.bmp", 0);
		if (brick[7] == 0)
			iShowBMP2(876, 53, "images\\woodBox.bmp", 0);
		if (brick[8] == 0)
			iShowBMP2(924, 53, "images\\woodBox.bmp", 0);
		if (brick[9] == 0)
			iShowBMP2(972, 53, "images\\woodBox.bmp", 0);
		if (brick[10] == 0)
			iShowBMP2(924, 76, "images\\woodTri1.bmp", 0);
		if (brick[11] == 0)
			iShowBMP2(972, 76, "images\\woodBox.bmp", 0);
		if (brick[12] == 0)
			iShowBMP2(1020, 76, "images\\woodBox.bmp", 0);
		if (brick[13] == 0)
			iShowBMP2(1068, 76, "images\\woodBox.bmp", 0);
		if (brick[14] == 0)
			iShowBMP2(1116, 76, "images\\woodBox.bmp", 0);
		if (brick[15] == 0)
			iShowBMP2(1164, 76, "images\\woodBox.bmp", 0);
		if (brick[16] == 0)
			iShowBMP2(972, 99, "images\\woodBox.bmp", 0);
		if (brick[17] == 0)
			iShowBMP2(1020, 99, "images\\woodBox.bmp", 0);
		if (brick[18] == 0)
			iShowBMP2(1068, 99, "images\\woodBox.bmp", 0);
		if (brick[19] == 0)
			iShowBMP2(972, 122, "images\\woodPillar.bmp", 0);
		if (brick[20] == 0)
			iShowBMP2(1094, 122, "images\\woodPillar.bmp", 0);
		if (brick[21] == 0)
			iShowBMP2(972, 169, "images\\woodBox.bmp", 0);
		if (brick[22] == 0)
			iShowBMP2(1020, 169, "images\\woodBox.bmp", 0);
		if (brick[23] == 0)
			iShowBMP2(1068, 169, "images\\woodBox.bmp", 0);
		if (brick[24] == 0)
			iShowBMP2(972, 192, "images\\woodPillar.bmp", 0);
		if (brick[25] == 0)
			iShowBMP2(1094, 192, "images\\woodPillar.bmp", 0);
		if (brick[26] == 0)
			iShowBMP2(972, 239, "images\\woodBox.bmp", 0);
		if (brick[27] == 0)
			iShowBMP2(1020, 239, "images\\woodBox.bmp", 0);
		if (brick[28] == 0)
			iShowBMP2(1068, 239, "images\\woodBox.bmp", 0);
		if (brick[29] == 0)
			iShowBMP2(972, 262, "images\\woodTri1.bmp", 0);
		if (brick[30] == 0)
			iShowBMP2(1020, 262, "images\\woodPillar.bmp", 0);
		if (brick[31] == 0)
			iShowBMP2(1042, 262, "images\\woodPillar.bmp", 0);
		if (brick[32] == 0)
			iShowBMP2(1068, 262, "images\\woodTri.bmp", 0);

		if ((countY == 0) || countY == 1)
		{
			iShowBMP2(00, 40, "images\\yellowBird.bmp", 0);
			iShowBMP2(40, 40, "images\\yellowBird.bmp", 0);
			iShowBMP2(80, 40, "images\\yellowBird.bmp", 0);
		}

		if ((countY == 2) || countY == 3)
		{
			iShowBMP2(40, 40, "images\\yellowBird.bmp", 0);
			iShowBMP2(80, 40, "images\\yellowBird.bmp", 0);
		}
		if ((countY == 4) || countY == 5)
			iShowBMP2(80, 40, "images\\yellowBird.bmp", 0);

		if (countY <= 8 && count == 3)
		{
			iShowBMP(0, 0, "images\\level2Win.bmp");
			if (musicOn)
				PlaySound("music\\playWin.wav", NULL, SND_SYNC);
		}
		if (countY > 7 && count != 3)
		{
			iShowBMP(0, 0, "images\\level2Loss.bmp");
			if (musicOn)
				PlaySound("music\\levelFailed.wav", NULL, SND_SYNC);
		}
	}
}

void blueBirdPlay2()
{
	if (gameState == 6 && difficultyMedium % 2 == 0)
	{
		iShowBMP(0, 0, "images\\level2.bmp");
		if (!isTriplet)
		{
			iShowBMP2(blue_x, blue_y, "images\\blueBird.bmp", 0);
		}
		if (isTriplet)
		{
			iShowBMP2(blue_x1, blue_y1, "images\\blueBird.bmp", 0);
			iShowBMP2(blue_x2, blue_y2, "images\\blueBird.bmp", 0);
			iShowBMP2(blue_x3, blue_y3, "images\\blueBird.bmp", 0);
		}

		if (level2Collision1 != 1)
			iShowBMP2(1020, 122, "images\\pig02.bmp", 0);
		if (level2Collision2 != 1)
			iShowBMP2(1020, 190, "images\\pig02.bmp", 0);
		if (level2Collision3 != 1)
			iShowBMP2(1135, 100, "images\\pig02.bmp", 0);
		if (level2Collision4 != 1)
			iShowBMP2(875, 75, "images\\pig02.bmp", 0);

		if (brick[0] == 0)
			iShowBMP2(830, 30, "images\\woodTri1.bmp", 0);
		if (brick[1] == 0)
			iShowBMP2(876, 30, "images\\woodBox.bmp", 0);
		if (brick[2] == 0)
			iShowBMP2(924, 30, "images\\woodBox.bmp", 0);
		if (brick[3] == 0)
			iShowBMP2(972, 30, "images\\woodBox.bmp", 0);
		if (brick[4] == 0)
			iShowBMP2(1020, 30, "images\\woodTri2.bmp", 0);
		if (brick[5] == 0)
			iShowBMP2(1094, 30, "images\\woodPillar.bmp", 0);
		if (brick[6] == 0)
			iShowBMP2(1190, 30, "images\\woodPillar.bmp", 0);
		if (brick[7] == 0)
			iShowBMP2(876, 53, "images\\woodBox.bmp", 0);
		if (brick[8] == 0)
			iShowBMP2(924, 53, "images\\woodBox.bmp", 0);
		if (brick[9] == 0)
			iShowBMP2(972, 53, "images\\woodBox.bmp", 0);
		if (brick[10] == 0)
			iShowBMP2(924, 76, "images\\woodTri1.bmp", 0);
		if (brick[11] == 0)
			iShowBMP2(972, 76, "images\\woodBox.bmp", 0);
		if (brick[12] == 0)
			iShowBMP2(1020, 76, "images\\woodBox.bmp", 0);
		if (brick[13] == 0)
			iShowBMP2(1068, 76, "images\\woodBox.bmp", 0);
		if (brick[14] == 0)
			iShowBMP2(1116, 76, "images\\woodBox.bmp", 0);
		if (brick[15] == 0)
			iShowBMP2(1164, 76, "images\\woodBox.bmp", 0);
		if (brick[16] == 0)
			iShowBMP2(972, 99, "images\\woodBox.bmp", 0);
		if (brick[17] == 0)
			iShowBMP2(1020, 99, "images\\woodBox.bmp", 0);
		if (brick[18] == 0)
			iShowBMP2(1068, 99, "images\\woodBox.bmp", 0);
		if (brick[19] == 0)
			iShowBMP2(972, 122, "images\\woodPillar.bmp", 0);
		if (brick[20] == 0)
			iShowBMP2(1094, 122, "images\\woodPillar.bmp", 0);
		if (brick[21] == 0)
			iShowBMP2(972, 169, "images\\woodBox.bmp", 0);
		if (brick[22] == 0)
			iShowBMP2(1020, 169, "images\\woodBox.bmp", 0);
		if (brick[23] == 0)
			iShowBMP2(1068, 169, "images\\woodBox.bmp", 0);
		if (brick[24] == 0)
			iShowBMP2(972, 192, "images\\woodPillar.bmp", 0);
		if (brick[25] == 0)
			iShowBMP2(1094, 192, "images\\woodPillar.bmp", 0);
		if (brick[26] == 0)
			iShowBMP2(972, 239, "images\\woodBox.bmp", 0);
		if (brick[27] == 0)
			iShowBMP2(1020, 239, "images\\woodBox.bmp", 0);
		if (brick[28] == 0)
			iShowBMP2(1068, 239, "images\\woodBox.bmp", 0);
		if (brick[29] == 0)
			iShowBMP2(972, 262, "images\\woodTri1.bmp", 0);
		if (brick[30] == 0)
			iShowBMP2(1020, 262, "images\\woodPillar.bmp", 0);
		if (brick[31] == 0)
			iShowBMP2(1042, 262, "images\\woodPillar.bmp", 0);
		if (brick[32] == 0)
			iShowBMP2(1068, 262, "images\\woodTri.bmp", 0);

		if ((countB == 0) || countB == 1)
		{
			iShowBMP2(00, 40, "images\\blueBird.bmp", 0);
			iShowBMP2(40, 40, "images\\blueBird.bmp", 0);
			iShowBMP2(80, 40, "images\\blueBird.bmp", 0);
		}
		if ((countB == 2) || countB == 3)
		{
			iShowBMP2(40, 40, "images\\blueBird.bmp", 0);
			iShowBMP2(80, 40, "images\\blueBird.bmp", 0);
		}
		if ((countB == 4) || countB == 5)
			iShowBMP2(80, 40, "images\\blueBird.bmp", 0);

		if (countB <= 8 && count == 3)
		{
			iShowBMP(0, 0, "images\\level2Win.bmp");
			if (musicOn)
				PlaySound("music\\playWin.wav", NULL, SND_SYNC);
		}
		if (countB > 7 && count != 3)
		{
			iShowBMP(0, 0, "images\\level2Loss.bmp");
			if (musicOn)
				PlaySound("music\\levelFailed.wav", NULL, SND_SYNC);
		}
	}
}

void redBirdPlay3()
{
	if (gameState == 4 && difficultyHard % 2 == 0)
	{
		iShowBMP(0, 0, "images\\level3.bmp");
		iShowBMP2(red_x, red_y, "images\\redBird.bmp", 0);
		if (level3Collision1 != 1)
			iShowBMP2(pig1_x, pig1_y, "images\\pig02.bmp", 0);
		if (level3Collision2 != 1)
			iShowBMP2(pig2_x, pig2_y, "images\\pig02.bmp", 0);
		if (level3Collision3 != 1)
			iShowBMP2(pig3_x, pig3_y, "images\\pig02.bmp", 0);
		if (level3Collision4 != 1)
			iShowBMP2(pig4_x, pig4_y, "images\\pig02.bmp", 0);
		if (level3Collision5 != 1)
			iShowBMP2(pig1_x, pig1_y - 20, "images\\woodBox.bmp", 0);
		if (level3Collision6 != 1)
			iShowBMP2(pig2_x, pig2_y - 20, "images\\woodBox.bmp", 0);
		if (level3Collision7 != 1)
			iShowBMP2(pig3_x, pig3_y - 20, "images\\woodBox.bmp", 0);
		if (level3Collision8 != 1)
			iShowBMP2(pig4_x, pig4_y - 20, "images\\woodBox.bmp", 0);

		if (countR == 0 || countR == 1)
		{
			iShowBMP2(00, 40, "images\\redBird.bmp", 0);
			iShowBMP2(40, 40, "images\\redBird.bmp", 0);
			iShowBMP2(80, 40, "images\\redBird.bmp", 0);
		}
		if (countR == 2 || countR == 3)
		{
			iShowBMP2(40, 40, "images\\redBird.bmp", 0);
			iShowBMP2(80, 40, "images\\redBird.bmp", 0);
		}
		if (countR == 4 || countR == 5)
			iShowBMP2(80, 40, "images\\redBird.bmp", 0);

		if (countR <= 12 && lvl3Count == 4)
		{
			iShowBMP(0, 0, "images\\level3Win.bmp");
			if (musicOn)
				PlaySound("music\\levelCleared.wav", NULL, SND_SYNC);
		}
		if (countR > 11 && lvl3Count != 4)
		{
			iShowBMP(0, 0, "images\\level3Loss.bmp");
			if (musicOn)
				PlaySound("music\\levelFailed.wav", NULL, SND_SYNC);
		}
	}
}

void yellowBirdPlay3()
{
}

void blueBirdPlay3()
{
}

void restart()
{
	isBirdFlying = false;
	isTriplet = false;
	isSpeed = false;

	bird_ix = 65.0;
	bird_iy = 130.0;

	red_x = bird_ix;
	red_y = bird_iy;
	yellow_x = bird_ix;
	yellow_y = bird_iy;
	blue_x = bird_ix;
	blue_y = bird_iy;
	redT = 0, yellowT = 0, blueT = 0, yellowT1 = 0;
	t1 = 0, t2 = 0, t3 = 0;

	if (gameState == 4)
		countR++;
	if (gameState == 5)
		countY++;
	if (gameState == 6)
		countB++;
}
void settingsMenu()
{
	if (gameState == 3)
		iShowBMP(0, 0, "images\\MenuSettings.bmp");
}
void playMenu()
{
	if (gameState == 2)
		iShowBMP(0, 0, "images\\MenuPlay.bmp");
}
void mainMenu()
{
	if (gameState == 1)
	{
		iShowBMP(0, 0, "images\\Menu.bmp");
	}
}
void leaderboardMenu()
{
	if (gameState == 7)
		iShowBMP(0, 0, "images\\MenuSettingsLeaderboard.bmp");
}
void difficultyMenu()
{
	if (gameState == 8)
	{
		iShowBMP(0, 0, "images\\MenuSettingsDifficulty.bmp");
		if (difficultyEasy % 2 == 0)
		{
			iShowBMP(0, 0, "images\\MenuSettingsDifficulty1.bmp");
		}
		else if (difficultyMedium % 2 == 0)
		{
			iShowBMP(0, 0, "images\\MenuSettingsDifficulty2.bmp");
		}
		else if (difficultyHard % 2 == 0)
		{
			iShowBMP(0, 0, "images\\MenuSettingsDifficulty3.bmp");
		}
		else
		{
			iShowBMP(0, 0, "images\\MenuSettingsDifficulty.bmp");
		}
	}
}
void soundsMenu()
{
	if (gameState == 9)
	{
		if (clickButton % 2 == 0)
		{
			iShowBMP(0, 0, "a\\Sounds0.bmp");
			musicOn = true;
		}
		else
		{
			iShowBMP(0, 0, "a\\Sounds32.bmp");
			musicOn = false;
		}
	}
}
void rulesMenu()
{
	if (gameState == 10)
		iShowBMP(0, 0, "images\\MenuSettingsRules.bmp");
}
void creditsMenu()
{
	if (gameState == 11)
		iShowBMP(0, 0, "images\\MenuSettingsCredits.bmp");
}
void nameInput()
{
	if (gameState == 12)
	{
		iShowBMP(0, 0, "images\\NameInput.bmp");
		iSetColor(0, 0, 0);
		iText(415, 336, playerName, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}
void showScore()
{
	if (gameState == 4 || gameState == 5 || gameState == 6)
	{
		iSetColor(0, 0, 0);
		sprintf(scoreShow, "%d", playerScore);
		iText(1150, 745, scoreShow, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	/* 	if(gameState==12){
			iSetColor(0,0,0);
			sprintf(scoreShow,"%d",playerScore);
			iText(662,454,scoreShow,GLUT_BITMAP_TIMES_ROMAN_24);
		} */
}
void dotLine()
{
	if (gameState == 4 || gameState == 5 || gameState == 6)
	{
		double vel = dotVelocity;
		double ang = dotAngle;
		dot_x = 65;
		dot_y = 130;
		dotT = 0;
		while (dot_y > 40)
		{
			dot_x = dot_ix + vel * cos(ang) * dotT;
			dot_y = dot_iy + vel * sin(ang) * dotT - 6 * dotT * dotT;
			iSetColor(0, 0, 0);
			iPoint(dot_x + 20, dot_y + 20, 1);
			dotT += 0.5;
		}
	}
}
void levelRestart()
{
	count = 0, count1 = 1, count2 = 1, count3 = 1, countY = 0, countR = 0, countB = 0;
	collision1 = 0, collision2 = 0, collision3 = 0;
	scoreStr[2] = '0';
	scoreStr[1] = '0';
	playerScore = 0;
	lvl2Count1 = 0, lvl2Count2 = 0, lvl2Count3 = 0, lvl2Count4 = 0;
	level2Collision1 = 0, level2Collision2 = 0, level2Collision3 = 0, level2Collision4 = 0;
	for (int i = 0; i < 33; i++)
	{
		brick[i] = 0;
		brickCheck[i] = 0;
	}
	level3Collision1 = 0, level3Collision2 = 0, level3Collision3 = 0, level3Collision4 = 0;
	level3Collision5 = 0, level3Collision6 = 0, level3Collision7 = 0, level3Collision8 = 0;
	lvl3Count1 = 0, lvl3Count2 = 0, lvl3Count3 = 0, lvl3Count4 = 0;
	lvl2Count = 0, lvl3Count = 0;
}

/*
	function iDraw() is called again and again by the system.

*/

void iDraw()
{
	// place your drawing codes here
	iClear();
	mainMenu();
	playMenu();
	settingsMenu();
	redBirdPlay1();
	yellowBirdPlay1();
	blueBirdPlay1();
	redBirdPlay2();
	yellowBirdPlay2();
	blueBirdPlay2();
	redBirdPlay3();
	// yellowBirdPlay3();
	// blueBirdPlay3();
	leaderboardMenu();
	difficultyMenu();
	soundsMenu();
	rulesMenu();
	creditsMenu();
	score();
	nameInput();
	dotLine();
	showScore();
	floatingPig();
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/

void iMouseMove(int mx1, int my1)
{
	// place your codes here
	bird_x = mx1 - 20;
	bird_y = my1 - 20;
	red_x = bird_x;
	red_y = bird_y;
	yellow_x = bird_x;
	yellow_y = bird_y;
	blue_x = bird_x;
	blue_y = bird_y;

	dotVelocity = launchVelocity(mx1, my1);
	dotAngle = launchAngle(mx1, my1);
	printf("%d %d\n", mx1, my1);
}

double launchVelocity(int mx, int my)
{
	if (bird_ix - mx != 0)
	{
		double m = (bird_iy - my) / (bird_ix - mx);
		double a = atan(m);
		double d = sqrt((bird_ix - mx) * (bird_iy - mx) + (bird_ix - my) * (bird_iy - my));
		double v = d * 2;
		return v;
	}
	else
		return 1;
}

double launchAngle(int mx, int my)
{
	if (bird_ix - mx != 0)
	{
		double m = (bird_iy - my) / (bird_ix - mx);
		double a = atan(m);
		return a;
	}
	else
		return 1;
}

void projectileMotion()
{
	if (gameState == 4)
	{
		redT += .50;
		red_x = red_ix + velocity * cos(angle) * redT;
		red_y = red_iy + velocity * sin(angle) * redT - 6 * redT * redT;

		if (difficultyEasy % 2 == 0)
			redCollisionLevel1();
		if (difficultyMedium % 2 == 0)
			redCollisionLevel2();
		if (difficultyHard % 2 == 0)
			redCollisionLevel3();
	}
	if (gameState == 5)
	{
		if (!isSpeed)
		{
			yellowT += .50;
			yellow_x = yellow_ix + velocity * cos(angle) * yellowT;
			yellow_y = yellow_iy + velocity * sin(angle) * yellowT - 6 * yellowT * yellowT;

			if (difficultyEasy % 2 == 0)
				yellowCollisionLevel1();
			// if(difficultyMedium%2==0)
			// yellowCollisionLevel2();
			// if(difficultyHard%2==0)
			// yellowCollisionLevel3();
		}
		if (isSpeed)
		{
			yellowT1 += .50;
			yellow_x = yellow_x + 2 * velocity * cos(angle / 10) * yellowT1;
			yellow_y = yellow_y + 2 * velocity * sin(angle / 10) * yellowT1 - 6 * yellowT1 * yellowT1;

			if (difficultyEasy % 2 == 0)
				yellowCollisionLevel1();
			// if(difficultyMedium%2==0)
			// yellowCollisionLevel2();
			// if(difficultyHard%2==0)
			// yellowCollisionLevel3();
		}
	}
	if (gameState == 6)
	{
		if (!isTriplet)
		{
			blueT += .50;
			blue_x = blue_ix + velocity * cos(angle) * blueT;
			blue_y = blue_iy + velocity * sin(angle) * blueT - 6 * blueT * blueT;

			if (difficultyEasy % 2 == 0)
				blueCollisionLevel1();
			// if(difficultyMedium%2==0)
			// blueCollisionLevel2();
			// if(difficultyHard%2==0)
			// blueCollisionLevel3();
		}
		if (isTriplet)
		{
			t1 += .70;
			t2 += .60;
			t3 += .50;

			blue_x1 = blue_x + 1.1 * velocity * cos(angle) * t1;
			blue_y1 = blue_y + 1.1 * velocity * sin(angle) * t1 - 6 * t1 * t1;

			blue_x2 = blue_x + velocity * cos(angle) * t2;
			blue_y2 = blue_y + velocity * sin(angle) * t2 - 6 * t2 * t2;

			blue_x3 = blue_x + 0.9 * velocity * cos(angle) * t3;
			blue_y3 = blue_y + 0.9 * velocity * sin(angle) * t3 - 6 * t3 * t3;

			if (difficultyEasy % 2 == 0)
				blueCollisionLevel1();
			if (difficultyMedium % 2 == 0)
				blueCollisionLevel2();
			// if(difficultyHard%2==0)
			// blueCollisionLevel3();
		}
	}
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/

void iMouse(int button, int state, int dx, int dy)
{
	int mx = dx;
	int my = dy;
	printf("#%d %d#\n", mx, my);

	if (isBirdFlying && gameState == 6 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		isTriplet = true;
	}
	if (isBirdFlying && gameState == 5 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		isSpeed = true;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
		printf("%d %d\n", mx, my);

		if (gameState == 1 && dx >= 29 && dx <= 89 && dy >= 33 && dy <= 89)
		{
			exit(0);
		}
		else if (gameState == 3 && dx >= 24 && dx <= 83 && dy >= 80 && dy <= 135)
		{
			gameState = 1;
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
				PlaySound("music\\background.wav", NULL, SND_LOOP | SND_ASYNC);
			}
		}
		else if (gameState == 1 && dx >= 449 && dx <= 782 && dy >= 335 && dy <= 466)
		{
			gameState = 2;
			if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
				PlaySound("music\\background.wav", NULL, SND_LOOP | SND_ASYNC);
			}
		}
		else if (gameState == 2 && dx >= 301 && dx <= 370 && dy >= 175 && dy <= 243)
		{
			gameState = 4;
			if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 4 && dx >= 31 && dx <= 90 && dy >= 719 && dy <= 775)
		{
			gameState = 2;
			levelRestart();
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
				PlaySound("music\\background.wav", NULL, SND_LOOP | SND_ASYNC);
			}
		}
		else if (gameState == 12 && dx >= 825 && dx <= 875 && dy >= 320 && dy <= 370)
		{
			gameState = 2;
			leaderboard();
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
			}
		}
		else if ((gameState == 4 || gameState == 5 || gameState == 6) && dx >= 685 && dx <= 760 && dy >= 185 && dy <= 265)
		{
			gameState = 12;
			if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
			}
		}
		else if ((gameState == 4 || gameState == 5 || gameState == 6) && dx >= 600 && dx <= 670 && dy >= 185 && dy <= 265)
		{
			if (gameState == 4)
			{
				gameState = 4;
				levelRestart();
			}

			else if (gameState == 5)
			{
				gameState = 5;
				levelRestart();
			}

			else if (gameState == 6)
			{
				gameState = 6;
				levelRestart();
			}

			else if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
			}
		}
		else if ((gameState == 4 || gameState == 5 || gameState == 6) && dx >= 500 && dx <= 575 && dy >= 185 && dy <= 265)
		{
			gameState = 2;
			if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 2 && dx >= 617 && dx <= 685 && dy >= 175 && dy <= 243)
		{
			gameState = 5;
			if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 5 && dx >= 31 && dx <= 90 && dy >= 719 && dy <= 775)
		{
			gameState = 2;
			levelRestart();
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
				PlaySound("music\\background.wav", NULL, SND_LOOP | SND_ASYNC);
			}
		}
		else if (gameState == 2 && dx >= 940 && dx <= 1008 && dy >= 175 && dy <= 243)
		{
			gameState = 6;
			if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 6 && dx >= 31 && dx <= 90 && dy >= 719 && dy <= 775)
		{
			gameState = 2;
			levelRestart();
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
				PlaySound("music\\background.wav", NULL, SND_LOOP | SND_ASYNC);
			}
		}

		else if (gameState == 2 && dx >= 26 && dx <= 84 && dy >= 35 && dy <= 92)
		{
			gameState = 1;
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
				PlaySound("music\\background.wav", NULL, SND_LOOP | SND_ASYNC);
			}
		}

		else if (gameState == 3 && dx >= 407 && dx <= 860 && dy >= 558 && dy <= 643)
		{
			gameState = 7;
			if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 7 && dx >= 36 && dx <= 90 && dy >= 61 && dy <= 116)
		{
			gameState = 3;
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 3 && dx >= 407 && dx <= 860 && dy >= 447 && dy <= 530)
		{
			gameState = 8;
			if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 8 && dx >= 275 && dx <= 345 && dy >= 215 && dy <= 285)
		{
			if (difficultyMedium % 2 != 0 && difficultyHard % 2 != 0)
				difficultyEasy++;
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 8 && dx >= 600 && dx <= 675 && dy >= 215 && dy <= 285)
		{
			if (difficultyEasy % 2 != 0 && difficultyHard % 2 != 0)
				difficultyMedium++;
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 8 && dx >= 930 && dx <= 1000 && dy >= 215 && dy <= 285)
		{
			if (difficultyMedium % 2 != 0 && difficultyEasy % 2 != 0)
				difficultyHard++;
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 8 && dx >= 36 && dx <= 90 && dy >= 61 && dy <= 116)
		{
			gameState = 3;
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 9 && dx >= 610 && dx <= 760 && dy >= 380 && dy <= 450)
		{
			clickButton++;
			printf("#%d#", clickButton);
			if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 3 && dx >= 407 && dx <= 860 && dy >= 338 && dy <= 422)
		{
			gameState = 9;
			if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
			}
		}

		else if (gameState == 9 && dx >= 36 && dx <= 90 && dy >= 61 && dy <= 116)
		{
			gameState = 3;
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 3 && dx >= 407 && dx <= 860 && dy >= 226 && dy <= 310)
		{
			gameState = 10;
			if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 10 && dx >= 36 && dx <= 90 && dy >= 61 && dy <= 116)
		{
			gameState = 3;
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 3 && dx >= 407 && dx <= 860 && dy >= 115 && dy <= 252)
		{
			gameState = 11;
			if (musicOn)
			{
				PlaySound("music\\MenuSelect.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 11 && dx >= 36 && dx <= 90 && dy >= 61 && dy <= 116)
		{
			gameState = 3;
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
			}
		}
		else if (gameState == 3 && dx >= 407 && dx <= 860 && dy >= 558 && dy <= 643)
		{
			gameState = 2;
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
				PlaySound("music\\background.wav", NULL, SND_LOOP | SND_ASYNC);
			}
		}

		else if (gameState == 1 && dx >= 1187 && dx <= 1247 && dy >= 42 && dy <= 97)
		{
			gameState = 3;
			if (musicOn)
			{
				PlaySound("music\\menu_back.wav", NULL, SND_SYNC);
			}
		}
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{

		// printf("%lf,%lf\n",bird_dx,bird_dy);

		if (gameState == 4)
		{
			restart();
			angle = launchAngle(mx, my);
			velocity = launchVelocity(mx, my);
			if (musicOn)
				PlaySound("music\\birdFlying.wav", NULL, SND_ASYNC);
			isBirdFlying = true;
			x = iSetTimer(1, projectileMotion);
		}
		if (gameState == 5)
		{
			restart();
			angle = launchAngle(mx, my);
			velocity = launchVelocity(mx, my);
			if (musicOn)
				PlaySound("music\\birdFlying.wav", NULL, SND_ASYNC);
			isBirdFlying = true;
			y = iSetTimer(5, projectileMotion);
		}
		if (gameState == 6)
		{
			restart();
			angle = launchAngle(mx, my);
			velocity = launchVelocity(mx, my);
			if (musicOn)
				PlaySound("music\\birdFlying.wav", NULL, SND_ASYNC);
			isBirdFlying = true;
			z = iSetTimer(5, projectileMotion);
		}
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/

void iKeyboard(unsigned char key)
{
	if (key == 'x')
	{
		exit(0);
	}
	if (key != '\b')
	{
		playerName[indexNumber] = key;
		indexNumber++;
		playerName[indexNumber] = '\0';
	}
	else
	{
		if (indexNumber <= 0)
			indexNumber = 0;
		else
			indexNumber--;
			playerName[indexNumber] = '\0';
	}

	// place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/

void iSpecialKeyboard(unsigned char key)
{
	// place your codes for other keys here
}

int main()
{
	// place your own initialization codes here.
	if (musicOn)
		PlaySound("music\\background.wav", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(1280, 800, "Angry Birds");

	return 0;
}