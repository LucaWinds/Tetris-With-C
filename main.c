
/*
2022학년도 1학기 2차 수행평가 개인 프로젝트
GSA 1403 김성현
*/


/*
테트리스란?
네 개의 사각형으로 이루어진 '테트로미노'는 무작위로 나타나 바닥과 블록 위에 떨어진다.
이 오락의 목표는 이 '테트로미노'를 움직이고 90도씩 회전하여, 수평선을 빈틈 없이 채우는 것이다.
이러한 수평선이 만들어질 때 이 선은 없어지며 그 위의 블록이 아래로 떨어지는데 테트리스 게임이 진행될수록
'테트로미노'는 더 빨리 떨어지며 게임을 즐기는 사람이 블록을 꼭대기까지 가득 메워,
'테트로미노'가 더 들어갈 공간이 없게 되면 게임이 끝나게 된다.
대다수의 테트리스의 점수 방식은 더 어려운 줄을 없앨수록 점수를 더 높이는 것이다.
(위키백과)

I, J, L, O, S, T, Z
7개의 테트로미노가 존재합니다.
*/


/*
이 게임의 특징|
현재 존재하는 가장 전형적인 테트리스 규칙을 대부분 따르며, 구현되지 않은 룰들이 있습니다.
1. 킥
2. T스핀 등의 특수 기술
3. 백투백

system("cls")를 활용한 콘솔창 구현이기에 컴퓨터 사양에 따라 깜빡이는 정도가 심할 수 있습니다.
코드 다 만들고 깔끔한 모션을 구현하는 법을 찾아서..
2학기 프로젝트때는 조금 더 깔끔한 콘솔창 구현을 해볼까 합니다.
*/


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>      //키보드 입력을 받기 위한 헤더파일
#include<windows.h>      //작업 대기(Sleep 함수)를 위한 헤더파일
#include<time.h>
#include <stdbool.h> //boolean 형식 사용
#include<MMSystem.h> //소리 출력
#pragma comment(lib,"Winmm.lib") //API 사운드 출력

void gotoxy(int x, int y);
/*
gotoxy : 콘솔창에서 원하는 부분에 출력할 수 있도록 하는 함수로, 콘솔게임 개발에 필수적으로 사용된다.
관리도 쉽고 다른 부분을 건들지 않고 거기에 딱 커서를 위치시킬수 있어서 매우 편리!
*/

void play_tetr();
void start_tetr(); //게임 시작 시 처음 보이는 곳
void helper1_tetr(); //도움말 정리
void helper2_tetr();
int game_tetr(); //게임 컨트롤 함수
void Init_tetr(); // 게임 기본 세팅 함수
void RandomBlock_tetr(); //다음 블럭 랜덤으로 뽑고 원래 다음 블럭이었던 블럭을 지금 블럭으로 바꾸는 함수
bool Crashchecker_tetr(int x, int y); //떨어질 때 부딫혔는지 체크
bool RotateCrashChecker_tetr(int x, int y, int BlockRotation); //회전하면서 부딫혔는지 체크
void FallingBlock_tetr(); //블럭 떨어뜨리는 함수
void BlockToGround_tetr(); //블럭이 땅에 닿았을 때 일정시간 이후 고정되게 하는 함수
void RemoveLine_tetr(); //한 줄을 모두 채웠을 때 사라지게 하는 함수
void DrawMap_tetr(); //게임판을 그리는 함수
void DrawBlock_tetr(); //블럭을 그리는 함수
void InputKey_tetr(); //키 입력받는 함수
void SpeedUp_tetr(); //레벨과 속도를 올리는 함수
void GameFinished_tetr(); //게임이 끝났을 때 일어나는 일들
void BlockMoveCnt_tetr(); //블럭이 움직이는 횟수 카운트해서 50회 이상이면 강제 하드드롭
void LineCrash_tetr(); //부서진 라인 개수 체크해서 콤보 계산


clock_t startDropT, endT, startGroundT; // 시간 체크
/*
이 함수는 Sleep 함수와는 다르게 프로그램 실행에 영향을 주지 않는다.
sleep 함수는 sleep 되는 동안 프로그램이 완전 정지하는데, 이 변수는 프로그램과 별개로 타이머 역할을 하여
일정한 시간마다 어떠한 행동 (여기서는 떨어지는 시간과 땅에 닿은 시간, 땅에 닿은 후 멈출때까지 시간을 재었다)
을 할 수 있도록 만들어진 함수.
*/
int x = 8, y = 0; // 초기 블럭 위치


int main()
{
    play_tetr();
}

int x_tetr = 8, y_tetr = 0; // 초기 블럭 위치
//변수 선언
int blockForm_tetr; //배열에 들어가는 블럭 모양
int nextBlockForm_tetr; //다음 블럭 모양
int holdBlockForm_tetr; //홀드중인 블럭 모양
int blockRotation_tetr = 0; //블럭 회전 모양 -> 배열에 들어감
int key_tetr; //입력받은 키 값
int score_tetr = 0; //점수
int droppingSpeed_tetr = 800; //떨어지는 속도 (정확히는 한칸 떨어지는데 걸리는 시간) : 레벨 증가에 따라 점점 작아진다. 
int level_tetr = 1; //레벨
int cntBlockFall_tetr = 0; //블럭 떨어뜨린 횟수 : 레벨 증가 척도
int cntBlockFallForUser_tetr = 0;
int cntLineCrashed_tetr = 0; //부서진 라인 개수
int finishFactor_tetr = 0; //게임 끝내는 인자
int holdingFactor_tetr = 0; //블럭을 홀드하고 다시 홀드하지 못하도록 정의한 인자
int restartFactor_tetr; //재시작을 하기 위해 입력받는 인자
int cntMove_tetr = 0; //움직인 횟수 카운트 -> 50이 넘으면 자동으로 떨어진다. (무한대로 움직여서 게임 못끝낼 수도 있으니까)
int cntLineCombo_tetr = 0; //한번에 여려줄 없애는거 카운트
int CHECK_tetr = 0; //많이 특이한 변수
/*
CHECK를 게임 실행 반복문이 한바퀴 돌때마다 1씩 늘린다. (반복문에는 시간 제어 함수가 없기에 엄청난 속도로 늘어난다)
이 CHECK 값이 10이 넘어가게 되면 CHECK를 0으로 되돌리고, 그동안 사라진 줄의 개수를 카운트하여 콤보수를 계산하는 매커니즘.
한번에 줄이 없어지는걸 카운트할 적당한 방법을 찾지 못해서 이러한 이상한 메커니즘 사용....
*/


int singleLine_tetr = 0, doubleLine_tetr = 0, tripleLine_tetr = 0, tetrisLine_tetr = 0; //한번에 없앤 줄 수를 UI에 띄우기 위한 변수


int block_tetr[7][4][4][4] = { // 블럭 형태 : 4차원 배열 선언 : (모양)(회전)(x좌표)(y좌표)
   { // ㅗ모양 블럭
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
   {    // 계단 블럭
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
   {   // 계단 블럭 반대
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
   {   // 1자형 블럭
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
   {   // L자형 블럭
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
   {   // L자형 블럭 반대
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
   {   // 네모 블럭
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


// 1: 벽 2: 떨어지는 블럭 3: 떨어진 블럭
int space_tetr[25 + 1][10 + 2];

/*
gotoxy : 콘솔창에서 원하는 부분에 출력할 수 있도록 하는 함수로, 콘솔게임 개발에 필수적으로 사용된다.
관리도 쉽고 다른 부분을 건들지 않고 거기에 딱 커서를 위치시킬수 있어서 매우 편리!
*/



void play_tetr() //준비 화면
{
    system("mode con cols=88 lines=22"); // 처음 콘솔창의 크기 정의
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
    char startFactor; //시작할 때 입력받는 인자로, 게임을 바로 시작할지 도움말을 볼지 체크
    system("cls");
    printf("※ 콘솔창의 글꼴을 consolas로 설정하고 게임을 입장해주세요\n");
    printf("※ 다른 글꼴을 사용할 시 게임 화면이 깨질 수 있습니다\n\n");

    printf("※ 더 좋은 게임 플레이를 위해 음악 설정을 해주세요\n");
    printf("※ 자세한 내용은 h를 입력해 알아봐주세요\n\n");

    printf("※ 콘솔 창의 크기를 더 작게 변경하지 말아주세요\n");
    printf("※ 게임 시작을 원하면 y를 입력해주세요\n\n");

    printf("※ 게임 플레이 방법 및 기본 게임 세팅을 알고 싶으시면 h를 입력해주세요\n");

A: //여기로 다시 돌아올거야
    startFactor = _getch();

    if (startFactor == 'y') start_tetr(); //게임 시작
    else if (startFactor == 'h') helper1_tetr(); //도움말
    else goto A; //이상한거 누르면 다시 입력 시키기

}



void helper1_tetr() //도움말 1페이지
{
    char startFactor;

    system("cls"); //전부 없애고 도움말을 보여주자.
    printf("※ 콘솔창의 윗 부분을 우클릭합니다.\n");
    printf("※ 기본값 에 들어가 글꼴 을 선택합니다.\n");
    printf("※ 글꼴을 consolas로 선택합니다.\n\n\n");
    Sleep(1000);

    printf("※ 코드 521열을 찾아봅니다.\n");
    printf("※ 다운받은 wav 파일의 경로를 414열에 있는 곳에서 복사해줍니다.\n");
    printf("※ \\를 \\\\ 로 모두 바꿔줍니다. \n\n");
    printf("예시 : D:\\\\광주과학고\\\\정보과학\\\\테트리스 A 브금.wav\n");
    Sleep(1000);

    printf("다음 페이지를 보기 위해, h를 입력해주세요.");

A:
    startFactor = _getch();

    if (startFactor == 'h') helper2_tetr();
    else goto A;
}

void helper2_tetr() //도움말 2페이지
{
    char startFactor2;

    system("cls"); //전부 없애고 도움말을 보여주자.
    printf("※ 테트리스는 간단한 퍼즐게임으로, 떨어지는 블럭을 쌓는 게임입니다.\n");
    printf("※ 블록을 쌓으면서 한 줄이 꽉 채워지면 그 줄은 사라집니다\n");
    printf("※ 블록이 맨 위까지 올라가지 않게 끝까지 버티면서 플레이하는 게임입니다.\n\n\n");
    Sleep(1000);

    printf("  △   : Rotate        SPACE : Hard Drop\n");
    Sleep(300);
    printf("◁  ▷ : Left / Right  C : Hold\n");
    Sleep(300);
    printf("  ▽   : Soft Drop     ESC  : Quit\n\n\n");
    Sleep(1000);

    printf("※ 하드 드랍은 즉시 블럭을 내리는 방법을, 소프트드랍은 한칸씩 블럭을 내리는 방법을 뜻합니다.\n");
    printf("※ 블럭은 전부 랜덤으로 정해지며 최대한 오래 버텨 가장 높은 점수를 기록해보세요! \n\n");
    Sleep(1000);

    printf("게임을 시작하기 위해, y를 입력해주세요.");

A:
    scanf("%c", &startFactor2);

    if (startFactor2 == 'y') start_tetr();
    else goto A;
}


void start_tetr() //게임 시작 화면
{
    system("mode con cols=88 lines=22"); // 처음 콘솔창의 크기 정의
    int gameStartFactor = 0;
    system("cls");
    printf("#                     ####### ####### ####### ######  ###  #####                       #\n#                        #    #          #    #     #  #  #     #                      #\n#                        #    #          #    #     #  #  #                            #\n#                        #    #####      #    ######   #   #####                       #\n#                        #    #          #    #   #    #        #                      #\n#                        #    #          #    #    #   #  #     #                      #\n#                        #    #######    #    #     # ###  #####                       #\n\n");
    printf("                               PRESS ANY BUTTON TO START                                \n");
    printf("                        2022학년도 1학기 2차 수행평가 개인프로젝트                         \n\n\n");
    printf("                            --- 게임 실행 중 오류 목록 ---                               \n");
    printf("                             가끔씩 홀드 기능이 고장남                                  \n");
    printf("                               가끔씩 블럭끼리 겹친다                                  \n");
    printf("                       일부 기기에서 restart가 작동하지 않는다                                  \n");
    printf("                                                                ");
    gameStartFactor = _getch();

    system("cls");
    Init_tetr(); //게임 시작 제어
    //로딩중...
    printf("\n\n\n\n                                      NOW LOADING...                                       \n\n\n\n\n      ");
    for (int i = 0; i < 24; i++) {
        printf("■ ");
        Sleep(50);
    }
    Sleep(200);
    system("cls");
    game_tetr(); //게임을 본격적으로 시작한다
}

void gotoxy(int x, int y) { //gotoxy 정의 : 원하는 위치에 커서 옮기기 : 용도는 출력문 위치 제어
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


int game_tetr() //게임 제어 함수
{
    system("mode con cols=44 lines=28");//콘솔창 크기를 테트리스 게임판 사이즈로
    int cntcntcntcnt;
    blockForm_tetr = rand() % 7; //처음 블럭 모양 정해주기
    for (int i = 3; i > 0; i--) { //게임 준비
        DrawMap_tetr(); //게임판 그리고
        gotoxy(11, 11); //3, 2, 1 카운트
        printf("%d", i);
        Sleep(1000);
        system("cls");
    }

    startDropT = clock(); //떨어지기 시작한다!
    //sndPlaySoundA("D:\\광주과학고\\정보과학\\테트리스 A 브금.wav", SND_ASYNC | SND_LOOP);

    /*
    테트리스 소리 나게 하는 코드
    이 코드 짠 사람은 음악을 들으면서 코드를 짜기 때문에 음악 겹치는게 싫어서 주석처리가 되어있습니다.
    사용하기 위해서는 주석을 해제 ( //를 지우기 ) 하고 파일 저장 위치를 큰따옴표 사이에 써주세요.
    단 \를 \\로 모두 바꾸어 써주셔야 합니다.
    예시 : D:\\광주과학고\\정보과학\\테트리스 A 브금.wav

    없어도 게임이 실행되지 않는다거나 하지 않으니까 음악파일을 다운받지 않으셨다면 그냥 플레이해도 무관합니다!
    */

    /*
    게임 실행을 위한 반복문이고, 게임 실행 시 상시 작동되는 함수들을 계속 실행해준다. 그 함수 목록은
    맵 그리기
    블럭 그리기
    블럭이 땅에 닿았는가?
    줄 지우기
    키 입력받기
    속도 올리기
    게임이 끝났는가?
    블럭이 50회 이상 움직여졌는가?

    이다. CHECK애 대해서는 변수 선언 파트에 자세히 설명되어 있다.

    */
    while (true) { //게임 실행 : 게임 실행시 상시 작동되는 함수들을 계속 실행해준다.
        DrawMap_tetr();
        DrawBlock_tetr();
        FallingBlock_tetr();
        BlockToGround_tetr();
        RemoveLine_tetr();
        InputKey_tetr();
        SpeedUp_tetr();
        BlockMoveCnt_tetr();

        //UI 재정리
        gotoxy(24, 1);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (block_tetr[nextBlockForm_tetr][1][i][j] == 1) {
                    gotoxy(30 + j * 2, 1 + i);
                    printf("□");
                }
            }
        }
        if (holdBlockForm_tetr != 0) {
            gotoxy(24, 8);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (block_tetr[holdBlockForm_tetr][1][i][j] == 1) {
                        gotoxy(30 + j * 2, 8 + i);
                        printf("□");
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
        //CHECK의 용도에 대해서는 변수 선언 파트에 자세히 설명되어 있습니다.
        for (int i = 1; i <= 10; i++) {
            if (space_tetr[1][i] == 3) {
                GameFinished_tetr();
                goto A;
            }
        }
    }
A:

    //게임이 끝나면 무한반복문을 탈출한다

    return 0;
}


void Init_tetr() { //커서 숨기고 시드 재설정 등등
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    srand(time(NULL));
}

void RandomBlock_tetr() { //다음 블럭을 랜덤으로 뽑기
    blockForm_tetr = nextBlockForm_tetr;
    nextBlockForm_tetr = rand() % 7;
}

void SpeedUp_tetr() { //12개 떨어뜨릴 때마다 레벨과 속도 증가
    if (cntBlockFall_tetr % 12 == 11) {
        droppingSpeed_tetr /= 1.2;
        level_tetr++;
        cntBlockFall_tetr++;
    }
}

/*
라인이 부서졌을 때 부서진 개수를 체크하여 게임판 밑에
몇개를 부쉈는지 다음과 같이 보여준다.

한 개 : SINGLE
두 개 : DOUBLE
세 개 : TRIPLE
네 개 : TETRIS
이때 TETRIS에 성공하면 옆에 별까지 뜨는 특수 효과가 있다.

이후 각각에 콤보에 따라 추가 점수를 부여한다.
*/
void LineCrash_tetr() { //라인이 몇 개 부서졌는지 체크해서, 해당 점수를 올리고 부순 라인 수를 카운트한다.
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
    else if (cntLineCombo_tetr == 4) { //출력문이 여러게 있는 이유는 반짝반짝 효과를 넣어보고 싶었기 때문이다.
        gotoxy(7, 26);
        printf("★TETRIS★");
        Sleep(150);
        gotoxy(7, 26);
        printf("☆TETRIS☆");
        Sleep(150);
        gotoxy(7, 26);
        printf("★TETRIS★");
        tetrisLine_tetr++;

        cntLineCombo_tetr = 0;
    }

}

void BlockMoveCnt_tetr() { //블럭이 움직이는 횟수를 카운트할 때, 50이 넘어가면 강제로 하드드랍시킨다.
    if (cntMove_tetr > 50) {
        while (Crashchecker_tetr(x_tetr, y_tetr + 1) == false) { //하드드랍 코드랑 완벽 동일 (점수 추가로 주는거 빼고)
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
블럭이 한칸 더 내려갔을 때, 벽이거나 블럭이 있는 곳이 없는지 확인해본다.
그렇다면, true, 아니라면, false를 return한다.
현재 블럭의 좌표보다 한칸 낮은 곳의 게임판 배열을 불러와서 그것을 블럭의 배열과 비교해보는 방법이다.
*/
bool Crashchecker_tetr(int x, int y) { //떨어지면서 꽝
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block_tetr[blockForm_tetr][blockRotation_tetr][i][j] == 1) {
                int t = space_tetr[i + y][j + x / 2];
                if (t == 1 || t == 2 || t == 3) { // 벽일 때, 블럭일 때
                    return true;
                }
            }
        }
    }
    return false;
}

/*
위와 거의 동일하다.
블럭이 회전되었을때, 벽이거나 블럭이 있는 곳이 없는지 확인해본다.
그렇다면, true, 아니라면, false를 return한다.
현재 블럭의 회전수보다 1 더 높은 블럭의 배열을 불러와 게임판과 비교해보는 방법이다.

* 킥은 구현되어있지 않다.
(킥이란 : 블럭이 회전되었을 때 옆에 닿게 된다면 자동으로 블럭의 위치를 한 칸 옆으로 이동시켜주고 블럭을 회전시켜주는 시스템)
*/
bool RotateCrashChecker_tetr(int x, int y, int z) { //돌면서 꽝
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block_tetr[blockForm_tetr][z + 1][i][j] == 1) {
                int t = space_tetr[i + y][j + x / 2];
                if (t == 1 || t == 2 || t == 3) { // 벽일 때, 블럭일 때
                    return true;
                }
            }
        }
    }
    return false;
}

void FallingBlock_tetr() { //부딫히기 전까지 일정 시간마다 떨어지게 하기
    endT = clock();
    if ((float)(endT - startDropT) >= droppingSpeed_tetr) {
        //떨어뜨리기 시작한 시간과 이 함수가 발동된 시간을 비교해서
        //일정 시간이 넘으면 한칸 내리고 함수를 초기화시켜주는 방법이다.
        if (Crashchecker_tetr(x_tetr, y_tetr + 1) == true) return;
        y_tetr++;
        startDropT = clock();
        startGroundT = clock();
        system("cls");
    }
}

void BlockToGround_tetr() { //바닥에 닿으면 일정시간 후 고정
    if (Crashchecker_tetr(x_tetr, y_tetr + 1) == true) {
        if ((float)(endT - startGroundT) > 1000) {
            // 현재 블록 저장 : 게임판에 블록의 모양을 저장한다.
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (block_tetr[blockForm_tetr][blockRotation_tetr][i][j] == 1) {
                        space_tetr[i + y_tetr][j + x_tetr / 2] = 3;
                    }
                }
            }
            score_tetr += 50; //점수를 추가하고, 블럭 떨어진 횟수를 추가하고 등등..
            cntBlockFall_tetr++;
            holdingFactor_tetr = 0;
            x_tetr = 8; //블럭의 좌표는 다시 처음으로 간다.
            y_tetr = 0;
            RandomBlock_tetr();
        }
    }
}

void RemoveLine_tetr() {
    for (int i = 25; i >= 0; i--) { // 벽라인 제외한 값
        int cnt = 0;
        for (int j = 1; j < 11; j++) { //각각의 높이에 대해서 블럭이 있는지 없는지 체크해본다.
            if (space_tetr[i][j] == 3) {
                cnt++;
            }
        }
        if (cnt >= 10) { // 벽돌이 다 차있다면
            cntLineCrashed_tetr++; //부순 횟수 미리 늘려놓고
            cntLineCombo_tetr++; //몇개 부쉈는지 확인하게 이것도 늘려놓고
            for (int j = 0; i - j >= 0; j++) {
                for (int x = 1; x < 11; x++) {
                    if (i - j - 1 >= 0)
                        space_tetr[i - j][x] = space_tetr[i - j - 1][x]; //위에 있던 블럭들을 아래로 내린다.
                    else      // 천장이면 0저장
                        space_tetr[i - j][x] = 0; //당연하게, 천장 위에는 배열이 없다. 그냥 0을 저장한다.
                }
            }
            score_tetr += 1000; //한 줄 지우면 기본 1000점 부여
        }
    }
}

/*
게임판에 저장된 배열을 그대로 출력해준 후, 사용자 인터페이스도 꾸며주게 됨으로서
여러가지 자신의 현재 플레이 상황을 보여줄 수 있다. (점수, 레벨 등)
*/
void DrawMap_tetr() { //게임판 그리기
    gotoxy(0, 0);
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 12; j++) {
            if (space_tetr[i][j] == 1) {
                gotoxy(j * 2, i);
                printf("▩");
            }
            else if (space_tetr[i][j] == 2) {
                gotoxy(j * 2, i);
                printf("□");
            }
            else if (space_tetr[i][j] == 3) {
                gotoxy(j * 2, i);
                printf("■");
            }
        }
    }


    //여기서 엄청나게 많이 쓰이는 gotoxy

    gotoxy(24, 0);
    printf("▩▩ NEXT BLOCK ▩▩");

    gotoxy(24, 6);
    printf("▩▩ HOLD BLOCK ▩▩");

    /*
    사용자 인터페이스 보여주기
    레벨, 점수, 부순 줄 개수, 프로젝트 이름
    */
    gotoxy(24, 12);
    printf("▩▩▩▩▩▩▩▩▩▩");
    gotoxy(24, 13);
    printf(" level : %d", level_tetr);
    gotoxy(24, 14);
    printf(" score : %d ", score_tetr);
    gotoxy(24, 15);
    printf("▩▩▩▩▩▩▩▩▩▩");
    gotoxy(24, 17);
    printf(" single : %d", singleLine_tetr);
    gotoxy(24, 19);
    printf(" double : %d ", doubleLine_tetr);
    gotoxy(24, 21);
    printf(" triple : %d", tripleLine_tetr);
    gotoxy(24, 23);
    printf(" tetris : %d ", tetrisLine_tetr);
    gotoxy(24, 25);
    printf("▩▩▩▩▩▩▩▩▩▩");
    gotoxy(22, 26);
    printf("▩");
    gotoxy(0, 26);
    printf("▩");
    gotoxy(24, 26);
    printf("   2022 GSA 정보");
    gotoxy(0, 27);
    printf("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
}

/*
블럭을 그려주는 함수로, 게임판에 떨어질 때마다 원래 블럭을 지우고 현재 위치 다시 블럭을 넣고 하면 컴퓨터와 프로그래머의 머리가 맛탱이가 가기 때문에
블럭은 따로 게임판에 저장해두지 말고 그냥 따로 출력하는 방식을 택함으로서
렉도 줄이고 코드 길이도 줄일 수 있었다!
당연히 출력할 때에는 gotoxy를 이용해서 출력한다.
*/
void DrawBlock_tetr() {//블럭을 그리기
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block_tetr[blockForm_tetr][blockRotation_tetr][i][j] == 1) {
                gotoxy(x_tetr + j * 2, y_tetr + i);
                printf("□");
            }
        }
    }
}

/*
게임 함수에서 게임이 종료됨을 알리고 게임 종료함수로 이동하는데, 이동되면 게임 오버를 띄우고,
게임을 재시작할것인지, 종료할 것인지 묻는다.
*/
void GameFinished_tetr() { //게임 종료 함수
    system("cls");
    finishFactor_tetr++;

    DrawMap_tetr();

    gotoxy(3, 26); // 원하는 위치로 이동해서 재시작 방법을 보여줍니다.
    printf("Press R to restart");
A:
    restartFactor_tetr = _getch();

    if (restartFactor_tetr == 'r') { //재시작, 초기화
        system("cls");
        score_tetr = 0; //모
        droppingSpeed_tetr = 800; //든
        level_tetr = 1; //변
        cntBlockFall_tetr = 0; //수
        cntLineCrashed_tetr = 0; //가
        cntBlockFallForUser_tetr = 0; //초
        finishFactor_tetr = 0; //기
        holdingFactor_tetr = 0; //화
        cntMove_tetr = 0; //된
        holdBlockForm_tetr = 0;
        singleLine_tetr = 0, doubleLine_tetr = 0, tripleLine_tetr = 0, tetrisLine_tetr = 0; //다
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
conio 헤더파일을 이용한 키 입력받는 함수이다.
우리가 원래 사용하는 scanf같은 함수들은 게임 실행에 치명적인 단점이 있는데,
바로 입력을 받을 때에는 프로그램 자체가 멈춰버린다는 것이다.
그러한 단점을 해결하기 위한 것이 이 함수인데, 이 함수는 프로그램 실행과 동시에 키보드에 입력이 되었는지를 판별해주어,
( _kbhit()은 boolean형을 반환하여, 키보드에 무언가 입력이 되면 true를 반환한다. )
입력이 되었을 때에 그 입력된 키가 무엇인지 _getch();라는 함수로 알아보고
해당하는 키에 대한 행동들을 switch case 문으로 입력해주었다.
*/
void InputKey_tetr() { //conio 헤더파일을 이용한 키 입력받는 함수
    int temp = 0;
    if (_kbhit()) {
        key_tetr = _getch();
        switch (key_tetr) {
        case 32: // space
           /*
           space를 누르면 하드드롭이 되는데, 부딫힐 때까지 y값을 강제로 높인다.
           이후 점수를 증가시킨다. 그리고 모든 블럭 떨어지는데 관련된 변수들은 초기화시킨다.
           블럭 떨어진 횟수를 카운트해주고, 블럭을 랜덤으로 뽑이주는 함수로 이동시킨다.
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
            left, right는 각각 블럭의 좌표를 2칸씩 밀고 (2칸이라고 하는게 실제 게임판에서는 1칸으로 보인다)
            땅에 닿기 시작한 시간을 초기화시키고, 움직인 횟수를 1 늘린다.
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
            down 버튼을 눌르면 소프트 드랍이 된다.
            down 버튼을 눌르게 되면 누른 시간에 따라 떨어지도록 한다.
            부딫히기 전까지 y좌표를 증가시킨다.
            */
        case 80: // down
            if (Crashchecker_tetr(x_tetr, y_tetr + 1) == false) {
                y_tetr++;
                score_tetr = score_tetr + 10;
            }
            break;
            /*
            up 버튼을 누르면 블럭을 회전시킨다.
            회전시켰을 때 부딫히지 않는다면 회전수를 1 늘리고, 360도 돈거는 안돈거랑 같으니까
            회전수가 4를 넘으면 0으로 되돌려놓는다.
            */
        case 72: //up
            if (RotateCrashChecker_tetr(x_tetr, y_tetr, blockRotation_tetr) == false)
                blockRotation_tetr++;
            if (blockRotation_tetr >= 4) blockRotation_tetr = 0;
            startGroundT = clock();
            break;
            /*
            esc를 누르면 게임이 강제종료된다.
            콘솔창의 크기를 적당하게 바꾸어주고 게임 화면을 비워 준 후,
            프로그램을 강제 종료시킨다.
            */
        case 27: //esc
            system("cls");
            exit(0);
            break;
            /*
            c를 누르면 홀드가 된다.
            (홀드란, 블럭을 원하는 동안만큼 잡고 있어 필요할 때 쓸수 있도록 하는 기술로,
            한 턴에 한 번만 사용 가능하다.)
            그래서 holdingFactor를 이용하여 내가 이번 턴에 홀드를 했는지 안했는지 확인하고, 홀드를 할 수 있는 상황일 때

            1. 홀드한 블럭이 있을 때
               홀드한 블럭과 내 현재 블럭을 바꾼다.
            2. 홀드한 블럭이 없을 때
               내 현재 블럭을 홀드 블럭으로 바꾸고, 나는 다음 블럭을 가져온다.

            홀드에 성공하면 holdingFactor가 1 올라 더이상 홀드를 할 수 없게 되고, 블럭을 떨어뜨리면 다시 0이 되어
            hold를 사용할 수 있게 된다.
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