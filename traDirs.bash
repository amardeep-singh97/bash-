#!bin/bash

while getopts t:a: flag
do 
	case "${flag}" in
		t) targetPath=${OPTARG};;
		a) archievePath=${OPTARG};;
	esac
done

if [ -z "$archievePath" ] && [ -z "$targetPath" ]; then
	echo 'Correct Format is tarDirs [-t target Directory] <-a archieve Directory>'
elif [ -z "$archievePath" ]; then
	echo 'Please enter archieve directory path'
else 
	if [ -z "$targetPath" ]; then

		if [ ! -d "$archievePath" ]; then
            mkdir $archievePath
            echo 'Created archieve directory.'
        fi

		dirpath="$(realpath $archievePath)"

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
	else

		firstChar=${targetPath:0:1}

        if [ $firstChar == "/" ]; then
            targetPath=${targetPath#"/"}
        fi

		if [ ! -d "$targetPath" ]; then
			echo 'Target directory does not exist.'
		else 

			if [ ! -d "$archievePath" ]; then
            	mkdir $archievePath
            	echo 'Created archieve directory.'
        	fi

			dirpath="$(realpath $archievePath)"

            cd $targetPath

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