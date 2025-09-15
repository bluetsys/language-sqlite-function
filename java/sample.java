import org.sqlite.Function;
import java.sql.*;

public class sample {
    public static void main(String[] args) throws Exception {
        Class.forName("org.sqlite.JDBC");
        Connection conn = DriverManager.getConnection("jdbc:sqlite::memory:");

        // 사용자 정의 upper 함수 등록
        Function.create(conn, "upper", new Function() {
            @Override
            protected void xFunc() throws SQLException {
                if (args() == 1 && value_text(0) != null) {
                    result(value_text(0).toUpperCase());
                } else {
                    result();
                }
            }
        });

        String result = null;

        long start = System.currentTimeMillis();
        for (int i = 0; i < 100_000; i++) {
            try (PreparedStatement stmt = conn.prepareStatement("SELECT upper('hello world') as uppercased")) {
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    result = rs.getString("uppercased");
                }
                rs.close();
            }
        }

        long end = System.currentTimeMillis();
        System.out.println(result); // HELLO WORLD
        System.out.println("Execution time: " + (end - start) + " ms");

        conn.close();
    }
}