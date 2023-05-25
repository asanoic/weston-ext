/*
 * Copyright © 2012 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef _WESTON_VERTEX_CLIPPING_H
#define _WESTON_VERTEX_CLIPPING_H

#include <stddef.h>
#include <stdbool.h>
#include <pixman.h>

struct clip_vertex {
	float x, y;
};

struct gl_quad {
	struct clip_vertex polygon[4];
	struct clip_vertex bbox[2];    /* Valid if !axis_aligned. */
	bool axis_aligned;
};

float
float_difference(float a, float b);

int
clip_transformed(const struct clip_vertex *polygon,
		 size_t polygon_len,
		 const struct clip_vertex box[2],
		 struct clip_vertex *restrict vertices);

/*
 * Compute the boundary vertices of the intersection of an arbitrary
 * quadrilateral stored into a 'quad' clipping context and a clipping
 * 'box'. 'box' points to an array of 2 vertices where the values of the 1st
 * vertex are less than or equal to the values of the 2nd vertex. The vertices
 * are written to 'vertices', and the return value is the number of vertices.
 * Vertices are produced in clockwise winding order. Guarantees to produce
 * either zero vertices, or 3-8 vertices with non-zero polygon area.
 */
int
clip_quad(struct gl_quad *quad,
	  const struct clip_vertex box[2],
	  struct clip_vertex *restrict vertices);

/*
 * Utility function calling 'clip_quad' but taking a pixman_box32 pointer as
 * clipping box.
 */
int
clip_quad_box32(struct gl_quad *quad,
		const struct pixman_box32* box,
		struct clip_vertex *restrict vertices);

#endif
