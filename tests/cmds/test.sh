grep 1 < filedoesnotexist | echo 1 | grep 1 > tmp_out | head -1 | cat
cat tmp_out
rm -f tmp_out
