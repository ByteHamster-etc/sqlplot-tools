set terminal pdf size 28cm,18cm linewidth 2.0
set output "test.pdf"
# IMPORT-DATA test test.data
set key top right

# MACRO SELECT host, 1.05 AS num FROM test GROUP BY host
key = 'val'
another = 'macro'

quit