#include <stdio.h>
#include <math.h>
#include <time.h>

//각각 레이어의 수, input 의 수(n), output의 수, bias 여부, eta 여부를 설정한다.
int hidden = 4;
int n = 10;
int output_count = 2;
int bias = 1;
double eta = 0.025;

int max = 900;
int ErrCount = 0;
int WeightCount = 0;

int allLine = 2257;

//1 - 10 번째 레이어까지의 뉴런의 숫자를 설정할 수 있다.
int hidden_N[10] = { 15,15,15,15,15,15,15,15,15,15 };

double w[10][15] = { {0,}, };
double w_middle[10][15][15] = { { {0,},} , };
double w_last[2][15] = { { 0,} , };
double w_bias[10][15] = { {0,}, };
double w_bias_output[2] = { 0, };

//evaluation Error의 값과 EBP error 의 값을 저장하는 변수이다.
double err = 0, evaErr = 0;

//각각 U와 delta의 변수
double U[10][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, };
double U_last[2] = { 0 , 0 };
double delta[10][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, };
double last_delta[2] = { 0, 0 };

FILE* weightWrite, * WeightRead;

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
	return (double)(rand() % 20) / 10 - 1.0;
}

void writeChoose(int write, double * weight_tmp) {
	if (write == 1) {
		fprintf(weightWrite, "%lf\n", *weight_tmp);
	}
	else if (write == 2) {
		fscanf(WeightRead, "%lf\n", weight_tmp);
	}
	else *weight_tmp = rate();
}

//weight 를 랜덤하게 세팅한다. seed 값은 1로 주었다.
void set_w(int write) {
	srand(1);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < hidden_N[0]; j++) {
			writeChoose(write, &w[i][j]);
		}
	}

	for (int i = 0; i < hidden - 1; i++) {
		for (int j = 0; j < hidden_N[i]; j++) {
			for (int k = 0; k < hidden_N[i + 1]; k++) {
				writeChoose(write, &w_middle[i][j][k]);
			}
		}
	}

	for (int i = 0; i < output_count; i++) {
		for (int j = 0; j < hidden_N[hidden - 1]; j++) {
			writeChoose(write, &w_last[i][j]);
		}
	}

	for (int i = 0; i < hidden; i++) {
		for (int j = 0; j < hidden_N[i]; j++) {
			writeChoose(write, &w_bias[i][j]);
		}
	}

	for (int i = 0; i < output_count; i++) {
		writeChoose(write, &w_bias_output[i]);
	}
}

void getEvaRealData(FILE * fin, FILE * eva, FILE * realData) {
	double x_tmp[9], t_tmp[2];
	int randIn = 0;

	while (fscanf(fin, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &x_tmp[0], &x_tmp[1], &x_tmp[2], &x_tmp[3], &x_tmp[4],
		&x_tmp[5] , &x_tmp[6] , &x_tmp[7] , &x_tmp[8], &t_tmp[0]) != EOF) {
		if (rand() % 5 == 0 && randIn < allLine / 10) {
			fprintf(eva, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", x_tmp[0], x_tmp[1], x_tmp[2], x_tmp[3], x_tmp[4],
				x_tmp[5], x_tmp[6], x_tmp[7], x_tmp[8], t_tmp[0]);
			randIn++;
		}
		else fprintf(realData, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", x_tmp[0], x_tmp[1], x_tmp[2], x_tmp[3], x_tmp[4],
			x_tmp[5], x_tmp[6], x_tmp[7], x_tmp[8], t_tmp[0]);
	}

	fclose(realData);
	fclose(eva);
}

void getETC(FILE * architecture, FILE * parameter) {
	fscanf(architecture, "%d, %d, %d, %d, %d, %d", &n, &hidden_N[0], &hidden_N[1], &hidden_N[2], &hidden_N[3], &output_count);
	fscanf(parameter, "%lf\n%d\n%d", &eta, &ErrCount, &WeightCount);

	fclose(architecture);
	fclose(parameter);
}

//무조건 시험시작하면 
//1. TrainingData0612 몇줄인지
//2. TestData0612.txt 파일 기댓값 있는지 없는지
//3. max 몇인지
//4. outputData.dat 파일에 좌표도 넣어야하는지

//set_w 0 rand, 1이면 weight의 값을 써주는 것, 2면 파일의 w값을 설정하는 것이다.
int main() {
	//w값이 [15][15] 의 배열이므로 값을 설정해준다.
	FILE* architecture = fopen("architecture.dat", "r"), * parameter = fopen("parameter.dat", "r"),
		 *fin = fopen("TrainingData0612.txt", "r");
	FILE* eva = fopen("evaData.txt", "w"), * realData = fopen("realData.txt", "w");

	int randIn = 0, onLearning = 0, weightSelect = 0, weightNumber;

	//get evaData.txt 파일, realData.txt 파일!
	getEvaRealData(fin, eva, realData);
	realData = fopen("realData.txt", "r");
	eva = fopen("evaData.txt", "r");

	//architecture와 parameter파일에서 값을 읽어온다.
	getETC(architecture, parameter);

	printf("test(0) or 학습(1) : ");
	scanf("%d", &onLearning);

	if (onLearning == 1) {
		printf("Weight 설정 기존 데이터(0) or rand(1) : ");
		scanf("%d", &weightSelect);

		if (weightSelect == 1) {
			set_w(0); //0이면 random으로 weight 설정
		}
		else if (weightSelect == 0) {
			printf("Weight를 설정하세요! : ");
			scanf("%d", &weightNumber);

			//입력한 epoch 번째의 weight 를 읽어오고
			char tmp[200];
			sprintf(tmp, "C:\\Users\\dkrle\\source\\repos\\ML_test\\ML_test\\weight\\weight%d.dat", weightNumber);
			WeightRead = fopen(tmp, "r");
			
			set_w(2); //읽어온 weight 로 초기화한다.

			//test를 위해서 맨처음의 weight 값을 기록한다.
			weightWrite = fopen("match.dat", "w");
			set_w(1); //write를 해줄때는 1번이다.

			fclose(weightWrite);
			fclose(WeightRead);
		}
	}
	else if (onLearning == 0) {
		printf("Test할 Weight를 입력하세요! : ");
		scanf("%d", &weightNumber);

		char tmp[200];
		sprintf(tmp, "C:\\Users\\dkrle\\source\\repos\\ML_test\\ML_test\\weight\\weight%d.dat", weightNumber);

		WeightRead = fopen(tmp, "r");

		set_w(2); //weight 를 읽어온 weight 로 설정한다.

		fclose(WeightRead);
	}

	double x[10] = { 0, }, x2 = 0, t[2] = { 0 };
	time_t current;
	struct tm* timer;

	if (onLearning == 1) {
		FILE* errFd = fopen("error.dat", "w");

		for (int i = 1; i <= max; i++) {
			rewind(realData); //파일을 처음부터 읽을 수 있도록 포인터를 처음으로 돌려준다.
			err = 0;
			int all = 0;
			while (fscanf(realData, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5],
				&x[6], &x[7], &x[8],&t[0]) != EOF){
				EBP(x, t);
				all++;
			}

			current = time(NULL);
			timer = localtime(&current);

			if (i % ErrCount == 0) {
				fprintf(errFd, "%d %lf %d:%d:%d:%d:%d:%d\n", i, err / all, timer->tm_year + 1900, timer->tm_mon + 1, timer->tm_mday,
					timer->tm_hour, timer->tm_min, timer->tm_sec); //1 epoch 수행결과의 에러를 error.txt 에 써준다.
			}

			if (i % WeightCount == 0) { 
				char WeightFileName[200];
				sprintf(WeightFileName, "C:\\Users\\dkrle\\source\\repos\\ML_test\\ML_test\\weight\\weight%d.dat", i);

				weightWrite = fopen(WeightFileName, "w");
				set_w(1);

				fclose(weightWrite);
			}
		}

		fclose(errFd);
	}
	else if (onLearning == 0) { //Test! 수행 Eva Data 와 각 Weight로 수행
		FILE* testData = fopen("TestData0612.txt", "r"), * outputData = fopen("output.dat", "w");

		//기댓값 있으면 %lf 및 ,&t[0] 추가!
		while (fscanf(testData, "%lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &x[0], &x[1], &x[2], &x[3], &x[4],
			&x[5], &x[6], &x[7], &x[8]) != EOF) {
			//fprintf(outputData, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %d\n", x[0], x[1], x[2], x[3], x[4],
			//	x[5], x[6], x[7], x[8], GridTest(x, t, 0));
			fprintf(outputData, "%d\n", GridTest(x, t, 0));
		}

		fclose(outputData);
		fclose(testData);
	}

	FILE* evErrFile = fopen("evaErr.txt", "w");

	for (int i = WeightCount; i <= max; i += WeightCount) {

		char WeightFileName[200];
		sprintf(WeightFileName, "C:\\Users\\dkrle\\source\\repos\\ML_test\\ML_test\\weight\\weight%d.dat", i);

		WeightRead = fopen(WeightFileName, "r");

		set_w(2);

		fclose(WeightRead);

		rewind(eva);
		evaErr = 0;
		while (fscanf(eva, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &x[0], &x[1], &x[2], &x[3], &x[4],
			&x[5], &x[6], &x[7], &x[8], &t[0]) != EOF) {
			//evaData.txt 파일에서 테스트 파일을 읽어와서 Error 값을 구한다.
			GridTest(x, t, 1);
		}
		fprintf(evErrFile, "%d %lf\n", i, evaErr / (allLine / 10));
	}

	fclose(eva);
	fclose(realData);
	fclose(fin);
	fclose(evErrFile);

	return 0;
}
