COMP-2710_AubieBook

Command-line Facebook clone in C++.
===================

Goals:

• To perform Object-Oriented Analysis, Design, and Testing

• To develop a non-trivial application using classes and constructors

• To learn distributed communication methods and develop a simple but useful distributed AubieBook system

• To learn to use file I/O and take advantage of the Network File System (NFS)

The proliferation of Internet applications in smartphones, laptops, ipads, and desktops shows the importance of communications among computing devices. One of the key functionalities is the ability to send and receive messages from one computer to another over the network. It is interesting to learn how a simple messaging system can provide this functionality. In this Lab 2, you will analyze, design, implement and test a simple distributed AubieBook system. It will have a simple text-based user interface that allows multiple users to send and receive messages to each other. In this lab project all the users must be implemented in distributed address space, i.e. each user must execute on a different computer and message of one user can be read by another through shared common files. The common files are shared through the Network File Server (NFS).

What is a Distributed AubieBook Message System?
You probably have used a distributed messaging system over the Internet. Although there are many different types of messaging systems, you will implement the Distributed AubieBook System that allows users to post and read messages from another user executing on a different computer. A user U can read the messages from another user V in two ways. The first method is by having U to add V as his friend and the system will retrieve messages posted by U. The second method is for V to tweet a message which will then be seen by all users, including U. For the purpose of this lab project, the Distributed AubieBook System is a program (or collection of programs) that does the following:

1) There are many distributed and concurrent users that use the AubieBook for posting their own messages and sharing them with their friends, i.e. all users may use the system simultaneously on different computers to post and read messages. In this assignment you must implement at least four users.

2) Each user can posts their message in their own wall page. The program must allow multiple lines of a message to be posted. The messages of each user are stored in a file with the user’s name, e.g. Jane’s wall page messages will be stored in the file called “Jane”. Since the file is maintained by NFS, another user Bill will also see the same file “Jane”, although it is executing on a different computer. The Distributed AubieBook System can then read the messages posted by Jane if Jane is Bill’s friend.

3) Each user can tweet a message which will be seen by all users. The program must allow multiple lines of a message to be tweeted. Messages tweeted by any user may be stored in a file called “tweet”. The format of the tweet messages will contain the user’s name, i.e. if Bill tweets a message “Greetings, everybody!”, then the message is stored in the file “tweet” as “<164><Bill>Greetings, everybody!”, where 164 is the timestamp. All users can then read the file “tweet” and display the user name and tweeted messages in reverse chronological order together with other messages.

4) Each user has a friend list which permits them to read the posted messages from the wall page file of each friend in the list. The user must be allowed to enter any name in the friend list only if the name is a valid user.

5) Each user has a home page. The home page of a user displays all the messages of all their friends, all tweeted messages from all users and all their own messages in reverse chronological order in which they are created, i.e. the most recent messages are displayed before the less recent messages.

6) In the home or wall pages, the program will first display only the three most recent messages from each friend, tweeted messages and messages from themselves, and prompt if the user wants to display more messages. If the response is “yes”, then all messages from themselves, tweeted messages and all their friends’ messages will be displayed, otherwise, the program will stop the display.

7) Since the users are each running on different computer, you must keep track of the time ordering of the messages. There are at least two methods for keeping track of the time ordering of the messages. The first method is to use the time() function to obtain the time and storing the time with the message. The second method is to maintain a file called “time”, shared by all the users. The file “time” contains an integer value which is incremented by one every time a user read the number to time-stamp their message. For example the number in the time file is initially 0. When Jane posts a message, the system will read the time file and time-stamp Jane’s message with 0. It then increments the time value and writes back 1 into the time file, over-writing the previous 0 value.
8) Each message stored in the wall page file of a user must NOT contain the name of the user, only the text message and the time-stamp. The name of the user is identified by the filename.

Message format
For this assignment, the messages must be stored in the file for each user using the following format. There must be exactly one message file for each user. In each of the user message file, the messages must be stored in reverse chronological order from which they were created. Each message must contain the timestamp and the user message using the following format “<Timestamp> message text”. The message must not contain the user’s name. However, each message must be of variable length. Different lines of a message must be separated by a ‘\n’ character, i.e. each line of the message must be terminated by a newline character. For examples, if John first entered the message “Welcome to the group!\nGreat to hear from you all!” And later John entered “I’ll update you all soon” then John’s message file must contain “<253>I’ll update you all soon<216> Welcome to the group!\nGreat to hear from you all!”. The string “<253>” is the timestamp enclosed in the < and > characters. Assume that messages will not contain these markers. The timestamp allows multiple messages sent by different users to be ordered correctly in reverse chronological order from which they were posted. The purpose for this standard message format is that everyone's wall message page should end up being compatible. That is, every user should be able to work with every friend’s wall messages.

Tweeted messages must use the following format “<Timestamp><Username> message text”. For example, if Bill tweets a message “Greetings, everybody!”, then the message is stored in the file “tweet” as “<164><Bill>Greetings, everybody!”, where 164 is the timestamp.

Your program must meet this requirement for message format, otherwise significant points will be deducted.

The user interface
Write a menu-based and text-based user interface for interacting with the Distributed AubieBook System. When the AubieBook system is first started, it will prompt for the user’s name. After the user’s name is entered, the system will print a banner welcoming the user.

Please enter user name: Bill
=========================================================== 
| Welcome to the AubieBook System, Bill! | 
===========================================================

The program will then make Bill the current user. If the file “Bill” exists, it will then read and update that file. If the file “Bill” does not exist, then it will first create the file “Bill” and then update and read “Bill” as the user posts messages and reads home or wall pages.

The main menu has (at least) 6 options to choose from as shown below. Abbreviate the menu so that all the 6 options can be shown in only one or two lines. The user interface will accept the option and all related inputs from the user, perform the operation and then repeatedly shows this menu of options again and prompts for the next option.

• Add a friend (f): When the user enters option ‘f’, the program will then prompt for the name of the friend. It then checks if the friend name is a currently valid user by checking if the wall page file with that user name exists. If so, it adds the friend in the current user’s friend list. If not, it’ll display an error message.

• Post a message (p): When the user enters option ‘p’, the program will prompt for the message and stores the message in the user’s wall page file with the user’s name. Your program must allow multiple lines of messages. To end a message, the user will enter a new line with a single ‘$’ character followed by hitting the enter key. The final ‘$’ character must not be stored in the message buffer; neither should it be displayed in the wall or home pages.

• Tweet a message (t): When the user enters option ‘t’, the program will prompt for the message and stores the message in the file “tweet”. As in posted messages, your program must allow multiple lines of messages. To end a message, the user will enter a new line with a single ‘$’ character followed by hitting the enter key.

• Display wall page (w): When the user enters option ‘w’, the program will first display a title indicating that it is displaying the current user’s wall page, e.g. “Jane’s Wall Page”. It then displays the latest three messages in the current user’s wall page and tweeted messages from that user only, in reverse chronological order. When displaying the wall page messages, it must NOT display the user’s name. After display the latest three messages (including tweet messages), it will then prompt the user if they want more messages. If the response is “no”, then it will stop displaying messages, but if the response is “yes”, it will display all the remaining messages from that user. If there are three or fewer messages then the program must not prompt for more messages.

• Display home page (h): When the user enters option ‘h’, the program will first display the current user home page title, e.g. “Joe’s Home Page”, and then it displays only the three latest messages either from the current user’s wall page, wall pages of all the friends of the current user, or tweeted messages from all users, whichever are the three latest messages. When displaying the message from each user, it must display the user name following by a ‘~’ and then followed by the message. It will then prompt the user if they want more. If the response is “no”, then it will stop displaying messages, but if the response is “yes”, it will display all the remaining messages from that user, wall pages of all the friends of the current user, and all tweeted messages. If there are three or fewer messages then the program must not prompt for more messages. In both the cases above, the messages are all displayed in reverse chronological order, i.e. the most recently posted messages will be displayed before the earlier messages.

• Quit this AubieBook System (q): When the user enters the option ‘q’, the program will exit normally.



SEE Example.txt for a Sample execution.
