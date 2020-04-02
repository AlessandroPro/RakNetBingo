README

Alessandro Profenna
PROG57370 - Midterm
RakNet Bingo

NOTE: In Visual Studio, your configuration must be set to Debug and your platform to Win32 for the project settings to work. 
Otherwise there will be compile issues with finding RakNet files.

All requirements have been fulfilled.
A gameplay video playing with 3 clients has been included in this submission as well.

To run it:

1) Start the server from visual studio or running the executable from the command line with "server" as the only argument.
2) Open a few command prompts to run the clients. Do the same as above but with "client" as the only argument for each.
3) Click 's' on the server. No input is required on the clients.

___________________________________________________
Flow:
___________________________________________________

When the server starts, you can either press ESC to close it or 's' to start the game.
When the game starts, the server caches all of the guids of clients currently connected, and uses them as the players.
This means that a client joining in the middle of the game will have to wait until the next game to play.
At this point, the server generates a unique game card with 9 numbers for each client, and sends the numbers through a custom message.
Upon receiving their message, each client parses the number message and fills their bingo card with their numbers.
Then the server will draw a random number between 10 and 99 every 100ms, and send that number to each client through a custom
message. Upon receipt, each client will check if it's on their card and mark it with an 'O' if it is. A client will print its board whenever
it is marked by a matching number.
If a client's card is completely marked, it will send a custom BINGO! message to the server, at which point the server will send a custom
message to all clients saying that there is a winner and that the game has ended.

___________________________________________________
Architecture:
___________________________________________________

The main function creates a BingoGame instance, which creates a derived BingoPlayer that is either a BingoClient
or BingoServer, depending on the command line argument. The RakNetController is also instantiated, which the BingoPlayer has
a reference to. Each BingoPlayer has an update function that is called repeatedly in the BingoGame's game loop.
The update function is where the client or server processes newly received messages and sends any messages it needs to send.
Default messages are processed in the RakNetController, while each custom message (those specific to the Bingo Game) are 
processed in the player's processMessage function.
The BingoClient has a bingoBoard, which can be filled, printed, and marked.

There is no input on the client side, other than pressing ESC to close the application.
They will automatically conenct when started.

___________________________________________________
Game Number Draws and Card (Board) Generation:
___________________________________________________

Here I'll explain the implementation of how the dealer draws numbers, and how the cards are generated for each client:

To ensure the dealer doesn't repeat numbers when it draws every 100ms, it stores numbers 10 to 99 in a bingoNum array, 
where the values at each index are randomly swapped around before each game. It's like shuffling a deck. 
It draws numbers from beginning to end of this array, and since they are in a random order, the draws appear random.

To ensure that every client gets a unique bingo card, the cards are created as such:

1) The bingoNum array with numbers 10 through 99 is shuffled, so they're in a random order.
2) The first x indices of this array are then reserved, with x being the number of clients in the game.
3) For each client their board is made up of the following 9 numbers:
    - 1 unique number from the subset of indices 0 to x in the array
    - the first 8 numbers after x in the array (after which the indices after x are reshuffled)
  The whole point of having a subset of numbers reserved at the beginning of the array is so that we guarantee
  each game card has at least 1 number that no other card has. This prevents ties.
  This also guarantees there are no repeated numbers on each card.