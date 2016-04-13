#!/bin/bash

echo; echo "Hit a key, then hit return."
read Keypress

case "$Keypress" in
	[[:lower:]] ) echo "Lowercase" ;;
	[[:upper:]] ) echo "Uppercase" ;;
	[0-9] ) echo "Digit" ;;
	* ) echo "Other crap" ;;
esac

exit 0
