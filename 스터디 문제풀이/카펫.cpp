vector<int> solution(int brown, int yellow)
{
    vector<int> answer;
    
    int carpet = brown + yellow;
    
    for(int i=carpet/2; i>0; i--)
    {
        if(carpet % i ==0)
        {
            int a = i;
            int b = carpet/i;
            
            if((a-2) * (b-2) == yellow)
            {
                answer.push_back(a);
                answer.push_back(b);
                break;
            }       
        }
    }
    return answer;
}
