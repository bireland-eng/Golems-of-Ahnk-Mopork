// GolemsOfAnkhMorporkICS4UUnit3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <random>
#define NOMINMAX //stops windows.h from breaking min and max
#include <Windows.h>

using namespace std;


/*
Name: Ben Ireland
Date: Feb 14th, 2026 to 
Purpose: To make a game very similar to mastermind. See overview in "ASSIGNMENT Unit 3 - Golems" for the plot.

Version: 1.0

Notes: The processes used for reading and writting to the file are based off the w3 school tutorial on how to read and write from a file in c++
Found here: https://www.w3schools.com/CPP/cpp_files.asp

The randum number generator is based off information from Microsoft learn about the random library
Found here: https://learn.microsoft.com/en-us/cpp/standard-library/random?view=msvc-170

The input functions are copyed from my InPr project, but the yOrN function was remade for this project to use the stringIn function instead


To enable ansi colour in console, code was taken from this windows article on how to enable ansi colour in console
Found here: https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences

To make a string uppercase i used this geeks for geeks article
Found here: https://www.geeksforgeeks.org/cpp/toupper-in-cpp/

Ascii art was made with https://www.asciiart.eu/image-to-ascii

The meansing of different ansi colour codes was found here https://gist.github.com/JBlond/2fea43a3049b38287e5e9cefc87b2124

A lot of other commands were taken from the cpp refrence sheet. The time.h part should be redone as running any command other than someVarible = time(0) gives a compiler error.
It complains that the implementation is not secure, and that the new secure version should be used instead.

*/









/*
Pre: Windows console
Post: A windows console that supports ansi colour codes
*/
void enableColour() {
    // 1. Get a handle to the console output
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        
    }

    // 2. Get the current console mode
    DWORD dwMode = 0;
    if (!GetConsoleMode(hConsole, &dwMode)) {
        
    }

    // 3. Enable ENABLE_VIRTUAL_TERMINAL_PROCESSING mode
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hConsole, dwMode)) {
        
    }

}


/*
@param question is the question that the user must answer
Pre: Valid place for the function to return to
Post: A string is returned
*/
string stringIn(string question) {
    //ask the user thequestion
    std::cout << question;

    string garbage;

    while (!(getline(cin, garbage))) {//contiues until cin can be put into garbage. cin >> garbage evaluates to false if it cannot be performed
        //error message
        //not sure how the user can type in something to cin that is not a string, but if they somehow do, I have and error message to catch them.
        std::cout << "\nInvalid input. Not a string. I have no clue how you manged to enter something that is not a string, so congratualtions, you broke this more than I ever could have expected!\nYou win!\n";

        //clear the error in cin
        cin.clear();

        //remove all charecters in cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        //ask the question again
        std::cout << question;

    }

    //returns the garbage
    return garbage;


}



/*
@param question is the question that the user must answer
@param minValue is the minimum acceptable length of string that the user can enter (inclusive)
@param maxValue is the maximum acceptable length of string that the user can enter (inclusive)
Pre: Valid place for the function to return to
Post: An string in the range(inclusive) is returned
*/
string stringMM(string question, size_t minValue, size_t maxValue) {


    string garbage = stringIn(question);//uses my previously made stringIn function, then checks if it meets the value restrictions

    while (garbage.length() < minValue || garbage.length() > maxValue) {//continues while garbage is smaller then the minumum or greater then the maximum
        //error message
        std::cout << "\nInvalid range. Data is not within valid length.\n";


        //clear cin (there wont be an error, but it can't hurt to clear cin)
        cin.clear();

        //remove all charecters in cin
        //cin.ignore(numeric_limits<streamsize>::max(), '\n'); not needed as getline already removes what it extracts from cin


        //gives the user another chance to enter data in the range
        garbage = stringIn(question);


    }

    //returns the garbage
    return garbage;

}



/*

@param question is the question that the user must answer
Pre: Valid place for the function to return to
Post: A true is returned for a yes and a false is returned for a no
*/
bool yOrN(string question) {


    //gets user input
    char garbage = (stringIn(question))[0];

    while (!(garbage == 'y' || garbage == 'Y' || garbage == 'n' || garbage == 'N')) {//continues to ask until the char is y Y n or N
        //error message
        std::cout << "\nInvalid input. Not an y or n.\n";


        //ask the question again
        garbage = (stringIn(question))[0];


    }

    //if it is a no, return false
    if (garbage == 'n' || garbage == 'N') {
        return false;
    }

    //otherwise return true
    return true;





    return true;
}


/*
@param question is the question that the user must answer
Pre: Valid place for the function to return to
Post: An integer is returned
*/
int intIn(string question) {
    //ask the user thequestion
    std::cout << question;

    int garbage;

    while (!(cin >> garbage)) {//contiues until cin can be put into garbage. cin >> garbage evaluates to false if it cannot be performed
        //error message
        std::cout << "\nInvalid input. Not an integer.\n";

        //clear the error in cin
        cin.clear();

        //remove all charecters in current line of cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        //ask the question again
        std::cout << question;

    }

    //returns the garbage
    return garbage;


}


/*
@param question is the question that the user must answer
@param minValue is the minimum acceptable integer value that the user can enter (inclusive)
@param maxValue is the maximum acceptable integer value that the user can enter (inclusive)
Pre: Valid place for the function to return to
Post: An integer in the range(inclusive) is returned
*/
int intMM(string question, int minValue, int maxValue) {


    int garbage = intIn(question);//uses my previously made intIn function, then checks if it meets the value restrictions

    while (garbage < minValue || garbage > maxValue) {//continues while garbage is smaller then the minumum or greater then the maximum
        //error message
        std::cout << "\nInvalid range. Data is not within valid interval.\n";


        //clear cin (there wont be an error, but it can't hurt to clear cin)
        cin.clear();

        //remove all charecters in current line of cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        //gives the user another chance to enter data in the range
        garbage = intIn(question);


    }

    //returns the garbage
    return garbage;

}



/*
@param difficulty difficulty ranges from 1 to 5 and sets the difficulty of the game
@param wins is the number of wins
@param losses is the number of losses
@param colour sets whether or not there is colour in the terminal
@param lastTimePlayed is the last time the game was played
@param totalSecondsPLayed is the total number of seconds 
Pre: File location must be writtable 
Post: Savfile with values is written to location

*/
void saveFileWritter(int difficulty, int wins, int losses, bool colour, time_t lastTimePlayed, long totalSecondsPlayed) {
    //create the file if it does not exist, completely overwrite it if it does
    ofstream saveData("saveData.txt");

    //write all values to the save file
    saveData << difficulty << endl;
    saveData << wins << endl;
    saveData << losses << endl;
    saveData << colour << endl;
    saveData << lastTimePlayed << endl;
    saveData << totalSecondsPlayed << endl;

    //close the save file
    saveData.close();
    

}

/*
Pre: cout is valid
Post: checks if a file of a specified name exists, and if not, it makes a placholder for it
*/
void fileChecker(string fileTitle) {
    //checks if the file  exists at the right location
    ifstream file(fileTitle+".txt");

    if (file.good()) {
        std::cout << fileTitle <<" file exists and is readable." << endl;
    }
    else {
        std::cout << fileTitle << " file does not exist or it is not readable.\nMaking new " << fileTitle << " file." << endl;
        //makes a placeholder file
        //create the file if it does not exist, completely overwrite it if it does
        ofstream fileMaker("plot.txt");

        //write placeholder to the file
        fileMaker << "This is a placeholder for the " <<fileTitle << " file. Please send a bug report to anhkmopork@gmail.com";

        //close it
        fileMaker.close();

    }

    //closes the file
    file.close();

}

/*
Pre: cout is valid
Post: A series of messages to cout confiming that the neccesary files exist, and informing the user which ones are missing. If it cannot find the file, it does its best job to make it.
*/
void allFilesVerifier() {

    //checks if the file saveData.txt exists at the right location
    ifstream saveData("saveData.txt");

    if (saveData.good()) {
        std::cout << "Save file exists and is readable." << endl;
    }
    else {
        std::cout << "Save file does not exist or it is not readable.\nMaking new save file.";
        //makes the save file with all default values of difficulty 3, no wins, no loses, colour, last played at the epoch, and no seconds played
        saveFileWritter(3, 0, 0, true, 0, 0);
    }

    //closes the file
    saveData.close();


    //checks each of the files for stuff I was too lazy to type into the program
    fileChecker("plot");
    fileChecker("defeat");
    fileChecker("title");
    fileChecker("victory");


    


}


/*
Pre: cout must be valid
Post: the help menu is displayed
*/
void helpMenu() {
    //output the menu options
    std::cout << "Enter a 1 for an explaination of how to play\nEnter a 2 for Frequently Asked Questions\nEnter a 3 to go back to the menu";

    //gets the users choice
    int userChoice = intMM("\nPlease enter your choice: ", 1, 3);
    
    //does what the user chooses
    if (userChoice == 1) {//Explains the game
        std::cout << "\nThere are 5 difficulty levels.\n1 has 4 spell components and 20 tries\n2 has 4 spell components and 15 tries\n3 has 4 spell components and 10 tries\n4 has 5 spell components and 10 tries\n5 has 5 spell components and 5 tries\n\n";
        //loops through the plot and explaination
        ifstream plot("plot.txt");
        string lineHolder;

        while (getline(plot, lineHolder)) {//while there is another line to get, get the line
            // Output the text from the file
            std::cout << lineHolder;
            std::cout << "\n";//spacing at the end of line
        }

        plot.close();


    }if (userChoice == 2) {//FAQs
        std::cout << "\nAre doubles allowed: Yes.\nIs it always possible with the number of guesses: Yes.\nHow do I report a bug: There are not any bugs, any bug that you find is a feature (but if you do find a bug that is not a feature, report it to anhkmopork@gmail.com).";
    }


}


/*
Pre: cout must be valid, and the savedata file must exist
Post: A simple and robust options menu for seeing and changing some options in the savefile
*/
void optionsMenu() {
    //open saveData
    ifstream saveData("saveData.txt");



    //extract all the savefile information
    int difficulty;
    int wins;
    int losses;
    bool colour;
    time_t lastTimePLayed;
    long totalSecondsPlayed;
    saveData >> difficulty;
    saveData >> wins;
    saveData >> losses;
    saveData >> colour;
    saveData >> lastTimePLayed;
    saveData >> totalSecondsPlayed;
    //close the file
    saveData.close();

    //Output all svae file info
    std::cout << "\nThe difficulty is level " << difficulty << endl;
    std::cout << "You have won " << wins << " times" << endl;
    std::cout << "You have lost " << losses << " times" << endl;
    std::cout << "Your colour choice is set to " << colour << endl;
    std::cout << "The last time you played was " << lastTimePLayed << endl;//not formatted
    std::cout << "You have played for " << totalSecondsPlayed << " seconds" << endl;

    //ask user if they want to modify anything
    std::cout << "\nEnter 1 to change the difficulty.\nEnter 2 to toggle colour\nEnter 3 to return to main menu.";
    int userChoice = intMM("\nWhat would you like to do: ", 1, 3);

    //change difficulty
    if (userChoice == 1) {
        //state current difficulty
        std::cout << "Your current difficuty is level " << difficulty << endl;
        //explain the difficulties
        std::cout << "\nThere are 5 difficulty levels.\n1 has 4 spell components and 20 tries\n2 has 4 spell components and 15 tries\n3 has 4 spell components and 10 tries\n4 has 5 spell components and 10 tries\n5 has 5 spell components and 5 tries\n";
        //change the difficulties
        difficulty = intMM("\nWhat would you like your new difficulty to be: ", 1, 5);
    }
    if (userChoice == 2) {
        //invert the colour option
        colour = !colour;
    }

    //write the new values
    saveFileWritter(difficulty, wins, losses, colour, lastTimePLayed, totalSecondsPlayed);


}


/*
Pre: Cout must be valid
Post: The user string with colours is output
*/
void outputUserGuessWithColour(string userGuess) {
    //colours used
    //ANSI escape sequence colour codes
    string reset = "\033[0m";
    string red = "\033[0;31m";
    string blue = "\033[0;34m";
    string yellow = "\033[0;33m";
    string green = "\033[0;32m";
    for (int i = 0; i < userGuess.length(); i++) {//the users guess coloured
        if (userGuess[i] == 'F') {
            std::cout << red << 'F' << reset;
        }
        if (userGuess[i] == 'W') {
            std::cout << blue << 'W' << reset;
        }
        if (userGuess[i] == 'A') {
            std::cout << yellow << 'A' << reset;
        }
        if (userGuess[i] == 'E') {
            std::cout << green << 'E' << reset;
        }
    }
}



/*
Pre: cout must be valid
Post: the colour of the golem's eyes are output all nicely
*/
void outputGolemEyesWithColour(string outputString) {
    //colours used
    //ANSI escape sequence colour codes
    string reset = "\033[0m";
    string red = "\033[0;31m";
    string blue = "\033[0;34m";
    string yellow = "\033[0;33m";
    string green = "\033[0;32m";

    size_t positionOfFirstBlueCharecter = outputString.find('B');//index of first blue charecter
    //two output strings so it can be coloured red and blue
    string redOutputString = "";
    string blueOutputString = "";

    if (positionOfFirstBlueCharecter != string::npos) {//if there is a blue charecter
        blueOutputString = outputString.substr(positionOfFirstBlueCharecter);//this is the substring with only blue charecters
        redOutputString = outputString.substr(0, positionOfFirstBlueCharecter);//substring with only red charecters
    }
    else {//if there is no blue charecter
        redOutputString = outputString;

    }

    //display the output strings
    std::cout << red << redOutputString << reset;
    std::cout << blue << blueOutputString << reset << endl;


        
}


/*
Pre: All txt files must be vaild, cout must be vaild
Post: The game runs
*/
void gameLoop(bool& continueGame) {

    //colours used
    //ANSI escape sequence colour codes
    string reset = "\033[0m";
    string red = "\033[0;31m";
    string blue = "\033[0;34m";
    string yellow = "\033[0;33m";
    string green = "\033[0;32m";
    //enable ansi colour in console

    
    

    //Grabbing all save file information
    //open saveData
    ifstream saveData("saveData.txt");

    //extract all the savefile information
    int difficulty;
    int wins;
    int losses;
    bool colour;
    time_t lastTimePLayed;
    long totalSecondsPlayed;
    saveData >> difficulty;
    saveData >> wins;
    saveData >> losses;
    saveData >> colour;
    saveData >> lastTimePLayed;
    saveData >> totalSecondsPlayed;
    //close the file
    saveData.close();

    //increase the losses by one here so a ragequit will still count as a loss
    losses++;

    //save this new information to the save file
    saveFileWritter(difficulty, wins, losses, colour, lastTimePLayed, totalSecondsPlayed);




    


    //set number of elements in the secret code based off difficultiy
    int elementsInCode = 4;

    if (difficulty >= 4) {//for difficulties of 4 of more, there are 5 charecters in secret code
        elementsInCode = 5;
    }

    //set number of guesses based off difficulty
    int guesses = 10; //default value just in case of an error, also eleminated need for 2 if statments

    //sets guesses for difficulty levels
    if (difficulty == 1) {
        guesses = 20;
    }
    if (difficulty == 2) {
        guesses = 15;
    }
    if (difficulty == 5) {
        guesses = 5;
    }










    //random number generator
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<> dist(0, 3); // distribute results between 1 and 6 inclusive.

    //make the secret code
    string secretCode = "";
    char possibleElements[] = { 'F', 'W', 'A', 'E'};//possible elements in secret code

    for (int i = 0; i < elementsInCode; i++) {
        secretCode = secretCode + possibleElements[dist(gen)];//adds elements to secret code until it is the right length
    }











    //grab the current time
    time_t startTime = time(0);

    //if it has been more than an hour since the last play, the plot should be explained again 
    if ((startTime - lastTimePLayed) > (60 * 60)) {//time_t is in seconds so 60 secons in a minute and 60 minutes in an hour gives one hour
        //loops through the plot and explaination
        ifstream plot("plot.txt");
        string lineHolder;

        while (getline(plot, lineHolder)) {//while there is another line to get, get the line
            // Output the text from the file
            std::cout << lineHolder;
            std::cout << "\n";//spacing at the end of line
        }

        plot.close();
    }

    
    if (colour) {//if the colour choice is enabled, it will display colour, otherwise the console will be stuck with just text
        enableColour();
    }




    //initalise varibles for the guessing loop

    string userGuess;
    string prompt = "\nPlease enter the golem shutdown code using the elements " + red + "F(Fire)" + reset + ", " + blue + "W(Water)" + reset + ", " + yellow + "A(Air)" + reset + ", and " + green + "E(Earth)" + reset + ": ";
    bool invalidLetters = false;
    string userGuessCopy;
    string secretCodeCopy;
    string nextStageUserGuess;
    string nextStageSecretCode;
    string outputString;
    int nextStageStringLength;

    //clear cin to prevent any invaild input from creeping in
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    //start guessing loop
    while (guesses > 0) {
        //get the users guess for the secret code
        if (colour) {

            userGuess = stringIn(prompt);
        }
        else {
            userGuess = stringIn("\nPlease enter the golem shutdown code using the elements F(Fire), W(Water), A(Air), and E(Earth): ");
        }

        //make it uppercase
        for (auto& x : userGuess) {
            x = toupper(x);
        }





        //checks if the user input uses valid charecters
        //checks each charecter to see if it is in the possible elements array
        //reset invalid letters
        invalidLetters = false;
        for (int i = 0; i < userGuess.length(); i++) {
            char letterToCheck = userGuess[i];//get the letter
            bool letterIsInArray = false;
            //check if letter in in possible elements
            for (int d = 0; d < (sizeof(possibleElements)/sizeof(possibleElements[0])); d++) {//goes through all elements in possible elements array
                if (letterToCheck == possibleElements[d]) {
                    letterIsInArray = true;
                    break;
                }

                }

            if (!letterIsInArray) {//if the letter is not in the possible elements array, that invalid letter = true
                invalidLetters = true;
            }

            }


        //all conditions for the string
        if (invalidLetters) {//there is an invalid letter
            guesses--;
            std::cout << "\nInvalid element. You lost a try.\n";


        }
        else if (userGuess.length() != elementsInCode) {//it is a wrong length
            guesses--;//remove a guess
            std::cout << "\nWrong number of elements. You lost a try.\n";
        }
        else if (userGuess == secretCode) {//if the guess is the secret code, break out of the loop
            break;
        }
        else {//if none of those happen, then it is now tim eto actually check the code
            

            guesses--;//subtract a guess
            //reset values
            userGuessCopy = userGuess;
            secretCodeCopy = secretCode;
            nextStageUserGuess = "";
            nextStageSecretCode = "";
            outputString = "";

            //gets the number of r's
            for (int i = 0; i < elementsInCode; i++) {//loop through the userstringcopy to find matches

                if (userGuessCopy[0] == secretCodeCopy[0]) {//if the first charecter is the same
                    //add an R to output string
                    outputString = outputString + 'R';
                    
                    //remove first charecter from both strings
                    userGuessCopy.erase(0, 1);
                    secretCodeCopy.erase(0, 1);
                }
                else {//otherwise
                    //move both first chareceter to the next stage
                    nextStageUserGuess = nextStageUserGuess + userGuessCopy.substr(0, 1);
                    nextStageSecretCode = nextStageSecretCode + secretCodeCopy.substr(0, 1);
                    //remove first charecter from both strings
                    userGuessCopy.erase(0, 1);
                    secretCodeCopy.erase(0, 1);

                }
            }

            
            

            

            nextStageStringLength = nextStageUserGuess.length();//says how long the next stage userstring is


            //gets the number of b's
            for (int i = 0; i < nextStageStringLength; i++) {//checks for the code contains the chareceters, but not being an exact match


                bool isInSecretCode = false;//reset if it is in the secret code
                for (int d = 0; d < nextStageSecretCode.length(); d++) {//check if it is in the secret code
                    if (nextStageUserGuess[0] == nextStageSecretCode[d]) {
                        isInSecretCode = true;//if it is in set isinsecret code to true and stop checking
                        break;
                    }

                }

                if (isInSecretCode) {
                    //add a b to output string
                    outputString = outputString + 'B';
                    //remove first instance of charecter in the secret code

                    //find the index of it
                    size_t positionOfCharecterToRemove = nextStageSecretCode.find(nextStageUserGuess[0]);

                    //remove it
                    nextStageSecretCode.erase(positionOfCharecterToRemove, 1);//remove one charecter at the position

                }

                //remove the first charecter in the nextstage user code
                nextStageUserGuess.erase(0, 1);

            }

            //now we can output the values so the user knows what happend

            if (colour) {//output with colour
                std::cout << "\nYou entered: ";
                outputUserGuessWithColour(userGuess);//outputs the user's guess with colour

                std::cout << "\nThe Golem's eyes flashed: ";
                outputGolemEyesWithColour(outputString);
            }
            else {//if no colour is chosen
                std::cout << "\nYou entered: " << userGuess;//output the user guess
                std::cout << "\nThe Golem's eyes flashed: " << outputString << endl;//output the output string

            }

            //ouput the remaining guesses
            std::cout << "\nYou have " << guesses << " remaining guesses\n\n\n";


        }
    


    }

    //Say whethere they win or lose here
    if (guesses > 0) {//the city watch won
        

        //update last time player, total seconds played, wins and losses
        lastTimePLayed = time(0);
        totalSecondsPlayed = totalSecondsPlayed + (time(0) - startTime);
        wins++;
        losses--;

        //write the information back to savefile
        saveFileWritter(difficulty, wins, losses, colour, lastTimePLayed, totalSecondsPlayed);


        //output victory message
        std::cout << "\nThe city watch wins!";
        std::cout << "\nThe golems have been defeated!\n";

        //output vicotry art
        ifstream victory("victory.txt");
        string lineHolder;

        std::cout << yellow;
        while (getline(victory, lineHolder)) {//while there is another line to get, get the line
            // Output the text from the file
            std::cout << lineHolder;
            std::cout << "\n";//spacing at the end of line
        }
        std::cout << reset;
        victory.close();
        


    }if (guesses <= 0) {//the city watch lost
        //update last time played, and total seconds played, (dont need to update losses, I assume that the player losses)
        lastTimePLayed = time(0);
        totalSecondsPlayed = totalSecondsPlayed + (time(0) - startTime);

        //write the information to the save file
        saveFileWritter(difficulty, wins, losses, colour, lastTimePLayed, totalSecondsPlayed);
        
        //ouput deafe message
        std::cout << "\nThe city watch loses.";
        std::cout << "\nThe rampage of the Golems cannot be stopped...\n";


        //output defeat art
        ifstream defeat("defeat.txt");
        string lineHolder;

        std::cout << red;
        while (getline(defeat, lineHolder)) {//while there is another line to get, get the line
            // Output the text from the file
            std::cout << lineHolder;
            std::cout << "\n";//spacing at the end of line
        }

        std::cout << reset;
        defeat.close();


    }

    //ask the user if they are done, or if they wan tto continue

    
    continueGame = yOrN("Would you like to continue(y/n): ");

    

}


/*
Pre: cout must be valid
Post: A lovely title screen is displayed.
*/
void titleScreen(bool& continueGame) {

    //open the title file and make a string to hold on lin eat a time
    ifstream title("title.txt");
    string lineHolder;

    while (getline(title, lineHolder)) {//while there is another line to get, get the line
        // Output the text from the file
        std::cout << lineHolder;
        std::cout << "\n";//spacing at the end of line
    }
    

    title.close();



    //gives the user thie menu and asks what they want to do
    std::cout << "\n\n1. Play game\n2. Options\n3. Help\n";

    int userChoice = intMM("\nPlease enter your choice: ", 1, 3);

    //does what the user chooses to do
    if (userChoice == 1) {
        gameLoop(continueGame);
    }
    if (userChoice == 2) {
        optionsMenu();
    }if (userChoice == 3) {
        helpMenu();
    }

    


}


int main()
{
    //file verification, checks that everything with the save file is right, and that the other neccesary files also exist
    allFilesVerifier();
    
    bool continueGame = true;

    //title screen
    while (continueGame) {//always go back to title screen. When user wins/loses the game, they have the option to quit game, which will end the program execution
        titleScreen(continueGame);
    }
    
    
    




    return 0;
}






