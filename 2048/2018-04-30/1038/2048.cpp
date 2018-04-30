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
	cout << "Press 'Q' to save\nPress 'P' to exit\n";
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

void choice()
{
	system("cls");
	cout << "2048 game" << endl;
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
		if (way == 'a' || way == 'A' || way == 75)
			Left();
		else
		{
			if (way == 'd' || way == 'D' || way == 77)
				Right();
			else
			{
				if (way == 's' || way == 'S' || way == 80)
					Down();
				else
				{
					if (way == 'w' || way == 'W' || way == 72)
						Up();
					else
					{
						if (way == 'q' || way == 'Q')
						{
							save();
							continue;
						}
						else
						{
							if (way == 'p' || way == 'P')
							{
								if (MessageBox(NULL, "Are you sure?", "WARNING", MB_YESNO) == IDYES)
								{
									if (compare())
										if (MessageBox(NULL, "Do you want to save?", "WARNING", MB_YESNO) == IDYES)
											save();
									exit(0);
								}
								else continue;
							}
							else
							{
								out();
								puts("Sorry, I don't seem to understand");
								continue;
							}
						}
					}
				}
			}
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
				/*
				if (maxx >= 1000000)
				{
				MessageBox(NULL, "YOU WIN!!!", "YOUWIN", MB_OK);
				return 0;
				}
				*/
			}
			else
				MessageBox(NULL, "You lose!", "2048", MB_OK);
			choice();
		}
	}
}

int main()
{
	//  puts("==========================  目前支持的最大数字为七位数  ==========================");
	//  puts("==========================如果超过七位可能会导致画面崩坏==========================");
	//  puts("========================== 感谢小猪承担了大部分难度（雾 ==========================");
	//  system("pause");
	//  system("cls");
	MessageBox(NULL, "Use 'W','A','S','D' or '←','→','↑','↓' to play", "helper", MB_OK);
	//  MessageBox(NULL,"Do you know where they are?","WARNING",MB_YESNO);
	MessageBox(NULL, "You know? Fine.", "helper", MB_OK);
	if (MessageBox(NULL, "Load Game?", "question", MB_YESNO) == IDYES) load();
	else beginning();
	play();
}
