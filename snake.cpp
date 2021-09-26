#include<iostream>
#include<string>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

const int WIDTH=50;
const int HEIGHT=30;

COORD Egg;
bool eaten=0;

COORD Snake;
int direction;
int taillen=0;
COORD tailpos[100];

bool over=0;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

COORD Cursorpos;
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void drawBoard()
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            if(i==0 || i==HEIGHT-1 || j==0 || j==WIDTH-1)
            {
                printf("#");
            }
            else if(i==Egg.X && j==Egg.Y)
            {
                printf("*");
            }
            // else if(i==Snake.X && j==Snake.Y)
            // {
            //     printf("o");
            // }
            else
            {
                bool print=0;
                for(int k=0;k<taillen+1;k++)
                {
                    if(i==tailpos[k].X && j==tailpos[k].Y)
                    {
                        print=1;
                        printf("o");
                    }
                }
                if(!print)
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score :  %d",taillen);
}
COORD generateegg()
{
    int x=rand(),y=rand();
    x=(x%(HEIGHT-1))+1;
    y=(y%(WIDTH-1))+1;
    Egg.X=x;
    Egg.Y=y;
    return Egg;
}
COORD generatesnake()
{
    int x=rand(),y=rand();
    x=(x%(HEIGHT-1))+1;
    y=(y%(WIDTH-1))+1;
    Snake.X=x;
    Snake.Y=y;
    return Snake;
}
void checkeaten()
{
    if(Snake.X==Egg.X && Snake.Y==Egg.Y)
    {
        eaten=1;
    }
    return;
}
void getdirection()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a':
            {
                direction=1;
                break;
            }
            case 'd':
            {
                direction=3;
                break;
            }
            case 'w':
            {
                direction=5;
                break;
            }
            case 's':
            {
                direction=2;
                break;
            }
        }
    }
}
void movesnake()
{
    if(direction==1)
    {
        Snake.Y=Snake.Y-1;
    }
    else if(direction==3)
    {
        Snake.Y=Snake.Y+1;
    }
    else if(direction==5)
    {
        Snake.X=Snake.X-1;
    }
    else if(direction==2)
    {
        Snake.X=Snake.X+1;
    }
}
void checkdead()
{
    if(Snake.X<=0 || Snake.X>=HEIGHT-1 || Snake.Y<=0 || Snake.Y>=WIDTH-1)
    {
        over=1;
    }
}
void play()
{
    while(!over)
    {
        for(int i=taillen;i>0;i--)
        {
            tailpos[i].X=tailpos[i-1].X;
            tailpos[i].Y=tailpos[i-1].Y;
        }
        tailpos[0].X=Snake.X;
        tailpos[0].Y=Snake.Y;
        generateegg();
        eaten=0;
        while(!eaten && !over)
        {
            for(int i=taillen;i>0;i--)
            {
                tailpos[i].X=tailpos[i-1].X;
                tailpos[i].Y=tailpos[i-1].Y;
            }
            tailpos[0].X=Snake.X;
            tailpos[0].Y=Snake.Y;
            drawBoard();
            getdirection();
            movesnake();
            checkdead();
            checkeaten();
            system("cls");
            Sleep(10);
        }
        taillen++;
    }
    return;
}
int main()
{
    setcursor(0,0);
    srand( (unsigned)time(NULL)); 
    while(!over)
    {
        generatesnake();
        play();
        system("cls");
    }
    return 0;
}