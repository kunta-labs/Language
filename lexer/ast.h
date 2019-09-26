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

#ifndef AST_H
#define AST_H
#include <string>
#include <vector>
#include <iostream>
#include <regex>
class Node {
	public:
		string type;
		string value;
		Node(string t, string v){
			cout << "[Node Created] = [" << t << "]" << endl;
			this->type = t;
			this->value = v;
		}
		Node(){
			cout << "Empty node created" << endl;
		}
		void SetType(string t){
			this->type = t; 
		}
		void SetValue(string v){
			this->value = v; 
		}
};

class ASTNode {
	public:
		Node self;
		Node parent;
		int ASTVectorID = -1;
		int ParentASTVectorID = -1;
		vector<ASTNode> children;
		ASTNode(Node s, vector<ASTNode> c, Node p){
			cout << "[ASTNode Created] = [" << s.type << "]" << endl;
			this->self = s;
			this->children = c;
			this->parent = p;
		}
		ASTNode(Node s, vector<ASTNode> c){
			cout << "[ASTNode [NO PARENT] Created] = [" << s.type << "]" << endl;
			this->self = s;
			this->children = c;
		}
		ASTNode(Node s, Node p){
			cout << "[ASTNode [NO CHILDREN] Created] = [" << s.type << "]" << endl;
			this->self = s;
			this->parent = p;
		}
		ASTNode(Node s){
			cout << "[ASTNode [NO CHILDREN, NO PARENT, JUST SELF] Created] = [" << s.type << "]" << endl;
			this->self = s;
		}
		ASTNode(){

		}
};



class AST{
	private:
	public:
		vector<ASTNode> Nodes;
		AST(){
			cout << "[AST Created]"  << endl;
		}
		void AddNode(ASTNode n){
			this->Nodes.push_back(n);
		}
};

class TraversableAST{
	public:
		AST base_tree;
		TraversableAST(AST bt){
			this->base_tree = bt;
		}
};

class Variable{
	public:
		map<string, string> memory;
		bool InsertNewVariable(pair<string, string> data){
			cout << "Inserted New Variable["<< data.first <<"] : " << data.second << endl;
			bool result;
			try{ 
			   memory.insert(data);
			   result = true;  
			}catch (exception& e){
			  cout << "[ERROR] An exception occurred. Exception SimpleLanguage NEXT. " << e.what() <<  '\n';
			  result = false;
			}
			return result;
		}
};

int RETURNINDEX = 0;
int FUNCTIONINDEX = -1;
int MECHANISMINDEX = -1;
int FCALLINDEX = 0;
Variable V;  
ASTNode *NodeInFocus;
ASTNode *LatestChildOfNodeInFocus;
AST AbstractSyntaxTree;

unordered_map<string, regex> TOKENS = {
    { "Blockchain",         GetRegex("Blockchain") },
    { "Mechanism",          GetRegex("Mechanism") },
    { "Root",               GetRegex("Root") },
    { "Aspect",             GetRegex("Aspect") },
    { "SemiColon",          GetRegex(R"(;)") },
    { "ClosedParenthesis",  GetRegex(R"(\))") },
    { "ClosedCurlyBraces",  GetRegex(R"(\})") },
    { "OpenParenthesis",    GetRegex(R"(\()") },
    { "OpenCurlyBraces",    GetRegex(R"(\{)") },
    { "Equal",              GetRegex("(=)") },
    { "FunctionDeclaration",GetRegex("(func)") }, 
    { "ReturnStatement",    GetRegex("(return)") },
    { "DataTypeNonce",    GetRegex("(Nonce)") },
    { "DataTypeInt",    GetRegex("(Int)") } 
};

void PrintNode(ASTNode n, string m){
    cout << "[PrintNode - " << m << "] -- ([" << n.self.type << "] , [ " << n.self.value << " ] )" << endl;
    cout << "[Children - " << m << "] -- (" << sizeof(n.children) << ")" << endl;
    for(auto i : n.children){
        cout << "[n_child]: " << i.self.type << endl;
    }
    cout << "[Parent - " << m << "] -- ([" << n.parent.type << "] , [ " << n.parent.value << " ] )" << endl;
}

AST ProcessNewNode(ASTNode n, AST t){
    t.Nodes.push_back(n);
    cout << "                                   " << endl;
    cout << "==========================================" << endl;
    cout << "================[NODES]===================" << endl;
    return t;
} 

void AddChildToAST(){

}

void SwitchASTNode(){

}

ASTNode CreateASTNodeChildren(ASTNode current,
                          ASTNode next,
                          ASTNode prev){
    cout << "======================[SimpleLanguageConditions BEGIN ===========================] : ["<<current.self.type<<"]" << endl;
    if(current.self.type == "Blockchain"){
        Node ChainNode("Chain","CHAINID");
        ASTNode RootChainNode(ChainNode);
        RootChainNode.ASTVectorID = AbstractSyntaxTree.Nodes.size();
        cout << "SET BLOCKCHAIN NAME AS NEXT" << endl;
        string s = current.self.value;
        s = ReplaceSubstring(s, R"(\()", R"( )");
        cout << "[Blockchain split] " << s << endl;
        s = ReplaceSubstring(s, R"(\))", R"( )");
        s = ReplaceSubstring(s, R"(,)", R"( )");
        cout << "[S] " << s << endl;
        strings ParsedNodeValue = SubParse(s);
        for (auto i : ParsedNodeValue){
            if(i == ParsedNodeValue[0]){
                string VariableName = "BlockchainName";
                pair<string,string> 
                PairToInsert(VariableName, i);
                cout << V.InsertNewVariable(PairToInsert) << endl;
                map<string, string> mem = V.memory;
                auto pos = mem.find(PairToInsert.first);
                Node ChainNameNode("ChainName", i);
                ASTNode ASTNode_ChainNameNode(ChainNameNode);
                PrintNode(ASTNode_ChainNameNode, "ASTNode_ChainNameNode");
                RootChainNode.children.push_back(ASTNode_ChainNameNode);
                if (pos == mem.end()) {
                    cout << "Memory Test for "<<VariableName<<" [FAIL]" << endl;
                } else {
                    string value = pos->second;
                    cout << "Memory Test for "<<VariableName<<" [PASS]: " << value << endl;
                }
            } else { 
                string VariableName = "imported "+i;
                pair<string,string> 
                PairToInsert(VariableName, "TRUE");
                cout << V.InsertNewVariable(PairToInsert) << endl;
            }
            cout << "[Blockchain][Subparse] - " << i << endl;
        } 
        current.children.push_back(next);
        AbstractSyntaxTree
        .Nodes
        .push_back(RootChainNode);
        NodeInFocus = &(AbstractSyntaxTree
                      .Nodes[AbstractSyntaxTree.Nodes.size()-1]);
        cout << "AbstractSyntaxTree SIZEOF: " << AbstractSyntaxTree.Nodes.size() << endl;
    } 
    else if (current.self.type == "OpenCurlyBracesNoClosed") {
        cout << "[JUST SKIP, ONLY RELEVANT WITH CONTEXT]" << endl;
        PrintNode(prev, "Print Prev from OpenCurlyBracesNoClosed");
        if(prev.self.type == "PostBlockchainDeclaration"){
           Node ChainBody("ChainBody", "ChainBody");
           ASTNode ASTNode_ChainBody(ChainBody);
           ASTNode_ChainBody.ASTVectorID = AbstractSyntaxTree.Nodes.size();
           ASTNode_ChainBody.ParentASTVectorID = AbstractSyntaxTree.Nodes.size()-1;
           NodeInFocus->children
           .push_back(ASTNode_ChainBody);
           NodeInFocus = &(NodeInFocus->children[NodeInFocus->children.size()-1]);
           AbstractSyntaxTree
           .Nodes
           .push_back(*NodeInFocus);
        }
    }
    else if (current.self.type == "UNKNOWN"){
    } 
    else if (current.self.type == "Equal"){
        string s = current.self.value;
        s = ReplaceSubstring(s, R"(\()", R"( )");
        cout << "[Equal split] " << s << endl;
        s = ReplaceSubstring(s, R"( , )", R"( )");
        s = ReplaceSubstring(s, R"(\))", R"( )");
        cout << "[S] " << s << endl;
        strings ParsedNodeValue;
        ParsedNodeValue = SubParse(s);
        string VariableName = "Variable_"+ParsedNodeValue[0];
        string allButVariableName;
        for (int i = 1; i < ParsedNodeValue.size(); i++){
            allButVariableName += ParsedNodeValue[i]+" ";
        }
        pair<string,string> 
        PairToInsert(VariableName, 
                     //ParsedNodeValue[1]);
                     allButVariableName);
        cout << V.InsertNewVariable(PairToInsert) << endl;
        map<string, string> mem = V.memory;
        auto pos = mem.find(VariableName);
        if (pos == mem.end()) {
            cout << "Memory Test for "<<VariableName<<" [FAIL]" << endl;
        } else {
            string value = pos->second;
            cout << "Memory Test for "<<VariableName<<" [PASS]: " << value << endl;
        }
        if(VariableName == "this.consensus"){
            cout << "[this.consensus]" << endl;
            Node SetConsensusNode("Consensus",
                                  ParsedNodeValue[1]);
            ASTNode ASTNode_SetConsensusNode(SetConsensusNode);
            ASTNode_SetConsensusNode.ASTVectorID = AbstractSyntaxTree.Nodes.size();
            ASTNode_SetConsensusNode.ParentASTVectorID = NodeInFocus->ASTVectorID;
            NodeInFocus
            ->children
            .push_back(ASTNode_SetConsensusNode);
            AbstractSyntaxTree
            .Nodes
            .push_back(NodeInFocus
            ->children[NodeInFocus
            ->children.size()-1]);
        }else{}
    } 
    else if (current.self.type == "SemiColon"){
    } 
    else if (current.self.type == "FunctionDeclaration") {
        string s = next.self.value;
        s = ReplaceSubstring(s, R"(\()", R"( )");
        cout << "[FunctionDeclaration split] " << s << endl;
        s = ReplaceSubstring(s, R"(\))", R"( )");
        s = ReplaceSubstring(s, 
                                   R"((,))", R"( )");
        cout << "[S] " << s << endl;
        strings ParsedNodeValue;
        ParsedNodeValue = SubParse(s);
        int functionIndex = ++FUNCTIONINDEX;   
        string VariableName = current.self.type+"_"+ to_string(functionIndex) + "_" +ParsedNodeValue[0];
        pair<string,string> 
        PairToInsert(VariableName, s);//ParsedNodeValue[0]);
        cout << V.InsertNewVariable(PairToInsert) << endl;
        map<string, string> mem = V.memory;
        auto pos = mem.find(VariableName);
        if (pos == mem.end()) {
            cout << "Memory Test for "<<VariableName<<" [FAIL]" << endl;
        } else {
            string value = pos->second;
            cout << "Memory Test for "<<VariableName<<" [PASS]: " << value << endl;
        }
        cout << "[FunctionDeclaration]" << endl;
        Node FunctionDeclarationNode("FunctionDeclarationNode",
                                     next.self.value);
        ASTNode ASTNode_FunctionDeclarationNode(FunctionDeclarationNode);
        ASTNode_FunctionDeclarationNode.ASTVectorID = AbstractSyntaxTree.Nodes.size();
        ASTNode_FunctionDeclarationNode.ParentASTVectorID = NodeInFocus->ASTVectorID; //AbstractSyntaxTree.Nodes.size()-1;
        AbstractSyntaxTree
        .Nodes[NodeInFocus->ASTVectorID]
        .children
        .push_back(ASTNode_FunctionDeclarationNode);
        AbstractSyntaxTree.Nodes.push_back(ASTNode_FunctionDeclarationNode);

        //NodeInFocus = &NodeInFocus->children[NodeInFocus->children.size()-1];
        NodeInFocus = &(AbstractSyntaxTree.Nodes[AbstractSyntaxTree.Nodes.size()-1]);

        Node MethodNameNode("MethodName", ParsedNodeValue[0]);
        ASTNode ASTNode_MethodNameNode(MethodNameNode);
        ASTNode_MethodNameNode
        .ASTVectorID = AbstractSyntaxTree.Nodes.size();
        ASTNode_MethodNameNode
        .ParentASTVectorID = NodeInFocus->ASTVectorID;
        AbstractSyntaxTree
        .Nodes[NodeInFocus->ASTVectorID]
        .children.push_back(ASTNode_MethodNameNode);
        for(int i = 1; i < ParsedNodeValue.size(); i++){
            if(i%2 != 0){
                cout << "[PARAM]" << ParsedNodeValue[i] << endl;
                Node ParamNode("Parameter", 
                                ParsedNodeValue[i]+" : "+ParsedNodeValue[i+1]);
                ASTNode ASTNode_ParamNode(ParamNode);
                ASTNode_ParamNode
                .ASTVectorID = AbstractSyntaxTree.Nodes.size();
                ASTNode_ParamNode
                .ParentASTVectorID = NodeInFocus->ASTVectorID;
                AbstractSyntaxTree
                .Nodes[NodeInFocus->ASTVectorID]
                .children.push_back(ASTNode_ParamNode);
            }    
        }
    }
    else if (current.self.type == "ReturnStatement"){
        string s = next.self.value;
        s = ReplaceSubstring(s, R"(\()", R"( )");
        cout << "[ReturnStatement split] " << s << endl;
        s = ReplaceSubstring(s, R"(\))", R"( )");
        cout << "[S] " << s << endl;
        strings ParsedNodeValue;
        ParsedNodeValue = SubParse(s);
        int returnIndex = FUNCTIONINDEX; //RETURNINDEX++;         
        string VariableName = current.self.type+"_" + to_string(returnIndex) + "_"+ParsedNodeValue[0];
        pair<string,string> 
        PairToInsert(VariableName, s); //ParsedNodeValue[0]);
        cout << V.InsertNewVariable(PairToInsert) << endl;
        map<string, string> mem = V.memory;
        auto pos = mem.find(VariableName);
        if (pos == mem.end()) {
            cout << "Memory Test for "<<VariableName<<" [FAIL]" << endl;
        } else {
            string value = pos->second;
            cout << "Memory Test for "<<VariableName<<" [PASS]: " << value << endl;
        }
        Node ReturnNode(VariableName,s);
        ASTNode ASTNode_ReturnNode(ReturnNode);
        ASTNode_ReturnNode.ASTVectorID = AbstractSyntaxTree.Nodes.size();
        ASTNode_ReturnNode.ParentASTVectorID = NodeInFocus->ASTVectorID;
        NodeInFocus
        ->children
        .push_back(ASTNode_ReturnNode);
    } 
    else if (current.self.type == "BothParenthesis"){
        string s = current.self.value;
        s = ReplaceSubstring(s, R"(\()", R"( )");
        cout << "[BothParenthesis split] " << s << endl;
        s = ReplaceSubstring(s, R"(\))", R"( )");
        cout << "[S] " << s << endl;
        strings ParsedNodeValue;
        ParsedNodeValue = SubParse(s);
        int functionCallIndex = FUNCTIONINDEX;//FCALLINDEX++; //FUNCTIONINDEX  // v1 in the range 0 to 99
        string VariableName = current.self.type+"_" + to_string(functionCallIndex) + "_"+ParsedNodeValue[0];
        pair<string,string> 
        PairToInsert(VariableName, s);//ParsedNodeValue[0]);
        cout << V.InsertNewVariable(PairToInsert) << endl;
        map<string, string> mem = V.memory;
        auto pos = mem.find(VariableName);
        if (pos == mem.end()) {
            cout << "Memory Test for "<<VariableName<<" [FAIL]" << endl;
        } else {
            string value = pos->second;
            cout << "Memory Test for "<<VariableName<<" [PASS]: " << value << endl;
        }
        Node FunctionCallNode("FunctionCall_"+VariableName,s);
        ASTNode ASTNode_FunctionCallNode(FunctionCallNode);
        ASTNode_FunctionCallNode.ASTVectorID = AbstractSyntaxTree.Nodes.size();
        ASTNode_FunctionCallNode.ParentASTVectorID = NodeInFocus->ASTVectorID;
        NodeInFocus
        ->children
        .push_back(ASTNode_FunctionCallNode);
    } 
    else if (current.self.type == "DataTypeNonce"){ ////DATATYPE NONCE
        string s = current.self.type;
        string VariableName = s+"_"+to_string(FUNCTIONINDEX);
        pair<string,string> 
        PairToInsert(VariableName, next.self.value);
        cout << V.InsertNewVariable(PairToInsert) << endl;
        map<string, string> mem = V.memory;
        auto pos = mem.find(VariableName);
        if (pos == mem.end()) {
            cout << "Memory Test for "<<VariableName<<" [FAIL]" << endl;
        } else {
            string value = pos->second;
            cout << "Memory Test for "<<VariableName<<" [PASS]: " << value << endl;
        }
        Node DataTypeNonceNode(VariableName,next.self.value);
        ASTNode ASTNode_DataTypeNonceNode(DataTypeNonceNode);
        ASTNode_DataTypeNonceNode.ASTVectorID = AbstractSyntaxTree.Nodes.size();
        ASTNode_DataTypeNonceNode.ParentASTVectorID = NodeInFocus->ASTVectorID;
        NodeInFocus
        ->children
        .push_back(ASTNode_DataTypeNonceNode);
    } 
    else if (current.self.type == "DataTypeInt"){ ////DATATYPE Integer
        string s = current.self.type;
        string VariableName = s+"_"+to_string(FUNCTIONINDEX);
        pair<string,string> 
        PairToInsert(VariableName, next.self.value);
        cout << V.InsertNewVariable(PairToInsert) << endl;
        map<string, string> mem = V.memory;
        auto pos = mem.find(VariableName);
        if (pos == mem.end()) {
            cout << "Memory Test for "<<VariableName<<" [FAIL]" << endl;
        } else {
            string value = pos->second;
            cout << "Memory Test for "<<VariableName<<" [PASS]: " << value << endl;
        }
        Node DataTypeIntNode(VariableName,next.self.value);
        ASTNode ASTNode_DataTypeIntNode(DataTypeIntNode);
        ASTNode_DataTypeIntNode.ASTVectorID = AbstractSyntaxTree.Nodes.size();
        ASTNode_DataTypeIntNode.ParentASTVectorID = NodeInFocus->ASTVectorID;
        NodeInFocus
        ->children
        .push_back(ASTNode_DataTypeIntNode);
    } 
    else if (current.self.type == "ClosedCurlyBracesNoOpen"){ ////ClosedParenthesisNoOpen 
        cout << "[INSIDE ClosedCurlyBracesNoOpen]" << endl;
        cout << "[NODEINFOCUS]: " 
        << NodeInFocus->self.type 
        << " -- " 
        << NodeInFocus->ParentASTVectorID
        << endl;
        PrintNode(current, "INSIDE ClosedCurlyBracesNoOpen");
        NodeInFocus = &(AbstractSyntaxTree
                        .Nodes[ NodeInFocus->ParentASTVectorID ] );
    } 
    else if (current.self.type == "Mechanism") {
        Node MechanismNode("Mechanism","MECHANISMID");
        ASTNode RootMechanismNode(MechanismNode);
        RootMechanismNode.ASTVectorID = AbstractSyntaxTree.Nodes.size();
        cout << "SET MECHANISM NAME AS NEXT" << endl;
        string s = current.self.value;
        s = ReplaceSubstring(s, R"(\()", R"( )");
        cout << "[Blockchain split] " << s << endl;
        s = ReplaceSubstring(s, R"(\))", R"( )");
        s = ReplaceSubstring(s, R"(,)", R"( )");
        cout << "[S] " << s << endl;
        strings ParsedNodeValue = SubParse(s);
        for (auto i : ParsedNodeValue){
            if(i == ParsedNodeValue[0]){
                string VariableName = "MechanismName";
                pair<string,string> 
                PairToInsert(VariableName, i);
                cout << V.InsertNewVariable(PairToInsert) << endl;
                map<string, string> mem = V.memory;
                auto pos = mem.find(PairToInsert.first);
                Node MechanismNameNode("MechanismName", i);
                ASTNode ASTNode_MechanismNameNode(MechanismNameNode);
                PrintNode(ASTNode_MechanismNameNode, "ASTNode_MechanismNameNode");
                RootMechanismNode.children.push_back(ASTNode_MechanismNameNode);
                if (pos == mem.end()) {
                    cout << "Memory Test for "<<VariableName<<" [FAIL]" << endl;
                } else {
                    string value = pos->second;
                    cout << "Memory Test for "<<VariableName<<" [PASS]: " << value << endl;
                }
            } else { 
                string VariableName = "imported "+i;
                pair<string,string> 
                PairToInsert(VariableName, "TRUE");
                cout << V.InsertNewVariable(PairToInsert) << endl;
            }
            cout << "[Mechanism][Subparse] - " << i << endl;
        }
        current.children.push_back(next);
        AbstractSyntaxTree
        .Nodes
        .push_back(RootMechanismNode);
        NodeInFocus = &(AbstractSyntaxTree
                      .Nodes[AbstractSyntaxTree.Nodes.size()-1]);

        cout << "AbstractSyntaxTree SIZEOF: " << AbstractSyntaxTree.Nodes.size() << endl;
    } 
    else if (current.self.type == "Aspect") {
        Node AspectNode("Aspect","AspectID");
        ASTNode RootAspectNode(AspectNode);
        RootAspectNode.ASTVectorID = AbstractSyntaxTree.Nodes.size();
        cout << "SET ASPECT NAME AS NEXT" << endl;
        string s = current.self.value;
        s = ReplaceSubstring(s, R"(\()", R"( )");
        cout << "[Blockchain split] " << s << endl;
        s = ReplaceSubstring(s, R"(\))", R"( )");
        s = ReplaceSubstring(s, R"(,)", R"( )");
        cout << "[S] " << s << endl;
        strings ParsedNodeValue = SubParse(s);
        for (auto i : ParsedNodeValue){
            if(i == ParsedNodeValue[0]){
                string VariableName = "AspectName";
                pair<string,string> 
                PairToInsert(VariableName, i);
                cout << V.InsertNewVariable(PairToInsert) << endl;
                map<string, string> mem = V.memory;
                auto pos = mem.find(PairToInsert.first);
                Node AspectNameNode("AspectName", i);
                ASTNode ASTNode_AspectNameNode(AspectNameNode);
                PrintNode(ASTNode_AspectNameNode, "ASTNode_AspectNameNode");
                RootAspectNode.children.push_back(ASTNode_AspectNameNode);
                if (pos == mem.end()) {
                    cout << "Memory Test for "<<VariableName<<" [FAIL]" << endl;
                } else {
                    string value = pos->second;
                    cout << "Memory Test for "<<VariableName<<" [PASS]: " << value << endl;
                }
            } else { 
                string VariableName = "imported "+i;
                pair<string,string> 
                PairToInsert(VariableName, "TRUE");
                cout << V.InsertNewVariable(PairToInsert) << endl;
            }
            cout << "[Aspect][Subparse] - " << i << endl;
        } 
        current.children.push_back(next);
        AbstractSyntaxTree
        .Nodes
        .push_back(RootAspectNode);
        NodeInFocus = &(AbstractSyntaxTree
                      .Nodes[AbstractSyntaxTree.Nodes.size()-1]);
        cout << "AbstractSyntaxTree SIZEOF: " << AbstractSyntaxTree.Nodes.size() << endl;
    } 
    else if (current.self.type == "Root") {
        Node RootNode("Root","ROOID");
        ASTNode RootRootNode(RootNode);
        RootRootNode.ASTVectorID = AbstractSyntaxTree.Nodes.size();
        cout << "SET ROOT NAME AS NEXT" << endl;
        string s = current.self.value;
        s = ReplaceSubstring(s, R"(\()", R"( )");
        cout << "[Blockchain split] " << s << endl;
        s = ReplaceSubstring(s, R"(\))", R"( )");
        s = ReplaceSubstring(s, R"(,)", R"( )");
        cout << "[S] " << s << endl;
        strings ParsedNodeValue = SubParse(s);
        for (auto i : ParsedNodeValue){
            if(i == ParsedNodeValue[0]){
                string VariableName = "RootName";
                pair<string,string> 
                PairToInsert(VariableName, i);
                cout << V.InsertNewVariable(PairToInsert) << endl;
                map<string, string> mem = V.memory;
                auto pos = mem.find(PairToInsert.first);
                Node RootNameNode("RootName", i);
                ASTNode ASTNode_RootNameNode(RootNameNode);
                PrintNode(ASTNode_RootNameNode, "ASTNode_RootNameNode");
                RootRootNode.children.push_back(ASTNode_RootNameNode);
                if (pos == mem.end()) {
                    cout << "Memory Test for "<<VariableName<<" [FAIL]" << endl;
                } else {
                    string value = pos->second;
                    cout << "Memory Test for "<<VariableName<<" [PASS]: " << value << endl;
                }
            } else {
                string VariableName = "imported "+i;
                pair<string,string> 
                PairToInsert(VariableName, "TRUE");
                cout << V.InsertNewVariable(PairToInsert) << endl;
            }
            cout << "[Root][Subparse] - " << i << endl;
        } 
        current.children.push_back(next);
        AbstractSyntaxTree
        .Nodes
        .push_back(RootRootNode);
        NodeInFocus = &(AbstractSyntaxTree
                      .Nodes[AbstractSyntaxTree.Nodes.size()-1]);
        cout << "AbstractSyntaxTree SIZEOF: " << AbstractSyntaxTree.Nodes.size() << endl;
    } 
    cout << "======================[SimpleLanguageConditions END ===========================]\n\n\n" << endl;
    return current;
}

void TraverseTree(ASTNode n){
    auto &last_child = *(--n.children.end());
    if(n.children.size() > 0){
        for(ASTNode &child : n.children){
            if (&child == &last_child){
                cout << "LAST CHILD === " <<child.self.type<<"]"<<endl;
                if(child.children.size() > 0){
                    cout << "\n\n=====[Child of "<<n.self.type<<"]["<<n.self.value<<"][PID: "<<child.ParentASTVectorID<<"]=====\nNumber of Children: " 
                    << child.children.size() 
                    << "\n=====[Parent Type] "
                    <<AbstractSyntaxTree.Nodes[child.ParentASTVectorID].self.type<<"]" << endl; 
                    cout << "[Traverse Tree Child: ["
                    << child.self.type<<"] : " 
                    << child.self.value  << "\n===============\n\n"
                    << endl;
                    TraverseTree(child);
                }else{
                    cout << "SUB-ROOT NODE - NO FUCKING CHILDREN == " << child.self.type<<"]"<<endl;
                }  
            }else{
                if(child.children.size() > 0){
                    cout << "\n\n=====[Child of "<<n.self.type<<"]["<<n.self.value<<"][PID: "<<child.ParentASTVectorID<<"]=====\nNumber of Children: " 
                    << child.children.size() 
                    << "\n=====[Parent Type] "
                    <<AbstractSyntaxTree.Nodes[child.ParentASTVectorID].self.type<<"]" << endl; 
                    cout << "[Traverse Tree Child: ["
                    << child.self.type<<"] : " 
                    << child.self.value  << "\n===============\n\n"
                    << endl;
                    TraverseTree(child);
                }else{
                    cout << "SUB-ROOT NODE - NO CHILDREN == " << child.self.type<<"]"<<endl;
                }     
            }
        }
    }else{
        cout << "ROOT NODE - NO CHILDREN" << endl;
    }
}


void PrintAST(AST t){
    cout << "\n=========ABSTRACT SYNTAX TREE==========\n\n" 
    << t.Nodes.size() << "\n" << endl;
    for(auto &n : t.Nodes){
        cout<<"["<<n.self.type<<"]["<<n.parent.type<<"][ID: "<<n.ASTVectorID<<"][PID: "<<n.ParentASTVectorID<<"]\n"<<endl;
        TraverseTree(n);
    }
}

/*
Function Evaluate
@desc : accept current token, previous token, and next token, and decide what pairs to make
@param string section
@param string prev
@param string next
@return one, single ASTNode
*/

ASTNode Evaluate(string section, string prev, string next){
    pair<string, string> ResultingPair;
    if ( regex_match (section, TOKENS["Blockchain"]) ){
        cout << "[Evaluate][Blockchain] matched, parse next section for blockchain name, and external objects used \n";
        ResultingPair = make_pair("Blockchain",next); 
    }else if ( regex_match (section, TOKENS["Mechanism"]) ){
        cout << "[Evaluate][Mechanism] matched, parse next section for Mechanism name, and external objects used \n";
        ResultingPair = make_pair("Mechanism",next); 
    } else if ( regex_match (section, TOKENS["Root"]) ){
        cout << "[Evaluate][Root] matched, parse next section for Root name, and external objects used \n";
        ResultingPair = make_pair("Root",next); 
    } else if ( regex_match (section, TOKENS["Aspect"]) ){
        cout << "[Evaluate][Aspect] matched, parse next section for Aspect name, and external objects used \n";
        ResultingPair = make_pair("Aspect",next); 
    }else if ( regex_search (section, TOKENS["SemiColon"]) ){
        cout << "[Evaluate][SemiColon] matched \n";
        ResultingPair = make_pair("SemiColon","");
    }else if (regex_search (section, TOKENS["ClosedParenthesis"]) &&
             !regex_search (section, TOKENS["OpenParenthesis"])){
        cout << "[Evaluate][ClosedParenthesisNoOpen] matched \n";
        ResultingPair = make_pair("ClosedParenthesisNoOpen",section);
    }else if (regex_search(section, TOKENS["ClosedParenthesis"]) &&
              regex_search(section, TOKENS["OpenParenthesis"]) 
              ){
        cout << "[Evaluate][BothParenthesis] [nofuncdef] matched \n";
        if(!regex_match (prev, TOKENS["Blockchain"]) &&
           !regex_search (prev, TOKENS["FunctionDeclaration"]) &&
           !regex_search (prev, TOKENS["Mechanism"]) && 
           !regex_search (prev, TOKENS["Aspect"]) &&
           !regex_search (prev, TOKENS["Root"])) {
            if(regex_search (prev, TOKENS["Equal"])){
                ResultingPair = make_pair("BothParenthesis", "");
            }else{
                string s = ReplaceSubstring(section, R"(\()", R"( )");
                cout << "[Actual Function Call split] " << s << endl;
                s = ReplaceSubstring(s, R"(\))", R"( )");
                s = ReplaceSubstring(s, R"(,)", R"( )");
                cout << "[S] " << s << endl;
                strings ParsedNodeValue = SubParse(s);
                ResultingPair = make_pair("BothParenthesis", "OP_FUNCCALL "+section);
            }
        } else if(regex_match (prev, TOKENS["Mechanism"])){
            ResultingPair = make_pair("PostMechanismDeclaration",section);
        } else if(regex_match (prev, TOKENS["Root"])){
            ResultingPair = make_pair("PostRootDeclaration",section);
        } else if(regex_match (prev, TOKENS["Aspect"])){
            ResultingPair = make_pair("PostAspectDeclaration",section);
        } else if(regex_search (prev, TOKENS["FunctionDeclaration"])){
            ResultingPair = make_pair("PostFunctionDeclaration",
                                      section);
        }else if(regex_match (prev, TOKENS["Blockchain"])){
            ResultingPair = make_pair("PostBlockchainDeclaration","PREV == BLOCKCHAIN");
        }   
    }else if (!regex_search (section, TOKENS["ClosedParenthesis"]) &&
             regex_search (section, TOKENS["OpenParenthesis"])){
        cout << "[Evaluate][OpenParenthesisNoClosed] matched \n";
        ResultingPair = make_pair("OpenParenthesisNoClosed",section);   
    }else if (regex_search (section, TOKENS["ClosedCurlyBraces"]) &&
              !regex_search (section, TOKENS["OpenCurlyBraces"])){
        cout << "[Evaluate][ClosedCurlyBracesNoOpen] matched \n";
        ResultingPair = make_pair("ClosedCurlyBracesNoOpen","");    
    }else if (regex_search (section, TOKENS["ClosedCurlyBraces"]) &&
              regex_search (section, TOKENS["OpenCurlyBraces"])){
        cout << "[Evaluate][BothBraces] matched \n";
        ResultingPair = make_pair("BothBraces",section);    
    }else if (regex_search (section, TOKENS["OpenCurlyBraces"]) &&
              !regex_search (section, TOKENS["ClosedCurlyBraces"])){
        cout << "[Evaluate][OpenCurlyBracesNoClosed] matched \n";
        ResultingPair = make_pair("OpenCurlyBracesNoClosed","");  
    }else if (regex_search (section, TOKENS["Equal"])){
        cout << "[Evaluate][Equal] matched \n";
        string stopAt = ";";
        string subparse = ParseUntilStop(next, stopAt);
        ResultingPair = make_pair("Equal", "OP_ASSIGN "+prev+"$"+subparse+"" );
    }else if (regex_search (section, TOKENS["FunctionDeclaration"])){
        cout << "[Evaluate][FunctionDeclaration] matched \n";
        ResultingPair = make_pair("FunctionDeclaration","OP_FUNCDECL");  
    }else if (regex_search (section, TOKENS["ReturnStatement"])){
        cout << "[Evaluate][ReturnStatement] matched \n";
        ResultingPair = make_pair("ReturnStatement",next);  
    }else if (regex_search (section, TOKENS["DataTypeNonce"])){
        cout << "[Evaluate][DataTypeNonce] matched \n";
        string type_id = "DataTypeNonce";
        ResultingPair = make_pair("type_id",type_id+" "+next);  
    }else if (regex_search (section, TOKENS["DataTypeInt"])){
        cout << "[Evaluate][DataTypeInt] matched \n";
        string type_id = "DataTypeInt";
        ResultingPair = make_pair(type_id,type_id); 
    }        
    else{
        string stopAt = ";";
        string subparse = ParseUntilStop(section, stopAt);
        cout << "[Evaluate][UNKNOWN] matched " << "[ " << section << " ]" << "\n";
        ResultingPair = make_pair("UNKNOWN",subparse);        
    }
    Node n(ResultingPair.first, ResultingPair.second);
    vector<ASTNode> children;
    Node parent;
    ASTNode ResultingASTNode(n, children, parent);
    PrintNode(ResultingASTNode, "ResultingASTNode");
    return ResultingASTNode;
}

/*
Function CreateNodes
@desc : accept vector<strings>, and produce an AST
@param vector<string> tokens
@return one, single ASTNode
*/

AST CreateNodes(strings tokens){
    AST tree; 
    auto &last_element = *(--tokens.end());
    cout << "\n============================\n" << endl;
    for(auto &i : tokens){
      cout << "[CreateNodes]: " << i << endl;
      string prev;// = *(&i - 1);
      string next;// = *(&i + 1);
      if (&i == &last_element){
        cout << "END OF TOKENS" << endl;
        cout << "\n\n=====[[END]" << i << "]" <<endl;
      }else{
        try{
            next = *(&i + 1);
          } catch (exception& e){
            throw "CreateNodes Error - No Next Token";
          }
          try{            
            if(&tokens[0] == &i){
                //cout << "[CreateNodes NO PREV]" << endl;
            }else{
                prev = *(&i - 1);
                //cout << "[CreateNodes Prev]: " << prev << endl;
            }
          } catch (exception& e){
            //cout << "An exception occurred. Exception CreateNodes PREV. " << endl;
            throw "CreateNodes Error - No Previous Token";
          }
          ASTNode node = Evaluate(i, prev, next);
          if(node.self.type != "NOOP"){
            tree = ProcessNewNode(node, tree);
          }
      }  
    }
    return tree;
}

#endif
