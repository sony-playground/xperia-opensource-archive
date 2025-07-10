#!/bin/bash

response() {
    if [ $1 == "-s" ]; then
        fastboot_get "_tmp_out" ${#2}
        diff "$HOST_TMP_DIR/_tmp_out" <(echo "$2"|tr -d '\n')
        if [ $? -ne 0 ]; then
            echo -ne "${RED}Invalid response, got:\n   "
            cat $HOST_TMP_DIR/_part
            echo -e ""
            echo -e "Should be:"
            echo -e "   $2${NC}"
            return 1
        fi
    elif [ $1 == "-f" ]; then
        fastboot_get "_tmp_out" "$3"
        mv "$HOST_TMP_DIR/_tmp_out" "$HOST_TMP_DIR/$2"
    else
        echo -e "${RED}$1 option not supported${NC}"
        return 1
    fi
    return 0
}

strindex() {
    x="${1%%$2*}"
    [[ "$x" = "$1" ]] && echo 255 || echo "${#x}"
}

exec_script() {
    while read -r line || [[ -n "$line" ]]; do
        [[ -z $line ]] && continue
        read -ra word <<< "$line"
        echo "$line"
        if [ ${word[0]} == "fc" ]; then
            spos=$(strindex "$line" "-s ")
            fpos=$(strindex "$line" "-f ")
            min=$((( $spos >= $fpos )) && echo "$fpos" || echo "$spos")
            if [ $min -ne 255 ]; then
                cmd="${line:3:min-3}"
                res="${line:min}"
            else
                echo -e "${RED}Missing response option:"
                echo -e "   ${line}"
                echo -e "Line must include -s or -f option${NC}"
                return 1
            fi
            if echo "$cmd" | grep -q ":%"; then
                IFS=% read a b <<< ${cmd}
                size=$(wc -c <"$HOST_TMP_DIR/$b")
                printf -v size '%08x' $size
                fastboot_command "$a$size"
            else
                fastboot_command ${cmd}
            fi
            response ${res}
            if [ $? -ne 0 ]; then
                echo -e "${RED}FAILED TO EXECUTE:"
                echo -e "   ${line}${NC}"
                return 1
            fi
        elif [ ${word[0]} == "fu" ]; then
            fastboot_put ${word[1]}
            response ${word[2]} ${word[3]} ${word[4]}
            if [ $? -ne 0 ]; then
                echo -e "${RED}FAILED TO EXECUTE:"
                echo -e "   ${line}${NC}"
                return 1
            fi
        elif [ ${word[0]} == "fd" ]; then
            if [ ${word[2]} == "-n" ]; then
                fastboot_get ${word[1]} ${word[3]}
            elif [ ${word[2]} == "-f" ]; then
                hex=`cat $HOST_TMP_DIR/${word[3]}`
                if [ ${hex:0:4} == "DATA" ]; then
                    fastboot_get ${word[1]} $((16#${hex:4:8}))
                else
                    echo -e "${RED}Invalid size file. Must begin with DATA${NC}"
                    return 1
                fi
            fi
            response ${word[4]} ${word[5]} ${word[6]}
            if [ $? != 0 ]; then
                return 1
            fi
        elif [ ${word[0]} == "sh" ]; then
            ./${line:3}
            if [ $? -ne 0 ]; then
                echo -e "${RED}${line:3} FAILED ${NC}"
                return 1
            fi
        elif [ ${word[0]} == "sc" ]; then
            side_command ${line:3}
        elif [ ${word[0]} == "sr" ]; then
            side_response ${word[1]}
        elif [ ${word[0]} == "xc" ]; then
            execute_cmd ${line:3}
        elif [ ${word[0]} == "start_loader" ]; then
            start_loader
        elif [ ${word[0]} == "stop_loader" ]; then
            stop_loader
        elif [ ${word[0]} == "run" ]; then
            cur_dir=`pwd`
            cd "../${word[1]}"
            exec_script cmd
            if [ $? -ne 0 ]; then
                cd $cur_dir
                echo -e "${RED}Subtest FAILED:"
                echo -e "   ${word[1]}${NC}"
                return 1
            fi
            cd $cur_dir
        elif [ ${word[0]} == "#" ]; then
            :
        else
            echo -e "${RED}"$line "cmd not supported${NC}"
            return 1
        fi
    done < "$1"
}

run_test() {
    echo "-------------------------"
    echo "BEGIN test" $1
    if [ ! -d $1 ]; then
        RETVAL=1
        echo -e "${RED}"$1 "test do not exist.${NC}"
        return
    fi
    cd $1
    exec_script cmd
    if [ $? -ne 0 ]; then
        echo -e "${RED}"$1 "failed.${NC}"
        failed_tests+=$1" "
        RETVAL=1
    else
        echo -e "${GREEN}"$1 "TESTS OK${NC}"
    fi
    pid=$(get_pid)
    stop_loader
    exec_memchk $pid
    cd ..
    rm -rf $HOST_TMP_DIR/*
    exec_remote rm -rf $DEV_TMP_DIR/*
    echo "END test" $1
}

contains() {
    string="$1"
    substring="$2"
    if test "${string#*$substring}" != "$string"
    then
      return 0    # $substring is in $string
    else
      return 1    # $substring is not in $string
    fi
}

RETVAL=0

. core/init.sh
. core/devcom.sh
. core/memchk.sh

if [ -z $HOST_TMP_DIR ]; then
  echo "init.sh failed, HOST_TMP_DIR is not set"
  exit 1
fi

export blacklist=`cat blacklist.txt | tr '\n' ' '`

# Make sure loader pipes are in place
start_loader
sleep .2
stop_loader
sleep .2

mkdir -p $HOST_TMP_DIR
exec_remote mkdir -p $DEV_TMP_DIR
rm -rf $HOST_TMP_DIR/*
exec_remote rm -rf $DEV_TMP_DIR/*

init_memchk

cd tests
if [ $# -eq 1 ]; then
    run_test ${1%/}
elif [ $# -eq 0 ]; then
    for d in */; do
        dir=${d%/}
        if ! contains " $blacklist " " $dir ";
        then
            run_test $dir
        else
            echo "Skipping test $dir"
        fi
    done
else
    echo "INVALID INPUT\n"
    echo "Valid inputs are no arguments or a single argument."
    echo "If no argument is provided, all testcases will be run"
    echo "A single test case can be run by providing the dir name"
    echo " as the only argument."
    RETVAL=1
fi
cd ..

echo "-------------------------"
if [ $RETVAL -eq 0 ]; then
    echo -e "${GREEN}ALL TESTS OK${NC}"
else
    echo -e "${RED}FOLLOWING TEST(S) FAILED:${NC}"
    for f in ${failed_tests}; do
        echo $f
    done
fi
echo "-------------------------"
