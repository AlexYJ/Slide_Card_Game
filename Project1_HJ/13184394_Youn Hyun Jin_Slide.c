/*
# 작성자 : 윤현진
# 학  번 : 13184394
# 제출일 : 140523(Fri)
# 내  용 : slide game_Project 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

#define MINP		3
#define MAXP		7
#define OFFSET		5
#define KEY_ESC		0x1B
#define KEY_8		'8'
#define KEY_2		'2'
#define KEY_4		'4'
#define KEY_6		'6'
#define KEY_W		'w'
#define KEY_X		'x'
#define KEY_A		'a'
#define KEY_D		'd'

//참, 거짓 값을 나타낼 문자 선언
typedef int BOOL;

int piece[MAXP][MAXP];			// pieces		퍼즐 조각
int blank_i, blank_j;			// empty piece	빈 조각의 위치
int size;						// board size   보드의 크기 

void init();					// initialize
void move(int key);				// slide a piece
int judge();					// judge the end of the game
void draw_piece(int i, int j);	// draw a piece
void gotoxy(int x, int y);		// move cursor


int main(void) //메인 함수
{
	BOOL isEndloop = 0;
	printf("enter a number (3 - 7): ");
	scanf("%d",&size);
	
	/*사용자로부터 크기를 입력받는다.
	범위(MINP: 3 - MAXP: 7)을 벗어나면 
	최소크기 MINP: 3으로 고정*/
	if(!(MINP<=size && size<=MAXP)) size=MINP;//입력된 크기가 3보다 작거나 7보다 크면, 최소인 3으로 출력	

	printf("Press ESC to exit.\n");
	printf("Left(4, A), Right(6, D), Down(2, X), Up(8, W)\n");


	// initilize the game
	init();


	// play
	while(!isEndloop) {
		int i,j;
		/* 
			judge()함수가 1을 리턴할 때까지 
			사용자로부터 키를 입력받아(_getch())
			퍼즐 조각을 움직이면서 게임 진행
		*/
		move(_getch());
		isEndloop = judge();
		
		//draw each puzzle
		for(i=0;i<size;i++) {
			for(j=0;j<size;j++) {
				draw_piece(i,j);
			}
		}
	
	}
	
	// exit the game
	gotoxy(0, size*3+1 + OFFSET);
	printf("Done!\n\n");

	return 0;
}


// judge the end of the game
int judge()
{
	//퍼즐 조각 순서가 맞다면 1을 반환, 그렇지 않다면 0을 반환
	int i,j,cnt=1; //숫자는 1부터 시작
	BOOL NOTarranged=0;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			//순서가 맞지 않으면 정렬되지 않았다고 판정
			if(piece[i][j]!=cnt) NOTarranged=1; 
			if((cnt+1)!=(size*size)) cnt++; //마지막 숫자가 일치하지 않는다면 비교해야 할 수 증가.
			else cnt=0; //판의 마지막 카드(오른 하단)은 무조건 0이 위치해야 한다.
		}
	}
	if(NOTarranged) return 0;
	else return 1;
}


// slide a piece
void move(int key)
{
	// 상하좌우 key에 따라 
	// 빈조각과 숫자 조각의 위치를 바꾼다
	int temp;
	
	switch(key)
	{
	case KEY_4:		// left
	case KEY_A:
		if((blank_j+1)!=size) { //오른쪽 끝에 닿지 않았으면
			temp=piece[blank_i][blank_j]; //blank와 오른쪽 숫자를 바꿔준다.
			piece[blank_i][blank_j]=piece[blank_i][blank_j+1];
			piece[blank_i][blank_j+1]=temp;

			blank_j++; //새로운 blank 위치 지정
		}
		break;
	case KEY_6:		// right
	case KEY_D:
		if((blank_j-1)!=-1) { //왼쪽 끝에 닿지 않았으면
			temp=piece[blank_i][blank_j]; //blank와 왼쪽 숫자를 바꿔준다.
			piece[blank_i][blank_j]=piece[blank_i][blank_j-1];
			piece[blank_i][blank_j-1]=temp;

			blank_j--; //새로운 blank 위치 지정
		}
		break;
	case KEY_2:		// down
	case KEY_X:
		if((blank_i-1)!=-1) { //위쪽 끝에 닿지 않았으면
			temp=piece[blank_i][blank_j]; //blank와 오른쪽 숫자를 바꿔준다.
			piece[blank_i][blank_j]=piece[blank_i-1][blank_j];
			piece[blank_i-1][blank_j]=temp;

			blank_i--; //새로운 blank 위치 지정
		}
		break;
	case KEY_8:		// up
	case KEY_W:
		if((blank_i+1)!=size) { //오른쪽 끝에 닿지 않았으면
			temp=piece[blank_i][blank_j]; //blank와 오른쪽 숫자를 바꿔준다.
			piece[blank_i][blank_j]=piece[blank_i+1][blank_j];
			piece[blank_i+1][blank_j]=temp;

			blank_i++; //새로운 blank 위치 지정
		}
		break;
	case KEY_ESC:	// ESC
		gotoxy(0, size*3+1 + OFFSET); //size로 변경했음. 값은 동일.
		printf("Exit!\n\n");

		exit(0);
		break;
	}

}

// initialize
void init()
{
	int i,j,cnt=1;
	int randKey;
	//int arr_numlist[MAXP*MAXP];
	//BOOL duplicated=0; //랜덤 난수 생성 시 중복 판별
	
	srand(time(NULL)); //랜덤 초기화
	for(i=0;i<size;i++) {
		for(j=0;j<size;j++) {
			if((i+1)*(j+1) != (size*size)) {
				piece[i][j] = cnt++;
			} else {
				piece[i][j] = 0;
			}
		}
	}
	blank_i = size - 1;
	blank_j = size - 1;

	//2차배열 piece를 초기화, 빈조각의 위치는 blank_i, blank_j로 나타낸다.

	//랜덤 숫자 배열을 들어내서 섞고 집어넣지 않고, 퍼즐 틀 내에서만 섞는다.
	for(i=0;i<300;i++) {
		randKey = rand() % 4;
		switch(randKey) {
		case 0:
			randKey = KEY_2;
			break;
		case 1:
			randKey = KEY_4;
			break;
		case 2:
			randKey = KEY_6;
			break;
		case 3:
			randKey = KEY_8;
			break;
		}
		move(randKey);
	}
	// draw pieces  
	for(i=0;i<size;i++) {
		for(j=0;j<size;j++) {
			draw_piece(i,j);
		}
	}
}


// draw a piece - 0이 포함되는 카드 가드라인과 0을 공백 문자로 처리, 공백처럼 보이게.
void draw_piece(int i, int j)
{
	//퍼즐 조각을 그린다
	//주어진 틀을 사용하면 한 카드 당 3행씩 차지함
	//주어진 틀을 사용하면 0부터 6열 간격으로 배당됨
	gotoxy(j*6,i*3+6); 
	piece[i][j]?printf("┌─┐"):printf("      ");
	gotoxy(j*6,i*3+7);
	//0이면 공백을 출력, 그렇지 않으면 숫자와 카드 양쪽 변을 출력
	piece[i][j]?printf("│%2d│",piece[i][j]):printf("      ");
	gotoxy(j*6,i*3+8);
	piece[i][j]?printf("└─┘"):printf("      ");
}


// move cursor to (x,y)
// upper left corner is (0,0)
void gotoxy(int x, int y)
{
	COORD Pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}