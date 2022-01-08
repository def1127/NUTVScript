# NUTVScript
NUTVScript is a custom interpreter designed to read .nutv code files that are formatted as film scripts. This is an esolang.

LET THE RECORD REFLECT THAT I STARTED THIS ON 01/05/22 AND HAVE A MVP ON 01/07/22

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
All functions including main must end with Cut!\
To print out to the console, use the "Exclaim " keyword followed by your string. You can print out variables by preceding the variable name with a '%'. If you want to print out a '%' without referencing a variable, use '/%'. You cannot exclaim a variable in the middle of the word, the variable must be its own separate word from the rest of the string. (ex. "Exclaim Variable /%a is set to %a" is valid, but "Exclaim variable /%a is set to%a" will not work as intended, and will not throw an error)

## Functions
Now this is very important, declare a function with the Scene: [name] keyphrase, if it doesn't look exactly like this, it won't be found by the interpreter.
Each function **MUST** contain a JUMPCUT: to the next function you want to run, failure to do this will cause the interpreter to keep running code past the end of your function and may cause unintended behavior.
