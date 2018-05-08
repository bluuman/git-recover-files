# git-recover-files

I used this to successfully recover my files after accidentally using ```git rm``` on some staged files.
I found this method documented here: https://www.spinics.net/lists/git/msg62499.html

to use:
download main.cpp
```g++ -std=c++11 -o recover main.cpp```
```./recover <GIT REPO WITH MISSING FILES>``` or ```./recover``` from inside of the git repo

you will get out.txt with the recovered files, good luck.
