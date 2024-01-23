#include <iostream>
using namespace std;

class Game
{
	int* Wait;
	int MaxQueueLength;
	int QueueLength;
public:
	Game() {
		Wait = nullptr;
		MaxQueueLength = 0;
		QueueLength = 0;
	}
	//Конструктор
	Game(int m);
	//Деструктор
	~Game();
	//Добавление элемента
	void Add(int c);
	//Извлечение элемента
	bool Extract();
	//Проверка существования элементов в очереди
	bool IsEmpty();
	//Проверка на переполнение очереди
	bool IsFull();
	//демонстрация очереди
	void ShowResult(const Game& second, const Game& third);
	//Рандомная генирация прокрутки каждого барабана 
	bool RandomScrolling();
	//Проверка на победу 
	bool CheckWin(const Game& second, const Game& third);
};

Game::~Game()
{
	delete[]Wait;
}
Game::Game(int m)
{
	MaxQueueLength = m;
	Wait = new int[MaxQueueLength];
	QueueLength = 0;
}

//Вывод елементов 
void Game::ShowResult(const Game& second, const Game& third) {

	cout << endl;
	for (int i = 0; i < QueueLength; i++) {

		cout << i + 1 << " line: " << Wait[i] << " " << second.Wait[i] << " " << third.Wait[i] << endl;
	}
	cout << endl;
}

bool Game::IsEmpty()
{
	return QueueLength == 0;
}

bool Game::IsFull()
{
	return QueueLength == MaxQueueLength;
}

void Game::Add(int c)
{
	if (!IsFull())
		Wait[QueueLength++] = c;
}

bool Game::Extract()
{
	if (!IsEmpty()) {

		int temp = Wait[0];
		for (int i = 1; i < QueueLength; i++)
			Wait[i - 1] = Wait[i];
		Wait[QueueLength - 1] = temp;
		return 1;
	}
	else return 0;
}

//Рандомная генирация прокрутки каждого барабана 
bool Game::RandomScrolling() {

	int randomScrolling = rand() % 5 + 1;
	cout <<" "<< randomScrolling;
	for (int i = 0; i < randomScrolling; i++) {

		Extract();
	}
	return true;
}

//Проверка на победу 
bool Game::CheckWin(const Game& second, const Game& third) {

	for (int i = 0; i < QueueLength; i++) {
		// Сравнение элементов всех массивов под одним и тем же индексом
		if (Wait[i] == second.Wait[i] && Wait[i] == third.Wait[i] && second.Wait[i] == third.Wait[i]) {
			cout << "Coincidence " << i+1 <<" line: " << Wait[i] << " " << second.Wait[i] << " " << third.Wait[i] << endl;
			return true; 
		}
	}
	return false;
}

int main()
{ 
	srand(time(0));
	Game firstWheel(3);
	Game secondWheel(3);
	Game thirdWheel(3);

	for (int i = 0; i < 3; i++) {

		firstWheel.Add(rand() % 2 + 1);
		secondWheel.Add(rand() % 2 + 1);
		thirdWheel.Add(rand() % 2 + 1);
	}

	cout << "Before scrolling"<<endl;
	firstWheel.ShowResult(secondWheel, thirdWheel);

	cout << "        ^ ^ ^\n        | | |\n       ";
	firstWheel.RandomScrolling();
	secondWheel.RandomScrolling();
	thirdWheel.RandomScrolling();

	cout << "\nNumber of spins of each reel" << endl;

	cout << "\nAfter srolling" << endl;
	firstWheel.ShowResult(secondWheel, thirdWheel);


	if (firstWheel.CheckWin(secondWheel, thirdWheel)) {
		cout << "Congratulations! You won!" << endl;
	}
	else {
		cout << "You lost. Try again!" << endl;
	}

	return 0;
}