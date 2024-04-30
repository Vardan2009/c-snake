#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define W 20
#define H 10
#define false 0
#define true 1
#define MAX_SNAKE_LEN 50
#define clrscr() system("cls")

typedef struct Point
{
    int x,y;
} Point;

Point create_point(int x, int y)
{
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

Point snake_vectors[MAX_SNAKE_LEN];
int snake_len;
int score;
Point food;
int running = true;

int is_safe_point_from_snake(int x,int y,int checkfrom)
{
    for(int i = checkfrom;i<snake_len;i++)
    {
        if(snake_vectors[i].x == x && snake_vectors[i].y == y)
            return false;
    }
    return true;
}

void random_food_pos()
{
    int rx = 1;
    int ry = 1;
    do
    {
     rx = 1 + rand() % (W-2);
     ry = 1 + rand() % (H-2);
    }
    while(!is_safe_point_from_snake(rx,ry,0));
    food.x = rx;
    food.y = ry;
}

void init_snake()
{
    srand(time(NULL));
    snake_len = 1;
    score = 1;
    Point start;
    start.x = 2;
    start.y = 2;
    random_food_pos();
    snake_vectors[0] = start;
}

void Draw()
{
    clrscr();
    for(int y = 0;y<H;y++)
    {
        for(int x = 0;x<W;x++)
        {
            if(y == 0 || y == H-1 || x == 0 || x == W-1)
            {
                printf("#");
            }
            else
            {
                int flag = 0;
                if(food.x == x && food.y == y)
                {
                    printf("$");
                    continue;
                }
                for(int sn = 0;sn<snake_len;sn++)
                {
                    Point p = snake_vectors[sn];
                    if(p.x == x && p.y == y)
                    {
                        if(sn == 0){
                            flag = 2;
                        }
                        else
                        {
                            flag = 1;
                        }
                        break;
                    }
                }
                if(flag == 2){
                    printf("&");
                }
                else if (flag == 1){
                    printf("*");
                }
                else{
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d",score);
}

int snake_out_of_bounds(Point p)
{
    return p.x <= 0 || p.x>=W-1 || p.y <= 0 || p.y >= H-1;
}

void add_snake_node()
{
    score++;
    if(snake_len >= MAX_SNAKE_LEN)
    {
        running = false;
        printf("You Win!");
    }
    else
    {
        snake_vectors[snake_len] = snake_vectors[snake_len-1];
        snake_len++;
    }
}

void move_snake(int dX,int dY)
{
    Point new_snake[MAX_SNAKE_LEN];
    Point old_head_pos = snake_vectors[0];
    for(int i =0;i<snake_len;i++)
    {
        new_snake[i+1] = snake_vectors[i];
    }
    Point new_pos = old_head_pos;
    new_pos.x += dX;
    new_pos.y += dY;
    new_snake[0] = new_pos;
    for(int i =0;i<snake_len;i++)
    {
        snake_vectors[i] = new_snake[i];
    }
    if(snake_out_of_bounds(new_pos) || !is_safe_point_from_snake(new_pos.x,new_pos.y,1))
    {
        running = false;
        return;
    }
    if(new_pos.x == food.x && new_pos.y == food.y)
    {
        add_snake_node();
        random_food_pos();
    }
}

int lastx = 1, lasty = 0;

int main()
{
    init_snake();
    Draw();
    while(running)
    {
        if(_kbhit()){
        char inp = getch();
        switch(inp)
        {
            case 'w':
                lastx = 0;
                lasty = -1;
                break;
            case 's':
                lastx = 0;
                lasty = 1;
                break;
            case 'a':
                lastx = -1;
                lasty = 0;
                break;
            case 'd':
                lastx = 1;
                lasty = 0;
                break;
            default:
                running = false;
                break;
        }
     }
     move_snake(lastx,lasty);
     Draw();
     Sleep(100);
    }
}
