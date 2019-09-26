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

var CBINDING = require('bindings')('Language');
var fs = require('fs');
var express = require("express");
var bodyParser = require('body-parser');
var http_port = process.env.HTTP_PORT || 3002;
var blockchain_templates = []
class BLOCKCHAIN_TEMPLATE {
	constructor(C) {
		this.CONFIG = C
		return this.CONFIG
	}
}

var CHAIN_STATE = {
	CREATED: 0,
	READY: 1,
	DEPLOYED: 2,
	FROZEN: 3
}

class REGISTERED_CHAIN {
	constructor() {
		this.state = CHAIN.CREATED
	}
}

var LANGUAGE_CREATE_CHAIN = (contents) => {
	var language_result = CBINDING.Language(contents)
	console.log("created chain...");
	return contents;
}

var LANGUAGE_CREATE_MALE = () => {
	var contents = fs.readFileSync('vote_male.kscript', 'utf8');
	return CBINDING.Language(contents);
}

var LANGUAGE_CREATE_FEMALE = () => {
	var contents = fs.readFileSync('vote_female.kscript', 'utf8');
	return CBINDING.Language(contents);
}

var LANGUAGE_CREATE_FEMALE = () => {
	var contents = fs.readFileSync('vote_female.kscript', 'utf8');
	return CBINDING.Language(contents);
}

var Language_EXECUTE = (file = true, 
						fileName = "",
						script = "") => {
	var contents = null
	console.log("script: "+script)
	console.log("file: "+file)
	console.log("fileName: "+fileName)
	if(file){
		contents = fs.readFileSync('simple.kscript', 'utf8');
	}else{
		contents = script;
	}
	if(contents == null){
		throw "NO CONTENTS";
	}
	return LANGUAGE_CREATE_CHAIN(contents)
}

var BASE64ENCODE = (content) => {
	return Buffer.from(content).toString('base64')
}

var BASE64DECODE = (content) => {
	return Buffer.from(content, 'base64').toString('ascii')
}

var initHttpServer = () => {
    var app = express();
    app.use(bodyParser.json());
    app.use(function(req, res, next) {
        res.header("Access-Control-Allow-Origin", "*");
        res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        next();
    });
    app.post('/compile', (req, res) => {
        res.header("Access-Control-Allow-Origin", "*");
        res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        codeSubmitted = BASE64DECODE(req.body.code)
        console.log(codeSubmitted)
        if(req.body.code == ""){

        }else{
        	Language_EXECUTE(file = false,
        					 filename = "",
        					 script = codeSubmitted)
        }
        res.send(JSON.stringify( {"result": BASE64DECODE(req.body.code)} ))
    });
	app.listen(http_port, () => console.log('Listening http on port for peers: ' + http_port));
};

function SubmitSource(code){
	console.log("TESTIT")
    codeSubmitted = code //"Blockchain{code=3;}"//BASE64DECODE("Blockchain{code=3;}")
    console.log(codeSubmitted)
	var lang_exec = Language_EXECUTE(file = false,
					 filename = "",
					 script = codeSubmitted)
	return lang_exec;
}

//TESTIT()
//initHttpServer()

module.exports = {
	SubmitSource
}
