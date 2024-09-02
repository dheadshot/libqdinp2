# libqdinp2
## The Quick and Dirty Input Library version 2

### Quick Notes for Compiling the Quick and Dirty Input Library:
* The library now works under Windows!  To use, define either `WIN32` or `WIN64` (depending on whether you are compiling for 32 or 64 bit Windows) and if your C runtime library does not support new-line translation then also define `NOTRANSLATE`.
* To compile on older *nixes like Coherent, define `COHERENT`.


### About the Quick and Dirty Input Library:
The Quick and Dirty Input Library began as part of "FREDLIN", a free version of "EDLIN" for Linux.  FREDLIN was written in 2015, based on ideas dreamt up in the time between 2010 and then, by DHeadshot.  In 2016, it was spun out as a separate project and in 2017 made open-source.  Windows support was introduced in 2022.

The library uses the original 86-DOS (AKA QDOS, the Quick and Dirty Operating System) "Template" system for input, albeit with different Ctrl actions (for Linux compatibility) and some additional customisation for the PC keyboard.

#### The Functions:
There are a number of functions available in the library.  This is a brief description of each of them.

* `qdinpver`: Returns the library version number as a string.
* `setmodsasfuncs`: Enables the "modsasfuncs" functionality.  This causes modifiers of function keys to be interpreted as additional function keys.
* `resetmodsasfuncs`: Disables the "modsasfuncs" functionality.  This means that modifiers of function keys will be passed as the modifier code "ORed" with the function key code.
* `getterm`: This should be called at the beginning of the program as it sets the internal variable to the identity of the user's terminal (or terminal emulator), so that the library will behave properly.
* `cls`: Clears the screen (of stdout).
* `qdgetch`: A little hack that waits for a keypress and returns it immediately.  If the key code is made of multiple strokes (e.g. a function key), qdgetch must be called additional times for each stroke.  This routine was based on "mygetch", created by VvV and kermi3 on the CProgramming.com boards.
* `regsiginthandler`: Registers the SIGINT handler that should be used if Ctrl+C is to be used to break out of inputs instead of Ctrl+D (thus freeing Ctrl+D to be used as an EOF character).  The function readqdline will execute this function itself if required, so this is best used if something goes wrong or you wish to roll your own function.
* `deregsiginthandler`: Deregisters the SIGINT handler described above.  The function readqdline will execute this function itself if required, so this is best used if something goes wrong or you wish to roll your own function.
* `gotoansixy`: Move the cursor to a given screen (x,y) co-ordinate, with the top-left of the screen as (1,1).
* `getansicursorpos`: Retrieve the row and column (y,x) of the position of the cursor onscreen, with the top-left of the screen as (1,1).
* `pushtotabstack`: Adds a tab-distance to the tabstack.
* `popfromtabstack`: Retrieves a tab distance from the tabstack.
* `cleartabstack`: Clears the tabstack.
* `writetab`: Outputs a tab character to stdout.
* `termbsn`: Performs a specified number of backspaces on the user's terminal, properly clearing what was typed before.  In version 1 of the library, this was "termbs", which only performed a single backspace.  A macro definition has been provided for compatibility with this.
* `writechar`: Write a single character to stdout and (on Windows) update the internal co-ordinate system.
* `writestr`: Write a string to stdout and (on Windows) update the internal co-ordinate system.
* `qdinstrch`: A function that finds the offset of a specified character within a target string, starting its search at a specified offset.
* `firstletter`: This function returns the character code of the first letter found in a specified string.  This function is used a lot in the command system for FREDLIN, but is provided here to support some of the supplementary functions of the library.
* `getkeyn`: The heart of the library, this function waits for a keypress and then returns a code representing the entire keypress, even if it is comprised of multiple keystrokes (e.g. a function key or escape sequence).  The codes are defined in the header file and detailed at the beginning of the main module.
* `readqdline`: This function is the full templating input function that makes the library.  It is described properly later on, but parameter-wise, it is given the memory location to place the outputted string (up to 256 characters), the template and an argument specifying whether to use the Ctrl+D sequence instead of Ctrl+C to cancel input.  If this is set to 1, SIGINT will not be changed and thus it can be used by other functionality in your program.  If it is set to 0, SIGINT will be changed for the duration of the function before being set back to the default.  The advantage of a value of 1 is that SIGINT can be used for your own functionality.  The advantage of a value of 0 is that Ctrl+D (and thus the EOF character) can be entered as an input.  The function returns 0 if everything went OK, 3 or 4 if the user cancelled text entry (depending on whether they used Ctrl+C or Ctrl+D), or -1 if the registration of the signal handler failed.  In version 1 of the library, this function was called "readline", which would conflict with other libraries.  As such it has been changed, however if compatibility with version 1 is required, it is advisable to define a header macro called "readline" that points to this function.
* `NEWreadqdline`: This function will eventually replace readqdline (and be called readqdline, with the old readqdline being renamed OLDreadqdline).  Essentially, it is readqdline without the 255 character limit (the limit is specified in an argument) and made more efficient.  Refer to readqdline for information on functionality and to the source code for information on the specifics.
* `keypause`: A supplementary function, this writes a message inviting the user to press a key to continue, awaits a keypress, then removes the message from the screen.
* `yesnomsg`: A supplementary function, this writes a specified message to the screen and then awaits an inputted line as an answer where the first letter is a "y" or "n" before returning.  It uses the readqdline function for this and will only return once it has a yes or no answer (represented by a 1 or 0 return).
* `NEWyesnomsg`: A supplementary function, this is a variant of `yesnomsg` that takes into account the use of cancelling text entry through Ctrl+C or Ctrl+D.
* `DoNothing`: A supplementary function that does nothing.  Can generally be ignored.
* `GiveOne`: A supplementary function that outputs 1.  Can generally be ignored.

##### Windows-Only Functions
There are some Windows-only functions that are largely for internal use but are exposed by the library in case needed.  They are detailed below:

* `SetCursorState`: Set the cursor size and visibility on stdout.
* `SetCursorPos_`: Set the cursor position by co-ordinates (x,y), with the top-left as (0,0) (not to be confused with the (1,1)-based system used by `gotoansixy`).
* `SetTextColour`: Set the colour of the text on stdout.
* `GetFgTextColour`: Get the current foreground text colour on stdout.
* `GetBgTextColour`: Get the current background text colour on stdout.
* `GetWinSize`: Get the current size of the text window of stdout.
* `GetCursorPos_`: Get the cursor position by co-ordinates (x,y), with the top-left as (0,0) (not to be confused with the (y,x), (1,1)-based system used by `getansicursorpos`).
* `GetCursorAttribs`: Get the current cursor attributes on stdout.
* `setcvars`: Update the internal co-ordinate system.
* `keytranslate`: Convert a Windows key-state into a Quick and Dirty Input Library key number.
* `GetKeynWin`: Read a keypress from stdin.


##### qdgetch Modes

There are several modes that can be used with qdgetch:

Mode 0. Block (the default)
Mode 1. Poll
Mode 2. Get Immediate (Has timeout)
Mode 3. Signals Disabled
Mode 4. Like 2. but with more stripping: cleans the bytes, doesn't allow XOn/XOff, disables legacy terminal functionality


#### The Quick and Dirty Input Library Template System:
The library uses a "Template" system for input.  When using the library for the user to enter a command, the template is recommended to be the last command the user typed.  When using the library for a user to enter text, the template is recommended to be the original contents of the text.  As the user types, the current position in the template is advanced unless "Insert Mode" is on.

The following key combinations work with the template:

Key  Combination | Description
---------------- | -----------
ESC S or F1 | This copies one character from the template to the current line.
ESC T or F2 | This must be followed by a character and copies all characters from the template up to but not including the next occurrence in the template of the specified character.  If the specified character does not occur from the current point in the template onwards, no characters are copied to the line and the position in the template does not advance.
ESC U or F3 | This copies all remaining characters from the template to the line.
ESC V or F4 | This skips over one character in the template.
ESC W or F5 | This must be followed by a character.  It skips over all characters in the template, up to but not including the next occurrence of the specified character in the template after the current point.  If the specified character does not appear, no characters are skipped.
ESC P | This turns on "Insert Mode".  In this mode, as characters are typed to the line, the current position in the template does not advance.
ESC Q | This turns off "Insert Mode".  Outside of this mode, the position in the template is advanced for each character typed to the line.  This is the default mode.
INS | This toggles "Insert Mode" on and off.  By default, it is off.
ESC R or F8 or ESC Return | This changes the template to be the current line.  The current line as typed into the buffer is cleared and "Insert Mode" is turned off.  On the screen, an At sign ("@") is written followed by a new line.  This does not affect the string provided to the function as the library maintains an internal template string.

The entered text ends with a new line keypress, the new line character (LF) being included in the text that is assigned to the target string.  The maximum length of inputted text is 255 characters, however a user can make text "wrap" to a new line if the programmer provides another call to the readqdline function.  To do this, the user must end the inputted text with a CTRL+Y.  This submits the text without the new line character appended to the end.

The user can clear the current line and start again by pressing CTRL+X.

The user can cancel the current line by pressing CTRL+D if the readqdline function was called with eofiscancel set to 1, or by pressing Ctrl+C if eofiscancel was set to 0.  This will cancel entering text, discarding any text written so far.  Any lines of text entered previously will not be affected as these would be from different calls to the readqdline function.  The yesnomsg function cannot be terminated in this way.

CTRL+L inserts a formfeed character into the text (displayed as an inverted L on the user's terminal), which can be used as a special character in an input line.

If a user simply wishes to enter the template as the submitted text, they simply have to press F3, as used in the template system of not only 86-DOS (AKA QDOS) but also basically every version of MS-DOS, PC-DOS, DR-DOS etc ever made.


#### The Original "About FREDLIN" Help Text from the FREDLIN Program (as written by DHeadshot in 2015):
The idea for FREDLIN arose in 2010 with my desire for "ed" to be easier to use.  It was my first time editing in Linux with the command line and only "ed" and "vi" were available.  I have never been able to get on with "vi", so I was left struggling with "ed".

The DOS line editor "EDLIN" was created by Tim Paterson (the genius behind the original release of DOS) in about 1980.  It has long been a simple-to-use line editor and I thus quickly identified it as a good replacement, at least for what I was doing.  I searched long and hard online to try to see if there was any project to port it across, but in vain.

Years later, I decided to port it across.  I thought I might be onto something when I found the source online for the FreeDOS version, however the author had changed too much of the program for my taste.  I even looked at disassembling the original program, but didn't get very far.  In the end, I decided to re-write it from scratch.

I had to change a few Ctrl actions for compatibility with the Linux platform and write a new line-entry system to support the original 86-DOS "Template" system, but the result you see before you: the result of five years of procrastination, plus a couple of week's work.

Please note that this is the first program I've written in C in four years, so apologies if it is not as efficient as it could be.

_Please note that since this was written, my C has improved immensely and thus this library is a lot more efficient than that original program._


### Credits:
2015-17 DHSC, 2017-?? The Quick and Dirty Input Library Project

This library is free open source code - use and distribute it as you like.  The only real requirement is that in the credits of your program you mention that the library was used and provide a link back to [the github site](https://github.com/dheadshot/libqdinp2).

The "mygetch" routine was created by VvV and kermi3 on the CProgramming.com boards, so thanks to them for that.

The library was inspired by the original 86-DOS templating system created by Tim Paterson of SCP.  None of his code or that of Microsoft has been used in this library though.
