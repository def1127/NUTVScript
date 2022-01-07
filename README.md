# NUTVScript
NUTVScript is a custom interpreter designed to read .nutv code files that are formatted as film scripts.
This is an esolang.
Dont take this too seriously.
## How to write a program / language specifications
First line of file must be the name of the file.\
Second line must begin with "Written By:"\
Main function should be titled "Scene: main".\
Declare a function with the "Scene:" keyword\
Declare a variable (only integers allowed) with the "Enter:" keyword\
**Files must end with "Cut!"**\
To perform math, use the "Set" keyword\
Syntax is "Set [var] = [var] [+/-] [var]"\
Comments can be made only on their own line by starting the line with a # followed by a space.\

## Functions
Now this is very important, declare a function with the Scene: [name] keyphrase, if it doesn't look exactly like this, it won't be found by the interpreter.
Each function **MUST** contain a JUMPCUT: to the next function you want to run, failure to do this will cause the interpreter to keep running code past the end of your function and may cause unintended behavior.
