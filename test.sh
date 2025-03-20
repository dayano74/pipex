# Pipex Test　Cases

#1. basic
echo -e "apple\nbanana\napple\ncherry" > infile
./pipex infile "grep apple" "wc -l" outfile

#2. invalid argc
./pipex infile "cat" "wc -l"

#3. file1 no existent
./pipex non_existent "cat" "wc -l" outfile

#4. no exist cmd
./pipex infile "nonexistentcmd" "wc -l" outfile

#5. cmd use '' and \
./pipex infile "awk '{print \$1}'" "uniq" outfile



