# wxEmuArm

This is a toy program that emulates some commands of the cpu.
It is a rewrite in CPP from the earlier EmuArm. It can now read in the file with instructions and go throught them step by step.
It is modelled after early arm architecture - having 15 general purpose 32-bit registers.
Also the commands are arm-like.
I implemented it with the thought of programing my own, more exotic bit operations and checking if they can be useful for something.
You can think about commands "count leading zeros" or "count bits set to 1" as examples of recently introduced binary operations that proved to be useful, but have not been widely implemented before.

![Screenshot](https://github.com/mkudla/wxEmuArm/blob/master/program.png)


## Compilation

It requires wxWidgets 2 library
The project uses code blocks IDE and it compiles succesfully under linux.

## Commands

mov register value
    - moves value to target register, ex: mov 3 2653
    
shr register shiftvalue
    - shifts target register right by shiftvalue , ex: shr 3 2

shl register shiftvalue
    - shifts target register left by shiftvalue , ex: shr 3 2

add register1 register2 targetregister
    - adds register1 register2 and puts output in targetregister, ex: add 3 2 5


sub register1 register2 targetregister
    - subs register1 register2 and puts output in targetregister, ex: sub 3 2 5

mul register1 register2 targetregister
    - multiplies register1 register2 and puts output in targetregister, ex: mul 3 2 5

xor register1 register2 targetregister
    - performs exclusive or operation between register1 and register2 and puts output in targetregister, ex: xor 3 2 5

and register1 register2 targetregister
    - performs and operation between register1 and register2 and puts output in targetregister, ex: and 3 2 5

    
## Implemented buttons

quit - quits program
load - loads program from file
step - executes program from the file one by one

