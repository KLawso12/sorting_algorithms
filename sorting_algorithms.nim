import std/os
import std/strutils
import std/osproc

if(paramCount() < 3):
    echo "error, less than 2 items, nothing to sort"
    quit(QuitSuccess)



var input = parseInt(paramStr(1))

var inputstr: string

case input:
    of 1:
        echo "selected algorithm: bubble (string)"
        if(defined(windows)):
            inputstr = ".\\bubble_str." & ExeExts[0]
        else:
            inputstr = "./bubble_str"
        inputstr &= " "
    of 2:
        echo "selected algorithm: bubble (double)"
        if(defined(windows)):
            inputstr = ".\\bubble_num." & ExeExts[0]
        else:
            inputstr = "./bubble_num"
        inputstr &= " "
    else:
        echo "not a valid selection"
        quit(QuitFailure)

for i in 2..paramCount():
    inputstr &= (paramStr(i))
    if(i == paramCount()):
        break
    inputstr &= " "


discard execCmd(inputstr)
quit(QuitSuccess)
