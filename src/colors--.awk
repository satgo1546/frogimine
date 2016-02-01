#  Copyright 2016 Frog Chen
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#==============================================================================
# ■ colors--.awk
#------------------------------------------------------------------------------
#   *-colors.csv → C++ / NASM
#==============================================================================

BEGIN {
	FS = ","
	if (output == "nasm") {
		print "; %macro color 3"
	}
}
output == "cpp" {
	printf "%s = %d,\n", $1, NR - 1
}
output == "nasm" {
	printf "color %d, %d, %d ; %d\n", $2, $3, $4, NR - 1
}
END {
	if (output != "cpp" && output != "nasm") {
		print "[!!] awk -v output=<cpp|nasm> -f ..."
	}
}
