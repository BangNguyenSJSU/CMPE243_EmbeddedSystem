#include "unity.h"
#include <stddef.h>
#include <string.h>

// The source wish to test
#include "line_buffer.h"

#define SIZE_OF_ARRAY(array) sizeof(array) / sizeof(array[0])
#define MAX_SIZE 8

static line_buffer_s obj_line_buffer;
static char buffer_memory[MAX_SIZE];

// ------------------ Test-Setup Section ------------------------

// This method re-initialize the char buffer for the rest of the tests
void setUp(void) {
  // Test True Case
  TEST_ASSERT_TRUE(line_buffer__init(&obj_line_buffer, buffer_memory, SIZE_OF_ARRAY(buffer_memory)));
};

void tearDown(void){};

// ------------------ Test Section ------------------------

void test_line_buffer_init_failure_NULL(void) {
  TEST_ASSERT_FALSE(line_buffer__init(NULL, buffer_memory, MAX_SIZE));
  TEST_ASSERT_FALSE(line_buffer__init(&obj_line_buffer, NULL, MAX_SIZE));
}

void test_line_buffer_innit(void) {

  // Testing an memory
  char array[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++) {
    array[i] = 0;
  }
  TEST_ASSERT_EQUAL_UINT8_ARRAY(array, obj_line_buffer.memory, MAX_SIZE);
  TEST_ASSERT_EQUAL(MAX_SIZE, obj_line_buffer.max_size);
  TEST_ASSERT_EQUAL(0, obj_line_buffer.write_index);
};

void test_line_buffer__add_FULL(void) {
  // in range
  for (int i = 0; i < MAX_SIZE; i++) {
    TEST_ASSERT_TRUE(line_buffer__add_byte(&obj_line_buffer, 't'));
  }
  // out rangre
  TEST_ASSERT_FALSE(line_buffer__add_byte(&obj_line_buffer, 'f'));
}

void test_line_buffer_add_byte_value(void) {
  for (int i = 0; i < MAX_SIZE; i++) {
    TEST_ASSERT_TRUE(line_buffer__add_byte(&obj_line_buffer, 'a' + i));
    TEST_ASSERT_EQUAL_CHAR('a' + i, obj_line_buffer.memory[i]);
  }
}

void test_line_buffer__remove_EMPTY(void) { TEST_ASSERT_FALSE(line_buffer__remove_line(&obj_line_buffer, NULL, 0)) }

void test_line_buffer_remove_NOT_EMPTY(void) {
  // ---- Intit buffer
  for (int i = 0; i < MAX_SIZE - 1; i++) {
    TEST_ASSERT_TRUE(line_buffer__add_byte(&obj_line_buffer, 'a' + i));
    TEST_ASSERT_EQUAL_CHAR('a' + i, obj_line_buffer.memory[i]);
  }

  TEST_ASSERT_TRUE(line_buffer__add_byte(&obj_line_buffer, '\n'));
  TEST_ASSERT_EQUAL_INT(MAX_SIZE, obj_line_buffer.write_index);

  char line_data[12];
  TEST_ASSERT_TRUE(line_buffer__remove_line(&obj_line_buffer, line_data, 12));
}

void test_line_buffer_remove(void) {
  line_buffer__add_byte(&obj_line_buffer, 'a');
  line_buffer__add_byte(&obj_line_buffer, 'b');
  line_buffer__add_byte(&obj_line_buffer, 'c');
  line_buffer__add_byte(&obj_line_buffer, 'd');
  line_buffer__add_byte(&obj_line_buffer, '\n');

  static char array_data[9] = {'z'};
  TEST_ASSERT_TRUE(line_buffer__remove_line(&obj_line_buffer, array_data, 2));
  TEST_ASSERT_EQUAL_STRING("abcd", array_data);
}

// Sample test from: http://books.socialledge.com/books/industrial-applications-with-can-bus/page/lab-gps-and-uart

static void add_to_line_buffer(const char *string) {
  for (size_t index = 0; index < strlen(string); index++) {
    TEST_ASSERT_TRUE(line_buffer__add_byte(&obj_line_buffer, string[index]));
  }
}

void test_line_buffer__nominal_case(void) {
  add_to_line_buffer("abc\n");

  char line[8];
  TEST_ASSERT_TRUE(line_buffer__remove_line(&obj_line_buffer, line, sizeof(line)));
  TEST_ASSERT_EQUAL_STRING(line, "abc");
}

void test_incomplete_line(void) {
  add_to_line_buffer("xy");

  char line[8];
  // Line buffer doesn't contain entire line yet (defined by \n)
  TEST_ASSERT_FALSE(line_buffer__remove_line(&obj_line_buffer, line, sizeof(line)));

  // Line buffer receives \n
  line_buffer__add_byte(&obj_line_buffer, '\n');
  TEST_ASSERT_TRUE(line_buffer__remove_line(&obj_line_buffer, line, sizeof(line)));
  TEST_ASSERT_EQUAL_STRING("xy", line);
}

void test_line_buffer__slash_r_slash_n_case(void) {
  add_to_line_buffer("ab\r\n");

  char line[8];
  TEST_ASSERT_TRUE(line_buffer__remove_line(&obj_line_buffer, line, sizeof(line)));
  TEST_ASSERT_EQUAL_STRING(line, "ab\r");
}

// Line buffer should be able to add multiple lines and we should be able to remove them one at a time
void test_line_buffer__multiple_lines(void) {

  add_to_line_buffer("adb\ncdd\n");

  char line[8];
  TEST_ASSERT_TRUE(line_buffer__remove_line(&obj_line_buffer, line, sizeof(line)));
  TEST_ASSERT_EQUAL_STRING(line, "adb");

  TEST_ASSERT_TRUE(line_buffer__remove_line(&obj_line_buffer, line, sizeof(line)));
  TEST_ASSERT_EQUAL_STRING(line, "cdd");
}

void test_line_buffer__overflow_case(void) {
  // Add chars until full capacity
  for (size_t i = 0; i < MAX_SIZE; i++) {
    TEST_ASSERT_TRUE(line_buffer__add_byte(&obj_line_buffer, 'a' + i));
  }

  // Buffer should be full now
  TEST_ASSERT_FALSE(line_buffer__add_byte(&obj_line_buffer, 'b'));

  // Retreive truncated output (without the newline char)
  // Do not modify this test; instead, change your API to make this test pass
  // Note that line buffer was full with "abcdefgh" but we should only
  // retreive "abcdefg" because we need to write NULL char to line[8]
  char line[8] = {0};
  TEST_ASSERT_TRUE(line_buffer__remove_line(&obj_line_buffer, line, sizeof(line)));
  TEST_ASSERT_EQUAL_STRING(line, "abcdefg");
}