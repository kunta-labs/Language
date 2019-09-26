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

#include <nan.h>
#include <iostream>
#include <fstream>
#include <iostream> 
#include "kuntac.h"
#include "json.hpp"
// for convenience
using json = nlohmann::json;
using namespace std;
void ResetEnvironment(){
  V.memory.clear(); 
  RETURNINDEX = 0;
  FUNCTIONINDEX = -1;
  MECHANISMINDEX = -1;
  FCALLINDEX = 0;
}

void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  cout << "METHOD IS RUNNING" << endl;
  ResetEnvironment();
  Nan::HandleScope scope;
  if (info[0]->IsString()) {
    v8::String::Utf8Value KVM_SCRIPT(info[0]->ToString());
    printf("[KVM Node Invocation] - %s ", (const char*)(*KVM_SCRIPT));
    string contents = (const char*)(*KVM_SCRIPT);
    strings KVM_Inst = KuntaScript::Parse(contents);
    json config = ScopesToOpcodes(KVM_Inst);
    v8::Isolate* isolate = info.GetIsolate();    
    v8::Local<v8::Array> result_list = v8::Array::New(isolate);
    v8::Local<v8::Object> r = v8::Object::New(isolate);
    r->Set( v8::String::NewFromUtf8( isolate, "configuration" ),
            v8::String::NewFromUtf8( isolate, config.dump().c_str() ));
    result_list->Set(0, r);
    info.GetReturnValue().Set(result_list);
  }
}

void Init(v8::Local<v8::Object> exports) {
  cout << "Init IS RUNNING" << endl;
  exports->Set(Nan::New("Language").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(Language, Init)
