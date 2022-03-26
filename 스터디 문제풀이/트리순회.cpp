#include <iostream>

using namespace std;

int Index[100001];
int inorder[100001];
int postorder[100001];
int n;

// 입력 받기
void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> inorder[i];
        Index[inorder[i]] = i; // inorder 요소들의 Index 정보 저장
    }
    for (int i = 1; i <= n; i++)
        cin >> postorder[i];
}

// preorder 를 출력하는 함수 (재귀)
void getPreOrder(int inStart, int inEnd, int postStart, int postEnd)
{
    // 더 이상 분할 할 수 없는 경우 return
    if (inStart > inEnd || postStart > postEnd)
        return;
    // postorder의 끝 값이 root값
    // Index 배열을 통해 inorder에서의 root index를 쉽게 구할 수 있다.
    int rootIndex = Index[postorder[postEnd]];
    int leftSize = rootIndex - inStart;
    int rightSize = inEnd - rootIndex;
    cout << inorder[rootIndex] << ' '; // root 값 출력

    // 재귀 함수 호출
    getPreOrder(inStart, rootIndex - 1, postStart, postStart + leftSize - 1);
    getPreOrder(rootIndex + 1, inEnd, postStart + leftSize, postEnd - 1);
}

int main()
{
    input();
    getPreOrder(1, n, 1, n);
    return 0;
}
