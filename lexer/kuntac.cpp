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

#include "kuntac.h"
using namespace std;
int main(int argc, char *argv[]){
	string file = argv[1];
	std::ifstream t(file);
	std::string contents((std::istreambuf_iterator<char>(t)),
	                 std::istreambuf_iterator<char>());
  	strings KVM_Inst = KuntaScript::Parse(contents);
  	cout << "                                   " << endl;
	cout << "==========================================" << endl;
	cout << "================[CREATE NODES]===================" << endl;

    ////TODO: convert to nodes
  	//CreateNodes(KVM_Inst);
	//CreateASTFromNodes();
  	//PrintAST(AbstractSyntaxTree);
	ScopesToOpcodes(KVM_Inst);
	return 0;
}



