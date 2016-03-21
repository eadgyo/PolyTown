Lupas Rename v5.0 [1-Apr-2005]
  
1.Introduction
2.Features
3.Web
4.History
5.Code
6.License


==============
1.Introduction
==============
  
Lupas Rename is a freeware utility that allows you to rename a masive number of files easily.

The program works in Win2K/WinXP.


=================
2.Features  
=================
  
Lupas Rename Features

Lupas Rename has a lot of features. These features has been divided into three categories:


Basic features
--------------
Quick Preview 
Shell Integration (Lupas Rename from Here in folders and drives) 
Allow to UNDO the last rename operation 
Basic operations on the name of the filename and/or the extension 
Replace 
Search and Replace 
Insert text before/after or at a specific position 
Crop n characters from the start/end or at a specific position 
Convert to uppercase/lowercase 
Converto to uppercase the first letter of each word 
Converto to uppercase only the first letter of the name/extension 
Autonumber in Dec, Hex, Oct or Binary 
Rename only the selected files of the files list view 
Right menu on the text edits to help to rename by using tags 
Path history with navigation 
Show/Hide the icons of the files to improve speed on reading folders 
Show/Hide the filenames 
Show/Hide the folders 
Work/No work with folders (when visibles) 
Convert accent to non accents (àèìòù,âêîôû,äëïöü,áéíóú... -> aeiou) 
It renames files and/or folders 
Recursive mode allows to list all the files and/or folders under a path and their sub-paths 
Use text files to insert/replace the filename/extension with the lines of the file contents 
Save/Load the options to a INI file 
Save the preview contents to a ansi file 
Make a .BAT file with the renames for use it from a command shell 
It allows to rename the files without using the GUI interface 
It support several command line parameters. 


Extended features
-----------------
Support file sizes greater than 4Gb 
Change and remember the order of the columns in the file list view by dragging them 
Option to start the application always maximized 
Option to remember the size of the columns 
Option to remember the position and size of the program 
Option to remember the last path used 
Save all the config info in a external ini file, it only uses the registry for shell integration 
Add/Remove for folder shell integration, usually known as 'Lupas Rename from Here' 


Advanced features [TAGs]
------------------------
Contextual menu in the edit texts od the filename/extension tag dialog to help to insert TAGs 
Autorename by using any base from 2 to 36 
Autorename in manual mode, by using any characters and/or numbers 
Autorename in Excel mode 
Use image attributes [Width, Height, Bits and Colors]
Supported formats: JPG, GIF, BMP, PNG, ICO, CUR, PSD, TGA, TARGA, IFF, PCX, PCC, ILBM & LBM 
Use MP3 tags [Artist, Album, Song title, Year and Comments,Bitrate,Samplerate,Length,MpegVersion,MpegLayer...] 
Use data of any column [Dates, extension, type, path, sub-path...] 
Use the current date to format the name/extension 
Create random names of a specified text and using the specified characters 
It renames the extension for the CDisplay Comic Reader zip|rar <> cbz|cbr 
It allow to insert text from a external file to any pos of the name or the extension 
Calculate the CRC32 to insert in any pos of the name
Use the EXIF metadata to extract info from your jpeg photos

=====
3.Web
=====
  
You can find the last version in http://rename.lupasfreeware.org

Comments and/or bugs are welcome in the forum of the web page

  
=========
4.History
=========

v5.0 Relase

  .AutoSort column by pressing Ctrl-Up or Ctrl-Down from inside the file list view
  .Updated the chm file

v5.0 RC10

  .Autoresize edits in TabName & TabExtension
  .Added an Edit to insert a path where it can be used system variables like, it depends of the Windows system:

    %USERPROFILE% The current user's profile folder
    %ALLUSERSPROFILE% The All Users profile folder
    %ProgramFiles%    The Program Files folder 
    %SystemRoot%      The system root folder 
    %SystemDrive%     The system drive letter

  .Minimum requirements to run the application 800x600 screen
  .Added 'ÿÝýçÇñÑ' to the RemoveAccents function
  .Added the old style buttons to rename/undo and about
  .Added the old Check 'Only rename the selected files'


v5.0 RC9

  .Added a bigger edit for all the text fields that allow TAGs, Ctrl-Alt-E from inside the Edit Box
  .Added filters for ReadOnly - Hidden - System 
  .Moved the More Options tab dialog to an external Config Dialog
  .Added two new tags [Thanks to jherz]:
    .New TAG <FORMAT_NUMBER>  more info in the help file
    .New TAG <EXTRACT_NUMBER> more info in the help file

v5.0 RC8

  .Fixed a bug with the icons for Win9x, LupasRename works fine again with Win9x
  .Added a dialog to config the colors of the file list view and the preview window

v5.0 RC7

  .Now it allow to sort the column name as numbers [Thanks to jherz]
  .Now when pressing F1 will display the CHM help file [Thanks to Pivert]
  .Added import functions to the text editor, it can import all the files in the file list or from the preview window, or it can import the selected files from the file list window/preview window [Thanks to StormLogiX]
  .Fixed a bug with the PATH by using Command Line [Thanks to Garry] 
  .Added a new parameter 'RECURSIVE=1|0' by default 0 [Thanks to Garry]
  .Use GMT when inserting DateTime is now optional [Thanks to Thara Sompan]
  .Fixed a bug with CropAt [Thanks to Nick]
  .Regex in mask by inserting : before the mask [Thanks to the boost library]


v5.0 RC6

  .Added PRELIMINARY support for regular expressions in the Filemask by using the boost library.
  .Added posibility to use GMT or Local time when inserting the current date-time
  .Fixed a bug in the Crop At feature

v5.0 RC5

  .Added more options for the EXIF info.
  .Added TAG to normalize the filename to DOS 8.3 format
  .Added advanced filters

v5.0 RC4

  .Added support for EXIF metadata of jpeg photo files.
  .Added manual renaming of one file, just select the file and click F2


v5.0 RC3

  .Added a progress Window when reading folders in recursive mode, so if the process is going to be large you can cancel it.
  .Added a progress windows when the runtime preview is larger than 1,5 seconds, then if the process is too large you can cancel it.


v5.0 RC2

  HELP is needed to translate the program to others languages.

  Rewritten from scratch. Faster than never. 
  .Added a CHM file with all the TAGs [Previous TAGs are obsolete]
  .Added the posibility to drag the columns to be ordered as you will
  .Added a lot of parameters to work from the shell command
  .Added a path history navigation
  .Added the posibility to work with folders even in recursive mode
  .Added extra info from MP3 files, ID3v1 & ID3v2 Tags, and Bitrate, Samplerate, Channels, Length...
  .Added CRC32 by using TAGs
  .Added support for Icons & cursors
  .Added a lot more of features, just read the CHM file

  .Fixed: Cannot retrieve some Width and Height from JPGs
  .Fixed: Data form external files were limited to 32 chars.
  .Fixed: The format for the dates are retrieved from the windows configuration
  .Fixed: It allow to work with file sizes greater than 4 Gb

  .Removed: Support for TIF images (I think I will read better the EXIF info in the future)
  .Removed (Temporary): Support for RA audio files
  .Removed (Temporary): Support for Nintendo 64 roms
  .Removed (Temporary): Support for HTML files


v4.2b
  Corrected bug with WinXP & SP2, the files in the left view were hidden.

v4.2
  Added Support for auto-rename cbr-cbz <-> rar-zip automatically
  Added new option to remove the accent symbols like àáäâÀÁÄÂ to the same vocal without the accent symbol

v4.1

  Now the program saves the width columns state
  Added support to rename from zip/rar to the "CD Display Comic" extensions cbz/cbr
    Added support to rename from "CD Display Comic" extensions (cbr/cbz) to zip/rar

v4.0

Additions:
  Added option to rename only the selected files
  Corrected the search in Match Case

v3.5

Additions:
  Added Support to RA Files, thanks to Evgeny Efimov
  Added More Languages support updated for the new version with the help menu


v3.1

Additions:
  Support for Nintendo 64 ROMS
  Added a Big Menu by pressing right click in any TextBox to help you with the variables. At the moment only in English

Corrected:
  A bug when using variables with manual numbering in any base greater than 10. Corrected
  Other bugs.


v3.0

Translations:
  Translated into Polish by Dawid Wróbel. 

Corrected:
  ZeroFill now works fine with Binary, Oct and Hex Modes
  Some MP3 TAGs didn't read correctly, corrected! (Reported by Dawid Wróbel)

Added more Options for Manual Numbering
  Remember:
  \N, is the current number given by the autonumber settings.
  \ND, is the current number in Decimal format and ZeroFill given by the autonumber settings.
  \NH, is the current number in Hexadecimal format and ZeroFill given by the autonumber settings.
  \NB, is the current number in Binary format and ZeroFill given by the autonumber settings.
  \NO, is the current number in Octal format and ZeroFill given by the autonumber settings.
  if you want to specify another ZeroFill you must write just the number after the expression
  Example: \NB12 will write the number in Binary mode and with 12 ZeroFills.
  Maximum ZeroFill alowed is 64

  Now Also, Excel Mode (A,B,C...Z, AA,AB,AC...AZ, BA,BB..BZ,AAA,AAB...AAZ)
    \NE, will write the current number in Excel Mode

  Also, Excel Mode with the chars you specify in the Manual TextBox in Autonumbering Options, 'ABCD' ...
    \NEM, will write the current number in Excel Mode with the chars from Manual in Autonumbering
    For Example, if you write in the Manual Textbox in Autonumber 'ABCD',
    and you write \NEM the program will count: A,B,C,D,AA,AB,AC,AD,BA,BB,BC...
    if you write in the Manual Textbox in Autonumber 'MNO',
    and you write \NEM the program will count: M,N,O,MM,MN,MO,NM,NN,NO,OM,ON,OO,MMM,MMN,MMO...

  Remember: The modes \NE and \NEM doesn't work with ZeroFill.

Now Support any base for numbering:
   If you write 'A' and a number or letter after the '\N' you can specify any base number, for example:
   \NA, is the current number given by the autonumber settings.
   \NA2, will write the current number in base 2 (Binary)
   \NA3, will write the current number in base 3
   \NA8, will write the current number in base 8 (Octal)
   \NA0, will write the current number in base 10 (Decimal)
   \NAA, will write the current number in base A (11) (0,1,2,3,4,5,6,7,8,9,A)
   \NAB, will write the current number in base B (12) (0,1,2,3,4,5,6,7,8,9,A,B)
   \NAC, will write the current number in base C (13) (0,1,2,3,4,5,6,7,8,9,A,B,C)
   \NAF, will write the current number in base 16 (Hexadecimal) (0,1,2,3,4,5,6,7,8,9,10,A,B..,F,10)
   You can use values from 2 to Z, and after then you can also use the ZeroFill Value
   Example: \NA74 will write the current number in base 7 and will write 4 zeros at the left of the number.

Added More suboptions to the column's variables:
Filename
  \1, Column 1 Added 'N', to write only the Filename without extension.
  Example 1: \1 will write the filename with it's extension
  Example 2: \1N will write the filename without the extension

Size
\3, Column 3
  Added 'M' or 'K' to write the size in Megabytes or in Kilobytes.
  Added 'Z', to write the number only if the size is greater than 0
  Added ',' or '.' to format the size in miles. 
  Example 1: \3K will write the size in Kbytes.
  Example 2: \3KZ will write the size in Kbytes only if the size is greater than 0 bytes.

  Order: First you must use the chars 'M' or 'K' (Optional)
    After that you can use the char 'Z' (Optional)
    And therefore you can use ',' or '.' to format the size in thousands.

    Example with a file with size: 544209049
    Example 1: \3 will write the size of the filename: 544209049
    Example 2: \3M will write the size of the filename in Mb: 518
    Example 3: \3K will write the size of the filename in Kb: 513454
    Example 4: \3K, will write the size of the filename in Kb and formatted: 513,454
    Example 5: \3K. will write the size of the filename in Kb and formatted: 513.454
    Example 6: \3KZ, will write the size of the filename in Kb only if size is <> 0 and formatted: 513,454
    Example 7: \3Z will write the size of the filename if size <> 0, else will write nothing: 544209049


v2.7
Added more Image Formats
  TIF(PC and Macintosh)

Added Options
  All the functionality of the filename options in the extension options, now you can use the same options in each item, for example search-replace, cropping...

Bugs Corrected
  Corrected a bug when inserting after the extension. Reported by Tom
  Corrected a few bugs (images files with 0 bytes stopped loading...)

v2.6
Corrected a Bug with some formats of JPG when reporting Width, Height and Colors.
Added a Hint to indicate you how many files and folders are listed in the File List.
Added a Small Editor in 'More Options' from where you can write or load txt files and after use the variable '\T' to rename the files with the data text in the editor.
Added Decimal, Hexadecimal, Binary and Octal format for Autonumbering
Added more variables you can put in any TextBox, insert, replace...

  Added more Image Formats
    Amiga Interchange Format ILBM, LBM, IFF
    Deluxe Paint LBM

  Also added more extensions:
    JPEG, JFIF, JIF for JPG
    PCC for PCX
    TARGA, PIX for TGA

  Manual Numbering
    \N, is the current number given by the autonumber settings.
    \ND, is the current number in Decimal format and ZeroFill given by the autonumber settings.
    \NH, is the current number in Hexadecimal format and ZeroFill given by the autonumber settings.
    \NB, is the current number in Binary format and ZeroFill given by the autonumber settings.
    \NO, is the current number in Octal format and ZeroFill given by the autonumber settings.
    if you want to specify another ZeroFill you must write just the number after the expression
    Example: \NB12 will write the number in Binary mode and with 12 ZeroFills.
    Maximum ZeroFill alowed is 64

  Two Digits for the Year (Optional)
    In all the variables where you use the Year (by default yyyy), now you can format now to yy by writting '2' after the 'Y'
    Sample: '\DY2', will write the two digits of the year of the current date

  Editor
    \T, is the data in the Nº Line of the editor (from 'More Options') equivalent to the Nº line in the file list

  Html Format
    \H, HTML file Title

v2.5
Translated into Italian thanks to Andrea Palazzi
Corrected a few bug reported by Andrea Palazzi
Added Autonumbering by Directory when in Recursive Mode (Optional)
Added Make a UNDO file Batch Option available after renaming files.
Added New Columns
Columns Availables: Name, Path, Size, Type, Ext, Date Creation, Date Modification, Date Accessed, Attributes

Added Variables for Substitutions.

Columns and Dates:
  \N where N is the column number.
  if you write \1 the program will write the data item in the column 1.
  if you write \2 the program will write the data item in the column 2.
  More Specific:
  if in 'Search Text' you write 'XX' and in the 'New Text' you write '-Size \3 Ext \5-' the program will change the words XX by '-Size nnn Ext EXT-' where nnn is the file size and EXT the extension file. You can use \n for substitute by each data in any column.
  If you want to write the date text from the columns 6,7 and 8 (Creation, Modification and Accessed dates) there are this options:
  \6, \7 or \8, this will write yyymmdd (default), but if you want to be more specific then you can use:
  \6y, \6m, \6d, \6h, for write only the year, the month, the day or the time.
  Example, the modification file date (col 7) is 15 June 1972 at 12:15.
  if you write '\7d-\7m-\7y' the program will write: '15-06-1972'
  if you write '\7d\7m\7y' the program will write: '15061972'
  if you write '\7' then program will write: '19720615', by default the program will write in the format yyymmdd
  if you write '\7m-\7d, \7h' then program will write: '06-15, 1215'

MP3 Tags (only for MP3 files)
  \A = Title (default)
  \AT = Title
  \AA = Artist
  \AB = Album
  \AY = Year
  \AC = Comment
  Example, if you write '\AY, \A' then program will write the 'Year, Title' of the sound.

Graphic Formats (only JPG, GIF, PNG, BMP, PSD (Photoshop), PCX and TGA supported at the moment)
  \G = WidthxHeightxColors (default), ex: '800x600x16M'
  \GW = Width
  \GH = Height
  \GB = Bits
  \GC = Colors (by default 256, 32K, 65K or 16M) But if you want to specify the number colors then you can use \GCC
  \GCC = Colors without format.
  Example, a 800x600x65K image, if you write '\GHx\GBBits' then program will write '600x16Bits'.

Generate a Random Name
  \R = Random name (8 characters and numbers)
  \Rn = Random name (n characters and numbers, maximum 64)

Current Date
  \D = Current Date (default in 'yyyymmdd hhmmss')
  \DY = year (yyyy)
  \DM = month (mm)
  \DD = day (dd)
  \DH = Current Time (Default in 'hhmmss')
  \DHH = Hour (hh)
  \DHM = Minutes (mm)
  \DHS = seconds (ss)

Modified: Now when the Recursive Directories option is selected the program deactivates automaticaly the View Folders Option
Rewrited the code for the ComboBox Rutines.

v2.0.2a
The language panel is resized correctly when the size of the form is changed.
Translated into Português by Marcos F.Souza

v2.0.2
Corrected a few bugs, (After Renaming, the text boxes went into read-only mode).
Rewrote some routines to increment speed.

v2.0.1
Now Translated into German by Michael Quack.
Corrected a bug in 1024x768 or more with Font Size Selected bigger than 100%, Now it's resized correctly in all screen formats and in all font sizes.

v2.0
Now Translated into French by Herve Thouzard.
Now Translated into Dutch by Michiel Postuma.
Added: Now, when there are errors while renaming files, due to Windows, or some opened files due to other errors, the program shows a Window with a report of the files not renamed.

v1.9
The same as v1.8, but with icons in the preview Window.

v1.8 
It's the same version as v1.7, but now you can change the language from the program.
Now there are three languages at the moment: English, Spanish and Catalan.

v1.7
Added Work with Folders:
If you select the option 'Work With Folders' then the program uses the folders as if they were files.  Then the filter, the sort option and the rename option will affect the folders, too.
Also added is an option to hide the files that permits working only with folders.

If you work with 'View Folders' activated then you cannot use the 'Recursive' option.
The Recursive option only works with files, and requires that 'View Folders' be disabled.

Corrected: A bug with files without extension. Now it works fine.

v1.6
A few Bugs corrected, thanks to Carra Bussa:
After Save the Preview Window/Make Batch File/LR Options now return to its original path.
Added: Now you can move by pressing Ctrl-Tab or Shift-Ctrl-Tab to go to the next tab page or the previous tab page.
Added: Autonumber with Negative Numbers.

v1.5
Added: Shell Extension optional.
Corrected: Now you cannot enter invalid filenames in the edit text boxes.
  
v1.4  
Corrected some bugs in the GUI. 
Now allows rename of an individual file from the same window as visualization of files.  
When you move up or down with the cursors to select a file, now the corresponding file is selected correctly in the previsualisation window.  
Now on the option "Directory Recursive" toggles automatically to the state of Non Recursive.  
  
v1.3   
Removed: The use of the bookstore Filemanager Toolset v2.5. Now all this programmed exclusively without third people's bookstores, this way it has been possible to reduce the size from the executable one when only putting the characteristics and options that are necessary to the program.  
Added: The option of Automatic, Directory Sort Recursive, Order for any upward or descending column.  
  
v1.0 Final Version (non beta)  
Added: Emergent menu with more options by pressing the right button of the mouse. 
Added: Guardar/Cargar the options to a file INI.  
Corrected small bugs with the environment: To maximize, redimension...  
  
v0.8.1b  
Added: To generate a batch (.BAT) for a renowned manual from TWO  
Added: To refresh  
  
v0.8b  
Added: The window of the program is now redimensionable.  
Added: To save the content from the previsualization window to a File .TXT  
Added: To begin with the Maximized window.  
Added: Remember the last working Directory.  
Added: Remember the size and position of the program.  
  
v0.5b  
Added: Undo  
Added: Multi-filters (separated by point and coma, eg: * .txt; * .exe;??? .doc)  
  
v0.3b (First Beta Publishes)  
Options of File  
Filter for any mask  
To replace the name for another.  
To replace a text specified for another inside the named file.  
To clip n characters to the left or the right.  
To insert any text before, or after, the name.  
To convert to UPPERCASE/lowercase or Capital  
To insert Autonumbering.  
Autonumber: To begin with the number n  
Autonumber: To increase every time po n  
Autonumber: To specify the zeros, eg 001 or 0001 or 01...  
  
Options of the Extension  
To replace for any other one  
To insert any text before or after the extension.  
To convert to UPPERCASE/lowercase or Capital  


======
5.Code  
======
  
This program is coded entirely usign Visual C++ 6.

  
=========
6.License
=========

You are free to use this program as you see fit, however an Email or Postcard would be nice.

Lupas Rename may be freely distributed as long as the files in this archive are unchanged and no fee is charged for its distribution. No part of this program may be reverse engineered, dissasembled, decompiled, or be used as part of another program.

Lupas Rename is provided "as is" and without any warranty. The author cannot be held responsible for anything that happens to you or your equipment. Use it at your own risk.

By using Lupas Rename, you agree to the terms of this license.

  
=========
Copyright  
=========

Lupas Rename is Copyright 1999-2005 Ivan Anton Albarracin
  
  
===============
Acknowledgments
===============

To David Amigo for his experience in Visual C++

To Giulio Fornasar for the Italian translation
To Sylvain MAHINC for the French translation
To H.C. van der Burg for the Dutch translation

To my brother Noel Anton for the times that I have bothered him with this program.

To my friend Xavi Pallicera, for the whole help in programming (among other things)

and:

Ingo Eckel for their excellent work with their bookstore Filemanager Toolset v2.5 of which I have learned too much.
Hervé Thouzard by his old French translation. 
Michiel Postuma by his old Dutch translation.
Michael Quack by his old German translation.
Marcos F. Souza by his old Portuguese translation.
Andrea Palazzi by his old Italian translation, his reports and his tests.
Dawid Wróbel by his old Polish translation.
Joan Antelman by his English corrections.

To anyone that uses this program, for the trust in this small program.