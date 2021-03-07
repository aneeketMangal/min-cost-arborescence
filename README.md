
  <h1 align="center">Min Cost Arborescence</h1>
  
* <h3><a href="https://drive.google.com/file/d/1k9FDRx2BQ49y0B5egzCysGSjCXWnwB6-/view?usp=sharing">About the algorithm</a></h3>

### Input format

* First line: Number of Test Cases <b>T</b>
* For each test case, First line/row indicate N D (single space separated); where,
     1. <b>N</b> is number of vertices in directed graph where vertices are labelled 1 to N (not 0 indexing)
     2. <b>D</b> specifies whether Directed Graph or undirected graph (D=0 means undirected, else it is directed)
     3. This is then followed by N lines each containing N integers (basically NxN Adjacency or say weight matrix representation of the graph of that test case).

### Assumptions
* There are no self-loops in the graph
* Diagonal entries are zero.
* The weight = 999999 indicates that there is no edge between those two vertices considered.
* -999 ≤ Adj matrix values ≤ 999 
* Whenever choices with equal considerations, prefer to consider vertices in lexicographic ordering.


## Output format
* If there is any negative weight cycle in graph, print -1.
* Else print NxN shortest path matrix.
* Print 999999 if the vertex is not reachable from the source vertex considered.

## Instructions to run
<b>First compile the code using g++ main.cpp</b>
* ./a.out 1  ----> <b>Array Heap</b>
* ./a.out 2  ----> <b>Binary Heap</b>
* ./a.out 3  ----> <b>Binomial Heap</b>
* ./a.out 4  ----> <b>Fibonacci Heap</b>





# min-cost-arborescence

1. This implementation uses a recursive implementation of Edmond's Branching Algorithm.
2. You may find better insight at here: https://drive.google.com/file/d/1k9FDRx2BQ49y0B5egzCysGSjCXWnwB6-/view?usp=sharing
3. I have tested the algorithm to work on 1500-2000 nodes graph.
4. Look for input and output format in the testCase.txt file.
