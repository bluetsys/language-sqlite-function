rm -rf sqlite-jdbc-3.36.0.3.jar
wget https://repo1.maven.org/maven2/org/xerial/sqlite-jdbc/3.36.0.3/sqlite-jdbc-3.36.0.3.jar
javac -cp .:sqlite-jdbc-3.36.0.3.jar sample.java