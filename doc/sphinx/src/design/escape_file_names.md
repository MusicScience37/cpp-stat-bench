# Escaping file names

In this library, user-specified names are used in file names.
So a function to escape file names is required.

| Code | Character | Allow in This Library | Usability in Windows | Usability in Ubuntu | Notes                                          |
| ---: | :-------- | :-------------------- | :------------------- | :------------------ | :--------------------------------------------- |
|   00 | (NUL)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   01 | (SOH)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   02 | (STX)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   03 | (ETX)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   04 | (EOT)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   05 | (ENQ)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   06 | (ACK)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   07 | (BEL)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   08 | (BS)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   09 | (HT)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   0A | (LF)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   0B | (VT)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   0C | (FF)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   0D | (CR)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   0E | (SO)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   0F | (SI)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   10 | (DLE)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   11 | (DC1)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   12 | (DC2)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   13 | (DC3)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   14 | (DC4)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   15 | (NAK)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   16 | (SYN)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   17 | (ETB)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   18 | (CAN)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   19 | (EM)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   1A | (SUB)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   1B | (ESC)     | ×                     | ×                    | ×                   | C0 control.                                    |
|   1C | (FS)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   1D | (GS)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   1E | (RS)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   1F | (US)      | ×                     | ×                    | ×                   | C0 control.                                    |
|   20 | (space)   | ×                     | ○                    | △                   | Quotation is needed.                           |
|   21 | !         | ○                     | ○                    | ○                   |                                                |
|   22 | "         | ×                     | △                    | △                   | Used as quotation.                             |
|   23 | #         | ×                     | ○                    | △                   | Used in comments.                              |
|   24 | $         | ×                     | ○                    | △                   | Used in variables.                             |
|   25 | %         | ×                     | △                    | ○                   | Used in variables.                             |
|   26 | &         | ×                     | ○                    | △                   | Used in shell.                                 |
|   27 | '         | ×                     | ○                    | △                   | Used as quotation.                             |
|   28 | (         | ×                     | ○                    | △                   | Used in shell.                                 |
|   29 | )         | ×                     | ○                    | △                   | Used in shell.                                 |
|   2A | \*        | ×                     | ×                    | △                   | Prohibited in Windows and used in shell.       |
|   2B | +         | ○                     | ○                    | ○                   |                                                |
|   2C | ,         | ×                     | △                    | △                   | Used as separators in some command line tools. |
|   2D | -         | ○                     | ○                    | ○                   |                                                |
|   2E | .         | ×                     | △                    | △                   | Confused with separator of extensions.         |
|   2F | /         | ×                     | ×                    | ×                   | Used as path separator.                        |
|   30 | 0         | ○                     | ○                    | ○                   |                                                |
|   31 | 1         | ○                     | ○                    | ○                   |                                                |
|   32 | 2         | ○                     | ○                    | ○                   |                                                |
|   33 | 3         | ○                     | ○                    | ○                   |                                                |
|   34 | 4         | ○                     | ○                    | ○                   |                                                |
|   35 | 5         | ○                     | ○                    | ○                   |                                                |
|   36 | 6         | ○                     | ○                    | ○                   |                                                |
|   37 | 7         | ○                     | ○                    | ○                   |                                                |
|   38 | 8         | ○                     | ○                    | ○                   |                                                |
|   39 | 9         | ○                     | ○                    | ○                   |                                                |
|   3A | :         | ×                     | ×                    | ○                   | Prohibited in Windows.                         |
|   3B | ;         | ×                     | ○                    | △                   | Used in shell.                                 |
|   3C | <         | ×                     | ×                    | △                   | Prohibited in Windows and used in shell.       |
|   3D | =         | ×                     | △                    | △                   | Used as separators in some command line tools. |
|   3E | >         | ×                     | ×                    | △                   | Prohibited in Windows and used in shell.       |
|   3F | ?         | ×                     | ×                    | ○                   | Prohibited in Windows.                         |
|   40 | @         | ○                     | ○                    | ○                   |                                                |
|   41 | A         | ○                     | ○                    | ○                   |                                                |
|   42 | B         | ○                     | ○                    | ○                   |                                                |
|   43 | C         | ○                     | ○                    | ○                   |                                                |
|   44 | D         | ○                     | ○                    | ○                   |                                                |
|   45 | E         | ○                     | ○                    | ○                   |                                                |
|   46 | F         | ○                     | ○                    | ○                   |                                                |
|   47 | G         | ○                     | ○                    | ○                   |                                                |
|   48 | H         | ○                     | ○                    | ○                   |                                                |
|   49 | I         | ○                     | ○                    | ○                   |                                                |
|   4A | J         | ○                     | ○                    | ○                   |                                                |
|   4B | K         | ○                     | ○                    | ○                   |                                                |
|   4C | L         | ○                     | ○                    | ○                   |                                                |
|   4D | M         | ○                     | ○                    | ○                   |                                                |
|   4E | N         | ○                     | ○                    | ○                   |                                                |
|   4F | O         | ○                     | ○                    | ○                   |                                                |
|   50 | P         | ○                     | ○                    | ○                   |                                                |
|   51 | Q         | ○                     | ○                    | ○                   |                                                |
|   52 | R         | ○                     | ○                    | ○                   |                                                |
|   53 | S         | ○                     | ○                    | ○                   |                                                |
|   54 | T         | ○                     | ○                    | ○                   |                                                |
|   55 | U         | ○                     | ○                    | ○                   |                                                |
|   56 | V         | ○                     | ○                    | ○                   |                                                |
|   57 | W         | ○                     | ○                    | ○                   |                                                |
|   58 | X         | ○                     | ○                    | ○                   |                                                |
|   59 | Y         | ○                     | ○                    | ○                   |                                                |
|   5A | Z         | ○                     | ○                    | ○                   |                                                |
|   5B | [         | ×                     | ○                    | △                   | Used in shell.                                 |
|   5C | \\        | ×                     | ×                    | ×                   | Used as path separator.                        |
|   5D | ]         | ×                     | ○                    | △                   | Used in shell.                                 |
|   5E | ^         | ○                     | ○                    | ○                   |                                                |
|   5F | \_        | ○                     | ○                    | ○                   |                                                |
|   60 | `         | ×                     | ○                    | △                   | Used as quotation.                             |
|   61 | a         | ○                     | ○                    | ○                   |                                                |
|   62 | b         | ○                     | ○                    | ○                   |                                                |
|   63 | c         | ○                     | ○                    | ○                   |                                                |
|   64 | d         | ○                     | ○                    | ○                   |                                                |
|   65 | e         | ○                     | ○                    | ○                   |                                                |
|   66 | f         | ○                     | ○                    | ○                   |                                                |
|   67 | g         | ○                     | ○                    | ○                   |                                                |
|   68 | h         | ○                     | ○                    | ○                   |                                                |
|   69 | i         | ○                     | ○                    | ○                   |                                                |
|   6A | j         | ○                     | ○                    | ○                   |                                                |
|   6B | k         | ○                     | ○                    | ○                   |                                                |
|   6C | l         | ○                     | ○                    | ○                   |                                                |
|   6D | m         | ○                     | ○                    | ○                   |                                                |
|   6E | n         | ○                     | ○                    | ○                   |                                                |
|   6F | o         | ○                     | ○                    | ○                   |                                                |
|   70 | p         | ○                     | ○                    | ○                   |                                                |
|   71 | q         | ○                     | ○                    | ○                   |                                                |
|   72 | r         | ○                     | ○                    | ○                   |                                                |
|   73 | s         | ○                     | ○                    | ○                   |                                                |
|   74 | t         | ○                     | ○                    | ○                   |                                                |
|   75 | u         | ○                     | ○                    | ○                   |                                                |
|   76 | v         | ○                     | ○                    | ○                   |                                                |
|   77 | w         | ○                     | ○                    | ○                   |                                                |
|   78 | x         | ○                     | ○                    | ○                   |                                                |
|   79 | y         | ○                     | ○                    | ○                   |                                                |
|   7A | z         | ○                     | ○                    | ○                   |                                                |
|   7B | {         | ○                     | ○                    | ○                   |                                                |
|   7C | \|        | ×                     | ×                    | △                   | Prohibited in Windows and used in shell.       |
|   7D | }         | ○                     | ○                    | ○                   |                                                |
|   7E | ~         | ○                     | ○                    | ○                   |                                                |
|   7F | (DEL)     | ×                     | ×                    | ×                   | Control character.                             |

| Symbol | Meaning                                  |
| :----- | :--------------------------------------- |
| ×      | Not allowed.                             |
| △      | Allowed, but some care is needed to use. |
| ○      | Allowed.                                 |
