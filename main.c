#include "ASEIO.h"
#include "wpc.h"

#define true 1
#define false 0

#define POSX 0
#define POSY 1

#define SPEED 40

int senderX,senderY,targetX,targetY;
int nowX=2;
int nowY=1;
int horizon;
int moveX;

void catch(void)
{
    ;
}

void release(void)
{
    ;
}

void down(int targetY1)
{
    int i;
    SetMotoCL(0,-40);
    for(i=0;i<(5-targetY1);i++)
    {
        while(DI(1)==0)
			printf("%d",DI(1));
        while(DI(1)==1)
			printf("%d",DI(1));
    }
    SetMotoCL(0,0);
    nowY=targetY1;
}

void moveRight(void)
{
    int i;
    SetMotoCL(0,40);
    for(i=0;i<moveX;i++)
    {
        while(DI(0)==0)
			printf("%d",DI(1));
        while(DI(0)==1)
			printf("%d",DI(1));
    }
    SetMotoCL(0,0);
    nowX=nowX+moveX;
}

void moveLeft(void)
{
    int i;
    SetMotoCL(0,-40);
    for(i=0;i<moveX;i++)
    {
        while(DI(0)==0)
			printf("%d",DI(1));
        while(DI(0)==1)
			printf("%d",DI(1));
    }
    SetMotoCL(0,0);
    nowX=nowX-moveX;
}

void up(void)
{
    int i;
    SetMotoCL(0,40);
    for(i=0;i<(5-nowY);i++)
    {
        while(DI(1)==0)
			printf("%d",DI(1));
        while(DI(1)==1)
			printf("%d",DI(1));
    }
    SetMotoCL(0,0);
}

void move(void)
{
    up();
    if(horizon==1)
    {
        moveRight();
    }
    else
    {
        moveLeft();
    }
}

void getToSender(void)
{
    if(senderX>=nowX)
            {
                horizon=1;
                moveX=senderX-nowX;
            }
    else
            {
                horizon=0;
                moveX=nowX-senderX;
                
            }
}

void getToTarget(void)
{
    if(targetX>=nowX)
            {
                horizon=1;
                moveX=targetX-nowX;
            }
    else
            {
                horizon=0;
                moveX=nowX-targetX;
                
            }
}

void operating(int sender,int target)
{
    senderX=(sender%3)+1;
    senderY=(sender/3)+1;
    targetX=(target%3)+1;
    targetY=(target/3)+1;
    getToSender();
    move();
    down(senderY);
    button();
    getToTarget();
    move();
    down(targetY);
	//printf("x:%d",moveX);
    
}

void main()
{
	operating(6,4);
    //nowY=3;
}


//2013DUODUOProgramAA0905