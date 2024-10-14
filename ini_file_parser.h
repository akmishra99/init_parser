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
