#include <stdio.h>
#include <math.h>
#define epoch 1000
#define extract_num 60
#define stride 1

int bias=0;
int fisrt_layer_num=0;
int second_layer_num=0;
double eta=0.4;

double u[2][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

double w[2][15] = { {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
						{-1.51, -1.42, -1.33, -1.21, -1.114, -1.01, -0.93,-0.18, -0.71, -0.63, -0.51, -1.61, -1.7, -1.8, -1.9} };

double hidden_weight[15][15] = { {1.1, 1.2, 1.3, 1.4, 0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.1, 1.2, 1.3, 1.4, 1.5},
						{ -0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.95},
					{-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},};

double last_weight[15] = {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9 };

double w_bias_output = 0;

double bias_weight[2][15] = { {-2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6},
						{-2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6} };

double delta[2][15] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
double u_last= 0;
double last_delta = 0;
double u_last_temp= 0;


double w_temp[2][15] = { {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
						{-1.51, -1.42, -1.33, -1.21, -1.114, -1.01, -0.93,-0.18, -0.71, -0.63, -0.51, -1.61, -1.7, -1.8, -1.9} };

double hidden_weight_temp[15][15] = { {1.1, 1.2, 1.3, 1.4, 0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.1, 1.2, 1.3, 1.4, 1.5},
						{ -0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.95},
					{-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},};

double last_weight_temp[15] = {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9 };
double w_bias_output_temp = 0;
double bias_weight_temp[2][15] = { {-2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6},
						{-2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6, -2.0, -1.9, -1.8, -1.7, -1.6} };



void Show_weight(){
		for(int i = 0; i <fisrt_layer_num; i++){
		printf("W%d%d : %lf\n", i + 3, 0, bias_weight[0][i]);
		printf("W%d%d : %lf\n", i + 3, 1, w[0][i]);
		printf("W%d%d : %lf\n", i + 3, 2, w[1][i]);
	}

	for (int i = 0; i < fisrt_layer_num; i++) {
		printf("W%d%d : %lf\n",fisrt_layer_num + 3 + i, 0, bias_weight[0][i]);
		for (int j = 0; j <second_layer_num; j++) {
			printf("W%d%d : %lf\n",fisrt_layer_num + 3 + i, j + 3,hidden_weight[i][j]);
		}
	}
	
	for (int i = 0; i < second_layer_num; i++) {
		printf("W%d,%d : %lf\n", fisrt_layer_num + second_layer_num + 3,fisrt_layer_num + 3 + i,  last_weight[i]);
	}
}


void FeedForward(double x1, double x2, double t){
	double S = 0, S_output = 0; 
	double S_middle[15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	//input 
	for (int i = 0; i <fisrt_layer_num; i++) {
		S = x1* w[0][i] + x2 * w[1][i];
		if(bias == 1) S += bias_weight[0][i]; 

		//find u
		u[0][i] = 1 / (1 + exp(-S));
	}

	for (int i = 0; i <second_layer_num; i++) {
		for (int j = 0; j < fisrt_layer_num; j++) {
			//find sum of middle
			S_middle[i] += u[0][j] * hidden_weight[j][i];
		}

		if (bias == 1) S_middle[i] +=bias_weight[1][i];
		
		u[1][i] = 1 / (1 + exp(-S_middle[i]));
		S_output += u[1][i]*last_weight[i];
	}

	if (bias == 1) S_output += w_bias_output;
	
	u_last = 1 / (1 + exp(-S_output));

}


void FeedBackward(double x1, double x2, double t){
//last layer delta finding
last_delta = (t - u_last) * u_last* (1 - u_last);

	//middle layer 
	for (int i = 0; i <second_layer_num; i++) {
		delta[1][i]=u[1][i]*(1-u[1][i])*last_delta*last_weight[i];
	}
	
	for (int i = 0; i <fisrt_layer_num; i++){
		double delta_sum= 0;
		for (int j = 0; j <second_layer_num; j++){
			delta_sum += delta[1][j]*hidden_weight[i][j];
		}
		delta[0][i] = u[0][i] * (1 - u[0][i]) *delta_sum;
	}

	//weight update
	for (int i = 0; i <fisrt_layer_num; i++) {
		for (int j = 0; j <second_layer_num; j++) {
			hidden_weight[i][j] += eta * delta[1][j] * u[0][i];
		}
		w[0][i]+=eta*delta[0][i]*x1;
		w[1][i]+=eta*delta[0][i]*x2;
		bias_weight[0][i]+=eta*delta[0][i];
	}

	for (int i = 0; i <second_layer_num; i++) {
		last_weight[i] += eta * last_delta * u[1][i];
		bias_weight[1][i] += eta * delta[1][i];
	}

	//output weight bias change
	w_bias_output += eta * last_delta;
}


void ErrorBackPropagate(double x1, double x2, double t) {
	FeedForward(x1,x2,t);
 	FeedBackward(x1,x2,t);	
}

void Change_weight() {
	printf("weight chage begin\n");
		for (int i = 3; i < fisrt_layer_num; i++) {
			for (int j = 0; j <second_layer_num; j++) {
				hidden_weight[i][j] = hidden_weight[i % 2 + 1][j] + (0.03 * (i % 5));
			}
		}
}

void ChooseMode(){
    printf("choose mode 1:with bias 2:without bias\n");
    scanf("%d",&bias);
    if(bias==1){
        printf("with bias\n");
    }else{
        printf("without bias\n");
    }
}

void Choose_fisrt_layer_num(){
    printf("choose the number of fisrt_layer_nun\n");
    scanf("%d",&fisrt_layer_num);
    printf("fisrt_layer_num:%d\n",fisrt_layer_num);
}

void Choose_second_layer_num(){
    printf("choose the number of _second_layer_num\n");
    scanf("%d",&second_layer_num);
    printf("_second_layer_num:%d\n",second_layer_num);
}

void Choose_eta(){
    printf("choose the size of eta \n");
    scanf("%lf",&eta);
    printf("eta: %lf\n",eta);
}

void memoize_weight(){
		for(int i = 0; i <fisrt_layer_num; i++){
		//printf("W%d%d : %lf\n", i + 3, 0, bias_weight[0][i]);
		//printf("W%d%d : %lf\n", i + 3, 1, w[0][i]);
		//printf("W%d%d : %lf\n", i + 3, 2, w[1][i]);
		bias_weight_temp[0][i]=bias_weight[0][i];
		w_temp[0][i]=w[0][i];
		w_temp[1][i]=w[1][i];
	}

	for (int i = 0; i < fisrt_layer_num; i++) {
		bias_weight_temp[0][i]=bias_weight[0][i];
		for (int j = 0; j <second_layer_num; j++) {
			hidden_weight_temp[i][j]=hidden_weight[i][j];
		}
	}
	
	for (int i = 0; i < second_layer_num; i++) {
		last_weight_temp[i]=last_weight[i];
	}
}

void Show_temp_weight(){
		for(int i = 0; i <fisrt_layer_num; i++){
		printf("W_temp%d%d : %lf\n", i + 3, 0, bias_weight_temp[0][i]);
		printf("W_temp%d%d : %lf\n", i + 3, 1, w_temp[0][i]);
		printf("W_temp%d%d : %lf\n", i + 3, 2, w_temp[1][i]);
	}

	for (int i = 0; i < fisrt_layer_num; i++) {
		printf("W_temp%d%d : %lf\n",fisrt_layer_num + 3 + i, 0, bias_weight_temp[0][i]);
		for (int j = 0; j <second_layer_num; j++) {
			printf("W_temp%d%d : %lf\n",fisrt_layer_num + 3 + i, j + 3,hidden_weight_temp[i][j]);
		}
	}

	for (int i = 0; i < second_layer_num; i++) {
		printf("W_temp%d,%d : %lf\n", fisrt_layer_num + second_layer_num + 3,fisrt_layer_num + 3 + i,  last_weight_temp[i]);
	}
}


void tempweight_to_weight(){
		for(int i = 0; i <fisrt_layer_num; i++){
		bias_weight[0][i]=bias_weight_temp[0][i];
		w[0][i]=w_temp[0][i];
		w[1][i]=w_temp[1][i];
	}

	for (int i = 0; i < fisrt_layer_num; i++) {
		bias_weight[0][i]=bias_weight_temp[0][i];
		for (int j = 0; j <second_layer_num; j++) {
			hidden_weight[i][j]=hidden_weight_temp[i][j];
		}
	}

	
	for (int i = 0; i < second_layer_num; i++) {
		last_weight[i]=last_weight_temp[i];
	}
}



int main() {

	ChooseMode();
	Change_weight();
	Choose_fisrt_layer_num();
	Choose_second_layer_num();
	Choose_eta();
	double x1 = 0, x2 = 0, t = 0;
	int cnt=0;
	
	//extract val_data
  	FILE* valdata =fopen("valdata.txt", "w");
	FILE* input = fopen("input.txt","r");
	while (fscanf(input, "%lf %lf %lf\n", &x1, &x2, &t) != EOF) {
		if(cnt<extract_num){
			fprintf(valdata,"%lf %lf %lf\n",x1,x2,t); 
		}
		cnt++;
	}
	fclose(valdata);
	fclose(input);
  	//extract end
   
	//training function
	double error = 0;
	double val_x1,val_x2,val_t=0;
	double val_err=0;
	FILE* err_epoch = fopen("error.txt", "w");
	double min_val_error=10000;
	int min_epoch=0;
	int skip=0;

	for (int i = 0; i <=epoch; i++) {
		FILE* input = fopen("input.txt", "r");
		error=0;
		skip=0;

		while (fscanf(input, "%lf %lf %lf\n", &x1, &x2, &t) != EOF) {
			if(skip>extract_num){
				ErrorBackPropagate(x1, x2, t);
				error =error+fabs(t-u_last);
			}
			skip++;
		}	
		fclose(input);

		if(i%stride==0){
			valdata =fopen("valdata.txt", "r");
			double val_error;
			val_err=0;
			while (fscanf(valdata,"%lf %lf %lf\n",&val_x1,&val_x2,&val_t) != EOF) {
				FeedForward(val_x1,val_x2,val_t);
				val_err=val_err+fabs(val_t-u_last);
			}
			printf("val_err:%lf\n",val_err);
			if(min_val_error>val_err){
				min_val_error=val_err;
				min_epoch=i;
				//copy weight data
				memoize_weight();
				FILE* val_grid = fopen("val_gird.txt", "w");
				valdata =fopen("valdata.txt", "r");
				while (fscanf(valdata,"%lf %lf %lf\n",&val_x1,&val_x2,&val_t) != EOF) {
					FeedForward(val_x1,val_x2,val_t);
					if(u_last>0.5){
						fprintf(val_grid,"%lf %lf %d\n",val_x1,val_x2,1);
					}
					else{
					 	fprintf(val_grid,"%lf %lf %d\n",val_x1,val_x2,0);
					}
				}

				fclose(val_grid);
			}
		fclose(valdata);	
		}
		fprintf(err_epoch , "%d %lf\n", i,error);		
	}
	fclose(err_epoch);
	//training end

	tempweight_to_weight();

	printf("min _epoch:%d\n",min_epoch);

	//grid test
	FILE *gridtest = fopen("grid.txt", "w");
	
	int val_count=0;

	if(gridtest==NULL){
        printf("haha file open failed\n");
    }


 	for(double i=-2.0;i<3.0;i=i+0.1){ 
        for(double j=-2.0;j<3.0;j=j+0.1){
            FeedForward(i,j,0);
            if(u_last>0.5){ 
                fprintf(gridtest,"%lf %lf %d\n",i,j,1);
            }
            else{
                fprintf(gridtest,"%lf %lf %d\n",i,j,0);
            }
        }
    }   
    fclose(gridtest);
	
	return 0;
}
