/*

AUthor:- Alok Kumar Mishra
e-mail :- akmishra_99@yahoo.com
Sunday , January 8, 2023

Revision 1.0 

*/

#include "ini_file_parser.h"

#if 0 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<map>
#include<algorithm>
#include <unistd.h>

using namespace std;

enum Status
{
    OK,
    ERROR,
    NEXT_ITEM
};
using Type_DataIndexMap = std::map<std::string, std::string>;
using Type_DataItem = map <std::string , map<std::string,std::string >>;
using Type_DataContainer = std::vector< Type_DataIndexMap > ;
using Type_ParseValues = std::pair<std::string, std::string>;
extern vector < ini_data> data;
// enum class Parse_DataType 
enum Parse_DataType
{
    PDATA_NONE,
    PDATA_COMMENT,
    PDATA_MULTI_LINE_START_COMMENT,
    PDATA_MULTI_LINE_END_COMMENT,
    PDATA_SECTION,
    PDATA_KEYVALUE,
    PDATA_UNKNOWN
};
enum class MEMORY_DISPLAY_UNIT 
{
      BYTES,
      KB,
      MB,
      GB,
      TB,
      NONE


};
typedef struct unit_and_size {
    enum MEMORY_DISPLAY_UNIT memory_unit = MEMORY_DISPLAY_UNIT::NONE;
    double size = -1.0;



} t_unit_and_size;
enum MEMORY_DISPLAY_UNIT memory_unit = MEMORY_DISPLAY_UNIT::BYTES;
Type_DataIndexMap dataIndexMap;

extern  void trim(string &str);
int toInt(std::string str)
{
    int num;
    std::stringstream ss(str);
    ss >> num;
    return num;
}
class ini_data {
public:
     
    Type_DataItem record;
    ini_data(Type_DataItem _record)
    {
        for(const auto & e : _record ){
            for (const auto &f : e.second) {
                map<string,string> g;
                g.insert( make_pair(f.first,f.second));

                record.insert(make_pair(e.first,g));
            }
        }

    }
    string retrieve_key() {
      
        for(const auto & e : record ) {
            if (!e.first.empty()) {

            
            return e.first;
            }
            else 
                return "";
        }

        return "";
    }
    t_unit_and_size convert_number(t_unit_and_size &number_to_convert) {
       if (memory_unit != number_to_convert.memory_unit ) {
           if (memory_unit ==  MEMORY_DISPLAY_UNIT::BYTES) {
               if ( number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::GB) {
                  number_to_convert.size = number_to_convert.size * 1024 * 1024 * 1024;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::BYTES;
                  return number_to_convert;
                }
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::MB) {
                  number_to_convert.size = number_to_convert.size * 1024 * 1024 ;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::BYTES;
                  return number_to_convert;                   

                }
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::KB) {
                  number_to_convert.size = number_to_convert.size * 1024 ;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::BYTES;
                  return number_to_convert;                   

                }
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::TB) {
                  number_to_convert.size = number_to_convert.size * 1024 * 1024 * 1024 * 1024;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::BYTES;
                  return number_to_convert;                   

                }                              
           }
           else if (memory_unit ==  MEMORY_DISPLAY_UNIT::KB) {
               if ( number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::GB) {
                  number_to_convert.size = number_to_convert.size * 1024 * 1024 ;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::KB;
                  return number_to_convert;
                }
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::MB) {
                  number_to_convert.size = number_to_convert.size * 1024 ;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::KB;
                  return number_to_convert;                   

                }
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::BYTES) {
                  number_to_convert.size = number_to_convert.size / 1024 ;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::KB;
                  return number_to_convert;                   

                }    
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::TB) {
                  number_to_convert.size = number_to_convert.size * 1024 * 1024 * 1024;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::KB;
                  return number_to_convert;                   

                }    
            }
            else if (memory_unit ==  MEMORY_DISPLAY_UNIT::MB) {
               if ( number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::GB) {
                  number_to_convert.size = number_to_convert.size * 1024  ;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::MB;
                  return number_to_convert;
                }
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::TB) {
                  number_to_convert.size = number_to_convert.size * 1024 * 1024 ;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::MB;
                  return number_to_convert;                   

                }
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::BYTES) {
                  number_to_convert.size = ( (number_to_convert.size / 1024) / 1024 );
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::MB;
                  return number_to_convert;                   

                }    
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::KB) {
                  number_to_convert.size = ( number_to_convert.size / 1024) ;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::MB;
                  return number_to_convert;                   

                } 



            }
            else if (memory_unit ==  MEMORY_DISPLAY_UNIT::GB) {
               if ( number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::TB) {
                  number_to_convert.size = number_to_convert.size * 1024  ;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::GB;
                  return number_to_convert;
                }
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::MB) {
                  number_to_convert.size = number_to_convert.size / 1024  ;
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::GB;
                  return number_to_convert;                   

                }
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::BYTES) {
                  number_to_convert.size = ( ((number_to_convert.size / 1024) / 1024 ) /1024);
                  number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::GB;
                  return number_to_convert;                   

                }    
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::KB) {
                  number_to_convert.size = (( number_to_convert.size / 1024) / 1024);
                  number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::GB;
                  return number_to_convert;                   

                } 



            }
            else if (memory_unit ==  MEMORY_DISPLAY_UNIT::TB) {
                if ( number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::GB) {
                    number_to_convert.size = number_to_convert.size / 1024  ;
                    number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::TB;
                    return number_to_convert;
                }
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::MB) {
                    number_to_convert.size = ((number_to_convert.size / 1024 ) / 1024) ;
                    number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::TB;
                    return number_to_convert;                   

                }
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::BYTES) {
                    number_to_convert.size = ( ((number_to_convert.size / 1024) / 1024 ) /1024) / 1024;
                    number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::TB;
                    return number_to_convert;                   

                }    
                else if (number_to_convert.memory_unit == MEMORY_DISPLAY_UNIT::KB) {
                    number_to_convert.size = (( number_to_convert.size / 1024) / 1024) / 1024;
                    number_to_convert.memory_unit = MEMORY_DISPLAY_UNIT::TB;
                    return number_to_convert;                   

                }  



            }         
       }  
       
       return number_to_convert;


    }
 

    t_unit_and_size  &extract_number(const string &given_string,t_unit_and_size &a_number)
    {
        
        auto equalsAt = given_string.find_first_of('=');
        auto bytesAt = given_string.find("BB");
        if (bytesAt == string::npos) {
            
            bytesAt = given_string.find("KB");
            if (bytesAt == string::npos) {
                bytesAt = given_string.find("MB");
                if (bytesAt == string::npos) {
                    bytesAt = given_string.find("GB");
                    if (bytesAt == string::npos) {
                        bytesAt = given_string.find("TB");
                        if (bytesAt == string::npos) {
                           a_number.memory_unit = MEMORY_DISPLAY_UNIT::NONE;
                           a_number.size = -1;
                           return a_number;
                        }
                        else {
                            a_number.memory_unit = MEMORY_DISPLAY_UNIT::TB;

                        }
                        
                    }
                    else {
                        a_number.memory_unit = MEMORY_DISPLAY_UNIT::GB;
                    }
                }
                else {
                    a_number.memory_unit = MEMORY_DISPLAY_UNIT::MB;
                }       
                

            }
            else {
                a_number.memory_unit = MEMORY_DISPLAY_UNIT::KB;
            }
        }
        else {
             a_number.memory_unit = MEMORY_DISPLAY_UNIT::BYTES;   
        }

        
        
        if ( equalsAt == string::npos) {
            if (bytesAt != string::npos) { 
                // auto value = given_string.substr(equalsAt + 1,bytesAt -1);
    
                // auto value = given_string.substr(equalsAt + 1,bytesAt -1);
                auto number_in_string = given_string.substr(0,bytesAt);
                if (!number_in_string.empty() ) {
                    trim(number_in_string);
                    a_number.size  = (double) toInt(number_in_string);

                    //a_number = convert_number(a_number)
                    convert_number(a_number);
                }
                // trim(value);
                // a_number.size  = toInt(value);
                
                return a_number;
            }
        
        }
        a_number.memory_unit = MEMORY_DISPLAY_UNIT::NONE;
        a_number.size = -1;
        return a_number;  

    }

    void print() 
    {
        t_unit_and_size a_number ; 
        for(const auto & e : record ){

            for (const auto &f : e.second) {
                cout << e.first << endl;
                cout << f.first << " = " ;
                extract_number(f.second,a_number);
                if ( a_number.memory_unit == MEMORY_DISPLAY_UNIT::NONE) {
                    cout << f.second  << endl;

                }
                else {
                    if (a_number.memory_unit == MEMORY_DISPLAY_UNIT::BYTES)

                        cout << a_number.size << " " << "Bytes " << endl; 
                    else if (a_number.memory_unit == MEMORY_DISPLAY_UNIT::KB)

                        cout << a_number.size << " " << "Kilo Bytes (KB)" << endl; 
                    else if (a_number.memory_unit == MEMORY_DISPLAY_UNIT::MB)

                        cout << a_number.size << " " << "Mega Bytes (MB)" << endl; 
                    else if (a_number.memory_unit == MEMORY_DISPLAY_UNIT::GB)

                        cout << a_number.size << " " << "Giga Bytes (GB)" << endl; 
                    else if (a_number.memory_unit == MEMORY_DISPLAY_UNIT::TB)

                        cout << a_number.size << " " << "Teraa Bytes (TB)" << endl; 
                    
                }
         
            }
        }       


    }
};
#endif 
vector < ini_data> data1;
ini_data *p_ini_data = nullptr;

inline void replace(std::string& str, std::string const& a, std::string const& b)
{
    if (!a.empty())
    {
        std::size_t pos = 0;
        while ((pos = str.find(a, pos)) != std::string::npos)
        {
            str.replace(pos, a.size(), b);
            pos += b.size();
        }
    }
}

inline void trim(string &str)
{
    const char* const whitespaceDelimiters = " \t\n\r\f\v";

    str.erase(str.find_last_not_of(whitespaceDelimiters) + 1);
    str.erase(0, str.find_first_not_of(whitespaceDelimiters));
}
string line_before_muli_line_commentAt = "";
string line_after_multi_line_commentAt = "";
bool multi_line_comment_found = false;
inline Parse_DataType parseLine(std::string line, Type_ParseValues& parseData)
{   size_t multi_line_commentAt = string::npos;
    size_t multi_line_end_commentAt = string::npos;
    parseData.first.clear();
    parseData.second.clear();
    trim(line);
 
    multi_line_commentAt = line.find("/*");
    multi_line_end_commentAt = line.find("*/");
    if (multi_line_commentAt != string::npos) {
        line_before_muli_line_commentAt = line.substr(0,multi_line_commentAt -1);
        if ( multi_line_end_commentAt != string::npos) {
            line_after_multi_line_commentAt = line.substr(multi_line_end_commentAt +2 );
            if ( line_after_multi_line_commentAt.empty()) {
                
                line = line_before_muli_line_commentAt;

            }
            else {
                line = line_before_muli_line_commentAt + line_after_multi_line_commentAt;
            }
        }
        else {
             multi_line_comment_found = true;
             return Parse_DataType::PDATA_MULTI_LINE_START_COMMENT;
        }
        

    }
    else if (( multi_line_end_commentAt != string::npos) && ( multi_line_comment_found)) {

        line_after_multi_line_commentAt = line.substr(multi_line_end_commentAt +2 );
        line = line_before_muli_line_commentAt + line_after_multi_line_commentAt;
        multi_line_comment_found =false;
        line_after_multi_line_commentAt = "";
        line = line_before_muli_line_commentAt = "";

    }
    else if (( multi_line_end_commentAt == string::npos) && ( multi_line_comment_found)) {

        return Parse_DataType::PDATA_MULTI_LINE_END_COMMENT;

    }   
    if (line.empty())
    {
        return Parse_DataType::PDATA_NONE;
    }
    char firstCharacter = line[0];
    if (firstCharacter == ';')
    {
        return Parse_DataType::PDATA_COMMENT;
    }
    if (firstCharacter == '[')
    {
        auto commentAt = line.find_first_of(';');
        if (commentAt != std::string::npos)
        {
            line = line.substr(0, commentAt);
        }
        auto closingBracketAt = line.find_last_of(']');
        if (closingBracketAt != std::string::npos)
        {
            auto section = line.substr(1, closingBracketAt - 1);
            trim(section);
            parseData.first = section;
            return Parse_DataType::PDATA_SECTION;
        }
    }
    auto lineNorm = line;
    replace(lineNorm, "\\=", "  ");
    auto equalsAt = lineNorm.find_first_of('=');
    if (equalsAt != std::string::npos)
    {
        auto key = line.substr(0, equalsAt);
        trim(key);
        replace(key, "\\=", "=");
        auto value = line.substr(equalsAt + 1);
        trim(value);
        parseData.first = key;
        parseData.second = value;
        return Parse_DataType::PDATA_KEYVALUE;
    }
    return Parse_DataType::PDATA_UNKNOWN;
}

struct less_than_key
{
    inline bool operator() (const ini_data& first, const ini_data& second)
    {   
        string record_first ;
        string record_second ;

            Type_DataItem  temp = first.record;
            for(const auto & e : temp ){
                record_first = e.first;
            }
 
            temp = second.record;
            for(const auto & e : temp ){
                record_second = e.first;
            }
      
        return (record_first < record_second);
    }
};

void display_data()
{
   for (auto &temp2 :data1  ) {
        Type_DataItem  temp = temp2.record;
        for(const auto & e : temp ){
            for (const auto &f : e.second) {
                map<string,string> g;
                g = e.second;
                for (const auto &h :g ) {
                    cout << "key = " << e.first << " secondary key = " << h.first << " value = " << h.second << endl;
                } 
            }
        }
    }  
}
void display_command_output_la ()
{
   for (auto &temp2 :data1  ) {
        Type_DataItem  temp = temp2.record;
        for(const auto & e : temp ){
            for (const auto &f : e.second) {
                map<string,string> g;
                g = e.second;
                for (const auto &h :g ) {
                    cout << " " << e.first << " " << h.first << " " << h.second << endl;
                } 
            }
        }
    }   



}
void display_single(ini_data *given_a_ini_data)
{
    ini_data a_ini_data(*given_a_ini_data);
    cout << "******* here it is ********" << endl;
    a_ini_data.print();
    cout << "*************************" << endl;

}

ini_data *binary_search_mine(const string &given_key)
{
    int index = -1, beggining = 0,end = data1.size();
    int number_of_elements_serached = 0;
    bool found = false;
    if (end == 0 )
        return p_ini_data;
    index = (beggining + end ) / 2;
    
        while(!found) {

        
            if (data1.at(index).retrieve_key() == given_key  ) {
                found = true;
                return &(data1.at(index));
            }
            else if ( data1.at(index).retrieve_key()  < given_key ) {

                beggining = index;
                index = (beggining + end )/ 2;
                number_of_elements_serached++;

            }
            else if ( data1.at(index).retrieve_key()  > given_key ) {

                end = index ;
                index = (beggining  + end ) /2 ;
                number_of_elements_serached++;

            }
            if ( number_of_elements_serached >= data1.size())
                break;

        }

    return p_ini_data;

}
bool  display_all_values_for_one_key(string &given_key)
{
    
    auto search_result = binary_search_mine(given_key);
    if (search_result) {
        for (auto &item1 : data1) {
            auto item = item1.record;
            if ( item1.retrieve_key() == given_key) { 
                display_single(&item1);
                
            }    
        }
        return true;

    }
    
    return false;
    
}
void display_usuage() 
{
        cout << "**********************************************" << endl;
        cout << "**********************************************" << endl;
        cout << "**********************************************" << endl;
        cout << endl << endl << endl;
        cout << "*******      command processr *****************" << endl;
        cout << "*******      available commands are ***********" << endl;
        cout << endl << endl << endl;
        cout << "**********************************************" << endl;
        cout << "**********************************************" << endl;
        cout << "**********************************************" << endl;      
        cout << "l section_name to list a section name " <<     endl;
        cout << "ll section_name to list all entries in a section " << endl;
        cout << "'la l' list all the entries in all sections as key/value entries " << endl;
        cout << "C followed by BB or KB or MB or GB or TB to change display Unit" << endl;
        cout << "BB to change display units to Bytes and KB to Kilo bytes, MB to Mega bytes, GB to Giga Bytes ans TB to terabytes " << endl;
        cout << "Help to display this message " << endl;
        cout << "q to exit" << endl;
        cout << "**********************************************" << endl;
        cout << "**********************************************" << endl;
        cout << "**********************************************" << endl;
        cout << endl << endl << endl;


        cout << endl << endl << endl;


}
int main(int argc, char **argv, char **envp)
{
    stringstream ss;
    string line;

    if (argc != 2)
    {
        cerr << "Usage " << argv[0] << " "
             << "filename" << endl;
        exit(1);
    }
    ifstream file(argv[1], ios::in);
    if (!file)
    {
        cerr << "unable to read file = " << argv[1] << endl;
        exit(2);
    }

    ss << file.rdbuf();
    file.close();
    Type_ParseValues parseData;
    bool inSection = false;
    string section;
    int position = 0 ; 
    while (getline(ss, line))
    {   
#ifdef VERBOSE
        cout << "line = " << line << endl;
#endif
        trim(line);
 
        auto parseResult = parseLine(line, parseData);
        if (parseResult == Parse_DataType::PDATA_SECTION)
        {
            inSection = true;
            // data[section = parseData.first];
            section = parseData.first;
        }
        else if (inSection && parseResult == Parse_DataType::PDATA_KEYVALUE)
        {
            auto const& key = parseData.first;
            auto const& value = parseData.second;
            
            // data[section][key] = value;
            Type_DataItem temp;
            Type_DataIndexMap temp3;
            temp3.insert(make_pair(key,value));
            temp.insert(make_pair(section,temp3));
            ini_data a_ini_data(temp);
            data1.push_back(a_ini_data);
        }
        if (!line.empty() && (line[0] != ';' ) && parseResult == Parse_DataType::PDATA_UNKNOWN)
        {
            if (parseResult == Parse_DataType::PDATA_KEYVALUE && !inSection)
            {
                continue;
            }
            if (data1.empty()) {
                cout << " line = " << line << endl;
                continue;
            }
            ini_data temp4 ( data1.back());
            Type_DataItem  temp5 = temp4.record;
            for( auto & e : temp5 ){
                for ( auto &f : e.second) {

                    f.second += line;
 
                }
  
                  
            }
            data1.pop_back();
            data1.push_back(ini_data(temp5));
        }
    }
 
    std::sort(data1.begin(), data1.end(), less_than_key());
#ifdef VERBOSE    
    display_data();
#endif 
    string command,sub_command;
    while(1) {
        
        display_usuage();
        cout << "enter command ->";
        cin >>  command ;
        if ((command == "help") || (command == "Help") || (command == "h")) {

            display_usuage();


        }
        else if ( command == "q") {

            exit(0);
        }
        else 
            cin >> sub_command;
        if (!command.empty()) {
            if ((command == "la") && (sub_command == "l")){
                
                display_command_output_la();

            }
            else if (( command == "l") && ( !sub_command.empty())) {

                string section_name_to_find = sub_command;
                auto search_result = binary_search_mine(sub_command);
                if (search_result) {
                    
                    display_single(search_result);

                }
                else {
                    cerr << "section = " << sub_command << " not found " << endl;
                     display_usuage();

                }
            }
            else if (( command == "ll") && (!sub_command.empty())) {

                if (!display_all_values_for_one_key(sub_command)) {
                    cerr << " section name = " << sub_command  <<  " not found " << endl;
                    display_usuage();
                }
            }
            else if (( command == "C") && (!sub_command.empty())) {
                if (sub_command == "BB" ) {
                    cout << "changing display unit to Bytes " << endl;
                    memory_unit = MEMORY_DISPLAY_UNIT::BYTES;
                }
                else if (sub_command == "KB") {

                    cout << "changing display unit to KiloBytes (KB) " << endl;
                    memory_unit = MEMORY_DISPLAY_UNIT::KB;
                }
                else if (sub_command == "MB") {

                    cout << "changing display unit to MegaBytes (MB) " << endl;
                    memory_unit = MEMORY_DISPLAY_UNIT::MB;
                }
                else if (sub_command == "GB") {

                    cout << "changing display unit to GigaBytes (GB) " << endl;
                    memory_unit = MEMORY_DISPLAY_UNIT::GB;
                }
                else if (sub_command == "TB") {

                    cout << "changing display unit to TeraBytes (TB) " << endl;
                    memory_unit = MEMORY_DISPLAY_UNIT::TB;
                }
                else {
                    cout << " in correct memory unit" << endl;
                    display_usuage();

                }

            }
            else {

                cerr << " " << "command = " << command << " and " << " sub_command = " << sub_command << " not found " << endl;
                display_usuage();
            }
        }
        else {

            cerr << " unknown command = " << command << endl;
            display_usuage();

        }

    }
    return 0;
}
