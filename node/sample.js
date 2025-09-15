const Database = require('better-sqlite3');
const db = new Database(':memory:');

function toUpperCase(text) {
  return text.toUpperCase();
}

db.function('upper', toUpperCase);

const start = performance.now();

let result = db.prepare("SELECT upper('hello world') as uppercased").get();
for (let i = 0; i < 100000; i++) {
  result = db.prepare("SELECT upper('hello world') as uppercased").get();
}
console.log(result.uppercased); // HELLO WORLD
const end = performance.now();
console.log(`Execution time: ${end - start} ms`); 