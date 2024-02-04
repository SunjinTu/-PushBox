#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<easyx.h>
#include<windows.h>
/*
* ������Ҫ�յ�
* ǽ Ŀ�ĵ� ���� ��� ��ͼ���к�����
* ����̨�汾
*/
#define SPACE 0  //�յ�
#define WALL 1   //ǽ
#define DEST 2   //Ŀ�ĵ�
#define BOX 3    //����
#define PLAYER 4 //���
#define ROW 10   //����
#define COLS 10  //����
#define IMGSIZE 64   //ͼƬ�������
#define GROUP 3//����

//�����ͼ
int map[GROUP][ROW][COLS];
int level = 0;//��ǰ���ڹؿ�

IMAGE imgs[7];
//����ͼƬ����
void loadImg() {
	loadimage(imgs + 0, "./images/0.png", IMGSIZE, IMGSIZE);
	loadimage(imgs + 1, "./images/1.jpg", IMGSIZE, IMGSIZE);
	loadimage(imgs + 2, "./images/2.png", IMGSIZE, IMGSIZE);
	loadimage(imgs + 3, "./images/3.png", IMGSIZE, IMGSIZE);
	loadimage(imgs + 4, "./images/4.jpg", IMGSIZE, IMGSIZE);
	loadimage(imgs + 5, "./images/5.jpg", IMGSIZE, IMGSIZE);
	loadimage(imgs + 6, "./images/6.jpg", IMGSIZE, IMGSIZE);

}
//��ʼ����ͼ
void initmap() {
	int tmap[GROUP][ROW][COLS] = {
		{
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,0,0,0,0},
			{0,0,0,1,2,1,0,0,0,0},
			{0,1,1,1,0,1,1,1,1,0},
			{0,1,0,0,3,3,0,2,1,0},
			{0,1,2,3,4,0,1,1,1,0},
			{0,1,1,1,1,3,1,0,0,0},
			{0,0,0,0,1,2,1,0,0,0},
			{0,0,0,0,1,1,1,0,0,0},
			{0,0,0,0,0,0,0,0,0,0}
		},
		{
			{0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,0,1,1,1,1},
			{0,1,2,0,0,1,0,2,0,1},
			{0,1,2,0,3,0,0,0,0,1},
			{0,0,1,0,0,3,0,0,1,0},
			{0,1,0,0,4,0,0,0,2,1},
			{0,1,3,0,0,0,0,3,0,1},
			{0,1,2,0,0,1,0,0,2,1},
			{0,0,1,1,1,0,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0}
		},
		{
			{1,1,1,1,1,0,0,0,0,0},
			{1,2,0,0,0,1,0,0,0,0},
			{0,1,0,3,0,0,1,0,0,0},
			{1,1,0,3,0,0,1,1,1,0},
			{1,2,0,0,3,0,3,2,1,0},
			{1,0,0,0,4,0,0,0,1,0},
			{1,2,0,3,0,3,0,2,1,0},
			{0,1,0,0,0,0,0,0,1,0},
			{0,1,1,0,2,0,0,1,0,0},
			{0,0,0,1,1,1,1,1,0,0}
		}
		
	};
	memcpy(map, tmap, sizeof(map));
}
//չʾ��ͼ
void show() {
	system("cls");//����
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLS; j++) {
			//printf("%d ",map[level][i][j]);
			switch (map[level][i][j])
			{
			case SPACE:
				printf("  ");
				break;
			case WALL:
				printf("\\\\");
				break;
			case PLAYER:
				printf("��");
				break;
			case BOX:
				printf("��");
				break;
			case DEST:
				printf("��");
				break;
			case PLAYER+DEST://��վ��Ŀ�ĵ���
				printf("��");
				break;
			case BOX+DEST://����վ��Ŀ�ĵ���
				printf("ţ");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
}
//�жϷ����
bool judge() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[level][i][j] == BOX) {
				return false;
			}
		}
	}
	return true;
}
//չʾͼƬ������
void draw() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLS; j++) {
			int x, y;
			x = j * IMGSIZE;//j��
			y = i * IMGSIZE;//i��
			putimage(x, y, imgs + map[level][i][j]);
		}
		printf("\n");
	}
}
//�ƶ�����
void move() {
	int r = -1, c = -1;//r��c���˵�����
	//���˵�����
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLS; j++) {
			if (map[level][i][j]==PLAYER||map[level][i][j]==PLAYER+DEST) {
				r = i;
				c = j;
				goto end;
			}
		}
	}
end:;
	int key=_getch();
	//printf(" %d\n", key);
	switch (key)
	{
	case 72://�������ƶ�
		if (map[level][r - 1][c] == SPACE || map[level][r - 1][c] ==  DEST) {//�����ҵ������ǿյػ�Ŀ�ĵ���ֱ���ƶ�
			map[level][r - 1][c] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		//���������������
		else if (map[level][r - 1][c] == BOX) {
			//������������ǿյػ�Ŀ�ĵ�
			if (map[level][r - 2][c] == SPACE || map[level][r - 2][c] == DEST) {
				map[level][r - 2][c] += BOX;//�Ȱ����������ƣ��ٰ��������ƶ�
				map[level][r - 1][c] -= BOX;//�����Ӵ�ԭ����λ��ɾ����
				map[level][r - 1][c] += PLAYER;//������ƶ������ӵ�λ��
				map[level][r][c] -= PLAYER;//����Ҵ�ԭ����λ��ɾ����
			}
		}
		break;
		
	case 80://�������ƶ�
		if (map[level][r + 1][c] == SPACE || map[level][r + 1][c] == DEST) {//�����ҵ������ǿյػ�Ŀ�ĵ���ֱ���ƶ�
			map[level][r + 1][c] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		//���������������
		else if (map[level][r + 1][c] == BOX) {
			//������������ǿյػ�Ŀ�ĵ�
			if (map[level][r + 2][c] == SPACE || map[level][r + 2][c] == DEST) {
				map[level][r + 2][c] += BOX;//�Ȱ����������ƣ��ٰ��������ƶ�
				map[level][r + 1][c] -= BOX;//�����Ӵ�ԭ����λ��ɾ����
				map[level][r + 1][c] += PLAYER;//������ƶ������ӵ�λ��
				map[level][r][c] -= PLAYER;//����Ҵ�ԭ����λ��ɾ����
			}
		}
			break;
			
	case 75://�������ƶ�
		if (map[level][r][c - 1] == SPACE || map[level][r][c - 1] == DEST) {//�����ҵ������ǿյػ�Ŀ�ĵ���ֱ���ƶ�
			map[level][r][c - 1] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		//���������������
		else if (map[level][r][c-1] == BOX) {
			//������������ǿյػ�Ŀ�ĵ�
			if (map[level][r][c-2] == SPACE || map[level][r][c-2] == DEST) {
				map[level][r][c-2] += BOX;//�Ȱ����������ƣ��ٰ��������ƶ�
				map[level][r][c-1] -= BOX;//�����Ӵ�ԭ����λ��ɾ����
				map[level][r][c-1] += PLAYER;//������ƶ������ӵ�λ��
				map[level][r][c] -= PLAYER;//����Ҵ�ԭ����λ��ɾ����
			}
		}
		break;

	case 77://�������ƶ�
		if (map[level][r][c + 1] == SPACE || map[level][r][c + 1] == DEST) {//�����ҵ������ǿյػ�Ŀ�ĵ���ֱ���ƶ�
			map[level][r][c + 1] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		//���������������
		else if (map[level][r][c + 1] == BOX) {
			//������������ǿյػ�Ŀ�ĵ�
			if (map[level][r][c + 2] == SPACE || map[level][r][c + 2] == DEST) {
				map[level][r][c + 2] += BOX;//�Ȱ����������ƣ��ٰ��������ƶ�
				map[level][r][c + 1] -= BOX;//�����Ӵ�ԭ����λ��ɾ����
				map[level][r][c + 1] += PLAYER;//������ƶ������ӵ�λ��
				map[level][r][c] -= PLAYER;//����Ҵ�ԭ����λ��ɾ����
			}
		}
		break;
	default:
		break;
	}
}
//�ж�ʧ��
bool Fail() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[level][i][j] == BOX){
				if ((map[level][i - 1][j] == WALL ||map[level][i-1][j] == BOX + DEST )&&
					(map[level][i][j - 1] == WALL|| map[level][i][j - 1]==BOX+DEST)) {
					return true;
				}
				else if ((map[level][i - 1][j] == WALL || map[level][i - 1][j] == BOX + DEST) &&
					(map[level][i][j +1] == WALL || map[level][i][j + 1] == BOX + DEST)) {
					return true;
				}
				else if ((map[level][i + 1][j] == WALL || map[level][i + 1][j] == BOX + DEST) &&
					(map[level][i][j + 1] == WALL || map[level][i][j + 1] == BOX + DEST)) {
					return true;
				}
				else if ((map[level][i + 1][j] == WALL || map[level][i + 1][j] == BOX + DEST) &&
					(map[level][i][j - 1] == WALL || map[level][i][j - 1] == BOX + DEST)) {
					return true;
				}
			}
		}
	}
	return false;
}

int main() {
	//��ʼ��ͼ�ν���
	initgraph(IMGSIZE*COLS,IMGSIZE*ROW,EW_SHOWCONSOLE);
	loadImg();
	initmap();
	while (level!=3) {
		show();
		draw();
		if (judge()) {
			MessageBox(NULL, "���Ѿ����˹�", "��ʾ", MB_OK);
			level++;
		}
		if (Fail()) {
			MessageBox(NULL, "ͨ��ʧ��", "��ʾ", MB_OK);
			break;
		}
		move();
	}
}