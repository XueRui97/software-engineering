#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct ball {	//����ṹ��
	double x;       //��������x����
	double y;			//��������y����
	double z;			//��������z����
	double r;			//�������İ뾶
}Ball;

typedef struct ballList {	//�������������Ѿ����õ�����
	struct ballList * next;
	Ball ball;
}BallList;

void insert(Ball ball);
double distance(Ball b1, Ball b2);
int judge(Ball b);
void putBall();
void putPoint(double x, double y,double z);

BallList *head = NULL;
double step = 0.01;			//�ı�����λ�õ���С��λ
int num = 0;             //��������ĸ���
double sumr = 0;				//������¼r^2֮��

int main() {
	int n, pointNum, i;
	printf("����������������: ");
	scanf("%d", &n);
	printf("������������: ");
	scanf("%d", &pointNum);
	for (i = 0; i < pointNum; i++) {
		printf("�������%d���������(�ո����)��", i + 1);
		double x, y, z;
		scanf("%lf %lf", &x, &y,&z);
		putPoint(x, y, z);
	}
	printf("\n����\t x����\t y����\t z����\t �뾶\t r^2֮��\n");
	for (i = 0; i < n; i++) {
		putBall();
	}
	printf("\nr^2֮�����Ϊ:\t %lf\n", sumr);
	system("pause");
	return 0;
	}

//�����õĵ���Ϊ�뾶Ϊ0�ĵ�����������
void putPoint(double x, double y,double z) {
	Ball ball = { x, y, z, 0 };
	insert(ball);
}

void insert(Ball ball) {		//����������������

	BallList * newBall = (BallList *)malloc(sizeof(BallList));
	newBall->ball = ball;
	newBall->next = head;
	head = newBall;
}

//�ı�����ĳ�ʼλ�ã������������������
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
					if (!judge(ball)) {	//�����򲻺��ʣ���С�뾶�벽�����³���
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

//�ж�����֮��ľ���
double distance(Ball b1, Ball b2) {
	double x1 = b1.x;
	double y1 = b1.y; 
	double z1 = b1.z;
	double x2 = b2.x;
	double y2 = b2.y;
	double z2 = b2.z;
	return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) +(z1 - z2)*(z1 - z2), 0.5);
}

//�ж��¼���������Ƿ���Ϲ���
int judge(Ball b) {
	//������������[-1��1]��
	if ((fabs(b.x) + b.r) > 1 || (fabs(b.y) + b.r) > 1 || (fabs(b.z) + b.r) > 1) {
		return 0;
	}
	//���αȽ�����b�����������Ƿ��ཻ
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
