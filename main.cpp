#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<easyx.h>
#include<windows.h>
/*
* 推箱子要空地
* 墙 目的地 箱子 玩家 地图的行和列数
* 控制台版本
*/
#define SPACE 0  //空地
#define WALL 1   //墙
#define DEST 2   //目的地
#define BOX 3    //箱子
#define PLAYER 4 //玩家
#define ROW 10   //行数
#define COLS 10  //列数
#define IMGSIZE 64   //图片最大像素
#define GROUP 3//组数

//定义地图
int map[GROUP][ROW][COLS];
int level = 0;//当前所在关卡

IMAGE imgs[7];
//定义图片数组
void loadImg() {
	loadimage(imgs + 0, "./images/0.png", IMGSIZE, IMGSIZE);
	loadimage(imgs + 1, "./images/1.jpg", IMGSIZE, IMGSIZE);
	loadimage(imgs + 2, "./images/2.png", IMGSIZE, IMGSIZE);
	loadimage(imgs + 3, "./images/3.png", IMGSIZE, IMGSIZE);
	loadimage(imgs + 4, "./images/4.jpg", IMGSIZE, IMGSIZE);
	loadimage(imgs + 5, "./images/5.jpg", IMGSIZE, IMGSIZE);
	loadimage(imgs + 6, "./images/6.jpg", IMGSIZE, IMGSIZE);

}
//初始化地图
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
//展示地图
void show() {
	system("cls");//清屏
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
				printf("人");
				break;
			case BOX:
				printf("箱");
				break;
			case DEST:
				printf("的");
				break;
			case PLAYER+DEST://人站在目的地上
				printf("哈");
				break;
			case BOX+DEST://箱子站在目的地上
				printf("牛");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
}
//判断否过关
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
//展示图片化界面
void draw() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLS; j++) {
			int x, y;
			x = j * IMGSIZE;//j列
			y = i * IMGSIZE;//i行
			putimage(x, y, imgs + map[level][i][j]);
		}
		printf("\n");
	}
}
//移动箱子
void move() {
	int r = -1, c = -1;//r和c是人的坐标
	//找人的坐标
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
	case 72://人向上移动
		if (map[level][r - 1][c] == SPACE || map[level][r - 1][c] ==  DEST) {//如果玩家的上面是空地或目的地则直接移动
			map[level][r - 1][c] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		//如果人上面是箱子
		else if (map[level][r - 1][c] == BOX) {
			//如果箱子上面是空地或目的地
			if (map[level][r - 2][c] == SPACE || map[level][r - 2][c] == DEST) {
				map[level][r - 2][c] += BOX;//先把箱子往上移，再把人往上移动
				map[level][r - 1][c] -= BOX;//把箱子从原来的位置删除掉
				map[level][r - 1][c] += PLAYER;//把玩家移动到箱子的位置
				map[level][r][c] -= PLAYER;//把玩家从原来的位置删除掉
			}
		}
		break;
		
	case 80://人向下移动
		if (map[level][r + 1][c] == SPACE || map[level][r + 1][c] == DEST) {//如果玩家的上面是空地或目的地则直接移动
			map[level][r + 1][c] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		//如果人下面是箱子
		else if (map[level][r + 1][c] == BOX) {
			//如果箱子下面是空地或目的地
			if (map[level][r + 2][c] == SPACE || map[level][r + 2][c] == DEST) {
				map[level][r + 2][c] += BOX;//先把箱子往下移，再把人往下移动
				map[level][r + 1][c] -= BOX;//把箱子从原来的位置删除掉
				map[level][r + 1][c] += PLAYER;//把玩家移动到箱子的位置
				map[level][r][c] -= PLAYER;//把玩家从原来的位置删除掉
			}
		}
			break;
			
	case 75://人向左移动
		if (map[level][r][c - 1] == SPACE || map[level][r][c - 1] == DEST) {//如果玩家的上面是空地或目的地则直接移动
			map[level][r][c - 1] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		//如果左上面是箱子
		else if (map[level][r][c-1] == BOX) {
			//如果箱子左面是空地或目的地
			if (map[level][r][c-2] == SPACE || map[level][r][c-2] == DEST) {
				map[level][r][c-2] += BOX;//先把箱子往左移，再把人往左移动
				map[level][r][c-1] -= BOX;//把箱子从原来的位置删除掉
				map[level][r][c-1] += PLAYER;//把玩家移动到箱子的位置
				map[level][r][c] -= PLAYER;//把玩家从原来的位置删除掉
			}
		}
		break;

	case 77://人向右移动
		if (map[level][r][c + 1] == SPACE || map[level][r][c + 1] == DEST) {//如果玩家的上面是空地或目的地则直接移动
			map[level][r][c + 1] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		//如果右右面是箱子
		else if (map[level][r][c + 1] == BOX) {
			//如果箱子右面是空地或目的地
			if (map[level][r][c + 2] == SPACE || map[level][r][c + 2] == DEST) {
				map[level][r][c + 2] += BOX;//先把箱子往右移，再把人往右移动
				map[level][r][c + 1] -= BOX;//把箱子从原来的位置删除掉
				map[level][r][c + 1] += PLAYER;//把玩家移动到箱子的位置
				map[level][r][c] -= PLAYER;//把玩家从原来的位置删除掉
			}
		}
		break;
	default:
		break;
	}
}
//判断失败
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
	//初始化图形界面
	initgraph(IMGSIZE*COLS,IMGSIZE*ROW,EW_SHOWCONSOLE);
	loadImg();
	initmap();
	while (level!=3) {
		show();
		draw();
		if (judge()) {
			MessageBox(NULL, "你已经过此关", "提示", MB_OK);
			level++;
		}
		if (Fail()) {
			MessageBox(NULL, "通关失败", "提示", MB_OK);
			break;
		}
		move();
	}
}