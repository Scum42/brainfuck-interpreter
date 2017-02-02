[ TL:201, HORZ:205, TR:187, VERT:186, BR:188, BL:200, NEWLINE:10 ]

## Set up values

# Newline (10) in cell 0

> ++
[
	< +++++
	> -
]

## Put 196 as a starter into the next 6 cells (1 through 7)

# Move to cell 7

>>>>>>

# Put 14x14 (196) in cell 8

+++++ +++++ ++++
[
	> +++++ +++++ ++++
	< -
]

# Copy 196 to cells 1 through 6

>

[
	<< +
	< +
	< +
	< +
	< +
	< +
	>>>>>>> -
]

# Increase cell 6 to 200

<< ++++

# Decrease cell 5 to 188

< ----- ---

# Decrease cell 4 to 186

< ----- -----

# Decrease cell 3 to 187

< ----- ----

# Increase cell 2 to 205

< +++++ ++++

# Increase cell 1 to 201

< +++++

#            V
#    0       1         2         3         4         5        6
# (NL:10 | TL:201 | HORZ:205 | TR:187 | VERT:186 | BR:188 | BL:200)

# Print TL

.

# Print HORZx10

> ..... .....

# Print TR

> .

# Print NL

<<< .

# Print VERT

>>>> .

# Print NULx10

>>> ..... .....

# Print VERT

<<< .

# Print NL

<<<< .

# Print BL

>>>>>> .

# Print HORZx10

<<<< ..... .....

# Print BR

>>> .

# Print NL

<<<<< .
