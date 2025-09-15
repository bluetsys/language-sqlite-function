<?php
// SQLite3::createFunction은 PHP 7.0 이상에서 사용 가능

class MyDB extends SQLite3 {
    function __construct() {
        $this->open(':memory:');
        // 사용자 정의 upper 함수 등록
        $this->createFunction('upper', 'strtoupper', 1);
    }
}

$db = new MyDB();

$result = '';
$res = $db->querySingle("SELECT upper('hello world') as uppercased", true);
$result = $res['uppercased'];

$start = microtime(true);
for ($i = 0; $i < 100000; $i++) {
    $res = $db->querySingle("SELECT upper('hello world') as uppercased", true);
    $result = $res['uppercased'];
}

$end = microtime(true);

echo $result . "\n"; // HELLO WORLD
echo "Execution time: " . round(($end - $start) * 1000) . " ms\n";
?>