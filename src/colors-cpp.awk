BEGIN {
	FS = ","
}
{
	printf "%s = %d,\n", $1, NR - 1
}
