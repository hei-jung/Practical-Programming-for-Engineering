#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void main(int argc, char *argv[])
{
	/*A와 관련한 변수*/
	int index, mode, num, a, b, x, y, A;
	int data[10][10], max_x, max_y, min_x, min_y;
	/*B와 관련한 변수*/
	char B[71];
	int blen, i, j;
	int C[70], temp = 0, count = 0;
	if (argc != 3) {
		printf("main.exe A(4<=A<=10) strlen(B)<=70 \n");
		exit(1);
	}
	A = atoi(argv[1]);
	if ((A < 4) || (A>10)) {
		printf("main.exe A(4<=A<=10)\n");
		exit(1);
	}
	num = A*A;
	blen = strlen(argv[2]);
	if (blen > 70) {
		printf("main.exe strlen(B)<=70 \n");
		exit(1);
	}
	//printf("%d\n", blen);
	strcpy(B, argv[2]);
	puts(B);
	for (i = 0; i < blen; i++) C[i] = B[i] - 48;
	//for (i = 0; i < blen; i++) printf("%2d", C[i]);
	//printf("\n");
	/*인수 B의 숫자 나누기(나눠서 배열 C에 저장)*/
	for (i = 0; i < blen; i = temp) {
		if (temp == blen - 2) {
			if (C[i] * 10 + C[i + 1] < num) {
				C[count] = C[i] * 10 + C[i+1];
			}
			else if (C[i] * 10 + C[i + 1] >= num) {
				C[count] = C[i];
				C[++count] = C[i + 1];
			}
			break;
		}
		if (temp == blen - 1) {
			C[count] = C[i];
		}
		for (j = i + 1; j <= i + 3; j++) {
			if (C[i] * 10 + C[j] < num) {
				C[i] = C[i] * 10 + C[j];
				temp = i + 1;
			}
			else if (C[i] * 10+C[j]>=num) {
				C[count] = C[i];
				count++;
				temp = j;
				break;
			}
		}
		
	}
	for (i = 0; i <= count; i++)	printf("%d ", C[i]);
	printf("\n");
	/*A 배열 채우기*/
	min_x = min_y = 0;
	max_x = max_y = A - 1;

	x = y = 0;
	data[y][x] = 0;
	mode = 0;
	a = 1;
	b = 0;
	min_y++;
	index = 0;
	while (index < num) {
		data[y][x] = index++;
		x = x + a;
		y = y + b;
		if ((mode == 0) && (x == max_x)) {
			a = 0;
			b = 1;
			max_x--;
			mode = 1;
		}
		if ((mode == 1) && (y == max_y)) {
			a = -1;
			b = 0;
			max_y--;
			mode = 2;
		}
		if ((mode == 2) && (x == min_x)) {
			a = 0;
			b = -1;
			min_x++;
			mode = 3;
		}
		if ((mode == 3) && (y == min_y)) {
			a = 1;
			b = 0;
			min_y++;
			mode = 0;
		}
	}
	for (y = 0; y < A; y++) {
		for (x = 0; x < A; x++) printf("%2d", data[y][x]);
		printf("\n");
	}//A 배열 출력
	/*거리의 최대값 찾기*/
	int p, q, m, n, distance, max_dist = 1;
	p = q = a = b = 0;
	for (y = 0; y < A; y++) {
		for (x = 0; x < A; x++) {
			for (i = 0; i <= count; i++) {
				if (data[y][x]==C[i]) {
					p = a;
					q = b;
					a = y;
					b = x;
					temp = i + 1;
					break;
				}
				distance = abs(p-a)+abs(q - b);
				if (distance > max_dist) {
					max_dist = distance;
					m = data[p][q];
					n = data[a][b];
				}
			}
		}
	}
	printf("(%d,%d) distance = %d\n", m,n,max_dist);
}
