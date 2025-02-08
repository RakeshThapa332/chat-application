#include<iostream>
#include<string.h>
#include<fstream>  // Include for file handling
using namespace std;

// Constants for limits
#define MAX_FRIENDS 100
#define MAX_MESSAGES 50
#define MAX_USERS 100

// Function declarations
void page1();
void page2(string);

// Global arrays to store user credentials
string usernames[MAX_USERS];
string passwords[MAX_USERS];
int userCount = 0;  // Track the number of registered users

// Class representing a friend with functionalities for managing friends and chats
class frnd
{
    string flist[MAX_FRIENDS];  // Array to store friends
    int flistCount = 0;  // Counter for the number of friends

    struct chat
    {
        int message_id;              // Unique ID for each message
        string sender, receiver;     // Sender and receiver of the message
        char mess[MAX_MESSAGES][100];// Array to store up to 50 messages of 100 characters each
        int num_of_message = 0;      // Counter for the number of messages
    };

public:
    chat sms[MAX_FRIENDS];  // Array to store chats, one for each friend
    void addfrnd(string);   // Function to add a friend
    void unfrnd(string);    // Function to remove a friend
    void dispfrnd(string);  // Function to display the friend list
    void chat_on(string, string, char*);  // Function to send a message
    void inbox(string);     // Function to display the inbox
    void saveChatToFile(string, string, char*);  // Function to save chat to a file
    void loadChatFromFile(string, string);       // Function to load chat from a file
    void saveFriendList(string);  // Function to save friend list to a file
    void loadFriendList(string);  // Function to load friend list from a file
};

// Function to save chat to a user-specific file
void frnd::saveChatToFile(string sender, string receiver, char *message)
{
    // Construct the filename using the sender and receiver
    string filename = sender + "_" + receiver + "_chat.txt";
    ofstream outFile(filename, ios::app);  // Open the file in append mode
    if (outFile.is_open())
    {
        // Write the sender, receiver, and message to the file
        outFile << sender << " -> " << receiver << ": " << message << endl;
        outFile.close();  // Close the file after writing
    }
    else
    {
        cout << "\nUnable to open file for writing.\n";
    }
}

// Function to load chat from a user-specific file
void frnd::loadChatFromFile(string user1, string user2)
{
    string filename = user1 + "_" + user2 + "_chat.txt";  // Construct the filename
    ifstream inFile(filename);  // Open the file for reading
    string line;
    if (inFile.is_open())
    {
        // Read each line and display if it matches the chat between user1 and user2
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();  // Close the file after reading
    }
    else
    {
        cout << "\nUnable to open file for reading.\n";
    }
}

// Function to handle the chat and save the message to the file
void frnd::chat_on(string uname, string reciepient, char *message)
{
    int flag = 0;
    int friendIndex = -1;

    // Find the friend index
    for (int i = 0; i < flistCount; i++)
    {
        if (flist[i] == reciepient)
        {
            friendIndex = i;
            flag = 1;
            break;
        }
    }

    if (friendIndex == -1)
    {
        cout << "\nSorry!! No user found\a\a\n";
        page2(uname);
        return;
    }

    // Check if there is space for a new message
    if (sms[friendIndex].num_of_message < MAX_MESSAGES)
    {
        sms[friendIndex].sender = uname;
        sms[friendIndex].receiver = reciepient;
        strcpy(sms[friendIndex].mess[sms[friendIndex].num_of_message], message);
        sms[friendIndex].num_of_message++;
        saveChatToFile(uname, reciepient, message);  // Save the message to file
    }
    else
    {
        cout << "\nMessage limit reached!!\n";
    }
}

// Function to display the inbox by loading chat history from file
void frnd::inbox(string uname)
{
    for (int i = 0; i < flistCount; i++)
    {
        loadChatFromFile(uname, flist[i]);  // Load chat history from file
    }
}

// Function to add a friend to the user's friend list
void frnd::addfrnd(string uname)
{
    if (flistCount < MAX_FRIENDS)
    {
        cout << "\nEnter friend's name: ";
        cin >> flist[flistCount];
        flistCount++;
        saveFriendList(uname);  // Save the updated friend list to a file
        cout << "\nFriend added!\n";
    }
    else
    {
        cout << "\nFriend list is full!\n";
    }
}

// Function to remove a friend from the user's friend list
void frnd::unfrnd(string uname)
{
    string fname;
    cout << "\nEnter friend's name to remove: ";
    cin >> fname;
    for (int i = 0; i < flistCount; i++)
    {
        if (flist[i] == fname)
        {
            // Shift friends down in the array to fill the gap
            for (int j = i; j < flistCount - 1; j++)
            {
                flist[j] = flist[j + 1];
            }
            flistCount--;
            saveFriendList(uname);  // Save the updated friend list to a file
            cout << "\nFriend removed!\n";
            return;
        }
    }
    cout << "\nFriend not found!\n";
}

// Function to display the user's friend list
void frnd::dispfrnd(string uname)
{
    cout << "\nFriend list:\n";
    for (int i = 0; i < flistCount; i++)
    {
        cout << flist[i] << endl;  // Display each friend's name
    }
}

// Function to save the friend list to a file
void frnd::saveFriendList(string uname)
{
    ofstream outFile(uname + "_friends.txt");
    if (outFile.is_open())
    {
        for (int i = 0; i < flistCount; i++)
        {
            outFile << flist[i] << endl;  // Save each friend's name to the file
        }
        outFile.close();
    }
    else
    {
        cout << "\nUnable to save friend list.\n";
    }
}

// Function to load the friend list from a file
void frnd::loadFriendList(string uname)
{
    ifstream inFile(uname + "_friends.txt");
    if (inFile.is_open())
    {
        string friendName;
        while (getline(inFile, friendName))
        {
            flist[flistCount++] = friendName;  // Load each friend's name into the list
        }
        inFile.close();
    }
    else
    {
        cout << "\nNo previous friend list found.\n";
    }
}

// Function to display the first page (login, register, exit)
void page1()
{
    cout << "\nWelcome to the Chat Application!\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Exit\n";
}

// Function to display the user's options after logging in
void page2(string uname)
{
    frnd f;
    f.loadFriendList(uname);  // Load the friend list when the user logs in
    int choice;
    do
    {
        cout << "\nWelcome " << uname << "!\n";
        cout << "1. Add Friend\n";
        cout << "2. Remove Friend\n";
        cout << "3. Display Friends\n";
        cout << "4. Chat\n";
        cout << "5. View Inbox\n";
        cout << "6. Logout\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: f.addfrnd(uname); break;   // Add a friend
            case 2: f.unfrnd(uname); break;    // Remove a friend
            case 3: f.dispfrnd(uname); break;  // Display friend list
            case 4:
            {
                string reciepient;
                char message[100];
                cout << "\nEnter friend's name: ";
                cin >> reciepient;
                cout << "\nEnter your message: ";
                cin.ignore();
                cin.getline(message, 100);
                f.chat_on(uname, reciepient, message);  // Send a message
                break;
            }
            case 5: f.inbox(uname); break;  // View inbox
            case 6: cout << "\nLogging out...\n"; break;  // Logout
            default: cout << "\nInvalid choice!\n";
        }
    } while(choice != 6);
}

// Function to register a new user
void registerUser(string uname, string pass)
{
    if (userCount < MAX_USERS)
    {
        usernames[userCount] = uname;
        passwords[userCount] = pass;
        userCount++;
        cout << "\nUser registered successfully!\n";
    }
    else
    {
        cout << "\nUser registration limit reached!\n";
    }
}

// Function to check if a user exists and password matches
bool loginUser(string uname, string pass)
{
    for (int i = 0; i < userCount; i++)
    {
        if (usernames[i] == uname && passwords[i] == pass)
        {
            return true;
        }
    }
    return false;
}

// Main function to handle user registration, login, and exit
int main()
{
    string uname, pass;
    int choice;

    do
    {
        page1();
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                cout << "\nEnter username: ";
                cin >> uname;
                cout << "\nEnter password: ";
                cin >> pass;

                if (loginUser(uname, pass))
                {
                    page2(uname);  // Go to user options page
                }
                else
                {
                    cout << "\nInvalid credentials!\n";
                }
                break;
            }
            case 2:
            {
                cout << "\nEnter username: ";
                cin >> uname;
                cout << "\nEnter password: ";
                cin >> pass;

                registerUser(uname, pass);  // Register a new user
                break;
            }
            case 3: cout << "\nExiting...\n"; break;  // Exit the application
            default: cout << "\nInvalid choice!\n";
        }
    } while(choice != 3);

    return 0;
}
