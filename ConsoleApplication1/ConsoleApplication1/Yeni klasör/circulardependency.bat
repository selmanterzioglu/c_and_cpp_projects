cinclude2dot.pl --include=./ --quotetype=quote > dependency.dot
sccmap -v dependency.dot > circulardependency.dot
dot -Tsvg circulardependency.dot > output.svg