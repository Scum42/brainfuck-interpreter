# First of all we need to parse the inputs

,					# Read input character to cell 0

>> +++++ +			# Put six in cell 2

[
	< +++++ +++		# Multiply six by eight
	> -
]

# Now cell 1 has 48 and cursor is on cell 2

<					# Move to cell 1

[
	< -				# Subtract cell 1 from cell 0
	> -
]

# Now cell 0 should have the value represented by input char
# cursor is on cell 1
# and cells 1 and 2 should be empty

<

[
	> +				# Copy cell 0 to cells 1 and 2
	> +
	<< -
]

>					# Move to cell 1 (first number)

[
	>
	
	[
		> +			# Copy 2 to 3 and 4 (4 is the total)
		> +
		<< -
	]
	
	>
	
	[
		< +			# Move 3 to 2
		> -
	]
	
	<< -
]

*

# |0|0|x|0|x^2|
#    ^
