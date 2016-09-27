echo "urate2.sh"
sh ./urate2.sh $1 &
echo "behaviour2.sh"
sh ./behaviour2.sh $1 &
echo "pc-behav-old2.sh"
sh ./pc-behav-old2.sh $1 &
echo "img2.sh"
sh ./img2.sh $1 &
echo "tid2.sh"
sh ./tid2.sh $1 &
echo "ugrade2.sh"
sh ./ugrade2.sh $1 &
wait

