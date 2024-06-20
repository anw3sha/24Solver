<h1>24 Solver</h1>

## Description
The 24 Solver is a web application that allows users to input four numbers and a target result. It generates mathematical expressions using the four numbers (addition, subtraction, multiplication, and division) to achieve the target result of 24. This was developed with the game 24 in mind but expanded to input any target result, not necessarily just the number 24.

## Features
1. Input four numbers and a target result.
2. Generate all possible mathematical expressions using the four numbers and basic arithmetic operations (+, -, *, /) that equate to the target result.
3. Display solutions or indicate if no solutions are found.
4. Handle non-integer inputs and provide appropriate error messages.

## Development
- **Frontend**: HTML, CSS, JavaScript
- **Backend**: Python, Flask
- **Solver**: C++

## Usage
To run the application:
1. Clone the repository.
2. Install necessary dependencies.
3. Start the Flask server with `python server.py`.
4. Open your web browser and navigate to `http://localhost:5000` to use the application.

- Enter the four numbers and your target result in the indicated fields.
- Click on the generate button to generate all possible solutions found.
- Solutions will be displayed below the input buttons. If no solutions exist, this will be indicated in the same area. 

## Description
The `24-solver` project consists of several components:

- **server.py**: Flask server script that handles the backend logic and serves the HTML templates.
- **templates/**: Contains the HTML template (`index.html`) for the frontend interface of the application.
- **static/**: Includes static files like `style.css` and `script.js`, which provides styling for the HTML templates.
- **24solver.cpp**: C++ program that generates mathematical solutions based on input data.
- **input.txt**: Input file used by `24solver.cpp` to read the numbers and target result.
- **requirements.txt**: File that includes all the dependencies necessary to run this code. A C++ compiler may be required if the solver needs to be recompiled. 
