10 PRINT "Prime Number Checker"
20 INPUT "Enter a number: "; num
30 isPrime = 1
40 FOR i = 2 TO num / 2
50     IF num MOD i = 0 THEN isPrime = 0: EXIT FOR
60 NEXT i
70 IF isPrime THEN PRINT num; " is a prime number."
80 IF NOT isPrime THEN PRINT num; " is not a prime number."
90 END
