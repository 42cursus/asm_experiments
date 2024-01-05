set height unlimited
set pagination off
-
dir src
br _start
set confirm off
set trace-commands on
layout split
layout reg
show debug-file-directory
run
x/s &msg
display (char *)$rsi
