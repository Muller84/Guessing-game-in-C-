#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

//Will generate a different random number when you run the program
void chance(){
	//function sets the starting point by time
	srand((unsigned int)time(NULL));

}

//The function will generate a random number between 1 and the maximum
int random_number(int maximum){
	int random = 1 + rand() % maximum;
	return random;
}

void setColor(HANDLE hConsole, int color) {
	SetConsoleTextAttribute(hConsole, color);
}

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Handle to control console colors

	// Check if the sound plays successfully, background asynchronously
	if (!PlaySound(TEXT("C:\\Users\\TinaM\\OneDrive\\Documents\\C++ training\\Project2\\song1.wav"), NULL, SND_FILENAME | SND_ASYNC)) {
		cout << "Error: Sound file not found or unable to play." << endl;
	}

	//before I generate a random number I call the random function
	chance();

	//Guess, the number is equal random number up to 100, strokes
	int guess, number = random_number(100), strokes = 0;
	setColor(hConsole, FOREGROUND_GREEN);
	// Ask for the first number
	cout << "Guess, Which number I think? (between 1 and 100): ";
	cin >> guess;
	strokes = 1;

	//Endless loop until the user guesses
	while (guess != number || guess < 1 || guess > 100 || !cin) {
		//The condition checks whether the user enters a letter
		if (!cin || guess < 1 || guess > 100) {
			setColor(hConsole, FOREGROUND_RED);
			//If an error occurs, an error message is printed
			cout << "Invalid input! Please enter a number between 1 and 100: ";
			//Clear errors
			cin.clear();
			//Clear the another characters from memory, including the error
			cin.ignore();
			strokes++;
			setColor(hConsole, FOREGROUND_GREEN);
			//Jump to the beginning of the cycle
			cout << "Guess, Which number I think? (between 1 and 100): ";
			cin >> guess;
			continue;
		}

		if (guess > number) {
			setColor(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "My number is smaller. Guess again: ";
			cin >> guess;
			strokes++; //increases strokes by 1
		}
		else if (guess < number) {
			setColor(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY),
				cout << "My number is bigger. Guess again: ";
			cin >> guess;
			strokes++; //increases strokes by 1
		}

	}

	// Play the sound and show the text simultaneously
	PlaySound(TEXT("C:\\Users\\TinaM\\OneDrive\\Documents\\C++ training\\Project2\\applause2_x.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(1000); // Brief pause to sync sound and text

	setColor(hConsole, FOREGROUND_RED);
	cout << "You won! You guessed right! It took you: " << strokes << " strokes!";

	setColor(hConsole, FOREGROUND_GREEN);
	cout << endl << "I COULD DO IT FOR " << strokes / 2 << " STROKES, HAVE ANOTHER GAME!" << endl;

	setColor(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default color

	// Ensure the sound has time to play
	Sleep(3000);

	return 0;
}