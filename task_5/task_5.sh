#!\bin\bash
kill $(ps aux | grep -E '\w*subli\w* {1}')
