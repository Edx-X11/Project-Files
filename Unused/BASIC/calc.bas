10 PRINT "Welcome to the Basic Calculator!"
20 INPUT "Enter first number: "; num1
30 INPUT "Enter second number: "; num2
40 INPUT "Enter operation (+, -, *, /): "; operation$
50 IF operation$ = "+" THEN PRINT "Result: "; num1 + num2
60 IF operation$ = "-" THEN PRINT "Result: "; num1 - num2
70 IF operation$ = "*" THEN PRINT "Result: "; num1 * num2
80 IF operation$ = "/" THEN PRINT "Result: "; num1 / num2
90 END
