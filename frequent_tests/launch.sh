#!/bash

DIR=".."

make -C $DIR
cp $DIR/minishell .
bash < frequent_tests.txt > expected_stdout 2> expected_errout
./minishell < frequent_tests.txt > my_stdout 2> my_errout

bash < echo_tests.txt > expected_stdout2 2> expected_errout2
./minishell < echo_tests.txt > my_stdout2 2> my_errout2
cat expected_stdout2 >> expected_stdout
cat my_stdout2 >> my_stdout

bash < echo_in_files.txt > expected_stdout3 2> expected_errout3
cat file1 file2 file3 file4 file5 file6 file7 file8 file9 file10 > files_with_bash
./minishell < echo_in_files.txt > my_stdout3 2> my_errout3
cat file1 file2 file3 file4 file5 file6 file7 file8 file9 file10 > files_with_minishell
cat expected_stdout3 >> expected_stdout
cat my_stdout3 >> my_stdout

echo "______________________________________________________________________" > log
echo "			SORTIE STANDARD			" >> log
echo "______________________________________________________________________" >> log
diff expected_stdout my_stdout >> log
echo "______________________________________________________________________" >> log
echo "			SORTIE ERREURS			" >> log
echo "______________________________________________________________________" >> log
diff expected_errout my_errout >> log
echo "______________________________________________________________________" >> log
echo "		COMPARAISONS DE FICHIERS		" >> log
echo "______________________________________________________________________" >> log
diff files_with_bash files_with_minishell >> log
# echo diff1 ; diff file1 my_file1
# echo diff2 ; diff file2 my_file2
# echo diff3 ; diff file3 my_file3
# echo diff4 ; diff file4 my_file4
# echo diff5 ; diff file5 my_file5
# echo diff6 ; diff file6 my_file6
# echo diff7 ; diff file7 my_file7
# echo diff8 ; diff file8 my_file8
# echo diff9 ; diff file9 my_file9
# echo diff10 ; diff file10 my_file10
