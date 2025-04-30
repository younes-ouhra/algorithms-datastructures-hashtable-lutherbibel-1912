#ifndef WORDHASHITEM_H
#define WORDHASHITEM_H
#include <string>

extern std::hash<std::string> calc_word_hash;

class WordHashItem
{
    private:
        std::string text;
        size_t counter;
        size_t should_index;
        size_t collisionDepth;

    public:
        WordHashItem(std::string text, size_t Tablesize)
        :text(text), counter(1), collisionDepth(0), should_index(calc_word_hash(text)%Tablesize){}

        std::string getText() const                     {return text;}

        size_t& getCounter()                            {return counter;}

        size_t getShouldIndex() const                   {return should_index;}

        size_t& getCollisionDepth()                     {return collisionDepth;}
        
        bool operator==(const WordHashItem& rhs) const  {return text==rhs.text;}
        
        bool operator!=(const WordHashItem& rhs) const  {return text!=rhs.text;}
        
        bool operator==(const std::string& rhs) const   {return text==rhs;}
        
        bool operator!=(const std::string& rhs) const   {return text!=rhs;}
};
#endif