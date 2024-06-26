cat > test1.txt <<EOL


str          !


     

	 end.
EOL

cat > test2.txt <<EOL

str          !


     

	 end.



EOL

cat > test3.txt <<EOL

str          !

()
   ()  
()
	 end.

EOL

cat > test4.txt <<EOL

str          !






	 end.



EOL

cat > test5.txt <<EOL
0 - ( )
1 - ()
2 - ()
3 - ()
4 - ()
5 - ()
6 - ()
7 - ()
8 - ()
9 - (	)
10 - (
)
11 - ()
12 - ()
13 - (
)
14 - ()
15 - ()
16 - ()
17 - ()
18 - ()
19 - ()
20 - ()
21 - ()
22 - ()
23 - ()
24 - ()
25 - ()
26 - ()
27 - ()
28 - ()
29 - ()
30 - ()
31 - ()
32 - ( )
33 - (!)
34 - (")
35 - (#)
36 - ($)
37 - (%)
38 - (&)
39 - (')
40 - (()
41 - ())
42 - (*)
43 - (+)
44 - (,)
45 - (-)
46 - (.)
47 - (/)
48 - (0)
49 - (1)
50 - (2)
51 - (3)
52 - (4)
53 - (5)
54 - (6)
55 - (7)
56 - (8)
57 - (9)
58 - (:)
59 - (;)
60 - (<)
61 - (=)
62 - (>)
63 - (?)
64 - (@)
65 - (A)
66 - (B)
67 - (C)
68 - (D)
69 - (E)
70 - (F)
71 - (G)
72 - (H)
73 - (I)
74 - (J)
75 - (K)
76 - (L)
77 - (M)
78 - (N)
79 - (O)
80 - (P)
81 - (Q)
82 - (R)
83 - (S)
84 - (T)
85 - (U)
86 - (V)
87 - (W)
88 - (X)
89 - (Y)
90 - (Z)
91 - ([)
92 - (\)
93 - (])
94 - (^)
95 - (_)
96 - (``)
97 - (a)
98 - (b)
99 - (c)
100 - (d)
101 - (e)
102 - (f)
103 - (g)
104 - (h)
105 - (i)
106 - (j)
107 - (k)
108 - (l)
109 - (m)
110 - (n)
111 - (o)
112 - (p)
113 - (q)
114 - (r)
115 - (s)
116 - (t)
117 - (u)
118 - (v)
119 - (w)
120 - (x)
121 - (y)
122 - (z)
123 - ({)
124 - (|)
125 - (})
126 - (~)
127 - ()
EOL


# Run s21_cat with different flags and compare output with cat
echo "Running s21_cat tests..."
echo

# Test 1: -b flag
echo "Test 1: -b flag"
./s21_cat -b test1.txt > s21_output1.txt
cat -b test1.txt > cat_output1.txt
if diff s21_output1.txt cat_output1.txt >/dev/null; then
    echo "OK"
else
    echo "Fail"
fi
echo

# Test 2: -n flag
echo "Test 2: -n flag"
./s21_cat -n test1.txt > s21_output2.txt
cat -n test1.txt > cat_output2.txt
if diff s21_output2.txt cat_output2.txt >/dev/null; then
echo "OK"
else
echo "Fail"
fi
echo

# Test 3: --number-nonblank flag
echo "Test 3: --number-nonblank flag"
./s21_cat --number-nonblank test1.txt > s21_output3.txt
cat -b test1.txt > cat_output3.txt
if diff s21_output3.txt cat_output3.txt >/dev/null; then
echo "OK"
else
echo "Fail"
fi
echo

# Test 4: --number flag
echo "Test 4: --number flag"
./s21_cat --number test1.txt > s21_output4.txt
cat -n test1.txt > cat_output4.txt
if diff s21_output4.txt cat_output4.txt >/dev/null; then
echo "OK"
else
echo "Fail"
fi
echo

# Test 5: -s flag
echo "Test 5: -s flag"
./s21_cat -s test2.txt > s21_output5.txt
cat -s test2.txt > cat_output5.txt
if diff s21_output5.txt cat_output5.txt >/dev/null; then
    echo "OK"
else
    echo "Fail"
fi
echo

# Test 6: --squeeze-blank flag
echo "Test 5: --squeeze-blank flag"
./s21_cat --squeeze-blank test2.txt > s21_output6.txt
cat -s test2.txt > cat_output6.txt
if diff s21_output6.txt cat_output6.txt >/dev/null; then
echo "OK"
else
echo "Fail"
fi
echo

# Test 7: -t flag
echo "Test 7: -t flag"
./s21_cat -t test3.txt > s21_output7.txt
cat -t test3.txt > cat_output7.txt
if diff s21_output3.txt cat_output7.txt >/dev/null; then
    echo "OK"
else
    echo "Fail"
fi
echo

# Test 8: -e flag
echo "Test 8: -e flag"
./s21_cat -e test5.txt > s21_output8.txt
cat -e test5.txt > cat_output8.txt
if diff s21_output8.txt cat_output8.txt >/dev/null; then
    echo "OK"
else
    echo "Fail"
fi
echo

# Test 9: -benst flag
echo "Test 9: -benst flag"
./s21_cat -benst test4.txt > s21_output9.txt
cat -benst test4.txt > cat_output9.txt
if diff s21_output9.txt cat_output9.txt >/dev/null; then
echo "OK"
else
echo "Fail"
fi
echo

# Clean up test files
rm test1.txt test2.txt test3.txt test4.txt test5.txt s21_output1.txt s21_output2.txt s21_output3.txt s21_output4.txt s21_output5.txt s21_output6.txt s21_output7.txt s21_output8.txt s21_output9.txt cat_output1.txt cat_output2.txt cat_output3.txt cat_output4.txt cat_output5.txt cat_output6.txt cat_output7.txt cat_output8.txt cat_output9.txt

echo
echo "Tests completed."

