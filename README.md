
  <h1 align="center">Min Cost Arborescence</h1>
  
### About the project
1. This project is the c++ implementation of Edmond's Branching Algorithm to find minimum cost arborescence.
2. Find details about the algorithm here: https://drive.google.com/file/d/1k9FDRx2BQ49y0B5egzCysGSjCXWnwB6-/view?usp=sharing
3. I have tested the algorithm to work on 1500-2000 nodes graph.
4. Look for input and output format in the testCase.txt file.
  
### Input format
* First line: Number of Test Cases <b>T</b>
* For each test case, First line/row indicate <b>N M s</b> (single space separated); where,
     1. <b>N</b> is number of vertices in directed graph where vertices are labelled 1 to N (not 0 indexing)
     2. <b>M</b> is the number of edges.
     3. <b>s</b> is the index of source vertex
     4. And then <b>M</b> rows mentioning <b>u v w</b>(single space separated, where <b>u</b> and <b>v</b> are vertex ids and <b>w</b> is weight.
### Assumptions
* All edge weights are non-negative.
* Whenever choices with equal considerations, prefer to consider vertices in lexicographic ordering.


### Output format

* For each test case, print <b>2N+1+1</b> entries (all single space separated)
* First entry is the total sum of min cost arborescence
* Then N entries corresponding to vertices V1, V2, V3..., VN providing the distance of i-th vertex from the
source vertex s. (print -1 if unreachable)
* Then print symbol <b>#</b>.
* Then print N entries (corresponding to vertices V1, V2, V3..., VN) providing the label of the parent node through
which one reaches i-th vertex (basically second last node in path from source vertex to that i-th vertex. (Indicate
0 if no parent i.e. for source vertex and -1 if vertex i not reachable).


### Instructions to run
``g++ main.cpp -o main && ./main<testCase.txt>output.txt``







