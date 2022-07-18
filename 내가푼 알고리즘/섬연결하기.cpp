#include <string>
#include <vector>
#include <algorithm> 
#define MAX 105
using namespace std;
int Parent[MAX];
vector<pair<int, pair<int, int>>> Edge; 
int Find_Parent(int A){
    if (A == Parent[A]) return A;    
    return Parent[A] = Find_Parent(Parent[A]);
} 
bool Same_Parent(int A, int B){   
    A = Find_Parent(A);    
    B = Find_Parent(B);    
    if (A == B) return true;
    return false;
} 
void Union(int A, int B){   
    A = Find_Parent(A);   
    B = Find_Parent(B);   
    Parent[B] = A;
}
int solution(int n, vector<vector<int>> costs){   
    int answer = 0;   
    for (int i = 0; i< n; i++) Parent[i] = i;  
    for (int i = 0; i < costs.size(); i++)    { 
        int Node1 = costs[i][0];
        int Node2 = costs[i][1]; 
        int Cost = costs[i][2]; 
        Edge.push_back(make_pair(Cost, make_pair(Node1, Node2)));    }  
    sort(Edge.begin(), Edge.end()); 
    for (int i = 0; i < Edge.size(); i++)    {    
        int Cost = Edge[i].first;    
        int Node1 = Edge[i].second.first;
        int Node2 = Edge[i].second.second; 
        if (Same_Parent(Node1, Node2) == false) 
        {            
            Union(Node1, Node2);
            answer = answer + Cost;
        }  
    }   
    return answer;
}
