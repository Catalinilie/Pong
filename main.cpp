#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <MMSystem.h>
using namespace std;
enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };
class cBall
{
private:
    int x, y;
    int originalX, originalY;
eDir direction;
public:

    cBall(int posX, int posY)
    {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        direction = STOP;
    }
    void Reset()
    {
        x = originalX;
        y = originalY;
        direction = STOP;
    }
    void changeDirection(eDir d)
    {
        direction = d;
    }
    void randomDirection()
    {
        direction = (eDir)((rand() % 6) + 1);
    }
    void directieOpusa()
    {
        if(direction==LEFT) direction=RIGHT;
        else if(direction==UPLEFT) direction=UPRIGHT;
        else if(direction==DOWNLEFT) direction=DOWNRIGHT;
        else if(direction==RIGHT) direction=LEFT;
        else if(direction==UPRIGHT) direction=UPLEFT;
        else if(direction==DOWNRIGHT) direction=DOWNLEFT;

    }
    void directieOpusaPerete()
    {
        if(direction==DOWNLEFT) direction=UPLEFT;
        else if(direction==DOWNRIGHT) direction=UPRIGHT;
        else if(direction==UPLEFT) direction=DOWNLEFT;
        else direction=DOWNRIGHT;
    }
    inline int getX()
    {
        return x;
    }
    inline int getY()
    {
        return y;
    }
    inline eDir getDirection()
    {
        return direction;
    }

    void Move()
    {
        switch (direction)
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
    {switch (direction)
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
    /*friend ostream & operator<<(ostream & o, cBall c)
    {
    	o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
    	return o;
    }
    */
    }
};
class cPaddle
{
private:
    int x, y;
    int originalX, originalY;
public:
    cPaddle()
    {
        x = y = 0;
    }
    cPaddle(int posX, int posY) : cPaddle()
    {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }

    void Reset()
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
//AI
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
    AI(int posX, int posY) : AI()
    {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }

    void Reset()
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
//AI game manager
class aiGameManger
{
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    int d;
    cBall * ball;
    cPaddle *player;
    AI *ai;
public:
    aiGameManger(int w, int h,int di)
    {
        srand(time(NULL));
        quit = false;
        up1 = 'w';

        down1 = 's';
d=di;
        score1 = score2 = 0;
        width = w;
        height = h;

        ball = new cBall(w / 2, h / 2);
        player = new cPaddle(1, h / 2 - 2);
        ai = new AI(w - 2, h / 2 - 2);
    }
    ~aiGameManger()
    {
        delete ball, player, ai;
    }
    void ScoreUpPlayer(cPaddle * player)
    {

            score1++;



        ball->Reset();
        player->Reset();
        ai->Reset();
    }
    void ScoreUpAi(AI *ai)
    {score2++;
     ball->Reset();
        player->Reset();
        ai->Reset();
    }
    void ClearScreen(int x, int y)
    {
        COORD p = {x,y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),p);
    }
    void Draw()
    {
        ClearScreen(0,0);
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player->getX();
        int player2x = ai->getX();
        int player1y = player->getY();
        int player2y = ai->getY();

        for (int i = 0; i < width+2; i++)
            cout << "\xB2";
        cout << endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {


                if (j == 0)
                    cout << "\xB2";

                if (ballx == j && bally == i)
                    cout << "O"; //ball
                else if(j==width/2 && i<height/3)
                    cout << "\xB2";
                else if(j==width/2 && i>(2*height)/3)
                    cout << "\xB2";
                else if (player1x == j && player1y == i)
                    cout << "\xDB"; //player1
                else if (player2x == j && player2y == i)
                    cout << "\xDB"; //player2

                else if (player1x == j && player1y + 1 == i)
                    cout << "\xDB"; //player1
                else if (player1x == j && player1y + 2 == i)
                    cout << "\xDB"; //player1
                else if (player1x == j && player1y + 3 == i)
                    cout << "\xDB"; //player1
                else if (player1x == j && player1y + 4 == i)
                    cout << "\xDB"; //player1

                else if (player2x == j && player2y + 1 == i)
                    cout << "\xDB"; //player1
                else if (player2x == j && player2y + 2 == i)
                    cout << "\xDB"; //player1
                else if (player2x == j && player2y + 3 == i)
                    cout << "\xDB"; //player1
                else if (player2x == j && player2y + 4 == i)
                    cout << "\xDB"; //player1
                else
                    cout << " ";

                if (j == width - 1)
                    cout << "\xB2";
            }
            cout << "\n";
        }

        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << "\n";

        cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
    }
    void Input()
    {

        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player->getX();
        int player2x = ai->getX();
        int player1y = player->getY();
        int player2y = ai->getY();

        if (kbhit())
        {
            char current = getch();
            if (current == up1)
                if (player1y > 0)
                    player->moveUp();
            if (current == up2)
                if (player2y > 0)
                    ai->moveUp();
            if (current == down1)
                if (player1y + 5 < height)
                    player->moveDown();
            if (current == down2)
                if (player2y + 5 < height)
                    ai->moveDown();

            if (ball->getDirection() == STOP)
                ball->randomDirection();

            if (current == 'q')
                quit = true;
        }
        if(ballx > width/4*(4-d) && ball->directiedreapta())
        {unsigned int u= (unsigned int)((rand() % 3) +1);
        if(bally<player2y+u  && player2y>0) ai->moveUp();
        else if(bally>player2y+u && player2y+5<height) ai->moveDown();
        }

    }
    void Logic()
    {

        ball->Move();
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player->getX();
        int player2x = ai->getX();
        int player1y = player->getY();
        int player2y = ai->getY();

        //ai
        //if(bally<player2y+3  && player2y>0) ai->moveUp();
        //else if(bally>player2y+3 && player2y+5<height) ai->moveDown();




        //right wall
        if (ballx == width - 1)
            ScoreUpPlayer(player);
        //left wall
        if (ballx == 0)
            ScoreUpAi(ai);
        //bottom wall
        //paleta stanga
        //for (int i = 0; i < 5; i++)
        if (ballx == player1x + 1)
            if (bally == player1y || bally==player1y+1)
                ball->changeDirection(UPRIGHT);
            else if(bally==player1y+2)
                ball->changeDirection(RIGHT);
            else if(bally==player1y+3||bally==player1y+4)ball->changeDirection(DOWNRIGHT);
        //ball->changeDirection((eDir)((rand() % 3) + 4));

        //right paddle
        //for (int i = 0; i < 5; i++)
        if (ballx == player2x - 1)
            if (bally == player2y || bally==player2y+1 )
                ball->changeDirection(UPLEFT);
            else if(bally==player2y+2)
                ball->changeDirection(LEFT);
            else if(bally==player2y+3||bally==player2y+4) ball->changeDirection(DOWNLEFT);


        //obstacole
        if(ballx==width/2-1 || ballx==width/2+1)
            if(bally<height/3 || bally>(2*height)/3)
                ball->directieOpusa();




        //bottom wall
        if (bally == height - 1)
            ball->directieOpusaPerete();
        //top wall
        if (bally == 0)
            ball->directieOpusaPerete();
        //ai

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



// 2 players game manager
class cGameManger
{
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    cBall * ball;
    cPaddle *player1;
    cPaddle *player2;
public:
    cGameManger(int w, int h)
    {
        srand(time(NULL));
        quit = false;
        up1 = 'w';
        up2 = 'i';
        down1 = 's';
        down2 = 'k';
        score1 = score2 = 0;
        width = w;
        height = h;
        ball = new cBall(w / 2, h / 2);
        player1 = new cPaddle(1, h / 2 - 2);
        player2 = new cPaddle(w - 2, h / 2 - 2);
    }
    ~cGameManger()
    {
        delete ball, player1, player2;
    }
    void ScoreUp(cPaddle * player)
    {
        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;

        ball->Reset();
        player1->Reset();
        player2->Reset();
    }
    void ClearScreen(int x, int y)
    {
        COORD p = {x,y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),p);
    }
    void Draw()
    {
        ClearScreen(0,0);
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        for (int i = 0; i < width+2; i++)
            cout << "\xB2";
        cout << endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {


                if (j == 0)
                    cout << "\xB2";

                if (ballx == j && bally == i)
                    cout << "O"; //ball
                else if(j==width/2 && i<height/3)
                    cout << "\xB2";
                else if(j==width/2 && i>(2*height)/3)
                    cout << "\xB2";
                else if (player1x == j && player1y == i)
                    cout << "\xDB"; //player1
                else if (player2x == j && player2y == i)
                    cout << "\xDB"; //player2

                else if (player1x == j && player1y + 1 == i)
                    cout << "\xDB"; //player1
                else if (player1x == j && player1y + 2 == i)
                    cout << "\xDB"; //player1
                else if (player1x == j && player1y + 3 == i)
                    cout << "\xDB"; //player1
                else if (player1x == j && player1y + 4 == i)
                    cout << "\xDB"; //player1

                else if (player2x == j && player2y + 1 == i)
                    cout << "\xDB"; //player1
                else if (player2x == j && player2y + 2 == i)
                    cout << "\xDB"; //player1
                else if (player2x == j && player2y + 3 == i)
                    cout << "\xDB"; //player1
                else if (player2x == j && player2y + 4 == i)
                    cout << "\xDB"; //player1
                else
                    cout << " ";

                if (j == width - 1)
                    cout << "\xB2";
            }
            cout << "\n";
        }

        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << "\n";

        cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
    }
    void Input()
    {

        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        if (kbhit())
        {
            char current = getch();
            if (current == up1)
                if (player1y > 0)
                    player1->moveUp();
            if (current == up2)
                if (player2y > 0)
                    player2->moveUp();
            if (current == down1)
                if (player1y + 5 < height)
                    player1->moveDown();
            if (current == down2)
                if (player2y + 5 < height)
                    player2->moveDown();

            if (ball->getDirection() == STOP)
                ball->randomDirection();

            if (current == 'q')
                quit = true;
        }
    }
    void Logic()
    {
        int ballix = ball->getX();
        int balliy = ball->getY();
        ball->Move();
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        //right wall
        if (ballx == width - 1)
            ScoreUp(player1);
        //left wall
        if (ballx == 0)
            ScoreUp(player2);
        //bottom wall
        //paleta stanga
        //for (int i = 0; i < 5; i++)
        if (ballx == player1x + 1)
            if (bally == player1y || bally==player1y+1)
                ball->changeDirection(UPRIGHT);
            else if(balliy==player1y+2)
                ball->changeDirection(RIGHT);
            else if(bally==player1y+3||bally==player1y+4)ball->changeDirection(DOWNRIGHT);
        //ball->changeDirection((eDir)((rand() % 3) + 4));

        //right paddle
        //for (int i = 0; i < 5; i++)
        if (ballx == player2x - 1)
            if (bally == player2y || bally==player2y+1 )
                ball->changeDirection(UPLEFT);
            else if(bally==player2y+2)
                ball->changeDirection(LEFT);
            else if(bally==player2y+3||bally==player2y+4) ball->changeDirection(DOWNLEFT);


        //obstacole
        if(ballx==width/2-1 || ballx==width/2+1)
            if(bally<height/3 || bally>(2*height)/3)
                ball->directieOpusa();




        //bottom wall
        if (bally == height - 1)
            ball->directieOpusaPerete();
        //top wall
        if (bally == 0)
            ball->directieOpusaPerete();
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
int main()
{/*
    cGameManager: 2 jucatori
    aiGameManager: 1 jucator
    al treilea parametru:dificultatea(0 1 2 3 sau 4)
    */
    cout<<"\xDB"<<"\n";


      PlaySound(TEXT("1.wav"), NULL, SND_FILENAME | SND_ASYNC);

    aiGameManger c(81, 25,2);
    c.Run();
    return 0;
}
