#include <iostream>
#define DICE 6
#define MAP_MAX 21
using namespace std;
 
// 전역 변수 리스트
int N, M, K;
// 주사위의 좌표
int dice_col, dice_row;
 
// 주사위의 숫자를 저장
int dice_num[DICE] = {0};
// 현재 주사위의 모양에 따라서, 주사위의 인덱스를 저장
int dice_index[DICE] = {1, 5, 3, 2, 4, 6};
// 지도 정보
int map[MAP_MAX][MAP_MAX];
 
// 맵의 값을 출력한다.
void print_state(){
    printf("\n");
    printf("\n");
    for ( int i = 0 ; i < DICE; i++)
        printf("%d ", dice_num[dice_index[i]-1]);
    printf("\n");
 
    for ( int i = 0 ; i < N; i++){
        for ( int j = 0 ; j < M ; j++){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
 
// 주사위의 인덱스를 결정한다.
void change_dice_index(int move_way){
    int sub = dice_index[0] ;
    switch (move_way) {
            // 동
        case 1:
            dice_index[0] = dice_index[4];
            dice_index[4] = dice_index[5];
            dice_index[5] = dice_index[2];
            dice_index[2] = sub;
            break;
            // 서
        case 2:
            dice_index[0] = dice_index[2];
            dice_index[2] = dice_index[5];
            dice_index[5] = dice_index[4];
            dice_index[4] = sub;
            break;
            // 북
        case 3:
            dice_index[0] = dice_index[1];
            dice_index[1] = dice_index[5];
            dice_index[5] = dice_index[3];
            dice_index[3] = sub;
            break;
            // 남
        case 4:
            dice_index[0] = dice_index[3];
            dice_index[3] = dice_index[5];
            dice_index[5] = dice_index[1];
            dice_index[1] = sub;
            break;
        default:
            printf("error!!");
            break;
    }
}
 
// 주사위의 포지션을 변경한다.
int change_dice_position(int move_way){
    int isOK = 0;
    switch (move_way) {
            // 동
        case 1:
            if ( dice_col + 1 < M ){
                dice_col += 1; isOK = 1;
            }
            break;
            // 서
        case 2:
            if ( dice_col - 1 >= 0 ){
                dice_col -= 1; isOK = 1;
            }
            break;
            // 북
        case 3:
            if ( dice_row - 1 >= 0 ){
                dice_row -= 1; isOK = 1;
            }
            break;
            // 남
        case 4:
            if ( dice_row + 1 < N ){
                dice_row += 1; isOK = 1;
            }
            break;
        default:
            break;
    }
    return isOK;
}
 
 
// 한 번 굴리는 것을 수행
int one_roll(int move_way){
    // 주사위의 좌표를 변경해준다. 범위를 벗어나면 즉각 리턴
    if(change_dice_position(move_way) == 0 )
        return -1;
 
    // 방향에 따라서 주사위의 인덱스들을 변경해준다.
    change_dice_index(move_way);
 
    // 주사위를 굴렸을 때, 이동한 칸에 써 있는 수가 0이면, 주사위의 바닥면에 써 있는 수가 칸에 복사된다
    if (map[dice_row][dice_col] == 0 ){
        map[dice_row][dice_col] = dice_num[dice_index[DICE-1]-1];
    }
    // 0이 아닌 경우에는 칸에 써 있는 수가 주사위의 바닥면으로 복사되며, 칸에 써 있는 수는 0이 된다.
    else {
        dice_num[dice_index[DICE-1]-1] = map[dice_row][dice_col];
        map[dice_row][dice_col] = 0 ;
    }
 
    return 1;
}
 
 
int main(){
    cin >> N >> M >> dice_row >> dice_col >> K;
 
    // 좌표에 있는 데이터 받기
    for ( int i = 0 ; i < N; i++){
        for ( int j = 0 ; j < M ; j++){
            scanf("%d", &map[i][j]);
        }
    }
    // 이동 수행
    int move_way;
    for ( int i = 0 ; i < K ; i++){
        scanf("%d", &move_way);
        // one_roll이 1을 리턴해야만 정답으로 인정
        if ( one_roll(move_way) == 1 )
            printf("%d\n", dice_num[dice_index[0]-1]);
    }
 
    return 0;
}
