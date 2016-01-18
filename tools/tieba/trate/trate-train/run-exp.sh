mlt ./feature.trate.txt -c norm 
mlt ./feature.trate.txt -c sd -ci 4:1 -rs 1024
mlt ./feature.trate.normed.txt -c sd -ci 4:1 -rs 1024 

mlt ./feature.trate.normed.0_2.txt -c tt -test ./feature.trate.normed.1_2.txt -cl liblinear --norm=0 -rs 1024
