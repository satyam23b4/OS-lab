read -p "Enter the pattern to search for: " pattern
echo "searching for the pattern $pattern in the current directory"
grep -rl "$pattern"
