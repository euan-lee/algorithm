void enqueue(int arr[], int val)//삽입
{
  int i = 0; 
  if (size == MAX_LEN) { // 배열에 공간이 없으면 실패
    printf("Overflow: Could not insertKey\n");
  }
  
  // 힙 끝에 요소 삽입.
  size ++;
  i = size;
  arr[i]= val;

  // 우선순위가 부모 노드가 더 작다면 교환하고 부모 노드부터 다시 비교, 힙속성을 유지할 때까지 반복함.
  while(i > 1 && arr[i/2] < arr[i]) {
    swap(arr[i/2], arr[i]);
    i = i/2;
  }
}
//heapify

void max_heapify (int arr[], int i)
{
  int largest = i;  
  int left = 2*i              //left child
  int right = 2*i +1          //right child
  
  // 현재 요소 i와 자식 노드의 값을 비교
  if(left <= size && arr[left] > arr[i] )
    largest = left;  
  if(right <= size && arr[right] > arr[largest] )
    largest = right;
  
  // 자식 노드의 값이 더 크다면 교환하고 교환된 자식 노드부터 heapify 진행
  if(largest != i ) {
    swap (arr[i] , arr[largest]);
    max_heapify (h, largest);
  } 
}int dequeue (int arr[]) {
  if(size == 0) {
    printf("empty\n");
  }
  
  // 루트 노드 값을 리턴값에 저장한 뒤, 마지막 요소를 루트노드에 배치함
  Node max = arr[1];
  arr[1] = arr[size];
  size --;

  // 루트 노드부터 heapify 수행
  max_heapify(arr, 1);
  
  return max;
}



