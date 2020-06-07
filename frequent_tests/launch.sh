#!/bash

# emplacement relatif du projet par rapport au testeur
DIR=".."

# compilation
make -C $DIR
cp $DIR/minishell .

# 1ere vague de tests : permissions, variables d'env, etc...
bash < frequent_tests.txt > expected_stdout 2> expected_errout
./minishell < frequent_tests.txt > my_stdout 2> my_errout

# 2eme vague de tests : echo 
bash < echo_tests.txt > expected_stdout2 2> expected_errout2
./minishell < echo_tests.txt > my_stdout2 2> my_errout2
cat expected_stdout2 >> expected_stdout
cat my_stdout2 >> my_stdout

# 3eme vague de tests : echo dans des fichiers
bash < echo_in_files.txt > expected_stdout3 2> expected_errout3
cat file1 file2 file3 file4 file5 file6 file7 file8 file9 file10 > files_with_bash
rm -rf file1 file2 file3 file4 file5 file6 file7 file8 file9 file10
./minishell < echo_in_files.txt > my_stdout3 2> my_errout3
cat file1 file2 file3 file4 file5 file6 file7 file8 file9 file10 > files_with_minishell
rm -rf file1 file2 file3 file4 file5 file6 file7 file8 file9 file10
cat expected_stdout3 >> expected_stdout
cat my_stdout3 >> my_stdout

# ecriture du fichier log qui recapitule tous les tests precedents
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

