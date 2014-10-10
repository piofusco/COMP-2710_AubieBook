// Program:		Aubiebook
// Name:		Michael Americo Pace
// Class:		COMP 2710
// Date: 		October 20, 2012
// Email: 		map0009@auburn.edu
//
// Description:	This class represents a User on AubieBook. User's have friends, post messages
//				and tweets.
// Compile instructions:   g++ User.cpp -o lab2
#include "User.h"
	
// Function:	Single parameter constructor for User
// Inputs:		name of new User
// Description:	Creates a new User and sets their name to string username. string values of the
//				user's files are written to more easily call on the file names. User's friends
//				must be read in from his friends file. This is done with initializeFriendsVector.
User::User(string username)	
{
	name = username;
	userFile = username + ".txt";
	friendFile = username + "_friends.txt";
	initializeFriendsVector();
}

// Function:      haveSameName
// Inputs:        user to be checked if friends with current user
// Outputs:       Returns true if current user and parameter are the same user
// Descriptions:  Checks if current user is the same as argument
bool User::haveSameName(string someName)
{
	if(name == someName)
	{
		return true;
	}
	return false;
}

// Function:		setName	
// Inputs:			name of user
// Descriptions:	Sets the name of current user
void User::setName(string username)	
{
	name = username;
}

// Function:      isFriendsWith 
// Inputs:        user to be checked if friends with current user
// Outputs:       Returns true if current user and parameter are friends
//                and false otherwise
// Descriptions:  Checks if current user is friends with parameter.
bool User::isFriendsWith(string possibleFriend)	
{
	if(friends.size() == 0)
	{
		return false;
	}
	vector<string>::iterator friend_iter;
	for(friend_iter=friends.begin(); friend_iter < friends.end(); friend_iter++)
	{
		if((*friend_iter) == possibleFriend)
		{
			return true;
		}
	}
	return false;
}

// Function:      printFriends
// Output:        prints current users list of friends
// Description:   Iterates through list of friends of current user and prints each one.
void User::printFriends()	
{
	vector<string>::iterator friend_iter = friends.begin();
	cout <<"\n" << name<< "'s friends..." << endl;
	for(friend_iter=friends.begin(); friend_iter < friends.end(); friend_iter++)
	{
		cout<<"\t"<<(*friend_iter)<<endl;
	}
}

// Function:		initializeFriendsVector
// Description:		Reads user's file containing friends. Copies each line to create a new user. Pushes
//					this user to vector friends. Prevents having to constantly read the file each time friends
//					are referenced.
void User::initializeFriendsVector()	
{	
	friends.clear();
	char temp[MAX_MESSAGE_SIZE];
	string tempString;

	ifstream fileIn;
	fileIn.open(friendFile.c_str());
	// If file hasn't been created, create it
	if( fileIn.is_open() == false)
  	{
  		ofstream fileOut;
  		fileOut.open(friendFile.c_str());
  		fileOut.close();
   	}
   	// Read each line of file, store each line to tempString, push tempString into friends vector
   	while(fileIn.good())
   	{
   		fileIn.getline(temp, MAX_MESSAGE_SIZE, '\n');
		tempString = temp;
		friends.push_back(tempString);
   	}
   	fileIn.close();
}

// Function:	toString
// Outputs:     returns string name of User
string User::toString()	
{
  return name;
}

// Function:		addFriend
// Input:			friendName
// Description:		Takes in string name and pushes this string to vector of friends
void User::addFriend(string friendName)
{
	friends.push_back(friendName);
	ofstream fileOut;
	fileOut.open(friendFile.c_str());
	fileOut << friendName << endl;
}