#include<iostream>
#include<conio.h>
using namespace std;
bool gameOver,restart;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void Setup() {
	gameOver = false;
	x = width / 2;
	y = height / 2;
	fruitx = rand() % width;
	fruity = rand() % height;
	nTail = 0;
	dir = RIGHT;
}
void Draw(char h,char t) {
	system("cls");
	for (int i = 0;i < width;i++) {
		cout << "#"<<" ";
	}
	cout << endl;
	for (int i = 0;i < height;i++) {
		for (int j = 0;j < 2*width;j++) {
			if (j == 0 || j ==2*(width - 1)) {
				cout << "#";
			}
			else if (i == y && j == x) {
				cout << h;
			}
			else if (i == fruity && j == fruitx) {
				cout << "?";
			}
			else {
				bool print = false;
				for (int k = 0;k < nTail;k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << t;
						print = true;
					}
				}
				if(!print)
				cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0;i < width;i++) {
		cout << "#"<<" ";
	}
	cout << endl;
}
void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			if(dir == UP || dir == DOWN)
				dir = LEFT;
			break;
		case 'd':
			if (dir == UP || dir == DOWN)
				dir = RIGHT;
			break;
		case 'w':
			if (dir == LEFT || dir == RIGHT)
				dir = UP;
			break;
		case 's':
			if (dir == LEFT || dir == RIGHT)
				dir = DOWN;
			break;
		case 'q':
			gameOver = true;
			break;
		}
	}
}
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1;i < nTail;i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x>2* width-1 || x<1 || y>height || y<0) {
		gameOver = true;
	}
	for (int i = 0;i < nTail;i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver=true;
		}
	}
	if (x == fruitx && y == fruity) {
		nTail += 1;
		fruitx = rand() % width;
		fruity = rand() % height;
	}
}
int main() {
	char h, t;
	cout << "enter head character" << endl;
	cin >> h;
	cout << "enter tail character" << endl;
	cin >> t;
	restart = true;
	while (restart) {
		dir = RIGHT;
		Setup();
		while (!gameOver) {
			Draw(h, t);
			Input();
			Logic();
			cout << endl << endl << "Score: " << nTail * 10;
			//gameOver = true;
			//Sleep(10);
		}
		system("cls");
		for (int i = 0;i < height / 2;i++) {
			cout << endl;
		}
		for (int i = 0;i < width;i++) {
			cout << " ";
		}
		cout << "Score: " << nTail * 10 << endl;
		for (int i = 0;i < height / 2;i++) {
			cout << endl;
		}
		char option;
		cout << "press 'R' to restart, or 'Q' to quit"<<endl;
		cin >> option;
		if (option == 'r') {
			continue;
		}
		else if (option == 'q') {
			restart = false;
		}
		else {
			cout << "enter valid option"<<endl;
		}
	}
	return 0;
}
