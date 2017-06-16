#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct ball {	//气球结构体
	double x;       //气球球心x坐标
	double y;			//气球球心y坐标
	double z;			//气球球心z坐标
	double r;			//气球球心半径
}Ball;

typedef struct ballList {	//用链表来储存已经放置的气球
	struct ballList * next;
	Ball ball;
}BallList;

void insert(Ball ball);
double distance(Ball b1, Ball b2);
int judge(Ball b);
void putBall();
void putPoint(double x, double y,double z);

BallList *head = NULL;
double step = 0.01;			//改变气球位置的最小单位
int num = 0;             //放置气球的个数
double sumr = 0;				//用来记录r^2之和

int main() {
	int n, pointNum, i;
	printf("请输入气球总数量: ");
	scanf("%d", &n);
	printf("请输入点的数量: ");
	scanf("%d", &pointNum);
	for (i = 0; i < pointNum; i++) {
		printf("请输入第%d个点的坐标(空格隔开)：", i + 1);
		double x, y, z;
		scanf("%lf %lf", &x, &y,&z);
		putPoint(x, y, z);
	}
	printf("\n球编号\t x坐标\t y坐标\t z坐标\t 半径\t r^2之和\n");
	for (i = 0; i < n; i++) {
		putBall();
	}
	printf("\nr^2之和最大为:\t %lf\n", sumr);
	system("pause");
	return 0;
	}

//将设置的点作为半径为0的点插入气球队列
void putPoint(double x, double y,double z) {
	Ball ball = { x, y, z, 0 };
	insert(ball);
}

void insert(Ball ball) {		//将气球插入气球队列

	BallList * newBall = (BallList *)malloc(sizeof(BallList));
	newBall->ball = ball;
	newBall->next = head;
	head = newBall;
}

//改变气球的初始位置，求的满足条件的气球
void putBall() {
	Ball ball = { -1 + step, -1 + step, -1 + step, 0 };
	Ball maxBall = ball;
	int i, j, k;
	for (i = 0; ball.x < 1; ++i) {
		ball.x += step;
		ball.y = -1 + step;
		for (j = 0; ball.y < 1; ++j) {
			ball.y += step;
			ball.z = -1 + step;
			for (k = 0; ball.z < 1; ++k) {
				ball.z += step;
				ball.r = 0;
				double rstep = 0.1;
				while (rstep > 0.00001) {
					if (ball.r > maxBall.r) {
						maxBall = ball;
					}
					ball.r += rstep;
					if (!judge(ball)) {	//此气球不合适，减小半径与步长重新尝试
						ball.r -= rstep;
						rstep /= 10;
					}
				}
			}
		}
	}
	if (judge(maxBall)) {
		insert(maxBall);
		num++;
		sumr += maxBall.r * maxBall.r;
		printf("%d\t %.3lf\t %.3lf\t %.3lf\t %.3lf\t %lf \n", num, maxBall.x, maxBall.y, maxBall.z, maxBall.r, sumr);
	}
}

//判断气球之间的距离
double distance(Ball b1, Ball b2) {
	double x1 = b1.x;
	double y1 = b1.y; 
	double z1 = b1.z;
	double x2 = b2.x;
	double y2 = b2.y;
	double z2 = b2.z;
	return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) +(z1 - z2)*(z1 - z2), 0.5);
}

//判断新加入的气球是否符合规则
int judge(Ball b) {
	//将气球限制在[-1，1]内
	if ((fabs(b.x) + b.r) > 1 || (fabs(b.y) + b.r) > 1 || (fabs(b.z) + b.r) > 1) {
		return 0;
	}
	//依次比较气球b与已有气球是否相交
	BallList *tmp = head;
	while (tmp) {
		Ball ball = tmp->ball;
		if (distance(b, ball) < b.r + ball.r) {
			return 0;
		}
		tmp = tmp->next;
	}
	return 1;
}

