#include <stdio.h>
#include <conio.h> /* getch() and kbhit() */
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <string.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

char Input;

int positionX, positionY, prevPositionX, prevPositionY;

int menu = 1;

struct Tail {
    int x;
    int y;
    int prevX;
    int prevY;
};

struct Tail tail[50];

int welcomeScreen()
{
    system("cls");
    char confirm;
    printf("To use this program, you should use new \"Windows Terminal\" downloadable from Windows Store.\nNew terminal is more resposive and works faster.\nIf you use other terminal, some incorrections may occur.\nBy pressing \"yes\" you agree with this.  (y = yes, n = no)\n\nYour answer: ");
    scanf(" %c", &confirm);
    int temp;
    switch (confirm)
    {
        case 'y':
            temp = 1;
            break;
        case 'n':
            temp = 0;
            break;
        default:
            temp = 0;
            break;
    } 
    return temp;
}

void writeDebugInfo(int axisY, int axisX, int Input, int positionX, int positionY, int targetX, int targetY, int count)
{
    gotoxy(8,(axisY + 2));
    printf("%d ", Input);
    gotoxy(14,(axisY + 3));
    printf("%d ", positionX);
    gotoxy(14,(axisY + 4));
    printf("%d ", positionY);
    gotoxy(12,(axisY + 5));
    printf("%d ", targetX);
    gotoxy(12,(axisY + 6));
    printf("%d ", targetY);
    gotoxy(8,(axisY + 7));
    printf("%d  ", count);
    for (int i = 1; i < axisY - 1; i++)
    {
        gotoxy((axisX + 4), i);
        printf("Tail %d: %d %d ", i, tail[i].x, tail[i].y);
    }
    gotoxy((axisX + 4), axisY - 1);
    printf("---------------");
    gotoxy((axisX + 4), axisY);
    printf("\033[1;32mTail count: %d\033[0m", count);
}

int CheckForInput(int Input, int cas)
{
    int count = 0;
    while (count < 5)
    {
        if(kbhit())
        {
            Input = getch();
        }
        Sleep(cas);
        count++;
    }
    return Input;
}

int LoadX()
{
    int loadX;
    gotoxy(10,7);
    char str[] = "Please choose length of rectangle (X) and then height of rectangle (Y).";
    int i;
    int strLength = strlen(str);
    for (i = 0; i < strLength; i++)
    {
        printf("%c", str[i]);
        Sleep(35);
    }
    Sleep(2000);
    gotoxy(10,8);
    printf("-----------------");
    gotoxy(10,9);
    char str1[] = "Choose \"X\": ";
    int y;
    int strLength1 = strlen(str1);
    for (y = 0; y < strLength1; y++)
    {
        printf("%c", str1[y]);
        Sleep(50);
    }
    scanf("%d", &loadX);
    return (loadX);
}

int LoadY()
{
    int loadY;
    gotoxy(10,10);
    char str[] = "Choose \"Y\": ";
    int i;
    int strLength = strlen(str);
    for (i = 0; i < strLength; i++)
    {
        printf("%c", str[i]);
        Sleep(50);
    }
    scanf("%d", &loadY);
    return (loadY);
}

void renderSnake(int positionX, int positionY, int count, int prevPositionX, int prevPositionY)
{
    for (int i = count; i >= 2; i--)
    {
        if (i != 0 && i != 1)
        {
            int tempX = tail[i].x;
            int tempY = tail[i].y;
            tail[i].x = tail[i-1].x;
            tail[i].y = tail[i-1].y;
            gotoxy(tail[i].x, tail[i].y);
            printf("\033[1;32m○\033[0m");
            if (i == count)
            {
            gotoxy(tempX, tempY);
            printf("\033[1;32m \033[0m");    
            }
            gotoxy(1,1);
            printf("\033[1;32m○\033[0m");
            
        }        
    }

    for (int i = 0; i <= count; i++)
    {
        if (i == 0)
        {
            tail[i].x = positionX;
            tail[i].y = positionY;
            gotoxy(tail[0].x, tail[0].y);
            printf("\033[1;32m⬤\033[0m");
            gotoxy(prevPositionX, prevPositionY);
            printf("\033[1;32m \033[0m");
        }
       
        if (i == 1)
        {
            
            int tempX = tail[i].x;
            int tempY = tail[i].y;
            tail[i].x = prevPositionX;
            tail[i].y = prevPositionY;
            // tail[i+1].x = tempX;
            // tail[i+1].y = tempY;
            gotoxy(tail[i].x, tail[i].y);
            printf("\033[1;32m○\033[0m");
            if (count < 2)
            {
                gotoxy(tempX, tempY);
                printf("\033[1;32m \033[0m");
            } 
        } 
    }
}

void renderTarget(int targetX, int targetY)
{
    gotoxy(targetX, targetY);
    printf("\033[0;33m+\033[0m");
}

void renderGameField(int axisX, int axisY)
{
    system("cls");
    for (int i = 1; i <= axisY; i++)
    {
        if (i == 1)
        {
            printf("╔");
            for (int y = 1; y <= (axisX - 2); y++)
            {
                printf("═");
            }
            printf("╗\n");
        }
        else if (i == axisY)
        {
            printf("╚");
            for (int y = 1; y <= (axisX - 2); y++)
            {
                printf("═");
            }
            printf("╝\n");
        }
        else
        {
            printf("║");
            for (int y = 1; y <= (axisX - 2); y++)
            {
                printf(" ");
            }
            printf("║\n");
        }
    }
}

int CalculatePositionX(int positionX, int Input)
{
    int temp = positionX;
    switch (Input)
    {
        case 72:
            break;
        case 80:
            break;
        case 75:
            temp--;
            break;
        case 77:
            temp++;
            break;
        default:
            break;
    }
    tail[0].x = temp;
    return temp;    
}

int CalculatePositionY(int positionY, int Input)
{
    int temp = positionY;
    switch (Input)
    {
        case 72:
            temp--;
            break;
        case 80:
            temp++;
            break;
        case 75:
            break;
        case 77:
            break;
        default:
            break;
    }
    tail[0].y = temp;

    return temp;
}

int TargetPositionX(int axisX)
{
    int target = rand() % (axisX - 2);
    switch (target)
    {
        case 0:
            target = 2;
            break;
        case 1:
            target = 2;
            break;
    }
    return target;
}

int TargetPositionY(int axisY)
{
    int target = rand() % (axisY - 2);
    switch (target)
    {
        case 0:
            target = 2;
            break;
        case 1:
            target = 2;
            break;
    }
    return target;
}

bool targetCheck(int positionX, int positionY, int targetX, int targetY)
{
    if (positionX == targetX && positionY == targetY)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkForGameOver(int positionX, int positionY, int axisX, int axisY, bool game)
{
    int tempGame = game;
    if (positionX == 1 || positionX == axisX || positionY == 1 || positionY == axisY)
    {
        tempGame = 0;
    }
    return tempGame;
}

void gameOver(int axisX, int axisY, int count)
{
    gotoxy(((axisX / 2) - 6), ((axisY / 2) - 1));
    printf("\033[0;31m╔══════════════╗\033[0m");
    gotoxy(((axisX / 2) - 6), (axisY / 2));
    printf("\033[0;31m║  GAME OVER!  ║\033[0m");
    gotoxy(((axisX / 2) - 6), ((axisY / 2) + 1));
    printf("\033[0;31m╚══════════════╝\033[0m");
    gotoxy(1,(axisY + 8));
    Sleep(3000);
    system("cls");
    printf("Your score was: %d.\nCongratulations!\n", count);
    Sleep(1000);
}

void easterEgg()
{
    system("title what?...");
    char str[] = "...what the hell man?";
    int i;
    int strLength = strlen(str);

    for (i = 0; i < strLength; i++)
    {
        printf("%c", str[i]);
        Sleep(50);
    }
    Sleep(2000);
    system("cls");

    char str2[] = "How would you do that?";
    strLength = strlen(str2);

    for (i = 0; i < strLength; i++)
    {
        printf("%c", str2[i]);
        Sleep(50);
    }
    Sleep(2000);
    system("cls");
    
    char str3[] = "Do you really think this program ";
    strLength = strlen(str3);

    for (i = 0; i < strLength; i++)
    {
        printf("%c", str3[i]);
        Sleep(50);
    }

    char str4[] = "CAN WORK WITH RECTANGLE HEIGHT OR LENGTH ZERO??";
    strLength = strlen(str4);

    for (i = 0; i < strLength; i++)
    {
        printf("\033[1;31m%c", str4[i]);
        Sleep(50);
    }
    Sleep(2000);
    printf("\033[0m\n");
    system("cls");
    return 0;
}

int HardcoreMode()
{

    char hard;
    int temp;
    gotoxy(10,11);
    char str[] = "Do you want to play in hardcore mode? (y = yes, n = no): ";
    int i;
    int strLength = strlen(str);
    for (i = 0; i < strLength; i++)
    {
        printf("%c", str[i]);
        Sleep(35);
    }
    scanf(" %c", &hard);
    switch (hard)
    {
        case 'y':
            temp = 1;
            break;
        case 'n':
            temp = 60;
            break;
        case 'r':
            temp = 44;
            break;
        default:
            temp = 60;
            break;
    }
    gotoxy(10,13);
    printf("Loading...");
    return temp;
}

void ShowMainMenu()
{
    system("cls");
    printf("\n ╔");
    for (int i = 1; i < 117; i++)
    {
        printf("═");
    }
    printf("╗\n");
    for (int i = 1; i <= 26; i++)
    {
        printf(" ║");
        for (int y = 1; y < 117; y++)
        { 
            printf(" ");
        }
        printf("║\n");    
    }
    printf(" ╚");
    for (int i = 1; i < 117; i++)
    {
        printf("═");
    }
    printf("╝");

        // zde je main menu

    gotoxy(10,5);
    printf("\033[0;32m");
    char str[] = "Welcome to this very simple game Snake";
    int i;
    int strLength = strlen(str);

    for (i = 0; i < strLength; i++)
    {
        printf("%c", str[i]);
        Sleep(40);
    }
    
    gotoxy(71, 17);
    printf("    _________         _________");
    gotoxy(71, 18);
    printf("   /         \\       /         \\");
    gotoxy(71, 19);
    printf("  /  /~~~~~\\  \\     /  /~~~~~\\  \\");
    gotoxy(71, 20);
    printf("  |  |     |  |     |  |     |  |");
    gotoxy(71, 21);
    printf("  |  |     |  |     |  |     |  |");
    gotoxy(71, 22);
    printf("  |  |     |  |     |  |     |  |         /");
    gotoxy(71, 23);
    printf("  |  |     |  |     |  |     |  |       //");
    gotoxy(71, 24);
    printf(" (o  o)    \\  \\_____/  /     \\  \\_____/ /");
    gotoxy(71, 25);
    printf("  \\__/      \\         /       \\        /");
    gotoxy(71, 26);
    printf("   |         ~~~~~~~~~         ~~~~~~~~");
    gotoxy(71, 27);
    printf("   ^");
    printf("\033[0m\n");
    Sleep(2000);

//    _________         _________
//   /         \       /         \   Normand
//  /  /~~~~~\  \     /  /~~~~~\  \  Veilleux
//  |  |     |  |     |  |     |  |
//  |  |     |  |     |  |     |  |
//  |  |     |  |     |  |     |  |         /
//  |  |     |  |     |  |     |  |       //
// (o  o)    \  \_____/  /     \  \_____/ /
//  \__/      \         /       \        /
//   |         ~~~~~~~~~         ~~~~~~~~
//   ^

}

void Credits()
{
    system("cls");
    system("title Thank you for playing:)");
    gotoxy(5,3);
    char str[] = "This game was made by Radomir Cech.";
    int i;
    int strLength = strlen(str);
    for (i = 0; i < strLength; i++)
    {
        printf("%c", str[i]);
        Sleep(35);
    }
    Sleep(1000);
    gotoxy(5,4);
    char str1[] = "I hope you enjoyed this prototype.";
    int strLength1 = strlen(str1);
    for (i = 0; i < strLength1; i++)
    {
        printf("%c", str1[i]);
        Sleep(35);
    }
    Sleep(1000);
    gotoxy(5,6);
    char str2[] = ":)";
    int strLength2 = strlen(str2);
    for (i = 0; i < strLength2; i++)
    {
        printf("%c", str2[i]);
        Sleep(100);
    }
    Sleep(3000);
    system("cls");
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    system("title Snake (alpha) - Welcome");
    int game = welcomeScreen();
    if (game == 1)
    {
        bool egg = 0;
        bool targetFound = 0;
        system("title Snake (alpha) - Settings");
        ShowMainMenu();
        int axisX = LoadX();    
        int axisY = LoadY();
        int cas = HardcoreMode(); 
        if (cas == 44)
        {
            game = 0;
        }
        Sleep(2000);
        system("cls");
        if (axisX == 0 || axisY == 0)
        {
            int axisX = 10;
            int axisY = 10;
            egg = 1;
            game = 0;
        }
        positionX = ((axisX + 2) / 2);
        positionY = ((axisY + 2) / 2);
        int Input = 77;
        int targetX = TargetPositionX(axisX);
        int targetY = TargetPositionY(axisY);
        int count = 0;
        prevPositionX = (axisX / 2);
        prevPositionY = (axisY / 2);
        system("title Snake (alpha) - Game");
        renderGameField(axisX, axisY);
        printf("\033[1;36m\nDebug: \n");
        printf("Position X = \nPosition Y = \nTarget X = \nTarget Y = \n\033[1;32mFound: \033[0m");        
        renderTarget(targetX, targetY);
        tail[0].x = positionX;
        tail[0].y = positionY;
        tail[1].x = targetX;
        tail[1].y = targetY;
        while (game == 1)
        {
            targetFound = targetCheck(positionX, positionY, targetX, targetY);
            if (targetFound == 1)
            {
                targetX = TargetPositionX(axisX);
                targetY = TargetPositionY(axisY);
                renderTarget(targetX, targetY);
                targetFound = 0;
                count++;
            }
            prevPositionX = positionX;
            prevPositionY = positionY;
            positionX = CalculatePositionX(positionX, Input);
            positionY = CalculatePositionY(positionY, Input);
            renderSnake(positionX, positionY, count, prevPositionX, prevPositionY);
            writeDebugInfo(axisY, axisX, Input, positionX, positionY, targetX, targetY, count);
            game = checkForGameOver(positionX, positionY, axisX, axisY, game);
            Input = CheckForInput(Input, cas);
        }
        if (egg == 1)
        {
            system("cls");
            easterEgg();
        }
        else if (cas == 44)
        {
            Credits();
        }
        else 
        {
            system("title Snake (alpha) - Game Over");
            gameOver(axisX, axisY, count);
        }
        }
    return 0;
}