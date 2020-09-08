#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10

int change(int *arr, int n);//change함수의 프로토타입!

int main(int argc, char *argv[])
{
	/*필요한 변수*/
	char name[MAX];
	int g, h, i, j, count = -1, in = 1, num;
	int newname[MAX * 2 - 1], tmp[MAX * 2 + 1], cal[MAX * 2 + 1];

	g = strlen(argv[1]);
	if (g < 5) {
		printf("name: too short\n");
		exit(1);
	}

	/*알파벳 대문자로만 된 이름을 받는다.*/
	for (i = 0; i < g; i++)	name[i] = argv[1][i];
	for (i = 0; i < g; i++)	printf("%c", name[i]);
	printf("\n");

	/*입력받은 이름이 제대로 되어 있는지 검사한다.*/
	for (i = 0; i < g; i++) {
		if (!(name[i] >= 65 && name[i] <= 90)) {
			printf("name: invalid format\n");
			return 0;
		}
	}

	/*이름의 각 알파벳을 규칙에 따라 숫자로 변환한다.*/
	for (i = 0; i < g; i++)
		newname[i] = 'A' - (((int)(name[i]) - 'A') + 40);
	printf("name:");
	for (i = 0; i < g; i++)
		printf("%3d", newname[i]);
	printf("\n");

	/*숫자 분리, 연산*/
	for (i = 0; i < g; i++) {
		if (newname[i] >= 10) {
			tmp[++count] = newname[i] / 10;
			tmp[++count] = newname[i] % 10;
		}
		else
			tmp[++count] = newname[i];
	}
	for (i = 0; i <= count; i++)//cal[i]를 cal_1[i]로 복사
		cal[i] = tmp[i];
	printf("(1)");
	for (i = 0; i <= count; i++)
		printf("%3d", cal[i]);
	printf("\n");
	//분리된 숫자 출력

	/*5000과 비교; 5000보다 작을 때까지 연산*/
	num = change(tmp, count);
	for (h = 0; h < count - 3; h++) {
		if (cal[h] != 0) {
			for (i = count; i >= 2; i--) {
				for (j = 0; j < i; j++)
					cal[j] = (cal[j] + cal[j + 1]) % 10;
				printf("(%d)", ++in);
				for (j = 0; j < i; j++)
					printf("%3d", cal[j]);
				printf("\n");
				if ((i == 4) && (cal[0] < 5)) {
					for (j = 0; j < g; j++)	printf("%c", name[j]);
					printf(" = ");
					for (j = 0; j < i; j++) {
						printf("%d", cal[j]);
					}
					printf("\n");
					break;
				}
				else if (i == 3) {
					num = change(cal, i);
					break;
				}
			}
			break;
		}
	}
	if ((num > 0) && (num < 5000)) {
		for (i = 0; i < g; i++)	printf("%c", name[i]);
		printf(" = %d", num);
	}

	return 0;
}

int change(int *arr, int n)
{
	int i, j, num = 0;
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j <= i; j++)
			arr[j] *= 10;
	}
	for (i = 0; i <= n; i++)
		num += arr[i];

	return num;
}
