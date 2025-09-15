#include <iostream>
#include <sqlite3.h>
#include <chrono>
#include <cctype>
#include <string>

// 사용자 정의 함수: 입력 문자열을 대문자로 변환
void upper_func(sqlite3_context *context, int argc, sqlite3_value **argv)
{
    if (argc == 1 && sqlite3_value_type(argv[0]) == SQLITE_TEXT)
    {
        const unsigned char *input = sqlite3_value_text(argv[0]);
        std::string result(reinterpret_cast<const char *>(input));
        for (auto &c : result)
            c = std::toupper(static_cast<unsigned char>(c));
        sqlite3_result_text(context, result.c_str(), -1, SQLITE_TRANSIENT);
    }
    else
    {
        sqlite3_result_null(context);
    }
}

int main()
{
    sqlite3 *db;
    // 메모리 DB 연결
    if (sqlite3_open(":memory:", &db) != SQLITE_OK)
    {
        std::cerr << "DB open error\n";
        return 1;
    }

    // 사용자 정의 함수 등록
    if (sqlite3_create_function(db, "upper", 1, SQLITE_UTF8, nullptr, upper_func, nullptr, nullptr) != SQLITE_OK)
    {
        std::cerr << "Function registration error\n";
        sqlite3_close(db);
        return 1;
    }

    // 쿼리 준비
    const char *sql = "SELECT upper('hello world') as uppercased;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Prepare error\n";
        sqlite3_close(db);
        return 1;
    }

    std::string result;

    // 시간 측정 시작
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; ++i)
    {
        // 쿼리 실행 및 결과 추출
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            const unsigned char *uppercased = sqlite3_column_text(stmt, 0);
            result = reinterpret_cast<const char *>(uppercased);
        }
        sqlite3_reset(stmt); // 반복 사용을 위해 리셋
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << result << std::endl; // HELLO WORLD
    std::cout << "Execution time: " << ms << " ms" << std::endl;

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}