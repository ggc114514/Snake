#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#define int long long
#define key GetAsyncKeyState

using namespace std;
struct point {
	int x, y;
};
const int mX = 15, mY = 45;
int len, score = 0, direction = 3, x = 10, y = 10, lx, ly;
/*direction
  2
1-+-3
  4
*/
point food;
char m[mX + 5][mY + 5];
queue<point> snake;
bool eat = 0, flag = 0, snake2[mX + 10][mY + 10];

void gotoxy(int x, int y) {
	COORD pos = {y, x};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void mem() {
	memset(snake2, 0, sizeof(snake2));
	for (int i = 1; i <= mX; i++)
		for (int j = 1; j <= mY; j++)
			m[i][j] = ' ';
	return;
}

void print() {
	cout << "┌";
	for (int i = 1; i <= mY; i++)	cout << "─";
	cout << "┐\n";
	for (int i = 1; i <= mX; i++) {
		cout << "│";
		for (int j = 1; j <= mY; j++)
			cout << " ";
		cout << "│\n";
	}
	cout << "└";
	for (int i = 1; i <= mY; i++)	cout << "─";
	cout << "┘\n";
	cout << "score = " << score << "\n";
	cout << "direction = " << direction << "\n";
	return;
}

void getfood() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> disx(2, mX - 2);
	uniform_int_distribution<> disy(2, mY - 2);
	int randx = disx(gen);
	food.x = disx(gen);
	food.y = disy(gen);
}

bool iskey() {
	if (key(87)&&direction!=4) {
		direction = 2;
		while (key(87));
	}//W
	else if (key(83)&&direction!=2) //S
		direction = 4;
	else if (key(65)&&direction!=3) //A
		direction = 1;
	else if (key(68)&&direction!=1)
		direction = 3;
	else
		return 0;
	return 1;
}

void game_over() {
	system("cls");
	cout << "Game over!\nYour final score = "<<score<<"\n";
	system("pause");
	exit(0);
}

signed main() {
	cin.tie(0), cout.tie(0);
	mem();
	print();

	snake.push((point) {
		10, 10
	});
	snake2[10][10] = 1;
	while (1) {
		iskey();
		gotoxy(mX + 3, 12);
		cout << direction;
		gotoxy(mX + 2, 8);
		cout << score;

		point tail = snake.front();
		snake.pop();
		snake2[tail.x][tail.y] = 0;
		gotoxy(tail.x, tail.y);
		cout << " ";
		
		if (direction == 1)	y--;
		else if (direction == 2)	x--;
		else if (direction == 3)	y++;
		else if (direction == 4)	x++;
		
		snake.push((point) {
			x, y
		});
		if (x <= 0 || x >= mX || y <= 0 || y == mY || snake2[x][y])	game_over();
		snake2[x][y] = 1;
		
		if (flag) {
			snake.push((point) {
				lx, ly
			});
			flag = 0;
		}
		if (x == food.x && y == food.y) {
			score++;
			eat = 0;
			flag = 1;
			lx = x;
			ly = y;
		}
		gotoxy(x, y);
		cout << "@";

		if (!eat) {
			do{
				getfood();
			}while(snake2[food.x][food.y]);
			gotoxy(food.x, food.y);
			cout << "$";
			eat = 1;
		}


		Sleep(100);
	}
	system("cls");
	return 0;
}
