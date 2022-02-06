//재귀로 작성(생각하지 못함 ㅠㅠ)




//while로 작성
int search(int *arr, int length, int target)
{
    int start = 0;
    int end = length-1;
    int mid = 0;
    while (start <= end){
        mid = (start+end) / 2;
        if (arr[mid] == target)
            return mid;
        else {
            if (arr[mid] < target)
                start = mid+1;
            else if (arr[mid] > target)
                end = mid-1;
        }
    }
    return -1;
}
 
