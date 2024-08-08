<<comment
echo "hello"
a=2
echo $a
read x y
echo $a $b
z=$(expr $x + $y)
echo $z
echo "Enter 2 values"
read a b
result=$[a==b]
echo "Check for equality = $result"
echo "Enter 2 values"
read a b
echo "enter operator(+, -, /, *, %)"
read op
result=$((a $op b))
echo "Result of performing $a $op $b is $result"
comment
echo "Enter a character"
read character
if [ "$character" = "2" ]; then
	echo "you entered 2"
fi
echo "Enter 2 digits"
read a b
if [ $a == $b]; then
	echo "entered digits are equal"
elif [ $a -gt $b ]; then
	echo "$a greater than $b" 
else
	echo "$a is less than $b"
fi
