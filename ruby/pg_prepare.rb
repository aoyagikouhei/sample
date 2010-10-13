## coding: utf-8
require 'pg'

conn = nil
begin
  conn = PGconn.connect("localhost",5432,"","","test","user","password")
  conn.exec("BEGIN")
  conn.prepare("select", <<EOS
    SELECT
      *
    FROM
      t_user
    WHERE
      id = $1
    FOR UPDATE NOWAIT
EOS
  )
  conn.prepare("update", <<EOS
    UPDATE t_user SET
      name = $2
    WHERE
      id = $1
EOS
  )
  conn.exec_prepared("select", [1])
  conn.exec_prepared("update", [1, "aaa"])
  conn.exec("COMMIT")
rescue => exc
  p exc
  conn.exec("ROLLBACK") if conn
ensure
  conn.close if conn
end