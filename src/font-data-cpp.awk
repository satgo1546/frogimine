BEGIN {
	valid_line_number = 0
	print "{"
}
/^[01]/ {
	valid_line_number++
	printf "0b%s,\n", $0
}
/^[01]/ && valid_line_number % 12 == 0 {
	print "}, {"
}
END {
	print "}"
}
