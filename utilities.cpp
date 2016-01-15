// utilities.cpp

#define _CRT_SECURE_NO_DEPRECATE

#include "utilities.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <random>
#include <utility>
using namespace std;

//*********************
//***  On a Windows system, if you replace the file name below with the
//***  name of some other file, use / in the string instead of \ (e.g.,
//***  "C:/CS31/Project5/mywordfile.txt").
//
//***  On a Mac, it's probably easiest to use the complete pathname to
//***  the words file, e.g. "/Users/yourUsername/words.txt" or
//***  "/Users/yourUsername/CS31/P5/words.txt".
//
//***  On a SEASnet Linux server, if you put the words.txt file in the
//***  same directory as your .cpp file, you can use "words.txt" as the
//***  file name string.
const char WORDFILENAME[] = "/Users/atibhav/Desktop/Class Stuff/CS 31 /wordList.txt";

int loadWords(char words[][MAXWORDLEN+1], int maxWords)
{
    
    /*ifstream wordfile(WORDFILENAME);
    if ( ! wordfile)
    {
        cout << "Cannot open " << WORDFILENAME << "!" << endl;
        return -1;
    }
    const int MAXFILELINELEN = 10000;
    char line[MAXFILELINELEN];
    int numWords = 0;
    while (wordfile.getline(line, MAXFILELINELEN))
    {
        if (numWords == maxWords)
        {
            cout << "Using only the first " << numWords << " words from "
            << WORDFILENAME << "." << endl;
            break;
        }
        
        // Store only words with of the right number of lower case letters
        
        int k;
        for (k = 0; islower(line[k]); k++)
            ;
        
        // The following two lines fix a potential issue for non-Windows
        // users and are harmless for Windows users.
        
        if (line[k] == '\r')
            line[k] = '\0';
        
        if (line[k] == '\0'  &&  k >= MINWORDLEN  &&  k <= MAXWORDLEN)
        {
            strcpy(words[numWords], line);
            numWords++;
        }
    }
    return numWords;*/
    strcpy(words[0], "eager");
    strcpy(words[1], "easter");
    strcpy(words[2], "jesse");
    strcpy(words[3], "track");
    strcpy(words[4], "dress");
    strcpy(words[5], "chair");
    strcpy(words[6], "peanut");
    strcpy(words[7], "laptop");
    strcpy(words[8], "guide");
    strcpy(words[9], "text");
    strcpy(words[10], "share");
    strcpy(words[11], "light");
    strcpy(words[12], "nail");
    strcpy(words[13], "colour");
    strcpy(words[14], "short");
    strcpy(words[15], "long");
    strcpy(words[16], "leaf");
    strcpy(words[17], "pills");
    strcpy(words[18], "sheets");
    strcpy(words[19], "blank");
    strcpy(words[20], "blink");
    strcpy(words[21], "favour");
    strcpy(words[22], "apple");
    strcpy(words[23], "cats");
    strcpy(words[24], "bears");
    strcpy(words[25], "monkey");
    strcpy(words[26], "trash");
    strcpy(words[27], "sign");
    strcpy(words[28], "outlet");
    strcpy(words[29], "switch");
    strcpy(words[30], "window");
    strcpy(words[31], "brick");
    strcpy(words[32], "green");
    strcpy(words[33], "mouse");
    strcpy(words[34], "person");
    strcpy(words[35], "bench");
    strcpy(words[36], "press");
    strcpy(words[37], "powder");
    
    return 38;
}

// Return random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    static uniform_int_distribution<> distro(min, max);
    return distro(generator);
}