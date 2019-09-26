/*
Copyright 2017-Present The Kunta Protocol Authors
This file is part of the Kunta Protocol library.
The Kunta Protocol is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
The Kunta Protocol is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public License
along with the Kunta Protocol library. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HELPERS_H
#define HELPERS_H
#include <string>
#include <regex>
#include "ks.h"

string ParseUntilStop(string section, string stop){
    vector<char> result_v;
    for(char i : section){
        char c_stop = *( stop.c_str() );
        if( i == c_stop ){
           cout << "[ParseUntilStop][Stop Reached] '" << stop << "'" << endl;
        }else{
            result_v.push_back(i);
        }
        //malloc(c_stop);
    }
    string result(result_v.begin(),result_v.end());
    return result;
}

strings SubParse(string s){
    strings p = KuntaScript::Parse(s);
    return p;
}

string ReplaceSubstring(string str, string s1, string s2){
    str = regex_replace(str, regex(s1), s2);
    return str;
}

bool in_array(const string &value, const vector<string> &array){
    return find(array.begin(), array.end(), value) != array.end();
}

regex GetRegex(string s){
    regex r(s);
    return r;
}

#endif



