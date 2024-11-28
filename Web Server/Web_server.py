from flask import Flask, render_template, jsonify
from datetime import datetime

app = Flask(__name__)

# Biến lưu giá trị ánh sáng mới nhất
current_light = 0

@app.route('/')
def index():
    return render_template('server.html')

@app.route('/update_light/<float:value>')
def update_light(value):
    global current_light
    current_light = value
    timestamp = datetime.now().strftime('%H:%M:%S')
    return jsonify({"status": "success"})

@app.route('/get_light')
def get_light():
    return jsonify({
        "light": current_light,
        "timestamp": datetime.now().strftime('%H:%M:%S')
    })

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)