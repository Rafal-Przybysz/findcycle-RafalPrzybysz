#include <iostream>
#include <vector>


class Graph
{
private:
	class Vertex
	{
	public:
		Vertex() : visited(false), onPath(false)
		{
		}
		bool visited;
		bool onPath;
		std::vector<int> edges;
	};


	std::vector<Vertex> vertices;

public:
	void setNumberOfVertices(int numberOfVertices)
	{
		vertices.resize(numberOfVertices);
	}

	void addEdge(int startVertex, int endVertex)
	{
		vertices[startVertex].edges.push_back(endVertex);
		vertices[endVertex].edges.push_back(startVertex);//pierwsza modyfikacja

	}

	void clearVisited()
	{
		for (auto& v : vertices)
		{
			v.visited = false;
			v.onPath = false;
		}
	}

	void dfs(int v)
	{
		if (vertices[v].visited)
			return;

		std::cout << v << ",";

		vertices[v].visited = true;
		for (auto w : vertices[v].edges)
		{
			dfs(w);
		}
	}

private:
	bool isCycle(int v, int prev ,std::vector<int>& cycle)
	{
		
		cycle.push_back(v);
		vertices[v].visited = true;
		vertices[v].onPath = true;
		for (auto w : vertices[v].edges)
		{
			if (w != prev)
			{
				if (!vertices[w].visited)
				{

					if (isCycle(w,prev, cycle))
						return true;
				}
				else
				{

					if (vertices[w].onPath)
					{
						while (cycle.front() != w)
							cycle.erase(cycle.begin());
						return true;
					}
				}
			}

		}
		cycle.pop_back();
		vertices[v].onPath = false;
		return false;
	}

public:
	std::vector<int> findCycle()
	{
		clearVisited();
		std::vector<int> cycle;
		if (isCycle(0,0, cycle))
			return cycle;
		else
			return std::vector<int>();
	}
};

int main()
{
	Graph graph;

	int numberOfVertices;
	std::cin >> numberOfVertices;

	graph.setNumberOfVertices(numberOfVertices);

	int numberOfEdges;
	std::cin >> numberOfEdges;

	for (int i = 0; i < numberOfEdges; ++i)
	{
		int v, w;
		std::cin >> v >> w;
		graph.addEdge(v, w);
	}

	std::cout << "DFS: ";
	graph.dfs(0);

	std::cout << "\nCycle: ";
	std::vector<int> cycle = graph.findCycle();
	if (cycle.empty())
		std::cout << "-";
	else
	{
		for (auto v : cycle)
			std::cout << v << ",";
	}
}
