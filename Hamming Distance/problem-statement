You are given a string , consisting of  small latin letters 'a' and 'b'. You are also given  queries to process. The queries are as follows:

C   : all the symbols in the string, starting at the , ending at the  become equal to ;
S    : swap two consecutive fragments of the string, where the first is denoted by a substring starting from  ending at  and the second is denoted by a substring starting at  ending at ;
R  : reverse the fragment of the string that starts at the  symbol and ends at the  one;
W  : output the substring of the string that starts at the  symbol and ends at the  one;
H   : output the Hamming distance between the consecutive substrings that starts at  and  respectively and have the length of .
Everything is 1-indexed here.

Input Format

The first line of input contains a single integer   the length of the string.
The second line contains the initial string  itself.
The third line of input contains a single integer   the number of queries.
Then, there are  lines, each denotes a query of one of the types above.

Constraints



Total number of characters printed in W-type queries will not exceed 
For C-type, R-type, W-type queries: ;  equals either a, or b
For S-type queries: 
For H-type queries: ; ; .

Output Format

For each query of the type W or the type H output an answer on the separate line of output.

Sample Input 0

10
aabbbabbab
6
R 1 5
W 3 8
C 4 4 a
H 2 1 9
S 5 9 10 10
H 1 2 9
Sample Output 0

baaabb
4
5
Explanation 0

Initial String - aabbbabbab

Queries	Updated String	Output
R 1 5	bbbaaabbab	
W 3 8		baaabb
C 4 4 a	bbbaaabbab	
H 2 1 9		4
S 5 9 10 10	bbbabaabba	
H 1 2 9		5
