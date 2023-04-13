#!/bin/bash
# Copyright (C) Ethan Uppal 2023. All rights reserved.

FILES=bin/out*

for f in $FILES
do
    pnmtopng $f > bin/"png_`basename $f`.png"
done
rm -rf bin/out*
magick -delay 5 `ls bin/png* | sort -n -t _ -k 3` bin/out.gif
rm -rf bin/png*
