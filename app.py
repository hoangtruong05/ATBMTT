# app.py - API Server sử dụng Flask

from flask import Flask, request, jsonify
from Crypto.Cipher import DES, DES3
from Crypto.Util.Padding import pad, unpad
from base64 import b64encode, b64decode
from flask_cors import CORS # Cần thiết cho việc chạy Frontend và Backend trên các cổng khác nhau

app = Flask(__name__)
# Cho phép yêu cầu từ trình duyệt (Frontend)
CORS(app) 

# --- HÀM HỖ TRỢ DES (Từ code Python gốc) ---

# Padding (PKCS7 tương đương với CryptoJS.pad.Pkcs7)
def custom_pad(data):
    # PyCryptodome's pad function handles PKCS7 padding by default for 8-byte blocks
    return pad(data, DES.block_size) 

def custom_unpad(data):
    # PyCryptodome's unpad function handles PKCS7 unpadding by default
    return unpad(data, DES.block_size)


# === CÁC HÀM ENCRYPT/DECRYPT CHÍNH ===

def single_des_cipher(data_bytes, key_bytes, is_encrypt):
    cipher = DES.new(key_bytes, DES.MODE_ECB)
    if is_encrypt:
        padded_bytes = custom_pad(data_bytes)
        return cipher.encrypt(padded_bytes)
    else:
        decrypted_bytes = cipher.decrypt(data_bytes)
        return custom_unpad(decrypted_bytes)

# EDE (Triple DES 2 key) - Mã hóa/Giải mã 3DES chuẩn
def triple_des_cipher(data_bytes, key_bytes, is_encrypt):
    # DES3.new sẽ tự động xử lý 2-key (16 byte) hoặc 3-key (24 byte)
    cipher = DES3.new(key_bytes, DES3.MODE_ECB)
    if is_encrypt:
        padded_bytes = custom_pad(data_bytes)
        return cipher.encrypt(padded_bytes)
    else:
        decrypted_bytes = cipher.decrypt(data_bytes)
        return custom_unpad(decrypted_bytes)


# Double DES: E(K2, E(K1, P))
def double_des_cipher(data_bytes, key_bytes, is_encrypt):
    key1, key2 = key_bytes[:8], key_bytes[8:16]
    
    if is_encrypt:
        # Bước 1: E(K1, P)
        cipher1 = DES.new(key1, DES.MODE_ECB)
        temp_padded = custom_pad(data_bytes) # PADDING BƯỚC ĐẦU
        temp = cipher1.encrypt(temp_padded)
        
        # Bước 2: E(K2, temp) - Không cần padding lại
        cipher2 = DES.new(key2, DES.MODE_ECB)
        result = cipher2.encrypt(temp)
        return result
    else:
        # Bước 1: D(K2, C)
        cipher2 = DES.new(key2, DES.MODE_ECB)
        temp = cipher2.decrypt(data_bytes)
        
        # Bước 2: D(K1, temp) - UNPADDING BƯỚC CUỐI
        cipher1 = DES.new(key1, DES.MODE_ECB)
        result = cipher1.decrypt(temp)
        return custom_unpad(result)


# --- ĐIỂM CUỐI API (API Endpoints) ---

@app.route('/process', methods=['POST'])
def process_data():
    data = request.json
    mode = data.get('mode') # Single, Double, Triple
    key_hex = data.get('key').strip()
    input_data = data.get('input').strip()
    action = data.get('action') # encrypt, decrypt
    
    # 1. Kiểm tra đầu vào cơ bản
    if not all([mode, key_hex, input_data, action]):
        return jsonify({"success": False, "error": "Missing input data (mode, key, input, or action)"}), 400

    # 2. Xử lý Key
    try:
        key_bytes = bytes.fromhex(key_hex)
        req_len = {'Single': 8, 'Double': 16, 'Triple': 24}
        if len(key_bytes) != req_len.get(mode):
            return jsonify({"success": False, "error": f"Invalid key length for {mode} DES. Expected {req_len.get(mode)} bytes, got {len(key_bytes)}."}), 400
    except ValueError:
        return jsonify({"success": False, "error": "Key must be a valid hex string."}), 400

    is_encrypt = (action == 'encrypt')
    result = ""
    
    try:
        if is_encrypt:
            input_bytes = input_data.encode('utf-8')
            if mode == 'Single':
                result_bytes = single_des_cipher(input_bytes, key_bytes, True)
            elif mode == 'Double':
                result_bytes = double_des_cipher(input_bytes, key_bytes, True)
            elif mode == 'Triple':
                result_bytes = triple_des_cipher(input_bytes, key_bytes, True)
                
            # Kết quả mã hóa: Base64
            result = b64encode(result_bytes).decode('ascii')
            
        else: # Decrypt
            input_bytes = b64decode(input_data)
            
            if mode == 'Single':
                result_bytes = single_des_cipher(input_bytes, key_bytes, False)
            elif mode == 'Double':
                result_bytes = double_des_cipher(input_bytes, key_bytes, False)
            elif mode == 'Triple':
                result_bytes = triple_des_cipher(input_bytes, key_bytes, False)
                
            # Kết quả giải mã: UTF-8 string
            result = result_bytes.decode('utf-8')
            
    except Exception as e:
        # Bắt lỗi giải mã (Sai khóa, sai padding, bản mã hỏng)
        return jsonify({"success": False, "error": f"Encryption/Decryption Error: {str(e)}", "detail": str(e)}), 400
        
    return jsonify({"success": True, "result": result, "mode": mode, "action": action})


if __name__ == '__main__':
    # Chạy server tại localhost:5000 (mặc định của Flask)
    app.run(debug=True, port=5000)