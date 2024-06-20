import os
from flask import Flask, request, jsonify, render_template
import subprocess

# Get the current directory of the script
current_dir = os.path.dirname(__file__)
template_dir = os.path.join(current_dir, 'templates')

app = Flask(__name__, template_folder=template_dir)

def solve_with_cpp(nums, target):
    input_data = f"{nums[0]} {nums[1]} {nums[2]} {nums[3]}\n{target}"
    input_file = os.path.join(current_dir, 'input.txt')
    
    with open(input_file, 'w') as f:
        f.write(input_data)

    cpp_program = os.path.join(current_dir, '24solver')
    result = subprocess.run([cpp_program], capture_output=True, text=True, cwd=current_dir)

    solutions = result.stdout.strip().split('\n')
    if solutions[0] == "No solutions found.":
        solutions = []

    return solutions

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/generate_solutions', methods=['POST'])
def generate_solutions():
    data = request.json
    print(f"Received data: {data}")  # Debug print

    try:
        nums = [
            int(data['num1']),
            int(data['num2']),
            int(data['num3']),
            int(data['num4'])
        ]
        target = int(data['target'])

        solutions = solve_with_cpp(nums, target)
        print(f"Solutions: {solutions}")  # Debug print
        if solutions:
            return jsonify({'solutions': solutions})
        else:
            return jsonify({'solutions': ['No solutions found.']})
    except ValueError as ve:
        error_message = f"Invalid input: {str(ve)}"
        print(f"Error: {error_message}")  # Debug print
        return jsonify({'error': error_message}), 400  # Return HTTP 400 Bad Request
    except Exception as e:
        error_message = f"Internal server error: {str(e)}"
        print(f"Error: {error_message}")  # Debug print
        return jsonify({'error': error_message}), 500  # Return HTTP 500 Internal Server Error

if __name__ == '__main__':
    app.run(debug=True)