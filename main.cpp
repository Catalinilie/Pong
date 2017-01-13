#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <MMSystem.h>
using namespace std;
void SetColor(int value)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}
void ShowConsoleCursor()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out,&cursorInfo);
    cursorInfo.bVisible = 0;
    SetConsoleCursorInfo(out,&cursorInfo);
}
void ClearScreen(int x, int y)
{
    COORD p = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),p);
}
enum directions { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };
class Ball
{
private:
    int x, y;
    int originalX, originalY;
    directions direction;
public:

    Ball(int posX, int posY)
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
    void changdirectionsection(directions d)
    {
        direction = d;
    }
    void directieRandom()
    {
        direction = (directions)((rand() % 6) + 1);
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
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    directions getDirection()
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
    {
        switch (direction)
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
class Paddle
{
private:
    int x, y;
    int originalX, originalY;
public:
    Paddle()
    {
        x = y = 0;
    }
    Paddle(int posX, int posY) : Paddle()
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
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    void moveUp()
    {
        y--;
    }
    void moveDown()
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
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    void moveUp()
    {
        y--;
    }
    void moveDown()
    {
        y++;
    }

};
//AI game manager
class aiGameManger
{
private:
    int width, height,dif=4,obs=0,q=4;
    int score1, score2;
    char up1, down1,res;
    bool quit,reset;
    int d;
    Ball * ball;
    Paddle *player;
    AI *ai;
public:
    aiGameManger(int w, int h,int di,int ob)
    {
        //srand(time(NULL));
        quit = false;
        reset=false;
        up1 = 'w';
        down1 = 's';
        res='r';
        d=di;
        obs=ob;
        score1 = score2 = 0;
        width = w;
        height = h;
        if(d==1) q=3;
        else if(d==2) q=5;
        else q=6;




        ball = new Ball(w / 2, h / 2);
        player = new Paddle(1, h / 2 - 2);
        ai = new AI(w - 2, h / 2 - 2);
    }
    void Reset()
    {
        ball->Reset();
        ball->changdirectionsection(STOP);
        player->Reset();
        ai->Reset();
    }
    void ScoreUpPlayer(Paddle * player)
    {

        score1++;



        ball->Reset();
        player->Reset();
        ai->Reset();
    }
    void ScoreUpAi(AI *ai)
    {
        score2++;
        ball->Reset();
        player->Reset();
        ai->Reset();
    }

    void Draw()
    {
        ShowConsoleCursor();
        ClearScreen(0,0);
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player->getX();
        int player2x = ai->getX();
        int player1y = player->getY();
        int player2y = ai->getY();

        SetColor(11);

        for (int i = 0; i < width+2; i++)
            cout << "\xB2";
        cout << "\n";

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {


                if (j == 0)
                    cout << "\xB2";

                if (ballx == j && bally == i)
                {
                    SetColor(15);
                    cout << "O"; //ball
                }

                else if(obs==1 &&j==width/2 && i<height/3)
                {
                    SetColor(11);
                    cout << "\xB2";
                }
                else if(obs==1 && j==width/2 && i>(2*height)/3)
                {
                    SetColor(11);
                    cout << "\xB2";
                }
                else if (player1x == j && player1y == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
                else if (player2x == j && player2y == i)
                {
                    SetColor(12);
                    cout << "\xB2";
                } //player2

                else if (player1x == j && player1y + 1 == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
                else if (player1x == j && player1y + 2 == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
                else if (player1x == j && player1y + 3 == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
                else if (player1x == j && player1y + 4 == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1

                else if (player2x == j && player2y + 1 == i)
                {
                    SetColor(12);
                    cout << "\xB2";
                } //player1
                else if (player2x == j && player2y + 2 == i)
                {
                    SetColor(12);
                    cout << "\xB2";
                } //player1
                else if (player2x == j && player2y + 3 == i)
                {
                    SetColor(12);
                    cout << "\xB2";
                } //player1
                else if (player2x == j && player2y + 4 == i)
                {
                    SetColor(12);
                    cout << "\xB2";
                } //player1
                else
                    cout << " ";

                if (j == width - 1)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
            }
            cout << "\n";
        }

        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << "\n";
        SetColor(10);
        cout << "Score Player: " << score1 << "\n" << "Score AI: " << score2 << "\n";
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


            if (current == down1)
                if (player1y + 5 < height)
                    player->moveDown();


            if (ball->getDirection() == STOP)
                ball->directieRandom();

            if (current == 'q')
                quit = true;
            if (current == 'r')
                Reset();
        }
        if(ballx > width/4*(4-d) && ball->directiedreapta() && dif%q!=0)
        {
            unsigned int u= (unsigned int)((rand() % 3) +1);
            if(bally<player2y+u  && player2y>0) ai->moveUp();
            else if(bally>player2y+u && player2y+5<height) ai->moveDown();
        }
        ++dif;
    }
    void Logic()
    {


        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player->getX();
        int player2x = ai->getX();
        int player1y = player->getY();
        int player2y = ai->getY();

        //left paddle
        if (ballx == player1x + 1)
            if (bally == player1y || bally==player1y+1)
                ball->changdirectionsection(UPRIGHT);
            else if(bally==player1y+2)
                ball->changdirectionsection(RIGHT);
            else if(bally==player1y+3||bally==player1y+4)ball->changdirectionsection(DOWNRIGHT);


        //right paddle

        if (ballx == player2x - 1)
            if (bally == player2y || bally==player2y+1 )
                ball->changdirectionsection(UPLEFT);
            else if(bally==player2y+2)
                ball->changdirectionsection(LEFT);
            else if(bally==player2y+3||bally==player2y+4) ball->changdirectionsection(DOWNLEFT);

        //right wall
        if (ballx == width - 1)
            ScoreUpPlayer(player);
        //left wall
        if (ballx == 0)
            ScoreUpAi(ai);
        //obstacole
        if(obs==1)
        {
            if(ballx==width/2-1 || ballx==width/2+1)
                if(bally<height/3 || bally>(2*height)/3)
                    ball->directieOpusa();
            if(ballx==width/2)
                if( bally==height/3+1 || bally>(2 * height) / 3 -1)

                    ball->directieOpusaPerete();
        }



        //bottom wall
        if (bally == height - 1)
            ball->directieOpusaPerete();
        //top wall
        if (bally == 0)
            ball->directieOpusaPerete();

        ball->Move();
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
    int score1, score2,obs;
    char up1, down1, up2, down2,res;
    bool quit;
    Ball * ball;
    Paddle *player1;
    Paddle *player2;
public:
    cGameManger(int w, int h,int ob)
    {
        obs=ob;
        srand(time(NULL));
        quit = false;
        up1 = 'w';
        up2 = 'i';
        down1 = 's';
        down2 = 'k';
        res='r';
        score1 = score2 = 0;
        width = w;
        height = h;
        ball = new Ball(w / 2, h / 2);
        player1 = new Paddle(1, h / 2 - 2);
        player2 = new Paddle(w - 2, h / 2 - 2);
    }
    void Reset()
    {
        ball->Reset();
        ball->changdirectionsection(STOP);
        player1->Reset();
        player2->Reset();
    }
    void ScoreUp(Paddle * player)
    {
        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;

        ball->Reset();
        player1->Reset();
        player2->Reset();
    }
    void Draw()
    {
        ShowConsoleCursor();
        ClearScreen(0,0);
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        SetColor(11);

        for (int i = 0; i < width+2; i++)
            cout << "\xB2";
        cout << "\n";

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {


                if (j == 0)
                    cout << "\xB2";

                if (ballx == j && bally == i)
                {
                    SetColor(15);
                    cout << "O"; //ball
                }
                else if(obs==1 &&j==width/2 && i<height/3)
                {
                    SetColor(11);
                    cout << "\xB2";
                }
                else if(obs==1&&j ==width/2 && i>(2*height)/3)
                {
                    SetColor(11);
                    cout << "\xB2";
                }
                else if (player1x == j && player1y == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
                else if (player2x == j && player2y == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player2

                else if (player1x == j && player1y + 1 == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
                else if (player1x == j && player1y + 2 == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
                else if (player1x == j && player1y + 3 == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
                else if (player1x == j && player1y + 4 == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1

                else if (player2x == j && player2y + 1 == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
                else if (player2x == j && player2y + 2 == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
                else if (player2x == j && player2y + 3 == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
                else if (player2x == j && player2y + 4 == i)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
                else
                    cout << " ";

                if (j == width - 1)
                {
                    SetColor(11);
                    cout << "\xB2";
                } //player1
            }
            cout << "\n";
        }

        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << "\n";
        SetColor(10);
        cout << "Score Player 1: " << score1 << "\n" << "Score Player 2: " << score2 << "\n";
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
                ball->directieRandom();

            if (current == 'q')
                quit = true;
            if(current =='r')
                Reset();
        }
    }
    void Logic()
    {
        int ballix = ball->getX();
        int balliy = ball->getY();

        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();


        //bottom wall
        //paleta stanga
        //for (int i = 0; i < 5; i++)
        if (ballx == player1x + 1)
            if (bally == player1y || bally==player1y+1)
                ball->changdirectionsection(UPRIGHT);
            else if(balliy==player1y+2)
                ball->changdirectionsection(RIGHT);
            else if(bally==player1y+3||bally==player1y+4)ball->changdirectionsection(DOWNRIGHT);
        //ball->changdirectionsection((directions)((rand() % 3) + 4));

        //right paddle
        //for (int i = 0; i < 5; i++)
        if (ballx == player2x - 1)
            if (bally == player2y || bally==player2y+1 )
                ball->changdirectionsection(UPLEFT);
            else if(bally==player2y+2)
                ball->changdirectionsection(LEFT);
            else if(bally==player2y+3||bally==player2y+4) ball->changdirectionsection(DOWNLEFT);
        //right wall
        if (ballx == width - 1)
            ScoreUp(player1);
        //left wall
        if (ballx == 0)
            ScoreUp(player2);

        //obstacole
        if(obs==1)
        {
            if(ballx==width/2-1 || ballx==width/2+1)
                if(bally<height/3 || bally>(2*height)/3)
                    ball->directieOpusa();
            if(ballx==width/2)
                if( bally==height/3+1 || bally>(2 * height) / 3 -1)
                    ball->directieOpusaPerete();
        }


        //bottom wall
        if (bally == height - 1)
            ball->directieOpusaPerete();
        //top wall
        if (bally == 0)
            ball->directieOpusaPerete();
        ball->Move();
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
{
    PlaySound(TEXT("Celtic_Music_-_Moonsong_1_ (3)"), NULL, SND_FILENAME | SND_ASYNC );
    int y,z,q,height=91,width=25;
    SetColor(11);
    cout << "Tipul jocului:" << "\n";
    cout << "1.Normal" << "\n";
    cout << "2.Obstacol" << "\n";
    cin >> z;
    if (z == 1)
    {
        cout << "1.jucator vs jucator" << "\n";
        cout << "2.Vs Computer" << "\n";
        cin >> y;
        if (y == 2)
        {
            cout << "Nivel de dificultate:" << "\n";
            cout << "1.Usor" << "\n";
            cout << "2.Normal" << "\n";
            cout << "3.Greu" << "\n";
            cin >> q;
        }
        if (y == 1)
        {
            cout << "\xDB" << "\n";
            PlaySound(TEXT("Celtic Music - Síocháin Shuthain.wav"), NULL, SND_FILENAME | SND_ASYNC  );
            cGameManger c(height, width,0);
            c.Run();
        }
        else if (y == 2)
        {
            cout << "\xDB" << "\n";
            PlaySound(TEXT("Celtic Music - Síocháin Shuthain.wav"), NULL, SND_FILENAME | SND_ASYNC  );
            aiGameManger c(height, width, q,0);
            c.Run();
        }
    }
    else if (z==2)
    {
        cout << "1.jucator vs jucator" << "\n";
        cout << "2.Vs Computer" << "\n";
        cin >> y;
        if (y == 2)
        {
            cout << "Nivel de dificultate:" << "\n";
            cout << "1.Usor" << "\n";
            cout << "2.Normal" << "\n";
            cout << "3.Greu" << "\n";
            cin >> q;
        }
        if (y == 1)
        {
            cout << "\xDB" << "\n";
            PlaySound(TEXT("Celtic Music - Síocháin Shuthain.wav"), NULL, SND_FILENAME | SND_ASYNC  );
            cGameManger c(height, width,1);
            c.Run();
        }
        else if (y == 2)
        {
            cout << "\xDB" << "\n";
            PlaySound(TEXT("Celtic Music - Síocháin Shuthain.wav"), NULL, SND_FILENAME | SND_ASYNC  );
            aiGameManger c(height, width, q,1);
            c.Run();
        }
    }

    return 0;
}
