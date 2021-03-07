#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define noEdge 999999

/*
	Note:- I have chosen super node index as last index, i.e. last in the compressed matrix as such
*/
/*
	tried test case (randomly generated using python):-
	
*/

/*
	noEdge defines that there is no edge from  u to v.
	BFS function provides functionality for performing BFS on given graph,
	to remove edges connecting unreachable nodes from source
*/
void BFS(int source, vector<int> matrix[], int n)
{
	int visited[n];
	for (int i = 0; i < n; i++)
	{
		visited[i] = 0;
	}
	queue<int> queue;
	visited[source] = true;
	queue.push(source);
	while (!queue.empty())
	{
		int temp = queue.front();
		queue.pop();
		for (int i = 0; i < n; i++)
		{
			if (!visited[i] && matrix[temp][i] != noEdge)
			{
				visited[i] = 1;
				queue.push(i);
			}
		}
	}
	for (int j = 0; j < n; j += 1)
	{
		if (visited[j] == 0)
		{
			for (int k = 0; k < n; k += 1)
			{
				matrix[j][k] = noEdge;
				matrix[k][j] = noEdge;
			}
		}
	}
}

/*
	this function helps to detect the cycle. The algo is pretty similar to union find algo.
	In each iteration we check if the parent of some node has already been visited or not.
	If it has been visited, we can say cycle has been detected and we break the loop.
	If no such condition occur we report that no cycle found.
*/
void cycleDetectorUtility(vector<int> firstZeroInEdge, int n, int &isCycle, int &temp)
{
	int visitedEdges[n] = {0};
	for (int i = 0; i < n; i++)
	{
		if (visitedEdges[i] == 0)
		{
			temp = i;
			while (1)
			{
				if (visitedEdges[temp] == 1)
				{
					isCycle = 1;
					break;
				}

				if (firstZeroInEdge[temp] != -1)
				{
					visitedEdges[temp] = 1;
					temp = firstZeroInEdge[temp];
				}
				else
					break;
			}
			for (int j = 0; j < n; j++)
			{
				visitedEdges[j] = 0;
			}
		}
		if (isCycle)
			break;
	}
}
/*
	It is a helper function which helps us in creating tracks of nodes in superNode, so that they 
	can be used further in the program. SImply, it helps us giving new labelling to the graph after
	formation of a superNode
*/
int compressionAndCallBack(vector<int> firstZeroInEdge, int *compressionUtility, int *callBackUtility, int n, int temp)
{
	int countOfCycle = 0;
	for (int i = 0; i < n; i++)
	{
		compressionUtility[i] = 1;
		callBackUtility[i] = -1;
	}
	int i = temp;
	compressionUtility[i] = 0;
	while (1)
	{
		i = firstZeroInEdge[i];
		countOfCycle += 1;
		compressionUtility[i] = 0;
		if (i == temp)
			break;
	}

	temp = 1;
	for (int i = 0; i < n; i++)
	{
		if (compressionUtility[i] == 1)
		{
			compressionUtility[i] = temp;
			callBackUtility[temp - 1] = i;
			temp += 1;
		}
	}
	return countOfCycle;
}

/*
	This is the main function that is used to create the arboroscence.
	It returns a vector, which holds the parent of each node in the arboroscence.
	Basically it returns mapping of the arboroscence.
	Firstly, we look for cycle, if cycle found then we compress the graph(i.e. form superNode)
	Then we do a recursive call on the modified graph until the graph contains no cycle.
	After recursion returns we remove the cycle by breaking it at the point where it has two inedges.
*/
vector<int> minCostArboroscence(int source, vector<int> matrix[], int n)
{
	int minIncomingEdge[n]; //stores minimum incoming edge on a graph
	vector<int> reducedEdgeWeights[n];
	vector<int> firstZeroInEdge; //stores parent i.e. lexiographically first node from which it has miinimum incoming node

	BFS(source, matrix, n); //removing unreachable edges

	for (int i = 0; i < n; i++)
	{
		int temp = INT_MAX;
		for (int j = 0; j < n; j++)
		{
			reducedEdgeWeights[i].push_back(noEdge);
			if (matrix[j][i] != noEdge)
			{
				if (matrix[j][i] < temp)
					temp = matrix[j][i];
			}
		}
		if (temp != INT_MAX)
			minIncomingEdge[i] = temp;
		else
			minIncomingEdge[i] = -1;
	}

	for (int i = 0; i < n; i++)
	{
		firstZeroInEdge.push_back(-1);
	}

	for (int i = 0; i < n; i += 1)
	{
		for (int j = 0; j < n; j += 1)
		{
			if (matrix[i][j] != noEdge)
				reducedEdgeWeights[i][j] = matrix[i][j] - minIncomingEdge[j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (reducedEdgeWeights[j][i] == 0)
			{
				firstZeroInEdge[i] = j;
				break;
			}
		}
	}

	int isCycle = 0;
	int temp;
	cycleDetectorUtility(firstZeroInEdge, n, isCycle, temp);

	if (isCycle)
	{
		int compressionUtility[n];
		int callBackUtility[n];
		int countOfCycle = compressionAndCallBack(firstZeroInEdge, compressionUtility, callBackUtility, n, temp);
		int changedSize = n + 1 - countOfCycle;
		int anotherHelperArray[changedSize];
		vector<int> changedMatrix[changedSize];
		for (int j = 0; j < changedSize; j += 1)
		{
			for (int k = 0; k < changedSize; k += 1)
				changedMatrix[j].push_back(noEdge);
		}

		//Graph compression changed Matrix is converted graph
		for (int j = 0; j < n; j += 1)
		{
			if (compressionUtility[j] == 0)
			{
				for (int k = 0; k < n; k += 1)
				{
					if (compressionUtility[k] != 0)
					{
						if (changedMatrix[changedSize - 1][compressionUtility[k] - 1] == noEdge)
							changedMatrix[changedSize - 1][compressionUtility[k] - 1] = reducedEdgeWeights[j][k];
						else
						{
							if (matrix[j][k] != noEdge)
								changedMatrix[changedSize - 1][compressionUtility[k] - 1] = min(changedMatrix[changedSize - 1][compressionUtility[k] - 1], reducedEdgeWeights[j][k]);
						}
					}
				}
			}
			else
			{
				for (int k = 0; k < n; k += 1)
				{
					if (compressionUtility[k] == 0)
					{
						if (changedMatrix[compressionUtility[j] - 1][changedSize - 1] == noEdge)
						{
							if (matrix[j][k] != noEdge)
							{
								anotherHelperArray[compressionUtility[j] - 1] = k;
								changedMatrix[compressionUtility[j] - 1][changedSize - 1] = reducedEdgeWeights[j][k];
							}
						}

						else
						{
							if (matrix[j][k] != noEdge)
							{
								if (changedMatrix[compressionUtility[j] - 1][changedSize - 1] > reducedEdgeWeights[j][k])
								{
									anotherHelperArray[compressionUtility[j] - 1] = k;
									changedMatrix[compressionUtility[j] - 1][changedSize - 1] = reducedEdgeWeights[j][k];
								}
							}
						}
					}
					else
						changedMatrix[compressionUtility[j] - 1][compressionUtility[k] - 1] = reducedEdgeWeights[j][k];
				}
			}
		}
		//recursive call
		vector<int> changedParentArray;
		changedParentArray = minCostArboroscence(compressionUtility[source] - 1, changedMatrix, changedSize);

		vector<int> finalParentArray;
		for (int i = 0; i < n; i++)
		{
			finalParentArray.push_back(-1);
		}
		for (int i = 0; i < n; i++)
		{
			if (compressionUtility[i] == 0)
				finalParentArray.at(i) = firstZeroInEdge.at(i);

			else
			{
				int testingElement = compressionUtility[i] - 1;
				if (changedParentArray.at(testingElement) == changedSize - 1)
				{
					int testingTwo = INT_MAX;
					int flag = 0;
					for (int j = 0; j < n; j++)
					{
						if (compressionUtility[j] == 0)
						{
							if (testingTwo > matrix[j][i])
							{
								testingTwo = matrix[j][i];
								flag = j + 1;
							}
						}
					}
					if (flag > 0)
						finalParentArray.at(i) = flag - 1;
					else
						finalParentArray.at(i) = -1;
				}

				else if (changedParentArray.at(testingElement) == -1)
					finalParentArray.at(i) = -1;
				else
					finalParentArray.at(i) = callBackUtility[changedParentArray.at(testingElement)];
			}
		}
		// Here we are looking for extra inEdge and removing it
		int dualInEdge = changedParentArray[changedSize - 1];
		if (dualInEdge != -1)
		{
			int solution = anotherHelperArray[dualInEdge];
			finalParentArray.at(solution) = callBackUtility[dualInEdge];
		}

		return finalParentArray;
	}
	return firstZeroInEdge;
}


int main()
{
	int t;
	cin >> t;
	for (int i = 0; i < t; i += 1)
	{
		int N, M, source, u, v, w;
		cin >> N >> M >> source;
		vector<int> matrix[N];

		int invalidCase = 0; //when negative edge is there
		for (int j = 0; j < N; j += 1)
		{
			for (int k = 0; k < N; k += 1)
			{
				matrix[j].push_back(noEdge);
			}
		}

		for (int j = 0; j < M; j += 1)
		{
			cin >> u >> v >> w;
			if (u != v && v != source)
			{
				if (w < 0)
					invalidCase = 1;

				else if (matrix[u - 1][v - 1] == noEdge)
					matrix[u - 1][v - 1] = w;
				else
					matrix[u - 1][v - 1] = min(matrix[u - 1][v - 1], w);
			}
		}

		if (invalidCase)
			cout << -1 << endl;
		else
		{
			vector<int> ans;
			ans = minCostArboroscence(source - 1, matrix, N);
			

			int finalAns[N] = {0};
			int minCostOfArboroscence = 0;
			int temp;
			for (int j = 0; j < N; j++)
			{
				if (ans[j] != -1)
					minCostOfArboroscence += matrix[ans[j]][j];
			}
			cout << minCostOfArboroscence << " ";

			for (int j = 0; j < N; j++)
			{
				int temp = j;
				if (ans[temp] == -1)
					finalAns[j] = -1;
				else
				{
					while (1)
					{
						if (temp != source - 1)
						{
							finalAns[j] += matrix[ans[temp]][temp];
							temp = ans[temp];
						}
						else
							break;
					}
				}
			}

			for (int j = 0; j < N; j++)
			{
				if (j + 1 == source)
					cout << 0 << " ";
				else
					cout << finalAns[j] << " ";
			}

			cout << "# ";
			for (int j = 0; j < N; j++)
			{
				if (j + 1 == source)
					cout << 0 << " ";
				else if (ans[j] == -1)
					cout << -1 << " ";
				else
					cout << ans[j] + 1 << " ";
			}
			cout << endl;
		}
	}
}
