#!bin/bash/

if [ $1 != "-t" ]; then

    if [ $1 == "-a" ] && [ -z $3 ]; then

        if [ ! -d "$2" ]; then
            mkdir $2
            echo 'Created archieve directory.'
        fi

        dirpath="$(realpath $2)"

        for Directories in *; do
        if [ -d "${Directories}" ]; then
            todayDate=`date +"%b%d%Y"`
            finalName="$Directories$todayDate"
            tar -zcvf "$finalName.tar" "${Directories}"
        fi
        done

        for tar in $(find . -name '*.tar'); do
        mv $tar $dirpath
        done

        echo 'Done.'

    elif [ $1 == "-a" ] && [ $3 == "-t" ]; then 

        echo 'Although, Correct Format is tarDirs [-t target Directory] <-a archieve Directory>'

        if [ ! -d "$4" ]; then
            echo 'Target directory does not exist.'
        else

            if [ ! -d "$2" ]; then
                mkdir $2
                echo 'Created archieve directory.'
            fi

            dirpath="$(realpath $2)"

            targetpath=$4
            firstChar=${targetpath:0:1}

            if [ $firstChar == "/" ]; then
                targetpath=${targetpath#"/"}
            fi

            cd $targetpath

            for Directories in *; do
            if [ -d "${Directories}" ]; then
                todayDate=`date +"%b%d%Y"`
                finalName="$Directories$todayDate"
                tar -zcvf "$finalName.tar" "${Directories}"
            fi
            done

            for tar in $(find . -name '*.tar'); do
            mv $tar $dirpath
            done

            echo 'Done.'
        fi
    else 

        echo 'Correct Format is tarDirs [-t target Directory] <-a archieve Directory>'

    fi

else

    if [ -z $3 ] || [ $3 != '-a' ]; then
        echo 'Correct Format is tarDirs [-t target Directory] <-a archieve Directory>'
    else    

        if [ ! -d "$2" ]; then
            echo 'Target directory does not exist.'
        else

            if [ ! -d "$4" ]; then
                mkdir $4
                echo 'Created archieve directory.'
            fi

            dirpath="$(realpath $4)"

            targetpath=$2
            firstChar=${targetpath:0:1}

            if [ $firstChar == "/" ]; then
                targetpath=${targetpath#"/"}
            fi

            cd $targetpath

            for Directories in *; do
                if [ -d "${Directories}" ]; then
                    todayDate=`date +"%b%d%Y"`
                    finalName="$Directories$todayDate"
                    tar -zcvf "$finalName.tar" "${Directories}"
                fi
            done

            for tar in $(find . -name '*.tar'); do
                mv $tar $dirpath
            done

            echo 'Done.'
        fi
    fi    
fi