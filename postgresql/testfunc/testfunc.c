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
PG_FUNCTION_INFO_V1(testfunc4);
PG_FUNCTION_INFO_V1(testfunc5);

extern Datum testfunc1(PG_FUNCTION_ARGS);
extern Datum testfunc2(PG_FUNCTION_ARGS);
extern Datum testfunc3(PG_FUNCTION_ARGS);
extern Datum testfunc4(PG_FUNCTION_ARGS);
extern Datum testfunc5(PG_FUNCTION_ARGS);

Datum
testfunc1(PG_FUNCTION_ARGS)
{
    PG_RETURN_BOOL(true);
}

Datum
testfunc2(PG_FUNCTION_ARGS)
{
    int64 i = PG_GETARG_INT64(0);
    PG_RETURN_INT64(i+1);
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

Datum
testfunc4(PG_FUNCTION_ARGS)
{
    int64 i = PG_GETARG_INT64(0);
    FuncCallContext *funcctx;
    MemoryContext oldcontext;
    if (SRF_IS_FIRSTCALL())
    {
        funcctx = SRF_FIRSTCALL_INIT();
        oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);
        funcctx->max_calls = 3;
        MemoryContextSwitchTo(oldcontext);
    }
    funcctx = SRF_PERCALL_SETUP();
    if (funcctx->call_cntr < funcctx->max_calls)
    {
        SRF_RETURN_NEXT(funcctx, Int64GetDatum(i + funcctx->call_cntr));
    }
    else
    {
        SRF_RETURN_DONE(funcctx);
    }
}

Datum
testfunc5(PG_FUNCTION_ARGS)
{
    int64 i = PG_GETARG_INT64(0);
    FuncCallContext *funcctx;
    MemoryContext oldcontext;
    if (SRF_IS_FIRSTCALL())
    {
        TupleDesc tupd;
        funcctx = SRF_FIRSTCALL_INIT();
        oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);
        tupd = CreateTemplateTupleDesc(2, false);
        TupleDescInitEntry(tupd, 1, "c1", INT8OID, -1, 0);
        TupleDescInitEntry(tupd, 2, "c2", INT8OID, -1, 0);
        funcctx->max_calls = 3;
        funcctx->user_fctx = tupd;
        MemoryContextSwitchTo(oldcontext);
    }
    funcctx = SRF_PERCALL_SETUP();
    if (funcctx->call_cntr < funcctx->max_calls)
    {
        TupleDesc tupd;
        HeapTupleData tupleData;
        HeapTuple tuple = &tupleData;
        char *values[2];
        Datum result;
        
        tupd = (TupleDesc)funcctx->user_fctx;
         values[0] = palloc(32);
        sprintf(values[0], INT64_FORMAT, i+1+funcctx->call_cntr);
        values[1] = palloc(32);
        sprintf(values[1], INT64_FORMAT, i+2+funcctx->call_cntr);
        tuple = BuildTupleFromCStrings(TupleDescGetAttInMetadata(tupd), values);
        result = TupleGetDatum(TupleDescGetSlot(tuple), tuple);
        
        SRF_RETURN_NEXT(funcctx, result);
    }
    else
    {
        SRF_RETURN_DONE(funcctx);
    }
}