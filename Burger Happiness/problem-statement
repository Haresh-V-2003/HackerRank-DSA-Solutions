In Burger Town new burger restaurants will be opened! Concretely,  restaurants will open in  days, while restaurant  will be opened on day  and will be located at . The town should be imagined as an one dimensional line in which every object's location can be described by the  coordinate.

Tim has just recently arrived the town after a very bad result in a programming contest. Thus he wants to cheer himself up by starting a trip to try out some new burgers.

Every burger restaurant  is associated with two integers  and . If Tim eats a burger from , then his happiness will increase by , which can also be negative, depending on the deliciousness of the burger. On the other hand, if Tim looks through the window of an opened restaurant , from which he will not eat a burger, then his happiness decreases by , since Tim gets sad by only seeing the burgers.

Tim's journey can start from any day  at the burger restaurant  and eats a burger from there. On each subsequent day , Tim has the following options:

Stay at the previous restaurant .
Or go to the new restaurant  to eat a burger from there.
If he decides for the latter option, then on the path from  to  he will look through all the windows that are on his path and maybe lose some happiness. Concretely, if , then he will look through the window of every opened restaurant , having . Similar for the case .

Since Tim is a very good friend of yours you should help him finding a trip that will maximize his happiness. If he should stay at home since no trip would cheer him up, then print 0.

Note: Tim's happiness is 0 at the beginning of the trip and is allowed to be negative throughout the time.

Input Format

 will be given on the first line, then  lines will follow, describing the restaurants numbered from 1 to  accordingly. Restaurant  will be described by ,  and  separated by a single space.

Output Format

Output the maximium happiness on one line.

Constraints




 and no two restaurants will have the same  coordinates.

Sample Input

 3
 2 -5 1
 1 5 1
 3 5 1
Sample Output

8
Sample Input

 4
 4 10 0
 1 -5 0
 3 0 10
 2 10 0
Sample Output

 15
Sample Input

 3
 1 -1 0
 2 -2 0
 3 -3 0
Sample Output

 0
First testcase: His trip starts on day 2 at restaurant 2 located at . He gains  happiness points there by eating a burger. On the next day he goes from restaurant 2 to 3, but will look through the window of restaurant 2 and 1. Therefore he loses  and  points on the way to restaurant 3. There he eats a burger and gains another  points. In total his happiness is equal to  8 and this is optimal.

Second testcase: His trip starts on day 1 at restaurant 1. Then his actions on day 2, 3 and 4 will be go to restaurant 2, stay at restaurant 2 and go to restaurant 4 respectively. The happiness of this optimal trip is equal to  15.

Third testcase: It's not worth to start the trip from any of the restaurant since he will only have negative happiness. That's why he should stay at home and 0 should be printed.
