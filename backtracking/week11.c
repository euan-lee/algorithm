#include <stdio.h>
#include <math.h>
#define eta 0.5
#define epoch 1000

int fisrt_layer_num=0;

int second_layer_num=0;

double first_weight[2][15]={
    {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
    {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9}
};

double hidden_weight[15][15]={
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9},
   {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9}
};

double last_weight[15][1]={{-0.5},{-0.4},{-0.3},{-0.2},{-0.1},{0.1},{0.2},{0.3},{0.4},{0.5},{0.6},{0.7},{0.8},{0.9},{1.0}};    

double bias_input[15]= {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9};

double bias_first[15]= {-0.5,-0.4,-0.3,-0.2,-0.1,0, 0.1, 0.2, 0.3,0.4,0.5,0.6,0.7,0.8,0.9};

double bias_second=-0.5;

int bias=0;

double U[2][15]=  {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

double U_last=0;

double delta[3][15]={{0,},{0,},{0,}};//[layer][neuron_number]



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
double Sigmoid(double sum){
    double result=0;
    result=1/(1 + exp(-sum));
      return result;
}

void FeedForward(double x1,double x2,double target){
 
    //x1,x2와 first weight로 u[0][0]~u[0][15]까지 구하기(ok)
    double sum=0;
    for(int i=0;i<fisrt_layer_num;i++){
        sum=x1*first_weight[0][i]+x2*first_weight[1][i];
        
        if(bias==1){
            sum=sum+bias_input[i];
        }

       U[0][i]=Sigmoid(sum);
    }

    
    //u[1][0]~u[1][second_layer_num]까지 구한다.(ok)
    double sum2=0;
   for(int i=0;i<second_layer_num;i++){
       for(int j=0;j<fisrt_layer_num;j++){
            sum2=sum2+U[0][j]*hidden_weight[j][i];//1레이어의 j번째 뉴런*hidden weight[j][i]      
       }
       if(bias==1){
           sum2=sum2+bias_first[i];
       }
       U[1][i]=Sigmoid(sum2);
   }

   //last layer 구하기(ok)
    double sum3=0;
    for(int k=0;k<second_layer_num;k++){
        sum3=sum3+U[1][k]*last_weight[k][0];
    }
    if(bias==1){
        sum3=sum3+ bias_second;
    }

    U_last=Sigmoid(sum3);

}

void FeeBackward(double x1,double x2,double target){

    //last delta (ok)
    delta[2][0]=(target-U_last)*U_last*(1-U_last);

    //last-1 delta(ok)
    for(int i=0;i<second_layer_num;i++){
        delta[1][i]=U[1][i]*delta[2][0]*last_weight[i][0];
    }

    //last-2 delta(ok)
    for(int i=0;i<fisrt_layer_num;i++){
        double delta_sum = 0;
      
        for(int j=0;j<second_layer_num;j++){
            delta_sum+=delta[1][j]*hidden_weight[i][j];
        }

        delta[0][i]=U[0][i]*(1-U[0][i])*delta_sum;
    }

   //first layer weight update()
    for(int i=0;i<fisrt_layer_num;i++){
        first_weight[0][i]=first_weight[0][i]+eta*x1*delta[0][i];
        first_weight[1][i]=first_weight[1][i]+eta*x2*delta[0][i];
    }

    if(bias==1){
        for(int i=0;i<fisrt_layer_num;i++){
           bias_input[i]=bias_input[i]+eta*1*delta[0][i];
        }    
    }

   //second layer weight update()
    
    for(int i=0;i<fisrt_layer_num;i++){
        for (int j = 0; j <second_layer_num; j++){
        hidden_weight[i][j]=hidden_weight[i][j]+eta*U[0][i]* delta[1][j];
        }
    }
     //second layer bias weight update()
    if(bias==1){
        for(int i=0;i<second_layer_num;i++){
           bias_first[i]= bias_first[i]+eta*1*delta[1][i];
        } 
    }


     //last layer weight update()
    for(int i=0;i<second_layer_num;i++){
        last_weight[i][1]=last_weight[i][1]+eta*delta[2][0]*U[1][i];
    }
    if(bias==1){
        bias_second= bias_second+delta[2][0]*eta*1;
    }
}



void Error_back_propagation(double x1,double x2,double target){
   FeedForward(x1,x2,target);
   FeeBackward(x1,x2,target);
};



int main(){

    double error=0;
    double x1,x2,target=0;
    ChooseMode();
    Choose_fisrt_layer_num();
    Choose_second_layer_num();

    //function fitting
     FILE *fp2 = fopen("result.txt","w"); 
    for(int i=0;i<epoch;i++){  
        FILE *fp = fopen("data.txt","r");     
        error=0;
        
        if(fp == NULL){
            printf("file open failed\n");
        }

        while(!((fscanf(fp, "%lf %lf %lf \n",&x1,&x2,&target))==EOF)){
            Error_back_propagation(x1,x2,target);
            error=error+fabs(target-U_last);
        }
        fclose(fp);   
        fprintf(fp2, "%d %lf\n",i,error);
    }   
    fclose(fp2); 


    //grid test
    printf("grid-data created\n");
     FILE *fp3= fopen("haha.txt","w");  
        if(fp3 == NULL){
            printf("haha file open failed\n");
        }

       for(double i=-2.0;i<3.0;i=i+0.1){ 
        for(double j=-2.0;j<3.0;j=j+0.1){
            FeedForward(i,j,0);
            if(U_last>0.5){
               // printf("x1:%lf x2:%lf,1\n",i,j);           
                fprintf(fp3,"%lf %lf %d\n",i,j,1);
            }
            else{
               // printf("x1:%lf x2:%lf,0\n",i,j);  
                fprintf(fp3,"%lf %lf %d\n",i,j,0);
            }
        }
        }   
    fclose(fp3);
}
