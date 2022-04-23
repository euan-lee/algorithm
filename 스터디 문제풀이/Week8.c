#include <stdio.h>
#include <math.h>
#include <time.h>

//각각 레이어의 수, input 의 수(n), output의 수, bias 여부, eta 여부를 설정한다.
#define hidden 5
#define n 10
#define output_count 2
#define bias 1
#define eta 0.025

//1 - 10 번째 레이어까지의 뉴런의 숫자를 설정할 수 있다.
int hidden_N[10] = { 15,15,15,15,15,15,15,15,15,15 };

double w[10][15] = { {0,}, };
double w_middle[10][15][15] = { { {0,},} , };
double w_last[2][15] = { { 0,} , };
double w_bias[10][15] = { {0,}, };
double w_bias_output[2] = {0,};

//evaluation Error의 값과 EBP error 의 값을 저장하는 변수이다.
double err = 0, evaErr = 0;

//각각 U와 delta의 변수
double U[10][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, };
double U_relu[10][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, };
double U_last[2] = { 0 , 0 };
double delta[10][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, };
double last_delta[2] = { 0, 0 };

FILE* weight;

void EBP(double x[], double t[]) {
	double S = 0, S_output = 0;
	double S_middle[15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	//input에서 첫번째 레이어로 들어가는 w 값을 이용해 S값에서 U 값을 구한다.
	for (int i = 0; i < hidden_N[0]; i++) {
		S = 0;
		for (int j = 0; j < n; j++) {
			S += x[j] * w[j][i];
		}
		if (bias == 1) S += w_bias[0][i];

		U[0][i] = 1 / (1 + exp(-S));
	}

	//각레이어에 해당하는 u 값을 1번째 레이어의 뉴런부터 순서대로 구한다.
	for (int i = 0; i < hidden - 1; i++) {
		for (int j = 0; j < hidden_N[i + 1]; j++) {
			S = 0;
			for (int k = 0; k < hidden_N[i]; k++) {
				S += U[i][k] * w_middle[i][k][j];
			}
			if (bias == 1) S += w_bias[i + 1][j];

			U[i + 1][j] = 1 / (1 + exp(-S));
		}
	}

	//output 의 u 값을 구한다.
	for (int i = 0; i < output_count; i++) {
		S = 0;
		for (int j = 0; j < hidden_N[hidden - 1]; j++) {
			S += U[hidden - 1][j] * w_last[i][j];
		}
		if (bias == 1) S += w_bias_output[i];

		U_last[i] = 1 / (1 + exp(-S));
	}

	//output의 델타값을 구한다.
	for (int i = 0; i < output_count; i++) {
		last_delta[i] = (t[i] - U_last[i]) * U_last[i] * (1 - U_last[i]);
		err += fabs(t[i] - U_last[i]);
	}

	//맨 마지막의 hidden 레이어 delta 값을 구한다.
	for (int i = 0; i < hidden_N[hidden - 1]; i++) {
		double allDelta = 0;
		for (int j = 0; j < output_count; j++) {
			allDelta += last_delta[j] * w_last[j][i];
		}
		delta[hidden - 1][i] = U[hidden - 1][i] * (1 - U[hidden - 1][i]) * allDelta;
	}

	//마지막 레이어에서부터 첫번째 레이어까지 delta 값을 구한다.
	for (int i = hidden - 1; i > 0; i--) {
		for (int j = 0; j < hidden_N[i - 1]; j++) {
			double allDelta = 0;
			for (int k = 0; k < hidden_N[i]; k++) {
				allDelta += delta[i][k] * w_middle[i - 1][j][k];\
			}
			delta[i - 1][j] = U[i - 1][j] * (1 - U[i - 1][j]) * allDelta;
		}
	}

	//구한 delta 값으로 input과 첫레이어의 w 값을 변화시킨다.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < hidden_N[0]; j++) {
			w[i][j] += eta * delta[0][j] * x[i];
		}
	}

	//각각 레이어 사이의 w 값을 변화시키고 해당되는 bias 의 w 값을 변화시킨다.
	for (int i = 0; i < hidden - 1; i++) {
		for (int j = 0; j < hidden_N[i]; j++) {
			for (int k = 0; k < hidden_N[i + 1]; k++) {
				w_middle[i][j][k] += eta * delta[i + 1][k] * U[i][j];
			}
			w_bias[i][j] += eta * delta[i][j];
		}
	}

	//맨 마지막 줄의 바이어스 weight 를 바꿔준다.
	for (int i = 0; i < hidden_N[hidden - 1]; i++) {
		w_bias[hidden - 1][i] += eta * delta[hidden - 1][i];
	}

	//output 에서 마지막 레이어사이의 weight 값을 변화시킨다. 그리고 output 에
	// 연결되어있는 bias 의 값을 변동시킨다.
	for (int i = 0; i < output_count; i++) {
		for (int j = 0; j < hidden_N[hidden - 1]; j++) {
			w_last[i][j] += eta * last_delta[i] * U[hidden - 1][j];
		}
		w_bias_output[i] += eta * last_delta[i];
	}
}

int GridTest(double x[], double t[], int evaluation) {
	double S = 0, S_output = 0;
	double U_tmp[10][15] = { {0,}, {0,} };
	double U_last_tmp[2] = { 0, };

	//input에서 첫번째 레이어로 들어가는 w 값을 이용해 S값에서 U 값을 구한다.
	for (int i = 0; i < hidden_N[0]; i++) {
		S = 0;
		for (int j = 0; j < n; j++) {
			S += x[j] * w[j][i];
		}
		if (bias == 1) S += w_bias[0][i];

		U_tmp[0][i] = 1 / (1 + exp(-S));
	}

	//각레이어에 해당하는 u 값을 1번째 레이어의 뉴런부터 순서대로 구한다.
	for (int i = 0; i < hidden - 1; i++) {
		for (int j = 0; j < hidden_N[i + 1]; j++) {
			S = 0;
			for (int k = 0; k < hidden_N[i]; k++) {
				S += U_tmp[i][k] * w_middle[i][k][j];
			}
			if (bias == 1) S += w_bias[i + 1][j];

			U_tmp[i + 1][j] = 1 / (1 + exp(-S));
		}
	}

	//output 의 u 값을 구한다.
	for (int i = 0; i < output_count; i++) {
		S = 0;
		for (int j = 0; j < hidden_N[hidden - 1]; j++) {
			S += U_tmp[hidden - 1][j] * w_last[i][j];
		}
		if (bias == 1) S += w_bias_output[i];

		U_last_tmp[i] = 1 / (1 + exp(-S));
	}

	int y = 0;
	
	if (U_last_tmp[0] > 0.5 || fabs(U_last_tmp[0] - 0.5) < 0.000001) y = 1;
	else y = 0;

	//evaluation Test 가 아니고 격자테스트의 경우에는, y 값을 리턴한다.
	if (evaluation == 0) return y;

	//evaluation Test이면 Error의 값을 변동시키고 함수를 종료한다.
	evaErr += fabs(t[0] - U_last_tmp[0]);

	return 0;
}

//-2 ~ 2 사이의 weight 값을 리턴한다.
double rate() {
	return (double)(rand() % 40) / 10 - 2.0;
}

//weight 를 랜덤하게 세팅한다. seed 값은 1로 주었다.
void set_w(int write) {
	srand(1);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < hidden_N[0]; j++) {
			if (write) {
				fprintf(weight, "%lf\n", w[i][j]);
				printf("w[%d][%d] = %lf\n", i, j, w[i][j]);
			}
			else w[i][j] = rate();
		}
	}

	if (write) {
		fprintf(weight, "\n");
		printf("\n");
	}

	for (int i = 0; i < hidden - 1; i++) {
		for (int j = 0; j < hidden_N[i]; j++) {
			for (int k = 0; k < hidden_N[i + 1]; k++) {
				if (write) {
					fprintf(weight, "%lf\n", w_middle[i][j][k]);
					printf("w_middle[%d][%d][%d] = %lf\n", i, j, k, w_middle[i][j][k]);
				}
				else w_middle[i][j][k] = rate();
			}
		}
	}

	if (write) {
		fprintf(weight, "\n");
		printf("\n");
	}

	for (int i = 0; i < output_count; i++) {
		for (int j = 0; j < hidden_N[hidden - 1]; j++) {
			if (write) {
				fprintf(weight, "%lf\n", w_last[i][j]);
				printf("w_last[%d][%d] = %lf\n", i, j, w_last[i][j]);
			}
			else w_last[i][j] = rate();
		}
	}

	if (write) {
		fprintf(weight, "\n");
		printf("\n");
	}

	for (int i = 0; i < hidden; i++) {
		for (int j = 0; j < hidden_N[i]; j++) {
			if (write) {
				fprintf(weight, "%lf\n", w_bias[i][j]);
				printf("w_bias[%d][%d] =  %lf\n", i, j, w_bias[i][j]);
			}
			else w_bias[i][j] = rate();
		}
	}

	if (write) {
		fprintf(weight, "\n");
		printf("\n");
	}

	for (int i = 0; i < output_count; i++) {
		if (write) {
			fprintf(weight, "%lf\n", w_bias_output[i]);
			printf("w_bias_output[%d] = %lf\n", i, w_bias_output[i]);
		}
		else w_bias_output[i] = rate();
	}

	if (write) {
		fprintf(weight, "\n");
		printf("\n");
	}
}

//gridtest 를 수행하고 그 수행한 정보를 txt 파일에 저장한다.
void writeGrid(FILE* grid, double t[]) {
	for (double j = 2; j >= 0; j -= 0.05) {
		for (double i = 0; i <= 2; i += 0.05) {
			double tmp_x[10] = { i,j, };
			fprintf(grid, "%lf %lf %d\n", i, j, GridTest(tmp_x, t, 0));
		}
	}
}

int main() {
	//w값이 [15][15] 의 배열이므로 값을 설정해준다.

	FILE* errFd = fopen("error.txt", "w"), * fin = fopen("getData.txt", "r"), * grid = fopen("grid.txt", "w"),
		* grid2 = fopen("grid1000.txt", "w"), * grid3 = fopen("grid2000.txt", "w"),
		* evErrFile = fopen("evaErr.txt", "w"), * eva = fopen("evaData.txt", "r");

	weight = fopen("weight.txt", "w");

	set_w(0);

	double x[10] = { 0, }, x2 = 0, t[2] = { 0 };
	int once = 0, grid_t = 0, count1 = 0, count2 = 0, gridError = 0;

	time_t current;
	struct tm* timer;

	//getData.txt 파일에서 불러와서 3000 epoch 의 Learning을 수행한다.
	for (int i = 1; i <= 3000; i++) {
		rewind(fin); //파일을 처음부터 읽을 수 있도록 포인터를 처음으로 돌려준다.
		err = 0;
		int all = 0;
		while (fscanf(fin, "%lf %lf %lf\n", &x[0], &x[1], &t[0]) != EOF) {
			EBP(x, t);
			all++;
		}

		fprintf(errFd, "%lf\n", err / all); //1 epoch 수행결과의 에러를 error.txt 에 써준다.

		// 1000번의 연산마다 gridTest 를 수행해서 txt파일에 써준다.
		if (i % 1000 == 0 && i > 0) {
			if (i == 1000) writeGrid(grid2, t);
			if (i == 2000) writeGrid(grid3, t);
		}

		if (i % 100 == 0 && i > 0) { // evaluation 테스트를 100번마다 수행한다.
			evaErr = 0;
			rewind(eva);
			while (fscanf(eva, "%lf %lf %lf\n", &x[0], &x[1], &t[0]) != EOF) {
				//evaData.txt 파일에서 테스트 파일을 읽어와서 Error 값을 구한다.
				GridTest(x, t, 1);
			}
			//evaluation test의 Error 값을 evaErr.txt 에 적는다.
			fprintf(evErrFile, "%lf\n", evaErr / 20);
		}
	}

	fclose(errFd);

	set_w(1);

	//x,y 축 (0,2) 구간의 GridTest 를 수행한다.
	writeGrid(grid, t);

	fclose(grid);
	fclose(grid2);
	fclose(grid3);
	fclose(fin);
	fclose(evErrFile);
	fclose(eva);

	return 0;
}
