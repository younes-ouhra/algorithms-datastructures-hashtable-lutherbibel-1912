#ifndef WORDHASH_H
#define WORDHASH_H
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "WordHashItem.h"

extern std::hash<std::string> calc_word_hash;

class WordHashOpen
{
    private:
        size_t Tablesize;
        WordHashItem** Items;
        size_t LastCollisionDepth;
    
    public:
        WordHashOpen(size_t Tablesize)
        :Tablesize(Tablesize), Items(new WordHashItem*[Tablesize])
        {
            for (size_t i=0; i<Tablesize; i++)
                {Items[i]=nullptr;}
        }
        

        WordHashOpen(const WordHashOpen& rhs)
        :Tablesize(rhs.Tablesize), Items(new WordHashItem*[Tablesize])
        {
            for (size_t i=0; i<Tablesize; i++)
                {Items[i]=new WordHashItem(*rhs[i]);}
        }

        ~WordHashOpen()
            {delete [] Items;}
        
        size_t getTablesize()const
            {return Tablesize;}
        
        size_t hashfunction(const std::string& Text)
            {return calc_word_hash(Text)%Tablesize;}

        void hashing_linearProbing(std::string word)
        {
            size_t index = hashfunction(word);

            if(Items[index] == nullptr)
                {Items[index] = new WordHashItem(word, Tablesize);}

            else if(Items[index] != nullptr && *Items[index] == word)
                {Items[index]->getCounter()++;}
            
            else if(Items[index] != nullptr && *Items[index] != word)
            {
                size_t i = 1;
                size_t CollisionDepth = 1;
                bool noHashing = false;

                while(Items[(index + i) % Tablesize] != nullptr)
                {
                    CollisionDepth++;
                    if(Items[(index + i) % Tablesize]->getText() == word)
                    {
                        Items[(index + i) % Tablesize]->getCounter()++;
                        noHashing = true;
                        break;
                    }
                    i++;
                }
                
                if(!noHashing)
                {
                    Items[(index + i) % Tablesize] = new WordHashItem(word, Tablesize);
                    Items[(index + i) % Tablesize]->getCollisionDepth() = CollisionDepth;
                }
            }
        }

        void hashing_quadraticProbing(std::string word)
        {
            size_t index = hashfunction(word);

            if(Items[index] == nullptr)
                {Items[index] = new WordHashItem(word, Tablesize);}

            else if(Items[index] != nullptr && *Items[index] == word)
                {Items[index]->getCounter()++;}
            
            else if(Items[index] != nullptr && *Items[index] != word)
            {
                size_t i = 1;
                size_t CollisionDepth = 1;
                bool noHashing = false;

                while(Items[(index + (i*i)) % Tablesize] != nullptr)
                {
                    CollisionDepth++;
                    if(Items[(index + (i*i)) % Tablesize]->getText() == word)
                    {
                        Items[(index + (i*i)) % Tablesize]->getCounter()++;
                        noHashing = true;
                        break;
                    }
                    i++;
                }
                
                if(!noHashing)
                {
                    Items[(index + (i*i)) % Tablesize] = new WordHashItem(word, Tablesize);
                    Items[(index + (i*i)) % Tablesize]->getCollisionDepth() = CollisionDepth;
                }
            }
        }
        

        WordHashItem*& operator[](size_t Index)
            {return Items[Index%Tablesize];}

        WordHashItem*& operator[](size_t Index) const
            {return Items[Index%Tablesize];}

        WordHashItem*& operator[](const std::string& Key)
            {return Items[hashfunction(Key)];}
        

        void print(double excutionTime, std::string theMethode)
        {
            time_t timestamp = time(&timestamp);
            struct tm datetime = *localtime(&timestamp);
	
            std::string fileName = "RESULTS_" + theMethode + "_";
            std::string day = std::to_string(datetime.tm_mday);
            std::string mont = std::to_string(datetime.tm_mon);
            std::string year = std::to_string(datetime.tm_year);
            std::string minut = std::to_string(datetime.tm_min);
            std::string hour = std::to_string(datetime.tm_hour);
    
            fileName = fileName + day + "_" + mont + "_" + year + "_" + "at" + hour + "_" + minut + ".txt";

            std::ofstream myFile(fileName);

            myFile << "\n\t\t\t\tTHE HASHING'S RESULTS WITH " + theMethode + ":\t\t\t\t\n\n";

            myFile << std::left << std::setw(15) << "HT-index";                     // Left aligned
            myFile << std::left << std::setw(15) << "word from HT";                 // Left aligned
            myFile << std::right << std::setw(15) << "repetitions";                 // Right aligned
            myFile << std::right << std::setw(15) << "should-index";                // Right aligned
            myFile << std::right << std::setw(15) << "is-index";                    // Right aligned
            myFile << std::right << std::setw(25) << "Depth of Collisions";         // Right aligned
            myFile << std::endl;

            for(size_t i = 0; i < Tablesize; i++)
            {
                myFile << std::left << std::setw(15) << "[" + std::to_string(i) + "]";

                if(Items[i] != nullptr)
                {
                    myFile << std::left << std::setw(15) << Items[i]->getText();
                    myFile << std::right << std::setw(15) << Items[i]->getCounter();
                    myFile << std::right << std::setw(15) << Items[i]->getShouldIndex();
                    myFile << std::right << std::setw(15) << i;
                    myFile << std::right << std::setw(25) << Items[i]->getCollisionDepth();
                    myFile << std::endl;
                }
                
                else if(Items[i] == nullptr)
                    {myFile << std::setw(15) << "___" << std::endl;}
                
            }

            size_t belegt=0;
            size_t unbelegt=0;
            WordHashItem* MaxWord=nullptr;
            WordHashItem* MaxWordDeap=nullptr;
            for (size_t i=0; i< Tablesize; i++)
            {
                if(Items[i])
                {
                    belegt++;
                    if(!MaxWord)                                                            {MaxWord=Items[i];}
                    if(!MaxWordDeap)                                                        {MaxWordDeap=Items[i];}
                    if(Items[i]->getCounter() > MaxWord->getCounter())                      {MaxWord=Items[i];}
                    if(Items[i]->getCollisionDepth() > MaxWordDeap->getCollisionDepth())    {MaxWordDeap=Items[i];}
                }
                
                else
                    {unbelegt++;}
            }

            myFile << "\n\nThe Hash-Table has " << belegt << " Elements (" << belegt*100.0/(belegt+unbelegt) << "%)." << std::endl;
            myFile << "The most common word is: ''" << MaxWord->getText() << "''." << std::endl;
            myFile << "The depthest collision was ''" << MaxWordDeap->getText() << "'' with " << MaxWordDeap->getCollisionDepth() << std::endl;
            myFile << "The excution time was " << excutionTime << " sec." << std::endl;
            myFile.close();
        }

};

#endif // WORDHASH_H