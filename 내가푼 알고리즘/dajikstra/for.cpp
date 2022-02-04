int Find_Shortest_Node()
{
    int Min_Dist, Min_Idx;
    Min_Dist = INF;
    Min_Idx = -1;
 
    for (int i = 1; i <= V; i++)
    {
        if (Select[i] == true) continue;
        if (Dist[i] < Min_Dist)
        {
            Min_Dist = Dist[i];
            Min_Idx = i;
        }
    }
    return Min_Idx;
}
 
void Update_Dist(int NewNode)
{
    for (int i = 1; i <= V; i++)
    {
        if (Select[i] == true) continue;
        if (Dist[i] > Dist[NewNode] + MAP[NewNode][i])
        {
            Dist[i] = Dist[NewNode] + MAP[NewNode][i];
        }
    }
}
 
void Dijkstra()
{
    for (int i = 1; i <= V; i++) Dist[i] = MAP[Start][i];
    Dist[Start] = 0;
    Select[Start] = true;
    
    for (int i = 0; i < V - 1; i++)
    {
        int NewNode = Find_Shortest_Node();
 
        Select[NewNode] = true;
        Update_Dist(NewNode);
    }
}

