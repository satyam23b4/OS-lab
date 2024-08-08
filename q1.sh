read file_name
if [ -f "$file_name" ]; then
	echo "$file_name is a file"
elif [ -d "$file_name" ]; then
	echo "$file_name is a directory"
else
	echo "$file_name is invalid"
fi

