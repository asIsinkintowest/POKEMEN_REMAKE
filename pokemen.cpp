#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<conio.h>
#include <string.h>
#include <windows.h>
#include"pokemenformat.c"
#pragma warning(disable:6387)
#pragma warning(disable:6262)

#define ROW 500        //大地图的行数
#define LINE 500       //大地图的列数
#define row_inner 50   //分区地图的行
#define line_inner 100 //分区地图的列数
#define many 116        //宝可梦的个数
#define screen_height 900 //窗口高度（行大小），单位是像素，为创建的easyx的界面的大小
#define screen_width 1500   //窗口宽度（列大小），单位是像素，为创建的easyx的界面的大小
#define line_num 71 //摄像头的行数
#define col_num 111 //摄像头的列数
int map_flag[4] = { 1, 1, 1, 1 };   //边界判断
int HEIGHT = 12, WIDTH = 12;    //地图字符的大小
int x, y;              //x，y是人物中心点在地图上的坐标
int OCCUR;                        //记录出现在野外的那只宝可梦
int flag = 1;          // flag判断地图是否进行
int pokemen_level[many][2] = { 0 }; //宝可梦的等级和经验
float HARD = 1; //难度系数
int START = 0;
int NUMBER = 0;//宝可梦序号
int take_part[116] = { 1,0,0,1,0,0,1 }; //参战
int chosenPokemen = 0;  //是否选中
float live_number[2];   //对战时的血量

// 是否进行战斗
int iffight = 1;
// 点击次数
int times = 0;
// 鼠标点击技能
int clickPlace;
double myAttackEffect;
double youAttackEffect;
// 血量
int youBlood;
int myBlood;
// 战斗文本
char text[14][100] = {
    "啊！野生的", "跳了出来", "就决定是你了！", "使用了", "野生的", "效果拔群", "击中要害", "效果不佳", "但是什么也没有发生", "顺利地逃走了", "恭喜你抓到了", "很遗憾你没有抓到", "恭喜你获得了胜利！", "再起不能"
};

void mouseMsg1();//开始界面
void mouseMsg2();//难度选择
void mouseMsg3();//图鉴的鼠标消息
void first();//开始界面
void second();//难度选择
void tujian();//图鉴界面
int limit3();//上限三只出战

void makeTree(char map[ROW][LINE * 3], int part[row_inner][line_inner]);
void makeSea(char map[ROW][LINE * 3], int part[row_inner][line_inner]);
void makeHill(char map[ROW][LINE * 3], int part[row_inner][line_inner]);
void makeFire(char map[ROW][LINE * 3], int part[row_inner][line_inner]);
void makeMap(char map[ROW][LINE * 3], int part[row_inner][line_inner]);

void move(char map[ROW][LINE * 3], int part[row_inner][line_inner]);
void movejudge(char map[ROW][LINE * 3]);

void print_map(char photohead[line_num][col_num]);
void mapcopy(char map[ROW][LINE * 3], char photohead[line_num][col_num]);

int pokemenJudge(int part[row_inner][line_inner]);

void pokemenGo();

void youPokemen(float youallBlood, int temp_level);
void myPokemen(float myallBlood, int myAllblood, char myAllBlood[100], int chosenPokemen);
int position(const char* a);
int getMouseMessage();
void drawLeft();																			// 左侧进入战斗起始界面
void drawRight();																			// 右侧进入战斗起始界面
void leftOutput(int a, double b, int c, double d);
void choosePokemen(int chosenPokemen);
int chooseThePokemen(int n, int a, int b, int c);
void choose(int a, int s_one, int s_two, int s_three, int c, float youallBlood, float myallBlood, int myAllblood, char myAllBlood[100], int chosenPokemen, int temp_level);
int firstChoose(int n, int p_one, int p_two, int p_three, int a, int b, int c);
void fight(int part[row_inner][line_inner]);

void pokemenCopy(int part[row_inner][line_inner], int temp_level);
void levelJudge(int i);
void levelPlus(int i);
float typeJudge(int a, int b);

void save(const char* filename);
void load(const char* filename);
void loadTrap(const char* filename);
void saveTrap(const char* filename);
void saveTakePart(const char* filename);
void loadTakePart(const char* filename);

int main()
{
    first();//调用开始界面函数
    closegraph();
    return 0;
}

void first() {
    loadTrap("trap.txt");
    initgraph(1200, 700, EW_SHOWCONSOLE);
    setbkcolor(YELLOW);
    cleardevice();
    settextcolor(BLUE);
    settextstyle(100, 0, "楷体");
    outtextxy(425, 60, "POKEMEN");

    setfillcolor(RED);
    solidrectangle(500, 200, 700, 250);
    settextcolor(YELLOW);
    settextstyle(30, 0, "楷体");
    setbkmode(TRANSPARENT);
    outtextxy(540, 210, "开始游戏");

    solidrectangle(500, 300, 700, 350);
    outtextxy(540, 310, "选择模式");

    solidrectangle(500, 400, 700, 450);
    outtextxy(540, 410, "图    鉴");

    solidrectangle(500, 500, 700, 550);
    outtextxy(540, 510, "退出游戏");
    mouseMsg1();
}
void second() {
    setbkcolor(YELLOW);
    cleardevice();
    settextcolor(BLUE);
    settextstyle(80, 0, "楷体");
    outtextxy(430, 60, "游戏模式");

    setfillcolor(RED);
    solidrectangle(500, 200, 700, 250);
    settextcolor(YELLOW);
    settextstyle(30, 0, "楷体");
    setbkmode(TRANSPARENT);
    outtextxy(555, 210, "简  单");

    solidrectangle(500, 300, 700, 350);
    outtextxy(555, 310, "一  般");

    solidrectangle(500, 400, 700, 450);
    outtextxy(555, 410, "困  难");

    solidrectangle(500, 500, 700, 550);
    outtextxy(555, 510, "返  回");
    mouseMsg2();
}
void tujian() {
    loadTakePart("takePart.txt");
    setbkcolor(YELLOW);
    cleardevice();
    settextcolor(BLACK);
    settextstyle(55, 0, "宋体");
    BeginBatchDraw();
    outtextxy(450, 60, "宝可梦图鉴");

    settextstyle(40, 0, "楷体");
    settextcolor(RED);
    outtextxy(510, 130, POKEMEN[NUMBER].name);
    int i = POKEMEN[NUMBER].number;
    char c[100];
    _itoa_s(i, c, 100, 10);
    outtextxy(450, 130, c);
    if (POKEMEN[NUMBER].trap == 1) {
        setlinecolor(RED);
        rectangle(700, 130, 800, 170);
        settextstyle(30, 0, "宋体");
        outtextxy(705, 135, "已捕获");
    }
    settextstyle(30, 0, "楷体");
    settextcolor(BLUE);
    outtextxy(305, 200, "技能:");
    outtextxy(350, 250, POKEMEN[NUMBER].skill_one);
    outtextxy(350, 350, POKEMEN[NUMBER].skill_two);
    outtextxy(350, 450, POKEMEN[NUMBER].skill_three);
    outtextxy(305, 520, "属性：");
    switch (POKEMEN[NUMBER].type) {
    case 1:outtextxy(400, 520, "草"); break;
    case 2: outtextxy(400, 520, "火"); break;
    case 3: outtextxy(400, 520, "水"); break;
    case 4: outtextxy(400, 520, "电"); break;
    case 5: outtextxy(400, 520, "虫"); break;
    case 6: outtextxy(400, 520, "冰"); break;
    case 7: outtextxy(400, 520, "龙"); break;
    case 8: outtextxy(400, 520, "毒"); break;
    case 9: outtextxy(400, 520, "恶"); break;
    case 10: outtextxy(400, 520, "钢"); break;
    case 11: outtextxy(400, 520, "飞行"); break;
    case 12: outtextxy(400, 520, "岩石"); break;
    case 13: outtextxy(400, 520, "幽灵"); break;
    case 14: outtextxy(400, 520, "格斗"); break;
    case 15: outtextxy(400, 520, "地面"); break;
    case 16: outtextxy(400, 520, "妖精"); break;
    case 17: outtextxy(400, 520, "一般"); break;
    case 18: outtextxy(400, 520, "超能力"); break;
    }
    int up = 180;
    for (int i = 0; i < 100; i++) {
        int left = 500;
        settextstyle(8, 0, "黑体");
        settextcolor(BLACK);
        outtextxy(left, up, POKEMEN[NUMBER].a[i]);
        up += 4;
    }
    FlushBatchDraw();
    setfillcolor(RED);

    settextstyle(30, 0, "楷体");
    settextcolor(YELLOW);
    setbkmode(TRANSPARENT);
    if (NUMBER > 0) {
        solidrectangle(300, 600, 450, 650);
        outtextxy(330, 610, "上一个");
    }
    if (limit3() < 3 && POKEMEN[NUMBER].trap == 1)if (take_part[NUMBER] == 0) {
        solidrectangle(500, 600, 650, 650);
        outtextxy(530, 610, "出  战");
    }
    if (take_part[NUMBER] == 1) {
        solidrectangle(500, 600, 650, 650);
        outtextxy(530, 610, "休  息");
    }

    if (NUMBER < many - 1) {
        solidrectangle(700, 600, 850, 650);
        outtextxy(730, 610, "下一个");
    }

    solidrectangle(900, 600, 1050, 650);
    outtextxy(930, 610, "返  回");
    EndBatchDraw();

    mouseMsg3();

}
void mouseMsg1() {//开始界面鼠标消息

    while (1) {
        MOUSEMSG msg = GetMouseMsg();
        int m = 0;
        if (msg.x > 500 && msg.x < 700 && msg.y>200 && msg.y < 250 && msg.uMsg == WM_LBUTTONDOWN)m = 1;
        if (msg.x > 500 && msg.x < 700 && msg.y>300 && msg.y < 350 && msg.uMsg == WM_LBUTTONDOWN)m = 2;
        if (msg.x > 500 && msg.x < 700 && msg.y>400 && msg.y < 450 && msg.uMsg == WM_LBUTTONDOWN)m = 3;
        if (msg.x > 500 && msg.x < 700 && msg.y>500 && msg.y < 550 && msg.uMsg == WM_LBUTTONDOWN)m = 4;
        switch (m) {
        case 1:pokemenGo(); break;
        case 2:second(); break;
        case 3:tujian(); break;
        case 4:exit(0); break;
        default:break;
        }
    }

}
void mouseMsg2() {//难度选择界面鼠标消息
    while (1) {
        MOUSEMSG msg = GetMouseMsg();
        int n = 0;
        if (msg.x > 500 && msg.x < 700 && msg.y>200 && msg.y < 250 && msg.uMsg == WM_LBUTTONDOWN)n = 1;
        if (msg.x > 500 && msg.x < 700 && msg.y>300 && msg.y < 350 && msg.uMsg == WM_LBUTTONDOWN)n = 2;
        if (msg.x > 500 && msg.x < 700 && msg.y>400 && msg.y < 450 && msg.uMsg == WM_LBUTTONDOWN)n = 3;
        if (msg.x > 500 && msg.x < 700 && msg.y>500 && msg.y < 550 && msg.uMsg == WM_LBUTTONDOWN)n = 4;
        switch (n) {
        case 1:HARD = 0.75; first(); break;
        case 2:HARD = 1; first(); break;
        case 3:HARD = 1.75; first(); break;
        case 4:first(); break;

        }

    }
}
void mouseMsg3() {
    while (1) {
        MOUSEMSG msg = GetMouseMsg();
        int m = 0;
        if (NUMBER > 0)if (msg.x > 300 && msg.x < 450 && msg.y>600 && msg.y < 650 && msg.uMsg == WM_LBUTTONDOWN)m = 1;
        if (NUMBER < many - 1)if (msg.x > 700 && msg.x < 850 && msg.y>600 && msg.y < 650 && msg.uMsg == WM_LBUTTONDOWN)m = 2;
        if (msg.x > 900 && msg.x < 1050 && msg.y>600 && msg.y < 650 && msg.uMsg == WM_LBUTTONDOWN)m = 3;

        if (POKEMEN[NUMBER].trap == 1)
        {
            if (limit3() < 3)if (take_part[NUMBER] == 0)
                if (msg.x > 500 && msg.x < 650 && msg.y>600 && msg.y < 650 && msg.uMsg == WM_LBUTTONDOWN)m = 4;

            if (take_part[NUMBER] == 1)
                if (msg.x > 500 && msg.x < 650 && msg.y>600 && msg.y < 650 && msg.uMsg == WM_LBUTTONDOWN)m = 5;
        }

        switch (m) {
        case 1:NUMBER--; tujian(); break;
        case 2:NUMBER++; tujian(); break;
        case 3:first(); break;
        case 4: take_part[NUMBER] = 1; saveTakePart("takePart.txt"); tujian(); break;
        case 5: take_part[NUMBER] = 0; saveTakePart("takePart.txt"); tujian(); break;
        default:break;
        }
    }
}

int limit3() {
    int num = 0;
    for (int i = 0; i < 116; i++) {
        if (take_part[i] == 1)num++;
    }
    return num;
}

void pokemenGo()
{
    srand((unsigned long)time(0));

   // x = rand() % 1398 + (col_num - 1) / 2; //人物随机出现在地图上的位置a
  //  y = rand() % 418 + (line_num - 1) / 2;

    x = 105;
    y = 44;

    int part[row_inner][line_inner] = { 0 }; //这个是分区地图，用来显示地貌的

    char map[ROW][LINE * 3]; //大地图

    char photohead[line_num][col_num]; //摄像机
    loadTrap("trap.txt");
    initgraph(screen_width, screen_height, EW_SHOWCONSOLE);
    loadTakePart("takePart.txt");
    setbkcolor(WHITE);
    cleardevice();
    makeMap(map, part);      //生成地图   
    mapcopy(map, photohead); //将以人物坐标为中心的一部分大地图复制到摄像机上
    print_map(photohead);    //将摄像机打印到屏幕上
    //fflush(stdout);
    system("pause");
    while (flag == 1)
    {
        move(map, part);               //人物的坐标在大地图上移动
        mapcopy(map, photohead); //将移动后的大地图的一部分复制到摄像机上
        print_map(photohead);    //将摄像机的内容打印到屏幕上，相当于刷新
        //  fflush(stdout);
        saveTrap("trap.txt");
        loadTrap("trap.txt");
    }
    //EndBatchDraw();
    closegraph();
}

/*大地图一共是500x1500，我将大地图分成5000个由10x15的小格子组成的分区地图
分区地图由part数组储存，每一个值都代表一个小格子
为了避免地貌冲突，我规定每个格子中只能出现一种地貌
格子比地貌要大，所以每种地貌在格子中出现的位置也是随机的*/
void makeTree(char map[ROW][LINE * 3], int part[row_inner][line_inner])
{

    int randomrow, randomcol, randomcol_inner, randomrow_inner;
    int rowtemp, coltemp;

    randomrow = rand() % row_inner;  //随机生成在分区地图的第几行
    randomcol = rand() % line_inner; //随机生成在分区地图的第几列 

    while (1) //这个循环的作用是避免一个格子被重复使用
    {
        if (part[randomrow][randomcol] == 0) //如果分区数组的该行该列为0，说明没有地貌
        {
            part[randomrow][randomcol] = 1; //将该行该列变成1，标志这个格子已经有地貌了
            break;
        }
        else //这个格子已经有地貌了
        {
            randomrow = rand() % row_inner; //重新随机格子
            randomcol = rand() % line_inner;
        }
    }

    /*接下来的内容是为了让地貌随机出现在格子中
    我给格子规定了三个单位的左右边界，一个单位的上下边界
    也就是说，每种地貌能够出现的大小是8x9的矩形
    在makeTree的例子中，树木是4x5的矩形
    */

    randomrow_inner = rand() % 4;
    randomcol_inner = rand() % 5;

    rowtemp = (randomrow + 1) * 10 - 9 + randomrow_inner;  //首先让地貌的上边界出现在格子的最下边，然后向上移九格，再向下移动随机数个格
    coltemp = (randomcol + 1) * 15 - 12 + randomcol_inner; //再让地貌的左边界出现在格子的最右边，然后向左移动12格，再向右移动随机数个格

    map[rowtemp][coltemp] = ' '; //画一颗大树
    map[rowtemp][coltemp + 1] = ' ';
    map[rowtemp][coltemp + 2] = '&';
    map[rowtemp][coltemp + 3] = ' ';
    map[rowtemp][coltemp + 4] = ' ';
    map[rowtemp + 1][coltemp] = ' ';
    map[rowtemp + 1][coltemp + 1] = '&';
    map[rowtemp + 1][coltemp + 2] = '&';
    map[rowtemp + 1][coltemp + 3] = '&';
    map[rowtemp + 1][coltemp + 4] = ' ';
    map[rowtemp + 2][coltemp] = '&';
    map[rowtemp + 2][coltemp + 1] = '&';
    map[rowtemp + 2][coltemp + 2] = '&';
    map[rowtemp + 2][coltemp + 3] = '&';
    map[rowtemp + 2][coltemp + 4] = '&';
    map[rowtemp + 3][coltemp] = ' ';
    map[rowtemp + 3][coltemp + 1] = '[';
    map[rowtemp + 3][coltemp + 2] = '|';
    map[rowtemp + 3][coltemp + 3] = ']';
    map[rowtemp + 3][coltemp + 4] = ' ';
    map[rowtemp + 4][coltemp] = ' ';
    map[rowtemp + 4][coltemp + 1] = '|';
    map[rowtemp + 4][coltemp + 2] = '_';
    map[rowtemp + 4][coltemp + 3] = '|';
    map[rowtemp + 4][coltemp + 4] = ' ';
}

void makeSea(char map[ROW][LINE * 3], int part[row_inner][line_inner])
{

    int randomrow, randomcol, randomcol_inner, randomrow_inner;
    int rowtemp, coltemp;

    randomrow = rand() % row_inner;
    randomcol = rand() % line_inner;

    while (1)
    {
        if (part[randomrow][randomcol] == 0)
        {
            part[randomrow][randomcol] = 2;
            break;
        }
        else
        {
            randomrow = rand() % row_inner;
            randomcol = rand() % line_inner;
        }
    }

    randomrow_inner = rand() % 4;
    randomcol_inner = rand() % 5;

    rowtemp = (randomrow + 1) * 10 - 9 + randomrow_inner;
    coltemp = (randomcol + 1) * 15 - 12 + randomcol_inner;

    map[rowtemp][coltemp] = ' ';
    map[rowtemp][coltemp + 1] = '_';
    map[rowtemp][coltemp + 2] = '_';
    map[rowtemp][coltemp + 3] = '_';
    map[rowtemp][coltemp + 4] = ' ';
    map[rowtemp + 1][coltemp] = '/';
    map[rowtemp + 1][coltemp + 1] = '~';
    map[rowtemp + 1][coltemp + 2] = ' ';
    map[rowtemp + 1][coltemp + 3] = '~';
    map[rowtemp + 1][coltemp + 4] = '\\';
    map[rowtemp + 2][coltemp] = '|';
    map[rowtemp + 2][coltemp + 1] = ' ';
    map[rowtemp + 2][coltemp + 2] = '~';
    map[rowtemp + 2][coltemp + 3] = ' ';
    map[rowtemp + 2][coltemp + 4] = '|';
    map[rowtemp + 3][coltemp] = '|';
    map[rowtemp + 3][coltemp + 1] = '~';
    map[rowtemp + 3][coltemp + 2] = '~';
    map[rowtemp + 3][coltemp + 3] = '~';
    map[rowtemp + 3][coltemp + 4] = '|';
    map[rowtemp + 4][coltemp] = '\\';
    map[rowtemp + 4][coltemp + 1] = '_';
    map[rowtemp + 4][coltemp + 2] = '_';
    map[rowtemp + 4][coltemp + 3] = '_';
    map[rowtemp + 4][coltemp + 4] = '/';
}

void makeHill(char map[ROW][LINE * 3], int part[row_inner][line_inner])
{

    int randomrow, randomcol, randomcol_inner, randomrow_inner;
    int rowtemp, coltemp;

    randomrow = rand() % row_inner;
    randomcol = rand() % line_inner;

    while (1)
    {
        if (part[randomrow][randomcol] == 0)
        {
            part[randomrow][randomcol] = 3;
            break;
        }
        else
        {
            randomrow = rand() % row_inner;
            randomcol = rand() % line_inner;
        }
    }

    randomrow_inner = rand() % 4;
    randomcol_inner = rand() % 5;

    rowtemp = (randomrow + 1) * 10 - 9 + randomrow_inner;
    coltemp = (randomcol + 1) * 15 - 12 + randomcol_inner;

    map[rowtemp][coltemp] = ' ';
    map[rowtemp][coltemp + 1] = '#';
    map[rowtemp][coltemp + 2] = '#';
    map[rowtemp][coltemp + 3] = '#';
    map[rowtemp][coltemp + 4] = ' ';
    map[rowtemp + 1][coltemp] = '#';
    map[rowtemp + 1][coltemp + 1] = ' ';
    map[rowtemp + 1][coltemp + 2] = ' ';
    map[rowtemp + 1][coltemp + 3] = ' ';
    map[rowtemp + 1][coltemp + 4] = '#';
    map[rowtemp + 2][coltemp] = '#';
    map[rowtemp + 2][coltemp + 1] = ' ';
    map[rowtemp + 2][coltemp + 2] = '@';
    map[rowtemp + 2][coltemp + 3] = ' ';
    map[rowtemp + 2][coltemp + 4] = '#';
    map[rowtemp + 3][coltemp] = '#';
    map[rowtemp + 3][coltemp + 1] = ' ';
    map[rowtemp + 3][coltemp + 2] = ' ';
    map[rowtemp + 3][coltemp + 3] = ' ';
    map[rowtemp + 3][coltemp + 4] = '#';
    map[rowtemp + 4][coltemp] = ' ';
    map[rowtemp + 4][coltemp + 1] = '#';
    map[rowtemp + 4][coltemp + 2] = '#';
    map[rowtemp + 4][coltemp + 3] = '#';
    map[rowtemp + 4][coltemp + 4] = ' ';
}

void makeFire(char map[ROW][LINE * 3], int part[row_inner][line_inner])
{

    int randomrow, randomcol, randomcol_inner, randomrow_inner;
    int rowtemp, coltemp;

    randomrow = rand() % row_inner;
    randomcol = rand() % line_inner;

    while (1)
    {
        if (part[randomrow][randomcol] == 0)
        {
            part[randomrow][randomcol] = 4;
            break;
        }
        else
        {
            randomrow = rand() % row_inner;
            randomcol = rand() % line_inner;
        }
    }

    randomrow_inner = rand() % 4;
    randomcol_inner = rand() % 5;

    rowtemp = (randomrow + 1) * 10 - 9 + randomrow_inner;
    coltemp = (randomcol + 1) * 15 - 12 + randomcol_inner;

    map[rowtemp][coltemp] = ' ';
    map[rowtemp][coltemp + 1] = ' ';
    map[rowtemp][coltemp + 2] = 'A';
    map[rowtemp][coltemp + 3] = ' ';
    map[rowtemp][coltemp + 4] = ' ';
    map[rowtemp + 1][coltemp] = ' ';
    map[rowtemp + 1][coltemp + 1] = 'A';
    map[rowtemp + 1][coltemp + 2] = 'X';
    map[rowtemp + 1][coltemp + 3] = 'A';
    map[rowtemp + 1][coltemp + 4] = ' ';
    map[rowtemp + 2][coltemp] = 'A';
    map[rowtemp + 2][coltemp + 1] = 'X';
    map[rowtemp + 2][coltemp + 2] = 'A';
    map[rowtemp + 2][coltemp + 3] = 'X';
    map[rowtemp + 2][coltemp + 4] = 'A';
    map[rowtemp + 3][coltemp] = '\\';
    map[rowtemp + 3][coltemp + 1] = 'X';
    map[rowtemp + 3][coltemp + 2] = 'X';
    map[rowtemp + 3][coltemp + 3] = 'X';
    map[rowtemp + 3][coltemp + 4] = '/';
    map[rowtemp + 4][coltemp] = ' ';
    map[rowtemp + 4][coltemp + 1] = '\\';
    map[rowtemp + 4][coltemp + 2] = '_';
    map[rowtemp + 4][coltemp + 3] = '/';
    map[rowtemp + 4][coltemp + 4] = ' ';
}
void makeMap(char map[ROW][LINE * 3], int part[row_inner][line_inner])
{
    //struct timeval tv;
    //mingw_gettimeofday(&tv, NULL);


    srand((unsigned int)time(0));

    for (int i = 0; i < ROW; i++) //首先生成一个全是草的地图
    {
        if (i == 0)
        {
            for (int j = 0; j < LINE * 3; j++)
            {
                map[i][j] = '+';
            }
        }
        else if (i == ROW - 1)
        {
            for (int j = 0; j < LINE * 3; j++)
            {
                map[i][j] = '+';
            }
        }
        else if (i % 2 == 0) //单数行显示M  ，双数行显示 M ，形成错落有致的效果
        {
            for (int j = 0; j < LINE; j++)
            {
                if (j == 0)
                {
                    map[i][j * 3] = '+';
                    map[i][j * 3 + 1] = '+';
                    map[i][j * 3 + 2] = ' ';
                }
                else if (j == LINE - 1)
                {
                    map[i][j * 3] = ' ';
                    map[i][j * 3 + 1] = '+';
                    map[i][j * 3 + 2] = '+';
                }
                else
                {
                    map[i][j * 3] = ' ';
                    map[i][j * 3 + 1] = 'M';
                    map[i][j * 3 + 2] = ' ';
                }
            }
        }
        else
        {
            for (int j = 0; j < LINE; j++)
            {
                if (j == 0)
                {
                    map[i][j * 3] = '+';
                    map[i][j * 3 + 1] = '+';
                    map[i][j * 3 + 2] = ' ';
                }
                else if (j == LINE - 1)
                {
                    map[i][j * 3] = 'M';
                    map[i][j * 3 + 1] = '+';
                    map[i][j * 3 + 2] = '+';
                }
                else
                {
                    map[i][j * 3] = 'M';
                    map[i][j * 3 + 1] = ' ';
                    map[i][j * 3 + 2] = ' ';
                }
            }
        }
    }

    for (int i = 0; i < 180; i++) //在地图上添加地貌，循环次数就是每种地貌在地图上的个数
    {
        makeTree(map, part);
        makeSea(map, part);
        makeHill(map, part);
        makeFire(map, part);
    }
}

void move(char map[ROW][LINE * 3], int part[row_inner][line_inner])
{
    char derection;

    derection = _getch(); //接收移动的指令,目前第一次还需要按enter，且没隔一次会失效一下。
    switch (derection)
    {
    case 'a':
    {
        x = x - 2;
        movejudge(map);
        break;
    }
    case 'w':
    {
        y = y - 1;
        movejudge(map);
        break; //上
    }
    case 'd':
    {
        x = x + 2;
        movejudge(map);
        break;
    } //右走
    case 's':
    {
        y = y + 1;
        movejudge(map);
        break;
    } //下
    case 'q':
        first();
        break; //退出
    case ' ':
    {
        times = 0;
        fight(part);
        initgraph(screen_width, screen_height, EW_SHOWCONSOLE);
        setbkcolor(WHITE);
        cleardevice();
        break;
    }
    default:
        derection = _getch();
    }
}

void movejudge(char map[ROW][LINE * 3])
{
    if (x < (col_num - 1) / 2)
    {
        map_flag[0] = 0;
    }
    else
    {
        map_flag[0] = 1;
    }
    if (x > LINE * 3 - (col_num - 1) / 2)
    {
        map_flag[1] = 0;
    }
    else
    {
        map_flag[1] = 1;
    }
    if (y < (line_num - 1) / 2)
    {
        map_flag[2] = 0;
    }
    else
    {
        map_flag[2] = 1;
    }
    if (y > ROW - (line_num - 1) / 2)
    {
        map_flag[3] = 0;
    }
    else
    {
        map_flag[3] = 1;
    }
    if (x < 2)
    {
        map_flag[0] = 2;
    }
    if (x > LINE * 3 - 3)
    {
        map_flag[1] = 2;
    }
    if (y < 2)
    {
        map_flag[2] = 2;
    }
    if (y > ROW - 3)
    {
        map_flag[3] = 2;
    }
}

void mapcopy(char map[ROW][LINE * 3], char photohead[line_num][col_num])
{
    if (map_flag[0] == 1 && map_flag[1] == 1 && map_flag[2] == 1 && map_flag[3] == 1)
    {
        for (int i = 0; i < line_num; i++)
        {
            for (int j = 0; j < col_num; j++)
            {
                photohead[i][j] = map[y - (line_num - 1) / 2 + i][x - (col_num - 1) / 2 + j]; //以x，y为中心，将一个31x101的大地图的一部分复制到摄像机里               
            }
        }
        photohead[(line_num - 1) / 2 - 2][(col_num - 1) / 2 - 2] = ' ';//改动
        photohead[(line_num - 1) / 2 - 2][(col_num - 1) / 2 - 1] = ' ';
        photohead[(line_num - 1) / 2 - 2][(col_num - 1) / 2] = '?';
        photohead[(line_num - 1) / 2 - 2][(col_num - 1) / 2 + 1] = ' ';
        photohead[(line_num - 1) / 2 - 2][(col_num - 1) / 2 + 2] = ' ';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2 - 2] = '*';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2 - 1] = '*';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2] = '*';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2 + 1] = '*';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2 + 2] = '*';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 - 2] = ' ';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 - 1] = ' ';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2] = '*';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 + 1] = ' ';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 + 2] = ' ';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 - 2] = ' ';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2 - 1] = '|';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2] = ' ';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2 + 1] = '|';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2 + 2] = ' ';
        photohead[(line_num - 1) / 2 + 2][(col_num - 1) / 2 - 2] = ' ';
        photohead[(line_num - 1) / 2 + 2][(col_num - 1) / 2 - 1] = '|';
        photohead[(line_num - 1) / 2 + 2][(col_num - 1) / 2] = ' ';
        photohead[(line_num - 1) / 2 + 2][(col_num - 1) / 2 + 1] = '|';
        photohead[(line_num - 1) / 2 + 2][(col_num - 1) / 2 + 2] = ' ';
    }

    else
    {
        if (map_flag[0] == 0 && map_flag[2] == 1 && map_flag[3] == 1 && map_flag[1] == 1)
        {
            for (int i = 0; i < line_num; i++)
            {
                for (int j = 0; j < col_num; j++)
                {
                    photohead[i][j] = map[y - (line_num - 1) / 2 + i][j];
                }
            }
            photohead[(line_num - 1) / 2 - 2][x - 2] = ' ';//只改13
            photohead[(line_num - 1) / 2 - 2][x - 1] = ' ';
            photohead[(line_num - 1) / 2 - 2][x] = '?';
            photohead[(line_num - 1) / 2 - 2][x + 1] = ' ';
            photohead[(line_num - 1) / 2 - 2][x + 2] = ' ';
            photohead[(line_num - 1) / 2 - 1][x - 2] = '*';
            photohead[(line_num - 1) / 2 - 1][x - 1] = '*';
            photohead[(line_num - 1) / 2 - 1][x] = '*';
            photohead[(line_num - 1) / 2 - 1][x + 1] = '*';
            photohead[(line_num - 1) / 2 - 1][x + 2] = '*';
            photohead[(line_num - 1) / 2][x - 2] = ' ';
            photohead[(line_num - 1) / 2][x - 1] = ' ';
            photohead[(line_num - 1) / 2][x] = '*';
            photohead[(line_num - 1) / 2][x + 1] = ' ';
            photohead[(line_num - 1) / 2][x + 2] = ' ';
            photohead[(line_num - 1) / 2 + 1][x - 2] = ' ';
            photohead[(line_num - 1) / 2 + 1][x - 1] = '|';
            photohead[(line_num - 1) / 2 + 1][x] = ' ';
            photohead[(line_num - 1) / 2 + 1][x + 1] = '|';
            photohead[(line_num - 1) / 2 + 1][x + 2] = ' ';
            photohead[(line_num - 1) / 2 + 2][x - 2] = ' ';
            photohead[(line_num - 1) / 2 + 2][x - 1] = '|';
            photohead[(line_num - 1) / 2 + 2][x] = ' ';
            photohead[(line_num - 1) / 2 + 2][x + 1] = '|';
            photohead[(line_num - 1) / 2 + 2][x + 2] = ' ';
        }
        if (map_flag[1] == 0 && map_flag[2] == 1 && map_flag[3] == 1 && map_flag[0] == 1)
        {
            for (int i = 0; i < line_num; i++)
            {
                for (int j = 0; j < col_num; j++)
                {
                    photohead[i][(col_num - 1) - j] = map[y - (line_num - 1) / 2 + i][1499 - j];
                }
            }
            photohead[(line_num - 1) / 2 - 2][col_num - 1502 + x] = ' ';
            photohead[(line_num - 1) / 2 - 2][col_num - 1501 + x] = ' ';
            photohead[(line_num - 1) / 2 - 2][col_num - 1500 + x] = '?';
            photohead[(line_num - 1) / 2 - 2][col_num - 1499 + x] = ' ';
            photohead[(line_num - 1) / 2 - 2][col_num - 1498 + x] = ' ';
            photohead[(line_num - 1) / 2 - 1][col_num - 1502 + x] = '*';
            photohead[(line_num - 1) / 2 - 1][col_num - 1501 + x] = '*';
            photohead[(line_num - 1) / 2 - 1][col_num - 1500 + x] = '*';//中心点 101-（1500-x）
            photohead[(line_num - 1) / 2 - 1][col_num - 1499 + x] = '*';
            photohead[(line_num - 1) / 2 - 1][col_num - 1498 + x] = '*';
            photohead[(line_num - 1) / 2][col_num - 1502 + x] = ' ';
            photohead[(line_num - 1) / 2][col_num - 1501 + x] = ' ';
            photohead[(line_num - 1) / 2][col_num - 1500 + x] = '*';
            photohead[(line_num - 1) / 2][col_num - 1499 + x] = ' ';
            photohead[(line_num - 1) / 2][col_num - 1498 + x] = ' ';
            photohead[(line_num - 1) / 2 + 1][col_num - 1502 + x] = ' ';
            photohead[(line_num - 1) / 2 + 1][col_num - 1501 + x] = '|';
            photohead[(line_num - 1) / 2 + 1][col_num - 1500 + x] = ' ';
            photohead[(line_num - 1) / 2 + 1][col_num - 1499 + x] = '|';
            photohead[(line_num - 1) / 2 + 1][col_num - 1498 + x] = ' ';
            photohead[(line_num - 1) / 2 + 2][col_num - 1502 + x] = ' ';
            photohead[(line_num - 1) / 2 + 2][col_num - 1501 + x] = '|';
            photohead[(line_num - 1) / 2 + 2][col_num - 1500 + x] = ' ';
            photohead[(line_num - 1) / 2 + 2][col_num - 1499 + x] = '|';
            photohead[(line_num - 1) / 2 + 2][col_num - 1498 + x] = ' ';
        }
        if (map_flag[2] == 0 && map_flag[0] == 1 && map_flag[1] == 1 && map_flag[3] == 1)
        {
            for (int i = 0; i < line_num; i++)
            {
                for (int j = 0; j < col_num; j++)
                {
                    photohead[i][j] = map[i][x - (col_num - 1) / 2 + j];
                }
            }
            photohead[y - 2][(col_num - 1) / 2 - 2] = ' ';//只改右
            photohead[y - 2][(col_num - 1) / 2 - 1] = ' ';
            photohead[y - 2][(col_num - 1) / 2] = '?';
            photohead[y - 2][(col_num - 1) / 2 + 1] = ' ';
            photohead[y - 2][(col_num - 1) / 2 + 2] = ' ';
            photohead[y - 1][(col_num - 1) / 2 - 2] = '*';
            photohead[y - 1][(col_num - 1) / 2 - 1] = '*';
            photohead[y - 1][(col_num - 1) / 2] = '*';
            photohead[y - 1][(col_num - 1) / 2 + 1] = '*';
            photohead[y - 1][(col_num - 1) / 2 + 2] = '*';
            photohead[y][(col_num - 1) / 2 - 2] = ' ';
            photohead[y][(col_num - 1) / 2 - 1] = ' ';
            photohead[y][(col_num - 1) / 2] = '*';
            photohead[y][(col_num - 1) / 2 + 1] = ' ';
            photohead[y][(col_num - 1) / 2 + 2] = ' ';
            photohead[y + 1][(col_num - 1) / 2 - 2] = ' ';
            photohead[y + 1][(col_num - 1) / 2 - 1] = '|';
            photohead[y + 1][(col_num - 1) / 2] = ' ';
            photohead[y + 1][(col_num - 1) / 2 + 1] = '|';
            photohead[y + 1][(col_num - 1) / 2 + 2] = ' ';
            photohead[y + 2][(col_num - 1) / 2 - 2] = ' ';
            photohead[y + 2][(col_num - 1) / 2 - 1] = '|';
            photohead[y + 2][(col_num - 1) / 2] = ' ';
            photohead[y + 2][(col_num - 1) / 2 + 1] = '|';
            photohead[y + 2][(col_num - 1) / 2 + 2] = ' ';
        }
        if (map_flag[3] == 0 && map_flag[0] == 1 && map_flag[1] == 1 && map_flag[2] == 1)
        {
            for (int i = 0; i < line_num; i++)
            {
                for (int j = 0; j < col_num; j++)
                {
                    photohead[(line_num - 1) - i][j] = map[499 - i][x - (line_num - 1) + j];
                }
            }
            photohead[line_num - 502 + y][(col_num - 1) / 2 - 28] = ' ';
            photohead[line_num - 502 + y][(col_num - 1) / 2 - 1] = ' ';
            photohead[line_num - 502 + y][(col_num - 1) / 2] = '?';
            photohead[line_num - 502 + y][(col_num - 1) / 2 + 1] = ' ';
            photohead[line_num - 502 + y][(col_num - 1) / 2 + 2] = ' ';
            photohead[line_num - 501 + y][(col_num - 1) / 2 - 2] = '*';
            photohead[line_num - 501 + y][(col_num - 1) / 2 - 1] = '*';
            photohead[line_num - 501 + y][(col_num - 1) / 2] = '*';
            photohead[line_num - 501 + y][(col_num - 1) / 2 + 1] = '*';
            photohead[line_num - 501 + y][(col_num - 1) / 2 + 2] = '*';
            photohead[line_num - 500 + y][(col_num - 1) / 2 - 2] = ' ';
            photohead[line_num - 500 + y][(col_num - 1) / 2 - 1] = ' ';
            photohead[line_num - 500 + y][(col_num - 1) / 2] = '*';//31-（500-y）
            photohead[line_num - 500 + y][(col_num - 1) / 2 + 1] = ' ';
            photohead[line_num - 500 + y][(col_num - 1) / 2 + 2] = ' ';
            photohead[line_num - 499 + y][(col_num - 1) / 2 - 2] = ' ';
            photohead[line_num - 499 + y][(col_num - 1) / 2 - 1] = '|';
            photohead[line_num - 499 + y][(col_num - 1) / 2] = ' ';
            photohead[line_num - 499 + y][(col_num - 1) / 2 + 1] = '|';
            photohead[line_num - 499 + y][(col_num - 1) / 2 + 2] = ' ';
            photohead[line_num - 498 + y][(col_num - 1) / 2 - 2] = ' ';
            photohead[line_num - 498 + y][(col_num - 1) / 2 - 1] = '|';
            photohead[line_num - 498 + y][(col_num - 1) / 2] = ' ';
            photohead[line_num - 498 + y][(col_num - 1) / 2 + 1] = '|';
            photohead[line_num - 498 + y][(col_num - 1) / 2 + 2] = ' ';
        }
        if (map_flag[0] == 0 && map_flag[2] == 0)
        {
            for (int i = 0; i < line_num; i++)
            {
                for (int j = 0; j < col_num; j++)
                {
                    photohead[i][j] = map[i][j];
                }
            }
            photohead[y - 2][x - 2] = ' ';
            photohead[y - 2][x - 1] = ' ';
            photohead[y - 2][x] = '?';

            photohead[y - 2][x + 1] = ' ';
            photohead[y - 2][x + 2] = ' ';
            photohead[y - 1][x - 2] = '*';
            photohead[y - 1][x - 1] = '*';
            photohead[y - 1][x] = '*';
            photohead[y - 1][x + 1] = '*';
            photohead[y - 1][x + 2] = '*';
            photohead[y][x - 2] = ' ';
            photohead[y][x - 1] = ' ';
            photohead[y][x] = '*';
            photohead[y][x + 1] = ' ';
            photohead[y][x + 2] = ' ';
            photohead[y + 1][x - 2] = ' ';
            photohead[y + 1][x - 1] = '|';
            photohead[y + 1][x] = ' ';
            photohead[y + 1][x + 1] = '|';
            photohead[y + 1][x + 2] = ' ';
            photohead[y + 2][x - 2] = ' ';
            photohead[y + 2][x - 1] = '|';
            photohead[y + 2][x] = ' ';
            photohead[y + 2][x + 1] = '|';
            photohead[y + 2][x + 2] = ' ';
        }
        if (map_flag[0] == 0 && map_flag[3] == 0)
        {
            for (int i = 0; i < line_num; i++)
            {
                for (int j = 0; j < col_num; j++)
                {
                    photohead[(line_num - 1) - i][j] = map[499 - i][j];
                }
            }
            photohead[line_num - 502 + y][x - 2] = ' ';
            photohead[line_num - 502 + y][x - 1] = ' ';
            photohead[line_num - 502 + y][x] = '?';
            photohead[line_num - 502 + y][x + 1] = ' ';
            photohead[line_num - 502 + y][x + 2] = ' ';
            photohead[line_num - 501 + y][x - 2] = '*';
            photohead[line_num - 501 + y][x - 1] = '*';
            photohead[line_num - 501 + y][x] = '*';
            photohead[line_num - 501 + y][x + 1] = '*';
            photohead[line_num - 501 + y][x + 2] = '*';
            photohead[line_num - 500 + y][x - 2] = ' ';
            photohead[line_num - 500 + y][x - 1] = ' ';
            photohead[line_num - 500 + y][x] = '*';//左
            photohead[line_num - 500 + y][x + 1] = ' ';
            photohead[line_num - 500 + y][x + 2] = ' ';
            photohead[line_num - 499 + y][x - 2] = ' ';
            photohead[line_num - 499 + y][x - 1] = '|';
            photohead[line_num - 499 + y][x] = ' ';
            photohead[line_num - 499 + y][x + 1] = '|';
            photohead[line_num - 499 + y][x + 2] = ' ';
            photohead[line_num - 498 + y][x - 2] = ' ';
            photohead[line_num - 498 + y][x - 1] = '|';
            photohead[line_num - 498 + y][x] = ' ';
            photohead[line_num - 498 + y][x + 1] = '|';
            photohead[line_num - 498 + y][x + 2] = ' ';
        }
        if (map_flag[1] == 0 && map_flag[2] == 0)
        {
            for (int i = 0; i < line_num; i++)
            {
                for (int j = 0; j < col_num; j++)
                {
                    photohead[i][(col_num - 1) - j] = map[i][1499 - j];
                }
            }
            photohead[y - 2][col_num - 1501 + x] = ' ';
            photohead[y - 2][col_num - 1501 + x] = ' ';
            photohead[y - 2][col_num - 1500 + x] = '?';
            photohead[y - 2][col_num - 1499 + x] = ' ';
            photohead[y - 2][col_num - 1498 + x] = ' ';
            photohead[y - 1][col_num - 1501 + x] = '*';
            photohead[y - 1][col_num - 1500 + x] = '*';
            photohead[y - 1][col_num - 1499 + x] = '*';
            photohead[y - 1][col_num - 1498 + x] = '*';
            photohead[y][col_num - 1501 + x] = ' ';
            photohead[y][col_num - 1501 + x] = ' ';
            photohead[y][col_num - 1500 + x] = '*';//右
            photohead[y][col_num - 1499 + x] = ' ';
            photohead[y][col_num - 1498 + x] = ' ';
            photohead[y + 1][col_num - 1501 + x] = ' ';
            photohead[y + 1][col_num - 1501 + x] = '|';
            photohead[y + 1][col_num - 1500 + x] = ' ';
            photohead[y + 1][col_num - 1499 + x] = '|';
            photohead[y + 1][col_num - 1498 + x] = ' ';
            photohead[y + 2][col_num - 1501 + x] = ' ';
            photohead[y + 2][col_num - 1501 + x] = '|';
            photohead[y + 2][col_num - 1500 + x] = ' ';
            photohead[y + 2][col_num - 1499 + x] = '|';
            photohead[y + 2][col_num - 1498 + x] = ' ';
        }
        if (map_flag[1] == 0 && map_flag[3] == 0)
        {
            for (int i = 0; i < line_num; i++)
            {
                for (int j = 0; j < col_num; j++)
                {
                    photohead[line_num - i][col_num - 1 - j] = map[499 - i][1499 - j];
                }
            }
            photohead[line_num - 502 + y][col_num - 1502 + x] = ' ';
            photohead[line_num - 502 + y][col_num - 1501 + x] = ' ';
            photohead[line_num - 502 + y][col_num - 1500 + x] = '?';
            photohead[line_num - 502 + y][col_num - 1499 + x] = ' ';
            photohead[line_num - 502 + y][col_num - 1498 + x] = ' ';
            photohead[line_num - 501 + y][col_num - 1502 + x] = '*';
            photohead[line_num - 501 + y][col_num - 1501 + x] = '*';
            photohead[line_num - 501 + y][col_num - 1500 + x] = '*';
            photohead[line_num - 501 + y][col_num - 1499 + x] = '*';
            photohead[line_num - 501 + y][col_num - 1498 + x] = '*';
            photohead[line_num - 500 + y][col_num - 1502 + x] = ' ';
            photohead[line_num - 500 + y][col_num - 1501 + x] = ' ';
            photohead[line_num - 500 + y][col_num - 1500 + x] = '*';
            photohead[line_num - 500 + y][col_num - 1499 + x] = ' ';
            photohead[line_num - 500 + y][col_num - 1498 + x] = ' ';
            photohead[line_num - 499 + y][col_num - 1502 + x] = ' ';
            photohead[line_num - 499 + y][col_num - 1501 + x] = '|';
            photohead[line_num - 499 + y][col_num - 1500 + x] = ' ';
            photohead[line_num - 499 + y][col_num - 1499 + x] = '|';
            photohead[line_num - 499 + y][col_num - 1498 + x] = ' ';
            photohead[line_num - 498 + y][col_num - 1502 + x] = ' ';
            photohead[line_num - 498 + y][col_num - 1501 + x] = '|';
            photohead[line_num - 498 + y][col_num - 1500 + x] = ' ';
            photohead[line_num - 498 + y][col_num - 1499 + x] = '|';
            photohead[line_num - 498 + y][col_num - 1498 + x] = ' ';
        }
    }
}

int pokemenJudge(int part[row_inner][line_inner])
{
    int i, m, n;
    m = y / 10;
    n = x / 15;
    i = rand() % many;
    switch (part[m][n])
    {
    case 4:
    {
        while (POKEMEN[i].type != 2 && POKEMEN[i].type != 12 && POKEMEN[i].type != 14 && POKEMEN[i].type != 15 && POKEMEN[i].type != 17 && POKEMEN[i].type != 9 && POKEMEN[i].type != 11)
        {
            i = rand() % many;
        }
        break;
    }
    case 1:
    {
        while (POKEMEN[i].type != 1 && POKEMEN[i].type != 5 && POKEMEN[i].type != 11 && POKEMEN[i].type != 12 && POKEMEN[i].type != 15 && POKEMEN[i].type != 17 && POKEMEN[i].type != 14 && POKEMEN[i].type != 8)
        {
            i = rand() % many;
        }
        break;
    }
    case 2:
    {
        while (POKEMEN[i].type != 3 && POKEMEN[i].type != 6 && POKEMEN[i].type != 13 && POKEMEN[i].type != 5 && POKEMEN[i].type != 8 && POKEMEN[i].type != 17 && POKEMEN[i].type != 9)
        {
            i = rand() % many;
        }
        break;

    }
    case 3:
    {
        while (POKEMEN[i].type != 7 && POKEMEN[i].type != 10 && POKEMEN[i].type != 13 && POKEMEN[i].type != 16 && POKEMEN[i].type != 17 && POKEMEN[i].type != 18)
        {
            i = rand() % many;
        }
        break;
    }
    }
    return i;
}

void print_map(char photohead[line_num][col_num])
{


    if (map_flag[0] == 2 || map_flag[1] == 2 || map_flag[2] == 2 || map_flag[3] == 2)
    {
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 - 4] = ' ';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 - 3] = 'Y';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 - 2] = 'O';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 - 1] = 'U';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2] = ' ';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 + 1] = 'O';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 + 2] = 'U';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 + 3] = 'T';
        photohead[(line_num - 1) / 2][(col_num - 1) / 2 + 4] = ' ';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2 - 4] = ' ';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2 - 3] = ' ';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2 - 2] = ' ';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2 - 1] = ' ';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2] = ' ';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2 + 1] = ' ';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2 + 2] = ' ';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2 + 3] = ' ';
        photohead[(line_num - 1) / 2 + 1][(col_num - 1) / 2 + 4] = ' ';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2 - 4] = ' ';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2 - 3] = ' ';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2 - 2] = ' ';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2 - 1] = ' ';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2] = ' ';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2 + 1] = ' ';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2 + 2] = ' ';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2 + 3] = ' ';
        photohead[(line_num - 1) / 2 - 1][(col_num - 1) / 2 + 4] = ' ';
    }
    BeginBatchDraw();
    settextcolor(GREEN);
    int height = 0, width = 0;
    settextstyle(HEIGHT, WIDTH, "楷体");
    for (int i = 0; i < line_num; i++)
    {

        for (int j = 0; j < col_num; j++)
        {
            height = 15 + HEIGHT * i;
            width = 85 + WIDTH * j;
            outtextxy(width, height, photohead[i][j]);

        }

    }
    FlushBatchDraw();
    EndBatchDraw();
}

void fight(int part[row_inner][line_inner])
{
    iffight = 1;
    initgraph(1500, 900, EW_SHOWCONSOLE);		// 窗口大小
    setbkcolor(RGB(255, 251, 240));				// 背景色
    cleardevice();								// 清屏显示背景色
    setfillcolor(RGB(255, 251, 240));			// 填充颜色背景色
    setlinecolor(BLACK);						// 黑色线
    setlinestyle(PS_SOLID, 4);					// 实线 粗细4
    BeginBatchDraw();
    drawRight();								// 右侧进入战斗起始界面

    int a, b, c;
    int fightPokemen[3] = { 0 };
    int j = 0;
    for (int i = 0; i <= 115; i++) {
        if (take_part[i] == 1) {
            fightPokemen[j] = i;
            j++;
        }
    }
    a = fightPokemen[0];
    b = fightPokemen[1];
    c = fightPokemen[2];

    // 定义宝可梦名称
    int p_one = position(POKEMEN[a].name);
    int p_two = position(POKEMEN[b].name);
    int p_three = position(POKEMEN[c].name);

    for (int o = 0; o < many; o++)
    {
        if (pokemen_level[o][0] < 1)
        {
            pokemen_level[o][0]++;
        }
    }
    int high_level = 0; //三只宝可梦中最高的等级
    for (int k = 0; k < 3; k++)
    {
        if (pokemen_level[fightPokemen[k]][0] >= high_level)
        {
            high_level = pokemen_level[fightPokemen[k]][0];
        }
    }

    int temp_level = rand() % (5) + high_level - 2; //对方宝可梦的等级在我方宝可梦的上下两级
    while (temp_level <= 0)
    {
        temp_level = rand() % (high_level + 3) + (high_level - 2);
    }
    live_number[0] = (float)(500 + (pokemen_level[chosenPokemen][0] * 50)); //我方血量
    live_number[1] = (float)((500 + (temp_level * 50)) * HARD); //敌方血量

    OCCUR = pokemenJudge(part); //地貌当中出现的那只宝可梦
    pokemenCopy(part, temp_level);

    drawLeft();									// 左侧进入战斗起始界面
    // 引入敌方宝可梦字符画
    settextcolor(BLACK);						// 文字颜色
    settextstyle(3, 3, "宋体");					// 字体形式 高度，宽度，字体
    setbkmode(TRANSPARENT);						// 考虑到文字背景也有默认颜色，可能发生遮挡，所以将文字背景改为透明
    int x1 = 1100;								// 设置字符画输出的水平位置
    int	y1 = 20;								// 设置字符画输出的竖直位置
    // 输出字符画
    for (int i = 0; i < 100; i++) {
        outtextxy(x1, y1, POKEMEN[OCCUR].a[i]);
        y1 += 3;
    }
    FlushBatchDraw();
    EndBatchDraw();
    // 第一次选择出战的宝可梦
    chosenPokemen = firstChoose(getMouseMessage(), p_one, p_two, p_three, a, b, c);

    float myallBlood = live_number[0];
    float youallBlood = live_number[1];
    int myAllblood = (int)(myallBlood / 100);
    char myAllBlood[100];
    _itoa_s(myAllblood, myAllBlood, 100, 10);

    // 定义判断字数过后的输出位置
    int s_one = position(POKEMEN[chosenPokemen].skill_one);
    int s_two = position(POKEMEN[chosenPokemen].skill_two);
    int s_three = position(POKEMEN[chosenPokemen].skill_three);

    srand((unsigned long)time(0));

    while (iffight == 1) {

        int r = rand() % 3 + 1;
        choose(getMouseMessage(), s_one, s_two, s_three, r, youallBlood, myallBlood, myAllblood, myAllBlood, chosenPokemen, temp_level);
        times++;
        BeginBatchDraw();
        youPokemen(youallBlood, temp_level);
        myPokemen(myallBlood, myAllblood, myAllBlood, chosenPokemen);
        FlushBatchDraw();
        EndBatchDraw();
    }

    closegraph();
}


float typeJudge(int a, int b) //前一个是进攻方，后一个是防守方
{
    if ((a == 17 && b == 13) || (a == 14 && b == 13) || (a == 15 && b == 11) || (a == 8 && b == 10) || (a == 13 && b == 17) || (a == 13 && b == 18) || (a == 18 && b == 9) || (a == 4 && b == 15) || (a == 6 && b == 16))
    {
        return 0;
    }
    else if ((a == 14 && b == 17) || (a == 14 && b == 12) || (a == 14 && b == 6) || (a == 14 && b == 9) || (a == 11 && b == 14) || (a == 11 && b == 5) || (a == 11 && b == 1) || (a == 8 && b == 1) ||
        (a == 8 && b == 16) || (a == 15 && b == 8) || (a == 15 && b == 12) || (a == 15 && b == 10) || (a == 15 && b == 2) || (a == 15 && b == 4) || (a == 12 && b == 11) || (a == 12 && b == 5) || (a == 12 && b == 2) || (a == 12 && b == 6) || (a == 5 && b == 1) || (a == 5 && b == 18) || (a == 5 && b == 9) || (a == 13 && b == 13) || (a == 13 && b == 18) || (a == 10 && b == 12) || (a == 10 && b == 6) || (a == 10 && b == 16) || (a == 2 && b == 5) || (a == 2 && b == 10) || (a == 2 && b == 1) || (a == 2 && b == 6) || (a == 3 && b == 15) || (a == 3 && b == 12) || (a == 3 && b == 2) || (a == 1 && b == 15) || (a == 3 && b == 12) || (a == 3 && b == 3) || (a == 4 && b == 11) || (a == 3 && b == 3) || (a == 18 && b == 14) || (a == 18 && b == 8) || (a == 6 && b == 11) || (a == 6 && b == 15) || (a == 6 && b == 1) || (a == 6 && b == 7) || (a == 7 && b == 7) || (a == 9 && b == 13) || (a == 9 && b == 18) || (a == 16 && b == 14) || (a == 16 && b == 7) || (a == 16 && b == 9))
    {
        return 2;
    }
    else if ((a == 17 && b == 12) || (a == 17 && b == 10) || (a == 14 && b == 11) || (a == 14 && b == 8) || (a == 14 && b == 5) || (a == 14 && b == 18) || (a == 14 && b == 16) || (a == 11 && b == 12) || (a == 11 && b == 10) || (a == 11 && b == 4) || (a == 8 && b == 8) || (a == 8 && b == 15) || (a == 8 && b == 12) || (a == 8 && b == 13) || (a == 15 && b == 5) || (a == 15 && b == 1) || (a == 12 && b == 14) || (a == 12 && b == 15) || (a == 12 && b == 10) || (a == 5 && b == 14) || (a == 5 && b == 11) || (a == 5 && b == 5) || (a == 5 && b == 13) || (a == 5 && b == 10) || (a == 5 && b == 2) || (a == 5 && b == 16) || (a == 13 && b == 9) || (a == 10 && b == 10) || (a == 10 && b == 2) || (a == 10 && b == 3) || (a == 10 && b == 4) || (a == 2 && b == 12) || (a == 2 && b == 2) || (a == 2 && b == 3) || (a == 2 && b == 7) || (a == 3 && b == 3) || (a == 3 && b == 1) || (a == 3 && b == 7) || (a == 1 && b == 11) || (a == 1 && b == 8) || (a == 1 && b == 5) || (a == 1 && b == 10) || (a == 1 && b == 2) || (a == 1 && b == 1) || (a == 1 && b == 7) || (a == 4 && b == 1) || (a == 4 && b == 4) || (a == 4 && b == 7) || (a == 18 && b == 10) || (a == 18 && b == 18) || (a == 6 && b == 10) || (a == 6 && b == 2) || (a == 6 && b == 3) || (a == 6 && b == 6) || (a == 7 && b == 10) || (a == 9 && b == 14) || (a == 9 && b == 9) || (a == 9 && b == 16) || (a == 16 && b == 8) || (a == 16 && b == 10) || (a == 16 && b == 2))
    {
        return 0.5;
    }
    else
    {
        return 1;
    }
}

int ball()
{
    srand((unsigned long)time(0));
    if (live_number[1] > 120)
    {
        return 0;
    }
    else
    {
        return rand() % 4;
    }
}

void levelPlus(int i)
{
    /*pokemen_level这个二维数组，第一列代表等级，第二列代表经验*/
    load("level.txt");  //加载等级文件
    pokemen_level[i][1] += 1;   //经验值加一
    int top;
    top = (pokemen_level[i][0] + 1) / 5;    //计数器，每隔五级，top加一
    if (pokemen_level[i][1] == (2 + top * 5)) //每升五级，所需要的经验多五只
    {
        pokemen_level[i][0]++;  //等级加一
        pokemen_level[i][1] = 0;    //经验值清空
        levelJudge(i);  //判断是否进化
    }
    save("level.txt");  //保存等级文件
}

void levelJudge(int i)
{
    /*前两个条件是判断宝可梦的等级达到了11级，21级。31级等可以进化的级数，第三个条件是判断它的下一只和它是不是同一种宝可梦
    ，换句话说就是看看有没有进化到最高级*/
    if ((pokemen_level[i][0] != 1) && (pokemen_level[i][0] % 10 == 1) && ((POKEMEN[i + 1].kind) == (POKEMEN[i].kind))) //每隔十级进化
    {
        POKEMEN[i + 1].trap = 1;    //捕获他的进化
        POKEMEN[i].trap = 0;    //放走原始宝可梦
        if (pokemen_level[i + 1][0] < pokemen_level[i][0])//继承等级和经验
        {
            pokemen_level[i + 1][0] = pokemen_level[i][0];
            pokemen_level[i + 1][1] = pokemen_level[i][1];
        }
        pokemen_level[i][0] = 0;    //清空原始宝可梦的等级和经验
        pokemen_level[i][1] = 0;
        take_part[i] = 0;   //休息原始宝可梦，出战进化后的宝可梦
        take_part[i + 1] = 1;
    }
}

int fightJudge() //判断谁胜利谁失败，1是对方胜利，2是我方胜利
{
    if (live_number[0] > 0 && live_number[1] > 0)
    {
        return 0;
    }
    else
    {
        if (live_number[0] <= 0)
        {
            return 1;
        }
        if (live_number[1] <= 0)
        {
            return 2;
        }
        return 0;
    }
}

void pokemenCopy(int part[row_inner][line_inner], int temp_level)
{

    if (POKEMEN[OCCUR].evolution == 1 && POKEMEN[OCCUR + 1].evolution == 1)   //防止出现与等级不相符的宝可梦
    {
        OCCUR = OCCUR;
    }
    else if (POKEMEN[OCCUR].evolution == 1 && POKEMEN[OCCUR + 1].evolution == 2 && temp_level > 10)
    {
        OCCUR += 1;
    }
    else
        if (POKEMEN[OCCUR].evolution == 2 && (temp_level < 11))
        {
            OCCUR -= 1;
        }
        else if (POKEMEN[OCCUR].evolution == 2 && POKEMEN[OCCUR + 1].evolution == 3 && (temp_level > 30))
        {
            OCCUR += 1;
        }
        else
            if (POKEMEN[OCCUR].evolution == 3 && temp_level < 11)
            {
                OCCUR -= 2;
            }
            else
                if (POKEMEN[OCCUR].evolution == 3 && temp_level < 21)
                {
                    OCCUR -= 1;
                }
                else if (POKEMEN[OCCUR].evolution == 3 && temp_level > 40 && (POKEMEN[OCCUR + 1].evolution == 4))
                {
                    OCCUR += 1;
                }
                else if (POKEMEN[OCCUR].evolution == 4 && temp_level < 41)
                {
                    OCCUR -= 1;
                }
                else {
                    OCCUR = OCCUR;
                }

}



// 左侧进入战斗起始界面
void drawLeft() {
    fillroundrect(20, 580, 1140, 880, 20, 20);  // 画底部左侧框
    settextcolor(BLACK);						// 文字颜色
    settextstyle(80, 0, "宋体");					// 字体形式 高度，宽度，字体
    setbkmode(TRANSPARENT);						// 考虑到文字背景也有默认颜色，可能发生遮挡，所以将文字背景改为透明
    outtextxy(40, 600, text[0]);				// 指定位置打印
    outtextxy(443, 600, POKEMEN[OCCUR].name);
    outtextxy(40, 690, text[1]);
}

// 右侧进入战斗起始界面
void drawRight() {
    fillroundrect(1160, 580, 1480, 880, 20, 20);	// 画底部右侧框
    settextcolor(BLACK);
    settextstyle(80, 0, "宋体");
    setbkmode(TRANSPARENT);
    outtextxy(1240, 600, "战斗");
    outtextxy(1240, 690, "捕捉");
    outtextxy(1240, 780, "逃跑");
}

// 检测长度
int position(const char* a) {
    switch (strlen(a)) {
    case 8:
        return 1200;
    case 6:
        return 1230;
    case 4:
        return 1260;
    case 2:
        return 1290;
    default: return 0;
    }
}

// 检测鼠标点击位置
int getMouseMessage() {
    while (true)
    {
        ExMessage msg = { 0 };																		// 初始量赋值
        if (peekmessage(&msg, EM_MOUSE))															// 检测鼠标信息
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:																	// 判断左键
                if (msg.x >= 1200 && msg.x <= 1440 && msg.y >= 590 && msg.y <= 680)					// 规定上方位置并返回值
                {
                    return 1;
                }
                else if (msg.x >= 1200 && msg.x <= 1440 && msg.y >= 681 && msg.y <= 770)			//规定中间位置并返回值
                {
                    return 2;
                }
                else if (msg.x >= 1200 && msg.x <= 1440 && msg.y >= 771 && msg.y <= 860)			// 规定下方位置并返回值
                {
                    return 3;
                }
            default:
                break;
            }
        }
    }
}

// 选择宠物
int chooseThePokemen(int n, int a, int b, int c) {
    int i = 0;
    switch (n) {
    case 1:
        i = a;
        break;
    case 2:
        i = b;
        break;
    case 3:
        i = c;
        break;
    }
    return i;
}

// 左侧战斗界面
void leftOutput(int a, double b, int c, double d) {
    fillroundrect(20, 580, 1140, 880, 20, 20);
    settextcolor(BLACK);
    settextstyle(80, 0, "宋体");
    setbkmode(TRANSPARENT);
    outtextxy(40, 600, POKEMEN[chosenPokemen].name);
    outtextxy(40, 690, text[3]);
    switch (a) {
    case 1:
        outtextxy(280, 690, POKEMEN[chosenPokemen].skill_one);
        break;
    case 2:
        outtextxy(280, 690, POKEMEN[chosenPokemen].skill_two);
        break;
    case 3:
        outtextxy(280, 690, POKEMEN[chosenPokemen].skill_three);
    }
    if (b == 0) {
        outtextxy(40, 780, text[8]);
    }
    else if (b == 0.5) {
        outtextxy(40, 780, text[7]);
    }
    else if (b == 1) {
        outtextxy(40, 780, text[6]);
    }
    else if (b == 2) {
        outtextxy(40, 780, text[5]);
    }

    Sleep(2000);								// 停留两秒

    fillroundrect(20, 580, 1140, 880, 20, 20);
    settextcolor(BLACK);
    settextstyle(80, 0, "宋体");
    setbkmode(TRANSPARENT);
    outtextxy(40, 600, text[4]);
    outtextxy(280, 600, POKEMEN[OCCUR].name);
    outtextxy(40, 690, text[3]);
    switch (c) {
    case 1:
        outtextxy(280, 690, POKEMEN[OCCUR].skill_one);
        break;
    case 2:
        outtextxy(280, 690, POKEMEN[OCCUR].skill_two);
        break;
    case 3:
        outtextxy(280, 690, POKEMEN[OCCUR].skill_three);
        break;
    }
    if (d == 0) {
        outtextxy(40, 780, text[8]);
    }
    else if (d == 0.5) {
        outtextxy(40, 780, text[7]);
    }
    else if (d == 1) {
        outtextxy(40, 780, text[6]);
    }
    else if (d == 2) {
        outtextxy(40, 780, text[5]);
    }
    drawRight();
}

// 敌方宝可梦界面
void youPokemen(float youallBlood, int temp_level) {
    BeginBatchDraw();
    char youLevel[100];
    float youPercentage = live_number[1] / youallBlood;
    int bloodLength = (int)((float(320)) * youPercentage);
    youBlood = 1100 + bloodLength;
    _itoa_s(temp_level, youLevel, 100, 10);
    fillroundrect(1000, 400, 1450, 500, 40, 40);
    solidrectangle(996, 380, 1446, 480);
    solidrectangle(1440, 390, 1460, 430);
    solidrectangle(990, 480, 1020, 510);
    settextcolor(BLACK);
    settextstyle(80, 0, "宋体");
    setbkmode(TRANSPARENT);
    outtextxy(1000, 340, POKEMEN[OCCUR].name);
    settextcolor(BLACK);
    settextstyle(50, 0, "Cascadia Code");
    setbkmode(TRANSPARENT);
    outtextxy(1360, 370, "Lv");
    outtextxy(1410, 370, youLevel);
    outtextxy(1040, 440, "HP");
    setfillcolor(RED);
    if (youBlood < 1100) {
        youBlood = 1101;
    }
    solidrectangle(1100, 460, youBlood, 480);

    setfillcolor(RGB(255, 251, 240));
    FlushBatchDraw();
    EndBatchDraw();
}

// 我方宝可梦界面
void myPokemen(float myallBlood, int myAllblood, char myAllBlood[100], int chosenPokemen) {
    BeginBatchDraw();
    char myLevel[100], nowMyBlood[100];
    float myPercentage = live_number[0] / myallBlood;
    int bloodLength = (int)((float(320)) * myPercentage);
    myBlood = 130 + bloodLength;
    int nowMyblood = (int)((float(myAllblood)) * myPercentage);
    _itoa_s(nowMyblood, nowMyBlood, 100, 10);
    _itoa_s(pokemen_level[chosenPokemen][0], myLevel, 100, 10);
    fillroundrect(50, 100, 500, 200, 40, 40);
    solidrectangle(54, 80, 504, 180);
    solidrectangle(40, 90, 60, 130);
    solidrectangle(480, 180, 510, 210);
    settextcolor(BLACK);
    settextstyle(80, 0, "宋体");
    setbkmode(TRANSPARENT);
    outtextxy(25, 40, POKEMEN[chosenPokemen].name);
    settextcolor(BLACK);
    settextstyle(50, 0, "Cascadia Code");
    setbkmode(TRANSPARENT);
    outtextxy(385, 70, "Lv");
    outtextxy(435, 70, myLevel);
    outtextxy(70, 135, "HP");
    setfillcolor(RED);
    if (myBlood < 130) {
        myBlood = 131;
    }
    solidrectangle(130, 155, myBlood, 175);
    setfillcolor(RGB(255, 251, 240));
    outtextxy(465, 135, nowMyBlood);
    outtextxy(510, 135, "/");
    outtextxy(535, 135, myAllBlood);
    FlushBatchDraw();
    EndBatchDraw();
}

// 出战宠物
void choosePokemen(int chosenPokemen) {
    settextcolor(BLACK);
    settextstyle(3, 3, "宋体");
    setbkmode(TRANSPARENT);
    int x, y;
    x = 100;
    y = 240;

    // 输出字符画
    BeginBatchDraw();
    for (int i = 0; i < 100; i++) {
        outtextxy(x, y, POKEMEN[chosenPokemen].a[i]);
        y += 3;
    }
    fillroundrect(20, 580, 1140, 880, 20, 20);
    settextcolor(BLACK);
    settextstyle(80, 0, "宋体");
    setbkmode(TRANSPARENT);
    FlushBatchDraw();
    EndBatchDraw();
    // 第一次出现固定语句
    if (times == 0) {
        fillroundrect(20, 580, 1140, 880, 20, 20);
        settextcolor(BLACK);
        settextstyle(80, 0, "宋体");
        setbkmode(TRANSPARENT);
        outtextxy(40, 600, text[2]);
        outtextxy(40, 690, POKEMEN[chosenPokemen].name);
    }
}

// 第一次选择出战的宝可梦
int firstChoose(int n, int p_one, int p_two, int p_three, int a, int b, int c) {
    int i = 0;
    switch (n) {
    case 1:														// 选择战斗
        fillroundrect(1160, 580, 1480, 880, 20, 20);
        settextcolor(BLACK);
        settextstyle(60, 0, "宋体");
        outtextxy(p_one, 610, POKEMEN[a].name);
        outtextxy(p_two, 700, POKEMEN[b].name);
        outtextxy(p_three, 790, POKEMEN[c].name);
        clickPlace = getMouseMessage();							// 获取鼠标点击位置
        i = chooseThePokemen(clickPlace, a, b, c);				// 选择宠物
        drawRight();											// 右侧进入战斗起始界面
        break;
    case 2:                                                     // 选择捕捉
        if (ball() == 0)
        {
            fillroundrect(20, 580, 1140, 880, 20, 20);
            settextcolor(BLACK);
            settextstyle(80, 0, "宋体");
            setbkmode(TRANSPARENT);
            outtextxy(40, 600, text[11]);
            outtextxy(40, 690, POKEMEN[OCCUR].name);
        }
        else {
            POKEMEN[OCCUR].trap = 1;
            fillroundrect(20, 580, 1140, 880, 20, 20);
            settextcolor(BLACK);
            settextstyle(80, 0, "宋体");
            setbkmode(TRANSPARENT);
            outtextxy(40, 600, text[10]);
            outtextxy(40, 690, POKEMEN[OCCUR].name);
        }

        Sleep(2000);

        iffight = 0;
        break;
    case 3:														// 选择逃跑
        fillroundrect(20, 580, 1140, 880, 20, 20);
        settextcolor(BLACK);
        settextstyle(80, 0, "宋体");
        setbkmode(TRANSPARENT);
        outtextxy(40, 600, text[9]);

        Sleep(2000);

        iffight = 0;
        break;
    }
    return i;
}

// 选择功能
void choose(int a, int s_one, int s_two, int s_three, int c, float youallBlood, float myallBlood, int myAllblood, char myAllBlood[100], int chosenPokemen, int temp_level) {
    switch (a) {
    case 1:// 选择战斗
        youPokemen(youallBlood, temp_level);// 敌方宝可梦
        myPokemen(myallBlood, myAllblood, myAllBlood, chosenPokemen);// 我方宝可梦
        choosePokemen(chosenPokemen);

        fillroundrect(1160, 580, 1480, 880, 20, 20);
        settextcolor(BLACK);
        settextstyle(60, 0, "宋体");
        outtextxy(s_one, 610, POKEMEN[chosenPokemen].skill_one);
        outtextxy(s_two, 700, POKEMEN[chosenPokemen].skill_two);
        outtextxy(s_three, 790, POKEMEN[chosenPokemen].skill_three);

        clickPlace = getMouseMessage();
        // live_number[1] -= POKEMEN[chosenPokemen].beat_one * (fuckJudge(POKEMEN[chosenPokemen].skill_type[clickPlace - 1], POKEMEN[OCCUR].type));
        switch (clickPlace)
        {
        case 1:
        {
            live_number[1] -= POKEMEN[chosenPokemen].beat_one * (typeJudge(POKEMEN[chosenPokemen].skill_type[0], POKEMEN[OCCUR].type));
            break;
        }
        case 2:
        {
            live_number[1] -= POKEMEN[chosenPokemen].beat_two * (typeJudge(POKEMEN[chosenPokemen].skill_type[1], POKEMEN[OCCUR].type));
            break;
        }
        case 3:
        {
            live_number[1] -= POKEMEN[chosenPokemen].beat_three * (typeJudge(POKEMEN[chosenPokemen].skill_type[2], POKEMEN[OCCUR].type));
            break;
        }
        default:
            break;
        }
        
        switch (c) // j是对面随机出的技能
        {
        case 1:
        {
            live_number[0] -= (POKEMEN[OCCUR].beat_one * HARD) * (typeJudge(POKEMEN[OCCUR].skill_type[0], POKEMEN[chosenPokemen].type));
            break;
        }
        case 2:
        {
            live_number[0] -= (POKEMEN[OCCUR].beat_two * HARD) * (typeJudge(POKEMEN[OCCUR].skill_type[1], POKEMEN[chosenPokemen].type));
            break;
        }
        case 3:
        {
            live_number[0] -= (POKEMEN[OCCUR].beat_three * HARD) * (typeJudge(POKEMEN[OCCUR].skill_type[2], POKEMEN[chosenPokemen].type));
            break;
        }
        default:
            break;
        }
        myAttackEffect = typeJudge(POKEMEN[chosenPokemen].skill_type[clickPlace - 1], POKEMEN[OCCUR].type);
        youAttackEffect = typeJudge(POKEMEN[OCCUR].skill_type[clickPlace - 1], POKEMEN[chosenPokemen].type);
        leftOutput(clickPlace, myAttackEffect, c, youAttackEffect);									// 左侧战斗界面
        if (fightJudge() == 2) //对方宝可梦死亡
        {
            fillroundrect(20, 580, 1140, 880, 20, 20);
            settextcolor(BLACK);
            settextstyle(80, 0, "宋体");
            setbkmode(TRANSPARENT);
            levelPlus(chosenPokemen);
            outtextxy(40, 600, text[12]);
            Sleep(2000);
            iffight = 0;
            break;
        }
        if (fightJudge() == 1) //我方宝可梦死亡
        {
            fillroundrect(20, 580, 1140, 880, 20, 20);
            settextcolor(BLACK);
            settextstyle(80, 0, "宋体");
            setbkmode(TRANSPARENT);
            outtextxy(40, 600, POKEMEN[chosenPokemen].name);
            outtextxy(40, 690, text[13]);
            Sleep(2000);
            iffight = 0;
            break;
        }
        drawRight();
        break;
    case 2:// 选择捕捉 有3/4的概率抓到宝可梦
        if (ball() == 0)
        {
            fillroundrect(20, 580, 1140, 880, 20, 20);
            settextcolor(BLACK);
            settextstyle(80, 0, "宋体");
            setbkmode(TRANSPARENT);
            outtextxy(40, 600, text[11]);
            outtextxy(40, 690, POKEMEN[OCCUR].name);
        }
        else {
            POKEMEN[OCCUR].trap = 1;
            fillroundrect(20, 580, 1140, 880, 20, 20);
            settextcolor(BLACK);
            settextstyle(80, 0, "宋体");
            setbkmode(TRANSPARENT);
            outtextxy(40, 600, text[10]);
            outtextxy(40, 690, POKEMEN[OCCUR].name);
        }

        Sleep(2000);

        iffight = 0;
        break;
    case 3:// 选择逃跑
        fillroundrect(20, 580, 1140, 880, 20, 20);
        settextcolor(BLACK);
        settextstyle(80, 0, "宋体");
        setbkmode(TRANSPARENT);
        outtextxy(40, 600, text[9]);

        Sleep(2000);

        iffight = 0;
        break;
    }
}
void save(const char* filename)
{
    FILE* fp = NULL;
    fopen_s(&fp, filename, "w+");

    int i, j;
    for (i = 0; i < many; i++)
    {
        for (j = 0; j < 2; j++)
        {
            fprintf(fp, "%d ", pokemen_level[i][j]);
        }
    }
    fclose(fp);
}

void load(const char* filename)
{
    FILE* fp = NULL;
    fopen_s(&fp, filename, "r");
    int i, j;
    for (i = 0; i < many; i++)
    {
        for (j = 0; j < 2; j++)
        {
            fscanf_s(fp, "%d ", &pokemen_level[i][j]);
        }
    }
    fclose(fp);
}
void saveTrap(const char* filename)
{
    FILE* fp = NULL;
    fopen_s(&fp, filename, "w+");

    int i;
    for (i = 0; i < many; i++)
    {
        fprintf(fp, "%d ", POKEMEN[i].trap);
    }
    fclose(fp);
}
void loadTrap(const char* filename)
{
    FILE* fp = NULL;
    fopen_s(&fp, filename, "r");
    int i;
    for (i = 0; i < many; i++)
    {
        fscanf_s(fp, "%d ", &POKEMEN[i].trap);
    }
    fclose(fp);
}

void saveTakePart(const char* filename)
{
    FILE* fp = NULL;
    fopen_s(&fp, filename, "w+");
    int i;
    for (i = 0; i < many; i++)
    {
        fprintf_s(fp, "%d ", take_part[i]);
    }
    fclose(fp);
}

void loadTakePart(const char* filename)
{
    FILE* fp = NULL;
    fopen_s(&fp, filename, "r");
    int i;
    for (i = 0; i < many; i++)
    {
        fscanf_s(fp, "%d", &take_part[i]);
    }
    fclose(fp);
}