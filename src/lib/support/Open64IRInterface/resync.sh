for i in `ls *.h *.?pp`
do 
  diff $i ~/Argonne/svn/Whirl2OA/$i
  if [ $? -eq 1 ]
  then 
    kdiff3 -m $i ~/Argonne/svn/Whirl2OA/$i -o $i   
  fi
done
