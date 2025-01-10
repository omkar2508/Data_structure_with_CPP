#include <iostream>
 #include <sstream>
#include <cstring>
#include <limits>
#define MAX_SIZE 20
using namespace std;

class Graph
{
    char landmarkNames[MAX_SIZE][15]; // Array to store landmark names
    int totalLandmarks, edgeCount, connectivityFlag;
    int adjacencyMatrix[MAX_SIZE][MAX_SIZE];

public:
    void createGraph();
    void applyKruskalAlgorithm();
    void depthFirstSearch(int);
};

struct Edge
{
    int startVertex, endVertex, distance;
} edgeList[MAX_SIZE], tempEdge;

int visited[MAX_SIZE]; // Global array to track visited vertices

// Depth-First Search to check graph connectivity
void Graph::depthFirstSearch(int vertex)
{
    if (visited[vertex] == 0)
        visited[vertex] = 1;

    for (int i = 1; i <= totalLandmarks; i++)
    {
        if (visited[i] == 0 && adjacencyMatrix[vertex][i] != 999)
            depthFirstSearch(i);
    }
}

// Graph creation function with input validation
void Graph::createGraph()
{
    int i, j, distance, edgeIndex = 0;
    connectivityFlag = 0;

    // Validate number of landmarks
    do
    {
        cout << "\nEnter Number of Landmarks (1 to " << MAX_SIZE << "): ";
        cin >> totalLandmarks;

        if (cin.fail() || totalLandmarks <= 0 || totalLandmarks > MAX_SIZE)
        {
            cout << "\nInvalid input! Please enter a number between 1 and " << MAX_SIZE << ".";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (totalLandmarks <= 0 || totalLandmarks > MAX_SIZE);

    // Initialize visited array and adjacency matrix
    for (i = 1; i <= totalLandmarks; i++)
    {
        visited[i] = 0;
        for (j = 1; j <= totalLandmarks; j++)
            adjacencyMatrix[i][j] = 999; // Assign infinity to all edges
    }

    cin.ignore(); // Clear input buffer

    // Input landmark names with validation
    for (i = 1; i <= totalLandmarks; i++)
    {
        cout << "\nEnter Name of Landmark " << i << " (Max 15 Characters): ";
        cin.getline(landmarkNames[i], 15);

        if (cin.fail() || strlen(landmarkNames[i]) == 0)
        {
            cout << "\nInvalid input! Please enter a valid name.";
            cin.clear();
            i--; // Retry current landmark
        }
    }

    // Input edges with validation
   // For parsing input

while (true)
{
    // Display landmarks with their indices
    for (i = 1; i <= totalLandmarks; i++)
        cout << i << ". " << landmarkNames[i] << "\t";

    cout << "\nEnter Two Landmark Numbers for Edge (Enter -1 to Stop): ";
    
    string input;
    getline(cin, input); // Read the entire line

    stringstream ss(input);
    int count = 0;
    int numbers[2]; // Array to hold exactly two numbers

    while (ss >> numbers[count]) // Parse numbers from the input
    {
        count++;
        if (count > 2) // If more than two numbers are entered, reject the input
            break;
    }

    if (count != 2) // If not exactly two numbers are provided
    {
        cout << "\nInvalid input! Please enter exactly two valid numbers.";
        continue; // Restart the loop
    }

    i = numbers[0];
    j = numbers[1];

    if (i == -1 || j == -1) // Stop condition
        break;

    if (i < 1 || i > totalLandmarks || j < 1 || j > totalLandmarks)
    {
        cout << "\nInvalid Edge! Please enter valid landmark numbers.";
        continue; // Restart loop for valid input
    }

    do
    {
        cout << "\nEnter Edge Distance (Positive Integer): ";
        cin >> distance;

        if (cin.fail() || distance <= 0)
        {
            cout << "\nInvalid input! Please enter a positive integer.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (distance <= 0);

    cin.ignore(); // Clear input buffer for next iteration

    // Update adjacency matrix and edge list
    adjacencyMatrix[i][j] = adjacencyMatrix[j][i] = distance;
    edgeList[edgeIndex].startVertex = i;
    edgeList[edgeIndex].endVertex = j;
    edgeList[edgeIndex].distance = distance;
    edgeIndex++;
}



    edgeCount = edgeIndex;

    // Sort edge list in ascending order of distances
    for (i = 0; i < edgeCount - 1; i++)
    {
        for (j = i + 1; j < edgeCount; j++)
        {
            if (edgeList[i].distance > edgeList[j].distance)
            {
                tempEdge = edgeList[i];
                edgeList[i] = edgeList[j];
                edgeList[j] = tempEdge;
            }
        }
    }

    depthFirstSearch(1);
    for (i = 1; i <= totalLandmarks; i++)
    {
        if (visited[i] == 0)
        {
            connectivityFlag = 1;
            break;
        }
    }
}

// Apply Kruskal's algorithm to find Minimum Spanning Tree
void Graph::applyKruskalAlgorithm()
{
    int component[MAX_SIZE][MAX_SIZE];
    int edgesSelected = 0, edgeIndex = 0, totalCost = 0;
    int parentVertex1, parentVertex2;

    if (connectivityFlag == 1)
    {
        cout << "\nGraph is Not Connected!";
        return;
    }

    // Initialize component array
    for (int i = 1; i <= totalLandmarks; i++)
    {
        for (int j = 1; j <= totalLandmarks; j++)
        {
            if (j == 1)
                component[i][j] = i;
            else
                component[i][j] = 0;
        }
    }

    while (edgesSelected < totalLandmarks - 1)
    {
        tempEdge = edgeList[edgeIndex];
        edgeIndex++;

        for (int i = 1; i <= totalLandmarks; i++)
        {
            for (int j = 1; j <= totalLandmarks; j++)
            {
                if (component[i][j] == tempEdge.startVertex)
                    parentVertex1 = i;
                if (component[i][j] == tempEdge.endVertex)
                    parentVertex2 = i;
            }
        }

        if (parentVertex1 != parentVertex2)
        {
            cout << "\n"
                 << landmarkNames[tempEdge.startVertex] << " <-----> " << landmarkNames[tempEdge.endVertex] << " = " << tempEdge.distance;
            totalCost += tempEdge.distance;
            edgesSelected++;

            // Merge components
            int index = 1;
            while (component[parentVertex1][index] != 0)
                index++;

            for (int j = 1; component[parentVertex2][j] != 0; j++, index++)
            {
                component[parentVertex1][index] = component[parentVertex2][j];
                component[parentVertex2][j] = 0;
            }
        }
    }

    cout << "\nTotal Cost of Spanning Tree: " << totalCost;
}

int main()
{
    Graph graphInstance;
    graphInstance.createGraph();
    graphInstance.applyKruskalAlgorithm();
    return 0;
}
