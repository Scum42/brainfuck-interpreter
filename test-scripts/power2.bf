# First of all we need to parse the inputs

,					# Read input character to cell 0

> +++++ +			# Put six in cell 1

[
	> +++++ +++		# Multiply six by eight
	< -
]

# Now cell 2 has 48 and cursor is on cell 1

>					# Move to cell 2

[
	<< -			# Subtract cell 2 from cell 0
	>> -
]

<<					# Move back to cell 0

# Now cell 0 should have the value represented by input char
# and cells 1 and 2 should be empty

> +					# Put 1 in cell 1 to start with (we'll be multiplying this by two a bunch)
<					# Move back to cell 0

[	
	>				# Move over to cell 1 (which has the total in it)
	
	[
		> ++		# Multiply that number by two (putting the result in cell 2)
		< -
	]
	
	>				# Move over to cell 2
	
	[
		< +			# Move value in cell 2 to cell 1 (it's the new total)
		> -
	]
	
	<< -			# Dec cell 0
]

>					# Place the cursor under cell 1 (where the output is)

*					# Dump