#include <bits/stdc++.h>
#include<iostream>
using namespace std;
#define N 10
int graph_adj[N][N];
int n;
int bellman_or_dijkstra; // 0 for Bellman-Ford and 1 for dijkstra

void print_bellman_ford_result(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

void bellman_ford(int graph[][N], int src)
{
    int dist[n];

    // Step 1: Initialize distances from src to all other vertices as INFINITE
    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple
    int u,v,weight;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(graph[i][j]!= 0) {
                u = i;
                v = j;
                weight = graph[i][j];
                if (dist[u] != INT_MAX
                && dist[u] + weight < dist[v])
                    dist[v] = dist[u] + weight;
           }
        }
    }

    // Step 3: check for negative-weight cycles.
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            if(graph[i][j]!= 0) {
                u = i;
                v = j;
                weight = graph[i][j];
                if (dist[u] != INT_MAX
                  && dist[u] + weight < dist[v]) {
                  printf("Graph contains negative weight cycle");
                  // If negative cycle is detected, simply return
                  return;
                }
            }
        }
    }
    print_bellman_ford_result(dist, n);
    return;
}

/* A utility function to find the vertex with minimum distance value, from
   the set of vertices not yet included in shortest path tree
*/
int find_min_dist_vertex(int dist[], bool sptSet[])
{

    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void print_dijkstras_result(int dist[])
{
    cout <<"Vertex \t Distance from Source" << endl;
    for (int i = 0; i < n; i++)
        cout  << i << " \t\t"<<dist[i]<< endl;
}

void dijkstra(int graph[][N], int src)
{
    int dist[n]; // The output array.  dist[i] will hold the shortest

    /* sptSet[i] will be true if vertex i is included in shortest
       path tree or shortest distance from src to i is finalized
    */
    bool sptSet[n];

    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        /* Pick the minimum distance vertex from the set of vertices not
            yet processed. u is always equal to src in the first iteration.
        */
        int u = find_min_dist_vertex(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < n; v++)
            // Do relaxation
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    print_dijkstras_result(dist);
}

// Driver function
int main()
{
    while (1){
    cout << endl <<"Enter 0 for Bellman-ford and 1 for Dijkstra's"<<endl;
    cin >> bellman_or_dijkstra;
    if (bellman_or_dijkstra !=0 && bellman_or_dijkstra != 1) {
        cout << "Invalid Selection!! \n Enter 0 for Bellman-Ford and 1 for Dijkstras";
        continue;
    }
    cout << "Enter number of vertices \n";
    cin >> n;

    // Get the adjacency matrix
    cout <<endl<<"Enter adjacency matrix \n";
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j< n; j++) {
            cout << "graph_adj["<<i<<"]"<<"["<<j<<"]  ";
            cin >> graph_adj[i][j];
            if(bellman_or_dijkstra && graph_adj[i][j] < 0) {
               cout << "graph[i][j] cannot be negative for Dijkstras";
               exit(0);
            }
            if(graph_adj[i][i] !=0) {
               cout << "graph[i][i] should be always equal to 0";
               exit(0);
            }
        }
        cout<<endl;
    }

    int source;
    cout << endl<<"Enter the source vertex"<<endl;
    cin >> source;
    if(bellman_or_dijkstra == 0)
        bellman_ford(graph_adj, source);
    else
        dijkstra(graph_adj, source);
  }
  return 0;
}
