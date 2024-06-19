import os
from flask import Flask, request, jsonify, render_template
import subprocess

# Get the current directory of the script
current_dir = os.path.dirname(__file__)
template_dir = os.path.join(current_dir, '.')

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

    nums = [
        int(data['num1']),
        int(data['num2']),
        int(data['num3']),
        int(data['num4'])
    ]
    target = int(data['target'])

    try:
        solutions = solve_with_cpp(nums, target)
        print(f"Solutions: {solutions}")  # Debug print
        if solutions:
            return jsonify({'solutions': solutions})
        else:
            return jsonify({'solutions': ['No solutions found.']})
    except Exception as e:
        print(f"Error: {e}")  # Debug print
        return jsonify({'error': str(e)})

if __name__ == '__main__':
    app.run(debug=True)