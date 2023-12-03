# Change Background
A command that allows you to change the Windows Terminal background from the command line.

# Setup
You can compile locally or download the provided exe.
Place the exe somewhere your system environment variable will pick up.

The command loads a list of potential image options when it is called.
The file for this should be called images.txt and be located in the same folder as the Windows Terminal settings:
%USERPROFILE%\AppData\Local\Packages\Microsoft.WindowsTerminal_8wekyb3d8bbwe\LocalState
Formatting for this file is as follows:
Each image entry should be on a seperate line.
Each image entry should contain a name, followed by any number of commas and spaces, and a filepath to a image file (in quotation marks).
The file should look something like this:

[name 1] [ , | _ ] ["image path 1 in quotes"]

[name 2] [ , | _ ] ["image path 2 in quotes"]

[name 3] [ , | _ ] ["image path 3 in quotes"]

I have included a sample images.txt in the files, and the command has built in documentation for this. 

Try passing the arguments --help --format.

# Usage
There are three options you will mainly use with this command. If you pass no arguments to the command, it will
change all of your set background images (Command line profiles you have a image set on) to a random background
in your images.txt file. If you pass the argument -r to the command, each set background image will be changed to
another random image from the images.txt file. If you pass a name that exists in your images.txt file, all set
background images will be changed to the image file associated with that name. If you attempt to pass a name 
that is spelling incorrectly, you will get a list of all the potential names. You can also get this list by
passing the argument --names or -n to the command. 
There is also a pretty nice set of help commands. Try --help.
# Demo
Yes my backgrounds are nice, thank you :)





