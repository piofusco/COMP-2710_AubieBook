// Program:    Aubiebook
// Name:       Michael Americo Pace
// Class:      COMP 2710
// Date:       October 20, 2012
// Email:      map0009@auburn.edu
//
// Description:   This class handles user input and output. Found here are all methods that require
//                user to type information, ex: typing the friend name & posting messages.
//                Menu.cpp displays major text output such as greetings, welcomes, menu, name 
//                prompts and farewells. Writes all information to files accordingly.
// Compile instructions:   g++ Menu.cpp -o lab2
#include "Menu.h"
   
   // Function:      Parameterless constructor for Menu. 
   // Description:   This class uses the string DOLLARSIGN as a delimeter for message intake.
   //                Other strings and chars are strictly for formatting messages and tweets.
   //                User currentUser represents the present user on AubieBook. bool userExists 
   //                flag whether or not a user has ever been created. Display display handles
   //                most cout prompts.
   Menu::Menu()   
   {
      DOLLARSIGN = "$";
      SPACETILDESPACE = " ~ ";
      OPEN_BRACKET = '<';
      CLOSED_BRACKET = '>';
      NEWLINE = "\n";
      userExists = false;
      initializeValidUsers();
      initializeMessageList();
      initializeValidChoices();
   }

   // Function:      chrologoical_sort
   // Description:   Sorts Message objects based on their time stamp.
   bool chronological_sort(Message* lhs, Message* rhs)
   {
      return lhs->timeStamp > rhs->timeStamp;
   }

   // Function:      promptAddFriend
   // Input:         stringUser
   // Output:        Displays a message to user asking them to type
   // Description:   Prompts user to end the name of the friend they wish to add to their                
   //                list of friends. Checks if User is valid. If user isn't valid, will 
   //                ask user to try again. Otherwise, will add to currentUsers friends.
   //                Also, adds current user to friends friendlist.
   void Menu::promptAddFriend() 
   {
      initializeValidUsers();
      currentUser->printFriends();
      string stringUser;
      cout << "\t\nPlease enter user name: ";
      cin >> stringUser;
      // If user tries to add itself as a friend
      if(currentUser->haveSameName(stringUser))
      {
        cout << "\t\nSadly, you can't add yourself as your own friend. Get a life." << endl;
        return;
      }
      // Check if user is valid
      int i = isUserValid(stringUser);
      if( i == -1)
      {
         cout << "\t\nNot a valid user. Please try again." << endl;
         return;
      }
      if( !currentUser->isFriendsWith(stringUser) )
      { // If valid user and not a friend of current user
        currentUser->addFriend( (*(validUsers.at(i))).toString() );
        // Add current user to stringUser's friend list
        validUsers.at(i)->addFriend(currentUser->toString());
      cout<<"\n";
      cout<<"\t======================================================\n";
      cout<<"\t                   Added "<<stringUser<<" to Friends List           \n";
      cout<<"\t======================================================\n";
      cout<<"\n";
      }
      else
      {
         cout<< "\t\nYou are already friends with "<<stringUser<<endl;
      }
   }   

   // Function:      createUser
   // Input:         string newUser
   // Description:   Takes a string and creates a new user object. This object is then added
   //                to a vector of valid users. A bool flag is also changed to true to tell
   //                the program that at least one user exists. currentUser is set to this new
   //                User object. VALID_USERS_FILENAME is given another string name of new User object.
   void Menu::createUser(string newUser)  {
      userExists = true;
      int checkUser = isUserValid(newUser);
      ofstream outStream;
      // If no user's exist or user hasn't been created
      // append to the VALID_USERS_FILENAME file
      outStream.open(VALID_USERS_FILENAME, ios::app);
      outStream << newUser << endl;
      outStream.close();
      // adds the user to the valid user vector
      User* new_user = new User(newUser);
      validUsers.push_back(new_user);
      currentUser = new_user;
      cout << newUser << " has been added!" << endl;
   }

   // Function:      promptLogin
   // Input:         stringUser
   // Output:        Displays a message to user asking them to type their name
   // Description:   Prompts user to end their name. Checks if this name is amoung
   //                valid users. If User already exists, logs on to this User. Otherwise,
   //                it creates a new user and pushes this to valid users.
   void Menu::promptLogin()  {
      printValidUsers();
      string stringUser;
      cout << "Enter name: ";
      cin >> stringUser;
      int i = isUserValid(stringUser);
      if(i < 0) 
      { // If no users have been created = user is invalid
         cout << "New user.." << endl;
         createUser(stringUser);
         return;
      } 
      else if(i >= 0)  
      { // If user exists
         cout << "Returning user.." << endl;
         currentUser = validUsers.at(i);
         userExists = true;
      }  
   }

   // Function:      isUserValid
   // Input:         User object
   // Output:        Returns int. -2 if no users have been created. -1 if user is not valid. Otherwise,
   //                will return the index in validUsers in which this user is found.
   // Description:   Iterates through a list of valid users and compares each object's toString()
   //                to the User object argument. 
   int Menu::isUserValid(string possibleUser) {
      if(validUsers.size() == 0) { // If no User's exist
        return -2;
      }
      vector<User*>::iterator bit = validUsers.begin();
      int i = 0;
      while(bit != validUsers.end())
      {

         if((*bit)->toString() == possibleUser)  {
            return i; // User exists, i is the index in which it is found
          }
         bit++;
         i++;
      }
      return -1; // User hasn't been created
   }

   // Function:      promptPostMessage
   // Input:         User types the message they wish to post. Their input is ended with a
   //                separate line containing only a '$' character.
   // Output:        Prompts user to enter a message
   // Description:   This function formats the message buffer. All new messages will be placed
   //                at the front of the buffer with the name of the current user enclosed
   //                in brackets. Each message is delimited with a '$' character and separated
   //                with a new line. Messages are stored as an object Message and pushed to messageList.
   void Menu::promptPostMessage() 
   {
      // Take in post and store it to line
      string line = "";
      string in = "";
      cout << "\tEnter message: ";
      do
      {
         in = "";
         getline(cin, in);
         if(in == DOLLARSIGN)
         {
            // End when input line has only "$"
            break;
         } // Add each line of input from in to line
         line += in + "\\" + "n";
      }
      while (1);
      line.erase(0, 2);
      // cout<< "\n LINE: " << line << "\nsize: " << line.length();
      // Create a Message from this information and store in messageList
      Message *tempPost = new Message;
      tempPost->type = POST;
      tempPost->timeStamp = time(0);
      tempPost->poster = currentUser->name;
      tempPost->message = line;
      // Add this post to front of messageList
      messageList.push_front(tempPost);
      // Re-writes all the posts to the users file
      putPosts();
      cout << "\n";
      cout << "\t======================================================\n";
      cout << "\t                   New   post   added                 \n";
      cout << "\t======================================================\n";
      cout << "\n";
   }

   // Function:      promptTweet
   // Input:         User types the message they wish to tweet. Their input is ended with a
   //                separate line containing only a '$' character.
   // Output:        Prompts user to enter a message
   // Description:   This function formats the tweet. All new tweet will be placed
   //                at the front of the buffer with the name of the current user enclosed
   //                in brackets. Each message is delimited with a '$' character and separated
   //                with a new line.
   void Menu::promptTweet()
   {
      // Take in post and store it to line
      string line = "";
      string in = "";
      cout << "\tEnter tweet: ";
      do
      {
         in = "";
         getline(cin, in);
         if(in == DOLLARSIGN)
         {
            // End when input line has only "$"
            break;  // and quit taking in messages
         }    
         line += in + "\\" + "n";   // Add each line of input from in to line
      }
      while (1);
      line.erase(0, 2);
      // Create a Message from this information and store in messageList
      Message *tempPost = new Message;
      tempPost->type=TWEET;
      tempPost->timeStamp = time(0);
      tempPost->poster=currentUser->name;
      tempPost->message = line;
      // Clear messageList
      messageList.clear();
      // Reread in all tweets so messageList is up-to-date
      initializeTweets();
      // Add this post to front of messageList
      messageList.push_front(tempPost);
      // Re-writes all the posts to the users file
      putTweets();
      cout << "\n";
      cout << "\t======================================================\n";
      cout << "\t                   New tweet added                    \n";
      cout << "\t======================================================\n";
      cout << "\n";
   }
   
   // Function:      isValidChoice
   // Input:         char representing user's choice at menu display
   // Output:        Returns true if choice is a char matching anything in validChoices, false otherwise
   bool Menu::isValidChoice(char choice)   
   {
      for(int i = 0; i < 6; i++)   
      {
         if(choice == validChoices[i]) 
         {
            return true;
         }
      }
      return false;
   }
   
   // Function:      handleChoice
   // Input:         Takes chars 'f', 'p', 't' 'w' 'h' or 'q'. Any inccorect input will prompt user to type a valid char.
   // Output:        Various prompts for each choice will ask the user to type in either messages/tweets they wish to post or friends 
   //                they wish to become friends with. Can display organize posts or tweets with wall page or home page.
   // Description:   If choice is 'q', will return 1 which closes AubieBook.
   int Menu::handleChoice(char choice) 
   {
      int returnValue = 0;
      switch(choice) 
      {
         case 'f': // Add friend
            promptAddFriend();
            break;
         case 'p': // Post a message
            promptPostMessage();
            break;
         case 't': // Post a message
            promptTweet();
            break;
         case 'w': // Display Wal Page
            displayWall();
            break;
         case 'h': // Display Home Page
            displayHomePage();   
            break;
         case 'q': // Exit program
            displayExit();
            returnValue = 1;
      }
      return returnValue;
   }

   // Function:
   // Input:
   // Output:
   // Description:
   char Menu::promptMenuChoice()
   {
      cin.clear();
      displayMenu();
      char choice;
      while(1)
      {
         string optionChoice = "";
         cin >> optionChoice;
         if(optionChoice.length() > 1)
         {
            cout << "\nInvalid choice." << endl;
            cout << "\nEnter option: ";
            continue;
         }
         else
         {
            choice = optionChoice.at(0);
            if(isValidChoice(choice))   
            {
               return choice;
            }
            else
            {
               cout << "\nInvalid choice." << endl;
               cout << "\nEnter option: ";
               continue;
            }
         }
      }
   }
   
   // Function:      Displays welcome and takes in users char choice for menu.
   // Input:         Continually prompts user until a correct char is entered.
   // Output:        Displays a welcome: if a user exists will display a specific
   //                welcome for them. Otherwise, a generic welcome display. Then
   //                posts the textual menu display.
   // Description:   Displays generic welcome and prompts user to log on. displays welcome to current user. Takes in users int choice and 
   //                determines if it is valid. Continually prompts user for a valid char. Once a valid choice has been made, choice is handed 
   //                to handleChoice() function.
   int Menu::startMenu()  
   {
      //cin.ignore(1000,'\n');
      // Login
      int quitValue = 0;
      while(1)
      {
         if(!userExists)  
         {
            displayWelcome();
            promptLogin();
         }
         // User has logged on previously
         else if(userExists) 
         {
            updateWelcome();
            while(1)
            {
               char option = promptMenuChoice();
               quitValue = handleChoice(option);
               if( quitValue == 1)
               {
                  return 1;
               } 
            }
         }
      }
   } 

   // Function:      displayWelcome() & updateWelcome()
   // Output:        Displays a generic welcome message or a welcome for a specified user
   // Description:   If a user hasn't been created, will display a generic welcome message.
   //                Otherwise, function will generate welcome greeting for specific user.
   void Menu::displayWelcome()  
   {
      string welcome = "\t===========================================================\n";
      welcome +=       "\t|               Distributed System AubieBook!             |\n";
      welcome += "\t===========================================================\n\n";
      cout << welcome;
   }

   void Menu::updateWelcome()   
   {
      string welcome = "\t===========================================================\n";
      welcome +=       "\t      Welcome to Distributed System Aubiebook, " + currentUser->toString() 
      + "!\n";
      welcome += "\t===========================================================\n\n";
      cout << welcome;
   }

   // Function:      displayExit
   // Description:   Displays exiting message.
   void Menu::displayExit()   
   {
      string quitPage = "\t===========================================================\n";
      quitPage +=       "\t|       Thank you for using the Aubiebook System          |\n";
      quitPage += "\t===========================================================\n\n";
      cout << quitPage;
   } 

   // Function:      displayMenu
   // Description:   Displays menu.
   void Menu::displayMenu()   
   {
      cout << "Add Friend (f), Post (p), Tweet (t), Wall (w), Home (h), Quit (q)" << endl;
      cout << "Enter option: ";
   }

   // Function:      promptMoreMessages
   // Input:         "yes" or "no" depending on whether user wishes to see more messages
   // Output:        Prompts user if they wish to see more messages, returns bool flag whether to continue
   //                displaying messages
   // Description:   Continually prompts user if they wish to see messages until they type
   //                either "yes" or "no."
   bool Menu::promptMoreMessages()
   {
      cout << "\t\tMore messages? (yes/no): ";
      string option = "";
      do 
      {
         cin >> option;
         if(option == "no")  
         {// If no end function call
            return false;
         }
         else if(option == "yes") 
         {// If yes break out of while loop then continue to print messages
            return true;
         }
         else
         { // Otherwise continually prompt until answer is correct
            cout << "\t\tPlease type either yes or no." << endl;
            cout << "\t\tMore messages? (yes/no): ";
            continue;
         }
      } while(1);
   }

   // Function:      putPost   
   // Description:   Iterates through every message and finds all posts by current user and writes them
   //                to its file. Each message is preceded by a time stamp enclosed by brackets followed by
   //                the message.
   void Menu::putPosts()
   {
      list<Message*>::iterator message_iter;
      ofstream fileOut;
      fileOut.open(currentUser->userFile.c_str());
      
      for( message_iter = messageList.begin(); message_iter != messageList.end(); message_iter++)
      {
         if( (*message_iter)->type == POST && currentUser->name == (*message_iter)->poster )
         {
            fileOut << "<" << (*message_iter)->timeStamp << ">" << (*message_iter)->message;
         }
         else
         {
            // cout << "\nrejecting post by: " <<(*message_iter)->poster;
         }
      }
      return;
   }

   // Function:      putTweets
   // Description:   Iterates through every message in messageList and finds all Tweets and writes them to
   //                file "tweet.txt" with time stamp enclosed by brackets followed by the poster enclosed by
   //                brackets followed by the message.
   void Menu::putTweets()
   {
      messageList.sort(chronological_sort);
      list<Message*>::iterator message_iter;
      ofstream fileOut;
      fileOut.open(TWEET_FILENAME);
      
      for( message_iter = messageList.begin(); message_iter != messageList.end(); message_iter++)
      {
         if( (*message_iter)->type == TWEET )
         {
            fileOut << "<" << (*message_iter)->timeStamp << "><" <<(*message_iter)->poster<< ">" <<(*message_iter)->message;
         }
      }
      return;
   }

   // Function:      formatPost
   // Input:         string sub, string someUser
   // Description:   This member takes a portion of the users message file and reformats it storing it 
   //                to messageList, a container for Message objects. Separates the time stamp from the message
   //                and uses this information to create a Message object. string someUser is used to define the post
   //                variable of the Message object to avoid Segmentation error if the current user has not been initialized.
   void Menu::formatPost(string sub, string someUser)  
   {
      string formatted_buffer = "";
      // Get time stamp
      int i = 0; // First '<'
      int j = i + 1; // Beginning of time stamp
      int endOfTime = sub.find_first_of(CLOSED_BRACKET, i); //
      int stampSize = endOfTime - j;
      endOfTime++;
      string stamp = sub.substr(j, stampSize); // string holding time stamp value
      int timeValue = atoi(sub.substr(j, stampSize).c_str()); // Convert to int
      // Get message
      int msg_size = sub.length() - endOfTime; // Find length of message
      string a_message = sub.substr(endOfTime, msg_size); // Create substring of message
      // add formatted message
      formatted_buffer += a_message; 
      // Create new Message with found parameters
      Message* newPost = new Message();
      newPost->type = POST;
      newPost->timeStamp = timeValue;
      newPost->poster = someUser;
      newPost->message = formatted_buffer;
      // Add new Message object to front of messageList
      messageList.push_front(newPost);
   }

   // Input:         string sub
   // Description:   This member takes a portion of the file "Tweet.txt" and reformats it. Separates the time stamp and name 
   //                from the message and uses this information to create a Message object. This object is stored in messageList.
   void Menu::formatTweet(string sub) 
   {
      string formatted_buffer = "";
      // cout << "Before call: " << sub << endl;
      // Get time stamp
      int i = 0; // First '<'
      int j = i + 1; // Beginning of time stamp
      int endOfTime = sub.find_first_of(CLOSED_BRACKET, i); // Find '>'
      int stampSize = endOfTime - j; // number of chars time
      endOfTime++;
      string stamp = sub.substr(j, stampSize); // string holding time stamp value
      int timeValue = atoi(sub.substr(j, stampSize).c_str()); // Convert to int
      // Get name
      int beginName = sub.find_first_of(OPEN_BRACKET, endOfTime);
      beginName++;
      int endName = sub.find_first_of(CLOSED_BRACKET, beginName);
      int nameLength = endName - beginName;
      string name = sub.substr(beginName, nameLength);
      // Get message
      endName++;
      int msg_size = sub.length() - endName; // Find length of message
      string a_message = sub.substr(endName, msg_size); // Create substring of message
      // add to buffer
      formatted_buffer += a_message; // add formatted message
   
      // Create new Message with found parameters
      Message* newPost = new Message();
      newPost->type = TWEET;
      newPost->timeStamp = timeValue;
      newPost->poster = name;
      newPost->message = formatted_buffer;
      // Add new Message object to front of messageList
      messageList.push_front(newPost);
   }

   // Function:      initializeValidChoices
   // Description:   Adds valid char choices to vector validChoices. These char's are the only valid option choices for the menu.
   void Menu::initializeValidChoices() 
   {
      validChoices.push_back('f');
      validChoices.push_back('p');
      validChoices.push_back('t');
      validChoices.push_back('w');
      validChoices.push_back('h');
      validChoices.push_back('q');
   }

   // Function:      initializeValidUsers       
   // Descriptions:  Reads in file VALID_USERS_FILENAME which contains a list of valid users. Creates users from each line and pushes
   //                each to vector storing valid users for quicker access as opposed to rereading the text file each time
   //                a user is checked.
   void Menu::initializeValidUsers()   
   {
      validUsers.clear();
      string line;
      User* tempUser;
      ifstream fileIn;
      fileIn.open(VALID_USERS_FILENAME); // Text file holding list of valid users
      if( fileIn.is_open() == false)
      {
         // If user.txt cannot be found make a new one
         ofstream fileOut;
         fileOut.open(VALID_USERS_FILENAME);
         fileOut.close();
         return;
      }
      while( fileIn.good() )
      {
         getline(fileIn,line,'\n');
         if(line.empty()) // If a blank line is encountered, don't create a blank user 
         {
            break;
         }
         tempUser = new User(line);
         validUsers.push_back(tempUser);
      }
      fileIn.close();
   }

   // Function:      initializeTweets
   // Description:   Iterates through file "tweet.txt" and creates a Message object from each tweet and pushing it to the front of
   //                messageList
   void Menu::initializeTweets()   {
      string line = "";
      ifstream fileIn;
      fileIn.open(TWEET_FILENAME);
      if( fileIn.is_open() == false)
      {
         //throw error or something or just make another one
         ofstream fileOut;
         fileOut.open(TWEET_FILENAME);
         fileOut.close();
         //cout << TWEET_FILENAME << " not found you dork.";
      }
      string tweetBuffer = "";
      while( fileIn.good() )
      {
         //this is assuming that the first character is not a newline
         getline(fileIn, line);
         tweetBuffer += line + "\n";
      }
      // Get rid of any stray newline characters
      while( tweetBuffer.length() > 0 && tweetBuffer.at(tweetBuffer.length()-1) == '\n' )
      {
         tweetBuffer.erase(tweetBuffer.length()-1,1);
      }
      if( tweetBuffer.length() > 0 )
      {
         int current_pos = 0;
         int initialBracket;
         int secondBracket;
         int nextInitialBracket;
         while( 1 )
         {
            initialBracket = current_pos;
            secondBracket  = tweetBuffer.find_first_of(OPEN_BRACKET,initialBracket+1);
            nextInitialBracket = tweetBuffer.find_first_of(OPEN_BRACKET,secondBracket+1);

            //cout<<initialBracket<<" "<<secondBracket<<" "<<nextInitialBracket<<endl;
            // If this is the last tweet
            if( nextInitialBracket == -1 )
            {
               // cout<<tweetBuffer.substr(initialBracket,tweetBuffer.length()-initialBracket);
               formatTweet(tweetBuffer.substr(initialBracket,tweetBuffer.length()-initialBracket));
               break;
            }
            // If there is more than 1 tweet left
            else
            {
               // cout<<tweetBuffer.substr(initialBracket,nextInitialBracket-initialBracket); 
               formatTweet(tweetBuffer.substr(initialBracket,nextInitialBracket-initialBracket));
            }
            current_pos = nextInitialBracket;
         }
      }
   }

   // Function:      initializePosts
   // Description:   Iterates through current users file creating Message objects from each post and pushing it to the front of 
   //                messageList
   void Menu::initializePosts()  {
      vector<User*>::iterator user_iter;
      ifstream fileIn;
      string line = "";
      //adds in all the valid users posts from all of their respective files
      for ( user_iter=validUsers.begin() ; user_iter < validUsers.end(); user_iter++ )
      {
         fileIn.open( ((*user_iter)->userFile).c_str() );
         if( fileIn.is_open() == false)
         {
            //throw error or something
            //file should have been created
            ofstream fileOut;
            fileOut.open( ((*user_iter)->userFile).c_str() );
            fileOut.close();
            continue;
         }
         while( !fileIn.eof() )
         {
            getline(fileIn, line, '<');
            if( line.empty() == true)
            {
               continue;
            }
            line = "<" + line;
            string tempName = (*user_iter)->name;
            formatPost(line, tempName);
         }
         fileIn.close();
      }
   }

   // Function:      initializeMessageList
   // Description:   Iterates through each valid user and formats their posts and tweets. All messages are then
   //                sorted in reverse chronological order.
   void Menu::initializeMessageList() 
   {
      messageList.clear();
      // adds all the posts from users file to messageList
      initializePosts();
      // adds in all the tweets from the tweets.txt file to messageList
      initializeTweets();
   }

   // Function:      displayHomePage
   // Description:   Iterates through current user's posts and tweets as well as his friends posts and tweets and prints
   //                them out in reverse chronological order. If there are more than 3 messages total, will print the first
   //                3 messages and then prompt the user if they wish to see more. If there are 3 or less, will not prompt user
   //                to see more.
   void Menu::displayHomePage()  
   {
      bool hasBeenPrompted = false;
      // Get up to date list of valid users
      initializeValidUsers();
      // Make sure User's friend list is up to date
      currentUser->initializeFriendsVector();
      // Reread in messages so they are up to date
      initializeMessageList();
      // Sort them again
      messageList.sort(chronological_sort);
      // Get the number of valid messages
      int numberOfPostsToDisplay = numberOfUserAndFriendsPosts();
      int numberOfPostsDisplayed = 0;
      list<Message*>::iterator message_iter;

      cout << "\t======================================================\n";
      cout << "\t                   " + currentUser->toString(); 
      cout << "'s Home Page";
      cout << "              \n";
      cout << "\t======================================================\n";
      for( message_iter = messageList.begin(); message_iter != messageList.end(); message_iter++)
      {
         if( numberOfPostsDisplayed == 3 && numberOfPostsToDisplay > 3 && hasBeenPrompted == false) // Three messages have been printed
         { // Prompt user if they wish to see more
            hasBeenPrompted = true;
            if( promptMoreMessages() != true )
            {
               break;
            }
         }
         // Add all of current user and his friends posts, plus all tweets
         if( currentUser->name == (*message_iter)->poster || currentUser->isFriendsWith((*message_iter)->poster)
            || (*message_iter)->type == TWEET)
         {
            //display message either tweet or message of current user or friends
            string output = splitLines((*message_iter)->message);
            cout<< (*message_iter)->poster << " ~ " << output << endl;
            numberOfPostsDisplayed++;
         }
      }
      cout << "\t======================================================\n";
      cout << "\t               End of " + currentUser->toString(); 
      cout << "'s Home Page";
      cout << "              \n";
      cout << "\t======================================================\n";
   }

   // Function:      displayWallPage
   // Description:   Iterates through current user's posts and tweets prints them out in reverse chronological order. If there 
   //                are more than 3 messages total, will print the first 3 messages and then prompt the user if they wish to 
   //                see more. If there are 3 or less, will not prompt user to see more.
   void Menu::displayWall()   
   {
      bool hasBeenPrompted = false;
      // Reread all messages
      initializeMessageList();
      // Sort all messages
      messageList.sort(chronological_sort);
      // Get the number of valid messages
      int numberOfPostsToDisplay = numberOfUserPosts();
      int numberOfPostsDisplayed = 0;
      list<Message*>::iterator message_iter;

      cout<<"\t======================================================\n";
      cout<<"\t                   " + currentUser->toString(); 
      cout<<"'s Wall Page";
      cout<<"              \n";
      cout<<"\t======================================================\n";
      
      for( message_iter = messageList.begin(); message_iter != messageList.end(); message_iter++)
      {
         if( numberOfPostsDisplayed == 3 && numberOfPostsToDisplay > 3 && hasBeenPrompted == false) // Three messages have been printed
         { // Prompt user if they wish to see more
            hasBeenPrompted = true;
            if( promptMoreMessages() != true )
            {
               break;
            }
         }
         if( currentUser->name == (*message_iter)->poster )
         {
            //display message
            string output = splitLines((*message_iter)->message);
            cout<<output<<endl;
            numberOfPostsDisplayed++;
         }
      }
      cout<<"\t======================================================\n";
      cout<<"\t               End of " + currentUser->toString(); 
      cout<<"'s Wall Page";
      cout<<"              \n";
      cout<<"\t======================================================\n";
   }
   
   // Function:      splitLines
   // Input:         string sub
   // Output:        string newSub
   // Description:   Takes in a string, finds each occurance of "\n" and replaces it with a new line character.
   string Menu::splitLines(string sub)
   {
      string newSub = sub;
      for(int i = 0; i < newSub.length(); i++)
      {
         if(newSub.at(i) == '\\')
         {
            newSub.erase(i,2);
            newSub.insert(i, "\n");
         }
      }
      return newSub;
   }

   // Function:      messageListDump
   // Description:   Iterates through every message and prints it out indicating Tweets or Post, along with the poster, the time
   //                it was posted and the message. Strictly used for testing.
   void Menu::messageListDump()
   {
      list<Message*>::iterator message_iter;

      for( message_iter = messageList.begin(); message_iter != messageList.end(); message_iter++)
      {
         switch((*message_iter)->type)
         {
            case TWEET: cout << "\nTWEET" << endl;
                        break;
            case POST:  cout << "\nPOST" << endl;
         }
         cout << (*message_iter)->poster << endl;
         cout << (*message_iter)->timeStamp << endl;
         cout << (*message_iter)->message << endl;
      }   
   }

   // Function:      printFriends
   // Output:        prints current users list of friends
   // Description:   Iterates through list of friends of current user and prints each one.
   void Menu::printValidUsers()  
   {
      vector<User*>::iterator bit = validUsers.begin();
      int i = 0;
      cout << "Printing valid users.." << endl;
      while(bit != validUsers.end())
      { 
         cout << validUsers.at(i)->toString() << endl;
         bit++;
         i++;
      }
   }
   
   // Function:      numberOfUserPosts & number UserAndFriendsPosts
   // Description:   Iterates through either just the User's posts and tweets or the User and its friends posts and tweets
   //                and counts how many.
   int Menu::numberOfUserPosts()
   {
      int numberOfMessages = 0;
      list<Message*>::iterator message_iter;

      for( message_iter = messageList.begin(); message_iter != messageList.end(); message_iter++)
      {
         if( currentUser->name == (*message_iter)->poster )
         {
            numberOfMessages++;
         }
      }
      return numberOfMessages;
   }

   int Menu::numberOfUserAndFriendsPosts()
   {
      int numberOfMessages = 0;
      list<Message*>::iterator message_iter;

      for( message_iter = messageList.begin(); message_iter != messageList.end(); message_iter++)
      {  // All of the current users messages, his friends messages and all tweets
         if( currentUser->name == (*message_iter)->poster || currentUser->isFriendsWith((*message_iter)->poster)
            || (*message_iter)->type == TWEET)
         {
            numberOfMessages++;
         }
      }
      return numberOfMessages;
   }