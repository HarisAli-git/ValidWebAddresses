#include <iostream>
#include <Windows.h>
#include <string>
int state = 0;												// curr_state variable
using namespace std;

void print_tst(const string &str, int &i)					// Trap_State function.. prints out the trap state explicilty
{
	for (; i < str.length(); i++)
	{
		cout << ' ' << str[i] << " Trap" << ' ' << '\n';
	}
}

void print_st(const char& c, const int& st)
{
	cout << ' ' << c << " q" << st << ' ' << '\n';			// print the current state along with the character
}

void eve_rem(const string &str, int &i, const int& st)		// this function evaluates the remaining string
{
	for (; i < str.length(); i++)
	{
		if (str[i] == '.')
			print_st(str[i], st);
		else if (str[i] == 'c')
		{
			print_st(str[i++], 8);
			if (str[i] == 'o' && i != str.length())
				print_st(str[i++], 9);
			if (str[i] == 'm' && i != str.length())
				print_st(str[i++], 10);
			if (i != str.length())
				print_tst(str, i);					// if string hasnt completed yet send it to the trap state
		}
		else if (str[i] == 'p')
		{
			print_st(str[i++], 11);
			if (str[i] == 'k' && i != str.length())
				print_st(str[i++], 12);
			if (i != str.length())
				print_tst(str, i);					// if string hasnt completed yet send it to the trap state
		}
		else
			print_tst(str, i);					// if the string doesnt have . or c or p then send it to the trap state
	}
}

void print_st_com(const string& str, int st)		// printing .com with respect to each state 
{
	int len = str.length();
	print_st(str[len - 4], st);
	if (st == 7)
		st++;
	if (st == 6)
		st = 8;
	print_st(str[len - 3], st++);
	print_st(str[len - 2], st++);
	print_st(str[len - 1], st++);
}

void print_st_pk(const string& str, int st)				// printing .pk with respect to each state
{
	int len = str.length();
	print_st(str[len - 3], st);
	if (st == 7)
		st = 11;
	if (st == 6)
		st = 11;
	print_st(str[len - 2], st++);
	print_st(str[len - 1], st++);
}

bool Check_dot_pk(const string &str)			// Function Checks that whether last 4 digits are .com
{
	int len = str.length();
	if (str[len - 3] != '.')
		return false;
	if (str[len - 2] != 'p')
		return false;
	if (str[len - 1] != 'k')
		return false;

	return true;
}

bool Check_dot_com(const string &str)			// Function Checks that whether last 4 digits are .com
{
	int len = str.length();
	if (str[len - 4] != '.')
		return false;
	if (str[len - 3] != 'c')
		return false;
	if (str[len - 2] != 'o')
		return false;
	if (str[len - 1] != 'm')
		return false;

	return true;
}


int check_S2S3(const string &str, int &i, int st)				// function checks the two sets S1 and S2 states
{
	int len = str.length();
	for (; str[i] != '.' && i != str.length(); i++)				// begin the evaluation of S2 set
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			print_st(str[i], st);
		}
		else
		{
			print_tst(str, i);
			return 0;
		}
		if (st == 6)
			st--;

	}
	if (i != str.length())									// if the string hasnt been ended then evaluate further set S3
	{
		int diff = len - i;
		if (st == 4)
			st = 7;
		else if (st == 5)
			st = 6;
		if (diff == 4 || diff == 3)
		{
			if (Check_dot_com(str) && (str.length() >= 5))
			{
				print_st_com(str, st);
				return 1;
			}
			else if (Check_dot_pk(str) && (str.length() >= 4))
			{
				print_st_pk(str, st);
				return 1;
			}
			else
			{	 // evaluate the remaining string
				eve_rem(str, i, st);
				return 0;				// if rejected, return 0
			}
		}
		else
		{		// evaluate the remaining string
			eve_rem(str, i, st);
			return 0;				// if rejected, return 0
		}
	}
	return 0;				// if rejected, return 0
}

void main()
{
	cout << "Haris Ali : 18L-1247\nTheory of Automata - Programming Assignment 1\n";
	cout << "Program checks if a website name is correct\n\n";

start:
	{
		cout << "\n\nWant to enter a string? (y/n) : ";
		char ch = NULL;

		cin >> ch;

		while (ch != 'n' && ch != 'N' && ch != 'y' && ch != 'Y')
		{
			cout << "\nPlease Enter a valid input i.e (y/n)!\n";
			cin.ignore();
			cin >> ch;
		}

		if (ch == 'n' || ch == 'N')							// if the user presses N or n, then exit the program
		{
			cout << "\nAs the user have choosen not to enter any string, hence the program will now terminate!\n";
			system("pause");
			return;											// terminating the program
		}

		else
		{													// else, create a string and take user input
			string str;
			state = 0;
			cout << "\nEnter the string: ";
			cin.ignore();
			getline(cin, str);
			int len = str.length(), wc = 0;
			for (int i = 0; i != len; i++)				// traversing the string in this loop
			{
				if (str[i] == 'w')						// if 'w' comes evaluate it seperately
				{
					if (wc <= 3)						// if 3 w's are completed then dont move further
					{
						print_st(str[i], ++state);
						wc++;
					}
					else
					{
						print_st(str[i], 4);
						wc++;
					}
				}
				else if (i > 0 && str[i] == '.')			// if a dot comes after first digit then evaluate it in this block
				{
					int sw = 6;
					if (wc > 3)								// check whether www has passed the evaluation
						sw = 7;								// if yes then state will be changed

					if (str[i + 1] == 'c')
					{
						if (str[i + 2] == 'o' && str[i + 3] == 'm' && i + 4 == str.length())
						{
							print_st_com(str, sw);
							cout << "\nAccepted";
							break;
						}
						if ((str[i + 1] >= 'a' && str[i + 1] <= 'z'))
						{
							if (wc > 3)						// check whether www has passed the evaluation
							{
								eve_rem(str, i, sw);		// if yes then evaluate remaining string
								cout << "\nRejected";
								break;
							}

							print_st(str[i++], 6);

							if (check_S2S3(str, i, 5) == 1)			// check the S2S3 sets
							{
								cout << "\nAccepted";
							}
							else
							{
								cout << "\nRejected";
							}
							break;
						}
						else
						{
							eve_rem(str, i, sw);
							cout << "\nRejected";
							break;
						}
					}
					else if (str[i + 1] == 'p')
					{
						if (str[i + 2] == 'k' && i + 3 == str.length())
						{
							print_st_pk(str, sw);
							cout << "\nAccepted";
							break;
						}
						else if ((str[i + 1] >= 'a' && str[i + 1] <= 'z'))
						{
							if (wc > 3)						// check whether www has passed the evaluation
							{
								eve_rem(str, i, sw);		// if yes then evaluate remaining string
								cout << "\nRejected";
								break;
							}

							print_st(str[i++], 6);

							if (check_S2S3(str, i, 5) == 1)			// check the S2S3 sets
							{
								cout << "\nAccepted";
							}
							else
							{
								cout << "\nRejected";
							}
							break;
						}
						else
						{
							eve_rem(str, i, sw);					// evaluate the remaining string
							cout << "\nRejected";
							break;
						}
					}

					else if (str[i + 1] >= 'a' && str[i + 1] <= 'z')		// if a to z letters come then execute this block
					{
						if (wc > 3)						// check whether www has passed the evaluation
						{
							eve_rem(str, i, sw);		// if yes then evaluate remaning string
							cout << "\nRejected";
							break;
						}

						print_st(str[i++], 6);

						if (check_S2S3(str, i, 5) == 1)			// check the S2S3 sets
						{
							cout << "\nAccepted";
						}
						else
						{
							cout << "\nRejected";
						}
						break;
					}
					else
					{
						eve_rem(str, i, sw);					// evaluate the remaining string 
						cout << "\nRejected";
						break;
					}

				}
				else if (str[i] >= 'a' && str[i] <= 'z')		// if there's a to z input move on to the q5, if w comes first then this block will be ignored
				{
					int st = 5;
					if (wc > 3)									// check whether 4 w's have come already
						st = 4;
					if (check_S2S3(str, i, st) == 1)			// check the S2S3 sets
					{
						cout << "\nAccepted";
					}
					else
					{
						cout << "\nRejected";
					}
					break;
				}
				else
				{								// Trap state has occured
					print_tst(str, i);			// Rest of the inputs will be in trap
					cout << "\n Rejected";
					break;
				}
			}
		}
	}
	goto start;				// transfer the control of the program again to the start label (moving to the step-2 again)
	system("pause");
}
