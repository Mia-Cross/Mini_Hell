#!/bash

# emplacement relatif du projet par rapport au testeur
DIR="../retry_minishell"

# compilation
make -C $DIR
cp $DIR/minishell .

# Comportement avec bash
bash < frequent_tests > expected_stdout 2> expected_errout
bash < echo_tests > expected_stdout2 2> expected_errout2
bash < echo_in_files > expected_stdout3 2> expected_errout3
bash < pipe_tests > expected_stdout4 2> expected_errout4
cat -e tests/* > files_with_bash
rm -rf tests

# Comportement Minishell
./minishell < frequent_tests > my_stdout 2> my_errout
./minishell < echo_tests > my_stdout2 2> my_errout2
./minishell < echo_in_files > my_stdout3 2> my_errout3
./minishell < pipe_tests > my_stdout4 2> my_errout4
cat -e tests/* > files_with_minishell

# ecriture du fichier log qui recapitule tous les tests precedents
echo "______________________________________________________________________" > log
echo "			FREQUENT_TESTS			" >> log
echo "			SORTIE STANDARD			" >> log
echo "______________________________________________________________________" >> log
diff expected_stdout my_stdout >> log
echo "______________________________________________________________________" >> log
echo "			SORTIE ERREURS			" >> log
echo "______________________________________________________________________" >> log
diff expected_errout my_errout >> log
echo "______________________________________________________________________" >> log
echo "				ECHO TESTS			" >> log
echo "			SORTIE STANDARD			" >> log
echo "______________________________________________________________________" >> log
diff expected_stdout2 my_stdout2 >> log
echo "______________________________________________________________________" >> log
echo "			SORTIE ERREURS			" >> log
echo "______________________________________________________________________" >> log
diff expected_errout2 my_errout2 >> log
echo "______________________________________________________________________" >> log
echo "			ECHO IN FILES			" >> log
echo "			SORTIE STANDARD			" >> log
echo "______________________________________________________________________" >> log
diff expected_stdout3 my_stdout3 >> log
echo "______________________________________________________________________" >> log
echo "			SORTIE ERREURS			" >> log
echo "______________________________________________________________________" >> log
diff expected_errout3 my_errout3 >> log
echo "______________________________________________________________________" >> log
echo "				PIPE TESTS			" >> log
echo "			SORTIE STANDARD			" >> log
echo "______________________________________________________________________" >> log
diff expected_stdout4 my_stdout4 >> log
echo "______________________________________________________________________" >> log
echo "			SORTIE ERREURS			" >> log
echo "______________________________________________________________________" >> log
diff expected_errout4 my_errout4 >> log
echo "______________________________________________________________________" >> log
echo "		COMPARAISONS DE FICHIERS		" >> log
echo "______________________________________________________________________" >> log
diff files_with_bash files_with_minishell >> log


# 3eme vague de tests : echo dans des fichiers
# echo -n "01 : " > files_with_bash
# cat -e file1 >> files_with_bash
# echo -n "02 : " >> files_with_bash
# cat -e file2 >> files_with_bash
# echo -n "03 : " >> files_with_bash
# cat -e file3 >> files_with_bash
# echo -n "04 : " >> files_with_bash
# cat -e file4 >> files_with_bash
# echo -n "05 : " >> files_with_bash
# cat -e file5 >> files_with_bash
# echo -n "06 : " >> files_with_bash
# cat -e file6 >> files_with_bash
# echo -n "07 : " >> files_with_bash
# cat -e file7 >> files_with_bash
# echo -n "08 : " >> files_with_bash
# cat -e file8 >> files_with_bash
# echo -n "09 : " >> files_with_bash
# cat -e file9 >> files_with_bash
# echo -n "10 : " >> files_with_bash
# cat -e file10 >> files_with_bash
# rm -rf file1 file2 file3 file4 file5 file6 file7 file8 file9 file10
# echo -n "01 : " > files_with_minishell
# cat -e file1 >> files_with_minishell
# echo -n "02 : " >> files_with_minishell
# cat -e file2 >> files_with_minishell
# echo -n "03 : " >> files_with_minishell
# cat -e file3 >> files_with_minishell
# echo -n "04 : " >> files_with_minishell
# cat -e file4 >> files_with_minishell
# echo -n "05 : " >> files_with_minishell
# cat -e file5 >> files_with_minishell
# echo -n "06 : " >> files_with_minishell
# cat -e file6 >> files_with_minishell
# echo -n "07 : " >> files_with_minishell
# cat -e file7 >> files_with_minishell
# echo -n "08 : " >> files_with_minishell
# cat -e file8 >> files_with_minishell
# echo -n "09 : " >> files_with_minishell
# cat -e file9 >> files_with_minishell
# echo -n "10 : " >> files_with_minishell
# cat -e file10 >> files_with_minishell
# rm -rf file1 file2 file3 file4 file5 file6 file7 file8 file9 file10
# cat -e expected_stdout3 >> expected_stdout
# cat -e my_stdout3 >> my_stdout
