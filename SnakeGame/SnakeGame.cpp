// SnakeTestingTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <list>
#include <Windows.h>


using namespace std;


// Screen size variables:
static int ScreenWidth = 120;
static int ScreenHeight = 30;


// Game Score Variables
int GameScore = 0;
int HighScore = 0;

// Game Difficulty
int GameSpeed = 2;

// User Menu Input:
int MenuInput = 0;
int NumberOfTraps = 0;

// Snake Body Length (greater increases to body length increase difficulty:
int SnakeBodyLength = 2; // Defualt value

// Snake Transparency Mode
int SnakeTransparencyMode = 0; // Default turned off.
char SnakeTail = '+';

struct SnakeBody {
	int x;
	int y;
};


void MenuInputThree() {
	while (MenuInput == 3) {
		cout << "1. 1 ADDITIONAL TRAP [2PTS EXTRA], 2. 3 ADDITIONAL TRAPS[5PTS EXTRA], 3. 5 ADDITIONAL TRAPS [10PTS EXTRA] \n";
		cin >> NumberOfTraps;
		cout << "======================================================\n";
		cout << "MENU\n";
		cout << "1. PLAY GAME\n";
		cout << "2. EXIT GAME\n";
		cout << "3. SELECT NUMBER OF TRAPS [ADDITIONAL POINTS REWARDED PER FOOD CAPTURE]\n";
		cout << "4. SELECT SNAKE LENGTH [LONGER = MORE PTS]\n";
		cout << "5. SELECT TRANSPARENCY MODE [TAIL TRANSPARENT = MORE PTS]\n";
		cout << "6. SELECT TIMER MODE [GET FOOD WITHIN ALLOCATED TIME OR LOSE]\n";
		cout << "======================================================\n";

		cin >> MenuInput;   // Taking input
	}
}

void MenuInputFour() {
	while (MenuInput == 4) {
		cout << "DEFAULT LENGTH = 2. 1. LENTGH = 4 [+2 PTS] 2. LENGTH = 6 [+4 PTS] \n";
		cin >> SnakeBodyLength;
		if (SnakeBodyLength == 1)
		{
			SnakeBodyLength = 4;
		}
		else if (SnakeBodyLength == 2)
		{
			SnakeBodyLength = 6;
		}
		cout << "======================================================\n";
		cout << "MENU\n";
		cout << "1. PLAY GAME\n";
		cout << "2. EXIT GAME\n";
		cout << "3. SELECT NUMBER OF TRAPS [ADDITIONAL POINTS REWARDED PER FOOD CAPTURE]\n";
		cout << "4. SELECT SNAKE LENGTH [LONGER = MORE PTS]\n";
		cout << "5. SELECT TRANSPARENCY MODE [TAIL TRANSPARENT = MORE PTS]\n";
		cout << "6. SELECT TIMER MODE [GET FOOD WITHIN ALLOCATED TIME OR LOSE]\n";
		cout << "======================================================\n";

		cin >> MenuInput;   // Taking input
	}
}

void MenuInputFive() {
	while (MenuInput == 5) {
		cout << "1 -- ON, 0 -- OFF\n";
		cin >> SnakeTransparencyMode;
		cout << "======================================================\n";
		cout << "MENU\n";
		cout << "1. PLAY GAME\n";
		cout << "2. EXIT GAME\n";
		cout << "3. SELECT NUMBER OF TRAPS [ADDITIONAL POINTS REWARDED PER FOOD CAPTURE]\n";
		cout << "4. SELECT SNAKE LENGTH [LONGER = MORE PTS]\n";
		cout << "5. SELECT TRANSPARENCY MODE [TAIL TRANSPARENT = MORE PTS]\n";
		cout << "6. SELECT TIMER MODE [GET FOOD WITHIN ALLOCATED TIME OR LOSE]\n";
		cout << "======================================================\n";

		cin >> MenuInput;   // Taking input
	}
}

/*
void MenuInputSix() {
	while (MenuInput == 6) {
		cout << "1 -- ON, 0 -- OFF\n";
		cin >> SnakeTransparencyMode;
		cout << "======================================================\n";
		cout << "MENU\n";
		cout << "1. PLAY GAME\n";
		cout << "2. EXIT GAME\n";
		cout << "3. SELECT NUMBER OF TRAPS [ADDITIONAL POINTS REWARDED PER FOOD CAPTURE]\n";
		cout << "4. SELECT SNAKE LENGTH [LONGER = MORE PTS]\n";
		cout << "5. SELECT TRANSPARENCY MODE [TAIL TRANSPARENT = MORE PTS]\n";
		cout << "6. SELECT TIMER MODE [GET FOOD WITHIN ALLOCATED TIME OR LOSE]\n";
		cout << "======================================================\n";

		cin >> MenuInput;   // Taking input
	}
}
*/

int main()
{





	while (MenuInput != 1)
	{
		cout << "======================================================\n";
		cout << "WELCOME TO THE SNAKE GAME.\n";
		cout << "PLEASE SELECT A MENU OPTION\n";
		cout << "======================================================\n";
		cout << "MENU\n";
		cout << "1. PLAY GAME\n";
		cout << "2. EXIT GAME\n";
		cout << "3. SELECT NUMBER OF TRAPS [ADDITIONAL POINTS REWARDED PER FOOD CAPTURE]\n";
		cout << "4. SELECT SNAKE LENGTH [LONGER = MORE PTS]\n";
		cout << "5. SELECT TRANSPARENCY MODE [TAIL TRANSPARENT = MORE PTS]\n";
		cout << "6. SELECT TIMER MODE [GET FOOD WITHIN ALLOCATED TIME OR LOSE]\n";
		cout << "======================================================\n";

		cin >> MenuInput;   // Taking input

		if (MenuInput == 3)
		{
			MenuInputThree();
		}
		if (MenuInput == 4)
		{
			MenuInputFour();
		}
		if (MenuInput == 5)
		{
			MenuInputFive();
		}
		/*
		if (MenuInput == 6)
		{
			MenuInputFour();
		}
		*/

	}






	// Creating standard screen buffer:
	wchar_t* screen = new wchar_t[ScreenWidth * ScreenHeight];
	for (int i = 0; i < ScreenWidth * ScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	while (MenuInput == 1)
	{
		// Reset to known state
		list<SnakeBody> snake = { {60,15}, {61,15}, {62,15}, {63,15}, {64,15} };

		/*
			Food, Traps, Snake Direction, Snake State [Dead, Alive]
		*/
		int FoodX = 18;
		int FoodY = 5;

		int TrapX = 36;
		int TrapY = 5;

		int TrapX2 = 15;
		int TrapY2 = 10;

		int TrapX3 = 36;
		int TrapY3 = 25;

		int TrapX4 = 72;
		int TrapY4 = 15;

		int TrapX5 = 17;
		int TrapY5 = 15;

		int TrapX6 = 99;
		int TrapY6 = 8;

		int SnakeDirection = 3; // 0 = North, 1 = East, 2 = South, 3 = West
		bool SnakeDead = false;

		// Game Controls
		bool KeyLeft = false,
			KeyRight = false,
			KeyLeftOld = false,
			KeyRightOld = false;

		/*
			WHILE THE SNAKE IS STILL ALIVE, GAME WILL CONTINUE TO OPERATE:
		*/
		while (SnakeDead != true) {
			/*
			*################################
			* GAME FUNCTION RELATED TO KEY INPUT.
			*/
			// Frame Timing. 
			auto t1 = chrono::system_clock::now();
			while ((chrono::system_clock::now() - t1) < ((SnakeDirection % 2 == 1) ? 120ms / GameSpeed : 200ms / GameSpeed))
			{
				// Get key input at current time:
				KeyRight = (0x8000 & GetAsyncKeyState((unsigned char)('\x27'))) != 0;
				KeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)('\x25'))) != 0;

				if (KeyRight && !KeyRightOld)
				{
					SnakeDirection++;
					// Wrap around if the direction is greater than 3 (snake direction west, move to north)
					if (SnakeDirection > 3) SnakeDirection = 0;
				}

				if (KeyLeft && !KeyLeftOld)
				{
					SnakeDirection--;
					// Wrap around if direction is less than 0 (snake direction north, move to west)
					if (SnakeDirection < 0) SnakeDirection = 3;
				}

				KeyRightOld = KeyRight;
				KeyLeftOld = KeyLeft;
			}
			//################################

			/*
			*################################
			* GAME FUNCTION RELATED TO MOVEMENT.
			*/
			switch (SnakeDirection) {
			case 0: // UP
				snake.push_front({ snake.front().x, snake.front().y - 1 });
				break;
			case 1: // RIGHT
				snake.push_front({ snake.front().x + 1, snake.front().y });
				break;
			case 2: // DOWN
				snake.push_front({ snake.front().x, snake.front().y + 1 });
				break;
			case 3: // LEFT
				snake.push_front({ snake.front().x - 1, snake.front().y });
				break;
			}

			/*
			* If snake captures food/Money update game score
			* Generate food/money somewhere random on the screen
			*/
			if (snake.front().x == FoodX && snake.front().y == FoodY) {
				// Increase the game score multiplied by the current game difficulty. [Base difficulty = 1]
				GameScore += 10 * GameSpeed;
				if (NumberOfTraps == 1) {
					GameScore += 2;
				}
				// Complications additional points:
				if (NumberOfTraps == 2) {
					GameScore += 5;
				}
				if (NumberOfTraps == 3) {
					GameScore += 10;
				}
				if (SnakeBodyLength == 4) {
					GameScore += 2;
				}
				if (SnakeBodyLength == 6) {
					GameScore += 4;
				}
				if (SnakeTransparencyMode == 1) {
					GameScore += 2;
				}

				// Increase Game speed.
				if (GameScore > 50 && GameScore <= 200) {
					GameSpeed = 3;
				}
				if (GameScore > 200) {
					GameSpeed = 4;
				}

				while (screen[FoodY * ScreenWidth + FoodX] != L' ') {
					FoodX = rand() % ScreenWidth;
					FoodY = (rand() % (ScreenHeight - 3)) + 3;
				}

				// Increase snake size by [user set] per food caught.
				for (int i = 0; i < SnakeBodyLength; i++) {
					snake.push_back({ snake.back().x, snake.back().y });

				}
			}
			/*
			* If the snake hits a mine.
			*/
			if (snake.front().x == TrapX && snake.front().y == TrapY) {
				SnakeDead = true;
			}
			// If traps selected is at 1:
			if (NumberOfTraps == 1 || NumberOfTraps == 2 || NumberOfTraps == 3) {
				if (snake.front().x == TrapX2 && snake.front().y == TrapY2) {
					SnakeDead = true;
				}
			}
			// If traps selected is at 2
			if (NumberOfTraps == 2 || NumberOfTraps == 3) {
				if (snake.front().x == TrapX3 && snake.front().y == TrapY3) {
					SnakeDead = true;
				}

				if (snake.front().x == TrapX4 && snake.front().y == TrapY4) {
					SnakeDead = true;
				}
			}

			// If traps selected is at 3
			if (NumberOfTraps == 3) {
				if (snake.front().x == TrapX4 && snake.front().y == TrapY4) {
					SnakeDead = true;
				}

				if (snake.front().x == TrapX5 && snake.front().y == TrapY5) {
					SnakeDead = true;
				}

				if (snake.front().x == TrapX6 && snake.front().y == TrapY6) {
					SnakeDead = true;
				}
			}

			/*
			* If snake hits a wall.
			* Set Snake Dead = true.
			*/
			if (snake.front().x < 0 || snake.front().x >= ScreenWidth) {
				SnakeDead = true;
			}

			if (snake.front().y < 3 || snake.front().y >= ScreenHeight) {
				SnakeDead = true;
			}


			// Check if snake has collided with itself
			for (list<SnakeBody>::iterator i = snake.begin(); i != snake.end(); i++) {
				if (i != snake.begin() && i->x == snake.front().x && i->y == snake.front().y) {
					SnakeDead = true;
				}
			}


			// As snake is moving, the back continuously needs to be deleted.
			snake.pop_back();
			//################################


			/*
			*################################3
			* GAME FUNCTION RELATED TO DISPLAYING.
			*/
			// Clear Screen [Game restarting or starting for the first time]
			for (int i = 0; i < ScreenWidth * ScreenHeight; i++) screen[i] = L' ';

			// Draw Stats & Border
			for (int i = 0; i < ScreenWidth; i++) {
				screen[i] = L'=';
				screen[2 * ScreenWidth + i] = L'=';
			}
			// Display full width multiple items:
			int cx = wsprintf(&screen[ScreenWidth + 3], L"[SNAKE GAME] | [HIGHSCORE] %d", HighScore);
			int dx = wsprintf(&screen[ScreenWidth + 34], L"[GAME LEVEL] %d", GameSpeed);
			wsprintf(&screen[ScreenWidth + 7] + (cx + dx), L" [SCORE]: %d", GameScore);

			// Draw Snake Body
			if (SnakeTransparencyMode == 1) {
				for (auto s : snake)
					screen[s.y * ScreenWidth + s.x] = SnakeDead ? L'!' : L'.';
			}
			else if (SnakeTransparencyMode == 0) {
				for (auto s : snake)
					screen[s.y * ScreenWidth + s.x] = SnakeDead ? L'!' : L'-';
			}


			// Draw Snake Head
			screen[snake.front().y * ScreenWidth + snake.front().x] = SnakeDead ? L'X' : L'@';

			// Draw Food
			screen[FoodY * ScreenWidth + FoodX] = L'$';

			// Draw Trap
			screen[TrapY * ScreenWidth + TrapX] = L'X';

			// Draw Traps appropriate to a specific trap level
			if (NumberOfTraps == 1 || NumberOfTraps == 2 || NumberOfTraps == 3) {
				screen[TrapY2 * ScreenWidth + TrapX2] = L'X';
			}
			if (NumberOfTraps == 2 || NumberOfTraps == 3) {
				screen[TrapY3 * ScreenWidth + TrapX3] = L'X';
				screen[TrapY4 * ScreenWidth + TrapX4] = L'X';
			}
			if (NumberOfTraps == 3) {
				screen[TrapY5 * ScreenWidth + TrapX5] = L'X';
				screen[TrapY6 * ScreenWidth + TrapX6] = L'X';

			}


			// If snake is dead:
			if (SnakeDead == true) {
				wsprintf(&screen[15 * ScreenWidth + 40], L"    PRESS SPACE TO RESTART GAME   ");

			}


			// Display Frame
			WriteConsoleOutputCharacter(hConsole, screen, ScreenWidth * ScreenHeight, { 0,0 }, &dwBytesWritten);
			//################################

		}
		/*
		* WAIT FOR USER TO RESTART GAME
		* CHECK FOR HIGH SCORE
		* RESET GAME SCORE & GAME LEVEL
		*/
		if (GameScore > HighScore) {
			HighScore = GameScore;
		}
		while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);
		GameScore = 0;
		GameSpeed = 2;
	}
}


