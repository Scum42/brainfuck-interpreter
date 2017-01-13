,           # Read the first character in the input

[           # If there was no input, the read was zero and this will be skipped
    >       # Move to the next cell
    ,       # Read the next input to that cell
]           # If there was no more input, the read will be zero and the loop will end

<           # When the loop ends, the current cell is zero, so go left

[
    <       # Keep going left until before the first character (which will be zero)
]

>           # Go right to get to the first character we read

[
    .       # Output the character and move right
    >       # This will continue until the first zero, at the end of the string
]