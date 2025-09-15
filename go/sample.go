package main

import (
	"database/sql"
	"fmt"
	"strings"
	"time"

	_ "github.com/mattn/go-sqlite3"
	"github.com/mattn/go-sqlite3"
)

func main() {
	// 사용자 정의 함수 등록을 위해 Driver를 커스터마이징합니다.
	sql.Register("sqlite3_with_upper", &sqlite3.SQLiteDriver{
		ConnectHook: func(conn *sqlite3.SQLiteConn) error {
			// 사용자 정의 upper 함수 등록
			return conn.RegisterFunc("upper", strings.ToUpper, true)
		},
	})

	db, err := sql.Open("sqlite3_with_upper", ":memory:")
	if err != nil {
		panic(err)
	}
	defer db.Close()

	var result string
	row := db.QueryRow("SELECT upper('hello world') as uppercased")
	row.Scan(&result)
	
	start := time.Now()

	for i := 0; i < 100000; i++ {
		row := db.QueryRow("SELECT upper('hello world') as uppercased")
		if err := row.Scan(&result); err != nil {
			panic(err)
		}
	}

	elapsed := time.Since(start).Milliseconds()

	fmt.Println(result) // HELLO WORLD
	fmt.Printf("Execution time: %d ms\n", elapsed)
}