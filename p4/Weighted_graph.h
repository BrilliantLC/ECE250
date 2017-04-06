/*****************************************
 * UW User ID:  c37liang
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 *  the provided code.
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"

// include whatever classes you want

class Weighted_graph {
	private:
		int *deg;
		int edges;
		int size;
		// stores the weight of edge connecting adjacent vertices, INF if not adjacent (can still be connected)
		double **weight_adj_matrix;

		static const double INF;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int ) const;

		void insert( int, int, double );

	// Friends
	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// constructor
Weighted_graph::Weighted_graph(int n) {
	if (n <= 0) {
		n = 1;
	}

	deg = new int[n];
	// initialize degree of all vertices to 0
	for (int i = 0; i < n; i++) {
		deg[i] = 0;
	}

	edges = 0;
	size = n;

	// create the weight adjacency matrix
	// initialize rows
	weight_adj_matrix = new double *[n];
	for (int i = 0; i < size; i++) {
		// initialize columns
		weight_adj_matrix[i] = new double[n];
	}
	// initialize every element to INF as all verticies are initially not connected
	// non-INF entries represent the weight between two vertices
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			weight_adj_matrix[i][j] = INF;
		}
	}
}

// destructor
Weighted_graph::~Weighted_graph() {
	delete[] deg;

	// delete the matrix
	for (int i = 0; i < size; i++) {
		delete[] weight_adj_matrix[i];
	}
	delete[] weight_adj_matrix;
}

int Weighted_graph::degree(int n) const {
	if (n < 0 || n > size - 1) {
		throw illegal_argument();
	}
	// returns the degree of the vertex n stored in an array
	return deg[n];
}

int Weighted_graph::edge_count() const {
	return edges;
}

double Weighted_graph::adjacent(int m, int n) const {
	if (n < 0 || m < 0 || n > size - 1 || m > size - 1) {
		throw illegal_argument();
	}

	if (m == n) {
		return 0;
	}
	// return element in the mth row and nth column in the adjacency matrix
	return weight_adj_matrix[m][n];
}

double Weighted_graph::distance(int m, int n) const {
	if (n < 0 || m < 0 || n > size - 1 || m > size - 1) {
		throw illegal_argument();
	}

	bool *visited = new bool[size];			// keeps track of the visited vertices
	double *dist = new double[size];  	// distance of all vertices relative to m
	// initialize arrays
	for (int i = 0; i < size; i++) {
		visited[i] = false;
		if(m == i)
			dist[i] = 0;										// distance to itself is 0
		else
			dist[i] = INF;									// else assume it's not reachable from m
	}

	// set the path to start at m
	visited[m] = true;
	int curr = m;												// current vertex visited
	int visitedCount = 1;
	int count = 0;											// number of vertices that are connected
	for (int i = 0; i < size; i++) {
		if (deg[i] != 0)
			count++;
	}
	// while have not gone through all connected verticies
	while(visitedCount != count) {
		// relax all adjacent edges
		for (int i = 0; i < size; i++) {
			// conditions: connected, not visited and new distance would become smaller
			if ((weight_adj_matrix[curr][i] != INF) && (!visited[i])
			&& (dist[i] > (dist[curr] + weight_adj_matrix[i][curr]))) {
				dist[i] = dist[curr] + weight_adj_matrix[i][curr];
			}
		}

		// set the next curr
		double minDistance = INF;		// initialize distance to infinity
		int minNode = -1;						// placeholder: index cannot be -1
		for(int i = 0; i < size; i++){
			if(dist[i] < minDistance && visited[i] == false){
				minDistance = dist[i];
				minNode = i;
			}
		}
		curr = minNode;							// go to the smallest adjacent vertex
		if (curr == -1)							// no relaxation available
			break;

		visited[curr] = true;
		visitedCount +=1;
	}

	// deallocate memory
	delete[] visited;
	double distance = dist[n];
	delete[] dist;

	return distance;
}

void Weighted_graph::insert(int m, int n, double w) {
	if (w <= 0 || w == INF || n < 0 || m < 0 || n > size - 1 || m > size - 1 || m == n) {
		throw illegal_argument();
	}
	// if an edge exists
	if (weight_adj_matrix[m][n] != INF) {
		weight_adj_matrix[m][n] = w;
		weight_adj_matrix[n][m] = w;
	} else {
		// otherwise, also increment the number of edges and the degrees of both vertices
		weight_adj_matrix[m][n] = w;
		weight_adj_matrix[n][m] = w;
		edges++;
		deg[m]++;
		deg[n]++;
	}
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
