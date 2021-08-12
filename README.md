# LinkAutomata
## DFA Diagram
![image](https://user-images.githubusercontent.com/68730185/129154429-ee0f36b3-8c5d-472a-aa8a-02f2f463d71a.png)
### In the above DFA, q0 is the starting state whereas, q10 and q12 are the final states

## Program Specs:
Program first asks user to input ‘y’ or ‘n’ as a yes or no. If the user enters a valid input then program asks the user to input a string. 
After the string is entered program checks step-by-step each state of the DFA. If any change of the state occurs, program changes itself accordingly. 
It outputs the character with its current state at each iteration. If at any iteration, the input goes on a trap state, then it will remain there till the rest of the string iteration is completed. 
There are separate functions to check the states and to change the state accordingly. After an input is completed, the program then prints Accepted or Rejected based on the string evaluation. The string is only considered accepted if it terminates on either q10 or q12. In the rest of the all cases, the string is rejected. 
The program has handled almost every case that I have given to it. For mine test case the program is working effectively. 

## Some of the string that I have tested:
1.	ww.com (accept)
2.	www.com (accept)
3.	wwww.com (accept)
4.	1.com (trap - reject)
5.	2.com (trap - reject)
6.	www.google.com (accept)
7.	www.lhr.nu (trap – reject)
8.	www.google (reject)
9.	www.lhr.nu.edu.pk (trap-reject)
10.	.com (trap-reject)
11.	.pk (trap – reject)
12.	lhr.com (accept)
These are just some of the strings, however, I have tested many.

