#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

#define V 6
#define INF 99999

struct Parcel {
  int start;
  int end;
};


int dist[V][V];
int del_dist[V];
int env_dist[V];
int flag = 1;

void func(int driv_loc, Parcel env[], int del_dist[], int env_dist[],
          int tot_env) {
  int* dist[V];
  for (int i = 0; i < V; i++) {
      dist[i] = new int[V];
  }
  if (flag == 1) {
    for (int i = 0; i < tot_env; i++) {
      env_dist[i] = dist[driv_loc][env[i].start];
    }
  }
  flag = 0;
  int temp = INF;
  int temp2 = -1;
  int temp3 = -1;
  for (int i = 0; i < tot_env; i++) {
    if (temp >= env_dist[i]) {
      temp = env_dist[i];
      temp2 = i;
    }
  }
  for (int i = 0; i < tot_env; i++) {
    if (temp >= del_dist[i]) {
      temp = del_dist[i];
      temp3 = i;
    }
  }
  if (temp == INF) {
    return;
  }
  if (temp3 != -1) {
    cout << "Parcel " << temp3 + 1 << " will be delivered" << endl;
    del_dist[temp3] = INF;
    driv_loc = temp3;
    for (int i = 0; i < tot_env; i++) {
      if (env_dist[i] != INF) {
        env_dist[i] = dist[driv_loc][env[i].start];
      }
    }
  } else {
    cout << "Parcel " << temp2 + 1 << " will be collected" << endl;
    driv_loc = temp2;
    env_dist[temp2] = INF;
    for (int i = 0; i < tot_env; i++) {
      if (env_dist[i] != INF) {
        env_dist[i] = dist[driv_loc][env[i].start];
      }
    }
    del_dist[temp2] = dist[driv_loc][env[temp2].end];
  }
  func(driv_loc, env, del_dist, env_dist, tot_env);
  for (int i = 0; i < V; i++) {
      delete[] dist[i];
  }
}

void addEdge(vector<vector<int>> &adj, int u, int v, int wt) {
  adj[u][v] = wt;
  adj[v][u] = wt;
}

void printSolution() {
  cout << "The following matrix shows the shortest distances between every "
          "pair of vertices:\n";
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      if (dist[i][j] == INF)
        cout << "INF\t";
      else
        cout << dist[i][j] << "\t";
    }
    cout << endl;
  }
}
int minDistance(int dist[], bool visited[]) {
    int min = INF, min_index;

    for (int v = 0; v < V; v++) {
        if (visited[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}
void printSol(int dist[])
{
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t\t\t" << dist[i] << endl;
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    bool visited[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);

        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSol(dist);
}

void floydWarshall(int graph[][V]) {
  for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++)
      dist[i][j] = graph[i][j];
  for (int k = 0; k < V; k++) {
    for (int i = 0; i < V; i++) {
      for (int j = 0; j < V; j++) {
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];
      }
    }
  }
  printSolution();
}
void takeEdgesInput(vector<vector<int>> &adj) {
  int edges;
  cout << "Enter the number of edges: ";
  cin >> edges;
  cout << "Enter the edges in the format 'source destination weight':" << endl;
  int u, v, wt;
  for (int i = 0; i < edges; i++) {
    cin >> u >> v >> wt;
    addEdge(adj, u, v, wt);
  }
}

int main() {
  int a ;
  cout<<"Enter the number of nodes: ";
  cin>>a;
  int input[a][a];
  
  for (int i = 0; i < a; i++) {
    for (int j = 0; j < a; j++) {
      input[i][j] = (i == j) ? 0 : INF;
    }
  }
  
  vector<vector<int>> adj(a, vector<int>(a, INF));
  int l;
  cout<<"1.Demo Matrix"<<endl;
  cout<<"2.Input Matrix";
  cin>>l;
  if(l==2)
  takeEdgesInput(adj);
  else{
  addEdge(adj, 0, 1, 2);
  
  addEdge(adj, 0, 5, 1);
  
  addEdge(adj, 0, 4, 8);
  
  addEdge(adj, 1, 0, 2);
  addEdge(adj, 1, 2, 6);
  addEdge(adj, 1, 5, 3);
  addEdge(adj, 2, 1, 6);
  addEdge(adj, 2, 5, 9);
  addEdge(adj, 2, 3, 2);
  
  addEdge(adj, 3, 4, 4);
  addEdge(adj, 3, 5, 17);
  addEdge(adj, 3, 2, 2);
  

  addEdge(adj, 4, 0, 8);
  addEdge(adj, 4, 5, 5);
  addEdge(adj, 4, 3, 4);
  
  addEdge(adj, 5, 0, 1);
  addEdge(adj, 5, 2, 9);
  addEdge(adj, 5, 1, 3);
  addEdge(adj, 5, 3, 17);
  addEdge(adj, 5, 4, 5);}
  int w;
  for (int u = 0; u < a; u++) {
    cout << "Node " << u << " makes an edge with:\n";
    for (int v = 0; v < a; v++) {
      if (adj[u][v] != INF) {
        w = adj[u][v];
        input[u][v] = w;
        cout << "\tNode " << v << " with edge weight = " << w << "\n";
      }
    }
  }
  cout << "Matrix representation of the graph:\n";
  for (int i = 0; i < a; i++) {
    for (int j = 0; j < a; j++) {
      if (input[i][j] == INF) {
        cout << "INF\t";
      } else {
        cout << input[i][j] << "\t";
      }
      if (j == a-1) {
        cout << endl;
      }
    }
  }
  int graph[V][V];
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      graph[i][j] = input[i][j];
    }
  }

  

  int choice;
  do {
    cout << "\nMenu:\n";
    cout << "1. Floyd-Warshall Algorithm\n";
    cout << "2. Dijkstra's Algorithm\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      cout << "Running Floyd-Warshall Algorithm:\n";
      int dri_loc, tot_env;
      cout << "Enter the vertex where the driver is located (Choose from 0, 1, 2, "
              "3, 4): ";
      cin >> dri_loc;
      cout << "Enter the number of Parcels: ";
      cin >> tot_env;
      Parcel env[tot_env];
      for (int i = 0; i < tot_env; i++) {
        cout << "Enter the Parcel location of Parcel " << i + 1 << ": ";
        cin >> env[i].start;
        cout << "Enter the delivery location of Parcel " << i + 1 << ": ";
        cin >> env[i].end;
      }
      for (int i = 0; i < tot_env; i++) {
        del_dist[i] = INF;
      }
      floydWarshall(graph);

      func(dri_loc, env, del_dist, env_dist, tot_env);

      break;
    case 2:
      cout << "Running Dijkstra's Algorithm:\n";
      int src;
      cout << "Enter the single source:\n";
      cin >> src;
      dijkstra(graph, src);
      
      break;
    case 3:
      cout << "Exiting...\n";
      break;
    default:
      cout << "Invalid choice! Please enter again.\n";
    }
  } while (choice != 3);

  return 0;
}
