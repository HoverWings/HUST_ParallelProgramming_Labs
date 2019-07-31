for((i=1;i<=1000;i+=10));  
do   
    # echo $(expr $i \* 3 + 1);  
    ./a.out $i
done  