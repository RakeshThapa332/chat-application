# Chat Application

A simple console-based chat application written in C++ that allows users to register, log in, manage their friend list, and send/receive messages. The system also supports viewing message history and saving chats to a file.

## Features

- **User Registration**: Allows a user to register with a username and password.
- **Login**: Enables users to log in using their registered username and password.
- **Friend Management**: Add or remove friends from your friend list.
- **Chat System**: Send and receive messages with your friends.
- **Message History**: View previous messages sent/received with friends.
- **Save Chat to File**: Chat history is saved in a file for later retrieval.

## File Operations

The system uses a text file (`chat_history.txt`) to store the chat history, which is updated each time a new message is sent. The file is used for both saving and loading chat messages.

## Structure

The system uses a class `frnd` to hold information about each user and their chats. This class contains:

- A list of friends (`flist`) where each user can add/remove friends.
- A chat history array that stores messages exchanged with each friend.
- File handling functions for saving and loading messages from a file.

## Usage

1. ***Clone the Repository***:

    ```bash
     git clone https://github.com/your-username/chat-application.git
    ```

2. **Compile the Code**:

    Use the following command to compile the C program:

    ```bash
    g++ main.cpp -o chat_app

    ```

3. **Run the Program**:

    After compiling, run the program:

    ```bash
    ./chat_app

    ```

4. Available Options:
   
   a) Login: Log in using a registered username and password.

   b) Register: Create a new user by providing a username and password.

   c) Add Friend: Add a friend to your friend list by entering their name.

   d) Remove Friend: Remove a friend from your friend list.

   e) Send Message: Choose a friend from your list and send them a message.

   f) View Inbox: View the chat history with your friends.

   g) Logout: Logout of your current session.

   Follow the prompts to enter student details and interact with the system.


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
