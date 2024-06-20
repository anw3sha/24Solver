function generateSolutions() {
    const num1 = document.getElementById('num1').value;
    const num2 = document.getElementById('num2').value;
    const num3 = document.getElementById('num3').value;
    const num4 = document.getElementById('num4').value;
    const target = document.getElementById('target').value;

    fetch('/generate_solutions', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ num1, num2, num3, num4, target })
    })
    .then(response => response.json())
    .then(data => {
        const resultsDiv = document.getElementById('results');
        resultsDiv.innerHTML = '';
        if (data.solutions.length > 0) {
            data.solutions.forEach(solution => {
                const p = document.createElement('p');
                p.textContent = solution;
                resultsDiv.appendChild(p);
            });
        } else {
            resultsDiv.textContent = 'No solutions found.';
        }
    })
    .catch(error => {
        console.error('Error:', error);
        const resultsDiv = document.getElementById('results');
        resultsDiv.textContent = 'Error: ' + error;
    });
}