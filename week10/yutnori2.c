#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int ThrowYut(char *,double a);//윷 던지는 함수

void main(int argc, char *argv[])
{
	int present = 0, next, move;
	char yut[5];
	double a;

	/*U의 확률 a 인자 받기*/
	a = atof(argv[1]);
	printf("'U'가 나올 확률 = %.2f\n'D'가 나올 확률 = %.2f\n\n", a,1-a);

	printf("Let's start 윷놀이!\n---------------------\n");
	/*윷 던지기*/
	srand(time(NULL));
	for (;;) {
		move = ThrowYut(yut, a);
		if (move == 0)	move = 5;

		/*말 옮기기*/
		next = present;
		if (present == 5) {
			next = 65;
			next = next + (move - 1);
		}
		else if (present == 10) {
			next = 86;
			next = next + (move - 1);
		}
		else if ((present >= 15) && (present < 20) && (present + move >= 20)) {
			if (present < 20) printf("%d -> Z (end)\n", present);
			else printf("%c -> Z (end)\n", present);
			break;
		}
		else if ((present == 65) && (move == 5)) next = 15;
		else if ((present == 66) && (move >= 4)) {
			next = 15;
			next = next + (move - 4);
		}
		else if (present == 67) {
			next = 88;
			next = next + (move - 1);
			if (move > 2) {
				if (present < 20) printf("%d -> Z (end)\n", present);
				else printf("%c -> Z (end)\n", present);
				break;
			}
		}
		else if ((present == 68) && (move >= 2)) {
			next = 15;
			next = next + (move - 2);
		}
		else if ((present == 69) && (move >= 1)) {
			next = 15;
			next = next + (move - 1);
		}
		else if ((present == 86) && (move == 5)) {
			if (present < 20) printf("%d -> Z (end)\n", present);
			else printf("%c -> Z (end)\n", present);
			break;
		}
		else if (present == 87) {
			if (move == 1)	next = 67;
			if ((move > 1) && (move < 4))	next = present + (move - 1);
			if (move == 4) {
				if (present < 20) printf("%d -> Z (end)\n", present);
				else printf("%c -> Z (end)\n", present);
				break;
			}
		}
		else if ((present > 87) && (present + move >= 90)) {
			if (present < 20) printf("%d -> Z (end)\n", present);
			else printf("%c -> Z (end)\n", present);
			break;
		}
		else
		{
			next = present + move;
		}

		/*말의 이동 출력*/
		if (present < 20) {
			if (present == 0)	printf("(start) Z -> ");
			else printf("%d -> ", present);
		}
		else printf("%c -> ", present);
		if (next < 65)	printf("%d\n", next);
		else printf("%c\n", next);
		present = next;
	}
}

int ThrowYut(char *arr, double a)
{
	int i, count = 0;
	int randnum;
	double prob;

	for (i = 0; i < 4; i++) {
		randnum = rand() % 100;
		prob = (double)randnum / 100.0;
		if (prob < a) {
			arr[i] = 'U';
			count++;
		}
		else {
			arr[i] = 'D';
		}
	}
	arr[4] = '\0';//배열의 index는 0에서부터 시작하니까 index 4가 끝임.
	puts(arr);
	switch (count) {
	case 1: printf("도: ");	break;
	case 2: printf("개: ");	break;
	case 3: printf("걸: ");	break;
	case 4: printf("윷: ");	break;
	case 0: printf("모: ");	break;
	}
	return count;
}
