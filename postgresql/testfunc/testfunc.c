#include "postgres.h"
#include "fmgr.h"
#include "funcapi.h"
#include "catalog/pg_type.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

PG_FUNCTION_INFO_V1(testfunc1);
PG_FUNCTION_INFO_V1(testfunc2);
PG_FUNCTION_INFO_V1(testfunc3);

extern Datum testfunc1(PG_FUNCTION_ARGS);
extern Datum testfunc2(PG_FUNCTION_ARGS);
extern Datum testfunc3(PG_FUNCTION_ARGS);

Datum
testfunc1(PG_FUNCTION_ARGS)
{
    PG_RETURN_BOOL(true);
}

Datum
testfunc2(PG_FUNCTION_ARGS)
{
    int32 i = PG_GETARG_INT32(0);
    PG_RETURN_INT32(i+1);
}

Datum
testfunc3(PG_FUNCTION_ARGS)
{
    TupleDesc tupd;
    HeapTupleData tupleData;
    HeapTuple tuple = &tupleData;
    char *values[2];
    Datum result;
    
    int64 i = PG_GETARG_INT64(0);
    
    tupd = CreateTemplateTupleDesc(2, false);
    TupleDescInitEntry(tupd, 1, "c1", INT8OID, -1, 0);
    TupleDescInitEntry(tupd, 2, "c2", INT8OID, -1, 0);
    values[0] = palloc(32);
    sprintf(values[0], INT64_FORMAT, i+1);
    values[1] = palloc(32);
    sprintf(values[1], INT64_FORMAT, i+2);
    
    tuple = BuildTupleFromCStrings(TupleDescGetAttInMetadata(tupd), values);
    result = TupleGetDatum(TupleDescGetSlot(tuple), tuple);
    PG_RETURN_DATUM(result);
}

