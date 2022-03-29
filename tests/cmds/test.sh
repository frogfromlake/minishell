/bin/echo 42 > /dev/null > tmp_redir_out
/bin/echo 2 >> /dev/null >> tmp_redir_out
cat tmp_redir_out
rm tmp_redir_out
