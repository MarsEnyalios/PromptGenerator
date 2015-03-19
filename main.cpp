//Mariah Burkett, 3.12.2015
//This program is designed: to generate prompts from a prompts.txt file in order to help the user write.
//Assuming a mildly intelligent user (won't enter over the amount of prompts in file. It won't crash the program to do so, however.)

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int countPrompts(string prompt[]);
void randPrompt(string prompt[], int randomPick, int numOfPrompts);
void pickPrompt(string prompt[]);
void writeDrabble(string prompt[], int randomPick, int numOfPrompts);
void wordCount(string erste);
void noSpaceCharCount(string erste);
void spaceCharCount(string erste);
void deletePrompt(string prompt[]);
void addPrompt();
void editPrompt(string prompt[]);

int main()
{
    const int ARR_SIZE = 5000;
    int choose;
    string prompt[ARR_SIZE];
    int numOfPrompts;
    int randomPick;

    srand(time(NULL));

    numOfPrompts = countPrompts(prompt);
    randomPick = rand()%numOfPrompts;

    cout << "This is a prompt generator! Prompts are helpful for when you're experiencing writer's "
         << "block, or if you want to write something different from normal, or if you're trying to "
         << "expand your boundaries as a writer. Here are your options: \n" << endl;

    do
    {
        cout << "\t1: Generate a random prompt\n"
             << "\t2: Select a prompt by number\n"
             << "\t3: Write from a random prompt\n"
             << "\t4: Add a prompt\n"
             << "\t5: Delete a prompt by number\n"
             << "\t6: Modify a prompt by number\n"
             << "\t7: Exit\n" << endl << "There are currently " << numOfPrompts << " prompts saved. What would you like to do? ";

        cin >> choose;
        cin.clear();
        cin.ignore(100, '\n');

        if (choose == 1)
        {
           randPrompt(prompt, randomPick, numOfPrompts);
        }
        else if (choose == 2)
        {
            pickPrompt(prompt);
        }
        else if (choose == 3)
        {
            writeDrabble(prompt, randomPick, numOfPrompts);
        }
        else if (choose == 4)
        {
            addPrompt();
            numOfPrompts = countPrompts(prompt);
        }
        else if (choose == 5)
        {
            deletePrompt(prompt);
            numOfPrompts = countPrompts(prompt);
        }

        else if (choose == 6)
        {
            editPrompt(prompt);
        }
        else if (choose == 7)
            cout << "\nCome again!\n" << endl;
        else
            cout << "Not an option!\n\n" << endl;
    } while (choose != 7);

    return 0;
}

//Function: countPrompts
//Description: Counts how many prompts are currently in the file prompts.txt
//Input: string prompt (pass by value because it's not being changed, just being counted)
//Output: int howMany; this is how many prompts there are in the file
//Precondition: the file 'prompts.txt' is already made

int countPrompts(string prompt[])
{
    int howMany = 0;

    ifstream fin;
    fin.open("prompts.txt");

    if (fin.is_open())
    {
        while (isalnum(fin.peek()) || ispunct(fin.peek()))
        {
            getline(fin, prompt[howMany]);
            howMany++;
        }
        fin.close();
    }

    return howMany;
}

//Function: randPrompt
//Description: Generates a random prompt from the database
//Input: string prompt[] and int randomPick (both by value because not being changed, just displayed)
//Precondition: prompt.txt must be made, countPrompts() must be run before, randomPick must be initialized

void randPrompt(string prompt[], int randomPick, int numOfPrompts)
{
    char mainMenu;
    randomPick = rand()%numOfPrompts;
    cout << "\nPROMPT #" << (randomPick + 1) << ": "  << prompt[randomPick] << "\n" << endl;

    cout << "Press any letter or number (+ enter) to continue. ";
    cin >> mainMenu;
    cin.clear();
    cin.ignore(100, '\n');
    cout << "\n" << endl;
}

//Function: pickPrompt
//Description: Allows the user to pick a prompt from the database
//Input: string prompt[] (again by value because not being changed)
//Precondition: string prompt[] is made, countPrompts() has been made and run

void pickPrompt(string prompt[])
{
    int userPick;
    char mainMenu;

    cout << "\nWhich prompt would you like? ";
    cin >> userPick;
    cin.clear();
    cin.ignore(100, '\n');

    if (userPick <= 0)
        cout << "\nYou'll make the program crash if you enter 0 or less!\n" << endl;
    else
        cout << "\nPROMPT #" << userPick << " IS: " << prompt[userPick-1] << "\n" << endl;

    cout << "Press any letter or number (+ enter) to continue. ";
    cin >> mainMenu;
    cin.clear();
    cin.ignore(100, '\n');
    cout << "\n" << endl;
}

//Function: writeDrabble
//Description: Allows the user to write to a text file
//Input: string prompt[] and int randomPick (both by value because not being changed, just displayed;
//       randomPick and numOfPrompts included for the sole purpose of being able to run randPrompt()
//Precondition: randPrompt() has been made
//Postcondition: A new, custom-named txt file is made that contains the user's words

void writeDrabble(string prompt[], int randomPick, int numOfPrompts)
{
    string erste = "";
    string zweite = "";  //I must have two of these so one can append to the other. Or else it does weird things.
    string fileName;
    int once = 0;

    ofstream fout;

    randPrompt(prompt, randomPick, numOfPrompts);

    cout << "Start writing! (To stop writing, press enter, type x12345, and press enter again). Go!\n" << endl;

    do
    {
        getline(cin, zweite);
        if (zweite == "x12345")
            erste.append("\n");
        else if (once == 0)
        {
            once++;
            erste.append(zweite); //eliminate \n at beginning of text files
        }
        else
            erste.append("\n" + zweite);
    } while (zweite != "x12345");

    wordCount(erste);
    noSpaceCharCount(erste);
    spaceCharCount(erste);

    cout << "What would you like to save this drabble under? (Be VERY careful not to overwrite pre-existing txt files!) ";

    do
    {
        getline(cin, fileName);
        if (fileName == "prompts")
            cout << "Trust me, you don't want to do that. Pick a different name: ";
    } while (fileName == "prompts");

    fileName = fileName + ".txt";
    fout.open(fileName.c_str());

    if (fout.is_open())
    {
        fout << erste;
        fout.close();
    }

    cout << "\nFile saved under " << fileName << " in whatever folder this application is located in!\n\n" << endl;
}

//Function: wordCount
//Description: Counts how many words a user wrote in a drabble
//Input: string erste by value b/c it's only displaying
//Precondition: writeDrabble() must be run

void wordCount(string erste)
{
    int Count = -1;

    for (int i = 0; i < erste.length(); i++)
    {
        if (erste[i] == ' ' || erste[i] == '\n')
           Count++;
    }

    cout << "\nGreat job! That was " << Count << " words, " ;
}

//Function: noSpaceCharCount
//Description: Counts how many characters there are without spaces in a certain drabble
//Input: string erste by value b/c it's only displaying
//Precondition: writeDrabble() must be run

void noSpaceCharCount(string erste)
{
    int Count = 1;

    for (int i = 0; i < erste.length(); i++)
    {
        if (erste[i] != ' ')
           Count++;
    }

    cout << Count << " characters with no spaces, and ";
}

//Function: spaceCharCount
//Description: Counts how many characters WITH spaces there are in a certain drabble
//Input: string erste by value b/c it's only displaying
//Precondition: writeDrabble() must be run

void spaceCharCount(string erste)
{
    int Count = 1;

    for (int i = 0; i < erste.length(); i++)
    {
        if (erste[i] != ' ' || erste[i] == ' ')
           Count++;
    }

    cout << Count << " characters with spaces. Great job again!\n\n" << endl;
}

//Function: deletePrompt
//Description: Allows a user to remove a prompt from the database
//Input: string prompt[] by value
//Precondition: prompts.txt be made, countPrompts() be made
//Postcondition: prompts.txt may be altered, depending on success of operation

void deletePrompt(string prompt[])
{
    int whichPrompt;                            //This is the variable that lets the user choose what prompt
    char iAmSure;
    int counter = 0;
    string thisPrompt;                          //This is the variable that we use to check if whichPrompt is equal to whatever prompt it is
    bool deleted;

    ifstream fin;
    ofstream fout;

    cout << "\nWhich prompt would you like to delete? ";
    cin >> whichPrompt;
    cin.clear();
    cin.ignore(100, '\n');

    if (whichPrompt <= 0)
    {
        cout << "\nYou'll make the program crash if you enter 0 or less!\n" << endl;
        return;
    }
    else
        whichPrompt--;

    cout << "\nThat prompt is: \n" << endl;
    cout << prompt[whichPrompt] << endl;
    cout << "\nAre you SURE you want to delete this prompt? (Y/N): ";
    cin >> iAmSure;
    cin.clear();
    cin.ignore(100, '\n');

    if (iAmSure == 'y' || iAmSure == 'Y')
    {
        fin.open("prompts.txt");

        if (fin.is_open())
        {
            while (isalnum(fin.peek()) || ispunct(fin.peek()))
            {
                getline(fin, thisPrompt);

                if (prompt[whichPrompt] != thisPrompt)
                {
                    prompt[counter] = thisPrompt;
                    counter++;
                }
                else
                {
                    deleted = true;
                }
            }
            fin.close();
        }
        else
            deleted = false;

        //Overwrite the file with the new information.

        fout.open("prompts.txt");

        if (fout.is_open())
        {
            for (int i = 0; i < counter; i++)
            {
                fout << prompt[i] << endl;
            }
            fout.close();
        }
        else
            deleted = false;
    }
    else
    {
        deleted = false;
    }

    if (deleted)
    {
        cout << "\nPrompt " << (whichPrompt + 1) << " was successfully removed!\n" << endl;
    }
    else
    {
        cout << "\nNo prompt was removed.\n" << endl;
    }
}

//Function: addPrompt
//Description: Allows a user to append a prompt to the prompts.txt file
//Precondition: prompts.txt file must be made (or else it'll make one for itself, I believe)
//Postcondition: A prompt is appended to the file

void addPrompt()
{
    string prompt;
    bool added = true;

    ifstream fin;
    ofstream fout;

    fin.open("prompts.txt");
    if (fin.is_open())
    {
        while (isalnum(fin.peek()) || ispunct(fin.peek()))
        {
            getline(fin, prompt);
        }
        fin.close();
    }
    else
        added = false;

    fout.open("prompts.txt", ios::app);

    if (fout.is_open())
    {
        cout << "Prompt to add: ";
        getline(cin, prompt);

        fout << prompt << "\n";

        fout.close();
    }
    else
        added = false;

    if (added)
        cout << "\nPrompt successfully added! \n" << endl;
    else
        cout << "\nSomething went wrong. No prompt was added.\n" << endl;
}

//Function: editPrompt
//Description: Allows the user to pick a prompt and modify it
//Input: string prompt[] (by value because it's not saving the information inside the program)
//Precondition: prompts.txt must be made
//Postcondition: prompts.txt is edited

void editPrompt(string prompt[])
{
    int whichPrompt;
    char iAmSure;
    string newPrompt;
    string thisPrompt;
    int counter = 0;
    bool edited;

    ifstream fin;
    ofstream fout;

    cout << "\nEnter the number of the prompt you would like to edit: ";
    cin >> whichPrompt;
    cin.clear();
    cin.ignore(100, '\n');

    if (whichPrompt <= 0)
    {
        cout << "\nYou'll crash the program if you enter 0 or less!\n" << endl;
        return;
    }
    else
        cout << "\nPrompt #" << whichPrompt << ": " << prompt[whichPrompt-1] << "\n";

    cout << "\nAre you sure you'd like to modify this prompt? (Y/N): ";
    cin >> iAmSure;
    cin.clear();
    cin.ignore(100, '\n');

    if (iAmSure == 'y' || iAmSure == 'Y')
    {
        fin.open("prompts.txt");

        if (fin.is_open())
        {
            while (isalnum(fin.peek()) || ispunct(fin.peek()))
            {
                getline(fin, thisPrompt);

                if (prompt[whichPrompt-1] != thisPrompt)
                {
                    prompt[counter] = thisPrompt;
                    counter++;
                }
                else
                {
                    cout << "\nEnter the edited prompt: ";
                    getline(cin, newPrompt);
                    prompt[counter] = newPrompt;
                    counter++;
                    edited = true;
                }
            }
            fin.close();
        }
        else
            edited = false;

        fout.open("prompts.txt");

        if (fout.is_open())
        {
            for (int i = 0; i < counter; i++)
            {
                fout << prompt[i] << endl;
            }
            fout.close();
        }
        else
            edited = false;
    }
    else
        edited = false;

    if (edited)
        cout << "Prompt successfully edited!\n" << endl;
    else
        cout << "\nNo prompt was edited.\n" << endl;
}
