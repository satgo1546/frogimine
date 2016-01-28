BEGIN {
	FS = ","
	print "; %macro color 3"
}
{
	printf "color %d, %d, %d ; %d\n", $2, $3, $4, NR - 1
}
