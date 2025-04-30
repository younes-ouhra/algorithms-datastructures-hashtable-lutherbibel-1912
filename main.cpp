#include <iostream>
#include <fstream>
#include <string>
#include "WordHash.h"
#include "WordHashItem.h"

using namespace std;

void purgeString(string& text)
{
    size_t result=0;
    while((result=text.find_first_not_of("abcdefghijklmnopqrstuvwxyz"
        "äöüß""ABCDEFGHILJKLMNOPQRSTUVWXYZ"
        "ÄÖÜ"))!=string::npos)
        {text.erase(result, 1);}
}

int main()
{
    WordHashOpen HashTable1(45562);
    WordHashOpen HashTable2(45562);
    WordHashOpen HashTable3(45562);
    WordHashOpen HashTable4(45562);

    //1ST HASHING
    fstream source1("deu_Lutherbibel_1912.txt");
    string word = "";
    double time=0.0, tstart;
    tstart = clock();                               // start
    while (source1 >> word)
    {
        purgeString(word);
        HashTable1.hashing_linearProbing(word);
    }
    time = clock() - tstart;                        // end
    time = time/CLOCKS_PER_SEC;
    HashTable1.print(time, "LINEAR_PROBING_");
    cout << "The excution time for 1 Bible with linear Probing was " << time << " sec.\n";
    
    
    //2ND HASHING
    fstream source2("deu_Lutherbibel_1912.txt");
    word = "";
    tstart = clock();                               // start
    while (source2 >> word)
    {
        purgeString(word);
        HashTable2.hashing_quadraticProbing(word);
    }
    time = clock() - tstart;                        // end
    time = time/CLOCKS_PER_SEC;
    HashTable2.print(time, "QUADRATIC_PROBING_");
    cout << "The excution time for 1 Bible with quadratic Probing was " << time << " sec.\n";


    //3RD HASHING
    fstream source3("deu_Lutherbibel_1912_10.txt");
    word = "";
    tstart = clock();                               // start
    while (source3 >> word)
    {
        purgeString(word);
        HashTable3.hashing_linearProbing(word);
    }
    time = clock() - tstart;                        // end
    time = time/CLOCKS_PER_SEC;
    HashTable3.print(time, "LINEAR_PROBING_10_");
    cout << "The excution time for 10 Bible with linear Probing was " << time << " sec.\n";


    //4TH HASHING
    fstream source4("deu_Lutherbibel_1912_10.txt");
    word = "";
    tstart = clock();                               // start
    while (source4 >> word)
    {
        purgeString(word);
        HashTable4.hashing_quadraticProbing(word);
    }
    time = clock() - tstart;                        // end
    time = time/CLOCKS_PER_SEC;
    HashTable4.print(time, "QUADRATIC_PROBING_10_");
    cout << "The excution time for 10 Bible with quadratic Probing was " << time << " sec.\n";

    return 0;
}