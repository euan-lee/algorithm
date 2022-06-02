#include <string>
#include <vector>
#include <map>
using namespace std;
 
 
void Mapping_String_To_Int(vector<string> List, map<string, int> &MAP)
{
    int Num = 1;
    for (int i = 0; i < List.size(); i++)
    {
        string S = List[i];
        MAP[S] = Num++;
    }
}
 
void Make_Parent(vector<string> enroll, vector<string> referral, map<string, int> MAP, vector<int>& Parent)
{
    for (int i = 0; i < enroll.size(); i++)
    {
        string Child = enroll[i];
        int I_Child = MAP[Child];
 
        string Par = referral[i];
        if (Par == "-")    Parent[I_Child] = 0;
        else
        {
            int I_Par = MAP[Par];
            Parent[I_Child] = I_Par;
        }
    }
}
 
void DFS(int Cur, int Cost, vector<int> Parent, vector<int> &Money)
{
    if (Cur == 0) return;
    
    int Give_Cost = Cost / 10;
    if (Give_Cost < 1)
    {
        Money[Cur] += Cost;
        return;
    }
    else
    {
        int My_Cost = Cost - Give_Cost;
        Money[Cur] += My_Cost;
        DFS(Parent[Cur], Give_Cost, Parent, Money);
    }
}
 
void Calculate(map<string, int> MAP, vector<int> Parent, vector<string> Seller, vector<int> Amount, vector<int> &Money)
{
    for (int i = 0; i < Seller.size(); i++)
    {
        string S_Seller = Seller[i];
        int I_Seller = MAP[S_Seller];
        int Cost = Amount[i] * 100;
 
        DFS(I_Seller, Cost, Parent, Money);
    }
}
 
vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) 
{
    vector<int> answer;
    
    map<string, int> Mapping;
    Mapping_String_To_Int(enroll, Mapping);
 
    vector<int> Parent(enroll.size() + 1);
    Make_Parent(enroll, referral, Mapping, Parent);
 
    vector<int> Money(enroll.size() + 1, 0);
    Calculate(Mapping, Parent, seller, amount, Money);
 
    for (int i = 1; i <= enroll.size(); i++) answer.push_back(Money[i]);
    return answer;
}
