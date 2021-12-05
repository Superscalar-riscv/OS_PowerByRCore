#!/bin/bash

# script to generate link_app.S 

apps_path="${OS_HOME}/user/build/"
script_text="./src/link_app.S"
# function for find app file
find_app_list() {
    let "num_apps=0"
    for bin in `find ${apps_path} -name "*.bin" | sort`
    do
        app_list[num_apps]=${bin}
        let num_apps+=1
    done
    return $num_apps
}
# app info
echo -e "\033[32m build.sh: generate link_app.S \033[0m"
find_app_list
apps_len=$?
echo len = $apps_len
# script="src/link_app.S"
cat > ${script_text} <<- EOF
# os/src/link_app.S

.align 3
    .section .data
    .global _num_app
_num_app:
    .quad ${apps_len}
EOF

# app_$(i)_start
int=0
while(($int<$num_apps))
do
cat >> ${script_text} <<- EOF
    .quad app_${int}_start
EOF
    let "int++"
done
#app_*_end
max_idx=`expr $num_apps - 1`
cat >> ${script_text} <<- EOF
    .quad app_${max_idx}_end

EOF

# all app .section
idx=0
while(($idx<$num_apps))
do
cat >> ${script_text} <<- EOF
    .section .data
    .global app_${idx}_start
    .global app_${idx}_end
app_${idx}_start:
    .incbin "${app_list[${idx}]}"
app_${idx}_end:

EOF
    let "idx++"
done

# cat ${script_text}