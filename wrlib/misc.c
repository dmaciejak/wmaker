/* 
 *  Raster graphics library
 * 
 *  Copyright (c) 1997 Alfredo K. Kojima
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *  
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *  
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <config.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>

#include "wraster.h"


int 
RBevelImage(RImage *image, int bevel_type)
{
    RColor color;
    RColor cdelta;
    int w, h;

    if (image->width<3 || image->height<3)
        return False;

    w = image->width;
    h = image->height;
    if (bevel_type>0) {  /* raised */
        /* top */
        cdelta.alpha = 0;
        cdelta.red = cdelta.green = cdelta.blue = 80;
        ROperateLine(image, RAddOperation, 0, 0, w-1, 0, &cdelta);
        if (bevel_type==RBEV_RAISED3 && w>3)
            ROperateLine(image, RAddOperation, 1, 1, w-3, 1,&cdelta);

        /* left */
        ROperateLine(image, RAddOperation, 0, 1, 0, h-1, &cdelta);
        if (bevel_type==RBEV_RAISED3 && h>3)
            ROperateLine(image, RAddOperation, 1, 2, 1, h-3, &cdelta);

	/* bottom */
        color.alpha = 255;
        color.red = color.green = color.blue = 0;
        cdelta.red = cdelta.green = cdelta.blue = 40;
        if (bevel_type==RBEV_RAISED2 || bevel_type==RBEV_RAISED3) {
            ROperateLine(image, RSubtractOperation, 0, h-2, w-3, 
				   h-2, &cdelta);
            RDrawLine(image, 0, h-1, w-1, h-1, &color);
        } else {
            ROperateLine(image, RSubtractOperation, 0, h-1, w-1, h-1,
				   &cdelta);
        }

	/* right */
        if (bevel_type==RBEV_RAISED2 || bevel_type==RBEV_RAISED3) {
            ROperateLine(image, RSubtractOperation, w-2, 0, w-2, h-2,
				   &cdelta);
            RDrawLine(image, w-1, 0, w-1, h-2, &color);
        } else {
            ROperateLine(image, RSubtractOperation, w-1, 0, w-1, h-2,
				   &cdelta);
        }
    } else { /* sunken */
        cdelta.alpha = 0;
        cdelta.red = cdelta.green = cdelta.blue = 40;
        ROperateLine(image, RSubtractOperation, 0, 0, w-1, 0, 
			       &cdelta);        /* top */
        ROperateLine(image, RSubtractOperation, 0, 1, 0, h-1, 
			       &cdelta);	/* left */
        cdelta.red = cdelta.green = cdelta.blue = 80;
        ROperateLine(image, RAddOperation, 0, h-1, w-1, h-1, &cdelta); /* bottom */
        ROperateLine(image, RAddOperation, w-1, 0, w-1, h-2, &cdelta); /* right */
    }
    return True;
}


int 
RClearImage(RImage *image, RColor *color)
{
    int bytes;
    
    bytes = image->width*image->height;

    if (color->alpha==255) {
	memset(image->data[0], color->red, bytes);
	memset(image->data[1], color->green, bytes);
	memset(image->data[2], color->blue, bytes);
	if (image->data[3])
	  memset(image->data[3], 0xff, bytes);
    } else {
	register int i;
	unsigned char *dr, *dg, *db;
	int alpha, nalpha, r, g, b;

	dr = image->data[0];
	dg = image->data[1];
	db = image->data[2];
    
	r = color->red;
	g = color->green;
	b = color->blue;
	alpha = color->alpha;
	nalpha = 255 - alpha;

	for (i=0; i<bytes; i++) {
	    *dr = (((int)*dr * nalpha) + (r * alpha))/256;
	    *dg = (((int)*dg * nalpha) + (g * alpha))/256;
	    *db = (((int)*db * nalpha) + (b * alpha))/256;
	    dr++;    dg++;    db++;
	}
    }

    return True;
}

