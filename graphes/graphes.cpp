// graphes.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;
int n = 0;
const int exit_from = 6;
struct node {
    int node, next, flag;
    bool is_end = false;
};
class Graph
{
public:
   // vector<vector<int>> graphList = {{1,1}};
    vector<vector<node>> graph_arr;
    
    Graph(vector<node> const &arr)
    {
        graph_arr.resize(n);
        for (auto &node: arr)
        {
            graph_arr[node.node].push_back(node);
        }
    };

};
void print_graph(Graph& graph, int noda, int *mass)
{
    for (size_t i = noda; i < n; i++)
    {
        
        if (graph.graph_arr[i].size() == NULL)
        {
            continue;
        }
        cout << i << " ->";
        for (node a: graph.graph_arr[i])
        {
            mass[a.next]++;
            cout << a.next;
        }
        cout << '\n';
    }
}
int deep_search(Graph &graph, int noda, int *flags, int* mass, int temp = 0)
{
    vector<node> temp_node = graph.graph_arr[noda];
    
    //mass[noda - 1] += 1;
    if (flags[noda-1] != -1)
    {
        
        if (temp_node[0].is_end)
        {
            cout << temp_node[0].node<<" <--- end"<<endl;
            flags[noda - 1] = -1;
            cout << mass[temp_node[0].node - 1] << "<mass" << endl;
            for (size_t i = 0; i < n; i++)
            {
                
                flags[i] = -1;
            }
            return 1;
        }
        cout << temp_node[0].node << endl;
        
        //cout << temp_node.size() << endl;
        flags[noda-1] = -1;
        //cout << temp_node[0].next << endl;
        if (temp_node.size() >= 1)
        {
           
            temp++;
            for (size_t i = 0; i < temp_node.size(); i++)
            {

                deep_search(graph, temp_node[i].next, flags, mass, i);
            }


        }
    }
    temp = 0;
   /* while (graph.graph_arr[noda][noda] != exit_from)
    {
        noda = graph.graph_arr[noda][0];
        cout << "search";
    }*/
    
}
int deicstra(Graph& graph, int noda, int* flags, int* mass, int temp = 0)
{
    vector<node> temp_node = graph.graph_arr[noda];

    //mass[noda - 1] += 1;
    if (flags[noda - 1] != -1 && mass[temp_node[0].node - 1]<=mass[temp_node[0].next - 1])
    {

        if (temp_node[0].is_end)
        {
            cout << temp_node[0].node << " <--- end" << endl;
            flags[noda - 1] = -1;
            cout << mass[temp_node[0].node - 1] << "<mass" << endl;
            for (size_t i = 0; i < n; i++)
            {

                flags[i] = -1;
            }
            return 1;
        }
        cout << temp_node[0].node << endl;

        //cout << temp_node.size() << endl;
        flags[noda - 1] = -1;
        //cout << temp_node[0].next << endl;
        if (temp_node.size() >= 1)
        {

            temp++;
            for (size_t i = 0; i < temp_node.size(); i++)
            {

                deep_search(graph, temp_node[i].next, flags, mass, i);
            }


        }
    }
    temp = 0;
    /* while (graph.graph_arr[noda][noda] != exit_from)
     {
         noda = graph.graph_arr[noda][0];
         cout << "search";
     }*/

}
int wigth(Graph& graph, int noda, int *flags)
{
    vector<node> list;
    for (size_t i = noda; i < n; i++)
    {
        
        if (graph.graph_arr[i].size() == NULL)
        {
            continue;
        }
        //cout << i << "->";
        for (node a : graph.graph_arr[i])
        {
            list.push_back(a);
            //cout << a.next;
        }
        //cout << '\n';
    }
    for (size_t i = 0; i < list.size()-1; i++)
    {
        if (flags[list[i].next-1]!=1)
        {
            if (list[i+1].is_end)
            {
                cout << list[i+1].next << "<---end";
                break;
            }
            cout << list[i].next<<endl;
            flags[list[i].next-1] = 1;
        }
        
    }
    return 1;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<node> graph =
    { {0,0},{1,1},{2,2},{3,3},{4,4},{5,5},{6,6}, 
      {0,1},{1,2},{0,3},{3,4},{4,2}, {3,5},{5,4},{5,6} };
    n = graph.size();
    graph[2].is_end = true;
    //cout << "Выберите вершину от которой будет осуществляться вывод ";
    int top;
    int* flags = new int(n);
    int* flags_deicstra = new int(n);
    int* mass = new int(n);
    int* flags_wight= new int(n);
    for (size_t i = 0; i < n; i++)
    {
        flags[i] = 0;
        flags_deicstra[i] = 0;
        flags_wight[i] = 0;
        mass[i] = 0;
    }
    top = 0;
    Graph new_graph(graph);
    cout << "Граф" << endl;
    print_graph(new_graph, top, mass);
    cout << "\n";
    cout << "Дейкстера " << endl;
    deicstra(new_graph, top, flags_deicstra, mass);
    for (size_t i = 0; i < n; i++)
    {
        flags[i] = 0;
    }
    cout << "\nDeep search " << endl;
    deep_search(new_graph, top, flags, mass);
    cout << "\n<><>" << endl;
    cout << "Wigth Search"<<endl;
    wigth(new_graph, 0, flags_wight);
    cout << endl;
    cout << "__--__--" << endl;
    for (size_t i = 0; i < n; i++)
    {
        if (!mass[i])
        {
            break;
        }
        cout<<i<<" have mass " << mass[i]-1 << endl;
    }
    //    vector<node> x = new_graph.graph_arr[2];
    //    cout << endl;
    //     //cout << x[0].is_end;
    //    cout << new_graph.graph_arr[2].size();
    //}
}