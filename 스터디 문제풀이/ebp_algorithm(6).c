#include <stdio.h>
#include <math.h>
#define w_range 10
#define bias 1
#define eta 0.9

//위에서 w_range 의 변수 값으로 뉴런의 갯수를 정할 수 있다. bias 는 포함여부를 1(하는 것)과 0(안하는 것)으로 나타낸다. 
//eta 값 또한 위에서 설정한다.

//w값을 임의로 설정했다. 
double w1_input[10] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4 };
double w2_input[10] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4 };
double w_output[10] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4 };
double w_bias[11] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5};

//U의 값은 w 의 값에서 파생되는 값으로 초기 설정값이 무관한 값이므로 0으로 놓는다.
double U[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double delta[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

double err = 0;

void EBP(double x1, double x2, double t) {
	double S = 0, S_output = 0; 
	//input 에서 중간 레이어로의 w 값을 구한다.
	for (int i = 0; i < w_range; i++) {
		S = x1* w1_input[i] + x2 * w2_input[i];
		if(bias == 1) S += w_bias[i]; //바이어스를 사용할 경우에만 바이어스 값을 S에 더해준다.

		//중간레이어의 각 S 값을 토대로 각각의 U 값을 구한다.
		U[i] = 1 / (1 + exp(-S));

		//구한 U 값을 토대로 출력단의 S 값을 구한다.
		S_output += U[i] * w_output[i];
	}

	//바이어스를 입력할 경우에만 출력단의 S 값에 바이어스의 w값을 더해준다.
	if (bias == 1) S_output += w_bias[w_range];
	
	//구한 출력단의 S값으로 출력단의 U 값을 구한다.
	U[w_range] = 1 / (1 + exp(-S_output));
	
	//error 값을 한 epoch(50번)로 줘야하기 때문에 += 을 사용해서 50번을 더해준다.
	err += fabs(t - U[w_range]);

	//구한 U 값과 들어온 t 값을 토대로 출력단의 delta 값을 구한다.
	delta[w_range] = (t - U[w_range]) * U[w_range] * (1 - U[w_range]);

	//출력단의 delta 값을 토대로 중간 레이어의 각각에 해당하는 delta 값을 구한다.
	for (int i = w_range - 1; i >= 0; i--) {
		delta[i] = U[i] * (1 - U[i]) * delta[w_range] * w_output[i];
	}

	//구한 델타의 값으로 모든 w의 변화량을 더해준다.
	for (int i = 0; i < w_range; i++) {
		w_output[i] = w_output[i] + eta * delta[w_range] * U[i];
		w1_input[i] = w1_input[i] + eta * delta[i] * x1;
		w2_input[i] = w2_input[i] + eta * delta[i] * x2;
		w_bias[i] = w_bias[i] + eta * delta[i];
	}

	//출력단에 연결된 bias의 w 값의 변화량도 더해준다.
	w_bias[w_range] += eta * delta[w_range];
}

int GridTest(double x1, double x2) {
	double S = 0, S_output = 0;
	double U_tmp[11] = { 0,0,0,0,0,0,0,0,0,0,0 };

	//x1,x2 와 학습을 통해 구한 w 의 값으로 S 값을 구하고 그 값에 해당하는 U 값을 구한다.
	//한 격자에 대한 테스트이기 때문에 전역변수 U가 아닌, U_tmp 라는 배열을 따로 함수에 선언해서 사용한다.
	for (int i = 0; i < w_range; i++) {
		if (bias == 1) S = x1 * w1_input[i] + x2 * w2_input[i] + w_bias[i];
		else S = x1 * w1_input[i] + x2 * w2_input[i];

		U_tmp[i] = 1 / (1 + exp(-S));
	}

	//출력단의 S 값 구한다.
	for (int i = 0; i < w_range; i++) {
		S_output += U_tmp[i] * w_output[i];
	}

	//바이어스가 있을 시에 바이어스 값도 S값에 더해준다.
	if (bias == 1) S_output += w_bias[w_range];

	//그 값으로 출력단의 U를 구한다.
	U_tmp[w_range] = 1 / (1 + exp(-S_output));
	
	//U 값이 0.5 보다 크거나 같을 경우에는 1을 리턴하고 그렇지 않을 경우 0을 리턴한다
	if (U_tmp[w_range] > 0.5 || fabs(U_tmp[w_range] - 0.5) < 0.000001) return 1;
	else return 0;
}


int main() {
	//에러값을 써줄 파일과, 학습시킬 인풋데이터를 넣은 파일, 격자테스트를 해서 결과값을 저장할 파일을 open 한다.
	FILE* errFd = fopen("error.txt", "w"), *fin = fopen("fin.txt", "r"), *grid = fopen("grid.txt", "w");	

	double x1 = 0, x2 = 0, t = 0;
	int once = 0, grid_t = 0, count1 = 0, count2 = 0, gridError = 0;

	//fin.txt 파일에서 테스트 값을 읽어와 200번의 epoch만큼을 가르친다.
	for (int i = 0; i < 200; i++) {
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
	for(int i = 0; i < w_range; i++){
		printf("W%d%d : %lf\n", i + 3, 0, w_bias[i]);
		printf("W%d%d : %lf\n", i + 3, 1, w1_input[i]);
		printf("W%d%d : %lf\n", i + 3, 2, w2_input[i]);;
	}

	//위의 중간 layer 로 들어오는 w 값을 출력한 이후에 output 쪽에 연결된 w 값을 출력한다.
	for (int i = 0; i < w_range; i++) {
		printf("W%d,%d : %lf\n", w_range + 3, i + 3, w_output[i]);
	}

	//격자테스트를 수행한다. 범위는 x축 -2 to 3, y축 -3 to 2 이다. 0.5 를 구간으로 한다.
	//출력은 각 좌표와 그에 해당하는 연산을 수행했을 때의 결과 값이다.
	for (double j = 2; j >= -3; j -= 0.5) {
		for (double i = -2; i <= 3; i += 0.5) {
			fprintf(grid,"%lf %lf %d\n", i, j,GridTest(i, j));
		}
	}

	fclose(grid);

	FILE* gridCheck = fopen("grid.txt", "r");

	// 격자테스트를 했을 때 값이 제대로 나오는지 확인한다. 그리고 error 값이 있는 해당 좌표를 출력한다.
	while (fscanf(gridCheck, "%lf %lf %d\n", &x1, &x2, &grid_t) != EOF) {
		if (x2 >= -0.5 && x1 - x2 >= -1 && x1 + x2 <= 2 && grid_t == 1) {}
		else if (grid_t == 1) {
			if (once == 0) { //1번만 Wrong...! 을 출력하도록 한다.
				printf("\nWrong...!\n");
				once = 1;
			}
			gridError++;	
			printf("x1 : %lf, x2 : %lf, t : %d", x1, x2, t);
		}
		else if (x2 >= -0.5 && x1 - x2 >= -1 && x1 + x2 <= 2 && grid_t == 0) {
			if (once == 0) {
				printf("\nWrong...!\n");
				once = 1;
			}
			gridError++;
			printf("x1 : %lf, x2 : %lf, t : %d", x1, x2, t);
		}
	}

	//격자테스트 후 전체 error 의 갯수를 출력한다.
	printf("grid error : %d\n", gridError);

	fclose(gridCheck);
	fclose(fin);

	return 0;
}
