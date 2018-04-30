#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

string a = " ------------------------------- \n";
string b = "|       |       |       |       |\n";
string c = "|   ", d = "   |   ", e = "   |\n";

int neww[4] = { 2,2,4,2 };
int num[5][5];
int used[5][5], b1[5][5];
int score;

char in()
{
	char ch;
	for (;;)
		if (_kbhit())
			return ch = _getch();
}

void out();

class HELPER
{
private:
	bool flag;

	void jieshao()
	{
		system("cls");
		puts("游戏介绍");
		puts("2048是一款数字益智游戏，而《2048》的初始数字则是由2+2组成的基数4。在操作方面的不同则表现为一步一格的移动，变成更为爽快的一次到底。相同数字的方况在靠拢、相撞时会相加。系统给予的数字方块不是2就是4，玩家要想办法在这小小的16格范围中凑出「2048」这个数字方块。");
		puts("\n按'B'键返回，按'C'继续游戏。");
		for (;;)
		{
			char ch = in();
			if (ch == 'c' || ch == 'C') flag = true;
			if (ch == 'b' || ch == 'c' || ch == 'B' || ch == 'C')
				return;
		}
	}

	void teach()
	{
		system("cls");
		puts("游戏攻略");
		puts("1、最大数尽可能放在角落。\n2、数字按顺序紧邻排列。\n3、首先满足最大数和次大数在的那一列 / 行是满的。\n4、时刻注意活动较大数（32以上）旁边要有相近的数。\n5、以大数所在的一行为主要移动方向\n6、不要急于“清理桌面”。");
		puts("\n按'B'键返回，按'C'继续游戏。");
		for (;;)
		{
			char ch = in();
			if (ch == 'c' || ch == 'C') flag = true;
			if (ch == 'b' || ch == 'c' || ch == 'B' || ch == 'C')
				return;
		}
	}

	void ppress()
	{
		system("cls");
		puts("按键功能");
		puts("上:'W','↑'\n下:'S','↓'\n左:'A','←'\n右:'D','→'\n保存:'Q'\n退出:'O'\n重新开始:'B'\n帮助:'H'");
		puts("\n按'B'键返回，按'C'继续游戏。");
		for (;;)
		{
			char ch = in();
			if (ch == 'c' || ch == 'C') flag = true;
			if (ch == 'b' || ch == 'c' || ch == 'B' || ch == 'C')
				return;
		}
	}

public:
	void realtime_helper()
	{
		cout << "Press 'H' to find help.\n";
	}
	void help()
	{
		for (;;)
		{
			if (flag)
			{
				flag = false;
				return;
			}
			system("cls");
			puts("按数字键来选择，按'B'键返回，按'C'继续游戏。");
			puts("1.游戏介绍\n2.按键功能\n3.游戏攻略");
			char ch = in();
			switch (ch)
			{
			case 'b':
			case 'B':
			case 'c':
			case 'C':
				out();
				return;
			case '1':
				jieshao();
				continue;
			case '2':
				ppress();
				continue;
			case '3':
				teach();
				continue;
			}
		}
	}
}helper;

int last_move[5][5];
int X, Y;

inline void beginning()
{
	score = 0;
	memset(num, 0, sizeof(num));
	srand((unsigned)time(NULL));
	X = rand() % 4 + 1;
	Y = rand() % 4 + 1;
	num[X][Y] = neww[rand() % 4];
}

bool pd_ex()
{
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (!num[i][j])
				return 1;
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 3; j++)
			if (num[i][j] == num[i][j + 1])
				return 1;
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 4; j++)
			if (num[i][j] == num[i + 1][j])
				return 1;
	return 0;
}

bool compare()
{
	int comp;
	ifstream fin("saveload.data");
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if ((!(fin >> comp)) || (comp ^ num[i][j]))
			{
				fin.close();
				return true;
			}
	fin >> comp;
	fin.close();
	return comp ^ score;
}

void print(int x, int y)
{
	if (num[x][y] != 0)
		if (num[x][y]<10)
		{
			cout << "   ";
			if (num[x][y] == 2)
			{
				cout << num[x][y];
			}
			if (num[x][y] == 4)
			{
				cout << num[x][y];
			}
			if (num[x][y] == 8)
			{
				cout << num[x][y];
			}
			cout << "   ";
		}
		else
		{
			if (num[x][y]<100)
				cout << "   " << num[x][y] << "  ";
			else if (num[x][y]<1000)
				cout << "  " << num[x][y] << "  ";
			else if (num[x][y]<10000)
				cout << "  " << num[x][y] << " ";
			else if (num[x][y]<100000)
				cout << " " << num[x][y] << " ";
			else if (num[x][y]<1000000)
				cout << num[x][y] << " ";
			else
				cout << num[x][y];
		}
	else
		cout << "       ";
}

void save()
{
	ofstream fout("saveload.data");
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			fout << num[i][j] << ' ';
	fout << score;
	fout.close();
	MessageBox(NULL, "保存成功！", "WARNING", MB_OK);
}

void load()
{
	ifstream fin("saveload.data");
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
		{
			if ((!(fin >> num[i][j])) || (num[i][j] & 1))
			{
				MessageBox(NULL, "找不到合法文件，准备重新开始", "WARNING", MB_OK);
				beginning();
				ofstream fout("saveload.data");
				for (int i = 1; i <= 4; i++)
					for (int j = 1; j <= 4; j++)
						fout << num[i][j] << " ";
				fout << score;
				fout.close();
				return;
			}
		}
	fin >> score;
	fin.close();
}

void out()
{
	system("cls");
	cout << a << b;
	cout << "|";
	print(1, 1);
	cout << "|";
	print(1, 2);
	cout << "|";
	print(1, 3);
	cout << "|";
	print(1, 4);
	cout << "|\n";
	cout << b << a << b;
	cout << "|";
	print(2, 1);
	cout << "|";
	print(2, 2);
	cout << "|";
	print(2, 3);
	cout << "|";
	print(2, 4);
	cout << "|\n";
	cout << b << a << b;
	cout << "|";
	print(3, 1);
	cout << "|";
	print(3, 2);
	cout << "|";
	print(3, 3);
	cout << "|";
	print(3, 4);
	cout << "|\n";
	cout << b << a << b;
	cout << "|";
	print(4, 1);
	cout << "|";
	print(4, 2);
	cout << "|";
	print(4, 3);
	cout << "|";
	print(4, 4);
	cout << "|\n";
	cout << b << a << "\n";
	cout << "Score:" << score << "\n";
	helper.realtime_helper();
}

inline void Left()
{
	memset(b1, 0, sizeof b1);
	memset(used, 0, sizeof used);
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (num[i][j])
			{
				int nx = j;
				while (nx != 1 && (!b1[i][nx - 1])) --nx;
				if (nx == 1)
					b1[i][nx] = num[i][j];
				else
				{
					bool flag = 0;
					if (b1[i][nx - 1] == num[i][j])
						if (!used[i][nx - 1])
						{
							b1[i][nx - 1] <<= 1;
							score += b1[i][nx - 1];
							used[i][nx - 1] = 1;
							flag = 1;
						}
					if (!flag)
						b1[i][nx] = num[i][j];
				}
			}
	swap(num, b1);
}

inline void Right()
{
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 2; j++)
			swap(num[i][j], num[i][4 - j + 1]);
	Left();
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 2; j++)
			swap(num[i][j], num[i][4 - j + 1]);
}

void Down()
{
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			b1[j][4 - i + 1] = num[i][j];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			num[i][j] = b1[i][j];
	Left();
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			b1[j][4 - i + 1] = num[i][j];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			num[i][j] = b1[i][j];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			b1[j][4 - i + 1] = num[i][j];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			num[i][j] = b1[i][j];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			b1[j][4 - i + 1] = num[i][j];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			num[i][j] = b1[i][j];
}

void Up()
{
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			b1[j][4 - i + 1] = num[i][j];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			num[i][j] = b1[i][j];

	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			b1[j][4 - i + 1] = num[i][j];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			num[i][j] = b1[i][j];
	Down();
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			b1[j][4 - i + 1] = num[i][j];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			num[i][j] = b1[i][j];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			b1[j][4 - i + 1] = num[i][j];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			num[i][j] = b1[i][j];
}

bool pd()
{
	int ls[5][5];
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (num[i][j] == 0)
				return 1;
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			ls[i][j] = num[i][j];
	Left();
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (ls[i][j] != num[i][j])
				return 1;
	Right();
	Right();
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (ls[i][j] != num[i][j])
				return 1;
	Left();
	Up();
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (ls[i][j] != num[i][j])
				return 1;
	Down();
	Down();
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (ls[i][j] != num[i][j])
				return 1;
	Up();
	return 0;
}

void play();

int main();

void choice()
{
	system("cls");
	if (MessageBox(NULL, "Restart?", "question", MB_YESNO) == IDYES)
	{
		beginning();
		play();
	}
	else
		exit(0);
}


void play()
{
	out();
	for (;;)
	{
		char way = in();
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
				last_move[i][j] = num[i][j];
		switch (way)
		{
		case 'a':
		//case 'A':
		case 75:
			Left();
			break;
		case 'd':
		//case 'D':
		case 77:
			Right();
			break;
		case 's':
		//case 'S':
		case 80:
			Down();
			break;
		case 'w':
		//case 'W':
		case 72:
			Up();
			break;
		case 'q':
		//case 'Q':
			save();
			continue;
		case 'o':
		//case 'O':
			if (MessageBox(NULL, "Are you sure?", "WARNING", MB_YESNO) == IDYES)
			{
				if (compare())
					if (MessageBox(NULL, "Do you want to save?", "WARNING", MB_YESNO) == IDYES)
						save();
				exit(0);
			}
			else continue;
		case 'b':
			system("cls");
			if (MessageBox(NULL, "Are you sure?", "WARNING", MB_YESNO) == IDYES)
			{
				main();
				exit(0);
			}
			else
			{
				out();
				continue;
			}
		case 'h':
			helper.help();
			continue;
		default:
			out();
			puts("Sorry, I don't seem to understand. You can press 'H' to find help");
			continue;
		}
		bool full = 1, usable = 0;
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
				if (last_move[i][j] ^ num[i][j])
					usable = 1;
		if (!usable)
		{
			out();
			puts("Invalid operation");
			goto nextstep;
		}
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
				if (num[i][j])
				{
					full = 0;
					break;
				}
		if (!full)
		{
			do
			{
				X = (rand() % 4) + 1;
				Y = (rand() % 4) + 1;
				if (num[X][Y] == 0)
				{
					num[X][Y] = neww[rand() % 4];
					break;
				}
			} while (1);
		}
		out();
	nextstep:
		if (!pd_ex())
		{
			int maxx = 0;
			for (int i = 1; i <= 4; i++)
				for (int j = 1; j <= 4; j++)
				{
					maxx = max(maxx, num[i][j]);
				}
			if (maxx >= 2048)
			{
				cout << "Game Over\nYour Biggest Number:" << maxx << "\n";
			}
			else
				MessageBox(NULL, "You lose!", "2048", MB_OK);
			choice();
		}
	}
}

int main()
{
	MessageBox(NULL, "Welcome to 2048 games.", "WELCOME", MB_OK);
	MessageBox(NULL, "在玩此游戏时，请不要开大写锁定。", "helper", MB_OK);
	if (MessageBox(NULL, "Load Game?", "question", MB_YESNO) == IDYES) load();
	else beginning();
	play();
	return 0;
}
