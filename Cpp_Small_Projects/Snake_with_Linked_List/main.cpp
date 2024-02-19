#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

enum Color
{
    BLUE = 1,
    GREEN = 2, 
    AQUA = 3,
    RED = 4,
    PURPLE = 5,
    YELLOW = 6,
    WHITE = 7,
};
enum Direction
{
    LEFT = 0,
    TOP = 1,
    RIGHT = 2,
    BOTTOM = 3,
};
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
class snakeBodyLinkedList
{
    public:
        snakeBodyLinkedList(uint8_t xCoordinates, uint8_t yCoordinates)
        {
            this->xCoordinat = xCoordinates;
            this->yCoordinat = yCoordinates;
        }
        uint8_t xCoordinat;
        uint8_t yCoordinat;
        snakeBodyLinkedList* pNext;
        snakeBodyLinkedList* pPrev;
};
class snake
{
    public:
        
        snake()
        {
            this->paneColor = RED;
            initialize();
        }   
        snake(Color paneColor)
        {
            this->paneColor = paneColor;
            initialize();
        }   
        void play()
        {
            setPaneColor();
            createSurronding();
            gotoxy(10, 15);
            createSnake();
            generateFood();
            while(1)
            {
                inputProcessing();
                this->move();
                //generateFood();
                Sleep(100);
            }
        }
        void play2()
        {
            inputProcessing();
        }
        
    protected:
        Color paneColor;
        int horizontalPixels;
        int verticalPixels;
        snakeBodyLinkedList* pHead;
        snakeBodyLinkedList* pTail;
        Direction direction;
        bool directionChanged;
        int counter = 0;
        int FoodXCoordinate;
        int FoodYCoourdinate;
        int score;
        void initialize()
        {
            pHead = NULL;
            pTail = NULL;
            horizontalPixels = 110;
            verticalPixels = 28;
            directionChanged = false;
            direction = RIGHT;
            srand((unsigned) time(NULL));
            score = 0;
            ShowConsoleCursor(false);
        }
        void setPaneColor()
        {
            switch(paneColor)
            {
                case 1: // BLUE
                    system("Color 1");
                    break;
                case 2: // GREEN
                    system("Color 2");
                    break;
                case 3: // AQUA
                    system("Color 3");
                    break;
                case 4: // RED
                    system("Color 4");
                    break;
                case 5: // PURPLE
                    system("Color 5");
                    break;
                case 6: // YELLOW
                    system("Color 6");
                    break;
                case 7: // WHITE
                    system("Color 7");
                    break;
                default:
                    throw std::invalid_argument("Unknown color");
            }

        }
        void createSurronding()
        {
            for(int i = 0; i < verticalPixels; i++)
            {
                for(int j = 0; j < horizontalPixels; j++)
                {
                    if(i == 0 || i == verticalPixels - 1)
                    {
                        cout << "*";
                    }
                    else
                    {
                        if(j == 0 )
                        {
                            cout << "*";
                        }
                        else if(j == horizontalPixels - 1)
                        {
                            cout << "*";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                }
                cout << endl;
            }
        }
        void gotoxy(int x, int y)
        { 
            COORD pos = {x, y};
            HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleCursorPosition(output, pos);
        }
        void createSnake()
        {
            int xCoor = horizontalPixels / 2;
            int yCoor = verticalPixels / 2;
            gotoxy(xCoor, yCoor);

            snakeBodyLinkedList* node = new snakeBodyLinkedList(xCoor, yCoor);
            pTail = node;
            pHead = node;
            node->pPrev = NULL;
            node->pNext = NULL;
            cout << "*";

            snakeBodyLinkedList* node2 = new snakeBodyLinkedList(xCoor + 1, yCoor);
            node->pNext = node2;
            node2->pPrev = node;
            node2->pNext = NULL;
            node = node2;
            cout << "*";

            node2 = new snakeBodyLinkedList(xCoor + 2, yCoor);
            node->pNext = node2;
            node2->pPrev = node;
            node2->pNext = NULL;
            node = node2;
            cout << "*";

            node2 = new snakeBodyLinkedList(xCoor + 3, yCoor);
            node->pNext = node2;
            node2->pPrev = node;
            node2->pNext = NULL;
            node = node2;
            cout << "*";

            node2 = new snakeBodyLinkedList(xCoor + 3, yCoor);
            node->pNext = node2;
            node2->pPrev = node;
            node2->pNext = NULL;
            node = node2;
            pHead = node;
            cout << ">";
        }
        void move()
        {
            snakeBodyLinkedList* node = new snakeBodyLinkedList(pHead->xCoordinat, pHead->yCoordinat);
            snakeBodyLinkedList* temp = pHead->pPrev;
            temp->pNext = node;
            pHead->pPrev = node;
            if(directionChanged == false)
            {
                gotoxy(node->xCoordinat, node->yCoordinat);
                cout << "*";
                temp = pTail;
                
                
                switch(direction)
                {
                    case LEFT:
                        gotoxy(--pHead->xCoordinat, pHead->yCoordinat);
                        cout << "<";
                        break;
                    case TOP:
                        gotoxy(pHead->xCoordinat, --pHead->yCoordinat);
                        cout << "^";
                        break;
                    case RIGHT:
                        gotoxy(++pHead->xCoordinat, pHead->yCoordinat);
                        cout << ">";
                        break;
                    case BOTTOM:
                        gotoxy(pHead->xCoordinat, ++pHead->yCoordinat);
                        cout << "v";
                        break;
                    default:
                        throw std::invalid_argument("Unknown Direction");
                }
                if(checkIsFood(pHead->xCoordinat, pHead->yCoordinat))
                {
                    score++;
                    generateFood();
                    updateScore();
                }
                else
                {
                    pTail = pTail->pNext;
                    pTail->pPrev = NULL;
                    gotoxy(temp->xCoordinat, temp->yCoordinat);
                    cout << " ";
                    delete temp;
                }
                if(checkPaneInLimits() == false)
                {
                    gotoxy(horizontalPixels / 2, verticalPixels / 2);
                    cout << "YOU HAVE FAILED!\n";
                    snakeDestructor();
                }
            }
            else
            {   // Direction Changed.
                directionChanged = false;
                gotoxy(node->xCoordinat, node->yCoordinat);
                cout << "*";
                
                //gotoxy(temp->xCoordinat, temp->yCoordinat);
                //cout << " ";
                //delete temp;
                switch(direction)
                {
                    case LEFT:
                        gotoxy(--pHead->xCoordinat, pHead->yCoordinat);
                        cout << "<";
                        break;
                    case TOP:
                        gotoxy(pHead->xCoordinat, --pHead->yCoordinat);
                        cout << "^";
                        break;
                    case RIGHT:
                        gotoxy(++pHead->xCoordinat, pHead->yCoordinat);
                        cout << ">";
                        break;
                    case BOTTOM:
                        gotoxy(pHead->xCoordinat, ++pHead->yCoordinat);
                        cout << "v";
                        break;
                    default:
                        throw std::invalid_argument("Unknown Direction");
                }
                if(checkIsFood(pHead->xCoordinat, pHead->yCoordinat))
                {
                    score++;
                    generateFood();
                    updateScore();
                }
                else
                {
                    temp = pTail;
                    pTail = pTail->pNext;
                    pTail->pPrev = NULL;
                    gotoxy(temp->xCoordinat, temp->yCoordinat);
                    cout << " ";
                    delete temp;
                }
                if(checkPaneInLimits() == false)
                {
                    gotoxy(horizontalPixels / 2, verticalPixels / 2);
                    cout << "YOU HAVE FAILED!\n";
                    snakeDestructor();
                }
            }
        
        }
        void updateScore()
        {
            gotoxy(0, verticalPixels);
            for(int i = 0; i < 30; i++)
            {
                cout << " ";
            }
            gotoxy(0, verticalPixels);
            cout << "Score : " << score;
        }
        void snakeDestructor()
        {
            snakeBodyLinkedList* temp = pTail;
            while(temp != NULL)
            {
                snakeBodyLinkedList* temp2 = temp->pNext;
                gotoxy(temp->xCoordinat, temp->yCoordinat);
                cout << " ";

                delete temp;
                temp = temp2;
            }
        }
        void inputProcessing()
        {
            char c;
            while(_kbhit())
            {
                c = _getch();
            }
            switch(c) 
            {
                case KEY_UP:
                    if(direction != TOP && direction != BOTTOM)
                    {
                        directionChanged = true;
                        direction = TOP;
                    }
                    break;
                case KEY_DOWN:
                    if(direction != BOTTOM && direction != TOP)
                    {
                        directionChanged = true;
                        direction = BOTTOM;
                    }
                    break;
                case KEY_LEFT:
                    if(direction != LEFT && direction != RIGHT)
                    {
                        directionChanged = true;
                        direction = LEFT;
                    }
                    break;
                case KEY_RIGHT:
                    if(direction != RIGHT && direction != LEFT)
                    {
                        directionChanged = true;
                        direction = RIGHT;
                    }
                    break;
            }
        }
        bool coordinateIsValid(int x, int y)
        {
            for(snakeBodyLinkedList* temp = pTail; temp != NULL; temp = temp->pPrev)
            {
                if(temp->xCoordinat == x && temp->yCoordinat == y)
                {
                    return false;
                }
            }
            return true;
        }
        void generateFood()
        {
            int xCoordinate = (rand() % (horizontalPixels - 2)) + 1;
            int yCoordinate = (rand() % (verticalPixels - 2)) + 1;
            if(coordinateIsValid(xCoordinate, yCoordinate) == true)
            {
                gotoxy(xCoordinate, yCoordinate);
                cout << "F";
            }
            this->FoodXCoordinate = xCoordinate;
            this->FoodYCoourdinate = yCoordinate;
        }
        bool checkIsFood(int x, int y)
        {
            if(x == FoodXCoordinate && y == FoodYCoourdinate)
            {
                return true;
            }
            return false;
        }
        bool checkPaneInLimits()
        {
            if(pHead->xCoordinat < 1 || (pHead->xCoordinat + 1) >= horizontalPixels)
            {
                return false;
            }
            if(pHead->yCoordinat < 1 || (pHead->yCoordinat + 1) >= verticalPixels)
            {
                return false;
            }
            return true;

        }
        void ShowConsoleCursor(bool showFlag)
        {
            HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

            CONSOLE_CURSOR_INFO     cursorInfo;

            GetConsoleCursorInfo(out, &cursorInfo);
            cursorInfo.bVisible = showFlag; // set the cursor visibility
            SetConsoleCursorInfo(out, &cursorInfo);
        }
};
int main(int argcs, char* argv[])
{
    snake mySnake(GREEN);
    mySnake.play();
    system("PAUSE");
    
}