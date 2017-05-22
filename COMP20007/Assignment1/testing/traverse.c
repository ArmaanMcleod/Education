/* * * * * * *
 * Module for completing coding tasks from assignment 1
 *
 * created for Assignment 1 COMP20007 Design of Algorithms 2017
 * by Armaan Dhaliwal-Mcleod 837674 <dhaliwala@student.unimelb.edu.au>
 */

// libraries and header files included for this module 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "traverse.h"
#include "stack.h"
#include "queue.h"


// struct which holds information about a current path
// used for parts 3, 4 and 5. 

typedef struct {
	Vertex **path;    // array of current vertices in path
	int len;          // current size of array
	int *visited;     // keeps track of visited vertices
} Current_path;


// struct which holds information about shortest path
// used solely for part 5

typedef struct {
	Vertex **shortestpath;    // array of current vertices in shortest path
	int len;				  // current size of array
	int dist;                 // cumulative distance of path
} Shortest_path;


// static function prototypes used in this mddule
static void dfs_detailed_path(Graph* graph, int source_id, 
	                int destination_id, Current_path *data); 

static void all_paths_dfs(Graph* graph, int source_id, 
	                int destination_id, Current_path *data);

static void shortest_path_dfs(Graph *graph, int source_id, 
	                int destination_id, Current_path *data, Shortest_path *path);

static void allocate_current_path(Current_path *data, int size);

static void allocate_shortest_path(Shortest_path *path, int size);


// function which prints depth-first exploration of network from given town
// takes as input a connected graph of road networks, and starting town index
// ideas based from <https://en.wikipedia.org/wiki/Depth-first_search>
void print_dfs(Graph* graph, int source_id) {
	int visited[graph->n], u, v, i;

	// initialize to false
	// used to check if vertex has been visited during traversal 
	for (i = 0; i < graph->n; i++) {
		visited[i] = 0;
	}

	// create empty stack
	Stack *S = new_stack();

	// push starting vertex onto stack
	stack_push(S, graph->vertices[source_id]);

	// main loop, which performs the bulk of depth first search
	// stops when stack is empty, which implies traversal is complete
	while (stack_size(S) > 0) {

		// pop most recently added vertex on top of the stack
		Vertex *top = stack_pop(S);
		u = top->first_edge->u;

		// check if vertex has not been visited
		if (visited[u] == 0) {

			// since unvisted, print out town
			printf("%s\n", top->label);

			// mark as visited
			visited[u] = 1;

			// create new temporary stack
			Stack *temp = new_stack();

			// check neighbours in adjancency list of popped vertex 
			// processes in order of vertex edge list
			while (top->first_edge != NULL) {
				v = top->first_edge->v;

				// check if vertex has not been visited
				if (visited[v] == 0) {

					// push onto temporary stack
					stack_push(temp, graph->vertices[v]);
				}
				top->first_edge = top->first_edge->next_edge;
			}

			// push vertices from temporary stack onto main stack
			// This allows items to be pushed in reverse order
			// This addition allows this algorithm to behave similarily to -
			// - recursive depth first search
			while (stack_size(temp) > 0) {
				Vertex *curr = stack_pop(temp);
				stack_push(S, curr);
			}

			// destroy temporary stack
			free_stack(temp);
		}
	}

	// destroy main stack
	free_stack(S);
}

// function which prints breadth-first exploration of network from given town
// takes as input a connected graph of road networks, and starting town index
// ideas based from <https://en.wikipedia.org/wiki/Breadth-first_search>
void print_bfs(Graph* graph, int source_id) {
	int visited[graph->n], u, v, i;

	// initialize to false
	// used to check if vertex has been visited during traversal 
	for (i = 0; i < graph->n; i++) {
		visited[i] = 0;
	}

	// create empty queue
	Queue *Q = new_queue();

	// enqueue starting vertex at the end of the queue                           
	queue_enqueue(Q, graph->vertices[source_id]);

	// main loop, which performs the bulk of breadth first search
	while (queue_size(Q) > 0) {

		// dequeue most recently added vertex to the queue
		Vertex *top = queue_dequeue(Q);
		u = top->first_edge->u;

		// check if vertex has not been visited
		if (visited[u] == 0) {

			// since unvisted, print out town
			printf("%s\n", top->label);

			// mark as visited
			visited[u] = 1;

			// check neighbours in adjancency list of popped vertex 
			// processes in order of vertex edge list
			while (top->first_edge != NULL) {
				v = top->first_edge->v;

				// check if vertex has not been visited
				if (visited[v] == 0) {

					// if not visited, enqueue vertex to the end of the queue
					queue_enqueue(Q, graph->vertices[v]);
				}
				top->first_edge = top->first_edge->next_edge;
			}
		}
	}

	// destroy queue
	free_queue(Q);
}

// function which prints out a simple path between a starting vertex and -
// -ending vertex, along with cumulative distances of each town along the path
// takes as input a connected graph of road networks, starting town index -
// -and destination town index
void detailed_path(Graph* graph, int source_id, int destination_id) {
	Current_path data;

	// allocate one path, which keeps track of vertices visited in the path 
	allocate_current_path(&data, graph->n);

	// calls helper function dfs_detailed_path() print out path
	dfs_detailed_path(graph, source_id, destination_id, &data);

	// finshed with current path information
	free(data.path);
	free(data.visited);
}

// helper function which performs depth first traversal to find a detailed -
// -path between two nodes in a fully connected graph
// takes as input a connected graph of road networks, starting town index, -
// -destination town index and information about the current path
// this implementation uses a modified recursive dfs to find a detailed path
static void dfs_detailed_path(Graph* graph, int source_id, 
	                          int destination_id, Current_path *data) {
	int v, dist, i;

	// mark current vetex as visited
	data->visited[source_id] = 1;

	// add vertex to current path
	data->path[data->len++] = graph->vertices[source_id];

	// condition which determines that the end of path has been found
	// ends recursion, since only one path is needed
	if (source_id == destination_id) {
		dist = 0;

		// prints out detailed path found, with cumulative distances
		for (i = 0; i < data->len; i++) {
			printf("%s (%dkm)\n", data->path[i]->label, dist);
			dist += data->path[i]->first_edge->weight;
		}
		return;
	}

	// look at neighbours of current vertex being explored
	Vertex *curr = graph->vertices[source_id];
	while (curr->first_edge != NULL) {
		v = curr->first_edge->v;

		// check if vertex has been visited
		if (data->visited[v] == 0) {

			// recursively search neigbours of current vertex
			dfs_detailed_path(graph, v, destination_id, data);
		}
		curr->first_edge = curr->first_edge->next_edge;
	}
}

// function which prints out all simple paths between two nodes in a fully -
// -connected graph
// takes as input a connected graph of road networks, starting town index and -
// -destination town index
void all_paths(Graph* graph, int source_id, int destination_id) {
	Current_path data;

	// allocate one path, which keeps track of vertices visited in the path 
	allocate_current_path(&data, graph->n);

	// calls helper function all_paths_dfs() print out all paths
    all_paths_dfs(graph, source_id, destination_id, &data);

    // finshed with current path information
    free(data.path);
	free(data.visited);
}

// helper function which performs depth first traversal to find all -
// -simple paths between two nodes in a fully connected graph
// takes as input a connected graph of road networks, starting town index, -
// -destination town index and information about the current path
// this implementation uses a modified backtracking recursive dfs
static void all_paths_dfs(Graph* graph, int source_id, 
	                      int destination_id, Current_path *data) {
    int i;

    // mark current vetex as visited
    data->visited[source_id] = 1;

    // add vertex to current path
    data->path[data->len++] = graph->vertices[source_id];

	// condition which determines that the end of path has been found
    if (source_id == destination_id) {

    	// prints out current path found
        for (i = 0; i < data->len-1; i++) {
            printf("%s, ", data->path[i]->label);
        }
        printf("%s\n", data->path[i]->label);
    }

    // look at neighbours of current vertex being explored
    Edge *curr = graph->vertices[source_id]->first_edge;
    while (curr != NULL) {

    	// check if vertex has been visited
        if (data->visited[curr->v] == 0) {

        	// recursively search neigbours of current vertex
            all_paths_dfs(graph, curr->v, destination_id, data);
        }
        curr = curr->next_edge;
    }

    // since current visited is all explored, it can removed
    data->len--;

    // mark as unvisited
    // very important as more paths can occur from this vertex
    data->visited[source_id] = 0;
}

// function which performs depth first traversal to find shortest path -
// -between two nodes in a fully connected graph
// takes as input a connected graph of road networks, starting town index and -
// -destination town index
void shortest_path(Graph* graph, int source_id, int destination_id) {
	Current_path data;
	Shortest_path path;
	int i;

	// allocate one path, which keeps track of vertices visited in the path 
	allocate_current_path(&data, graph->n);

	// allocate shortest path
	allocate_shortest_path(&path, graph->n);

	// calls helper function shortest_path_dfs() to find shortest path
	shortest_path_dfs(graph, source_id, destination_id, &data, &path);

	// prints out most recent shortest path found 
	for (i = 0; i < path.len-1; i++) {
		printf("%s, ", path.shortestpath[i]->label);
	}

	printf("%s (%dkm)\n", path.shortestpath[i]->label, path.dist);

	// finshed with current path and shortest path information
	free(data.path);
	free(data.visited);
	free(path.shortestpath);
}

// helper function which performs depth first traversal to find the shortest -
// -path between two nodes in a fully connected graph
// takes as input a connected graph of road networks, starting town index, -
// -destination town index and information about the current path and -
// -shortest path
// this implementation uses a modified backtracking recursive dfs
static void shortest_path_dfs(Graph *graph, int source_id, int destination_id, 
	                          Current_path *data, Shortest_path *path) {
	int i, currdist;

	// mark current vetex as visited
    data->visited[source_id] = 1;

    // add vertex to current path
    data->path[data->len++] = graph->vertices[source_id];

	// condition which determines that the end of path has been found
    if (source_id == destination_id) {
    	currdist = 0;

    	// accumulates a cumulative distance of current shortest path
        for (i = 1; i < data->len; i++) {
        	currdist += data->path[i]->first_edge->weight;
        }

        // compares current distance with previous distance
        if (currdist < path->dist) {

        	// updates current shortest path information
        	path->dist = currdist;
        	path->len = data->len;
        	for (i = 0; i < path->len; i++) {
        		path->shortestpath[i] = data->path[i];
        	}
        }
    } 

    // look at neighbours of current vertex being explored
	Edge *curr = graph->vertices[source_id]->first_edge;
	while (curr != NULL) {

		// check if vertex has been visited
        if (data->visited[curr->v] == 0) {

        	// recursively search neigbours of current vertex
            shortest_path_dfs(graph, curr->v, destination_id, data, path);
        }
        curr = curr->next_edge;
    }

     // since current visited is all explored, it can removed
    data->len--;

    // mark as unvisited
    // very important as more paths can occur from this vertex
    data->visited[source_id] = 0;
}

// helpter function to allocate contents of current path 
static void allocate_current_path(Current_path *data, int size) {

	// allocates path array 
	data->path = malloc(size * sizeof(*(data->path)));
	assert(data->path != NULL); 

	// allocates visited array
	data->visited = calloc(size, sizeof(*(data->visited)));
	assert(data->visited != NULL);

	// initializes starting length of array
	data->len = 0;
}

static void allocate_shortest_path(Shortest_path *path, int size) {

	// allocates shortest path array 
	path->shortestpath = malloc(size * sizeof(*(path->shortestpath)));
	assert(path->shortestpath != NULL);

	// initializes starting length of array
	path->len = 0;

	// set default distance
	path->dist = INT_MAX;
}

