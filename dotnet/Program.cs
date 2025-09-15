using System;
using Microsoft.Data.Sqlite;

using var connection = new SqliteConnection("Data Source=:memory:");
connection.Open();

connection.CreateFunction("upper", (string s) =>
{
    return s.ToUpper();
});

var command = connection.CreateCommand();
command.CommandText = "SELECT upper('hello world') as uppercased;";
var result = command.ExecuteScalar();
var start = DateTime.Now;
for (int i = 0; i < 100000; i++)
{
    result = command.ExecuteScalar();
}
var end = DateTime.Now;
Console.WriteLine(result);
Console.WriteLine($"Execution time: {(end - start).TotalMilliseconds} ms");
