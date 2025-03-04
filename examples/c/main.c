#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "kuzu.h"

int main() {
    kuzu_database db;
    kuzu_connection conn;
    kuzu_database_init("" /* fill db path */, kuzu_default_system_config(), &db);
    kuzu_connection_init(&db, &conn);

    // Create schema.
    kuzu_query_result result;
    kuzu_connection_query(
        &conn, "CREATE NODE TABLE Person(name STRING, expression STRING, PRIMARY KEY(name));", &result);
    kuzu_query_result_destroy(&result);
    // Create nodes.
    kuzu_connection_query(&conn, "CREATE (:Person {name: '哈尔滨工业大学', expression: '根号3加根号2保留小数点后两位'});", &result);
    kuzu_query_result_destroy(&result);
    kuzu_connection_query(&conn, "CREATE (:Person {name: 'UC berkeley', expression: 'f(x)=ln(x)在x=2处的导数'});", &result);
    kuzu_query_result_destroy(&result);

    // Execute a simple query.
    kuzu_connection_query(&conn, "MATCH (a:Person) RETURN a.name AS NAME, a.expression AS EXPRESSION;", &result);

    // Fetch each value.
    kuzu_flat_tuple tuple;
    kuzu_value value;
    printf("test 1\n");
    while (kuzu_query_result_has_next(&result)) {
        kuzu_query_result_get_next(&result, &tuple);

        kuzu_flat_tuple_get_value(&tuple, 0, &value);
        char* name;
        kuzu_value_get_string(&value, &name);

        kuzu_flat_tuple_get_value(&tuple, 1, &value);
        int64_t age;
        kuzu_value_get_int64(&value, &age);

        printf("name: %s, age: %" PRIi64 " \n", name, age);
        kuzu_destroy_string(name);
    }
    kuzu_value_destroy(&value);
    kuzu_flat_tuple_destroy(&tuple);
    kuzu_connection_query(&conn, "MATCH (a:Person) RETURN LOCATE(a.name) AS LOCATION, CALCULATE(a.expression) AS RESULT",&result);

    printf("test 2\n");
    while (kuzu_query_result_has_next(&result)) {
        kuzu_query_result_get_next(&result, &tuple);

        kuzu_flat_tuple_get_value(&tuple, 0, &value);
        char* location;
        kuzu_value_get_string(&value, &location);

        // kuzu_flat_tuple_get_value(&tuple, 1, &value);
        // int64_t result;
        // kuzu_value_get_int64(&value, &result);

        kuzu_flat_tuple_get_value(&tuple, 1, &value);
        char* result;
        kuzu_value_get_string(&value, &result);

        printf("location: %s, result: %s\n",location, result);
        kuzu_destroy_string(location);
        kuzu_destroy_string(result);
    }
    kuzu_value_destroy(&value);
    kuzu_flat_tuple_destroy(&tuple);

    // // Print query result.
    // char* result_string = kuzu_query_result_to_string(&result);
    // printf("%s", result_string);
    // kuzu_destroy_string(result_string);

    kuzu_query_result_destroy(&result);

    kuzu_connection_destroy(&conn);
    kuzu_database_destroy(&db);
    printf("\ntest end\n");
    return 0;
}
