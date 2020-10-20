#!/bin/bash

# is c/cpp file
function isCppFile(){
    file=$1
    # .c$: .代表任意字符，使用\.转义
    result=$(echo $file | grep "\.c$")
    if [ -n "$result" ]; then
        return 1;
    fi
    
    result=$(echo $file | grep "\.cpp$")
    if [ -n "$result" ]; then
        return 1;
    fi
    
    result=$(echo $file | grep "\.h$")
    if [ -n "$result" ]; then
        return 1;
    fi
    
    result=$(echo $file | grep "\.hpp$")
    if [ -n "$result" ]; then
        return 1;
    fi
    
    return 0;
}

function formatFile(){
    file=$1
    isCppFile $file
    isC=$?
    if [ "$isC" -eq "1" ]; then
        # install apk in background
        {
            # echo "format c file $file"
            # formatRet=`clang-format $file`
            # # 格式化后的代码覆盖写入
            # echo $formatRet > $file
            clang-format -style=llvm -i $file
        }
    fi
}

function foreachFile(){
    directory=$1
    # echo "####" $directory
    for file in `ls $directory`
    do
        aFile=$directory/$file
        if [ -d $aFile ]
        then
            foreachFile $aFile &
        else
            #     echo $file is file
            formatFile $aFile
        fi
    done
}

directory=$PWD
echo now path: $directory
foreachFile $directory


