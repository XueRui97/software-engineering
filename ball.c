#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 

//����ṹ�� 
typedef struct ball{ 
	double x;    //Բ��x���� 
	double y;		//Բ��y���� 
	double r;		//Բ�뾶 
}Ball; 
 
//�������������Ѿ����õ����� 
typedef struct ballList{ 
	struct ballList * next; 
	Ball ball; 
}BallList; 

void insert(Ball ball); 
double distance(Ball b1, Ball b2); 
int judge(Ball b); 
void putBall(); 

 
BallList *head = NULL; 
double step = 0.01;							//�ı�����λ�õ���С��λ 
int num = 0;                                //��������ĸ��� 
double sumr = 0;							//������¼r^2֮�� 

 
void main(void){ 
	int n=0; 
	printf("��������������: "); 
	scanf_s("%d", &n); 
	printf("\n����\t x����\t y����\t �뾶\t r^2֮��\n"); 
	int i;
	for (i = 0; i < n; i++){ 
		putBall(); 
	} 
	printf("\nr^2֮�����Ϊ:\t %lf\n", sumr); 
	system("pause"); 
} 
void insert(Ball ball){ 	//��������
	BallList * newBall = (BallList *)malloc(sizeof(BallList)); 
	newBall->ball = ball; 
	newBall->next = head; 
	head = newBall; 
} 
void putBall(){ //�ı�����ĳ�ʼλ�ã������������������ 
	Ball ball = { -1 + step, -1 + step, 0 }; 
	Ball maxBall = ball; 
	int i, j; 
	for (i = 0; ball.x < 1; ++i){ 
		ball.x += step; 
		ball.y = -1 + step; 
		for (j = 0; ball.y < 1; ++j){ 
			ball.y += step; 
			ball.r = 0; 
			double rstep = 0.1; 
			while (rstep > 0.00001){ 
				if (ball.r > maxBall.r){ 
					maxBall = ball; 
				} 
				ball.r += rstep; 
				if (!judge(ball)){  //�����򲻺��ʣ���С�뾶�벽�����³��� 
					ball.r -= rstep; 
					rstep /= 10; 
				} 
			} 
		} 
	} 
	if (judge(maxBall)){ 
		insert(maxBall); 
		num++; 
		sumr += maxBall.r * maxBall.r; 
		printf("%d\t %.3lf\t %.3lf\t %.3lf\t %lf \n", num, maxBall.x, maxBall.y, maxBall.r, sumr); 
	} 
} 
int judge(Ball b){ //�ж��¼���������Ƿ���Ϲ��� 
	//������������[-1��1]�� 
	if ((fabs(b.x) + b.r) > 1 || (fabs(b.y) + b.r) > 1){ 
		return 0; 
	} 
	//���αȽ�����b�����������Ƿ��ཻ 
	BallList *tmp = head; 
	while (tmp){ 
		Ball ball = tmp->ball; 
		//���������ཻ�ж� 
		if (distance(b, ball) < b.r + ball.r){ 
 			return 0; 
 		} 
		tmp = tmp->next; 
	} 
	return 1; 
} 
//�ж���������֮��ľ��� 
double distance(Ball b1, Ball b2){ 
	double x1 = b1.x; 
	double y1 = b1.y; 	double x2 = b2.x; 
	double y2 = b2.y; 
	return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2), 0.5); 
} 

