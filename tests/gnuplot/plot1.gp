set terminal pdf size 28cm,18cm linewidth 2.0
set output "test.pdf"
# IMPORT-DATA test test.data
set key top right

# PLOT SELECT testsize AS x, CAST(bandwidth AS BIGINT) AS y FROM test WHERE funcname='ScanWrite64PtrUnrollLoop' ORDER BY x
plot \
    'blah.txt' index 0 with linespoints

## PLOT SELECT testsize AS x, CAST(bandwidth AS BIGINT) AS y FROM test
## WHERE funcname='ScanRead64PtrUnrollLoop' ORDER BY x
plot \
    'blah.txt' index 1 with linespoints, \
    'blah.txt' index 2 with linespoints

# indentation start

    ## PLOT SELECT testsize AS x, CAST(rate * 1e12 AS BIGINT) AS y FROM test
    ## WHERE funcname='ScanWrite64PtrUnrollLoop' ORDER BY x

    ## PLOT SELECT testsize AS x, CAST(rate * 1e12 AS BIGINT) AS y FROM test
    ## WHERE funcname='ScanRead64PtrUnrollLoop' ORDER BY x
    plot \
        'blah.txt' index 3 with linespoints

# indentation end
quit