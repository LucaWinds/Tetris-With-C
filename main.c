
/*
2022�г⵵ 1�б� 2�� ������ ���� ������Ʈ
GSA 1403 �輺��
*/


/*
��Ʈ������?
�� ���� �簢������ �̷���� '��Ʈ�ι̳�'�� �������� ��Ÿ�� �ٴڰ� ��� ���� ��������.
�� ������ ��ǥ�� �� '��Ʈ�ι̳�'�� �����̰� 90���� ȸ���Ͽ�, ������ ��ƴ ���� ä��� ���̴�.
�̷��� ������ ������� �� �� ���� �������� �� ���� ����� �Ʒ��� �������µ� ��Ʈ���� ������ ����ɼ���
'��Ʈ�ι̳�'�� �� ���� �������� ������ ���� ����� ����� �������� ���� �޿�,
'��Ʈ�ι̳�'�� �� �� ������ ���� �Ǹ� ������ ������ �ȴ�.
��ټ��� ��Ʈ������ ���� ����� �� ����� ���� ���ټ��� ������ �� ���̴� ���̴�.
(��Ű���)

I, J, L, O, S, T, Z
7���� ��Ʈ�ι̳밡 �����մϴ�.
*/


/*
�� ������ Ư¡|
���� �����ϴ� ���� �������� ��Ʈ���� ��Ģ�� ��κ� ������, �������� ���� ����� �ֽ��ϴ�.
1. ű
2. T���� ���� Ư�� ���
3. ������

system("cls")�� Ȱ���� �ܼ�â �����̱⿡ ��ǻ�� ��翡 ���� �����̴� ������ ���� �� �ֽ��ϴ�.
�ڵ� �� ����� ����� ����� �����ϴ� ���� ã�Ƽ�..
2�б� ������Ʈ���� ���� �� ����� �ܼ�â ������ �غ��� �մϴ�.
*/


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>      //Ű���� �Է��� �ޱ� ���� �������
#include<windows.h>      //�۾� ���(Sleep �Լ�)�� ���� �������
#include<time.h>
#include <stdbool.h> //boolean ���� ���
#include<MMSystem.h> //�Ҹ� ���
#pragma comment(lib,"Winmm.lib") //API ���� ���

void gotoxy(int x, int y);
/*
gotoxy : �ܼ�â���� ���ϴ� �κп� ����� �� �ֵ��� �ϴ� �Լ���, �ְܼ��� ���߿� �ʼ������� ���ȴ�.
������ ���� �ٸ� �κ��� �ǵ��� �ʰ� �ű⿡ �� Ŀ���� ��ġ��ų�� �־ �ſ� ��!
*/

void play_tetr();
void start_tetr(); //���� ���� �� ó�� ���̴� ��
void helper1_tetr(); //���� ����
void helper2_tetr();
int game_tetr(); //���� ��Ʈ�� �Լ�
void Init_tetr(); // ���� �⺻ ���� �Լ�
void RandomBlock_tetr(); //���� �� �������� �̰� ���� ���� ���̾��� ���� ���� ������ �ٲٴ� �Լ�
bool Crashchecker_tetr(int x, int y); //������ �� �΋H������ üũ
bool RotateCrashChecker_tetr(int x, int y, int BlockRotation); //ȸ���ϸ鼭 �΋H������ üũ
void FallingBlock_tetr(); //�� ����߸��� �Լ�
void BlockToGround_tetr(); //���� ���� ����� �� �����ð� ���� �����ǰ� �ϴ� �Լ�
void RemoveLine_tetr(); //�� ���� ��� ä���� �� ������� �ϴ� �Լ�
void DrawMap_tetr(); //�������� �׸��� �Լ�
void DrawBlock_tetr(); //���� �׸��� �Լ�
void InputKey_tetr(); //Ű �Է¹޴� �Լ�
void SpeedUp_tetr(); //������ �ӵ��� �ø��� �Լ�
void GameFinished_tetr(); //������ ������ �� �Ͼ�� �ϵ�
void BlockMoveCnt_tetr(); //���� �����̴� Ƚ�� ī��Ʈ�ؼ� 50ȸ �̻��̸� ���� �ϵ���
void LineCrash_tetr(); //�μ��� ���� ���� üũ�ؼ� �޺� ���


clock_t startDropT, endT, startGroundT; // �ð� üũ
/*
�� �Լ��� Sleep �Լ��ʹ� �ٸ��� ���α׷� ���࿡ ������ ���� �ʴ´�.
sleep �Լ��� sleep �Ǵ� ���� ���α׷��� ���� �����ϴµ�, �� ������ ���α׷��� ������ Ÿ�̸� ������ �Ͽ�
������ �ð����� ��� �ൿ (���⼭�� �������� �ð��� ���� ���� �ð�, ���� ���� �� ���⶧���� �ð��� �����)
�� �� �� �ֵ��� ������� �Լ�.
*/
int x = 8, y = 0; // �ʱ� �� ��ġ


int main()
{
    play_tetr();
}

int x_tetr = 8, y_tetr = 0; // �ʱ� �� ��ġ
//���� ����
int blockForm_tetr; //�迭�� ���� �� ���
int nextBlockForm_tetr; //���� �� ���
int holdBlockForm_tetr; //Ȧ������ �� ���
int blockRotation_tetr = 0; //�� ȸ�� ��� -> �迭�� ��
int key_tetr; //�Է¹��� Ű ��
int score_tetr = 0; //����
int droppingSpeed_tetr = 800; //�������� �ӵ� (��Ȯ���� ��ĭ �������µ� �ɸ��� �ð�) : ���� ������ ���� ���� �۾�����. 
int level_tetr = 1; //����
int cntBlockFall_tetr = 0; //�� ����߸� Ƚ�� : ���� ���� ô��
int cntBlockFallForUser_tetr = 0;
int cntLineCrashed_tetr = 0; //�μ��� ���� ����
int finishFactor_tetr = 0; //���� ������ ����
int holdingFactor_tetr = 0; //���� Ȧ���ϰ� �ٽ� Ȧ������ ���ϵ��� ������ ����
int restartFactor_tetr; //������� �ϱ� ���� �Է¹޴� ����
int cntMove_tetr = 0; //������ Ƚ�� ī��Ʈ -> 50�� ������ �ڵ����� ��������. (���Ѵ�� �������� ���� ������ ���� �����ϱ�)
int cntLineCombo_tetr = 0; //�ѹ��� ������ ���ִ°� ī��Ʈ
int CHECK_tetr = 0; //���� Ư���� ����
/*
CHECK�� ���� ���� �ݺ����� �ѹ��� �������� 1�� �ø���. (�ݺ������� �ð� ���� �Լ��� ���⿡ ��û�� �ӵ��� �þ��)
�� CHECK ���� 10�� �Ѿ�� �Ǹ� CHECK�� 0���� �ǵ�����, �׵��� ����� ���� ������ ī��Ʈ�Ͽ� �޺����� ����ϴ� ��Ŀ����.
�ѹ��� ���� �������°� ī��Ʈ�� ������ ����� ã�� ���ؼ� �̷��� �̻��� ��Ŀ���� ���....
*/


int singleLine_tetr = 0, doubleLine_tetr = 0, tripleLine_tetr = 0, tetrisLine_tetr = 0; //�ѹ��� ���� �� ���� UI�� ���� ���� ����


int block_tetr[7][4][4][4] = { // �� ���� : 4���� �迭 ���� : (���)(ȸ��)(x��ǥ)(y��ǥ)
   { // �Ǹ�� ��
     {
       {0,0,0,0},
       {0,1,0,0},
       {1,1,1,0},
       {0,0,0,0}
     },
     {
       {0,0,0,0},
       {0,1,0,0},
       {0,1,1,0},
       {0,1,0,0}
     },
     {
       {0,0,0,0},
       {0,0,0,0},
       {1,1,1,0},
       {0,1,0,0}
     },
     {
       {0,0,0,0},
       {0,1,0,0},
       {1,1,0,0},
       {0,1,0,0}
     }
   },
   {    // ��� ��
     {
       {0,0,0,0},
       {0,1,1,0},
       {1,1,0,0},
       {0,0,0,0}
     },
     {
       {0,0,0,0},
       {1,0,0,0},
       {1,1,0,0},
       {0,1,0,0}
     },
     {
       {0,0,0,0},
       {0,1,1,0},
       {1,1,0,0},
       {0,0,0,0}
     },
     {
       {0,0,0,0},
       {1,0,0,0},
       {1,1,0,0},
       {0,1,0,0}
     }
   },
   {   // ��� �� �ݴ�
     {
       {0,0,0,0},
       {1,1,0,0},
       {0,1,1,0},
       {0,0,0,0}
     },
     {
       {0,0,0,0},
       {0,1,0,0},
       {1,1,0,0},
       {1,0,0,0}
     },
     {
       {0,0,0,0},
       {1,1,0,0},
       {0,1,1,0},
       {0,0,0,0}
     },
     {
       {0,0,0,0},
       {0,1,0,0},
       {1,1,0,0},
       {1,0,0,0}
     }
   },
   {   // 1���� ��
     {
       {0,1,0,0},
       {0,1,0,0},
       {0,1,0,0},
       {0,1,0,0}
     },
     {
       {0,0,0,0},
       {0,0,0,0},
       {1,1,1,1},
       {0,0,0,0}
     },
     {
       {0,1,0,0},
       {0,1,0,0},
       {0,1,0,0},
       {0,1,0,0}
     },
     {
       {0,0,0,0},
       {0,0,0,0},
       {1,1,1,1},
       {0,0,0,0}
     }
   },
   {   // L���� ��
     {
       {0,0,0,0},
       {1,0,0,0},
       {1,1,1,0},
       {0,0,0,0}
     },
     {
       {0,0,0,0},
       {1,1,0,0},
       {1,0,0,0},
       {1,0,0,0}
     },
     {
       {0,0,0,0},
       {1,1,1,0},
       {0,0,1,0},
       {0,0,0,0}
     },
     {
       {0,1,0,0},
       {0,1,0,0},
       {1,1,0,0},
       {0,0,0,0}
     }
   },
   {   // L���� �� �ݴ�
     {
       {0,0,0,0},
       {0,0,1,0},
       {1,1,1,0},
       {0,0,0,0}
     },
     {
       {1,0,0,0},
       {1,0,0,0},
       {1,1,0,0},
       {0,0,0,0}
     },
     {
       {0,0,0,0},
       {1,1,1,0},
       {1,0,0,0},
       {0,0,0,0}
     },
     {
       {0,0,0,0},
       {1,1,0,0},
       {0,1,0,0},
       {0,1,0,0}
     }
   },
   {   // �׸� ��
     {
       {0,0,0,0},
       {0,1,1,0},
       {0,1,1,0},
       {0,0,0,0}
     },
     {
       {0,0,0,0},
       {0,1,1,0},
       {0,1,1,0},
       {0,0,0,0}
     },
     {
       {0,0,0,0},
       {0,1,1,0},
       {0,1,1,0},
       {0,0,0,0}
     },
     {
       {0,0,0,0},
       {0,1,1,0},
       {0,1,1,0},
       {0,0,0,0}
     }
   }
};


// 1: �� 2: �������� �� 3: ������ ��
int space_tetr[25 + 1][10 + 2];

/*
gotoxy : �ܼ�â���� ���ϴ� �κп� ����� �� �ֵ��� �ϴ� �Լ���, �ְܼ��� ���߿� �ʼ������� ���ȴ�.
������ ���� �ٸ� �κ��� �ǵ��� �ʰ� �ű⿡ �� Ŀ���� ��ġ��ų�� �־ �ſ� ��!
*/



void play_tetr() //�غ� ȭ��
{
    system("mode con cols=88 lines=22"); // ó�� �ܼ�â�� ũ�� ����
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 12; j++) {
            if (i == 25 || j == 0 || j == 11) {
                space_tetr[i][j] = 1;
                // gotoxy(50 + i, 30 + j);
                 //printf("1");
            }
            else {
                space_tetr[i][j] = 0;
                // gotoxy(50 + i, 30 + j);
                // printf("0");
            }

            //Sleep(10);
        }
    }
    // Sleep(1000);
    char startFactor; //������ �� �Է¹޴� ���ڷ�, ������ �ٷ� �������� ������ ���� üũ
    system("cls");
    printf("�� �ܼ�â�� �۲��� consolas�� �����ϰ� ������ �������ּ���\n");
    printf("�� �ٸ� �۲��� ����� �� ���� ȭ���� ���� �� �ֽ��ϴ�\n\n");

    printf("�� �� ���� ���� �÷��̸� ���� ���� ������ ���ּ���\n");
    printf("�� �ڼ��� ������ h�� �Է��� �˾ƺ��ּ���\n\n");

    printf("�� �ܼ� â�� ũ�⸦ �� �۰� �������� �����ּ���\n");
    printf("�� ���� ������ ���ϸ� y�� �Է����ּ���\n\n");

    printf("�� ���� �÷��� ��� �� �⺻ ���� ������ �˰� �����ø� h�� �Է����ּ���\n");

A: //����� �ٽ� ���ƿðž�
    startFactor = _getch();

    if (startFactor == 'y') start_tetr(); //���� ����
    else if (startFactor == 'h') helper1_tetr(); //����
    else goto A; //�̻��Ѱ� ������ �ٽ� �Է� ��Ű��

}



void helper1_tetr() //���� 1������
{
    char startFactor;

    system("cls"); //���� ���ְ� ������ ��������.
    printf("�� �ܼ�â�� �� �κ��� ��Ŭ���մϴ�.\n");
    printf("�� �⺻�� �� �� �۲� �� �����մϴ�.\n");
    printf("�� �۲��� consolas�� �����մϴ�.\n\n\n");
    Sleep(1000);

    printf("�� �ڵ� 521���� ã�ƺ��ϴ�.\n");
    printf("�� �ٿ���� wav ������ ��θ� 414���� �ִ� ������ �������ݴϴ�.\n");
    printf("�� \\�� \\\\ �� ��� �ٲ��ݴϴ�. \n\n");
    printf("���� : D:\\\\���ְ��а�\\\\��������\\\\��Ʈ���� A ���.wav\n");
    Sleep(1000);

    printf("���� �������� ���� ����, h�� �Է����ּ���.");

A:
    startFactor = _getch();

    if (startFactor == 'h') helper2_tetr();
    else goto A;
}

void helper2_tetr() //���� 2������
{
    char startFactor2;

    system("cls"); //���� ���ְ� ������ ��������.
    printf("�� ��Ʈ������ ������ �����������, �������� ���� �״� �����Դϴ�.\n");
    printf("�� ����� �����鼭 �� ���� �� ä������ �� ���� ������ϴ�\n");
    printf("�� ����� �� ������ �ö��� �ʰ� ������ ��Ƽ�鼭 �÷����ϴ� �����Դϴ�.\n\n\n");
    Sleep(1000);

    printf("  ��   : Rotate        SPACE : Hard Drop\n");
    Sleep(300);
    printf("��  �� : Left / Right  C : Hold\n");
    Sleep(300);
    printf("  ��   : Soft Drop     ESC  : Quit\n\n\n");
    Sleep(1000);

    printf("�� �ϵ� ����� ��� ���� ������ �����, ����Ʈ����� ��ĭ�� ���� ������ ����� ���մϴ�.\n");
    printf("�� ���� ���� �������� �������� �ִ��� ���� ���� ���� ���� ������ ����غ�����! \n\n");
    Sleep(1000);

    printf("������ �����ϱ� ����, y�� �Է����ּ���.");

A:
    scanf("%c", &startFactor2);

    if (startFactor2 == 'y') start_tetr();
    else goto A;
}


void start_tetr() //���� ���� ȭ��
{
    system("mode con cols=88 lines=22"); // ó�� �ܼ�â�� ũ�� ����
    int gameStartFactor = 0;
    system("cls");
    printf("#                     ####### ####### ####### ######  ###  #####                       #\n#                        #    #          #    #     #  #  #     #                      #\n#                        #    #          #    #     #  #  #                            #\n#                        #    #####      #    ######   #   #####                       #\n#                        #    #          #    #   #    #        #                      #\n#                        #    #          #    #    #   #  #     #                      #\n#                        #    #######    #    #     # ###  #####                       #\n\n");
    printf("                               PRESS ANY BUTTON TO START                                \n");
    printf("                        2022�г⵵ 1�б� 2�� ������ ����������Ʈ                         \n\n\n");
    printf("                            --- ���� ���� �� ���� ��� ---                               \n");
    printf("                             ������ Ȧ�� ����� ���峲                                  \n");
    printf("                               ������ ������ ��ģ��                                  \n");
    printf("                       �Ϻ� ��⿡�� restart�� �۵����� �ʴ´�                                  \n");
    printf("                                                                ");
    gameStartFactor = _getch();

    system("cls");
    Init_tetr(); //���� ���� ����
    //�ε���...
    printf("\n\n\n\n                                      NOW LOADING...                                       \n\n\n\n\n      ");
    for (int i = 0; i < 24; i++) {
        printf("�� ");
        Sleep(50);
    }
    Sleep(200);
    system("cls");
    game_tetr(); //������ ���������� �����Ѵ�
}

void gotoxy(int x, int y) { //gotoxy ���� : ���ϴ� ��ġ�� Ŀ�� �ű�� : �뵵�� ��¹� ��ġ ����
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


int game_tetr() //���� ���� �Լ�
{
    system("mode con cols=44 lines=28");//�ܼ�â ũ�⸦ ��Ʈ���� ������ �������
    int cntcntcntcnt;
    blockForm_tetr = rand() % 7; //ó�� �� ��� �����ֱ�
    for (int i = 3; i > 0; i--) { //���� �غ�
        DrawMap_tetr(); //������ �׸���
        gotoxy(11, 11); //3, 2, 1 ī��Ʈ
        printf("%d", i);
        Sleep(1000);
        system("cls");
    }

    startDropT = clock(); //�������� �����Ѵ�!
    //sndPlaySoundA("D:\\���ְ��а�\\��������\\��Ʈ���� A ���.wav", SND_ASYNC | SND_LOOP);

    /*
    ��Ʈ���� �Ҹ� ���� �ϴ� �ڵ�
    �� �ڵ� § ����� ������ �����鼭 �ڵ带 ¥�� ������ ���� ��ġ�°� �Ⱦ �ּ�ó���� �Ǿ��ֽ��ϴ�.
    ����ϱ� ���ؼ��� �ּ��� ���� ( //�� ����� ) �ϰ� ���� ���� ��ġ�� ū����ǥ ���̿� ���ּ���.
    �� \�� \\�� ��� �ٲپ� ���ּž� �մϴ�.
    ���� : D:\\���ְ��а�\\��������\\��Ʈ���� A ���.wav

    ��� ������ ������� �ʴ´ٰų� ���� �����ϱ� ���������� �ٿ���� �����̴ٸ� �׳� �÷����ص� �����մϴ�!
    */

    /*
    ���� ������ ���� �ݺ����̰�, ���� ���� �� ��� �۵��Ǵ� �Լ����� ��� �������ش�. �� �Լ� �����
    �� �׸���
    �� �׸���
    ���� ���� ��Ҵ°�?
    �� �����
    Ű �Է¹ޱ�
    �ӵ� �ø���
    ������ �����°�?
    ���� 50ȸ �̻� ���������°�?

    �̴�. CHECK�� ���ؼ��� ���� ���� ��Ʈ�� �ڼ��� ����Ǿ� �ִ�.

    */
    while (true) { //���� ���� : ���� ����� ��� �۵��Ǵ� �Լ����� ��� �������ش�.
        DrawMap_tetr();
        DrawBlock_tetr();
        FallingBlock_tetr();
        BlockToGround_tetr();
        RemoveLine_tetr();
        InputKey_tetr();
        SpeedUp_tetr();
        BlockMoveCnt_tetr();

        //UI ������
        gotoxy(24, 1);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (block_tetr[nextBlockForm_tetr][1][i][j] == 1) {
                    gotoxy(30 + j * 2, 1 + i);
                    printf("��");
                }
            }
        }
        if (holdBlockForm_tetr != 0) {
            gotoxy(24, 8);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (block_tetr[holdBlockForm_tetr][1][i][j] == 1) {
                        gotoxy(30 + j * 2, 8 + i);
                        printf("��");
                    }
                }
            }
        }
        else {
            gotoxy(33, 9);
            printf("-");
        }

        if (CHECK_tetr > 10) {
            LineCrash_tetr();
            CHECK_tetr = 0;
        }
        else {
            CHECK_tetr++;
        }


        if (finishFactor_tetr != 0) {
            break;
        }
        //CHECK�� �뵵�� ���ؼ��� ���� ���� ��Ʈ�� �ڼ��� ����Ǿ� �ֽ��ϴ�.
        for (int i = 1; i <= 10; i++) {
            if (space_tetr[1][i] == 3) {
                GameFinished_tetr();
                goto A;
            }
        }
    }
A:

    //������ ������ ���ѹݺ����� Ż���Ѵ�

    return 0;
}


void Init_tetr() { //Ŀ�� ����� �õ� �缳�� ���
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    srand(time(NULL));
}

void RandomBlock_tetr() { //���� ���� �������� �̱�
    blockForm_tetr = nextBlockForm_tetr;
    nextBlockForm_tetr = rand() % 7;
}

void SpeedUp_tetr() { //12�� ����߸� ������ ������ �ӵ� ����
    if (cntBlockFall_tetr % 12 == 11) {
        droppingSpeed_tetr /= 1.2;
        level_tetr++;
        cntBlockFall_tetr++;
    }
}

/*
������ �μ����� �� �μ��� ������ üũ�Ͽ� ������ �ؿ�
��� �ν����� ������ ���� �����ش�.

�� �� : SINGLE
�� �� : DOUBLE
�� �� : TRIPLE
�� �� : TETRIS
�̶� TETRIS�� �����ϸ� ���� ������ �ߴ� Ư�� ȿ���� �ִ�.

���� ������ �޺��� ���� �߰� ������ �ο��Ѵ�.
*/
void LineCrash_tetr() { //������ �� �� �μ������� üũ�ؼ�, �ش� ������ �ø��� �μ� ���� ���� ī��Ʈ�Ѵ�.
    if (cntLineCombo_tetr == 1) {
        gotoxy(9, 26);
        printf("SINGLE");
        Sleep(300);
        singleLine_tetr++;
        cntLineCombo_tetr = 0;
    }
    else if (cntLineCombo_tetr == 2) {
        gotoxy(9, 26);
        printf("DOUBLE");
        Sleep(300);
        doubleLine_tetr++;
        cntLineCombo_tetr = 0;
    }
    else if (cntLineCombo_tetr == 3) {
        ;
        gotoxy(9, 26);
        printf("TRIPLE");
        Sleep(300);
        tripleLine_tetr++;
        cntLineCombo_tetr = 0;
    }
    else if (cntLineCombo_tetr == 4) { //��¹��� ������ �ִ� ������ ��¦��¦ ȿ���� �־�� �;��� �����̴�.
        gotoxy(7, 26);
        printf("��TETRIS��");
        Sleep(150);
        gotoxy(7, 26);
        printf("��TETRIS��");
        Sleep(150);
        gotoxy(7, 26);
        printf("��TETRIS��");
        tetrisLine_tetr++;

        cntLineCombo_tetr = 0;
    }

}

void BlockMoveCnt_tetr() { //���� �����̴� Ƚ���� ī��Ʈ�� ��, 50�� �Ѿ�� ������ �ϵ�����Ų��.
    if (cntMove_tetr > 50) {
        while (Crashchecker_tetr(x_tetr, y_tetr + 1) == false) { //�ϵ��� �ڵ�� �Ϻ� ���� (���� �߰��� �ִ°� ����)
            y_tetr++;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (block_tetr[blockForm_tetr][blockRotation_tetr][i][j] == 1) {
                    space_tetr[i + y_tetr][j + x_tetr / 2] = 3;
                }
            }
        }
        cntBlockFall_tetr++;
        cntBlockFallForUser_tetr++;
        holdingFactor_tetr = 0;
        x_tetr = 8;
        y_tetr = 0;
        cntMove_tetr = 0;
        RandomBlock_tetr();
    }
}

/*
���� ��ĭ �� �������� ��, ���̰ų� ���� �ִ� ���� ������ Ȯ���غ���.
�׷��ٸ�, true, �ƴ϶��, false�� return�Ѵ�.
���� ���� ��ǥ���� ��ĭ ���� ���� ������ �迭�� �ҷ��ͼ� �װ��� ���� �迭�� ���غ��� ����̴�.
*/
bool Crashchecker_tetr(int x, int y) { //�������鼭 ��
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block_tetr[blockForm_tetr][blockRotation_tetr][i][j] == 1) {
                int t = space_tetr[i + y][j + x / 2];
                if (t == 1 || t == 2 || t == 3) { // ���� ��, ���� ��
                    return true;
                }
            }
        }
    }
    return false;
}

/*
���� ���� �����ϴ�.
���� ȸ���Ǿ�����, ���̰ų� ���� �ִ� ���� ������ Ȯ���غ���.
�׷��ٸ�, true, �ƴ϶��, false�� return�Ѵ�.
���� ���� ȸ�������� 1 �� ���� ���� �迭�� �ҷ��� �����ǰ� ���غ��� ����̴�.

* ű�� �����Ǿ����� �ʴ�.
(ű�̶� : ���� ȸ���Ǿ��� �� ���� ��� �ȴٸ� �ڵ����� ���� ��ġ�� �� ĭ ������ �̵������ְ� ���� ȸ�������ִ� �ý���)
*/
bool RotateCrashChecker_tetr(int x, int y, int z) { //���鼭 ��
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block_tetr[blockForm_tetr][z + 1][i][j] == 1) {
                int t = space_tetr[i + y][j + x / 2];
                if (t == 1 || t == 2 || t == 3) { // ���� ��, ���� ��
                    return true;
                }
            }
        }
    }
    return false;
}

void FallingBlock_tetr() { //�΋H���� ������ ���� �ð����� �������� �ϱ�
    endT = clock();
    if ((float)(endT - startDropT) >= droppingSpeed_tetr) {
        //����߸��� ������ �ð��� �� �Լ��� �ߵ��� �ð��� ���ؼ�
        //���� �ð��� ������ ��ĭ ������ �Լ��� �ʱ�ȭ�����ִ� ����̴�.
        if (Crashchecker_tetr(x_tetr, y_tetr + 1) == true) return;
        y_tetr++;
        startDropT = clock();
        startGroundT = clock();
        system("cls");
    }
}

void BlockToGround_tetr() { //�ٴڿ� ������ �����ð� �� ����
    if (Crashchecker_tetr(x_tetr, y_tetr + 1) == true) {
        if ((float)(endT - startGroundT) > 1000) {
            // ���� ��� ���� : �����ǿ� ����� ����� �����Ѵ�.
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (block_tetr[blockForm_tetr][blockRotation_tetr][i][j] == 1) {
                        space_tetr[i + y_tetr][j + x_tetr / 2] = 3;
                    }
                }
            }
            score_tetr += 50; //������ �߰��ϰ�, �� ������ Ƚ���� �߰��ϰ� ���..
            cntBlockFall_tetr++;
            holdingFactor_tetr = 0;
            x_tetr = 8; //���� ��ǥ�� �ٽ� ó������ ����.
            y_tetr = 0;
            RandomBlock_tetr();
        }
    }
}

void RemoveLine_tetr() {
    for (int i = 25; i >= 0; i--) { // ������ ������ ��
        int cnt = 0;
        for (int j = 1; j < 11; j++) { //������ ���̿� ���ؼ� ���� �ִ��� ������ üũ�غ���.
            if (space_tetr[i][j] == 3) {
                cnt++;
            }
        }
        if (cnt >= 10) { // ������ �� ���ִٸ�
            cntLineCrashed_tetr++; //�μ� Ƚ�� �̸� �÷�����
            cntLineCombo_tetr++; //� �ν����� Ȯ���ϰ� �̰͵� �÷�����
            for (int j = 0; i - j >= 0; j++) {
                for (int x = 1; x < 11; x++) {
                    if (i - j - 1 >= 0)
                        space_tetr[i - j][x] = space_tetr[i - j - 1][x]; //���� �ִ� ������ �Ʒ��� ������.
                    else      // õ���̸� 0����
                        space_tetr[i - j][x] = 0; //�翬�ϰ�, õ�� ������ �迭�� ����. �׳� 0�� �����Ѵ�.
                }
            }
            score_tetr += 1000; //�� �� ����� �⺻ 1000�� �ο�
        }
    }
}

/*
�����ǿ� ����� �迭�� �״�� ������� ��, ����� �������̽��� �ٸ��ְ� �����μ�
�������� �ڽ��� ���� �÷��� ��Ȳ�� ������ �� �ִ�. (����, ���� ��)
*/
void DrawMap_tetr() { //������ �׸���
    gotoxy(0, 0);
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 12; j++) {
            if (space_tetr[i][j] == 1) {
                gotoxy(j * 2, i);
                printf("��");
            }
            else if (space_tetr[i][j] == 2) {
                gotoxy(j * 2, i);
                printf("��");
            }
            else if (space_tetr[i][j] == 3) {
                gotoxy(j * 2, i);
                printf("��");
            }
        }
    }


    //���⼭ ��û���� ���� ���̴� gotoxy

    gotoxy(24, 0);
    printf("�̢� NEXT BLOCK �̢�");

    gotoxy(24, 6);
    printf("�̢� HOLD BLOCK �̢�");

    /*
    ����� �������̽� �����ֱ�
    ����, ����, �μ� �� ����, ������Ʈ �̸�
    */
    gotoxy(24, 12);
    printf("�̢̢̢̢̢̢̢̢̢�");
    gotoxy(24, 13);
    printf(" level : %d", level_tetr);
    gotoxy(24, 14);
    printf(" score : %d ", score_tetr);
    gotoxy(24, 15);
    printf("�̢̢̢̢̢̢̢̢̢�");
    gotoxy(24, 17);
    printf(" single : %d", singleLine_tetr);
    gotoxy(24, 19);
    printf(" double : %d ", doubleLine_tetr);
    gotoxy(24, 21);
    printf(" triple : %d", tripleLine_tetr);
    gotoxy(24, 23);
    printf(" tetris : %d ", tetrisLine_tetr);
    gotoxy(24, 25);
    printf("�̢̢̢̢̢̢̢̢̢�");
    gotoxy(22, 26);
    printf("��");
    gotoxy(0, 26);
    printf("��");
    gotoxy(24, 26);
    printf("   2022 GSA ����");
    gotoxy(0, 27);
    printf("�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�");
}

/*
���� �׷��ִ� �Լ���, �����ǿ� ������ ������ ���� ���� ����� ���� ��ġ �ٽ� ���� �ְ� �ϸ� ��ǻ�Ϳ� ���α׷����� �Ӹ��� �����̰� ���� ������
���� ���� �����ǿ� �����ص��� ���� �׳� ���� ����ϴ� ����� �������μ�
���� ���̰� �ڵ� ���̵� ���� �� �־���!
�翬�� ����� ������ gotoxy�� �̿��ؼ� ����Ѵ�.
*/
void DrawBlock_tetr() {//���� �׸���
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block_tetr[blockForm_tetr][blockRotation_tetr][i][j] == 1) {
                gotoxy(x_tetr + j * 2, y_tetr + i);
                printf("��");
            }
        }
    }
}

/*
���� �Լ����� ������ ������� �˸��� ���� �����Լ��� �̵��ϴµ�, �̵��Ǹ� ���� ������ ����,
������ ������Ұ�����, ������ ������ ���´�.
*/
void GameFinished_tetr() { //���� ���� �Լ�
    system("cls");
    finishFactor_tetr++;

    DrawMap_tetr();

    gotoxy(3, 26); // ���ϴ� ��ġ�� �̵��ؼ� ����� ����� �����ݴϴ�.
    printf("Press R to restart");
A:
    restartFactor_tetr = _getch();

    if (restartFactor_tetr == 'r') { //�����, �ʱ�ȭ
        system("cls");
        score_tetr = 0; //��
        droppingSpeed_tetr = 800; //��
        level_tetr = 1; //��
        cntBlockFall_tetr = 0; //��
        cntLineCrashed_tetr = 0; //��
        cntBlockFallForUser_tetr = 0; //��
        finishFactor_tetr = 0; //��
        holdingFactor_tetr = 0; //ȭ
        cntMove_tetr = 0; //��
        holdBlockForm_tetr = 0;
        singleLine_tetr = 0, doubleLine_tetr = 0, tripleLine_tetr = 0, tetrisLine_tetr = 0; //��
        system("cls");
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 12; j++) {
                if (i == 25 || j == 0 || j == 11) {
                    space_tetr[i][j] = 1;
                    //   gotoxy(50 + i, 30 + j);
                    //   printf("1");
                }
                else {
                    space_tetr[i][j] = 0;
                    //  gotoxy(50 + i, 30 + j);
                    //  printf("0");
                }

                //   Sleep(10);
            }
        }
        //   Sleep(1000);
        start_tetr();
    }
    else {
        goto A;
    }



}

/*
conio ��������� �̿��� Ű �Է¹޴� �Լ��̴�.
�츮�� ���� ����ϴ� scanf���� �Լ����� ���� ���࿡ ġ������ ������ �ִµ�,
�ٷ� �Է��� ���� ������ ���α׷� ��ü�� ��������ٴ� ���̴�.
�׷��� ������ �ذ��ϱ� ���� ���� �� �Լ��ε�, �� �Լ��� ���α׷� ����� ���ÿ� Ű���忡 �Է��� �Ǿ������� �Ǻ����־�,
( _kbhit()�� boolean���� ��ȯ�Ͽ�, Ű���忡 ���� �Է��� �Ǹ� true�� ��ȯ�Ѵ�. )
�Է��� �Ǿ��� ���� �� �Էµ� Ű�� �������� _getch();��� �Լ��� �˾ƺ���
�ش��ϴ� Ű�� ���� �ൿ���� switch case ������ �Է����־���.
*/
void InputKey_tetr() { //conio ��������� �̿��� Ű �Է¹޴� �Լ�
    int temp = 0;
    if (_kbhit()) {
        key_tetr = _getch();
        switch (key_tetr) {
        case 32: // space
           /*
           space�� ������ �ϵ����� �Ǵµ�, �΋H�� ������ y���� ������ ���δ�.
           ���� ������ ������Ų��. �׸��� ��� �� �������µ� ���õ� �������� �ʱ�ȭ��Ų��.
           �� ������ Ƚ���� ī��Ʈ���ְ�, ���� �������� �����ִ� �Լ��� �̵���Ų��.
           */
            while (Crashchecker_tetr(x_tetr, y_tetr + 1) == false) {
                y_tetr++;
            }
            score_tetr += 250;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (block_tetr[blockForm_tetr][blockRotation_tetr][i][j] == 1) {
                        space_tetr[i + y_tetr][j + x_tetr / 2] = 3;
                    }
                }
            }
            cntBlockFall_tetr++;
            cntBlockFallForUser_tetr++;
            holdingFactor_tetr = 0;
            x_tetr = 8;
            y_tetr = 0;
            cntMove_tetr = 0;
            RandomBlock_tetr();
            break;
            /*
            left, right�� ���� ���� ��ǥ�� 2ĭ�� �а� (2ĭ�̶�� �ϴ°� ���� �����ǿ����� 1ĭ���� ���δ�)
            ���� ��� ������ �ð��� �ʱ�ȭ��Ű��, ������ Ƚ���� 1 �ø���.
            */
        case 75: // left
            if (Crashchecker_tetr(x_tetr - 2, y_tetr) == false) {
                x_tetr -= 2;
                startGroundT = clock();
                cntMove_tetr++;
            }
            break;
        case 77: // right
            if (Crashchecker_tetr(x_tetr + 2, y_tetr) == false) {
                x_tetr += 2;
                startGroundT = clock();
                cntMove_tetr++;
            }
            break;
            /*
            down ��ư�� ������ ����Ʈ ����� �ȴ�.
            down ��ư�� ������ �Ǹ� ���� �ð��� ���� ���������� �Ѵ�.
            �΋H���� ������ y��ǥ�� ������Ų��.
            */
        case 80: // down
            if (Crashchecker_tetr(x_tetr, y_tetr + 1) == false) {
                y_tetr++;
                score_tetr = score_tetr + 10;
            }
            break;
            /*
            up ��ư�� ������ ���� ȸ����Ų��.
            ȸ�������� �� �΋H���� �ʴ´ٸ� ȸ������ 1 �ø���, 360�� ���Ŵ� �ȵ��Ŷ� �����ϱ�
            ȸ������ 4�� ������ 0���� �ǵ������´�.
            */
        case 72: //up
            if (RotateCrashChecker_tetr(x_tetr, y_tetr, blockRotation_tetr) == false)
                blockRotation_tetr++;
            if (blockRotation_tetr >= 4) blockRotation_tetr = 0;
            startGroundT = clock();
            break;
            /*
            esc�� ������ ������ ��������ȴ�.
            �ܼ�â�� ũ�⸦ �����ϰ� �ٲپ��ְ� ���� ȭ���� ��� �� ��,
            ���α׷��� ���� �����Ų��.
            */
        case 27: //esc
            system("cls");
            exit(0);
            break;
            /*
            c�� ������ Ȧ�尡 �ȴ�.
            (Ȧ���, ���� ���ϴ� ���ȸ�ŭ ��� �־� �ʿ��� �� ���� �ֵ��� �ϴ� �����,
            �� �Ͽ� �� ���� ��� �����ϴ�.)
            �׷��� holdingFactor�� �̿��Ͽ� ���� �̹� �Ͽ� Ȧ�带 �ߴ��� ���ߴ��� Ȯ���ϰ�, Ȧ�带 �� �� �ִ� ��Ȳ�� ��

            1. Ȧ���� ���� ���� ��
               Ȧ���� ���� �� ���� ���� �ٲ۴�.
            2. Ȧ���� ���� ���� ��
               �� ���� ���� Ȧ�� ������ �ٲٰ�, ���� ���� ���� �����´�.

            Ȧ�忡 �����ϸ� holdingFactor�� 1 �ö� ���̻� Ȧ�带 �� �� ���� �ǰ�, ���� ����߸��� �ٽ� 0�� �Ǿ�
            hold�� ����� �� �ְ� �ȴ�.
            */
        case 99: //c
            if (holdingFactor_tetr == 0) {
                if (holdBlockForm_tetr != 0) {
                    temp = holdBlockForm_tetr;
                    holdBlockForm_tetr = blockForm_tetr;
                    blockForm_tetr = temp;
                    x_tetr = 8;
                    y_tetr = 0;
                    holdingFactor_tetr++;
                }
                else {
                    holdBlockForm_tetr = blockForm_tetr;
                    x_tetr = 8;
                    y_tetr = 0;
                    RandomBlock_tetr();
                    holdingFactor_tetr++;
                }
            }
            cntMove_tetr = 0;
        }

        system("cls");
    }
}