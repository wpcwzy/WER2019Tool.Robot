#define left_crossing 1
#define right_crossing 5
#define middle_crossing 15
#define center_crossing 15
#define left 1
#define middle 0
#define right 2

int debugFlag;
int ai0=0;
int ai1=0;
int ai2=0;
int ai3=0;
int ai4=0;
double readAngel=0;
double debugTemp=0;

void button(void)
{
    printf("Wait for button.");
    WER_next();
}

void route_crossing(int speed,int way,float time)
{
    if(way==middle_crossing)
    {
        printf("Finding center cross.\n\nSpeed:%d Time:%f",speed,time);
    }
    else 
    {    
        if(way==left_crossing)
        {   
            printf("Finding left cross.\n\nSpeed:%d Time:%f",speed,time);
        }
        else
        {
            printf("Finding right cross.\n\nSpeed:%d Time:%f",speed,time);
        }
    }
    WER_LineWay_C(speed,way,time);
}

void route_time(int speed,float time)
{
    printf("Find route acrodding time\n\nSpeed:%d Time:%f",speed,time);
    WER_LineWay_T(speed,time);
}

void route_left(int speed)
{
    printf("Left turn.\n\nSpeed:%d",speed);
    WER_LTurn(speed);
}

void route_right(int speed)
{
    printf("Right turn.\n\nSpeed:%d",speed);
    WER_RTurn(speed);
}

void route_turn(int leftSpeed,int rightSpeed)
{
    printf("Turning.\n\nLeft:%d, Right:%d",leftSpeed,rightSpeed);
    WER_Around(leftSpeed,rightSpeed,0);
}

void route_turn_adv(int leftSpeed,int rightSpeed,int position)
{
    printf("Turning.\n\nLeft:%d, Right:%d",leftSpeed,rightSpeed);
    WER_Around(leftSpeed,rightSpeed,position);
}

void motor(int leftSpeed,int rightSpeed,float time)
{
    printf("Setting Motor.\n\nLeft:%d Right:%d\n\nTime:%f",leftSpeed,rightSpeed,time);
    WER_SetMotor(leftSpeed,rightSpeed,time);
}

void motor_sensor(int port,char* operator,int valve,int leftSpeed,int rightSpeed)
{
    printf("Setting sensor motor.\n\nLeft:%d Right:%d\n\nPort:%d,value:%d",leftSpeed,rightSpeed,port,valve);
    WER_SetMotor_L(port,operator,valve,leftSpeed,rightSpeed);
}

double calcAngel(double angel)
{
    double magicNumber=3.4133;
    double result;
    result=(angel+150)*magicNumber;
    return result;
}

double calcOutput(double angel)
{
    double magicNumber=3.4133;
    double result;
    result=angel/magicNumber-150;
    return result;
}

void servo(int id,int speed,double inputAngel)
{
    double angel;
    angel=calcAngel(inputAngel);
    printf("Servo moved\n\nPos:%g",inputAngel);
    PO16_Move(id,speed,angel);
}

void setSensor()
{
    WER_Set_Floorsensor();
}

void pause()
{
    if(debugFlag)
    {
        ai0=AI(0);
        ai1=AI(1);
        ai2=AI(2);
        ai3=AI(3);
        ai4=AI(4);
        debugTemp=PO16_ReadAngle(1);
        readAngel=calcOutput(debugTemp);
        printf("0:%d 1:%d 2:%d\n\n3:%d 4:%d\n\nservo:%g",ai0,ai1,ai2,ai3,ai4,readAngel);
        WER_next();
    }
    else
    {
        printf("Skip debug.");
    }
}

void init()
{
    //WER_InitRobot_5(motorLeft,powerLeft,motorRight,powerRight,IO0,IO1,IO2,IO3,IO4,1);
    WER_InitRobot_5(0,1,1,1,0,1,2,3,4,1);
    ServoPort_Init(11);
    ServoPort_Init(10);
    printf("Init Finished.");
    button();
}