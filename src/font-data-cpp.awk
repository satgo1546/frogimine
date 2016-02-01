BEGIN {
	print "{"
}
/^[01]/ {
	printf "0b%s,\n", $0
}
/^$/ {
	print "}, {"
}
END {
	print "}"
}
