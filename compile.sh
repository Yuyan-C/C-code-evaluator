gcc -c main.c output.c parser.c rate_comment.c rate_doc.c rate_indentation.c rate_modular.c rate_testcases.c rate_var.c 
gcc -o ceval main.o output.o parser.o rate_comment.o rate_doc.o rate_indentation.o rate_modular.o rate_testcases.o rate_var.o
rm *.o 