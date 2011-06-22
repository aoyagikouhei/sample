def apply(src) {
  def val = ""
  (0..1).each { year ->
    (1..12).each { month ->
      if (year == 0) {
        val = "e"
      } else {
        val = "o"
      }
      if (month < 10) {
        val = val + "0"
      }
      val = val + month
      print(src.replaceAll("###", val).replaceAll("!!!", year.toString()).replaceAll("&&&", month.toString()))
    }
  }
}

-- テーブル作成

def table = """\
DROP TABLE IF EXISTS t_access_log_### CASCADE;
CREATE TABLE t_access_log_### (
    CHECK (!!! = date_part('year', insert_ts)::int % 2 AND &&& = date_part('month', insert_ts))
) INHERITS (t_access_log);
CREATE INDEX ix_t_access_log_### ON t_access_log_### (insert_ts, session_id);

"""

apply(table)

-- ストアードプロシージャ作成

def prefix = """\
CREATE OR REPLACE FUNCTION t_access_log_insert_trigger()
RETURNS TRIGGER AS \$\$
BEGIN
  IF FALSE THEN
    NULL;
"""

def function = """\
  ELSIF !!! = date_part('year', NEW.insert_ts)::int % 2 AND &&& = date_part('month', NEW.insert_ts) THEN
    INSERT INTO t_access_log_### VALUES (NEW.*);
"""

def postfix = """\
  ELSE
    RAISE EXCEPTION 'Date out of range.  Fix the t_access_log_insert_trigger() function!';
  END IF;
  RETURN NULL;
END;
\$\$
LANGUAGE plpgsql;
"""

print(prefix)
apply(function)
print(postfix)