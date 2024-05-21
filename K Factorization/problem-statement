At the time when Pythagoreanism was prevalent, people were also focused on different ways to factorize a number. In one class, Pythagoras asked his disciples to solve one such problem, Reverse Factorization. They were given a set of integer, , and an integer . They need to find the a way to reach , starting from , and at each step multiplying current value by any element of . But soon they realised that there may exist more than one way to reach . So they decided to find a way in which number of states are least. All of sudden they started on this new problem. People solved it and then started shouting their answer. CRAP!!!. There still exists multiple answers. So finally after much consideration, they settled on the lexicographically smallest series among those solutions which contains the least number of states.

For example, if  and  then following ways exists

(a) 1  ->  2  ->  4  ->  12
       x2     x2     x3

(b) 1  ->  4  ->  12
       x4     x3

(c) 1  ->  3  ->  12
       x3     x4
Here (a) is not the minimal state, as it has  states in total. While (b) and (c) are contenders for answer, both having 3 states, (c) is lexicographically smaller than (b) so it is the answer. In this case you have to print 1 3 12. If there exists no way to reach  print -1.

Input Format

Input contains two lines where first line contains two space separated integer,  and , representing the final value to reach and the size of set , respectively. Next line contains K space integers representing the set .

Constraints

, where 
, where  AND 
Note:

Lexicographical order: If  and  are two ordered lists, then  is lexicographically smaller than  if any one of the following condition satisfies.

 AND .
 AND  AND .
You need to find the lexigraphically smallest series among those solutions which contains the least number of states.

Output Format

Print the steps to reach  if it exists. Otherwise print -1.

Sample Input 0

12 3
2 3 4
Sample Output 0

1 3 12
Explanation 0

This is the same case which is explaned above.

Sample Input 1

15 5
2 10 6 9 11
Sample Output 1

-1
Explanation 1

Here no way exists so that we can reach  starting from .

Sample Input 2

72 9
2 4 6 9 3 7 16 10 5
Sample Output 2

1 2 8 72
Explanation 2

There are multiple ways to reach 72 using these 8 numbers. Out of which following 6 ways consists of minimal states (4).

States          =>  Multiplication operation
 1   9  18  72  =>      (x9, x2, x4)
 1   4  36  72  =>      (x4, x9, x2)
 1   2   8  72  =>      (x2, x4, x9)
 1   2  18  72  =>      (x2, x9, x4)
 1   4   8  72  =>      (x4, x2, x9)
 1   9  36  72  =>      (x9, x4, x2)
As series 1 2 8 72 is lexicographically smallest, it is the answer.
