#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>

#define clr(a) memset(a, 0, sizeof(a))
#define back(a) (a+strlen(a))

using namespace std;

int x,y,n,m,sum,placex,placey;
char mp[301][301];
bool flag[301][301],know[301][301];

char in();
void die();
void out();
void win();
void move();
void start();
void change();
void out_DIE();
void out_WIN();
void restart();
void search(int,int);

#define PERR(bSuccess, api) \
	{if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__,GetLastError(), api, __LINE__);}
void MyCls(HANDLE);
inline void clrscr()
{
	HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
	MyCls(hStdOut);
	return;
}

void MyCls(HANDLE hConsole)
{
	COORD coordScreen= {0,0};
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);
	PERR(bSuccess,"GetConsoleScreenBufferInfo");
	dwConSize=csbi.dwSize.X * csbi.dwSize.Y;
	bSuccess=FillConsoleOutputCharacter(hConsole,(TCHAR)' ',dwConSize,coordScreen,&cCharsWritten);
	PERR(bSuccess,"FillConsoleOutputCharacter");
	bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);
	PERR(bSuccess,"ConsoleScreenBufferInfo");
	bSuccess=FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten);
	PERR(bSuccess,"FillConsoleOutputAttribute");
	bSuccess=SetConsoleCursorPosition(hConsole,coordScreen);
	PERR(bSuccess,"SetConsoleCursorPosition");
}

void hidecursor()
{
	CONSOLE_CURSOR_INFO cursor_info= {1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}

char in()
{
	char ch;
	while(1)
		if(_kbhit())
			return ch=_getch();
}

void win()
{
	out_WIN();
	puts("You Win!");
	exit(0);
}

void start()
{
	bool first=1;
	placex=placey=1;
	while(1)
	{
		out();
		int rest=0;
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++)
				if(!know[i][j])
					rest++;
		if(rest==sum)
			win();
		char moveway=in();
		if(moveway=='j'||moveway=='J')
		{
			if(first)
			{
				if(flag[placex][placey])
				{
again2:
					x=rand()%n+1;
					y=rand()%m+1;
					if(flag[x][y])
						goto again2;
					flag[x][y]=1;
					flag[placex][placey]=0;
				}
				first=0;
			}
			change();
			continue;
		}
		if(moveway=='w'||moveway=='W')
		{
			if(placex-1>0)
			{
				placex--;
				continue;
			}
			else
			{
				out();
				puts("ERROR");
			}
		}
		if(moveway=='s'||moveway=='S')
		{
			if(placex+1<=n)
			{
				placex++;
				continue;
			}
			else
			{
				out();
				puts("ERROR");
			}
		}
		if(moveway=='a'||moveway=='A')
		{
			if(placey-1>0)
			{
				placey--;
				continue;
			}
			else
			{
				out();
				puts("ERROR");
			}
		}
		if(moveway=='d'||moveway=='D')
		{
			if(placey+1<=m)
			{
				placey++;
				continue;
			}
			else
			{
				out();
				puts("ERROR");
			}
		}
		if(moveway=='k'||moveway=='K')
		{
			if(know[placex][placey])
				continue;
			if(mp[placex][placey]!='B')
				mp[placex][placey]='B';
			else
				mp[placex][placey]=char(219);
			continue;
		}
	}
}

void die()
{
	clrscr();
	out_DIE();
	puts("Restart?(Press Y/N)");
again3:
	char ch=in();
	if(ch=='y'||ch=='Y')
		restart();
	else if(ch=='n'||ch=='N')
		exit(0);
	else
		goto again3;
}

void change()
{
	if(mp[placex][placey]=='B')
		return;
	if(flag[placex][placey]&&!know[placex][placey])
		die();
	else
		search(placex,placey);
}

void search(int a,int b)
{
	int boombs=0,points=0;
	if(!know[a][b])
	{
		for(int i=-1; i<=1; i++)
			for(int j=-1; j<=1; j++)
				if(a+i>0&&b+j>0&&a+i<=n&&b+j<=m)
					if(flag[a+i][b+j])
						boombs++;
		if(!boombs)
		{
			know[a][b]=1;
			mp[a][b]='.';
			for(int i=-1; i<=1; i++)
				for(int j=-1; j<=1; j++)
					if(a+i>0&&b+j>0&&a+i<=n&&b+j<=m)
						if(!know[a+i][b+j])
							search(a+i,b+j);
			return;
		}
		mp[a][b]=boombs+'0';
		know[a][b]=1;
		return;
	}
	else
	{
		for(int i=-1; i<=1; i++)
			for(int j=-1; j<=1; j++)
				if(a+i>0&&b+j>0&&a+i<=n&&b+j<=m)
				{
					if(flag[a+i][b+j])
						boombs++;
					if(mp[a+i][b+j]=='B')
						points++;
				}
		if(boombs==points)
		{
			for(int i=-1; i<=1; i++)
				for(int j=-1; j<=1; j++)
				{
					if(mp[a+i][b+j]!='B')
						if(flag[a+i][b+j])
							die();
					if(!know[a+i][b+j]&&!flag[a+i][b+j])
						search(a+i,b+j);
				}
		}
		else
			puts("ERROR");
	}
}

#define dd c = getchar()
inline void read(int& x)
{
	char dd;
	for(; !isdigit(c); dd);
	for(; isdigit(c); dd)
		x = (x<<1) + (x<<3) + (c^48);
}
#undef dd

void restart()
{
	srand((unsigned)time(NULL));
	placex=placey==1;
//kkksc03:
	clrscr();
	puts("Please input the size");
	read(n);
	read(m);
//	if(n<1||m<1)
//		goto kkksc03;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
		{
			mp[i][j]=char(219);
			flag[i][j]=know[i][j]=0;
		}
again1:
	clrscr();
	puts("Please input the number of booms");
	read(sum);
	if(sum>=n*m)
	{
		puts("ERROR");
		goto again1;
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			mp[i][j]=char(219);
	for(int i=1; i<=sum; i++)
	{
again:
		x=rand()%n+1;
		y=rand()%m+1;
		if(flag[x][y])
			goto again;
		flag[x][y]=1;
	}
	out();
	start();
}

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	restart();
	return 0;
}

char screen[1000000];

void out()
{
	clrscr();
	putchar(' ');
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	for(int i=1; i<=3*m; i++)
		putchar('-');
	puts("");
	for(int i=1; i<=n; i++)
	{
		putchar('|');
		for(int j=1; j<=m; j++)
		{
			if(i==placex&&j==placey)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
				if(mp[i][j]==char(219))
					cout<<mp[i][j]<<mp[i][j]<<mp[i][j];
				else
					cout<<" "<<mp[i][j]<<" ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			}
			else if(mp[i][j]=='B')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
				cout<<" "<<mp[i][j]<<" ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				if(mp[i][j]==char(219))
					cout<<mp[i][j]<<mp[i][j]<<mp[i][j];
				else
					cout<<" "<<mp[i][j]<<" ";
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		cout<<"|\n";
	}
	cout<<" ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	for(int i=1; i<=3*m; i++)
		cout<<"-";
	cout<<"\n";
	int bom=0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(mp[i][j]=='B')
				bom++;
	cout<<"BOOMS:"<<sum-bom<<"\n";
}

void out_DIE()
{
	clrscr();
	cout<<" ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	for(int i=1; i<=3*m; i++)
		cout<<"-";
	cout<<"\n";
	for(int i=1; i<=n; i++)
	{
		cout<<"|";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		for(int j=1; j<=m; j++)
		{
			if(mp[i][j]==char(219))
			{
				if(!flag[i][j])
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
					cout<<mp[i][j]<<mp[i][j]<<mp[i][j];
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
					cout<<" B ";
				}
			}
			else
			{
				if(mp[i][j]=='B')
				{
					if(flag[i][j])
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
						cout<<" "<<mp[i][j]<<" ";
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						cout<<" X ";
					}
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
					cout<<" "<<mp[i][j]<<" ";
				}
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		cout<<"|\n";
	}
	cout<<" ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	for(int i=1; i<=3*m; i++)
		cout<<"-";
	cout<<"\n";
	puts("You Lose");
	system("pause");
	clrscr();
}

void out_WIN()
{
	clrscr();
	cout<<" ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	for(int i=1; i<=3*m; i++)
		cout<<"-";
	cout<<"\n";
	for(int i=1; i<=n; i++)
	{
		cout<<"|";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		for(int j=1; j<=m; j++)
		{
			if(flag[i][j])
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
				cout<<" B ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			}
			else
				cout<<" "<<mp[i][j]<<" ";
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		cout<<"|\n";
	}
	cout<<" ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	for(int i=1; i<=3*m; i++)
		cout<<"-";
	cout<<"\n";
	puts("You Win!");
	system("pause");
	clrscr();
	puts("Restart?(Press Y/N)");
	for(; ; )
	{
		char ch=in();
		if(ch=='y'||ch=='Y')
		{
			restart();
			exit(0);
		}
		else if(ch=='n'||ch=='N')
			exit(0);
	}
}
