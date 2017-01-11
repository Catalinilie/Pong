#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <MMSystem.h>
using namespace std;
enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };
class cMinge
{
private:
	int x, y;
	int originalX, originalY;
	eDir directie;
public:
	cMinge(int pozX, int pozY)
	{
		originalX = pozX;
		originalY = pozY;
		x = pozX;
		y = pozY;
		directie = STOP;
	}
	void Reseteaza()
	{
		x = originalX;
		y = originalY;
		directie = STOP;
	}
	void schimbaDirectia(eDir d)
	{
		directie = d;
	}
	void randomdirectie()
	{
		directie = (eDir)((rand() % 6) + 1);
	}
	void directieOpusa()
	{
		if (directie == LEFT) directie = RIGHT;
		else if (directie == UPLEFT) directie = UPRIGHT;
		else if (directie == DOWNLEFT) directie = DOWNRIGHT;
		else if (directie == RIGHT) directie = LEFT;
		else if (directie == UPRIGHT) directie = UPLEFT;
		else if (directie == DOWNRIGHT) directie = DOWNLEFT;
	}
	void directieOpusaPerete()
	{
		if (directie == DOWNLEFT) directie = UPLEFT;
		else if (directie == DOWNRIGHT) directie = UPRIGHT;
		else if (directie == UPLEFT) directie = DOWNLEFT;
		else directie = DOWNRIGHT;
	}
	inline int getX()
	{
		return x;
	}
	inline int getY()
	{
		return y;
	}
	inline eDir getdirectie()
	{
		return directie;
	}
	void Move()
	{
		switch (directie)
		{
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--;
			y--;
			break;
		case DOWNLEFT:
			x--;
			y++;
			break;
		case UPRIGHT:
			x++;
			y--;
			break;
		case DOWNRIGHT:
			x++;
			y++;
			break;
		default:
			break;
		}
	}
	bool directiedreapta()
	{
		switch (directie)
		{
		case RIGHT:
			return true;
		case UPRIGHT:
			return true;
			break;
		case DOWNRIGHT:
			return true;
		default:
			return false;

		}
	}
};
class cPaleta
{
private:
	int x, y;
	int originalX, originalY;
public:
	cPaleta()
	{
		x = y = 0;
	}
	cPaleta(int pozX, int pozY) : cPaleta()
	{
		originalX = pozX;
		originalY = pozY;
		x = pozX;
		y = pozY;
	}
	void Reseteaza()
	{
		x = originalX;
		y = originalY;
	}
	inline int getX()
	{
		return x;
	}
	inline int getY()
	{
		return y;
	}
	inline void moveUp()
	{
		y--;
	}
	inline void moveDown()
	{
		y++;
	}
};
class AI
{
private:
	int x, y;
	int originalX, originalY;
public:
	AI()
	{
		x = y = 0;
	}
	AI(int pozX, int pozY) : AI()
	{
		originalX = pozX;
		originalY = pozY;
		x = pozX;
		y = pozY;
	}

	void Reseteaza()
	{
		x = originalX;
		y = originalY;
	}
	inline int getX()
	{
		return x;
	}
	inline int getY()
	{
		return y;
	}
	inline void moveUp()
	{
		y--;
	}
	inline void moveDown()
	{
		y++;
	}

};
class aiGameManger
{
private:
	int latime, inaltime;
	int scor1, scor2;
	char up1, down1, up2, down2;
	bool quit;
	int d;
	cMinge * minge;
	cPaleta *jucator;
	AI *ai;
public:
	aiGameManger(int w, int h, int di)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w';

		down1 = 's';
		d = di;
		scor1 = scor2 = 0;
		latime = w;
		inaltime = h;

		minge = new cMinge(w / 2, h / 2);
		jucator = new cPaleta(1, h / 2 - 2);
		ai = new AI(w - 2, h / 2 - 2);
	}
	void ScorUpjucator(cPaleta * jucator)
	{
		scor1++; 
		minge->Reseteaza();
		jucator->Reseteaza();
		ai->Reseteaza();
	}
	void ScorUpAi(AI *ai)
	{
		scor2++;
		minge->Reseteaza(ScoreUpjucator);
		jucator->Reseteaza();
		ai->Reseteaza();
	}
	void ClearScreen(int x, int y)
	{
		COORD p = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	}
	void Draw()
	{
		ClearScreen(0, 0);
		int mingex = minge->getX();
		int mingey = minge->getY();
		int jucator1x = jucator->getX();
		int jucator2x = ai->getX();
		int jucator1y = jucator->getY();
		int jucator2y = ai->getY();
		for (int i = 0; i < latime + 2; i++)
			cout << "\xB2";
		cout << endl;
		for (int i = 0; i < inaltime; i++)
		{
			for (int j = 0; j < latime; j++)
			{
				if (j == 0)
					cout << "\xB2";
				if (mingex == j && mingey == i)
					cout << "O"; 
				else if (jucator1x == j && jucator1y == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y == i)
					cout << "\xDB"; 

				else if (jucator1x == j && jucator1y + 1 == i)
					cout << "\xDB"; 
				else if (jucator1x == j && jucator1y + 2 == i)
					cout << "\xDB"; 
				else if (jucator1x == j && jucator1y + 3 == i)
					cout << "\xDB"; 
				else if (jucator1x == j && jucator1y + 4 == i)
					cout << "\xDB"; 

				else if (jucator2x == j && jucator2y + 1 == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y + 2 == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y + 3 == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y + 4 == i)
					cout << "\xDB"; 
				else
					cout << " ";
				if (j == latime - 1)
					cout << "\xB2";
			}
			cout << "\n";
		}
		for (int i = 0; i < latime + 2; i++)
			cout << "\xB2";
		cout << "\n";
		cout << "Score 1: " << scor1 << endl << "Score 2: " << scor2 << endl;
	}
	void Input()
	{
		int mingex = minge->getX();
		int mingey = minge->getY();
		int jucator1x = jucator->getX();
		int jucator2x = ai->getX();
		int jucator1y = jucator->getY();
		int jucator2y = ai->getY();
		if (_kbhit())
		{
			char curent = _getch();
			if (curent == up1)
				if (jucator1y > 0)
					jucator->moveUp();
			if (curent == up2)
				if (jucator2y > 0)
					ai->moveUp();
			if (curent == down1)
				if (jucator1y + 5 < inaltime)
					jucator->moveDown();
			if (curent == down2)
				if (jucator2y + 5 < inaltime)
					ai->moveDown();
			if (minge->getdirectie() == STOP)
				minge->randomdirectie();
			if (curent == 'q')
				quit = true;
		}
		if (mingex > latime / 4 * (4 - d) && minge->directiedreapta())
		{
			unsigned int u = (unsigned int)((rand() % 3) + 1);
			if (mingey<jucator2y + u  && jucator2y>0) ai->moveUp();
			else if (mingey>jucator2y + u && jucator2y + 5<inaltime) ai->moveDown();
		}
	}
	void Logic()
	{

		minge->Move();
		int mingex = minge->getX();
		int mingey = minge->getY();
		int jucator1x = jucator->getX();
		int jucator2x = ai->getX();
		int jucator1y = jucator->getY();
		int jucator2y = ai->getY();
		if (mingex == latime - 1)
			ScorUpjucator(jucator);
		if (mingex == 0)
			ScorUpAi(ai);
		if (mingex == jucator1x + 1)
			if (mingey == jucator1y || mingey == jucator1y + 1)
				minge->schimbaDirectia(UPRIGHT);
			else if (mingey == jucator1y + 2)
				minge->schimbaDirectia(RIGHT);
			else if (mingey == jucator1y + 3 || mingey == jucator1y + 4)minge->schimbaDirectia(DOWNRIGHT);
			if (mingex == jucator2x - 1)
				if (mingey == jucator2y || mingey == jucator2y + 1)
					minge->schimbaDirectia(UPLEFT);
				else if (mingey == jucator2y + 2)
					minge->schimbaDirectia(LEFT);
				else if (mingey == jucator2y + 3 || mingey == jucator2y + 4) minge->schimbaDirectia(DOWNLEFT);
				if (mingex == latime / 2 - 1 || mingex == latime / 2 + 1)
					if (mingey<inaltime / 3 || mingey>(2 * inaltime) / 3)
						minge->directieOpusa();
				if (mingey == inaltime - 1)
					minge->directieOpusaPerete();
				if (mingey == 0)
					minge->directieOpusaPerete();
	}
	void Run()
	{
		while (!quit)
		{
			Draw();
			Input();
			Logic();
		}
	}
};
class aiGameMangers
{
private:
	int latime, inaltime;
	int scor1, scor2;
	char up1, down1, up2, down2;
	bool quit;
	int d;
	cMinge * minge;
	cPaleta *jucator;
	AI *ai;
public:
	aiGameMangers(int w, int h, int di)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w';

		down1 = 's';
		d = di;
		scor1 = scor2 = 0;
		latime = w;
		inaltime = h;

		minge = new cMinge(w / 2, h / 2);
		jucator = new cPaleta(1, h / 2 - 2);
		ai = new AI(w - 2, h / 2 - 2);
	}
	void ScorUpjucator(cPaleta * jucator)
	{
		scor1++;
		minge->Reseteaza();
		jucator->Reseteaza();
		ai->Reseteaza();
	}
	void ScorUpAi(AI *ai)
	{
		scor2++;
		minge->Reseteaza();
		jucator->Reseteaza();
		ai->Reseteaza();
	}
	void ClearScreen(int x, int y)
	{
		COORD p = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	}
	void Draw()
	{
		ClearScreen(0, 0);
		int mingex = minge->getX();
		int mingey = minge->getY();
		int jucator1x = jucator->getX();
		int jucator2x = ai->getX();
		int jucator1y = jucator->getY();
		int jucator2y = ai->getY();
		for (int i = 0; i < latime + 2; i++)
			cout << "\xB2";
		cout << endl;
		for (int i = 0; i < inaltime; i++)
		{
			for (int j = 0; j < latime; j++)
			{
				if (j == 0)
					cout << "\xB2";

				if (mingex == j && mingey == i)
					cout << "O"; 
				else if (j == latime / 2 && i<inaltime / 3)
					cout << "\xB2";
				else if (j == latime / 2 && i>(2 * inaltime) / 3)
					cout << "\xB2";
				else if (jucator1x == j && jucator1y == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y == i)
					cout << "\xDB"; 

				else if (jucator1x == j && jucator1y + 1 == i)
					cout << "\xDB";
				else if (jucator1x == j && jucator1y + 2 == i)
					cout << "\xDB"; 
				else if (jucator1x == j && jucator1y + 3 == i)
					cout << "\xDB"; 
				else if (jucator1x == j && jucator1y + 4 == i)
					cout << "\xDB"; 

				else if (jucator2x == j && jucator2y + 1 == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y + 2 == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y + 3 == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y + 4 == i)
					cout << "\xDB"; 
					cout << " ";

				if (j == latime - 1)
					cout << "\xB2";
			}
			cout << "\n";
		}
		for (int i = 0; i < latime + 2; i++)
			cout << "\xB2";
		cout << "\n";
		cout << "Score 1: " << scor1 << endl << "Score 2: " << scor2 << endl;
	}
	void Input()
	{
		int mingex = minge->getX();
		int mingey = minge->getY();
		int jucator1x = jucator->getX();
		int jucator2x = ai->getX();
		int jucator1y = jucator->getY();
		int jucator2y = ai->getY();
		if (_kbhit())
		{
			char curent = _getch();
			if (curent == up1)
				if (jucator1y > 0)
					jucator->moveUp();
			if (curent == up2)
				if (jucator2y > 0)
					ai->moveUp();
			if (curent == down1)
				if (jucator1y + 5 < inaltime)
					jucator->moveDown();
			if (curent == down2)
				if (jucator2y + 5 < inaltime)
					ai->moveDown();

			if (minge->getdirectie() == STOP)
				minge->randomdirectie();

			if (curent == 'q')
				quit = true;
		}
		if (mingex > latime / 4 * (4 - d) && minge->directiedreapta())
		{
			unsigned int u = (unsigned int)((rand() % 3) + 1);
			if (mingey<jucator2y + u  && jucator2y>0) ai->moveUp();
			else if (mingey>jucator2y + u && jucator2y + 5<inaltime) ai->moveDown();
		}

	}
	void Logic()
	{
		minge->Move();
		int mingex = minge->getX();
		int mingey = minge->getY();
		int jucator1x = jucator->getX();
		int jucator2x = ai->getX();
		int jucator1y = jucator->getY();
		int jucator2y = ai->getY();
		if (mingex == latime - 1)
			ScorUpjucator(jucator);
		if (mingex == 0)
			ScorUpAi(ai);
		if (mingex == jucator1x + 1)
			if (mingey == jucator1y || mingey == jucator1y + 1)
				minge->schimbaDirectia(UPRIGHT);
			else if (mingey == jucator1y + 2)
				minge->schimbaDirectia(RIGHT);
			else if (mingey == jucator1y + 3 || mingey == jucator1y + 4)minge->schimbaDirectia(DOWNRIGHT);
			if (mingex == jucator2x - 1)
				if (mingey == jucator2y || mingey == jucator2y + 1)
					minge->schimbaDirectia(UPLEFT);
				else if (mingey == jucator2y + 2)
					minge->schimbaDirectia(LEFT);
				else if (mingey == jucator2y + 3 || mingey == jucator2y + 4) minge->schimbaDirectia(DOWNLEFT);
				if (mingex == latime / 2 - 1 || mingex == latime / 2 + 1)
					if (mingey<inaltime / 3 || mingey>(2 * inaltime) / 3)
						minge->directieOpusa();
				if (mingey == inaltime - 1)
					minge->directieOpusaPerete();
				if (mingey == 0)
					minge->directieOpusaPerete();
	}
	void Run()
	{
		while (!quit)
		{
			Draw();
			Input();
			Logic();
		}
	}
};
class cGameMangers
{
private:
	int latime, inaltime;
	int scor1, scor2;
	char up1, down1, up2, down2;
	bool quit;
	cMinge * minge;
	cPaleta *jucator1;
	cPaleta *jucator2;
public:
	cGameMangers(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w';
		up2 = 'i';
		down1 = 's';
		down2 = 'k';
		scor1 = scor2 = 0;
		latime = w;
		inaltime = h;
		minge = new cMinge(w / 2, h / 2);
		jucator1 = new cPaleta(1, h / 2 - 2);
		jucator2 = new cPaleta(w - 2, h / 2 - 2);
	}
	void ScoreUp(cPaleta * jucator)
	{
		if (jucator == jucator1)
			scor1++;
		else if (jucator == jucator2)
			scor2++;
		minge->Reseteaza();
		jucator1->Reseteaza();
		jucator2->Reseteaza();
	}
	void ClearScreen(int x, int y)
	{
		COORD p = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	}
	void Draw()
	{
		ClearScreen(0, 0);
		for (int i = 0; i < latime + 2; i++)
			cout << "\xB2";
		cout << endl;
		for (int i = 0; i < inaltime; i++)
		{
			for (int j = 0; j < latime; j++)
			{
				int mingex = minge->getX();
				int mingey = minge->getY();
				int jucator1x = jucator1->getX();
				int jucator2x = jucator2->getX();
				int jucator1y = jucator1->getY();
				int jucator2y = jucator2->getY();

				if (j == 0)
					cout << "\xB2";

				if (mingex == j && mingey == i)
					cout << "O";
				else if (jucator1x == j && jucator1y == i)
					cout << "\xDB";
				else if (jucator2x == j && jucator2y == i)
					cout << "\xDB"; 

				else if (jucator1x == j && jucator1y + 1 == i)
					cout << "\xDB"; 
				else if (jucator1x == j && jucator1y + 2 == i)
					cout << "\xDB"; 
				else if (jucator1x == j && jucator1y + 3 == i)
					cout << "\xDB"; 

				else if (jucator2x == j && jucator2y + 1 == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y + 2 == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y + 3 == i)
					cout << "\xDB"; 
				else
					cout << " ";

				if (j == latime - 1)
					cout << "\xB2";
			}
			cout << endl;
		}

		for (int i = 0; i < latime + 2; i++)
			cout << "\xB2";
		cout << endl;
		cout << "Score 1: " << scor1 << endl << "Score 2: " << scor2 << endl;
	}
	void Input()
	{
		int mingex = minge->getX();
		int mingey = minge->getY();
		int jucator1x = jucator1->getX();
		int jucator2x = jucator2->getX();
		int jucator1y = jucator1->getY();
		int jucator2y = jucator2->getY();
		if (_kbhit())
		{
			char curent = _getch();
			if (curent == up1)
				if (jucator1y > 0)
					jucator1->moveUp();
			if (curent == up2)
				if (jucator2y > 0)
					jucator2->moveUp();
			if (curent == down1)
				if (jucator1y + 5 < inaltime)
					jucator1->moveDown();
			if (curent == down2)
				if (jucator2y + 5 < inaltime)
					jucator2->moveDown();

			if (minge->getdirectie() == STOP)
				minge->randomdirectie();

			if (curent == 'q')
				quit = true;
		}
	}
	void Logic()
	{
		int mingeix = minge->getX();
		int mingeiy = minge->getY();
		minge->Move();
		int mingex = minge->getX();
		int mingey = minge->getY();
		int jucator1x = jucator1->getX();
		int jucator2x = jucator2->getX();
		int jucator1y = jucator1->getY();
		int jucator2y = jucator2->getY();
		if (mingex == latime - 1)
			ScoreUp(jucator1);
		if (mingex == 0)
			ScoreUp(jucator2);
		if (mingex == jucator1x + 1)
			if (mingey == jucator1y || mingey == jucator1y + 1)
				minge->schimbaDirectia(UPRIGHT);
			else if (mingeiy == jucator1y + 2)
				minge->schimbaDirectia(RIGHT);
			else if (mingey == jucator1y + 3 || mingey == jucator1y + 4)minge->schimbaDirectia(DOWNRIGHT);
			if (mingex == jucator2x - 1)
				if (mingey == jucator2y || mingey == jucator2y + 1)
					minge->schimbaDirectia(UPLEFT);
				else if (mingey == jucator2y + 2)
					minge->schimbaDirectia(LEFT);
				else if (mingey == jucator2y + 3 || mingey == jucator2y + 4) minge->schimbaDirectia(DOWNLEFT);
				if (mingex == latime / 2 - 1 || mingex == latime / 2 + 1)
					if (mingey<inaltime / 3 || mingey>(2 * inaltime) / 3)
						minge->directieOpusa();
				if (mingey == inaltime - 1)
					minge->directieOpusaPerete();
				if (mingey == 0)
					minge->directieOpusaPerete();
	}
	void Run()
	{
		while (!quit)
		{
			Draw();
			Input();
			Logic();
		}
	}
};
class cGameManger
{
private:
	int latime, inaltime;
	int scor1, scor2;
	char up1, down1, up2, down2;
	bool quit;
	cMinge * minge;
	cPaleta *jucator1;
	cPaleta *jucator2;
public:
	cGameManger(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w';
		up2 = 'i';
		down1 = 's';
		down2 = 'k';
		scor1 = scor2 = 0;
		latime = w;
		inaltime = h;
		minge = new cMinge(w / 2, h / 2);
		jucator1 = new cPaleta(1, h / 2 - 2);
		jucator2 = new cPaleta(w - 2, h / 2 - 2);
	}
	void ScoreUp(cPaleta * jucator)
	{
		if (jucator == jucator1)
			scor1++;
		else if (jucator == jucator2)
			scor2++;

		minge->Reseteaza();
		jucator1->Reseteaza();
		jucator2->Reseteaza();
	}
	void ClearScreen(int x, int y)
	{
		COORD p = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	}
	void Draw()
	{
		ClearScreen(0, 0);
		int mingex = minge->getX();
		int mingey = minge->getY();
		int jucator1x = jucator1->getX();
		int jucator2x = jucator2->getX();
		int jucator1y = jucator1->getY();
		int jucator2y = jucator2->getY();

		for (int i = 0; i < latime + 2; i++)
			cout << "\xB2";
		cout << endl;

		for (int i = 0; i < inaltime; i++)
		{
			for (int j = 0; j < latime; j++)
			{


				if (j == 0)
					cout << "\xB2";

				if (mingex == j && mingey == i)
					cout << "O"; 
				else if (j == latime / 2 && i<inaltime / 3)
					cout << "\xB2";
				else if (j == latime / 2 && i>(2 * inaltime) / 3)
					cout << "\xB2";
				else if (jucator1x == j && jucator1y == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y == i)
					cout << "\xDB"; 

				else if (jucator1x == j && jucator1y + 1 == i)
					cout << "\xDB"; 
				else if (jucator1x == j && jucator1y + 2 == i)
					cout << "\xDB"; 
				else if (jucator1x == j && jucator1y + 3 == i)
					cout << "\xDB"; 
				else if (jucator1x == j && jucator1y + 4 == i)
					cout << "\xDB";

				else if (jucator2x == j && jucator2y + 1 == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y + 2 == i)
					cout << "\xDB";
				else if (jucator2x == j && jucator2y + 3 == i)
					cout << "\xDB"; 
				else if (jucator2x == j && jucator2y + 4 == i)
					cout << "\xDB"; 
				else
					cout << " ";

				if (j == latime - 1)
					cout << "\xB2";
			}
			cout << "\n";
		}
		for (int i = 0; i < latime + 2; i++)
			cout << "\xB2";
		cout << "\n";

		cout << "Score 1: " << scor1 << endl << "Score 2: " << scor2 << endl;
	}
	void Input()
	{
		int mingex = minge->getX();
		int mingey = minge->getY();
		int jucator1x = jucator1->getX();
		int jucator2x = jucator2->getX();
		int jucator1y = jucator1->getY();
		int jucator2y = jucator2->getY();
		if (_kbhit())
		{
			char curent = _getch();
			if (curent == up1)
				if (jucator1y > 0)
					jucator1->moveUp();
			if (curent == up2)
				if (jucator2y > 0)
					jucator2->moveUp();
			if (curent == down1)
				if (jucator1y + 5 < inaltime)
					jucator1->moveDown();
			if (curent == down2)
				if (jucator2y + 5 < inaltime)
					jucator2->moveDown();

			if (minge->getdirectie() == STOP)
				minge->randomdirectie();

			if (curent == 'q')
				quit = true;
		}
	}
	void Logic()
	{
		int mingeix = minge->getX();
		int mingeiy = minge->getY();
		minge->Move();
		int mingex = minge->getX();
		int mingey = minge->getY();
		int jucator1x = jucator1->getX();
		int jucator2x = jucator2->getX();
		int jucator1y = jucator1->getY();
		int jucator2y = jucator2->getY();
		if (mingex == latime - 1)
			ScoreUp(jucator1);
		if (mingex == 0)
			ScoreUp(jucator2);
		if (mingex == jucator1x + 1)
			if (mingey == jucator1y || mingey == jucator1y + 1)
				minge->schimbaDirectia(UPRIGHT);
			else if (mingeiy == jucator1y + 2)
				minge->schimbaDirectia(RIGHT);
			else if (mingey == jucator1y + 3 || mingey == jucator1y + 4)minge->schimbaDirectia(DOWNRIGHT);
			if (mingex == jucator2x - 1)
				if (mingey == jucator2y || mingey == jucator2y + 1)
					minge->schimbaDirectia(UPLEFT);
				else if (mingey == jucator2y + 2)
					minge->schimbaDirectia(LEFT);
				else if (mingey == jucator2y + 3 || mingey == jucator2y + 4) minge->schimbaDirectia(DOWNLEFT);
				if (mingex == latime / 2 - 1 || mingex == latime / 2 + 1)
					if (mingey<inaltime / 3 || mingey>(2 * inaltime) / 3)
						minge->directieOpusa();
				if (mingey == inaltime - 1)
					minge->directieOpusaPerete();
				if (mingey == 0)
					minge->directieOpusaPerete();
	}
	void Run()
	{
		while (!quit)
		{
			Draw();
			Input();
			Logic();
		}
	}
};
void main()
{
	int y,z,q;
	cout << "Tipul jocului:" << endl;
	cout << "1.Normal" << endl;
	cout << "2.Obstacol" << endl;
	cin >> z;
	if (z == 1)
	{
		cout << "1.jucator vs jucator" << endl;
		cout << "2.Vs Computer" << endl;
		cin >> y;
		if (y == 2)
		{
			cout << "Nivel de dificultate:" << endl;
			cout << "1.Usor" << endl;
			cout << "2.Normal" << endl;
			cout << "3.Greu" << endl;
			cin >> q;
		}
		if (y == 1)
		{
			cout << "\xDB" << "\n";
			cGameMangers c(61, 15);
			c.Run();
		}
		else if (y == 2)
		{
			cout << "\xDB" << "\n";
			aiGameManger c(61, 15, q);
			c.Run();
		}
	}
	else if (z==2)
	{
		cout << "1.jucator vs jucator" << endl;
		cout << "2.Vs Computer" << endl;
		cin >> y;
		if (y == 2)
		{
			cout << "Nivel de dificultate:" << endl;
			cout << "1.Usor" << endl;
			cout << "2.Normal" << endl;
			cout << "3.Greu" << endl;
			cin >> q;
		}
		if (y == 1)
		{
			cout << "\xDB" << "\n";
			cGameManger c(61, 15);
			c.Run();
		}
		else if (y == 2)
		{
			cout << "\xDB" << "\n";
			aiGameMangers c(61, 15, q);
			c.Run();
		}
	}
}
