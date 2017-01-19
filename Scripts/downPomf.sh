#!/bin/sh
downpomf=""
uppomf="https://up.serioushomebrew.nl/upload.php"

if test $# -lt 1 ; then
    echo "Usage: `basename $0` FILE [FILE...]"
    exit 1
fi

set=
for f ; do
    test "$set" || set -- ; set=1
    set -- "$@" -F "files[]=@$f"
done

curl -fsSL "$@" "$uppomf" | jq -c -r --arg base "$downpomf" '$base + .files[].url'
