#
# Test variety of commands for the programs
#

exe='./StringToNPAlpha'
input='tests/test1.in'
upperShort='upper'
upperLong="all-uppercase"
lowerShort='lower'
lowerLong='all-lowercase'
firstShort='first'
firstLong='first-capital'
followShort='follow'
followLong='follow-input'

linebreak="echo ---------------------------"

# Testing with no options
$exe < $input
$linebreak

# Options with no arguments
echo 'Short Options'
$linebreak
$exe -A < $input
$linebreak
$exe -L < $input
$linebreak
$exe -F < $input
$linebreak
$exe -f < $input
$linebreak
$exe -n < $input
$linebreak

echo
echo 'Long Options'
$exe --all-uppercase < $input
$linebreak
$exe --all-lowercase < $input
$linebreak
$exe --first-capital < $input
$linebreak
$exe --follow-input < $input
$linebreak
$exe --number-format < $input
$linebreak

# Options with arguments

# IMPORTANT NOTE ABOUT SYNTAX OF OPTIONS ARGUMENTS
# The syntax for a programs optional arguments using C getopt and getopt_long
# is that they aren't written the same way.
# Usually you will input an option's argument as just spilt up with a ' ',
# nothing, or '=', but with optional arguments, for short options (e.g. -f),
# you put the argument directly following the option with NO whitespace OR '='
# (e.g. -Largument), and with long arguments (e.g. --long-argument-name) you
# use an '=' directly after the option followed directly by the and nothing
# else (e.g. --long-argument-name=argument)
echo 'Short Options Arguments'
echo '---------------------------'
$linebreak
$exe -f$upperShort < $input
$linebreak
$exe -f$upperLong < $input
$linebreak
$exe -f$firstShort < $input
$linebreak
$exe -f$firstLong < $input
$linebreak

$exe -n$upperShort < $input
$linebreak
$exe -n$upperLong < $input
$linebreak
$exe -n$lowerShort < $input
$linebreak
$exe -n$lowerLong < $input
$linebreak
$exe -n$firstShort < $input
$linebreak
$exe -n$firstLong < $input
$linebreak
$exe -n$followShort < $input
$linebreak
$exe -n$followLong < $input
$linebreak

echo 'Long Options Arguments'
$exe --follow-input=$upperShort < $input
$linebreak
$exe --follow-input=$upperLong < $input
$linebreak
$exe --follow-input=$firstShort < $input
$linebreak
$exe --follow-input=$firstLong < $input
$linebreak

$exe --number-format=$upperShort < $input
$linebreak
$exe --number-format=$upperLong < $input
$linebreak
$exe --number-format=$lowerShort < $input
$linebreak
$exe --number-format=$lowerLong < $input
$linebreak
$exe --number-format=$firstShort < $input
$linebreak
$exe --number-format=$firstLong < $input
