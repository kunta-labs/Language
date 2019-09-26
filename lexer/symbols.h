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

#ifndef SYMBOLS_H
#define SYMBOLS_H
#include <string>
#include <regex>
#include <tuple>
class CodeBlock{
    private:
        strings block;
    public:
        CodeBlock(strings c){
            this->setBlock(c);
        }
        void setBlock(strings c){
            this->block = c;
        }
        strings getBlock(){
            return this->block;
        }
};

typedef map< string, vector<string> > Table; 
typedef map< string, string > LookupTable; 
typedef tuple<string, LookupTable> ScopeContent; 
typedef map< string, ScopeContent > ScopeSymbolContentTable;

class SymbolTables{
    public:
        SymbolTables(){

        }
        Table T;
        ScopeSymbolContentTable SSCT;
};

class ScopeTables{
    public:
    	vector<string> lexsubset;
    	SymbolTables symbol_tables;
        ScopeTables(){

        }
        void addToSymbolTable(string id, vector<string> proc){
        	pair<string, vector<string>> P = make_pair(id,proc);
        	this->symbol_tables.T.insert( P );
        }
        void addToScopeSymbolContentTable(string id, string type){
            LookupTable table;
            map<string,ScopeContent>::iterator ssct_f = this->symbol_tables.SSCT.find(id);
            ScopeContent sc;
            if(ssct_f != this->symbol_tables.SSCT.end())
            {
               sc = ssct_f->second;
               table = get<1>(ssct_f->second);
            }
            table.insert( make_pair(id,type) );
            sc = make_tuple(type,table);
            pair<string, ScopeContent> P = make_pair(id,sc);
            this->symbol_tables.SSCT.insert( P );
        }
};

strings CreateLexSubset(strings lexsubset, string breaker, 
                        string depthIndicator, int offset){
    int breaker_count = -1;
    int ending_offset = 0;
    vector<string>::const_iterator first = lexsubset.begin() + offset;
    vector<string>::const_iterator last = lexsubset.end();
    vector<string> sv(first, last);
    vector<string> subvec;
    for (auto &lss : sv){
        if( (regex_match(lss, GetRegex(R"(\})"))) & (breaker_count == 0) ){
            cout << "CreateLexSubset 1: " << lss << " : " << breaker_count <<  endl;
            subvec.push_back(lss);
            break;
        }
        else if( (regex_match(lss, GetRegex(R"(\})"))) & (breaker_count > 0) ){
            cout << "CreateLexSubset 2: " << lss << " : " << breaker_count << endl;
            breaker_count = breaker_count - 1;
            subvec.push_back(lss);
        }
        else if( regex_match (lss, GetRegex( R"(\{)" ) ) ){
            cout << "CreateLexSubset 3: " << lss << " : " << breaker_count << endl;
            breaker_count = breaker_count + 1;
            subvec.push_back(lss);
        }
        else{
            cout << "CreateLexSubset 4: " << lss << " : " << breaker_count << endl;
            subvec.push_back(lss);
        }
    }
    return subvec;
}

ScopeTables CreateScopes(strings lexset){
    unordered_map<string, regex> ScopeParents = {
                { "Blockchain",         GetRegex("Blockchain") },
                { "Mechanism",          GetRegex("Mechanism") },
                { "Root",               GetRegex("Root") },
                { "Aspect",             GetRegex("Aspect") },
                { "FunctionDeclaration",GetRegex("(func)") }
            };
    ScopeTables scope_lookup_table;
    auto &last_element = *(--lexset.end());
    string default_parent_id = "NOPARENT";
    string parent_id = default_parent_id;
    int offset = 0;
    for(auto &i : lexset){
      offset = offset+1;
      cout << "[CreateScopes]: " << i << endl;
      string prev;
      string next;
      if (&i == &last_element){
        cout << "END OF LEXSET" << endl;
        cout << "\n\n=====[[END]" << i << "]" <<endl;
      }else{
        try{
            next = *(&i + 1);
        } catch (exception& e){
            cout << "An exception occurred. Exception CreateScopes NEXT. " << endl;
        }
        try{        
            if(&lexset[0] == &i){
                cout << "[CreateScopes NO PREV]" << endl;
            }else{
                prev = *(&i - 1);
            }
        } catch (exception& e){
            cout << "An exception occurred. Exception CreateScopes PREV. " << endl;
        }
        string VariableName_prefix;
        string parse_separator = "_$"+parent_id+"$";
        if ( regex_match (next, ScopeParents["Mechanism"]) ){ //MECHANISM
            cout << "[CREATESCOPE_MECHANISM]" << endl;
            VariableName_prefix = "Mechanism"+parse_separator;
            string tmpStr = *(&i + 2);
            tmpStr = ReplaceSubstring(tmpStr, R"(\()", R"( )");
            cout << "[Equal split] " << tmpStr << endl;
            tmpStr = ReplaceSubstring(tmpStr, R"( , )", R"( )");
            tmpStr = ReplaceSubstring(tmpStr, R"(\))", R"( )");
            cout << "[S] " << tmpStr << endl;
            strings ParsedNodeValue;
            ParsedNodeValue = SubParse(tmpStr);
            parent_id = ParsedNodeValue[0]; //assign this new scope id to the new parent
            string VariableName = VariableName_prefix+ParsedNodeValue[0];
            strings subvec = CreateLexSubset(lexset, "}", "{", offset);
            //scope_lookup_table.V.InsertNewVariable( make_pair(VariableName, "subvec") );
            scope_lookup_table.addToSymbolTable(VariableName, subvec);
            scope_lookup_table.addToScopeSymbolContentTable(ParsedNodeValue[0]+"$"+parent_id, "Mechanism");
        }else if ( regex_match (next, ScopeParents["Blockchain"]) ){ //Blockchain
            cout << "[CREATESCOPE_Blockchain]" << endl;
            parse_separator = "_$"+default_parent_id+"$";
            VariableName_prefix = "Blockchain"+parse_separator;
            string tmpStr = *(&i + 2);
            tmpStr = ReplaceSubstring(tmpStr, R"(\()", R"( )");
            cout << "[Equal split] " << tmpStr << endl;
            tmpStr = ReplaceSubstring(tmpStr, R"( , )", R"( )");
            tmpStr = ReplaceSubstring(tmpStr, R"(\))", R"( )");
            cout << "[S] " << tmpStr << endl;
            strings ParsedNodeValue;
            ParsedNodeValue = SubParse(tmpStr);
            parent_id = ParsedNodeValue[0]; //assign this new scope id to the new parent
            string VariableName = VariableName_prefix+ParsedNodeValue[0];
            strings subvec = CreateLexSubset(lexset, "}", "{", offset);
            //scope_lookup_table.V.InsertNewVariable( make_pair(VariableName, "subvec") );
            scope_lookup_table.addToSymbolTable(VariableName, subvec);
            scope_lookup_table.addToScopeSymbolContentTable(ParsedNodeValue[0]+"$"+parent_id, "Blockchain");
        }else if ( regex_match (next, ScopeParents["FunctionDeclaration"]) ){ //Blockchain
            cout << "[CREATESCOPE_FunctionDeclaration]" << endl;
            VariableName_prefix = "FunctionDeclaration"+parse_separator;
            string tmpStr = *(&i + 2);
            tmpStr = ReplaceSubstring(tmpStr, R"(\()", R"( )");
            cout << "[Equal split] " << tmpStr << endl;
            tmpStr = ReplaceSubstring(tmpStr, R"( , )", R"( )");
            tmpStr = ReplaceSubstring(tmpStr, R"(\))", R"( )");
            cout << "[S] " << tmpStr << endl;
            strings ParsedNodeValue;
            ParsedNodeValue = SubParse(tmpStr);
            //parent_id = ParsedNodeValue[0]; //NO NEED BECAUSE THIS FUNCTION CANNOT BE A PARENT SCOPE
            string VariableName = VariableName_prefix+ParsedNodeValue[0];
            strings subvec = CreateLexSubset(lexset, "}", "{", offset);
            //scope_lookup_table.V.InsertNewVariable( make_pair(VariableName, "subvec") );
            scope_lookup_table.addToSymbolTable(VariableName, subvec);
            scope_lookup_table.addToScopeSymbolContentTable(ParsedNodeValue[0]+"$"+parent_id, "FunctionDeclaration");
        }else if ( regex_match (next, ScopeParents["Root"]) ){ //Blockchain
            cout << "[CREATESCOPE_Root]" << endl;
            parse_separator = "_$"+default_parent_id+"$";
            VariableName_prefix = "Root"+parse_separator;
            string tmpStr = *(&i + 2);
            tmpStr = ReplaceSubstring(tmpStr, R"(\()", R"( )");
            cout << "[Equal split] " << tmpStr << endl;
            tmpStr = ReplaceSubstring(tmpStr, R"( , )", R"( )");
            tmpStr = ReplaceSubstring(tmpStr, R"(\))", R"( )");
            cout << "[S] " << tmpStr << endl;
            strings ParsedNodeValue;
            ParsedNodeValue = SubParse(tmpStr);
            parent_id = ParsedNodeValue[0]; //ASSIGN TO BE PARENTED
            string VariableName = VariableName_prefix+ParsedNodeValue[0];
            strings subvec = CreateLexSubset(lexset, "}", "{", offset);
            //scope_lookup_table.V.InsertNewVariable( make_pair(VariableName, "subvec") );
            scope_lookup_table.addToSymbolTable(VariableName, subvec);
            scope_lookup_table.addToScopeSymbolContentTable(ParsedNodeValue[0]+"$"+parent_id, "Root");
        }else if ( regex_match (next, ScopeParents["Aspect"]) ){ //Blockchain
            cout << "[CREATESCOPE_Aspect" << endl;
            //TODO: RESET PARSE SEPARATOR BECAUSE A CHAIN CANNOT HAVE A PARENT
            parse_separator = "_$"+default_parent_id+"$";
            VariableName_prefix = "Aspect"+parse_separator;
            string tmpStr = *(&i + 2);
            tmpStr = ReplaceSubstring(tmpStr, R"(\()", R"( )");
            cout << "[Equal split] " << tmpStr << endl;
            tmpStr = ReplaceSubstring(tmpStr, R"( , )", R"( )");
            tmpStr = ReplaceSubstring(tmpStr, R"(\))", R"( )");
            cout << "[S] " << tmpStr << endl;
            strings ParsedNodeValue;
            ParsedNodeValue = SubParse(tmpStr);
            parent_id = ParsedNodeValue[0]; //ASSIGN TO BE PARENTED
            string VariableName = VariableName_prefix+ParsedNodeValue[0];
            strings subvec = CreateLexSubset(lexset, "}", "{", offset);
            //scope_lookup_table.V.InsertNewVariable( make_pair(VariableName, "subvec") );
            scope_lookup_table.addToSymbolTable(VariableName, subvec);
            scope_lookup_table.addToScopeSymbolContentTable(ParsedNodeValue[0]+"$"+parent_id, "Aspect");
        }
      }
    } 
    Variable scopeV; 
    cout << "DONE CreateScopes" << endl;    
    return scope_lookup_table;
}

string GenerateOpCodesFromAST(AST tree){
    cout << "[Inside GenerateOpCodesFromAST]" << endl;
    string string_procedure = "";
    for(auto n = tree.Nodes.begin(); 
        n != tree.Nodes.end(); 
        n++)
    {
        string node_type = n->self.type;
        string node_value = n->self.value;
        string suffix = " ";
        if(n == tree.Nodes.begin())
        {
            cout << "DO SOMETHING" << endl;
            if(node_value != ""){
                string_procedure = string_procedure + node_value + suffix;
            }
        }
        else if(next(n) == tree.Nodes.end())
        {
            cout << "DO SOMETHING ELSE" << node_value << ":" << node_type << endl;
            string_procedure = string_procedure + node_value + "OP_END";
        }
        else{
            if(node_value != ""){
                string_procedure = string_procedure + node_value + suffix;
            }
        }
        cout << "NODE CONTENT" << endl;
        cout << "[ " << node_type 
        << " , " << node_value << "  ]" << endl;
        cout << "[CHILDREN]" << endl;
        for(auto c : n->children){
            cout << "[CHILD][ " << c.self.type << " , " << c.self.value << "]" << endl;
        }
        cout << "[END CHILDREN]" << endl;
    }
    return string_procedure;
}

#endif