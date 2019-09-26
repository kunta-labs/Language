# Abstraction Language


## basic script
```javascript
Blockchain B1(Consensus, Root) {
	this.consensus = Consensus.POW;
	func Create(Config i, Status s){ 
		log("created..."); 
		return True; 
	}
	func testFunc(Block b){
		Nonce answer = b.nonce;
		return answer;
	}
	func OnNewBlock(Block b, Hash h){
		log("i wrote a new block: "+b.id+" : "+h);
		Int number_result = testFunc(b);
		log(number_result);
	}
}
```

# POC

votes.kscript

```javascript
Aspect votes{
	description
	default_value
}
```

vote.kscript

```javascript
import votes

Root vote(Aspect){
	name: 
	access
	code
	return

	AddAspect(votes)
}
```


end_date.kscript

```javascript
Aspect end_date{
	description
	default_value
}
```

verdict.kscript

```javascript
import end_date

Root verdict(Aspect){
	name: 
	access
	code
	return

	AddAspect(end_date)
}
```

```javascript
import vote, votes;
import verdict, end_date;

Blockchain(Consensus, Root) { 

	require(1); 
	require(2); 

	this.consensus = Consensus.POW;

	AddRoot(vote);
	AddRoot(verdict);

	func Create(){ 
		test('dsd'); 
		return 0; 
	}; 

	func OnNewBlock(){
		log("i wrote a new block");
	}

	create(); 

}
```

# Compilation

### compile all files - 

```javascript
kuntac -o target --bin --abi B1.kscript 
```

# Creates these files
```javascript
$tree
.
├── B1.kscript
└── target
   ├── B1.abi
   ├── B1.bin
   ├── votes.abi?
   └── votes.bin?
   ├── verdict.abi?
   └── verdict.bin?
```

```javascript

kunode.Chain()
kunode.RootInstance()
```

```javascript
kunode.deploy(<contents of the file B1.abi>)?
```

### create root instance - kunode

## poc 2

```javascript
import vote, votes;
import verdict, end_date;

Blockchain B1(Consensus, Root) { 

	require(1); 
	require(2); 

	this.consensus = Consensus.POW;

	AddRoot(vote);
	AddRoot(verdict);

	func Create(){ 
		test('dsd'); 
		return 0; 
	}; 

	func OnNewBlock(){
		log("i wrote a new block");
	}

	create(); 

}
```

```javascript
B1.start()
```

# kunode

```javascript
RootInstance ballot1 = Female(vote, ...); 
```

```javascript
RootInstance myvote = Male(ballot1, ...)
```

```javascript
B1.send(ballot1)
```



