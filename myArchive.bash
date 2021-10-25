#!bin/bash/

#This method is to remove . from extension, if user adds one
detect_dot(){
	firstChar=${extension:0:1}
	if [ firstChar=="." ];then
		extension=${extension#"."}
	fi
}

while getopts t:a: options
do 
	case "${options}" in
		t) target=${OPTARG};;
		a) archive=${OPTARG};;
		*) echo 'Correct Format is myArchive -t [path] -a [path] <extension lists>'
	esac
done

arr=($@) #Getting all arguments as array.
startIndex=$OPTIND #Pointer to first extension as argument 
totalVals=$# 

((startIndex--)) #Decreasing to use it as array index

if [ -z $target ];then

	if [ ! -w "./" ]; then
		echo "Error: No Write Permission"
		exit 0
	fi

	if [ -z $archive ];then
		if [ ! -d './archiveDirectory' ];then
			mkdir './archiveDirectory'
			echo 'Archive directory created'
		fi
		for ((i=startIndex; i<totalVals; i++ )); do
			extension=${arr[i]}	#getting extenstions
			detect_dot			#Calling function
			for file in $(find . -name '*.'${extension}); do
				mv "$file" './archiveDirectory'
			done
		done
	else
		if [ ! -d "$archive" ];then
			mkdir $archive
			echo 'Archive directory created.'
		fi
		dirpath="$(realpath $archive)"
		for ((i= startIndex; i<totalVals; i++ )); do
			extension=${arr[i]}
			detect_dot
			for file in $(find . -name '*.'${extension}); do
				mv ${file} $dirpath
			done
		done
	fi

else
	if [ ! -d "$target" ]; then
		echo "Target directory dosen't exist."
	else
		if [ ! -w "$target" ]; then
			echo "Error: No Write Permission"
			exit 0
		fi

		if [ -z $archive ]; then
			if [ ! -d './archiveDirectory' ];then
				mkdir './archiveDirectory'
				echo 'Archive Directory created.'
			fi
			for ((i=startIndex; i<totalVals; i++ )); do
				extension=${arr[i]}
				detect_dot
				for file in $(find ${target} -name '*.'${extension}); do
					mv $file './archiveDirectory'
				done
			done
		else
			if [ ! -d $archive ]; then
				mkdir $archive
				echo 'Archive Directory created.'
			fi
			dirpath=$(realpath $archive)
			for ((i=startIndex; i<totalVals; i++ )); do
				extension=${arr[i]}
				detect_dot
				for file in $(find ${target} -name '*.'${extension}); do
					mv $file $dirpath
				done
			done
		fi
	fi
fi