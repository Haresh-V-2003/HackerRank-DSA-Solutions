A tree of  nodes is an un-directed connected graph having  edges. Let us denote  as the root node. If  is a node such that it is at a distance of  from , and  is a node such that it is at at distance of  from  and  is connected to , then we call  as the parent of .

Similarly, if  is at a distance of  from  and  is at a distance of  from  and there is a path of length  from  to , then we call  as the th parent of .

Susan likes to play with graphs and Tree data structure is one of her favorites. She has designed a problem and wants to know if anyone can solve it. Sometimes she adds or removes a leaf node. Your task is to figure out the th parent of a node at any instant.

Input Format

The first line contain an integer  denoting the number of test cases.  test cases follow. First line of each test case contains an integer , the number of nodes in the tree.  lines follows each containing two integers  and  separated by a single space denoting  as the parent of . If  is , then X is the root node of the tree. ( is for namesake and is not in the tree).
The next line contains an integer , the number of queries.
 lines follow each containing a query.

   :  is added as a new leaf node whose parent is  .  is not in the tree while  is in.
  : This tells that leaf node  is removed from the tree.  is a leaf in the tree.
   : In this query output the th parent of  .  is a node in the tree.
Note

Each node index is any number between 1 and 105 i.e., a tree with a single node can have its root indexed as 105
Constraints







Output Format

For each query of type , output the th parent of . If th parent doesn't exist, output  and if the node doesn't exist, output .

Sample Input

2
7
2 0
5 2
3 5
7 5
9 8
8 2
6 8
10
0 5 15
2 15 2
1 3
0 15 20
0 20 13
2 13 4
2 13 3
2 6 10
2 11 1
2 9 1
1
10000 0
3
0 10000 4
1 4
2 4 1
Sample Output

2
2
5
0
0
8
0
Explanation

There are 2 test cases. The first test case has 7 nodes with 2 as its root. There are 10 queries

0 5 15 -> 15 is added as a leaf node to 5.
2 15 2 -> 2nd parent of 15 is 15->5->2 is 2.
1 3 -> leaf node 3 is removed from the tree.
0 15 20 -> 20 is added as a leaf node to 15.
0 20 13 -> 13 is added as a leaf node to 20.
2 13 4 -> 4th parent of 13 is 2.
2 13 3 -> 3rd parent of 13 is 5.
2 6 10 -> there is no 10th parent of 6 and hence 0.
2 11 1 -> 11 is not a node in the tree, hence 0.
2 9 1 -> 9's parent is 8.
the second testcase has a tree with only 1 node (10000).

0 10000 4 -> 4 is added as a leaf node to 10000.
1 4 -> 4 is removed.
2 4 1 -> as 4 is already removed, answer is 0.
