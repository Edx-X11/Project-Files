10 PRINT "Data Analysis Tool"
20 PRINT "--------------------"

30 REM Input data (replace with your own data)
40 LET data = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]

50 REM Calculate basic statistics
60 LET n = 10
70 LET sum = 0
80 LET sum_squared = 0
90 LET min_value = data[1]
100 LET max_value = data[1]

110 FOR i = 1 TO n
120   LET sum = sum + data[i]
130   LET sum_squared = sum_squared + data[i] * data[i]
140   IF data[i] < min_value THEN min_value = data[i]
150   IF data[i] > max_value THEN max_value = data[i]
160 NEXT i

170 LET average = sum / n
180 LET variance = (sum_squared / n) - (average * average)
190 LET standard_deviation = SQR(variance)

200 PRINT "Advanced Statistics:"
210 PRINT "---------------------"
220 PRINT "Sum: "; sum
230 PRINT "Average: "; average
240 PRINT "Minimum Value: "; min_value
250 PRINT "Maximum Value: "; max_value
260 PRINT "Variance: "; variance
270 PRINT "Standard Deviation: "; standard_deviation

280 PRINT "---------------------"
290 PRINT "Thank you for using the Data Analysis Tool"
