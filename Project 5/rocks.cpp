//
//  main.cpp
//  Project 5
//
//  Created by Atibhav Mittal on 11/8/15.
//  Copyright © 2015 ati. All rights reserved.
//

#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include "utilities.h"
#include <cassert>
#include <cstring>

using namespace std;
const int MAXLENGTH = 10000;

int xxxmanageOneRound(const char words[][MAXWORDLEN +1], int nWords, int wordnum);
int countRocks(const char wordGuessed[MAXWORDLEN+1], const char secretWord[MAXWORDLEN +1]);
int countPebbles(const char wordGuessed[MAXWORDLEN+1], const char secretWord[MAXWORDLEN+1]);
void sortWord(char word[MAXWORDLEN+1]);
bool checkProbeWord(const char []);
bool checkValidity(const char wordList[][MAXWORDLEN+1], int nWords, const char word[]);
int manageOneRound(const char[][7], int, int);

int xxxmain() {
    
    char arrayOfWords[MAXLENGTH][MAXWORDLEN+1];
    int wordsLoaded = loadWords(arrayOfWords, MAXLENGTH); //find number of words loaded
    
    cout.setf(ios::fixed);
    cout.precision(2);
    
    if(wordsLoaded<1)
    {
        cout<<"No words were loaded, so I can't play the game."<<endl;
    }
    else
    {
        int minimum = 0;
        int maximum = 0;
        double average = 0;
        int roundsToPlay = 0;
        cout<<"How many rounds do you want to play? ";
        cin>>roundsToPlay;
        cin.ignore(1000, '\n');
        if(roundsToPlay<1)
        {
            cout<<"The number of rounds must be positive."<<endl;
            return 1;
        }
        else
        {
            for(int i = 1; i<=roundsToPlay; i++)
            {
                cout<<endl;
                cout<<"Round "<<i<<endl;
                int wordNumber = randInt(0, wordsLoaded-1);
                cout<<"The secret word is "<<strlen(arrayOfWords[wordNumber])<<" letters long."<<endl;
                int tries = manageOneRound(arrayOfWords, wordsLoaded, wordNumber);
                if(tries == -1)
                {
                    break;
                }
                else if(tries!=1)
                {
                    cout<<"You got it in "<<tries<<" tries."<<endl;
                
                }
                else
                {
                    cout<<"You got it in 1 try."<<endl;
                }
                if(i == 1) //first try so tries is minimum and maximum and average
                {
                    minimum = tries;
                    maximum = tries;
                    average = tries;
                }
                else
                {
                    average = ((average*(i-1)) + tries)/ i ;
                }
                if (minimum>tries) //set minimum
                {
                    minimum = tries;
                }
                if (maximum<tries) //set maximum
                {
                    maximum = tries;
                }
                cout<<"Average: "<<average<<", minimum: "<<minimum<<", maximum: "<<maximum<<endl;
            }
        }
    }
    return 0;
}

//count the number of rocks in the word guessed and the secret word
int countRocks(const char wordGuessed[MAXWORDLEN+1],const char secretWord[MAXWORDLEN +1])
{
    int numRocks = 0;
    for( int i = 0; wordGuessed[i]!='\0' || secretWord[i] != '\0'; i++)
    {
        
        if(wordGuessed[i] == secretWord[i])
        {
            //letter in ith position in both strings is the same
            numRocks++;
        }
    }
    return numRocks;
}

void sortWord(char word[MAXWORDLEN+1]) //sort the word in alphabetical order using bubble sort
{
    size_t n = strlen(word);
    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            if(word[j]<word[i])
            {
                char temp = word[i];
                word[i] = word[j];
                word[j] = temp;
            }
        }
    }
}

//count the number of pebbles in the word guessed
int countPebbles(const char wordGuessed[MAXWORDLEN+1], const char secretWord[MAXWORDLEN+1])
{
    int numberOfSameCharacters = 0;
    char wordGuessedSorted[MAXWORDLEN+1];
    char secretWordSorted[MAXWORDLEN+1];
    /*
     sort both these words in alphabetical order and store them in a different array
     */
    strcpy(wordGuessedSorted, wordGuessed);
    strcpy(secretWordSorted, secretWord);
    sortWord(secretWordSorted);
    sortWord(wordGuessedSorted);
    int i = 0, j = 0;
    while(wordGuessedSorted[i] != '\0' && secretWordSorted[j] != '\0')
    {
        if(wordGuessedSorted[i] == secretWordSorted[j])
        {
            //letter is same so move onto next character in both arrays
            numberOfSameCharacters++;
            i++;
            j++;
        }
        else if(wordGuessedSorted[i] > secretWordSorted[j])
        {
            //character in secret word sorted is smaller so increment index value of j
            j++;
        }
        else
        {
            //character in probe word sorted is smaller so increment index value of i
            i++;
        }
    }
    //numberOfSameCharacters includes the number of rocks
    numberOfSameCharacters -= countRocks(wordGuessed, secretWord);
    return numberOfSameCharacters;
}

//check if the word has any upper case alphabet or any non alphabet characters
//returns true if probe word is incorrect
bool checkProbeWord(const char word[])
{
    for(int i = 0; word[i]!= '\0'; i++)
    {
        if(!isalpha(word[i])||isupper(word[i]))
        {
            return true;
        }
    }
    return false;
}

//check if word guessed is in the array or not
bool checkValidity(const char wordList[][MAXWORDLEN+1], int nWords, const char word[])
{
    for(int i = 0; i<nWords; i++)
    {
        if(strcmp(wordList[i], word)==0)
        {
            return true;
        }
    }
    return false;
}

//manage one round of the game
int xxxmanageOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum)
{
    
    if(nWords<0 || wordnum<0 || wordnum>=nWords)
    {
        return -1;
    }
    char secretWord[MAXWORDLEN+1];
    strcpy(secretWord, words[wordnum]);
    
    
    
    char wordGuessed[MAXWORDLEN+1];
    int tries = 0;
    do
    {
        cout<<"Probe word: ";
        cin.getline(wordGuessed, 100);
        if(strlen(wordGuessed)<MINWORDLEN || strlen(wordGuessed)>MAXWORDLEN||
           checkProbeWord(wordGuessed)==true)
        {
            cout<<"Your probe word must be a word of 4 to 6 lower case letters."<<endl;
        }
        else if(checkValidity(words, nWords, wordGuessed)== false)
        {
            cout<<"I don't know that word."<<endl;
        }
        else
        {
            tries++;
            if(strcmp(wordGuessed, secretWord)!=0) //words are not the same
            {
                cout<<"Rocks: "<<countRocks(wordGuessed, secretWord)<<", ";
                cout<<"Pebbles: "<<countPebbles(wordGuessed, secretWord)<<endl;
            }
        }
    }while(strcmp(secretWord, wordGuessed)!=0);
    return tries;
}

#include <streambuf>
#include <sstream>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <random>
#include <utility>
#include <cstdlib>


class TooMuchOutput {};

class limitoutputstringbuf : public stringbuf
{
public:
    limitoutputstringbuf(streamsize max)
    : m_left(max)
    {}
    int_type overflow(int_type c = traits_type::eof())
    {
        if (m_left == 0)
            throw TooMuchOutput();
        m_left--;
        return stringbuf::overflow(c);
    }
private:
    streamsize m_left;
};

class streambuf_switcher
{
public:
    streambuf_switcher(ios& dest, ios& src)
    : streambuf_switcher(dest, src.rdbuf())
    {}
    streambuf_switcher(ios& dest, streambuf* src)
    : dest_stream(dest), saved_streambuf(dest.rdbuf(src))
    {}
    ~streambuf_switcher()
    {
        dest_stream.rdbuf(saved_streambuf);
    }
private:
    ios& dest_stream;
    streambuf* saved_streambuf;
};

int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

int xxxmanageOneRound(const char [][7], int, int);

using MORtype = function<int(const char[][7], int, int)>;
MORtype fffmanageOneRound = xxxmanageOneRound;
const initializer_list<const char*>* initWords;

int loadWords(char words[][7], int maxWords)
{
    if (maxWords < 1)
        return maxWords;
    int num = 0;
    for (auto w : *initWords)
    {
        if (num == maxWords)
            break;
        strcpy(words[num], w);
        num++;
    }
    return num;
}

void testmain(const initializer_list<const char*>& words, const char* input, const MORtype& mor)
{
    initWords = &words;
    istringstream iss(input);
    streambuf_switcher ssi(cin, iss);
    fffmanageOneRound = mor;
    xxxmain();
}

int manageOneRound(const char words[][7], int num, int wordnum)
{
    return fffmanageOneRound(words, num, wordnum);
}

void testmanageOneRound(const initializer_list<const char*>& words,
                        const char* input, int wordnum, int& score, string& output,
                        bool testBadWordnum = false)
{
    initWords = &words;
    istringstream iss(input);
    streambuf_switcher ssi(cin, iss);
    limitoutputstringbuf losb(1000);
    streambuf_switcher sso(cout, &losb);
    char wordList[9000][7];
    int nWords = loadWords(wordList, 10);
    if (testBadWordnum)
        nWords = wordnum;
    score = xxxmanageOneRound(wordList, nWords, wordnum);
    output = losb.str();
}

void testone(int n)
{
    int score;
    string output;
    
    switch (n)
    {
        default: {
            return;
        } break; case 1: {      // 0 rounds
            testmain({ "tiger", "heron" }, "0\n1\nheron\n",
                     [](const char [][7], int, int)->int
                     { throw 1; });
        } break; case 2: {      // got it in 1 try
            testmain({ "tiger", "heron" }, "1\n",
                     [](const char [][7], int, int)->int
                     { return 1; });
        } break; case 3: {      // stats for one game
            testmain({ "tiger", "heron" }, "1\n",
                     [](const char [][7], int, int)->int
                     { return 42; });
        } break; case 4: {      // stats for several games
            testmain({ "tiger", "heron" }, "4\n",
                     [](const char [][7], int, int)->int
                     {
                         static const size_t NUM_SCORES = 4;
                         static int scores[NUM_SCORES] = { 4, 6, 3, 8 };
                         static int r = NUM_SCORES - 1;
                         if (++r == NUM_SCORES)
                             r = 0;
                         return scores[r];
                     });
        } break; case 5: {      // random numbers used
            static int counts[10] = { 0 };
            static int errors = 0;
            {
                limitoutputstringbuf losb(1000);
                streambuf_switcher sso(cout, &losb);
                testmain({ "tiger", "heron", "okapi", "ocelot", "myna",
                    "hyrax", "bison", "squid", "kudu", "pika" },
                         "1000\n", [](const char [][7], int, int wordnum)->int
                         {
                             if (wordnum >= 0  &&  wordnum < 10)
                                 counts[wordnum]++;
                             else
                                 errors++;
                             return 1;
                         });
            }
            if (errors > 0)
                cout << "ERRORS: " << errors << endl;
            if (none_of(counts, counts+10,
                        [](int k) { return k-100 < -35  ||  k-100 > 35; }))
                cout << "CORRECT";
            else
            {
                for (int k = 0; k < 10; k++)
                    cout << counts[k] << " ";
            }
        } break; case 6: {      // bad arg to manageOneRound
            testmanageOneRound({ "tiger", "heron", "heron" }, "heron\n", 2,
                               score, output, true);
            cout << (score == -1 && output.empty() ? "CORRECT" : "WRONG");
        } break; case 7: {      // last word OK
            testmanageOneRound({ "tiger", "heron" }, "heron\n", 1,
                               score, output);
            cout << (score == 1 ? "CORRECT" : "WRONG");
        } break; case 8: {      // guessed in one try
            testmanageOneRound({ "tiger", "heron", "myna" }, "heron\n", 1, score, output);
            cout << (score == 1 ? "CORRECT" : "WRONG");
        } break; case 9: {      // guessed in two tries
            testmanageOneRound({ "tiger", "heron", "myna" }, "tiger\nheron\n", 1, score, output);
            cout << (score == 2 ? "CORRECT" : "WRONG");
        } break; case 10: {     // errors don't count as guesses
            testmanageOneRound({ "tiger", "heron", "myna" }, "he@on\nokapi\nheron\n", 1, score, output);
            cout << (score == 1 ? "CORRECT" : "WRONG");
        } break; case 11: {     // invalid characters in probe word
            testmanageOneRound({ "tiger", "heron", "myna" }, "he@on\nheron\n", 1, score, output);
            cout << output;
        } break; case 12: {     // too few characters in probe word
            testmanageOneRound({ "tiger", "heron", "myna" }, "abc\nheron\n", 1, score, output);
            cout << output;
        } break; case 13: {     // too many characters in probe word
            testmanageOneRound({ "tiger", "heron", "myna" }, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz\nheron\n", 1, score, output);
            cout << output;
        } break; case 14: {     // probe word not in list
            testmanageOneRound({ "tiger", "heron", "myna" }, "okapi\nheron\n", 1, score, output);
            cout << output;
        } break; case 15: {     // rocks/pebbles: 0/0
            testmanageOneRound({ "hyrax", "bison", "myna" }, "hyrax\nbison\n", 1, score, output);
            cout << output;
        } break; case 16: {     // 1/0
            testmanageOneRound({ "tiger", "bison", "myna" }, "tiger\nbison\n", 1, score, output);
            cout << output;
        } break; case 17: {     // 4/0
            testmanageOneRound({ "mouse", "louse", "myna" }, "mouse\nlouse\n", 1, score, output);
            cout << output;
        } break; case 18: {     // 0/1
            testmanageOneRound({ "tiger", "mouse", "myna" }, "tiger\nmouse\n", 1, score, output);
            cout << output;
        } break; case 19: {     // 0/4
            testmanageOneRound({ "rhino", "minor", "myna" }, "rhino\nminor\n", 1, score, output);
            cout << output;
        } break; case 20: {     // 1/3
            testmanageOneRound({ "horse", "shrew", "myna" }, "horse\nshrew\n", 1, score, output);
            cout << output;
        } break; case 21: {     // 0/5 not a win for 5 letter
            testmanageOneRound({ "stare", "aster", "myna" }, "stare\naster\n", 1, score, output);
            cout << output;
        } break; case 22: {     // 1/2 more of a letter in secret word than probe
            testmanageOneRound({ "sheep", "geese", "myna" }, "sheep\ngeese\n", 1, score, output);
            cout << output;
        } break; case 23: {     // 1/2 more of a letter in probe than secret word
            testmanageOneRound({ "geese", "sheep", "myna" }, "geese\nsheep\n", 1, score, output);
            cout << output;
        } break; case 24: {     // 0/5 multiple letters
            testmanageOneRound({ "emerge", "redeem", "myna" }, "emerge\nredeem\n", 1, score, output);
            cout << output;
        } break; case 25: {     // 1/2 probe 4, secret 5
            testmanageOneRound({ "myna", "hyena", "pika" }, "myna\nhyena\n", 1, score, output);
            cout << output;
        } break; case 26: {     // 1/2 probe 5, secret 4
            testmanageOneRound({ "hyena", "myna", "pika" }, "hyena\nmyna\n", 1, score, output);
            cout << output;
        } break; case 27: {     // 1/3 probe 4, secret 6
            testmanageOneRound({ "bear", "badger", "myna" }, "bear\nbadger\n", 1, score, output);
            cout << output;
        } break; case 28: {     // 1/3 probe 6, secret 4
            testmanageOneRound({ "badger", "bear", "myna" }, "badger\nbear\n", 1, score, output);
            cout << output;
        } break; case 29: {     // 5/0 probe 5, secret 6
            testmanageOneRound({ "tiger", "tigers", "myna" }, "tiger\ntigers\n", 1, score, output);
            cout << output;
        } break; case 30: {     // 5/0 probe 6, secret 5
            testmanageOneRound({ "tigers", "tiger", "myna" }, "tigers\ntiger\n", 1, score, output);
            cout << output;
        } break; case 31: {     // 2/2 probe 6, secret 4, repeats
            testmanageOneRound({ "veer", "vervet", "myna" }, "veer\nvervet\n", 1, score, output);
            cout << output;
        } break; case 32: {     // 2/2 probe 4, secret 6, repeats
            testmanageOneRound({ "vervet", "veer", "myna" }, "vervet\nveer\n", 1, score, output);
            cout << output;
        } break; case 33: {     // checking doesn't corrupt word
            int score2;
            string output2;
            testmanageOneRound({ "llama", "halal", "myna" }, "llama\nllama\nhalal\n", 1, score, output);
            testmanageOneRound({ "llama", "halal", "myna" }, "halal\nhalal\nllama\n", 0, score2, output2);
            cout << (score == 3 && score2 == 3 && output == output2 ? "CORRECT" : "WRONG");
        } break;
    }
    cout << endl;
}

int main()
{
    cout << "Enter test number (1-33): ";
    int n;
    cin >> n;
    string s;
    {
        limitoutputstringbuf losb(1000);
        streambuf_switcher sso(cout, &losb);
        
        try
        {
            testone(n);
            cout << "DONE" << endl;
        }
        catch(...)
        {
        }
        
        s = losb.str();
    }
    cout << s;
    if (!s.empty()  &&  s.back() != '\n')
        cout << endl;
}