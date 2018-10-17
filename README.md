Game Description:
    The game implemented is a form of the well known game "Simon Says". One player sends a sequence of directions to the other player, where that sequence quickly plays across the receivers LED matrix.
    The receiver must then replicate the message. If they are correct, they receive a point. Only the receiver can gain a point each round.
    Once the round is over, both players have their roles swapped. This carries on until either player gains three points. At that point a winner is announced and the game concludes.


Instructions for game set up:
    1)      Make sure both UCFKs are plugged into a computer, or computers with the source code readily available, and all required AVR tools installed.\
    2)      Open a terminal window in the source directory.
    3)      Make the program and download it into both UCFKs.
    
    --------Once both UCFKs are running, the first player to press down their navswitch, causes a handshake between UCFKs to commence, players are determined and the game starts-------

Message creation step:
    1) An S will display across the screen of the message sender.
    2) The sender inputs a sequence of directions via the nav-switch of at most 6 characters.
        a) If more than 6 characters is attempted, an X will display on screen.
    3) The sender then pressed the nav button to send the message.
    4) The sender will be given a waiting prompt until the receiver has attempted to copy the sequence made by the sender.
 
Follow the leader
    1) A R will display on the screen of the receiver.
    2) The receiver will be given a waiting prompt until the sender's message has been received.
    3) When the message is received arrows will quickly slide across the screen which the receiver must try to recreate using the nav-switch directional buttons.
        a) There is no backspace - what you enter is there to stay!
    4) The receiver pressed the nav-switch down when they wish to confirm their message.
    5) The receiver will then be notified if their answer was correct or wrong.

End of round stage
    1) Both players will be given a symbol to show if they lost or won the round ('Y' for win 'X' for loss).
    2) The player rolls are swapped and a new round starts.

End of game
    1) Once either player reaches 3 points the match is over.
    2) Text will be displayed telling the user if they won or loss.
    3) The game ends.

    --------For any time if you want to clear the game, press the button S2.--------
