/*
# �ۼ��� : ������
# ��  �� : 13184394
# ������ : 140523(Fri)
# ��  �� : slide game_Project 1
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

//��, ���� ���� ��Ÿ�� ���� ����
typedef int BOOL;

int piece[MAXP][MAXP];			// pieces		���� ����
int blank_i, blank_j;			// empty piece	�� ������ ��ġ
int size;						// board size   ������ ũ�� 

void init();					// initialize
void move(int key);				// slide a piece
int judge();					// judge the end of the game
void draw_piece(int i, int j);	// draw a piece
void gotoxy(int x, int y);		// move cursor


int main(void) //���� �Լ�
{
	BOOL isEndloop = 0;
	printf("enter a number (3 - 7): ");
	scanf("%d",&size);
	
	/*����ڷκ��� ũ�⸦ �Է¹޴´�.
	����(MINP: 3 - MAXP: 7)�� ����� 
	�ּ�ũ�� MINP: 3���� ����*/
	if(!(MINP<=size && size<=MAXP)) size=MINP;//�Էµ� ũ�Ⱑ 3���� �۰ų� 7���� ũ��, �ּ��� 3���� ���	

	printf("Press ESC to exit.\n");
	printf("Left(4, A), Right(6, D), Down(2, X), Up(8, W)\n");


	// initilize the game
	init();


	// play
	while(!isEndloop) {
		int i,j;
		/* 
			judge()�Լ��� 1�� ������ ������ 
			����ڷκ��� Ű�� �Է¹޾�(_getch())
			���� ������ �����̸鼭 ���� ����
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
	//���� ���� ������ �´ٸ� 1�� ��ȯ, �׷��� �ʴٸ� 0�� ��ȯ
	int i,j,cnt=1; //���ڴ� 1���� ����
	BOOL NOTarranged=0;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			//������ ���� ������ ���ĵ��� �ʾҴٰ� ����
			if(piece[i][j]!=cnt) NOTarranged=1; 
			if((cnt+1)!=(size*size)) cnt++; //������ ���ڰ� ��ġ���� �ʴ´ٸ� ���ؾ� �� �� ����.
			else cnt=0; //���� ������ ī��(���� �ϴ�)�� ������ 0�� ��ġ�ؾ� �Ѵ�.
		}
	}
	if(NOTarranged) return 0;
	else return 1;
}


// slide a piece
void move(int key)
{
	// �����¿� key�� ���� 
	// �������� ���� ������ ��ġ�� �ٲ۴�
	int temp;
	
	switch(key)
	{
	case KEY_4:		// left
	case KEY_A:
		if((blank_j+1)!=size) { //������ ���� ���� �ʾ�����
			temp=piece[blank_i][blank_j]; //blank�� ������ ���ڸ� �ٲ��ش�.
			piece[blank_i][blank_j]=piece[blank_i][blank_j+1];
			piece[blank_i][blank_j+1]=temp;

			blank_j++; //���ο� blank ��ġ ����
		}
		break;
	case KEY_6:		// right
	case KEY_D:
		if((blank_j-1)!=-1) { //���� ���� ���� �ʾ�����
			temp=piece[blank_i][blank_j]; //blank�� ���� ���ڸ� �ٲ��ش�.
			piece[blank_i][blank_j]=piece[blank_i][blank_j-1];
			piece[blank_i][blank_j-1]=temp;

			blank_j--; //���ο� blank ��ġ ����
		}
		break;
	case KEY_2:		// down
	case KEY_X:
		if((blank_i-1)!=-1) { //���� ���� ���� �ʾ�����
			temp=piece[blank_i][blank_j]; //blank�� ������ ���ڸ� �ٲ��ش�.
			piece[blank_i][blank_j]=piece[blank_i-1][blank_j];
			piece[blank_i-1][blank_j]=temp;

			blank_i--; //���ο� blank ��ġ ����
		}
		break;
	case KEY_8:		// up
	case KEY_W:
		if((blank_i+1)!=size) { //������ ���� ���� �ʾ�����
			temp=piece[blank_i][blank_j]; //blank�� ������ ���ڸ� �ٲ��ش�.
			piece[blank_i][blank_j]=piece[blank_i+1][blank_j];
			piece[blank_i+1][blank_j]=temp;

			blank_i++; //���ο� blank ��ġ ����
		}
		break;
	case KEY_ESC:	// ESC
		gotoxy(0, size*3+1 + OFFSET); //size�� ��������. ���� ����.
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
	//BOOL duplicated=0; //���� ���� ���� �� �ߺ� �Ǻ�
	
	srand(time(NULL)); //���� �ʱ�ȭ
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

	//2���迭 piece�� �ʱ�ȭ, �������� ��ġ�� blank_i, blank_j�� ��Ÿ����.

	//���� ���� �迭�� ���� ���� ������� �ʰ�, ���� Ʋ �������� ���´�.
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


// draw a piece - 0�� ���ԵǴ� ī�� ������ΰ� 0�� ���� ���ڷ� ó��, ����ó�� ���̰�.
void draw_piece(int i, int j)
{
	//���� ������ �׸���
	//�־��� Ʋ�� ����ϸ� �� ī�� �� 3�྿ ������
	//�־��� Ʋ�� ����ϸ� 0���� 6�� �������� ����
	gotoxy(j*6,i*3+6); 
	piece[i][j]?printf("������"):printf("      ");
	gotoxy(j*6,i*3+7);
	//0�̸� ������ ���, �׷��� ������ ���ڿ� ī�� ���� ���� ���
	piece[i][j]?printf("��%2d��",piece[i][j]):printf("      ");
	gotoxy(j*6,i*3+8);
	piece[i][j]?printf("������"):printf("      ");
}


// move cursor to (x,y)
// upper left corner is (0,0)
void gotoxy(int x, int y)
{
	COORD Pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}