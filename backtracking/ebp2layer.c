#include <stdio.h>
#include <math.h>
#define w_first 3
#define w_second 15
#define bias 1
#define eta 0.2

//위에서 w_range 의 변수 값으로 뉴런의 갯수를 정할 수 있다. 
//bias 는 포함여부를 1(하는 것)과 0(안하는 것)으로 나타낸다. 
//eta 값 또한 위에서 설정한다.

//w값을 임의로 설정했다. 
double w[2][15] = { {1.5, 1.4, 1.3, 1.2, 1.1, 1.5, 1.4, 1.3, 1.2, 1.1, 1.5, 1.4, 1.3, 1.2, 1.1},
						{-1.5, -1.4, -1.3, -1.2, -1.1, -1.0, -0.9,-0.8, -0.7, -0.6, -0.5, -1.6, -1.7, -1.8, -1.9} };
double w_middle[15][15] = { {1.1, 1.2, 1.3, 1.4, 1.5, 1.1, 1.2, 1.3, 1.4, 1.5, 1.1, 1.2, 1.3, 1.4, 1.5},
						{ -1.1, -1.2, -1.3, -1.4, -1.5, -1.1, -1.2, -1.3, -1.4, -1.5, -1.1, -1.2, -1.3, -1.4, -1.5},
					{1.5, 1.4, 1.3, 1.2, 1.1, 1.5, 1.4, 1.3, 1.2, 1.1, 1.5, 1.4, 1.3, 1.2, 1.1},};
double w_last[15] = { 0.5, -0.4, 0.3, -0.2, 0.1, -0.2, -0.3, 0.4, -0.5, 0.6, -0.7, 0.8, -0.9, 1.0, -1.1 };
double w_bias[2][15] = { {-2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6},
						{-2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6} };
double w_bias_output = -3;
//U의 값은 w 의 값에서 파생되는 값으로 초기 설정값이 무관한 값이므로 0으로 놓는다.
double U[2][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
double last_U = 0;

double delta[2][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
double last_delta = 0;

double err = 0;

void EBP(double x1, double x2, double t) {
	double S = 0, S_output = 0; 
	double S_middle[15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	//input 에서 중간 레이어로의 w 값을 구한다.
	for (int i = 0; i < w_first; i++) {
		S = x1* w[0][i] + x2 * w[1][i];
		if(bias == 1) S += w_bias[0][i]; //바이어스를 사용할 경우에만 바이어스 값을 S에 더해준다.

		//중간레이어의 각 S 값을 토대로 각각의 U 값을 구한다.
		U[0][i] = 1 / (1 + exp(-S));
	}

	for (int i = 0; i < w_second; i++) {
		for (int j = 0; j < w_first; j++) {
			//구한 U 값을 토대로 출력단의 S 값을 구한다.
			S_middle[i] += U[0][j] * w_middle[j][i];
		}
		//바이어스를 입력할 경우에만 출력단의 S 값에 바이어스의 w값을 더해준다.
		if (bias == 1) S_middle[i] += w_bias[1][i];
		
		U[1][i] = 1 / (1 + exp(-S_middle[i]));
		S_output += U[1][i] * w_last[i];
	}

	if (bias == 1) S_output += w_bias_output;
	
	last_U = 1 / (1 + exp(-S_output));

	//error 값을 한 epoch(50번)로 줘야하기 때문에 += 을 사용해서 50번을 더해준다.
	err += fabs(t - last_U);

	//구한 U 값과 들어온 t 값을 토대로 출력단의 delta 값을 구한다.
	last_delta = (t - last_U) * last_U * (1 - last_U);

	//출력단의 delta 값을 토대로 중간 레이어의 각각에 해당하는 delta 값을 구한다.
	for (int i = 0; i < w_second; i++) {
		delta[1][i] = U[1][i] * (1 - U[1][i]) * last_delta * w_last[i];
	}
	
	for (int i = 0; i < w_first; i++){
		double allDelta = 0;
		for (int j = 0; j < w_second; j++){
			allDelta += delta[1][j] * w_middle[i][j];
		}
		delta[0][i] = U[0][i] * (1 - U[0][i]) * allDelta;
	}

	//구한 델타의 값으로 모든 w의 변화량을 더해준다.
	for (int i = 0; i < w_first; i++) {
		for (int j = 0; j < w_second; j++) {
			w_middle[i][j] += eta * delta[1][j] * U[0][i];
		}
		w[0][i] += eta * delta[0][i] * x1;
		w[1][i] += eta * delta[0][i] * x2;
		w_bias[0][i] += eta * delta[0][i];
	}

	for (int i = 0; i < w_second; i++) {
		w_last[i] += eta * last_delta * U[1][i];
		w_bias[1][i] += eta * delta[1][i];
	}

	//출력단에 연결된 bias의 w값의 변화량도 더해준다.
	w_bias_output += eta * last_delta;
}

/*
int GridTest(double x1, double x2) {
	double S = 0, S_output = 0;
	double U_tmp[11] = { 0,0,0,0,0,0,0,0,0,0,0 };
	//x1,x2 와 학습을 통해 구한 w 의 값으로 S 값을 구하고 그 값에 해당하는 U 값을 구한다.
	//한 격자에 대한 테스트이기 때문에 전역변수 U가 아닌, U_tmp 라는 배열을 따로 함수에 선언해서 사용한다.
	for (int i = 0; i < w_first; i++) {
		if (bias == 1) S = x1 * w1_input[i] + x2 * w2_input[i] + w_bias[i];
		else S = x1 * w1_input[i] + x2 * w2_input[i];
		U_tmp[i] = 1 / (1 + exp(-S));
	}
	//출력단의 S 값 구한다.
	for (int i = 0; i < w_first; i++) {
		S_output += U_tmp[i] * w_output[i];
	}
	//바이어스가 있을 시에 바이어스 값도 S값에 더해준다.
	if (bias == 1) S_output += w_bias[w_first];
	//그 값으로 출력단의 U를 구한다.
	U_tmp[w_first] = 1 / (1 + exp(-S_output));
	
	//U 값이 0.5 보다 크거나 같을 경우에는 1을 리턴하고 그렇지 않을 경우 0을 리턴한다
	if (U_tmp[w_range] > 0.5 || fabs(U_tmp[w_range] - 0.5) < 0.000001) return 1;
	else return 0;
}
*/

void set_w() {
	if (w_first > 3) {
		for (int i = 3; i < w_first; i++) {
			printf("%d, ", i);
			for (int j = 0; j < w_second; j++) {
				w_middle[i][j] = w_middle[i % 2 + 1][j] + (0.05 * (i % 5));
				printf("%.2f ", w_middle[i][j]);
			}
			printf("\n");
		}
	}
}

int main() {

	set_w();

	//에러값을 써줄 파일과, 학습시킬 인풋데이터를 넣은 파일, 격자테스트를 해서 결과값을 저장할 파일을 open 한다.
	FILE* errFd = fopen("error.txt", "w"), *fin = fopen("fin.txt", "r"), *grid = fopen("grid.txt", "w");	

	double x1 = 0, x2 = 0, t = 0;
	int once = 0, grid_t = 0, count1 = 0, count2 = 0, gridError = 0;

	//fin.txt 파일에서 테스트 값을 읽어와 200번의 epoch만큼을 가르친다.
	for (int i = 0; i < 400; i++) {
		rewind(fin);
		err = 0;
		while (fscanf(fin, "%lf %lf %lf\n", &x1, &x2, &t) != EOF) {
			EBP(x1, x2, t);
		}
		//각 epoch 마다의 error 값을 기록한다.
		fprintf(errFd, "%lf\n", err);
	}

	fclose(errFd);

	//w30 w31 w32 w40 w41 w42 순으로 될 수 있도록 값을 출력한다.
	for(int i = 0; i < w_first; i++){
		printf("W%d%d : %lf\n", i + 3, 0, w_bias[0][i]);
		printf("W%d%d : %lf\n", i + 3, 1, w[0][i]);
		printf("W%d%d : %lf\n", i + 3, 2, w[1][i]);
	}

	for (int i = 0; i < w_first; i++) {
		printf("W%d%d : %lf\n", w_first + 3 + i, 0, w_bias[0][i]);
		for (int j = 0; j < w_second; j++) {
			printf("W%d%d : %lf\n", w_first + 3 + i, j + 3, w_middle[i][j]);
		}
	}

	//위의 중간 layer 로 들어오는 w 값을 출력한 이후에 output 쪽에 연결된 w 값을 출력한다.
	for (int i = 0; i < w_second; i++) {
		printf("W%d,%d : %lf\n", w_first + w_second + 3, w_first + 3 + i, w_last[i]);
	}

	//격자테스트를 수행한다. 범위는 x축 -2 to 3, y축 -3 to 2 이다. 0.5 를 구간으로 한다.
	//출력은 각 좌표와 그에 해당하는 연산을 수행했을 때의 결과 값이다.
	/*
	for (double j = 2; j >= -3; j -= 0.5) {
		for (double i = -2; i <= 3; i += 0.5) {
			fprintf(grid,"%lf %lf %d\n", i, j,GridTest(i, j));
		}
	}
	*/

	/*
	fclose(grid);
	FILE* gridCheck = fopen("grid.txt", "r");
	// 격자테스트를 했을 때 값이 제대로 나오는지 확인한다. 
	//그리고 error 값이 있는 해당 좌표를 출력한다.
	while (fscanf(gridCheck, "%lf %lf %d\n", &x1, &x2, &grid_t) != EOF) {
		if (x2 >= -0.5 && x1 - x2 >= -1 && x1 + x2 <= 2 && grid_t == 1) {}
		else if (grid_t == 1) {
			if (once == 0) { //1번만 Wrong...! 을 출력하도록 한다.
				printf("\nWrong...!\n");
				once = 1;
			}
			gridError++;	
			printf("x1 : %lf, x2 : %lf, t : %d\n", x1, x2, t);
		}
		else if (x2 >= -0.5 && x1 - x2 >= -1 && x1 + x2 <= 2 && grid_t == 0) {
			if (once == 0) {
				printf("\nWrong...!\n");
				once = 1;
			}
			gridError++;
			printf("x1 : %lf, x2 : %lf, t : %d\n", x1, x2, t);
		}
	}
	//격자테스트 후 전체 error 의 갯수를 출력한다.
	printf("grid error : %d\n", gridError);
	fclose(gridCheck);
	*/
	fclose(fin);


	return 0;
}
