/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors
  Modifications (c) 2024 sbJSON Authors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "unity.h"

static sbJSON item[1];

static void assert_is_value(sbJSON *value_item, int type) {
    TEST_ASSERT_NOT_NULL_MESSAGE(value_item, "Item is NULL.");

    assert_not_in_list(value_item);
    assert_has_type(value_item, type);
    assert_has_no_reference(value_item);
    assert_has_no_const_string(value_item);
    assert_has_no_string(value_item);
}

static void assert_parse_value(const char *string, int type) {
    parse_buffer buffer = {0, 0, 0, 0, {0, 0, 0}};
    buffer.content = (const unsigned char *)string;
    buffer.length = strlen(string) + sizeof("");
    buffer.hooks = global_hooks;

    TEST_ASSERT_TRUE(parse_value(item, &buffer));
    assert_is_value(item, type);
}

static void parse_value_should_parse_null(void) {
    assert_parse_value("null", sbJSON_Null);
    reset(item);
}

static void parse_value_should_parse_true(void) {
    assert_parse_value("true", sbJSON_Bool);
    reset(item);
}

static void parse_value_should_parse_false(void) {
    assert_parse_value("true", sbJSON_Bool);
    reset(item);
}

static void parse_value_should_parse_number(void) {
    assert_parse_value("1.5", sbJSON_Number);
    reset(item);
}

static void parse_value_should_parse_string(void) {
    assert_parse_value("\"\"", sbJSON_String);
    reset(item);
    assert_parse_value("\"hello\"", sbJSON_String);
    reset(item);
}

static void parse_value_should_parse_array(void) {
    assert_parse_value("[]", sbJSON_Array);
    reset(item);
}

static void parse_value_should_parse_object(void) {
    assert_parse_value("{}", sbJSON_Object);
    reset(item);
}

int main(void) {
    /* initialize sbJSON item */
    memset(item, 0, sizeof(sbJSON));
    UNITY_BEGIN();
    RUN_TEST(parse_value_should_parse_null);
    RUN_TEST(parse_value_should_parse_true);
    RUN_TEST(parse_value_should_parse_false);
    RUN_TEST(parse_value_should_parse_number);
    RUN_TEST(parse_value_should_parse_string);
    RUN_TEST(parse_value_should_parse_array);
    RUN_TEST(parse_value_should_parse_object);
    return UNITY_END();
}
