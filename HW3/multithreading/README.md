STEPS TO EXECUTE MULTITHREAD:

1. Run make
2. This creates the multithred executable
3. Execute ./multithread threads.txt where threads.txt is the filename
4. Enter text. Terminate entry by adding '~' in a new line
4. Open another terminal and run: pkill -USR1 multithread
5. This computes statistics of the file
6. Run: pkill -USR2 multithread
7. This prints out statistics of the file
8. Press Cntrl+C to have a graceful exit
