#include <iostream>
#include <limits>
#include <string>
#define MAX_NODES 20
using namespace std;

class Graph
{
	string landmarks[MAX_NODES];			   // Names of landmarks
	int numLandmarks;						   // Number of landmarks
	bool isConnected;						   // Flag to check if the graph is connected
	int adjacencyMatrix[MAX_NODES][MAX_NODES]; // Adjacency matrix to store distances

public:
	void createGraph();
	void dijkstraShortestPath();
	void depthFirstSearch(int);
};

int visitedNodes[MAX_NODES]; // Global visited nodes array for DFS

// Depth First Search to check graph connectivity
void Graph::depthFirstSearch(int currentNode)
{
	visitedNodes[currentNode] = 1;
	for (int i = 1; i <= numLandmarks; i++)
	{
		if (visitedNodes[i] == 0 && adjacencyMatrix[currentNode][i] != 999)
		{
			depthFirstSearch(i);
		}
	}
}

// Function to create the graph
void Graph::createGraph()
{
	int startNode, endNode, distance;

	cout << "\nEnter the number of landmarks: ";
	while (true)
	{
		cin >> numLandmarks;
		if (cin.fail() || numLandmarks <= 0 || numLandmarks > MAX_NODES)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input! Please enter a valid integer between 1 and " << MAX_NODES << ": ";
		}
		else
		{
			break;
		}
	}

	// Initialize adjacency matrix and visited array
	for (int i = 1; i <= numLandmarks; i++)
	{
		visitedNodes[i] = 0;
		for (int j = 1; j <= numLandmarks; j++)
		{
			adjacencyMatrix[i][j] = 999; // 999 indicates no direct connection
		}
	}

	cin.ignore(); // Clear newline character for getline
	for (int i = 1; i <= numLandmarks; i++)
	{
		cout << "\nEnter the name of landmark " << i << ": ";
		getline(cin, landmarks[i]);
	}

	cout << "\nEnter edges (landmarks and their distance). To stop, enter -1 for any landmark:\n";
	while (true)
	{
		for (int i = 1; i <= numLandmarks; i++)
		{
			cout << i << ". " << landmarks[i] << "\t";
		}

		cout << "\nEnter two landmark numbers for an edge: ";
		cin >> startNode >> endNode;

		if (startNode == -1 || endNode == -1)
			break;

		if (startNode < 1 || startNode > numLandmarks || endNode < 1 || endNode > numLandmarks)
		{
			cout << "Invalid edge! Please enter valid landmark numbers.\n";
			continue;
		}

		cout << "Enter the distance between these landmarks: ";
		while (true)
		{
			cin >> distance;
			if (cin.fail() || distance <= 0)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input! Please enter a positive distance: ";
			}
			else
			{
				break;
			}
		}
		adjacencyMatrix[startNode][endNode] = adjacencyMatrix[endNode][startNode] = distance;
	}

	// Check if the graph is connected
	depthFirstSearch(1);
	isConnected = true;
	for (int i = 1; i <= numLandmarks; i++)
	{
		if (visitedNodes[i] == 0)
		{
			isConnected = false;
			break;
		}
	}

	if (!isConnected)
	{
		cout << "\nWarning: The graph is not connected. Shortest paths may not exist for all pairs.\n";
	}
}

// Dijkstra's algorithm to find the shortest path
void Graph::dijkstraShortestPath()
{
	if (!isConnected)
	{
		cout << "\nThe graph is not connected! Shortest paths may not be available for all landmarks.\n";
		return;
	}

	int visited[MAX_NODES], distances[MAX_NODES], predecessors[MAX_NODES];
	int source, destination, currentNode, minDistance, nextNode;
	char continueSearch;

	do
	{
		for (int i = 1; i <= numLandmarks; i++)
		{
			cout << i << ". " << landmarks[i] << "\n";
		}

		cout << "\nEnter source and destination landmark numbers: ";
		while (true)
		{
			cin >> source >> destination;
			if (cin.fail() || source < 1 || source > numLandmarks || destination < 1 || destination > numLandmarks)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input! Please enter valid landmark numbers: ";
			}
			else
			{
				break;
			}
		}

		// Initialize distances and visited arrays
		for (int i = 1; i <= numLandmarks; i++)
		{
			visited[i] = 0;
			distances[i] = 999; // Set all distances to infinity (999 here)
			predecessors[i] = -1;
		}

		distances[source] = 0;
		predecessors[source] = source;

		currentNode = source;
		while (currentNode != destination)
		{
			minDistance = 999;
			for (int i = 1; i <= numLandmarks; i++)
			{
				if (!visited[i] && distances[i] < minDistance)
				{
					minDistance = distances[i];
					nextNode = i;
				}
			}

			if (minDistance == 999)
				break; // No path exists

			visited[nextNode] = 1;
			for (int i = 1; i <= numLandmarks; i++)
			{
				if (!visited[i] && adjacencyMatrix[nextNode][i] != 999)
				{
					int newDistance = distances[nextNode] + adjacencyMatrix[nextNode][i];
					if (newDistance < distances[i])
					{
						distances[i] = newDistance;
						predecessors[i] = nextNode;
					}
				}
			}
			currentNode = nextNode;
		}

		if (distances[destination] == 999)
		{
			cout << "\nNo path exists between the selected landmarks.\n";
		}
		else
		{
			cout << "\nShortest distance: " << distances[destination] << "\nPath: ";
			int temp = destination;
			while (temp != source)
			{
				cout << landmarks[temp] << " <- ";
				temp = predecessors[temp];
			}
			cout << landmarks[source] << "\n";
		}

		cout << "\nDo you want to continue? (1 for Yes, any other key to exit): ";
		cin >> continueSearch;
	} while (continueSearch == '1');
}

int main()
{
	Graph cityGraph;
	cityGraph.createGraph();
	cityGraph.dijkstraShortestPath();
	return 0;
}
