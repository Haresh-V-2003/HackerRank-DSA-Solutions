There are  points on a plane. Each point  is described by , where . There are three types of queries needed: 

X i j Reflect all points in the inclusive range between points  and  along the -axis.
Y i j Reflect all points in the inclusive range between points  and  along the -axis.
C i j Count the number of points in the inclusive range between points  and  in each of the  quadrants. Then print a single line of four space-separated integers describing the respective numbers of points in the first, second, third, and fourth quadrants in that order.
As a reminder, the four quadrants of a graph are labeled as follows:


Given a set of  points and  queries, perform each query in order. For example, given points  and . Initially the points are in quadrants  and . The first query says to reflect points with indices from  to  along the -axis. After the query,  and quadrants are  and . The next query prints the number of points in each quadrant: 0 1 0 1. The third query says to reflect the point with index  to  along the -axis, so now . The points now lie in quadrants  and , so the fourth query output is 0 1 1 0.

Note: Points may sometimes share the same coordinates.

Function Description

Complete the quadrants function in the editor below. It should print the results of each C type query on a new line.

quadrants has the following parameters:
- p[p[1]...p[n]]: a 2-dimensional array of integers where each element  contains two integers  and 
- queries[queries[1]...queries[n]: an array of strings

Input Format

The first line contains a single integer, , that denotes the number of points.
Each line  of the  subsequent lines contains two space-separated integers that describe the respective  and  values for point  .
The next line contains a single integer, , that denotes the number of queries.
Each of the  subsequent lines contains three space-separated values that describe a query in one of the three forms defined above.

Constraints

No point lies on the  or  axes.
In all queries, .
Output Format

For each query of type C i j, print four space-separated integers that describe the number of points having indices in the inclusive range between  and  in the first, second, third, and fourth graph quadrants in that order.

Sample Input

4
1 1
-1 1
-1 -1
1 -1
5
C 1 4
X 2 4
C 3 4
Y 1 2
C 1 3
Sample Output

1 1 1 1
1 1 0 0
0 2 0 1
Explanation

Initially,  so there is one point in each of the four quadrants. The first query results in printing 1 1 1 1.

The second query, X 2 4, reflects the points in the inclusive range between indices  and  along the -axis. Now .

The query C 3 4 requires that the number of points considering  through  be printed: 1 1 0 0

The third query, Y 1 2 requires reflection of  along the -axis. Now .

The last query, C 1 3 requires that the number of points considering  through  be printed: 0 2 0 1
