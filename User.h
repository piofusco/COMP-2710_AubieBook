// Program:		Aubiebook
// Name:		Michael Americo Pace
// Class:		COMP 2710
// Date: 		October 20, 2012
// Email: 		map0009@auburn.edu
//
// Description:	Class definition of User class.
#ifndef USER_H
#define USER_H
#include <vector>
#include <iostream>
#include <fstream>
#include "Message.h"
using namespace std;
class User 
{
   	public:
	User(string username);
	bool haveSameName(string someName);
	void setName(string username);
	bool isFriendsWith(string possibleFriend);
	void printFriends();
	void initializeFriendsVector();
	string toString();
	void addFriend(string friendName);

	string name;
	string userFile;
	string friendFile;
   	vector<string> friends;
};
#endif