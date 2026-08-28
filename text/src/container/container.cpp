#include"container.h"

using namespace std;
typedef map<string,int>::value_type valType;
typedef pair< short,short > location; 
typedef vector< location > loc;  
typedef vector< location > loc; 
typedef vector< string > text; 
typedef pair< text*,loc* > text_loc;
static void add_map(int type,map<string,int>* word,string name,int value)
{
    // map<string,int> word = word1;
    switch(type)
    {
        case 0:
            (*word)[name] = value;
            break;
        case 1:
            word->insert(map<string,int>::value_type(name,value));
            break;
        case 2:
            word->insert(valType(name,value));
    }
    cout<<name<<" = "<<(*word)[name]<<endl;
}
static int container_find(map<string,int> word,string name)
{
    int iterator = 0;
    map<string,int>::iterator it;
    it =  word.find(name);
    if(it != word.end())
    {
        iterator = (*it).second;
        cout<<name<<":"<<iterator<<endl;
    }  
    return iterator;
}
void display_map_text( map<string,loc*> *text_map ) 
{ 
    typedef map<string,loc*> tmap; 
    tmap::iterator iter = text_map->begin(), 
    iter_end = text_map->end(); 
    while ( iter != iter_end ) 
    { 
        cout << "word: " << (*iter).first << " ("; 
        int loc_cnt = 0; 
        loc *text_locs = (*iter).second; 
        loc::iterator liter = text_locs->begin(), 
        liter_end = text_locs->end(); 
        while ( liter != liter_end ) 
        { 
            if ( loc_cnt ) 
                cout << ','; 
            else ++loc_cnt; 
                cout << '(' << (*liter).first << ',' << (*liter).second << ')'; 
            ++liter; 
        } 
        cout << ")\n"; 
        ++iter; 
    } 
    cout << endl; 
} 
void container_init(void)
{
    cout<<"抽象容器"<<endl;
    map<string,int> word_count;
    add_map(0,&word_count,string("Anna"),1);
    container_find(word_count,string("Anna"));
    add_map(1,&word_count,string("Danny"),1);
    container_find(word_count,string("Danny"));
    add_map(1,&word_count,string("Danny2"),1);
}