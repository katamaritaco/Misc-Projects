###
# This Makefile can be used to make a parser for the CSX language
# (parser.class) and to make a program (P3.class) that tests the parser and
# the unparse methods in ast.java.
#
# make clean removes all generated files.
#
###

JC = javac

P5.class: P5.java parser.class Yylex.class ASTnode.class
	$(JC) -g P5.java

parser.class: parser.java ASTnode.class Yylex.class ErrMsg.class
	$(JC) parser.java

parser.java: CSX.cup
	java java_cup.Main < CSX.cup

Yylex.class: CSX.jlex.java sym.class ErrMsg.class
	$(JC) CSX.jlex.java

ASTnode.class: ast.java
	$(JC) -g ast.java 

CSX.jlex.java: CSX.jlex sym.class
	java JLex.Main CSX.jlex

sym.class: sym.java
	$(JC) -g sym.java

sym.java: CSX.cup
	java java_cup.Main < CSX.cup

SymTable.class: SymTable.java
	$(JC) -g SymTable.java

ErrMsg.class: ErrMsg.java
	$(JC) ErrMsg.java

###
# clean
###
clean:
	rm -f *~ *.class parser.java CSX.jlex.java sym.java

###
# test
###
test:
	java P5 test.csx test.out
	cat test.out
errors:
	java P5 typeErrors.csx typeErrors.out

beck:
	java P5 becksCascade.csx  beck.out #we only want the error output

	
