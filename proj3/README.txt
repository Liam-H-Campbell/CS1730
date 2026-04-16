William(Liam) Campbell 811374731
    whc06250@uga.edu


    to compile: use Makefile

    to run: ./proj3.out text1.txt text2.txt


    as long as the first file isnt much smaller than the second file then step1 will take more time.
    this is because the loops insid step 1 are reliant on the size of text1 and the loop inside text2 is reliant
    on the size of text2.

    if text1 and text2 have a similar size then step1 will take longer than step2.

    this is because getc is called every iteration of the loop in step 1

    and fread is called once for each file in step2.

    making step2 the more efficient comparison.
