import sqlite3
import time

conn = sqlite3.connect(":memory:") # Or specify a database file path

def toUpperCase(value):
    return value.upper()

conn.create_function("upper", 1, toUpperCase);

cursor = conn.cursor()
cursor.execute("SELECT upper('hello world') as uppercased;")
result = cursor.fetchone()[0]
start_ms = time.time() * 1000  # 시작 시간 (밀리초)
for _ in range(100000):
    cursor.execute("SELECT upper('hello world') as uppercased;")
    result = cursor.fetchone()[0]
end_ms = time.time() * 1000  # 종료 시간 (밀리초)
print(result) # Output: HELLO WORLD
print(f"Execution time: {end_ms - start_ms} ms")
conn.close()