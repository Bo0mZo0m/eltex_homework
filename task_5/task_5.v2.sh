#!\bin\bash
kill $(ps -ax | grep sublime | grep -v grep | grep -oE  ' [0-9]+ ' | grep -oE ' [0-9]+ ' |xargs)

