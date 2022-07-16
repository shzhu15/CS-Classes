# Prepare files.
# Usage: ./hw4_executor.sh untar [true]-> true if need to recreate submissions.
hw=hw4
TARPATH="../tars"
DSTPATH="../submissions"
if [[ $1 == 'untar' ]];then
	if [[ $2 == 'true' ]];then mv $DSTPATH $DSTPATH"_old";fi
	if [[ ! -d $DSTPATH ]];then mkdir $DSTPATH;fi 
	for eid in `ls ../tars`;do
	
		# Copy necessary tar files.
		if [[ -f $TARPATH/$eid/LATE_${hw}.tar ]]; then
	    #echo -e "\nLate file copied for $eid"
			mkdir $DSTPATH/$eid
	    cp $TARPATH/$eid/LATE_${hw}.tar $DSTPATH/$eid/
	  elif [[ -f $TARPATH/$eid/${hw}.tar ]]; then
	    mkdir $DSTPATH/$eid
	    cp $TARPATH/$eid/${hw}.tar $DSTPATH/$eid
	    #echo -e "\nCopied tar file (ON-TIME)."
	  else
	    echo -e "\nERROR coping tar file for $eid."
		fi

		# Untar the files.
		#echo -e "\nUntar files in $DSTPATH directory...."
		depth=$(tar -tf $DSTPATH/$eid/*.tar |head -1|grep -o \/|wc -l)
		#mkdir ./tmp_$1/$eid/untar
		tar -xf $DSTPATH/$eid/*.tar --strip=$depth -C $DSTPATH/$eid/
	done
fi
# Command to format spaces,tabs,newline, carriage return.
clean="tr '\040\011\012\015' ' '|sed 's/P2 /P2\n/g'|sed 's/Alpha /Alpha\n/g'|sed 's/ $/\n/g'"
key=../input_images/key
# Start compilation and execution
for i in `ls -d ../submissions/*`; do
	echo "Executing User: "${i#../submissions/}
	out=$i/output	
	if [[ -d $out ]]; then rm -fr $out;fi 
	mkdir $out
	if [[ -f $out/logger.out ]];then rm $out/logger.out;fi
	if [[ -f $i/test_empty ]];then rm $i/test_*;fi	
	exec 3>> $out/logger.out #open fd 3.
	exec 2>&3
	echo "User: " ${i#../submissions/} >&3
	cd $i
	if [[ -f hw4.a ]]; then 
		rm hw4.a && make &> /dev/null
	else
		make &> /dev/null
	fi
	cd - &> /dev/null 
	echo -e "-----------------------------------\n##empty test\n..................................." >&3
	g++ -Wall empty.cc $i/hw4.a -I $i/ -o $i/test_empty 
	timeout 10s $i/test_empty empty.alpha alpha >&3
	timeout 10s $i/test_empty empty_comment.alpha alpha >&3
	timeout 10s $i/test_empty simple.alpha alpha >&3
	timeout 10s $i/test_empty empty.pgm pgm >&3
	timeout 10s $i/test_empty simple.pgm pgm >&3
	timeout 10s $i/test_empty empty_bad.pgm pgm >&3
	
	echo -e "-----------------------------------\n##width test\n..................................." >&3
	g++ -Wall width.cc $i/hw4.a -I $i/ -o $i/test_width
	#timeout 10s $i/test_width >&3
	timeout 10s $i/test_width  empty.alpha alpha >&3
	timeout 10s $i/test_width  simple.alpha alpha >&3
	timeout 10s $i/test_width  empty.pgm pgm >&3
	timeout 10s $i/test_width  simple.pgm pgm >&3
	
	echo -e "-----------------------------------\n##height test\n..................................." >&3
	g++ -Wall height.cc $i/hw4.a -I $i/ -o $i/test_height 
	timeout 10s $i/test_height empty.alpha alpha >&3
	timeout 10s $i/test_height simple.alpha alpha >&3
	timeout 10s $i/test_height empty.pgm pgm >&3
	timeout 10s $i/test_height simple.pgm pgm >&3
	
	echo -e "-----------------------------------\n##getpixel test\n..................................." >&3
	g++ -Wall getpixel.cc $i/hw4.a -I $i/ -o $i/test_pixel 
	#timeout 10s $i/test_pixel >&3
	timeout 10s $i/test_pixel simple.alpha alpha 0 0 >&3
	timeout 10s $i/test_pixel simple.alpha alpha -1 -2 >&3
	timeout 10s $i/test_pixel simple.alpha alpha 1 2 >&3
	timeout 10s $i/test_pixel empty.alpha alpha 1 2 >&3
	timeout 10s $i/test_pixel simple.alpha alpha 100 200 >&3
	timeout 10s $i/test_pixel simple.pgm pgm 0 0 >&3
	timeout 10s $i/test_pixel simple.pgm pgm 3 5 >&3
	timeout 10s $i/test_pixel empty.pgm pgm 3 5 >&3
	timeout 10s $i/test_pixel simple.pgm pgm -3 -5 >&3
	
	echo -e "-----------------------------------\n##range test\n..................................." >&3
	g++ -Wall range.cc $i/hw4.a -I $i/ -o $i/test_range 
	timeout 10s $i/test_range simple.alpha alpha >&3
	timeout 10s $i/test_range simple.pgm pgm >&3
	timeout 10s $i/test_range range1.pgm pgm >&3
	
	
	echo -e "-----------------------------------\n##mirror test\n..................................." >&3
	g++ -Wall mirror.cc $i/hw4.a -I $i/ -o $i/test_mirror 
	timeout 10s $i/test_mirror simple.alpha 1 alpha|eval $clean > $out/mirror1.alpha
	diff_out=$(diff -w $out/mirror1.alpha $key/amirror1.alpha |grep -vE ">[[:space:]]$|<[[:space:]]$") 
	if [[ ! -z "$diff_out" ]];then echo "mirror1.alpha different" >&3;fi
	timeout 10s $i/test_mirror simple.pgm 1 pgm|eval $clean > $out/mirror1.pgm
	diff_out=$(diff -w $out/mirror1.pgm  $key/amirror1.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "mirror1.pgm different" >&3;fi	
	timeout 10s $i/test_mirror simple.alpha 2 alpha|eval $clean > $out/mirror2.alpha
	diff_out=$(diff -w $out/mirror2.alpha $key/amirror2.alpha |grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "mirror2.alpha different" >&3;fi
	timeout 10s $i/test_mirror simple.pgm 2 pgm|eval $clean > $out/mirror2.pgm
	diff_out=$(diff -w $out/mirror2.pgm  $key/amirror2.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "mirror2.pgm different" >&3;fi

	
	echo -e "-----------------------------------\n##rotate test\n..................................." >&3
	g++ -Wall rotate.cc $i/hw4.a -I $i/ -o $i/test_rotate 
	timeout 10s $i/test_rotate simple.alpha 0 alpha|eval $clean > $out/rotate1.alpha
	diff_out=$(diff -w $out/rotate1.alpha  $key/arotate1.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "rotate1.alpha different" >&3;fi
	timeout 10s $i/test_rotate simple.pgm 0 pgm|eval $clean > $out/rotate1.pgm
	diff_out=$(diff -w $out/rotate1.pgm  $key/arotate1.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "rotate1.pgm different" >&3;fi
	
	timeout 10s $i/test_rotate simple.alpha 90 alpha|eval $clean > $out/rotate2.alpha
	diff_out=$(diff -w $out/rotate2.alpha  $key/arotate2.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "rotate2.alpha different" >&3;fi

	timeout 10s $i/test_rotate simple.pgm 90 pgm|eval $clean > $out/rotate2.pgm
	diff_out=$(diff -w $out/rotate2.pgm  $key/arotate2.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "rotate2.pgm different" >&3;fi

	
	timeout 10s $i/test_rotate simple.alpha -630 alpha|eval $clean > $out/rotate3.alpha
	diff_out=$(diff -w $out/rotate3.alpha  $key/arotate2.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "rotate3.alpha different" >&3;fi

	timeout 10s $i/test_rotate simple.pgm -630 pgm|eval $clean > $out/rotate3.pgm
	diff_out=$(diff -w $out/rotate3.pgm  $key/arotate2.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "rotate3.pgm different" >&3;fi

	
	timeout 10s $i/test_rotate simple.alpha 720 alpha|eval $clean > $out/rotate4.alpha
	diff_out=$(diff -w $out/rotate4.alpha  $key/arotate1.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "rotate4.alpha different" >&3;fi

	timeout 10s $i/test_rotate simple.pgm 720 pgm| eval $clean > $out/rotate4.pgm
	diff_out=$(diff -w $out/rotate4.pgm  $key/arotate1.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "rotate4.pgm different" >&3;fi

	
	echo -e "-----------------------------------\n##resize test\n..................................." >&3
	g++ -Wall resize.cc $i/hw4.a -I $i/ -o $i/test_resize 
	timeout 10s $i/test_resize simple.alpha 0.5 alpha| eval $clean > $out/resize1.alpha
	diff_out=$(diff -w $out/resize1.alpha  $key/aresize1.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "resize1.alpha different" >&3;fi

	timeout 10s $i/test_resize simple.pgm 0.5 pgm|eval $clean > $out/resize1.pgm
	diff_out=$(diff -w $out/resize1.pgm  $key/aresize1.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "resize1.pgm different" >&3;fi

	# Double size
	timeout 10s $i/test_resize simple.alpha 2.0 alpha|eval $clean > $out/resize2.alpha
	diff_out=$(diff -w $out/resize2.alpha  $key/aresize2.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$")
	if [[ ! -z "$diff_out" ]];then echo "resize2.alpha different" >&3;fi

	timeout 10s $i/test_resize simple.pgm 2.0 pgm|eval $clean > $out/resize2.pgm
	diff_out=$(diff -w $out/resize2.pgm  $key/aresize2.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "resize2.pgm different" >&3;fi
	
  #$i/test_resize asterisk.alpha 2.0 alpha|eval $clean > $out/resize3.alpha
  #$i/test_resize $out/resize3.alpha 0.5 alpha|eval $clean > $out/resize31.pgm
  #diff_out=$(diff -w $out/resize3.pgm  $key/aresize3.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$")
	
		
	echo -e "-----------------------------------\n##write-file test\n..................................." >&3
	g++ -Wall write_file.cc $i/hw4.a -I $i/ -o $i/test_file
	timeout 10s $i/test_file simple.alpha alpha >&3 && mv out_* $out/ 
	timeout 10s $i/test_file simple.pgm pgm >&3 && mv out_* $out/ 
	diff_out=$(diff -w $out/out_simple.pgm  $key/aout_simple.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$") 
  if [[ ! -z "$diff_out" ]];then echo "out_simple.pgm different" >&3;fi
	diff_out=$(diff -w $out/out_simple.alpha  $key/aout_simple.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "out_simple.alpha different" >&3;fi
	
	echo -e "-----------------------------------\n##read-file test\n..................................." >&3
	g++ -Wall read_file.cc $i/hw4.a -I $i/ -o $i/test_read
	# Good read alpha
	timeout 10s $i/test_read asterisk.alpha alpha| eval $clean > $out/read1.alpha
	timeout 10s $i/test_read comments.alpha alpha| eval $clean > $out/read2.alpha
	# Bad read alpha
	timeout 10s $i/test_read bad_char.alpha alpha| eval $clean > $out/read3.alpha
	timeout 10s $i/test_read asterisk_bad.alpha alpha| eval $clean > $out/read4.alpha
	# Good read pgm
	timeout 10s $i/test_read luna.pgm pgm | eval $clean > $out/read5.pgm
	# Bad read pgm
	timeout 10s $i/test_read range_bad.pgm pgm | eval $clean > $out/read6.pgm
  diff_out=$(diff -w $out/read1.alpha  $key/aread1.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "read1.alpha different" >&3;fi
  diff_out=$(diff -w $out/read2.alpha  $key/aread2.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "read2.alpha different" >&3;fi
  diff_out=$(diff -w $out/read3.alpha  $key/aread3.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "read3.alpha different" >&3;fi
  diff_out=$(diff -w $out/read4.alpha  $key/aread4.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "read4.alpha different" >&3;fi
  diff_out=$(diff -w $out/read5.pgm  $key/aread5.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "read5.pgm different" >&3;fi
  diff_out=$(diff -w $out/read6.pgm  $key/aread6.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "read6.pgm different" >&3;fi
	
	echo -e "-----------------------------------\n##Copy-Ctor test\n..................................." >&3
	g++ -Wall copy_constructor.cc $i/hw4.a -I $i/ -o $i/test_cctor
	timeout 10s $i/test_cctor hi.alpha alpha >&3 
	timeout 10s $i/test_cctor hi.pgm pgm >&3 
	mv *_cons.* $out/
	cat $out/copy_cons.pgm | eval $clean > $out/copy_cons1.pgm
	cat $out/copy_cons.alpha| eval $clean > $out/copy_cons1.alpha
	cat $out/orig_cons.pgm | eval $clean > $out/orig_cons1.pgm
	cat $out/orig_cons.alpha | eval $clean > $out/orig_cons1.alpha
  diff_out=$(diff -w $out/copy_cons1.alpha  $key/acopy_cons1.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "copy_cons1.alpha different" >&3;fi
  diff_out=$(diff -w $out/orig_cons1.alpha  $key/aorig_cons1.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$") 
  if [[ ! -z "$diff_out" ]];then echo "orig_cons1.alpha different" >&3;fi
  diff_out=$(diff -w $out/copy_cons1.pgm  $key/acopy_cons1.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$") 
  if [[ ! -z "$diff_out" ]];then echo "copy_cons1.pgm different" >&3;fi
  diff_out=$(diff -w $out/orig_cons1.pgm  $key/aorig_cons1.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$")
  if [[ ! -z "$diff_out" ]];then echo "orig_cons1.pgm different" >&3;fi

	echo -e "-----------------------------------\n##Operator-Assignment test\n..................................." >&3
	g++ -Wall operator_assignment.cc $i/hw4.a -I $i/ -o $i/test_assign
	timeout 10s $i/test_assign alpha >&3 && mv assign.* $out/
	timeout 10s $i/test_assign pgm >&3 && mv assign.* $out/
	cat $out/assign.alpha | eval $clean > $out/assign1.alpha
	cat $out/assign.pgm | eval $clean > $out/assign1.pgm
  diff_out=$(diff -w $out/assign1.alpha  $key/aassign1.alpha|grep -vE ">[[:space:]]$|<[[:space:]]$") 
  if [[ ! -z "$diff_out" ]];then echo "assign1.alpha different" >&3;fi
  diff_out=$(diff -w $out/assign1.pgm  $key/aassign1.pgm|grep -vE ">[[:space:]]$|<[[:space:]]$") 
  if [[ ! -z "$diff_out" ]];then echo "assign1.pgm different" >&3;fi

	echo -e "-----------------------------------\n##COUT test\n..................................." >&3
	g++ -Wall cout.cc $i/hw4.a -I $i/ -o $i/test_cout
	timeout 10s $i/test_cout alpha| eval $clean >&3
	timeout 10s $i/test_cout pgm | eval $clean >&3
	
	# Redundant test that will always fail as const object was being changed.
	#echo -e "-----------------------------------\n##Const-correctness test\n..................................." >&3
	#g++ -Wall const_correctness.cc $i/hw4.a -I $i/ -o $i/test_const
	#if [[ -f $i/test_const ]]; then timeout 10s $i/test_const >&3 && mv assign.* $out/;fi
	
	
	exec 3>&- #close fd 3.
	echo "Creating difference file with key"
	diff -w $key/alogger.out $out/logger.out |grep -vE ">[[:space:]]$|<[[:space:]]$" > $out/final.out
done
