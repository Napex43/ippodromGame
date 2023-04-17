#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <string>
#include <math.h>

#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13

#pragma comment(lib, "winmm.lib")

using namespace std;

void Image(int xScreen, int yScreen, LPCSTR image)
{
	HWND hWnd = GetForegroundWindow();
	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

	HDC hdc = GetDC(hWnd);


	HBITMAP hBmp = (HBITMAP)LoadImageA(NULL, image, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	HDC hMemDC = CreateCompatibleDC(hdc);
	SelectObject(hMemDC, hBmp);

	BITMAP bmp;
	GetObject(hBmp, sizeof(BITMAP), &bmp);
	BitBlt(hdc, xScreen, yScreen, bmp.bmWidth, bmp.bmHeight, hMemDC, 0, 0, SRCCOPY);

	DeleteDC(hMemDC);
	DeleteObject(hBmp);
	ReleaseDC(hWnd, hdc);
}

void Circle(HWND hW, int xCenter, int yCenter, int radius, COLORREF borderColor, COLORREF fillColor)
{
	HDC hDC = GetDC(hW);
	HPEN hPen = CreatePen(PS_SOLID, 1, borderColor);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hBrush = CreateSolidBrush(fillColor);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC, xCenter - radius, yCenter - radius, xCenter + radius, yCenter + radius);

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
	ReleaseDC(hW, hDC);
}

void Ride(int x, int* sum)
{
	int h1 = -10, h2 = -10, h3 = -10;
	HDC hdc = GetDC(GetConsoleWindow());
	HBRUSH brush = CreateSolidBrush(RGB(52, 163, 255));
	HBRUSH brush1 = CreateSolidBrush(RGB(30, 30, 30));
	HBRUSH brush2 = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH brush3 = CreateSolidBrush(RGB(255, 100, 100));
	cout << "GO!";

	while (true)	
	{
		while (h1 < 931 && h2 < 931 && h3 < 931)
		{
			h1 += 5 + rand() % 10;
			h2 += 5 + rand() % 10;
			h3 += 5 + rand() % 10;

			SelectObject(hdc, brush);
			Rectangle(hdc, 0, 200, 1200, 500);

			Image(h1, 210, "horse1//6.bmp");
			Image(h2, 303, "horse2//6.bmp");
			Image(h3, 395, "horse3//6.bmp");
			Image(1050, 201, "finish.bmp");
			Sleep(40);
			Image(h1, 210, "horse1//5.bmp");
			Image(h2, 303, "horse2//5.bmp");
			Image(h3, 395, "horse3//5.bmp");
			Image(1050, 201, "finish.bmp");
			Sleep(40);
			Image(h1, 210, "horse1//4.bmp");
			Image(h2, 303, "horse2//4.bmp");
			Image(h3, 395, "horse3//4.bmp");
			Image(1050, 201, "finish.bmp");
			Sleep(40);
			Image(h1, 210, "horse1//3.bmp");
			Image(h2, 303, "horse2//3.bmp");
			Image(h3, 395, "horse3//3.bmp");
			Image(1050, 201, "finish.bmp");
			Sleep(40);
			Image(h1, 210, "horse1//2.bmp");
			Image(h2, 303, "horse2//2.bmp");
			Image(h3, 395, "horse3//2.bmp");
			Image(1050, 201, "finish.bmp");
			Sleep(40);
			Image(h1, 210, "horse1//1.bmp");
			Image(h2, 303, "horse2//1.bmp");
			Image(h3, 395, "horse3//1.bmp");
			Image(1050, 201, "finish.bmp");
			Sleep(40);
		}
		if (x == 1)
			x = h1;
		if (x == 2)
			x = h2;
		if (x == 3)
			x = h3;
		printf("\nРасстояние 1 = %d", h1);
		printf("\nРасстояние 2 = %d", h2);
		printf("\nРасстояние 3 = %d", h3);
		if (x >= h1 && x >= h2 && x >= h3)
		{
			printf("\nИгрок выйграл!!!    ");
			*sum += 2000;
			PlaySound(L"C:\\Projects\\RGR_Ippodrom\\win.WAV", NULL, SND_NODEFAULT | SND_LOOP);
		}
		else
		{
			printf("\nИгрок пройграл      ");
			PlaySound(L"C:\\Projects\\RGR_Ippodrom\\lose.WAV", NULL, SND_NODEFAULT | SND_LOOP);
		}
		break;
	}
	system("pause");
}

void pos(int x, int y)
{
	COORD pos;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hand, pos);
}

int ippodrom()
{
	SetConsoleTitle(L"Главное меню");
	setlocale(0, "RUS");
	srand(time(NULL));

	int n, sum = 10000;
	int player;

	while (true)
	{
		system("CLS");
		pos(45, 0);
		cout << "Ваши деньги - " << sum << endl;
		cout << "На какой номер поставите? От 1 до 3. Для выхода введите 0" << endl;
		cin >> n;
		if (sum >= 1000)
		{
			switch (n)
			{
			case 1: player = 1; sum -= 1000; Ride(player, &sum); break;
			case 2: player = 2; sum -= 1000; Ride(player, &sum); break;
			case 3: player = 3; sum -= 1000; Ride(player, &sum); break;
			case 0: cout << "До встречи!"; _getch(); return 0;
			default: cout << "ОШИБКА: Выберите от 1 до 3"; _getch(); break;
			}
		}	
		else
		{
			cout << "У вас нехватает денег. Ставки окончены" << endl;
			_getch();
			return 0;
		}
	}
}

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
// Текстовый курсор в точку x,y
void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

// Видимость курсора
void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show; // изменяем видимость курсора
	structCursorInfo.dwSize = size; // изменяем размер курсора
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

// Об авторе

void author()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = 45;
	position.Y = 7;
	SetConsoleCursorPosition(color, position);
	printf("_______________________________");
	position.X = 44;
	position.Y = 8;
	SetConsoleCursorPosition(color, position);
	printf("|                               |");
	position.X = 44;
	position.Y = 9;
	SetConsoleCursorPosition(color, position);
	printf("|        >");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("Студент ОмГТУ");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("<        | ");
	position.X = 44;
	position.Y = 10;
	SetConsoleCursorPosition(color, position);
	printf("|_______________________________|");
	position.X = 44;
	position.Y = 11;
	SetConsoleCursorPosition(color, position);
	printf("|                               |");
	position.X = 44;
	position.Y = 12;
	SetConsoleCursorPosition(color, position);
	printf("|       >");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("Группы ПИ - 221");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("<       | ");
	position.X = 44;
	position.Y = 13;
	SetConsoleCursorPosition(color, position);
	printf("|_______________________________|");
	position.X = 44;
	position.Y = 14;
	SetConsoleCursorPosition(color, position);
	printf("|                               |");
	position.X = 44;
	position.Y = 15;
	SetConsoleCursorPosition(color, position);
	printf("|  >Алтынбаев Наиль Дамирович<  |");
	position.X = 44;
	position.Y = 16;
	SetConsoleCursorPosition(color, position);
	printf("|_______________________________|\n");
	_getche();
}

// Графическая заставка

void Line(HWND hW, int x0, int y0, int x1, int y1, COLORREF color)
{
	HDC hDC = GetDC(hW);
	HPEN hPen = CreatePen(PS_SOLID, 2, color);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	POINT p = { 0, 0 };
	GetCurrentPositionEx(hDC, &p);
	MoveToEx(hDC, x0, y0, &p);
	LineTo(hDC, x1, y1);

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	ReleaseDC(hW, hDC);
}

void Picture(HWND hW, int dx, int dy, int mode)
{
	COLORREF border = RGB(255, 255, 0), fill = RGB(127, 127, 0), line = RGB(0, 255, 0), black = RGB(0, 0, 0);
	if (!mode)
		border = fill = line = black;
	int x0 = 50, y0 = 50, r = 10;

	system("cls");
	Circle(hW, x0 + dx, y0 + dy, r, border, fill);
	Line(hW, x0 + dx, y0 + dy + r, x0 + dx, y0 + dy + r + 30, line);
	Line(hW, x0 + dx, y0 + dy + r + 30, x0 + dx - 10, y0 + dy + r + 70, line);
	Line(hW, x0 + dx, y0 + dy + r + 30, x0 + dx + 10, y0 + dy + r + 60, line);
	Line(hW, x0 + dx - 5, y0 + dy + r + 7, x0 + dx + 5, y0 + dy + r + 2, line);
	Line(hW, x0 + dx - 5, y0 + dy + r + 7, x0 + dx - 10, y0 + dy + r + 20, line);
	Line(hW, x0 + dx + 5, y0 + dy + r + 2, x0 + dx + 10, y0 + dy + r + 20, line);
	Sleep(400);
	system("cls");
	Circle(hW, x0 + dx, y0 + dy, r, border, fill);
	Line(hW, x0 + dx, y0 + dy + r, x0 + dx, y0 + dy + r + 30, line);
	Line(hW, x0 + dx, y0 + dy + r + 30, x0 + dx - 10, y0 + dy + r + 60, line);
	Line(hW, x0 + dx, y0 + dy + r + 30, x0 + dx + 10, y0 + dy + r + 70, line);
	Line(hW, x0 + dx - 5, y0 + dy + r + 7, x0 + dx + 5, y0 + dy + r + 2, line);
	Line(hW, x0 + dx - 5, y0 + dy + r + 7, x0 + dx - 10, y0 + dy + r + 5, line);
	Line(hW, x0 + dx + 5, y0 + dy + r + 2, x0 + dx + 10, y0 + dy + r + 25, line);
}


void animation(HANDLE& hStdOut)
{
	HWND hW = GetConsoleWindow();
	int step = -1;

	for (; !_kbhit(); ++step)
	{
		Picture(hW, 5 * step, 0, 2);

		if (step > 100)
			step = -10;
		Sleep(100);
	}
	Sleep(400);
	system("cls");
	_getch();
	return;
}

// Графики
#define graph1(x) (2 * sin(2 * x + 1)) 
#define graph2(x) (pow((x + 5), 3) * (1 + pow(sin(x), 2)))
void graphs()
{
	bool first = true;
	bool second = true;
	HWND hwn = GetConsoleWindow();
	HDC hdc = GetDC(hwn);
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = 27;
	position.Y = 19;
	SetConsoleCursorPosition(color, position);
	SetConsoleTextAttribute(color, 4);
	printf("F1=2*sin(2*x+1)");
	SetConsoleTextAttribute(color, 15);
	position.X = 0;
	position.Y = 5;
	SetConsoleCursorPosition(color, position);
	SetConsoleTextAttribute(color, 9);
	printf("F2=(x+5)^3*1+sin(x)^2");
	SetConsoleTextAttribute(color, 15);
	float x;
	HDC draw = GetDC(GetConsoleWindow());
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	Sleep(50);
	SelectObject(draw, pen);

	int zaseh;
	for (zaseh = 0; zaseh < 440; zaseh += 10)
	{
		MoveToEx(draw, zaseh, 353, NULL);
		LineTo(draw, zaseh, 347);
	}
	int zaseh2;
	for (zaseh2 = 0; zaseh2 < 440; zaseh2 += 10)
	{
		MoveToEx(draw, 223, zaseh2, NULL);
		LineTo(draw, 217, zaseh2);
	}

	MoveToEx(draw, 0, 350, NULL);
	LineTo(draw, 440, 350);

	MoveToEx(draw, 440, 350, NULL);
	LineTo(draw, 435, 345);

	MoveToEx(draw, 440, 350, NULL);
	LineTo(draw, 435, 355);

	MoveToEx(draw, 220, 25, NULL);
	LineTo(draw, 220, 470);

	MoveToEx(draw, 220, 25, NULL);
	LineTo(draw, 225, 30);

	MoveToEx(draw, 220, 25, NULL);
	LineTo(draw, 215, 30);

	TextOutA(hdc, 445, 340, "X", 1);
	TextOutA(hdc, 216, 5, "Y", 1);
	DeleteObject(pen);
	for (x = -15.0f; x <= 10.0f; x += 0.01f)
	{
		SetPixel(hdc, 10 * x + 220, 350 - 9 * graph1(x), RGB(255, 0, 0));
		if (first)
		{
			pen = CreatePen(PS_DASHDOT, 2, RGB(255, 0, 0));
			SelectObject(hdc, pen);
			MoveToEx(hdc, 10 * x + 220, 350 - 9 * graph1(x), NULL);
			first = false;
		}
		else LineTo(hdc, 10 * x + 220, 350 - 9 * graph1(x));
	}
	for (x = -15.0f; x <= 10.0f; x += 0.01f)
	{
		SetPixel(hdc, 10 * x + 220, 350 - 9 * graph2(x), RGB(0, 100, 255));
		if (second)
		{
			pen = CreatePen(PS_DASHDOT, 2, RGB(0, 100, 255));
			SelectObject(hdc, pen);
			MoveToEx(hdc, 10 * x + 220, 350 - 9 * graph2(x), NULL);
			second = false;
		}
		else LineTo(hdc, 10 * x + 220, 350 - 9 * graph2(x));
	}
	Sleep(10);
	_getche();
}

// Меню

int main()
{
	SetConsoleTitle(L"Главное меню");
	system("CLS");
	setlocale(0, "RUS");
	ConsoleCursorVisible(false, 100);

	string Zagolovok = { " Главное меню " };
	string Menu[] = { "Об авторе", "Графическая заставка", "Построение графиков", "Игра Ипподром", "Выход" };
	int active_menu = 0;
	char ch;
	while (true)
	{
		int x = 49, y = 10;
		GoToXY(x, y);

		for (int i = 0; i < size(Menu); i++)
		{
			if (i == active_menu) SetConsoleTextAttribute(hStdOut, 9 | FOREGROUND_INTENSITY);

			else SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			GoToXY(x, y++);
			cout << Menu[i] << endl;
		}

		ch = _getch();
		if (ch == -32) ch = _getch(); // Отлавливаем стрелочки
		switch (ch)
		{
		case ESC:
			exit(0);
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < size(Menu) - 1)
				++active_menu;
			break;
		case ENTER:
			switch (active_menu)
			{
			case 0: system("CLS");
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				author();
				system("CLS");
				break;
			case 1: system("CLS");
				animation(hStdOut);
				system("CLS");
				break;
			case 2: system("CLS");
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				graphs();
				system("CLS");
				break;
			case 3:
				system("CLS");
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				ippodrom();
				system("CLS");
				break;
			case 4:
				exit(0);
			}
			break;
		}
	}
}
