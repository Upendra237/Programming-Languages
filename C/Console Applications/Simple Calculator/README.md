# Simple Calculator

A beginner-friendly calculator written in C with a clean, modular design.

## Features

- Basic arithmetic operations (+, -, *, /, %, ^)
- Mathematical functions (sqrt, abs, round, ceil, floor)
- Simple transformations (inc, dec, double, half, square, cube)
- Comparison operations (max, min, avg)
- Number checking (positive, negative, zero)
- Interactive command-line interface
- Minimal dependencies (only requires stdio.h)
- Clear error handling

## Installation

### Prerequisites
- GCC or any C compiler

### Compiling
```bash
# Compile the source code
gcc calculator.c -o calculator

# Run the program
./calculator
```

## Usage

1. Run the program
2. Enter calculations at the `Calculate>` prompt
3. Type `help` to see available commands
4. Type `cls` to clear the screen
5. Type `exit` to quit the program

## Command Reference

### Two-number Operations
- `a + b` - Addition
- `a - b` - Subtraction
- `a * b` - Multiplication
- `a / b` - Division
- `a % b` - Modulus (remainder)
- `a ^ b` - Power (a raised to power b)
- `max a b` - Maximum value
- `min a b` - Minimum value
- `avg a b` - Average value

### Single-number Operations
- `sqrt a` - Square root
- `abs a` - Absolute value
- `round a` - Round to nearest integer
- `ceil a` - Round up to nearest integer
- `floor a` - Round down to nearest integer
- `inc a` - Increment by 1
- `dec a` - Decrement by 1
- `double a` - Multiply by 2
- `half a` - Divide by 2
- `square a` - Square the number
- `cube a` - Cube the number

### Check Operations
- `pos a` - Is positive? (returns 1 for true, 0 for false)
- `neg a` - Is negative? (returns 1 for true, 0 for false)
- `zero a` - Is zero? (returns 1 for true, 0 for false)

### System Commands
- `cls` - Clear screen
- `exit` - Exit program
- `help` - Show help information

## Test Cases

### Arithmetic Operations

| Input | Expected Output | Description |
|-------|----------------|-------------|
| `5 + 3` | `8.00` | Basic addition |
| `10 + -5` | `5.00` | Addition with negative number |
| `0 + 0` | `0.00` | Addition with zeros |
| `10 - 4` | `6.00` | Basic subtraction |
| `5 - 10` | `-5.00` | Subtraction resulting in negative |
| `5 - -3` | `8.00` | Subtraction with negative number |
| `7 * 6` | `42.00` | Basic multiplication |
| `5 * -3` | `-15.00` | Multiplication with negative |
| `0 * 10` | `0.00` | Multiplication with zero |
| `20 / 4` | `5.00` | Basic division |
| `15 / 2` | `7.50` | Division with decimal result |
| `5 / 0` | `Error: Cannot divide by zero` | Division by zero error |
| `17 % 5` | `2.00` | Basic modulus |
| `10 % 2` | `0.00` | Modulus with no remainder |
| `5 % 0` | `Error: Cannot find modulus with zero divisor` | Modulus by zero error |
| `2 ^ 3` | `8.00` | Basic power operation |
| `5 ^ 2` | `25.00` | Square using power |
| `2 ^ 0` | `1.00` | Power with zero exponent |
| `2 ^ -2` | `0.25` | Power with negative exponent |

### Mathematical Functions

| Input | Expected Output | Description |
|-------|----------------|-------------|
| `sqrt 16` | `4.00` | Square root of perfect square |
| `sqrt 2` | `1.41` | Square root with decimal result |
| `sqrt 0` | `0.00` | Square root of zero |
| `sqrt -4` | `Error: Cannot calculate square root of negative number` | Square root error |
| `abs 5` | `5.00` | Absolute value of positive |
| `abs -5` | `5.00` | Absolute value of negative |
| `abs 0` | `0.00` | Absolute value of zero |
| `round 3.2` | `3.00` | Round down |
| `round 3.7` | `4.00` | Round up |
| `round -3.7` | `-4.00` | Round negative down |
| `round -3.2` | `-3.00` | Round negative up |
| `ceil 3.2` | `4.00` | Ceiling of positive |
| `ceil -3.2` | `-3.00` | Ceiling of negative |
| `floor 3.7` | `3.00` | Floor of positive |
| `floor -3.7` | `-4.00` | Floor of negative |

### Transformations

| Input | Expected Output | Description |
|-------|----------------|-------------|
| `inc 5` | `6.00` | Increment positive |
| `inc -1` | `0.00` | Increment negative to zero |
| `dec 5` | `4.00` | Decrement positive |
| `dec 0` | `-1.00` | Decrement zero |
| `double 4` | `8.00` | Double positive |
| `double -3` | `-6.00` | Double negative |
| `half 10` | `5.00` | Half of positive even |
| `half 5` | `2.50` | Half of positive odd |
| `half -8` | `-4.00` | Half of negative |
| `square 4` | `16.00` | Square positive |
| `square -3` | `9.00` | Square negative |
| `square 0` | `0.00` | Square zero |
| `cube 3` | `27.00` | Cube positive |
| `cube -2` | `-8.00` | Cube negative |
| `cube 0` | `0.00` | Cube zero |

### Comparisons

| Input | Expected Output | Description |
|-------|----------------|-------------|
| `max 5 10` | `10.00` | Max with second larger |
| `max 10 5` | `10.00` | Max with first larger |
| `max -5 -10` | `-5.00` | Max with negative numbers |
| `min 5 10` | `5.00` | Min with first smaller |
| `min 10 5` | `5.00` | Min with second smaller |
| `min -5 -10` | `-10.00` | Min with negative numbers |
| `avg 10 20` | `15.00` | Average of positives |
| `avg -10 10` | `0.00` | Average of positive and negative |
| `avg -10 -20` | `-15.00` | Average of negatives |

### Boolean Checks

| Input | Expected Output | Description |
|-------|----------------|-------------|
| `pos 5` | `1.00` | Check positive (true) |
| `pos 0` | `0.00` | Check zero for positive (false) |
| `pos -5` | `0.00` | Check negative for positive (false) |
| `neg -5` | `1.00` | Check negative (true) |
| `neg 0` | `0.00` | Check zero for negative (false) |
| `neg 5` | `0.00` | Check positive for negative (false) |
| `zero 0` | `1.00` | Check zero (true) |
| `zero 5` | `0.00` | Check positive for zero (false) |
| `zero -5` | `0.00` | Check negative for zero (false) |

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgements

- Inspired by the need for a simple educational calculator
- Designed for beginning C programmers