rm -rf build
mkdir "build/gen_src"
java -cp lib/ JLex.Main src/Main.lex
mv src/Main.lex.java build/gen_src/Yylex.java
java -jar lib/java-cup-11b.jar src/Main.cup
mv parser.java build/gen_src/parser.java
mv sym.java build/gen_src/sym.java
javac -cp lib/java-cup-11b.jar -d build build/gen_src/parser.java build/gen_src/sym.java build/gen_src/Yylex.java