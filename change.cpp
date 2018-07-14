/*
 * Program name: change.cpp
 * Description: This program makes change for an amount A using as few coins as possible.
 * Name: Calista Wong
 * * */
#include <iostream>
#include <climits>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/*Input:
 * amount: the amount you need to make in coins
 * d: array with the values of our coin denoms
 * size: number of coin denoms we are working with
 * C: array with space set to amount+1, used for keeping track of number of coins we need
 * s: array with space set to amount+1, used for keeping track of the coins we will use
 *
*/
//Citation: http://www.bogotobogo.com/Algorithms/dynamic_programming.php
int CoinChangeDynamic(int amount, int d[], int size, int C[], int s[])
{
    C[0] = 0; //initialize the base case
    for(int j = 1; j <= amount; j++) //do until change amount becomes zero
        {
                C[j] = INT_MAX; //initialize each value in C as maximum value possible
                for(int i = 0; i < size; i++) //do for every coin denomination value
                        {
                                if(j >= d[i] && 1 + C[j-d[i]] < C[j] ) //if current amount we are looking at is greater than or equal to the coin denomination value we are looking at AND number of coins used is less than the previous
                                        {
                                                C[j] = 1 + C[j-d[i]]; //store the number
                                                s[j] = i;  // store the coin, i-th denomination used for the amount of j
                                        }
                        }
        }
        return C[amount]; //return minimum number of coins
}

int main()
{
    ifstream infile;
        infile.open("amount.txt");
        if (!infile)
                {
                        cout << "File not found." << endl;
                }
        else
                {
                        //count how many lines and the highest number of elements
                        string str;
                        int numLine = 0;
                        int highest = 0;
                        while (getline(infile, str))
                                {
                                        numLine++;
                                        //store as string vector
                                        vector<string> result;
                                        istringstream iss(str);
                                        for(string s; iss >> s;)
                                                result.push_back(s);
                                        if (result.size() > highest)
                                        highest = result.size();
                                }
                        numLine = numLine+numLine; //allocate space for the new line

                        //rewind the file
                        infile.clear();
                        infile.seekg(0);

                        //create a 2D array using info
                        int myArray[numLine][highest];

                        //initialize every third line with all 0
 				  for (int i=0; i<numLine; i++)
                        {
                                for (int j=0; j<highest; j++)
                                {
                                        myArray[i][j] = 0;
                                }
                        }

                        //create another 2D array with bool info
                        bool boolArray[numLine][highest];
                        //initialize with all false
                        for (int i=0; i<numLine; i++)
                        {
                                for (int j=0; j<highest; j++)
                                {
                                        boolArray[i][j] = false;
                                }
                        }

                        bool marker = true; //variable that keeps track of whether we are looking at coin denoms or amounts
                        int row = 0;

                        int amount;
                        int*array;
                        int sizeArr = 0;


                        int getResult = 0;
                        while (getline(infile, str))
                                {
                                        if (marker == true) //we need to store the first line in an array
                                                {
                                                        marker = false;
                                                        //we need to store the numbers in the line in an array
                                                        vector<string> result;
                                                        istringstream iss(str);
                                                        for(string s; iss >> s;)
                                                                result.push_back(s);
                                                        //dynamic array for number of vector elements
                                                        array = new int[result.size()];

                                                        //store size of array
                                                        sizeArr = result.size();
                                                        //convert into string and store into array
                                                              for (int i=0; i<result.size(); i++)
                                                              {
                                                                        //convert string into integer
                                                                        string myString = result[i];
                                                                        stringstream geek(myString);
                                                                        int x = 0;
                                                                        geek >> x;

                                                                        //store into array
                                                                        array[i] = x;

                                                              }

                                                        //store into data array
                                                        for (int i=0; i<result.size(); i++)
                                                                {
                                                                        myArray[row][i] = array[i];
                                                                        boolArray[row][i] = true;
                                                                }

                                                        //increment row
                                                        row++;
                                                }
                                        else //marker == false
                                                {
                                                        marker = true;
                                                        //convert string into integer
                                                        stringstream geek(str);
                                                        int x = 0;
                                                        geek >> x;
                                                        amount = x;
 //store into data array
                                                        myArray[row][0] = amount;
                                                        boolArray[row][0] = true;

                                                        //increment row
                                                        row++;

                                                        //initialize row below with zero
                                                        for (int i=0; i<sizeArr; i++)
                                                        {
                                                                myArray[row][i] = 0;
                                                                boolArray[row][i] = true;
                                                        }

                                                }
                                                        getResult++;


                                        if (getResult==2) //ONLY send to function if we have both the coin denoms and amount
                                                {
                                                        //testing information:
                                                        int size = sizeArr;
                                                        int *C = new int[amount+1];
                                                        int *s = new int[amount+1];
                                                        int ans = CoinChangeDynamic(amount, array, size, C, s);
                                                        int k = amount;
                                                        //store in data array
                                                        while(k)
                                                                {
                                                                        for (int i=0; i<sizeArr; i++) //sizeArr is the length of the line, or number of coins
                                                                        {
                                                                                if (array[i] == array[s[k]])
                                                                                {
                                                                                        //store count in data array
                                                                                        myArray[row][i]++;
                                                                                }

                                                                        }
                                                                        k = k - array[s[k]];
                                                                }
                                                        row++;
                                                        delete[] C;
                                                        delete[] s;

                                                        //store the number of coins used
                                                        myArray[row][0] = ans;
                                                        boolArray[row][0] = true;

                                                        //reset to next pair of lines
                                                        getResult = 0;
                                                        row++;
                                                }
                                        }


                        infile.close();


                        //write to data file
                        ofstream outfile;
                        outfile.open("change.txt");
                        for (int i=0; i<numLine; i++)
                                {
                                        for (int j=0; j<highest; j++)
                                                {
                                                        if (boolArray[i][j] == true)
                                                        {
                                                                outfile << myArray[i][j] << " " ;
                                                        }
                                                }
                                        outfile << endl;
                                }

                }

        return 0;
}