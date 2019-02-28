set terminal pdf size 28cm,18cm linewidth 2.0
set output "test.pdf"
# IMPORT-DATA test test.data
set key top right

## MULTIPLOT(funcname) SELECT testsize AS x, FLOOR(bandwidth) AS y, MULTIPLOT
## FROM test WHERE host='earth' ORDER BY MULTIPLOT,x

## MULTIPLOT(testsize) SELECT testsize AS x, FLOOR(AVG(bandwidth)) AS y, MULTIPLOT
## FROM test WHERE host='earth' GROUP BY MULTIPLOT ORDER BY MULTIPLOT,x
plot \
    'stdin-data.txt' index 0 with lines linetype 4, \
    'stdin-data.txt' index 1 linecolor 2 with lines, \
    'stdin-data.txt' index 2 with lines, \
    'stdin-data.txt' index 3 with points, \
    'stdin-data.txt' index 4 with lines, \
    'stdin-data.txt' index 5 with lines

## MULTIPLOT(funcname)
## SELECT testsize AS x, FLOOR(bandwidth) AS y,
## FLOOR(bandwidth * 1.1) AS xmax, FLOOR(bandwidth * 0.9) AS xmin, MULTIPLOT
## FROM test WHERE host='earth' ORDER BY MULTIPLOT,x

## MULTIPLOT(funcname)
## SELECT testsize AS x, FLOOR(bandwidth) AS y,
## FLOOR(bandwidth * 1.1) AS ymax, FLOOR(bandwidth * 0.9) AS ymin, MULTIPLOT
## FROM test WHERE host='earth' ORDER BY MULTIPLOT,x

## MULTIPLOT(funcname)
## SELECT testsize AS x, FLOOR(bandwidth) AS y,
## FLOOR(bandwidth * 1.1) AS xmax, FLOOR(bandwidth * 0.9) AS xmin,
## FLOOR(bandwidth * 1.1) AS ymax, FLOOR(bandwidth * 0.9) AS ymin, MULTIPLOT
## FROM test WHERE host='earth' ORDER BY MULTIPLOT,x

quit