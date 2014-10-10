// Program:		Aubiebook
// Name:		Michael Americo Pace
// Class:		COMP 2710
// Date: 		October 20, 2012
// Email: 		map0009@auburn.edu
//
// Description:	This class represents a Message beit a tweet or post. Has variables to know
//				the time in which the message was made, the poster and the content of the message.
#ifndef MESSAGE_H
#define MESSAGE_H
#define MAX_MESSAGE_SIZE	256
using namespace std;

enum MessageType { POST, TWEET };

class Message 
{
	public:
	MessageType type;
	int timeStamp;
	string poster;
	string message;
};
#endif