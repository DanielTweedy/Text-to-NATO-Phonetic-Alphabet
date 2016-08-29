printf '{'
for x in $(cat RAF1924Lower.ignore); do
	if [ $x != 'ace' ]; then
		printf ", "
	fi; printf "\"$x\""
done
printf '};'
echo
