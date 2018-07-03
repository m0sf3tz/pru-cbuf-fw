/*
 * cbuf.h
 *
 *  Created on: Jul 1, 2018
 *      Author: Sam2
 */

#ifndef CBUF_H_
#define CBUF_H_


typedef union
{
     uint32_t     flags;
     struct
     {
      uint32_t overflow : 1;        /* Explanation of foo */
     };
} circular_buf_stats_t;




typedef struct {
    uint32_t head;
    uint32_t tail;
    uint32_t * zeroth;
    circular_buf_stats_t * stat;
    uint32_t size; //of the buffer
    uint8_t full;
} circular_buf_t;



static  void wrap_around_memput(circular_buf_t * cbuf, char * src, uint32_t len);
static  void wrap_around_memget(circular_buf_t * cbuf, char * dest, uint32_t len);
int     circular_buf_reset(circular_buf_t * cbuf, uint32_t * zero, uint32_t size, circular_buf_stats_t * stat);
uint8_t circular_buf_empty(circular_buf_t * cbuf);
uint8_t circular_buf_full(circular_buf_t cbuf);
int     circular_buf_space(circular_buf_t * cbuf);
void    circular_buf_next_head(circular_buf_t * cbuf, uint32_t put);
void    circular_buf_next_tail(circular_buf_t * cbuf, uint32_t get);
int     circular_buf_put(circular_buf_t * cbuf, char * src, size_t len);
int     circular_buf_get(circular_buf_t * cbuf, char * dest, size_t len);

#endif /* CBUF_H_ */
