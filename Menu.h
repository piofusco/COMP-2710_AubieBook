// Program:		Aubiebook
// Name:		Michael Americo Pace
// Class:		COMP 2710
// Date: 		October 20, 2012
// Email: 		map0009@auburn.edu
//
// Description:	Class definition of the menu class.
#ifndef MENU_H
#define MENU_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <sstream>
#include "Message.h"
#include "User.h"

#define TWEET_FILENAME "tweet.txt"        // Text which holds all tweets
#define VALID_USERS_FILENAME "users.txt"  // Text which holds all valid users

using namespace std;
   class Menu	{
   public:
      Menu();
      //file I/O
      void initializeValidUsers();
      void initializeTweets();
      void initializePosts();
      void initializeMessageList();
      void putPosts();
      void putTweets();
      
      //user I/O
      char promptMenuChoice();
      void promptLogin();
      void promptAddFriend();
      void promptPostMessage();
      void promptTweet();
      bool promptMoreMessages();
      bool isValidChoice(char choice);
      int handleChoice(char choice);
      
      //display
      int startMenu();
      void displayWelcome();
      void updateWelcome();
      void displayMenu();
      void displayWall();
      void displayHomePage();
      void displayExit();
      void printValidUsers();
      void messageListDump();
      
      //data manipulation
      string splitLines(string sub);
      void initializeValidChoices();
      void formatPost(string substring, string someUser);
      void formatTweet(string substring);
      void createUser(string possibleUser);
      int isUserValid(string possibleUser);
      int totalWall();
      int totalFriends();
      int totalHome();
      int numberOfUserPosts();
      int numberOfUserAndFriendsPosts();
      
      time_t currentTime;           // int that is used as a time signiture for tweets and messages
      bool userExists;              // bool value - true if at least one user has been created                
      User* currentUser;            // User object that menu references as current user
      vector<User*> validUsers;     // vector of User objects which are valid Users
      vector<char> validChoices;    // vector of valid users entries for the menu
      list<Message*> messageList;   // list of Message's used as a map to print out wall and home pages
      string SPACETILDESPACE;       // " ~ " this sequence of characters is added to a users name before the message
      string NEWLINE;               // "\n" used to separate messages
      string DOLLARSIGN;            // "$" - used as a delimiter to take in messages
      char OPEN_BRACKET;            // '<' and '>' separate names in messages
      char CLOSED_BRACKET;
};
#endif