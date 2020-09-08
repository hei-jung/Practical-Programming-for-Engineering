#include<stdio.h>
#include<stdlib.h>

#define Height 400
#define Width 400
#define Byte_Pixel 4

void main(int argc, char *argv[])
{
	long file_size;
	char *file_buffer, data[Height][Width][Byte_Pixel];
	char input_file[20], output_file[20];
	int i, j, k, q, count = 55;
	int mode, num, index[8];
	FILE *fpt;

	if (argc != 5) {
		printf("ERROR \n");
		exit(1);
	}

	sprintf(input_file, "%s", argv[1]);
	fpt = fopen(input_file, "rb");
	if (fpt == NULL)	exit(1);

	mode = atoi(argv[3]);
	if ((mode == 0) || (mode == 1))	printf("mode = %d\n", mode);
	else {
		printf("mode는 0과 1만 가능합니다!\n");
		exit(1);
	}

	/*파일크기*/
	fseek(fpt, 0, SEEK_END);
	file_size = ftell(fpt);
	rewind(fpt);
	/*파일버퍼에 크기할당*/
	file_buffer = (char *)malloc(file_size);
	fread(file_buffer, sizeof(char), file_size, fpt);
	fclose(fpt);

	printf("file size = %d ( = %d) \n", file_size, (54 + Height*Width*Byte_Pixel));

	num = atoi(argv[4]);
	for (i = 7; i >= 0; i--) {
		index[i] = num % 10 - 1;//배열은 0부터 7까지니까 1 빼주기
		num = num / 10;
	}
	printf("order in: ");
	for (i = 0; i < 8;i++)	printf("%d",index[i] + 1);
	printf("\n");

	q = Width / 8;
	if (mode == 0) {
		/*파일버퍼의 데이터 저장*/
		for (i = 0; i < Height; i++) {
			for (j = 0; j < Width; j++) {
				for (k = 0; k < Byte_Pixel; k++) {
					data[i][j][k] = file_buffer[count++];//count는 55부터 시작!
				}
			}
		}
		/*파일버퍼에 데이터 새로 옮기기*/
		count = 55;
		for (i = 0; i < Height; i++) {
			for (j = 0; j < Width; j++) {
				for (k = 0; k < Byte_Pixel; k++) {
					if (j < q * 1)	file_buffer[count++] = data[i][j + q*index[0]][k];
					if ((j >= q * 1) && (j < q * 2))	file_buffer[count++] = data[i][(j - q) + q*index[1]][k];
					if ((j >= q * 2) && (j < q * 3))	file_buffer[count++] = data[i][(j - q * 2) + q*index[2]][k];
					if ((j >= q * 3) && (j < q * 4))	file_buffer[count++] = data[i][(j - q * 3) + q*index[3]][k];
					if ((j >= q * 4) && (j < q * 5))	file_buffer[count++] = data[i][(j - q * 4) + q*index[4]][k];
					if ((j >= q * 5) && (j < q * 6))	file_buffer[count++] = data[i][(j - q * 5) + q*index[5]][k];
					if ((j >= q * 6) && (j < q * 7))	file_buffer[count++] = data[i][(j - q * 6) + q*index[6]][k];
					if ((j >= q * 7) && (j < q * 8))	file_buffer[count++] = data[i][(j - q * 7) + q*index[7]][k];
				}
			}
		}
	}
	else if(mode==1){
		/*파일버퍼의 데이터 저장*/
		for (i = 0; i < Height; i++) {
			for (j = q*index[0]; j < q*(index[0] + 1); j++) {
				for (k = 0; k < Byte_Pixel; k++) {
					data[i][j][k] = file_buffer[count++];
				}
			}
			for (j = q*index[1]; j < q*(index[1] + 1); j++) {
				for (k = 0; k < Byte_Pixel; k++) {
					data[i][j][k] = file_buffer[count++];
				}
			}
			for (j = q*index[2]; j < q*(index[2] + 1); j++) {
				for (k = 0; k < Byte_Pixel; k++) {
					data[i][j][k] = file_buffer[count++];
				}
			}
			for (j = q*index[3]; j < q*(index[3] + 1); j++) {
				for (k = 0; k < Byte_Pixel; k++) {
					data[i][j][k] = file_buffer[count++];
				}
			}
			for (j = q*index[4]; j < q*(index[4] + 1); j++) {
				for (k = 0; k < Byte_Pixel; k++) {
					data[i][j][k] = file_buffer[count++];
				}
			}
			for (j = q*index[5]; j < q*(index[5] + 1); j++) {
				for (k = 0; k < Byte_Pixel; k++) {
					data[i][j][k] = file_buffer[count++];
				}
			}
			for (j = q*index[6]; j < q*(index[6] + 1); j++) {
				for (k = 0; k < Byte_Pixel; k++) {
					data[i][j][k] = file_buffer[count++];
				}
			}
			for (j = q*index[7]; j < q*(index[7] + 1); j++) {
				for (k = 0; k < Byte_Pixel; k++) {
					data[i][j][k] = file_buffer[count++];
				}
			}
		}
		/*파일버퍼에 데이터 새로 옮기기*/
		count = 55;
		for (i = 0; i < Height; i++) {
			for (j = 0; j < Width; j++) {
				for (k = 0; k < Byte_Pixel; k++) {
					file_buffer[count++] = data[i][j][k];
				}
			}
		}
	}

	sprintf(output_file, "%s", argv[2]);
	fpt = fopen(output_file, "wb");
	fwrite(file_buffer, sizeof(char), file_size, fpt);
	fclose(fpt);
}
