There are  people at the railway station, and each one wants to buy a ticket to go to one of  different destinations. The  people are in a queue.

There are  ticket windows from which tickets can be purchased. The  people will be distributed in the windows such that the order is maintained. In other words, suppose we number the people  to  from front to back. If person  and person  go to the same window and , then person  should still be ahead of person  in the window.

Each ticketing window has an offer. If a person in the queue shares the same destination as the person immediately in front of him/her, a 20% reduction in the ticket price is offered to him/her.

For example, suppose there are  people in the queue for a single ticket window, all with the same destination which costs  bucks. Then the first person in the queue pays  bucks, and the 2nd and 3rd persons get a discount of 20% on  bucks, so they end up paying  bucks each instead of  bucks.

Try to distribute the  people across the  windows such that the total cost  paid by all  people is minimized.

Input Format

The first line contains  integers:

 is the number of people
 is the number of ticket windows
 is the number of destinations separated by a single space (in the same order)
Then  lines follow. The  line contains an alphanumeric string  and an integer :

 is the  destination
 is the ticket price for 
Then  lines follow. The  line contains an alphanumeric string  which is the destination of the  person.

Constraints

The  available destinations have nonempty and distinct names.
Each person's destination appears in the list of  available destinations.
Output Format

Output  lines. The first line contains , the total cost that is to be minimized. In the  following line, print the ticket window which the  person goes to. The windows are indexed  to . There may be multiple ways to distribute the people among the windows such that the total cost is minimized; any one will be accepted.

The answer  will be accepted if it is within an error of  of the true answer.

Sample Input

5 2 3
CALIFORNIA 10
HAWAII 8
NEWYORK 12
NEWYORK
NEWYORK
CALIFORNIA
NEWYORK
HAWAII
Sample Output

49.2
1
1
2
1
1
Explanation

At the beginning, all the people are in the same queue, and will go to the ticket windows one by one in the initial order.

 will buy ticket in the first window.
 will buy ticket in the second window.
In the first ticket window, #1 will pay  bucks to go to NEWYORK, and #2 and #4 have the same destination with the person in front of them, so they will get 20% off, and will pay  bucks each. #5 has a different destination, so it will cost him  bucks to go to HAWAII.

In the second ticket window, #3 will pay  bucks to go to CALIFORNIA.
