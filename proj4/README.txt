William(Liam) Campbell 811374731
    whc06250@uga.edu

    to compile: use makefile "make"

    to run: ./proj4.out input.txt output.txt sum (#of threads)


    findings from running test cases:
    The smaller the input file the smaller the performance difference between 1 2 3 threaded
    processes. Eventually if the file is too small creating new threads will be slower than
    doing the process with a single thread. the most noticeable difference is the largest input file where a single
    thread takes three times as long as a 3 threaded process.
