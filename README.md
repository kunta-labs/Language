# Abstraction Language


1)
```javascript
Blockchain(Consensus, Root, Access, Aspect) { 

	require(1); 
	require(2); 

	this.consensus = Consensus;

	Root vote = new Root();

	vote.access = Access.public;
	vote.return = "votes";

	Aspect votes = new Aspect();
	votes.default = Integer(100);

	Aspect able_to_vote = new Aspect();
	able_to_vote.default = Integer(1);


	Root verdict = new Root();

	verdict.access = Access.public;
	verdict.return = Blank;

	Aspect end_date = new Aspect();
	end_date.default = Timestamp(1826387363);


	func create(){ 
		test('dsd'); 
		return 0; 
	}; 

	create(); 

}
```

# POC
2)

votes.kscript

```javascript
Aspect votes{
	description
	default_value
}
```
//////////

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
/////////////



end_date.kscript

```javascript
Aspect end_date{
	description
	default_value
}
```
/////////

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
///////////

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

//////////////////// end POC
--------------------------

# Compilation

1) compile all files - 

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
kunode.deploy(<contents of the file Greeter.abi>)?
```

# eth example
```javascript
var greeterFactory = eth.contract(<contents of the file Greeter.abi>)
var greeterCompiled = "0x" + "<contents of the file Greeter.bin>"

var _greeting = "Hello World!"

var greeter = greeterFactory.new(_greeting,{from:eth.accounts[0],data:greeterCompiled,gas:47000000}, function(e, contract){
    if(e) {
      console.error(e); // If something goes wrong, at least we'll know.
      return;
    }

    if(!contract.address) {
      console.log("Contract transaction send: TransactionHash: " + contract.transactionHash + " waiting to be mined...");

    } else {
      console.log("Contract mined! Address: " + contract.address);
      console.log(contract);
    }
})
```

/////////////////////////

# 2) produce bc config
# 3) create root instance - kunode

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

////////////////

# kunode

//female
```javascript
RootInstance ballot1 = Female(vote, ...); //should be ballot instead of vote lol
```

```javascript
RootInstance myvote = Male(ballot1, ...)
```

```javascript
B1.send(ballot1)
```

```javascript
Time now = Time.now() + 5 minutes
```


```javascript
if(B1.time.after(now)){
	B1.send(myvote)
}
```

```javascript
RootInstance decision = Female(vedict)
```

```javascript
RootInstance judge = Male(decision)
```

```javascript
B1.send(decision)
```

```javascript
B1.send(judge)
```


```javascript
if(!B1.tx && B1.txd ){
	log("these nuts");
}
```


//////////////////// end POC 2

blockchain { require 1 ; require 1 ; test dsd return 0 ;  }

```javascript
{
"type":1,
"options":{},
"consensus":0,
"genesis_block":{},
"roots":[
	{"name":"vote",
	"access":0,
	"code":"[ACCOUNT] [INTEGER] OP_ADD OP_STORE OP_CONST [HASHPUBK] OP_CONST [PUBKHASH] OP_CONST_EQUAL_DROP [ACCOUNT] OP_CRITICAL_VERIFY [UNIX_TIME] OP_TIME_GREATER OP_CRITICAL_VERIFY",
	"return":"votes",
	"aspects":[
		{"description":"holding the total number of votes at a time",
		"aspect":"votes",
		"default_value":100},
		{"description":"votes can only happen if 1",
		"aspect":"able_to_vote",
		"default_value":1}
		]},
	{"name":"verdict",
	"access":0,
	"code":"[EXTERN_STATE] [PARAMETER] OP_ATLEAST_ZERO OP_VERIFY",
	"return":"#BLANK#",
	"aspects":[
		{"description":"refer to extern state, grab v, sum",
		"aspect":"end_date",
		"default_value":1826387363}
		]
	}
	]
}

[ACCOUNT] [INTEGER] OP_ADD OP_STORE OP_CONST [HASHPUBK] OP_CONST [PUBKHASH] OP_CONST_EQUAL_DROP [ACCOUNT] OP_CRITICAL_VERIFY [UNIX_TIME] OP_TIME_GREATER OP_CRITICAL_VERIFY
```

```javascript
RootInstance {
	
}
```

# Built in analytics

```javascript

vector block_times = B1.all.blocktime

float average_blocktime = Analytics.avg(block_times)

```

```javascript
vector all_blocks = B1.all

//out of these transaction, give me the top 10 high activity blocks
vector high_activity_blocks = Analytics.block.activity.high(all_blocks, 10) 



vector all_root_instances = B1.all.ri

//out of these transaction, give me the top 10 high male-activity blocks 
vector high_male_activity_blocks = Analytics.block.activity.male_high(all_root_instances, 10) 


```

# Built in prover
if(B1.rootInstances.contains(ri)){
	
}


```javascript


////////////////////////

```bash
[LEX]: Aspect
[LEX]: votes{
[LEX]: description
[LEX]: =
[LEX]: "blah"
[LEX]: ;
[LEX]: default_value
[LEX]: =
[LEX]: 0;
[LEX]: }
[LEX]: Root
[LEX]: vote(Aspect)
[LEX]: {
[LEX]: access
[LEX]: =
[LEX]: 0;
[LEX]: code
[LEX]: =
[LEX]: "dsdsdf"
[LEX]: ;
[LEX]: return
[LEX]: =
[LEX]: "blah"
[LEX]: ;
[LEX]: AddAspect(votes)
[LEX]: ;
[LEX]: }
[LEX]: Aspect
[LEX]: end_date{
[LEX]: description
[LEX]: =
[LEX]: "end date"
[LEX]: default_value
[LEX]: =
[LEX]: 1826387363
[LEX]: }
[LEX]: Root
[LEX]: verdict(Aspect)
[LEX]: {
[LEX]: access
[LEX]: =
[LEX]: 0;
[LEX]: code
[LEX]: =
[LEX]: "dsds"
[LEX]: ;
[LEX]: return
[LEX]: =
[LEX]: "dsd"
[LEX]: ;
[LEX]: AddAspect(end_date)
[LEX]: ;
[LEX]: }
[LEX]: Blockchain(Consensus, Root)
[LEX]: {
[LEX]: require(1)
[LEX]: ;
[LEX]: require(2)
[LEX]: ;
[LEX]: this.consensus
[LEX]: =
[LEX]: Consensus.POW;
[LEX]: AddRoot(vote)
[LEX]: ;
[LEX]: AddRoot(verdict)
[LEX]: ;
[LEX]: func
[LEX]: Create()
[LEX]: {
[LEX]: test('dsd')
[LEX]: ;
[LEX]: return
[LEX]: 0;
[LEX]: };
[LEX]: func
[LEX]: OnNewBlock()
[LEX]: {
[LEX]: log("i wrote a new block")
[LEX]: ;
[LEX]: }
[LEX]: create()
[LEX]: ;
[LEX]: }
```

////////////



# 4 types
- Assignment
- Operations
- Function calls
- Fuction definition

## AST 
(type, value)

traverse each node, depth first

visit = {
	numberliteral(node, parent)
	callexpression(node, parent)
}

tokens = tokenizer()
ast = parser()
newast = transformer()
output = codegenerator()

(if, switch, for) is a function, not a keyword

Parse(tokens, ";")

keep going until run out of tokens

	if p is not None, everytime it returns something useful
	//go to next, becuase it didnt find anything useful

Parser:
	stop_At;

next expr

	self.fail_if_at_end(";") //if i didn't find a semicolon but was supposed to

	self.tokens.next

	(type,  value) =by design, 

	first check if type is one of the things we should stop
		return "Stuff we already parsed so far"

	////////////////////
	big if else block on type of lex token

	if prev if None and type in ()
	else if type == operation
	else if type == "{"
	else if type == "("
	else if type == "="  

	////if prev is none, we havent hit any tokens yet

	if prev is none, and type in (number, string, symbol)
		return self.next_expr (myself) (type, value)

	if type = operation
		next = self.next_Expr(None)
		///get left hand and riht hand side of expression
		return self.next_Expr(("operation", value, prev, next))

	//call func
	if type == "("
		args = self.multi_expr(",",")")
		return self.next_exp(("Call",prev,args))

	//efine function
	if type == "{"
		params = self.parameterslist() //gets names of all arguments, simpler version of multi_exp, //MUST ALL BE SYBBOL
		body = multi_expre(";", "}")
		return self.next_expr(("function", params, body))

	if type == "="
		if prev[0] != symbol:
			raise Exception //can only assign to a symbol
		nxt = next_expr(None)
		return next_expr(("assignment", prev, nxt))


	else:
		raise Exception("unexpected token")

# Theorem Proving in Lean

```bash
import system.io
variable [io.interface]
open nat io

def hello_world : io unit :=
put_str "hello world there...\n"

#eval hello_world


#print axioms hello_world

def print_squares : ℕ → io unit
| 0        := return ()
| (succ n) := print_squares n >>
              put_str (nat.to_string n ++ "^2 = " ++ 
                       nat.to_string (n * n) ++ "\n")

#eval print_squares 4


meta def m91 : ℕ → ℕ
| n := if n > 100 then n - 10 else m91 (m91 (n + 11))

#eval m91 10

#eval m91 100

#eval m91 1000


meta def testComp : ℕ → ℕ
| n := if n = 1 then n else n

#eval testComp 1

meta def print_m91 : ℕ → io unit
| 0        := return ()
| (succ n) := print_m91 n >>
              put_str ("m91 " ++ nat.to_string n ++ " = " ++ 
                       nat.to_string (testComp n) ++ "\n")

#eval print_m91 4

meta def foo : ℕ → ℕ
| n := n + 1

#reduce foo
--#eval foo 1


//////////////////////

/- declare some constants -/
constant m : nat -- m is a natural number
constant n : nat
constants b1 b2 : bool -- declare two constants at once
/- check their types -/
#check m -- output: nat
#check n
#check n + 0 -- nat
#check m * (n + 0) -- nat
#check b1 -- bool
#check b1 && b2 -- "&&" is boolean and
#check b1 || b2 -- boolean or
#check tt -- boolean "true"
-- Try some examples of your own.


//////////////////////


/- declare some constants -/
constants m n : nat -- m is a natural number
constants b1 b2 : bool -- declare two constants at once
/- check their types -/
#check m -- output: nat
#check n
#check n + 0 -- nat
#check m * (n + 0) -- nat
#check b1 -- bool
#check b1 && b2 -- "&&" is boolean and
#check b1 || b2 -- boolean or
#check tt -- boolean "true"
-- Try some examples of your own.


----------------------------

constant f : nat → nat -- type the arrow as "\to" or "\r"
constant f' : nat -> nat -- alternative ASCII notation
constant f'' : ℕ → ℕ -- alternative notation for nat
constant p : nat × nat -- type the product as "\times"
constant q : prod nat nat -- alternative notation
constant g : nat → nat → nat
constant g' : nat → (nat → nat) -- has the same type as g!
constant h : nat × nat → nat
constant F : (nat → nat) → nat -- a "functional"

#check f -- N → N
#check f n -- N
#check g m n -- N
#check g m -- N → N
#check (m, n) -- N × N
#check p.1 -- N
#check p.2 -- N
#check (m, n).1 -- N
#check (p.1, n) -- N × N
#check F f -- N


constant func : ℕ → ℕ
constant test : (ℕ → ℕ) → ℕ

#check test func 

constant func2 : nat × nat → nat

constant test2 : (nat × nat → nat) → nat


#check func2
#check test2 


constants a b  : Type
constant F : Type → Type
constant G : Type → Type → Type


#check a -- Type
#check F a -- Type
#check F nat -- Type
#check G a -- Type → Type
#check G a b -- Type
#check G a ℕ -- Type



constants α β : Type

#check α × β -- Type
#check nat × nat -- Type

#check prod α β -- Type
#check prod nat nat -- Type



//////////////////////

#check fun x : nat, x + 5
#check λ x : nat, x + 5

constants α β : Type
constants a1 a2 : α
constants b1 b2 : β
constant f : α → α
constant g : α → β
constant h : α → β → α
constant p : α → α → bool
#check fun x : α, f x -- α → α
#check λ x : α, f x -- α → α
#check λ x : α, f (f x) -- α → α
#check λ x : α, h x b1 -- α → α
#check λ y : β, h a1 y -- β → α
#check λ x : α, p (f (f x)) (h (f a1) b2) -- α → bool
#check λ x : α, λ y : β, h (f x) y -- α → β → α
#check λ (x : α) (y : β), h (f x) y -- α → β → α
#check λ x y, h (f x) y -- α → β → α



//////////////////


#check fun x : nat, x + 5
#check λ x : nat, x + 5



constants α β c : Type
constants a1 a2 : α
constants b1 b2 : β
constant f : α → α
constant g : α → β
constant h : α → β → α
constant p : α → α → bool



#check h


#check fun x : α, f x -- α → α
#check λ x : α, f x -- α → α
#check λ x : α, f (f x) -- α → α
#check λ x : α, h x b1 -- α → α
#check λ Z : β, h a1 Z -- β → α



#check λ x : α, p (f (f x)) (h (f a1) b2) -- α → bool
#check λ x : α, λ y : β, h (f x) y -- α → β → α
#check λ (x : α) (y : β), h (f x) y -- α → β → α
#check λ x y, h (f x) y -- α → β → α


/////////////////////


#check fun x : nat, x + 5
#check λ x : nat, x + 5



constants α β c D : Type
constants a1 a2 : α
constants b1 b2 : β
constant f : α → α
constant g : α → β
constant h : α → β → α
constant p : α → α → bool



#check h


#check fun x : α, f x -- α → α
#check λ x : α, f x -- α → α
#check λ x : α, f (f x) -- α → α
#check λ x : α, h x b1 -- α → α
#check λ Z : β, h a1 Z -- β → α

--#check λ f : (f x)
#check fun testfunc : α, (α → D)

#check λ testfunc : c, D

#check λ x : α, p (f (f x)) (h (f a1) b2) -- α → bool
#check λ x : α, λ y : β, h (f x) y -- α → β → α
#check λ (x : α) (y : β), h (f x) y -- α → β → α
#check λ x y, h (f x) y -- α → β → α


/////////////////////


constants α β γ : Type
constant f : α → β
constant g : β → γ
constant b : β
#check λ x : α, x -- α → α
#check λ x : α, b -- α → β
#check λ x : α, g (f x) -- α → γ
#check λ x, g (f x)


#check λ b : β, λ x : α, x -- β → α → α
#check λ (b : β) (x : α), x -- β → α → α
#check λ (g : β → γ) (f : α → β) (x : α), g (f x)
-- (β → γ) → (α → β) → α → γ

#check λ (α β : Type) (b : β) (x : α), x
#check λ (α β γ : Type) (g : β → γ) (f : α → β) (x : α), g (f x)

```
