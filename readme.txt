try to calculating PCC for all the pair-wised genes for the file "data.zip"
with c/c++/perl/python/java or other commonly used language, in data file, 
each row represented a gene, column represented the samples.
see PCC defination here: http://en.wikipedia.org/wiki/Pearson_product-moment_correlation_coefficient

requirements:
1. results should look like this one:
gene1\tgene2\tpcc1\n
gene1\tgene3\tpcc1\n
...
gene2\tgene3\tpcc1\n
gene2\tgene4\tpcc1\n
...
2. define two parameters for programe input, first to be the input, second to be the output file name;
3. the program must be functional, and the results should be correct.

bonus:
1. try to mimic the time cost;
2. mutiple-processing/CPU calculation is encouraged;
3. detailed helping messages is encouraged;
4. friendly GUI is encouraged;