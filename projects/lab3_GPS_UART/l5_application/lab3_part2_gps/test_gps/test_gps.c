// @file test_gps.c
#include "unity.h"

// Mocks
#include "Mockclock.h"
#include "Mockuart.h"

#include "Mockqueue.h"

// We can choose to use real implementation (not Mock) for line_buffer.h
// because this is a relatively trivial module
#include "line_buffer.h"

// Include the source we wish to test
#include "gps.h"

void setUp(void) {}
void tearDown(void) {}

void test_init(void) {}

void test_GPGLL_line_is_ignored(void) {}

void test_GPGGA_coordinates_are_parsed(void) {
  // const char *uart_driver_returned_data = "$GPGGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh\r\n";
  // for(size_t index = 0; index <= strlen(uart_driver_returned_data); index++) {
  //   const char the_char_to_return = uart_driver_returned_data[index];
    
  //   const bool last_char = (index < strlen(uart_driver_returned_data));
  //   uart__get_ExpectAndReturn(UART__3, ptr, 0, last_char);
  //   // TODO: Research on ReturnThruPtr() to make it return the char 'the_char_to_return'
  // }
 
 // gps__run_once();
  
  // TODO: Test gps__get_coordinates():
}

void test_GPGGA_incomplete_line(void) {}

void test_more_that_you_think_you_need(void) {}
