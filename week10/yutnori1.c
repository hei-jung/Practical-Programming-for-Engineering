//yut을 던질때마다 count를 count+4해주고 u의 개수도 세어줌
//ucount/count가 a 값에 가까워질 때 종료
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int ThrowYut(char *);//윷 던지는 함수
int CountU(char *);//UP 세는 함수
int CheckFunc(double a, int ucount, int count);

void main(int argc, char *argv[])
{
	int i, present = 0, next, move;
	int count = 0, ucount = 0;
	char yut[5];
	double a;

	/*U의 확률 a 인자 받기*/
	a = atof(argv[1]);
	printf("%.3f\n", a);

	printf("윷놀이를 시작합니다!\n---------------------\n");

	/*윷 던지기*/
	srand(time(NULL));
	while (present < 90)
	{
		move = ThrowYut(yut);
		ucount += CountU(yut);
		count += 4;

		/*말 옮기기*/
		next = present;
		if (present == 5) next = 65;	next = next + (move - 1);
		if (present == 10)	next = 86;	next = next + (move - 1);
		if ((present >= 15) && (present < 20) && (present + move >= 20)) {
			if (present < 20) printf("%d -> Z (end)\n", present);
			else printf("%c -> Z (end)\n", present);
			break;
		}
		if (present == 67) {
			next = 88;
			next = next + (move - 1);
			if (move > 2) {
				if (present < 20) printf("%d -> Z (end)\n", present);
				else printf("%c -> Z (end)\n", present);
				break;
			}
		}
		if ((present == 86) && (move == 5)) {
			if (present < 20) printf("%d -> Z (end)\n", present);
			else printf("%c -> Z (end)\n", present);
			break;
		}
		if (present == 87) {
			if(move==1)	next = 67;
			if ((move > 1)&&(move<4))	next = present + (move - 1);
			if (move == 4) {
				if (present < 20) printf("%d -> Z (end)\n", present);
				else printf("%c -> Z (end)\n", present);
				break;
			}
		}
		if ((present > 87) && (present + move >= 90)) {
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

		if (CheckFunc(a, ucount, count) == 0) break;
	}
}

int ThrowYut(char *arr)
{
	int i, count = 0;

	for (i = 0; i < 4; i++) {
		if (rand() % 2 == 0)	arr[i] = 'D';
		else {
			arr[i] = 'U';
			count++;
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
	if (count != 0)	return count;
	else
	{
		return 5;//'모'일 때는 5칸 이동하도록
	}
}

int CountU(char *arr)
{
	int i, count = 0;

	for (i = 0; i < 4; i++) {
		if (arr[i] == 'U')	count++;
	}
	if (count == 0)	count = 5;

	return count;
}

int CheckFunc(double a, int ucount, int count) 
{
	int num1 = (int)(10.0*a);
	int num2 = (int)(10.0*((double)ucount / (double)count));
	if (num1 == num2)	return 0;
	return 1;
}
