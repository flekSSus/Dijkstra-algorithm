#include<utility>
#include<fstream>
#include<vector>
#include<queue>

int main()
{
    std::ifstream in("input.txt"); 
    std::ofstream out("output.txt");

    int numOfNodes(0);
    int numOfEdges(0);

    in>>numOfNodes>>numOfEdges;
    std::vector<int> arrVisited(numOfNodes,0);
    std::vector<long long > arrDis(numOfNodes,-1);
    std::vector< std::vector< std::pair<long long,int> > > list(numOfNodes);
    std::priority_queue< std::pair<long long,int> ,
                         std::vector< std::pair<long long ,int> >,
                         std::greater<std::pair<long long ,int> >> 
    binHeap;

    arrDis[0]=0;
    binHeap.push(std::make_pair(0,0));

    for(int i(0);i<numOfEdges;++i)
    {
        int nodeBegin(0);
        int nodeEnd(0);
        int weight(0);
        in>>nodeBegin>>nodeEnd>>weight;
        
        list[nodeBegin-1].push_back(std::make_pair(weight,nodeEnd-1));
        list[nodeEnd-1].push_back(std::make_pair(weight,nodeBegin-1));

    }

    while(!binHeap.empty())
    {
        auto top= binHeap.top();
        binHeap.pop();

        if(arrVisited[top.second]==1)
            continue;
        arrDis[top.second]=top.first;
        arrVisited[top.second]=1;    
        
        for(auto i: list[top.second])
        {
            binHeap.push(std::make_pair(i.first+top.first, i.second));
        }
    }

    out<<arrDis[numOfNodes-1];
    
    in.close();
    out.close();
}

