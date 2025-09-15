use rusqlite::{Connection, Result, functions::FunctionFlags};
use std::time::Instant;

fn main() -> Result<()> {
    // 메모리 DB 연결
    let conn = Connection::open_in_memory()?;
    
    // 사용자 정의 함수 upper 등록 (rusqlite는 이미 UPPER 함수 내장, 예시로 커스텀 등록)
    conn.create_scalar_function(
        "upper",
        1,
        FunctionFlags::SQLITE_UTF8,
        |ctx| {
            let s: String = ctx.get::<String>(0)?;
            Ok(s.to_uppercase())
        }
    )?;

    let mut result = String::new();
    let start = Instant::now();

    for _ in 0..100_000 {
        let mut stmt = conn.prepare("SELECT upper('hello world') as uppercased")?;
        let mut rows = stmt.query([])?;
        if let Some(row) = rows.next()? {
            result = row.get::<_, String>(0)?;
        }
    }

    let elapsed_ms = start.elapsed().as_millis();

    println!("{}", result); // HELLO WORLD
    println!("Execution time: {} ms", elapsed_ms);

    Ok(())
}