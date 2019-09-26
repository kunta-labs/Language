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

#ifndef KUNTAC_H
#define KUNTAC_H
#include <iostream>
#include <vector>
//#include "vm.h"
#include <fstream>
#include <streambuf>
#include <regex>
//#include <pair>
#include <unordered_map>
#include <cstring>

#include <algorithm> // for copy
#include <iterator> // for ostream_iterator

#include <string>
#include <exception>
#include <map>
#include <random>
#include <cstdlib>
#include "ks.h"
#include "helpers.h"
#include "ast.h"
#include "symbols.h"
//#include "exprtk.cpp"
#include "json.hpp"
// for convenience
using json = nlohmann::json;

void SimpleLanguage(AST t){
    cout << "[simple language]" << endl;
    //auto last_element = *t.Nodes.rbegin();
    auto &last_element = *(--t.Nodes.end());
    for(auto &n : t.Nodes){
        cout << "======================[BEGIN SimpleLanguage ITERATION ===========================]" << endl;
        cout << "[" << n.self.type << "]" << endl;
        ASTNode next;
        ASTNode prev;   
        if (&n == &last_element){
            cout << "END OF NODES" << endl;
            cout << "\n\n=====[[END]"<<n.self.type<<"]"<<endl;
        }else{
            try{
               cout << "HERE 1" << endl;
               next = *(&n + 1);
               cout << "[SimpleLanguage NEXT]: " 
               << endl;
               cout << next.self.type << endl;
            }catch (exception& e){
              cout << "[ERROR] An exception occurred. Exception SimpleLanguage NEXT. " << e.what() <<  '\n';
            }
            try{
              if(&t.Nodes[0] == &n){
                cout << "[SimpleLanguage NO PREV]" << endl;
              }else{
                cout << "===1===" << endl;
                prev = *(&n - 1);
                cout << "===2===" << endl;
                cout << "[SimpleLanguage Prev]: " 
                << prev.self.type << endl;
              }
            }catch (exception& e){
              cout << "[ERROR] An exception occurred. Exception SimpleLanguage Prev. " << e.what() << '\n';
            }
            cout << "[Self] - [ " << n.self.type << " , " << n.self.value << "  ]" << endl;
            cout << "[Next] - [ " << next.self.type << " , " << next.self.value << "  ]" << endl;
            cout << "[Prev] - [ " << prev.self.type << " , " << prev.self.value << "  ]" << endl;
            cout << "======================[END SimpleLanguage ITERATION ===========================]\n\n\n" << endl;
        }    
    }
}

void Transform(){

}

json ScopesToOpcodes(vector<string> lexset){
    json j;
    json config = {
      {"type", 0},
      {"consensus", 0},
      {"genesis_block", {}},
      {"roots", {
        
      }},
      {"options", {
        {"currency", "USD"},
      }},
      {"chainscript", 
        {}
      },
    };

    ScopeTables scope_tables = CreateScopes(lexset);
    cout << "\n\n================[scope_lookup_table]===================\n\n" << endl;
    for(map<string,strings>::iterator it = scope_tables.symbol_tables.T.begin();
        it != scope_tables.symbol_tables.T.end();
        ++it) {
        //v.push_back(it->first);
        cout << "[Scope:" << it->first <<"] : "<< it->second.size() << "\n" << endl;
    }
    cout << "=======================" << endl;
    json function_holder = json::array();
    for(map<string,ScopeContent>::iterator it = scope_tables.symbol_tables.SSCT.begin();
    it != scope_tables.symbol_tables.SSCT.end();
    ++it) {
        json NativeFunction = {};
        json BlankObjTest = {};
        string scope_type_id = it->first;
        ScopeContent sc = it->second;
        string ScopeType = get<0>(sc);
        cout  << "\n" << "[ScopeType : " << scope_type_id <<" ] : "<< ScopeType << endl;
        string substring = ReplaceSubstring(scope_type_id, R"(\$)", R"( )");
        cout << "[ScopeType SubString] " << substring << endl;
        strings ParsedNodeValue = SubParse(substring);
        string scope_name = ParsedNodeValue[0];
        string scope_type = ParsedNodeValue[1];
        cout << "[scope_name " << scope_name 
        << " : [scope_type " << scope_type
        << " : substring: " << substring << endl;
        unordered_map<string, regex> ScopeNames = {
                { "OnNewBlock",        GetRegex("(OnNewBlock\\$"+scope_type+")") },
                { "OnCreate",          GetRegex("(OnCreate\\$"+scope_type+")") },
                
        };

        unordered_map<string, string> CorrectScopeParents = {
                { "OnNewBlock",        "Blockchain"  },
                { "OnCreate",          "Blockchain" },
                
        };        

        if( regex_match (scope_type_id, ScopeNames["OnNewBlock"] )){
            LookupTable lut = get<1>(sc);
            cout << "Scope OnNewblock : " << scope_type_id << endl;
            cout << "[ONNEWBLOCK$]" << endl;
            cout << "[LUT] : " << scope_type << endl;
            auto found_parent = scope_tables.symbol_tables.SSCT.find(scope_type+"$"+scope_type); //scope_type+"\\$"+scope_type
            string parent_type = get<0>(found_parent->second);
            cout << "parent type: " << parent_type << endl;
            if( parent_type == CorrectScopeParents[scope_name] ){
                try{ 
                    cout << "CorrectScopeParents[scope_name] : "
                    << scope_name  << " : "
                    << CorrectScopeParents[scope_name] << endl;
                    string scopeToFetch = "FunctionDeclaration_$"+scope_type+"$"+scope_name;
                    cout << "scopeToFetch : " << scopeToFetch << endl;
                    vector<string> scopeToRun = scope_tables
                                                .symbol_tables
                                                .T
                                                .find(scopeToFetch)->second;
                    cout << "Scope to execute on " 
                    << scope_name 
                    << " : " << scopeToRun.size() << endl;
                    AST scope_ast = CreateNodes(scopeToRun);
                    string opcodes_string = GenerateOpCodesFromAST(scope_ast);
                    cout << "\n\n[Before SimpleLanguage]\n\n" << endl;
                    cout << opcodes_string << "\n\n" << endl;
                    //SimpleLanguage(scope_ast);
                    NativeFunction = {scope_name, 
                        {"params", 
                            {
                                {"type","Block"},
                                {"name","i"},
                            },
                            {
                                {"type","Status"},
                                {"name","s"},
                            }
                        },
                        {"body", 
                            {
                                {"code", opcodes_string}, //"OP_FUNCCALL [FUNC_NAME] [PARAM] OP_RETURN [VALUE]"
                                {"script", opcodes_string},
                            }
                        },
                        {"return", 
                            {
                                {"code","[ACCOUNT]"},
                                {"script","votes"},
                            }
                        }
                    };
                    //config["chainscript"]["functions"] =  { OnNewBlockFunc };
                } catch (exception& e){
                    cout << "An exception occurred. Exception OnNewBlock ScopeContent Iteration " << endl;
                }
            }  
            else{
                throw "INCORRECT SCOPE FOR "+scope_name;
            }
        } 
        else if( regex_match (scope_type_id, ScopeNames["OnCreate"]) ){
            LookupTable lut = get<1>(sc);
            cout << "Scope OnCreate : " << scope_type_id << endl;
            cout << "[ONCREATE$]" << endl;
            cout << "[LUT] : " << scope_type << endl;
            auto found_parent = scope_tables.symbol_tables.SSCT.find(scope_type+"$"+scope_type); //scope_type+"\\$"+scope_type
            string parent_type = get<0>(found_parent->second);
            cout << "parent type: " << parent_type << endl;
            if( parent_type == CorrectScopeParents[scope_name] ){
                try{ 
                    cout << "CorrectScopeParents[scope_name] : "
                    << scope_name  << " : "
                    << CorrectScopeParents[scope_name] << endl;
                    string scopeToFetch = "FunctionDeclaration_$"+scope_type+"$"+scope_name;
                    cout << "scopeToFetch : " << scopeToFetch << endl;
                    vector<string> scopeToRun = scope_tables
                                                .symbol_tables
                                                .T
                                                .find(scopeToFetch)->second;
                    cout << "Scope to execute on " 
                    << scope_name 
                    << " : " << scopeToRun.size() << endl;
                    AST scope_ast = CreateNodes(scopeToRun);
                    string opcodes_string = GenerateOpCodesFromAST(scope_ast);
                    cout << "\n\n[Before SimpleLanguage]\n\n" << endl;
                    cout << opcodes_string << "\n\n" << endl;
                    //SimpleLanguage(scope_ast);
                    NativeFunction = {scope_name, 
                        {"params", 
                            {
                                {"type","Block"},
                                {"name","i"},
                            },
                            {
                                {"type","Status"},
                                {"name","s"},
                            }
                        },
                        {"body", 
                            {
                                {"code", opcodes_string}, //"OP_FUNCCALL [FUNC_NAME] [PARAM] OP_RETURN [VALUE]"
                                {"script", opcodes_string},
                            }
                        },
                        {"return", 
                            {
                                {"code","[ACCOUNT]"},
                                {"script","votes"},
                            }
                        }
                    };
                    //config["chainscript"]["functions"] =  { OnNewBlockFunc };
                } catch (exception& e){
                    cout << "An exception occurred. Exception OnNewBlock ScopeContent Iteration " << endl;
                }
            } 
            else{
                throw "INCORRECT SCOPE FOR "+scope_name;
            }
        }else{
            cout << "ELSE $ " << scope_type_id << endl;
            for(map<string,string>::iterator s = get<1>(sc).begin();
            s != get<1>(sc).end();
            ++s) {
                cout << "ScopeContent TEST ELSE: " << scope_type_id << endl;
            }
            //scope_lookup_table.symbol_table.STT.find( scope_type_id )->second 
        } 
        if(NativeFunction != BlankObjTest){
            function_holder.push_back(NativeFunction);
        }
    }
    json aspect_1 = {
        {"description", "holding the total number of votes at a time"},
        {"aspect", "votes"},
        {"default_value", 1200},
    };
    json aspect_2 =  {
        {"description", "votes can only happen if 1"},
        {"aspect", "able_to_vote"},
        {"default_value", 1},
    };
    json vote_root = {
        {"name", "vote"},
        {"access", 0},
        {"code", "[ACCOUNT] [INTEGER] OP_ADD OP_STORE OP_CONST [HASHPUBK] OP_CONST [PUBKHASH] OP_CONST_EQUAL_DROP [ACCOUNT] OP_CRITICAL_VERIFY"},
        {"return", "votes"},
        {
            "aspects", {}
        }
    };
    json verdict_root = {
        {"name", "verdict"},
        {"access", 0},
        {"code", "[EXTERN_STATE] [PARAMETER] OP_ATLEAST_ZERO OP_VERIFY"},
        {"return", "#BLANK#"},
        {
            "aspects", {
                {
                    {"description", "refer to extern state, grab v, sum"},
                    {"aspect", "end_date"},
                    {"default_value", 1826387363},
                }
            }
        }
    };
    config["roots"] =  { vote_root, verdict_root };
    config["chainscript"]["functions"] = function_holder;
    cout << config.dump(2) << endl;
    return config;
}
#endif


