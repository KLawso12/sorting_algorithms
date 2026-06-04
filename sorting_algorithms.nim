import std/os
import std/strutils
import std/osproc

if(paramCount() < 2):
    echo "error, less than 2 items, nothing to sort"
    quit(QuitSuccess)


echo "Choose your sorting algorithm:"
echo "1. Bubble sort"

var input = parseInt(readLine(stdin))

var inputstr: string

case input:
    of 1:
        if(defined(windows)):
            inputstr = ".\\bubble." & ExeExts[0]
        else:
            inputstr = "./bubble"
        inputstr &= " "
    else:
        echo "not a valid selection"
        quit(QuitFailure)

for i in 1..paramCount():
    inputstr &= (paramStr(i))
    if(i == paramCount()):
        break
    inputstr &= " "


discard execCmd(inputstr)
quit(QuitSuccess)
