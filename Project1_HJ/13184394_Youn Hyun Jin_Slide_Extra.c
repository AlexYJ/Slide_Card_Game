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

//�ܼ� �۾� �� ����
#define COL						GetStdHandle(STD_OUTPUT_HANDLE)             // �ܼ�â�� ���� �޾ƿ�
#define SETTEXTCOLOR_ORIGINAL   SetConsoleTextAttribute(COL, 0x0007)        // �⺻ �ܼ� ����
#define SETTEXTCOLOR_RED        SetConsoleTextAttribute(COL, 0x000c)        // ������
#define SETTEXTCOLOR_BLUE		SetConsoleTextAttribute(COL, 0x0009)        // �Ķ���


//��, ���� ���� ��Ÿ�� ���� ����
typedef int BOOL;

int piece[MAXP][MAXP];			// pieces		���� ����
int blank_i, blank_j;			// empty piece	�� ������ ��ġ
int size;						// board size   ������ ũ�� 
int move_cnt;					// count Ƚ��

void print_comp();				// print a computer
void delay(unsigned int n);		// ms timer
void draw_Count();	    // draw count number

void init();					// initialize
void move(int key);				// slide a piece
int judge();					// judge the end of the game
void draw_piece(int i, int j);	// draw a piece
void gotoxy(int x, int y);		// move cursor
void Whattime(struct tm** pToday); //print present time


int main(void) //���� �Լ�
{
	BOOL isEndloop = 0;
	struct tm* today; //��¥ ��¿� ����ü ����
	print_comp(); //��ǻ�� �׸� �Լ� ȣ��

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
		
		draw_Count(); //ī��Ʈ �Լ� ȣ��, ���
	
//�ð� ���. ���������� �������� ���� ��, ��, ��, ��, ��, �ʰ� ��µ�. ���� ���ϰ� press ESC to exit�� ��µ� �� �� �ڸ��� ����.
		Whattime(&today);
		printf("%04d-%02d-%02d %02d:%02d:%02d\n",
			today->tm_year + 1900,   // tm_year�� 1900�� ���ؾ� ���� ������ ��
            today->tm_mon + 1, // tm_mon�� 1���� 0���� �Է¹޾� 1�� ������� ���� ǥ���� �� ����
            today->tm_mday,
            today->tm_hour,
            today->tm_min,
            today->tm_sec);


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
			move_cnt++; //�̵�Ƚ�� ��������
		}
		break;
	case KEY_6:		// right
	case KEY_D:
		if((blank_j-1)!=-1) { //���� ���� ���� �ʾ�����
			temp=piece[blank_i][blank_j]; //blank�� ���� ���ڸ� �ٲ��ش�.
			piece[blank_i][blank_j]=piece[blank_i][blank_j-1];
			piece[blank_i][blank_j-1]=temp;

			blank_j--; //���ο� blank ��ġ ����
			move_cnt++; //�̵�Ƚ�� ��������
		}
		break;
	case KEY_2:		// down
	case KEY_X:
		if((blank_i-1)!=-1) { //���� ���� ���� �ʾ�����
			temp=piece[blank_i][blank_j]; //blank�� ������ ���ڸ� �ٲ��ش�.
			piece[blank_i][blank_j]=piece[blank_i-1][blank_j];
			piece[blank_i-1][blank_j]=temp;

			blank_i--; //���ο� blank ��ġ ����
			move_cnt++; //�̵�Ƚ�� ��������
		}
		break;
	case KEY_8:		// up
	case KEY_W:
		if((blank_i+1)!=size) { //������ ���� ���� �ʾ�����
			temp=piece[blank_i][blank_j]; //blank�� ������ ���ڸ� �ٲ��ش�.
			piece[blank_i][blank_j]=piece[blank_i+1][blank_j];
			piece[blank_i+1][blank_j]=temp;

			blank_i++; //���ο� blank ��ġ ����
			move_cnt++; //�̵�Ƚ�� ��������
		}
		break;
	case KEY_ESC:	// ESC
		gotoxy(0, size*3+1 + OFFSET); //size�� ��������. ���� ����.
		printf("Exit!\n\n");

		exit(0);
		break;
	}

}

void Whattime(struct tm** pToday) //����ð� ǥ���Լ� ����
{
    time_t ltime;
	time(&ltime);
    *pToday = localtime(&ltime);
}

//ASCII generator2�� �̿��Ͽ� �׸��� ��Ÿ ���ڷ� ������ �����Ѵ�.
void print_comp()
{
	//���ڿ� �迭 ����(29��)
	char* comp[29] = {  
                                                  
"  Please Wait a Second.......                                   ",
"            ,:i7r777r7r7rrii;vvL7v7v7uu            .,;YXSSFSFO. ",
"           .@BMMONPFF5FSEZMB@B@B@B@B@B@:      uO@B@M@BB8MMBB@B: ",
"           .B: . ..::ir7YSXZZOMBB@B@B@@r      B@BM::OMF1FXPEO@. ",
"           .@:.,::::ii7vuFqEOOMMBM@B@B@i      @BGv UMGPv1XNqOB. ",
"           .Bi,::i:iirvu2XN88MOBMBMBB@Br      B@5:.@B@FJ2qP0G@. ",
"           .@i::i:i;r7JukPGGOMMMBBBM@B@r      @Mu.YBZMS5XkNNMB. ",
"           .@7:iiri77YUkPEZOOMMMBBBBB@Bv      BM7.BNj@11SqPE8@  ",
"            @7irrr7vjuSXEGOOMMBMBMBMBB@v      @Eir@M@MF2XP00M@  ",
"           .BLr77vvJUFXEZOOMMBMBMBMBM@BL      BP,qBBBM55SqqqG@  ",
"            @j7vLYuUkkEZO8MMBMBMBMBMBB@7      @urB@MBMS5PkkXOB  ",
"           .B1vuYU2SX0GOOMMBM@MBMBMMM@B7      Bv1@MBBMFSPNNZM@  ",
"            @1uu21XqZZOOMMBBBM@MBMBMMB@7      BLBMBM@OXSqN00MB  ",
"           .BN1SFPqEGOMBB@B@@@B@MBMMM@Bv      O0BMMBBMSPPEqZO@  ",
"           .@B@B@B@B@B@MMOMOMOBB@B@B@B@J      MB@OMM@OqkNNEZM@  ",
"            .:ruSZM@B@B@B@BBO@B@B@B@B@B7      B@OOMMBMXPPEE8M@  ",
"                          rZO7 .::ii;rr       @BMOBB@MNPEEGM@@r,",
"                          E@@@:               @@MMOOMO02kOB@Xr. ",
"      FBMSXSFJL7i::1MMMOB@@@@B@@MBu          .@@BMMOBMOPMBML:.  ",
"    7@B@B@B@B@B@B@B@MOEBGZFkPFPG8@krii::., ,  M@B@B@B@B@Mk7:.   ",
"  ;B@@@M@BMOM8O8OMMGONZSSjSG8EGGGEO@@B@B@B7.  :XSFFq8M@57:.     ",
" .B@B@B@@@B@MBOMZM88O8O8OZB8GOGZNE8MGMGBB2  XSj7;Y:             ",
"      .,:i7vJUkXE0GGOOOOOOO8O8O8MMMOMMMBu   @B@0r:@7            ",
"                     ..::;rLj5F0EMM@B@Bu     BB@B@@@u           ",
"                                              1F@B@BJ           ", 
"     SEOULTECH 13184394 YOUN HYUN JIN / COMPUTER PROGRAMMING    "

	};

	int i,j;
	//����Ϳ� Ű���� �κ�
	for(i=0;i<=8;i++){
		for(j=0;j<=67;j++) {
			if(j<46) { //����Ϳ� Ű���� ������
				SETTEXTCOLOR_ORIGINAL; //�⺻ �ܼ� â�� ��Ʈ ������ ���.
				putchar(comp[i][j]);
			}
			else { //��ǻ�� ��ü ��
				SETTEXTCOLOR_RED;
				putchar(comp[i][j]);
			}
		}
		putchar('\n');
	}
	//����Ϳ� Ű���� �κ� �̾� ���
	for(i=9;i<=13;i++){
		for(j=0;j<=67;j++) {
				if(j<46) { 
				SETTEXTCOLOR_ORIGINAL;
				putchar(comp[i][j]);
			}
			else { //��ǻ�� ��ü ��
				SETTEXTCOLOR_RED;
				putchar(comp[i][j]);
			}
		}
		putchar('\n');
	}
	
	//����Ϳ� Ű���� �κ� �̾� ���
	for(i=14;i<=21;i++){
		for(j=0;j<=67;j++) {
			if(j<44) {
				SETTEXTCOLOR_ORIGINAL;
				putchar(comp[i][j]);
			}
			else { //��ǻ�� ��ü ��
				SETTEXTCOLOR_RED;
				putchar(comp[i][j]);
			}
		}
		putchar('\n');
	}

	i=25;
	for(j=0;j<=67;j++) {
		 //�� ���� �й��� �̸��� �Ķ������� ó��
			SETTEXTCOLOR_BLUE;
			putchar(comp[i][j]);
	}

	SETTEXTCOLOR_ORIGINAL; //��Ÿ ���� �κ��� �ܼ� ���â�� ��Ʈ������ ���

	delay(2500); //�����̸� 2500ms�� ����.
	system("cls"); //��ǻ�� ȭ�� ����.
}

void delay(unsigned int n) //������(��ǻ�� �׸��� �ܼ� ȭ�鿡 �� �ִ� �ð�)
{ 
	unsigned o = GetTickCount(); //OS������ ������ �ҿ�� �ð��� msec ������ ��ȯ, windows.h ������� ����
	while((GetTickCount()-o)< n);
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

//����ڰ� ����Ű�� ���� ������ Ƚ���� ī��Ʈ�ϴ� ī��Ʈ�Լ� ���
void draw_Count()
{
	gotoxy(40,0); 
	printf("Move Count: %d\n",move_cnt);
}

// move cursor to (x,y)
// upper left corner is (0,0)
void gotoxy(int x, int y)
{
	COORD Pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}