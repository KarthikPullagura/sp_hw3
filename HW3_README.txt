make
rm -fr hw3_k
gcc   hw3_k.c -o hw3_k


./hw3_k -s 1024 -e "ls -l"

S:0
s:1(1024)
f:0( : 0)
t:0()
.
s:ls -l ./D1
total 0
s:ls -l ./D2
total 0
s:ls -l ./D3
total 0
s:ls -l ./D4
total 0
s:ls -l ./Makefile
-rwxr-xr-x 1 root root 72 Mar 12 19:34 ./Makefile
s:ls -l ./s.c
-rw-r--r-- 1 root root 113 Mar 12 18:55 ./s.c



./hw3_k -f "D 3" -E "tar cvf Dfolder.tar"


S:0
s:0(0)
f:1(D : 3)
t:0()
.
[1] D1 (directory)
[2] D2 (directory)
[3] D3 (directory)
[4] D4 (directory)
[5] HW2_README.txt (regular file)
s:tar cvf Dfolder.tar ./D1 ./D2 ./D3 ./D4 ./HW2_README.txt
./D1/
./D2/
./D3/
./D4/
./HW2_README.txt
 tar -tf Dfolder.tar
./D1/
./D2/
./D3/
./D4/
./HW2_README.txt







./hw3_k -s 1024 -f "ake 1" -e "wc -l"

S:0
s:1(1024)
f:1(ake : 1)
t:0()
.
s:wc -l ./Makefile
9 ./Makefile

















